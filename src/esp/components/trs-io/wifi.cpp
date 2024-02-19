
#include "retrostore.h"
#include "wifi.h"
#include "printer.h"
#include "ntp_sync.h"
#include "trs-fs.h"
#ifdef CONFIG_TRS_IO_PP
#include "fs-roms.h"
#include "fs-spiffs.h"
#endif
#include "smb.h"
#include "ota.h"
#include "led.h"
#include "io.h"
#include "settings.h"
#include "event.h"
#include "ntp_sync.h"
#include "esp_wifi.h"
#include "esp_spiffs.h"
#include "esp_mock.h"
#include "version.h"
#include "mdns.h"
#include "esp_event.h"
#include "esp_log.h"
#include "mongoose.h"
#include "web_debugger.h"
#include <string.h>
#include "cJSON.h"


#define SSID "TRS-IO"
#define MDNS_NAME "trs-io"

static const char* TAG = "TRS-IO wifi";


static uint8_t status = RS_STATUS_WIFI_CONNECTING;

uint8_t* get_wifi_status()
{
  return &status;
}


static char ip[16] = {'-', '\0'};

const char* get_wifi_ip()
{
  return ip;
}

static void event_handler(void* arg, esp_event_base_t event_base,
                          int32_t event_id, void* event_data)
{
  if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
    esp_wifi_connect();
  } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
    ESP_LOGI(TAG,"connect to the AP fail");
    status = RS_STATUS_WIFI_NOT_CONNECTED;
    evt_signal(EVT_WIFI_DOWN);
    esp_wifi_connect();
    set_led(true, false, false, false, false);
  } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
    ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
    snprintf(ip, sizeof(ip), IPSTR, IP2STR(&event->ip_info.ip));
    ESP_LOGI(TAG, "Got IP: %s", ip);
    status = RS_STATUS_WIFI_CONNECTED;
    set_led(false, true, false, false, true);
    evt_signal(EVT_WIFI_UP);
  } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED) {
    evt_signal(EVT_START_MG);
    wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
    ESP_LOGI(TAG, "Station "MACSTR" join, AID=%d", MAC2STR(event->mac), event->aid);
  } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STADISCONNECTED) {
    wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
    ESP_LOGI(TAG, "Station "MACSTR" leave, AID=%d", MAC2STR(event->mac), event->aid);
    evt_signal(EVT_WIFI_DOWN);
    status = RS_STATUS_WIFI_NOT_CONNECTED;
    ip[0] = '-';
    ip[1] = '\0';
    set_led(true, false, false, false, false);
    esp_wifi_connect();
  }
}

void set_wifi_credentials(const char* ssid, const char* passwd)
{
  // Store credentials and reboot
  settings_set_wifi_ssid(ssid);
  settings_set_wifi_passwd(passwd);
  settings_commit();
  esp_restart();
}



//-----------------------------------------------------------------
// Web server

#define PRINTER_QUEUE_SIZE 100

static mg_queue prn_queue;
static int num_printer_sockets = 0;

typedef void (*settings_set_t)(const string&);
typedef string& (*settings_get_t)();

static bool extract_post_param(struct mg_http_message* message,
                               const char* param,
                               settings_set_t set,
                               settings_get_t get,
                               size_t max_len)
{
  // SMB URL is the longest parameter
  static char buf[MAX_LEN_SMB_URL + 1] EXT_RAM_ATTR;

  mg_http_get_var(&message->body, param, buf, sizeof(buf));
  // In case someone tries to force a buffer overflow
  buf[max_len + 1] = '\0';

  string& orig = get();
  if (strcmp(orig.c_str(), buf) == 0) {
    // Setting has not changed
    return false;
  }
  set(string(buf));
  return true;
}

