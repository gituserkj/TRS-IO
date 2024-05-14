

#include "ptrs.h"
#include "cass.h"
#include "roms.h"
#include "spi.h"
#include "settings.h"
#include <trs-lib.h>
#include <fabgl.h>
#include <esp_log.h>

#define MENU_CONFIGURE 0
#define MENU_ROMS 1
#define MENU_STATUS 2
#define MENU_RESET 3
#define MENU_HELP 4
#define MENU_EXIT 5


static menu_item_t main_menu_items[] = {
  MENU_ITEM(MENU_CONFIGURE, "Configure"),
  MENU_ITEM(MENU_ROMS, "ROMs"),
  MENU_ITEM(MENU_STATUS, "Status"),
  MENU_ITEM(MENU_RESET, "Reset Settings"),
  MENU_ITEM(MENU_HELP, "Help"),
  MENU_ITEM(MENU_EXIT, "Exit"),
  MENU_ITEM_END
};

static menu_t main_menu = {
  .title = "TRS-IO++",
  .items = main_menu_items
};



void configure_pocket_trs(bool is_80_cols)
{
  bool reboot = false;
  bool show_from_left = false;
  uint8_t status;

  init_trs_lib(is_80_cols);

  while(!reboot) {
    status = menu(&main_menu, show_from_left, true);
    if (status == MENU_ABORT || status == MENU_EXIT) {
      break;
    }
    switch (status) {
    case MENU_CONFIGURE:
      reboot = configure_ptrs_settings();
      break;
    case MENU_ROMS:
      configure_roms();
      break;
    case MENU_STATUS:
      ptrs_status();
      break;
    }
    show_from_left = true;
  }

  if (reboot) {
    wnd_popup("Rebooting TRS-IO++...");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }

  exit_trs_lib();

  if (reboot) {
    esp_restart();
  }
}

void ptrs_load_rom()
{
  // Pause Z80
  spi_z80_pause();

  // Upload ROM
  string& rom_file = settings_get_rom(SETTINGS_ROM_M3); //TODO hardcoded for M3
  string rom_path = "/roms/" + rom_file;
  ESP_LOGI("PTRS", "Uploading ROM: '%s'", rom_file.c_str());
  FILE* f = fopen(rom_path.c_str(), "rb");
  if (f != NULL) {
    uint8_t* buf = (uint8_t*) malloc(1024);
    int br;
    uint16_t addr = 0;
    do {
      br = fread(buf, 1, sizeof(buf), f);
      for (int x = 0; x < br; x++) {
        spi_bram_poke(addr++, buf[x]);
      }
    } while (br != 0);
    fclose(f);
    free(buf);
  } else {
    ESP_LOGE("PTRS", "ROM '%s' not found!", rom_file.c_str());
  }

  // Reset and resume Z80
  spi_ptrs_rst();
}

void init_ptrs()
{
  init_cass();
  ptrs_load_rom();
}