static bool mongoose_handle_config(struct mg_http_message* message,
                                   char** response,
                                   const char** content_type)
{
  bool reboot = false;
  bool smb_connect = false;

  *response = "";
  *content_type = "text/plain";

  reboot |= extract_post_param(message, "ssid", settings_set_wifi_ssid, settings_get_wifi_ssid, MAX_LEN_WIFI_SSID);
  reboot |= extract_post_param(message, "passwd", settings_set_wifi_passwd, settings_get_wifi_passwd, MAX_LEN_WIFI_PASSWD);
  extract_post_param(message, "tz", settings_set_tz, settings_get_tz, MAX_LEN_TZ);
  set_timezone();

  smb_connect |= extract_post_param(message, "smb_url", settings_set_smb_url, settings_get_smb_url, MAX_LEN_SMB_URL);
  smb_connect |= extract_post_param(message, "smb_user", settings_set_smb_user, settings_get_smb_user, MAX_LEN_SMB_USER);
  smb_connect |= extract_post_param(message, "smb_passwd", settings_set_smb_passwd, settings_get_smb_passwd, MAX_LEN_SMB_PASSWD);

  settings_commit();

  if (smb_connect) {
    init_trs_fs_smb();
  }

  return reboot;
}

static void mongoose_handle_status(struct mg_http_message* message,
                                   char** response,
                                   const char** content_type)
{
  static char* resp = NULL;

  if (resp != NULL) {
    free(resp);
    resp = NULL;
  }

  cJSON* s = cJSON_CreateObject();
  cJSON_AddNumberToObject(s, "hardware_rev", TRS_IO_HARDWARE_REVISION);
  cJSON_AddNumberToObject(s, "vers_major", TRS_IO_VERSION_MAJOR);
  cJSON_AddNumberToObject(s, "vers_minor", TRS_IO_VERSION_MINOR);
  cJSON_AddNumberToObject(s, "wifi_status", status);
  cJSON_AddStringToObject(s, "ip", get_wifi_ip());

  string& ssid = settings_get_wifi_ssid();
  string& passwd = settings_get_wifi_passwd();
  string& tz = settings_get_tz();
  string& smb_url = settings_get_smb_url();
  string& smb_user = settings_get_smb_user();
  string& smb_passwd = settings_get_smb_passwd();

  if (!ssid.empty()) {
    cJSON_AddStringToObject(s, "ssid", ssid.c_str());
  }
  if (!passwd.empty()) {
    cJSON_AddStringToObject(s, "passwd", passwd.c_str());
  }
  if (!tz.empty()) {
    cJSON_AddStringToObject(s, "tz", tz.c_str());
  }
  if (!smb_url.empty()) {
    cJSON_AddStringToObject(s, "smb_url", smb_url.c_str());
  }
  if (!smb_user.empty()) {
    cJSON_AddStringToObject(s, "smb_user", smb_user.c_str());
  }
  if (!smb_passwd.empty()) {
    cJSON_AddStringToObject(s, "smb_passwd", smb_passwd.c_str());
  }

  time_t now;
  struct tm timeinfo;
  time(&now);
  localtime_r(&now, &timeinfo);
  char* time;
  asprintf(&time, "%d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
  cJSON_AddStringToObject(s, "time", time);
  free(time);

  const char* smb_err = get_smb_err_msg();
  if (smb_err != NULL) {
    cJSON_AddStringToObject(s, "smb_err", smb_err);
  }

  const char* posix_err = get_posix_err_msg();
  if (posix_err != NULL) {
    cJSON_AddStringToObject(s, "posix_err", posix_err);
  }

  cJSON_AddBoolToObject(s, "has_sd_card", trs_fs_has_sd_card_reader());

  const char* frehd_msg = get_frehd_msg();
  if (frehd_msg != NULL) {
    cJSON_AddStringToObject(s, "frehd_loaded", frehd_msg);
  }

  resp = cJSON_PrintUnformatted(s);
  *response = resp;
  cJSON_Delete(s);

  *content_type = "application/json";
}

static void mongoose_event_handler(struct mg_connection *c,
                                   int event, void *eventData, void *fn_data)
{
  static bool reboot = false;

  // Return if the web debugger is handling the request.
  if (trx_handle_http_request(c, event, eventData, fn_data)) {
    return;
  }

  switch (event) {
  case MG_EV_HTTP_MSG:
    {
      struct mg_http_message* message = (struct mg_http_message*) eventData;
      char* response = NULL;
      int response_len = 0;
      const char* content_type = "text/html";

      if (mg_http_match_uri(message, "/config")) {
        reboot = mongoose_handle_config(message, &response, &content_type);
        response_len = strlen(response);
      } else if (mg_http_match_uri(message, "/status")) {
        mongoose_handle_status(message, &response, &content_type);
        response_len = strlen(response);
      } else if (mg_http_match_uri(message, "/log")) {
        num_printer_sockets++;
        mg_ws_upgrade(c, message, NULL);
        return;
      }

      if (response != NULL) {
        mg_printf(c, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nConnection: close\r\nContent-Length: %d\r\n\r\n", content_type, response_len);
        mg_send(c, response, response_len);
#ifdef CONFIG_TRS_IO_PP
      } else if (mg_http_match_uri(message, "/roms/php/connector.minimal.php")) {
        process_file_browser_req(c, message);
      } else if (strncmp(message->uri.ptr, "/roms", 5) == 0) {
        static const struct mg_http_serve_opts opts = {.root_dir = "/elFinder"};
        mg_http_serve_dir(c, (struct mg_http_message*) eventData, &opts);
#endif
      } else {
        static const struct mg_http_serve_opts opts = {.root_dir = "/html"};
        mg_http_serve_dir(c, (struct mg_http_message*) eventData, &opts);
      }
    }
    break;
  case MG_EV_CLOSE:
    {
      if (c->is_websocket) {
        num_printer_sockets--;
      }
    }
    break;
  case MG_EV_POLL:
    {
      if (reboot) {
        esp_restart();
      }

      char *ptr;
      size_t len;
      while ((len = mg_queue_next(&prn_queue, &ptr)) > 0) {
        assert(len == 1);
        const char* p = charToUTF8(*ptr);
        for (struct mg_connection* t = c->mgr->conns; t != NULL; t = t->next) {
          if (!t->is_websocket) continue;  // Ignore non-websocket connections
          mg_ws_send(t, p, strlen(p), WEBSOCKET_OP_TEXT);
        }
        mg_queue_del(&prn_queue, 1);
      }
    }
    break;
  }
}

void trs_printer_write(const char ch)
{
  if (num_printer_sockets != 0) {
    char *ptr;
    if (mg_queue_book(&prn_queue, &ptr, 1) < 1) {
      // Not enough space
    } else {
      *ptr = ch;
      mg_queue_add(&prn_queue, 1);
    }
  }
}

uint8_t trs_printer_read()
{
  return (num_printer_sockets == 0 || prn_queue.head != prn_queue.tail) ? 0xff : 0x30; /* printer selected, ready, with paper, not busy */;
}

static void init_mdns()
{
  // Start mDNS service
  ESP_ERROR_CHECK(mdns_init());
  ESP_ERROR_CHECK(mdns_hostname_set(MDNS_NAME));
  ESP_ERROR_CHECK(mdns_instance_name_set(MDNS_NAME));
  ESP_ERROR_CHECK(mdns_service_add("TRS-IO-WebServer", "_http",
				   "_tcp", 80, NULL, 0));
}

static void mg_task(void* p)
{
  static struct mg_mgr mgr;
  static char printer_buf[100];

  evt_wait(EVT_START_MG);
  ESP_LOGI(TAG, "Starting Mongoose");
  init_time();
  init_mdns();

  // Start Mongoose
  mg_mgr_init(&mgr);
  mg_queue_init(&prn_queue, printer_buf, sizeof(printer_buf));
  mg_http_listen(&mgr, "http://0.0.0.0:80", mongoose_event_handler, &mgr);

  while(true) {
    vTaskDelay(1);
    mg_mgr_poll(&mgr, 1000);
  }
}

//--------------------------------------------------------------------------

void wifi_init_ap()
{
  wifi_config_t wifi_config = {
    .ap = {0}
  };

  esp_netif_create_default_wifi_ap();
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&cfg));

  strcpy((char*) wifi_config.ap.ssid, SSID);
  wifi_config.ap.ssid_len = strlen(SSID);
  strcpy((char*) wifi_config.ap.password, "");
  wifi_config.ap.max_connection = 1;
  wifi_config.ap.authmode = WIFI_AUTH_OPEN;

  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
  ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
}

static void wifi_init_sta()
{
  wifi_config_t wifi_config = {
    .sta = {0},
  };

  status = RS_STATUS_WIFI_CONNECTING;

  string& ssid = settings_get_wifi_ssid();
  string& passwd = settings_get_wifi_passwd();
  strcpy((char*) wifi_config.sta.ssid, ssid.c_str());
  strcpy((char*) wifi_config.sta.password, passwd.c_str());

  ESP_LOGI(TAG, "wifi_init_sta: SSID=%s", (char*) wifi_config.sta.ssid);
  ESP_LOGI(TAG, "wifi_init_sta: Passwd=%s", (char*) wifi_config.sta.password);

  esp_netif_create_default_wifi_sta();
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&cfg));
  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
  ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
}

/*
 * The SPIFFS filesystem does not support directories. Mongoose uses
 * stat() to find out if a path is a directory (to send index.html).
 * We use a custom version of stat() that has the directory paths
 * hardcoded in order to recognize them properly.
 */
static int stat_spiffs(const char *path, size_t *size, time_t *mtime) {
  struct stat st;

  if (size) *size = 0;
  if (mtime) *mtime = 0;
  int len = strlen(path);
  if (len == 0) return 0;
  if (path[len - 1] == '/') {
    return MG_FS_READ | MG_FS_DIR;
  }
  if (strcmp(path, "/html/printer") == 0 || strcmp(path, "/elFinder/roms") == 0) {
    return MG_FS_READ | MG_FS_DIR;
  }
  if (stat(path, &st) != 0) return 0;
  if (size) *size = (size_t) st.st_size;
  if (mtime) *mtime = st.st_mtime;
  return MG_FS_READ | MG_FS_WRITE | (S_ISDIR(st.st_mode) ? MG_FS_DIR : 0);
}

static esp_err_t init_spiffs()
{
  esp_err_t ret;

  ESP_LOGI(TAG, "Initializing SPIFFS");

  static const esp_vfs_spiffs_conf_t conf_html = {
    .base_path = "/html",
    .partition_label = "html",
    .max_files = 2,
    .format_if_mount_failed = false
  };

  ret = esp_vfs_spiffs_register(&conf_html);

  if (ret != ESP_OK) {
    ESP_LOGE(TAG, "Failed to initialize 'html' SPIFFS (%s)", esp_err_to_name(ret));
  }

#ifdef CONFIG_TRS_IO_PP
  static const esp_vfs_spiffs_conf_t conf_elfinder = {
    .base_path = "/elFinder",
    .partition_label = "elFinder",
    .max_files = 5,
    .format_if_mount_failed = false
  };

  ret = esp_vfs_spiffs_register(&conf_elfinder);

  if (ret != ESP_OK) {
    ESP_LOGE(TAG, "Failed to initialize 'elFinder' SPIFFS (%s)", esp_err_to_name(ret));
  }

  static esp_vfs_spiffs_conf_t conf_roms = {
    .base_path = "/roms",
    .partition_label = "roms",
    .max_files = 5,
    .format_if_mount_failed = false
  };

  ret = esp_vfs_spiffs_register(&conf_roms);

  if (ret != ESP_OK) {
    ESP_LOGE(TAG, "Failed to initialize 'roms' SPIFFS (%s)", esp_err_to_name(ret));
  }

  init_fs_roms();
#endif

  // Use custom version of stat() to work around SPIFFS limitations
  mg_fs_posix.st = stat_spiffs;

  return ret;
}

void init_wifi()
{
  ESP_ERROR_CHECK(init_spiffs());
  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(esp_event_loop_create_default());
  ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                ESP_EVENT_ANY_ID,
                                                event_handler,
                                                NULL,
                                                NULL));
  ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                IP_EVENT_STA_GOT_IP,
                                                event_handler,
                                                NULL,
                                                NULL));

#ifdef CONFIG_TRS_IO_USE_COMPILE_TIME_WIFI_CREDS
  storage_set_str(WIFI_KEY_SSID, CONFIG_TRS_IO_SSID);
  storage_set_str(WIFI_KEY_PASSWD, CONFIG_TRS_IO_PASSWD);
#endif
  if (settings_has_wifi_credentials()) {
    wifi_init_sta();
  } else {
    status = RS_STATUS_WIFI_NOT_CONFIGURED;
    set_led(false, true, true, true, false);
    wifi_init_ap();
  }
  ESP_ERROR_CHECK(esp_wifi_start());
  ESP_ERROR_CHECK(esp_wifi_set_max_tx_power(8));
  ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE));

  xTaskCreatePinnedToCore(mg_task, "mg", 6000, NULL, 1, NULL, 0);
}
