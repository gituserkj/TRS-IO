# Simulates the TRS-IO++, for easier development.

from http.server import HTTPServer, BaseHTTPRequestHandler
import os, json, time

EXT_TO_MINE_TYPE = {
        ".html": "text/html",
        ".css": "text/css",
        ".ttf": "font/ttf",
        ".js": "text/javascript",
}

STATE_DIR = "state"
DEFAULT_SETTINGS = {
    "color": 1,
    "tz": "GMT-8",
    "ssid": "fandango",
    "passwd": "22PineCreekSLO",
    "smb_url": "smb://unifi/TRS-IO/smb-m3",
    "smb_user": "lk",
    "smb_passwd": "XXX"
}

def createStateDirIfNecessary():
    global STATE_DIR

    if not os.path.isdir(STATE_DIR):
        os.mkdir(STATE_DIR)

def getSettingsPathname():
    return os.path.join(STATE_DIR, "settings.json")

def readSettings():
    path = getSettingsPathname()
    if os.path.exists(path):
        settings = json.load(open(path))
    else:
        settings = DEFAULT_SETTINGS

    return settings

def writeSettings(settings):
    createStateDirIfNecessary()
    path = getSettingsPathname()
    f = open(path, "w")
    json.dump(settings, f, indent="    ")
    f.close()

def makeStatus():
    settings = readSettings()

    t = time.localtime()
    status = {
        "hardware_rev": 1,
        "vers_major": 2,
        "vers_minor": 0,
        "wifi_status": 2,
        "ip": "192.168.1.188",
        "config": 0, # only for TRS-IO++
        "time": "%d:%02d" % (t.tm_hour, t.tm_min),
        "smb_err": "Session setup failed with (0xc000006d) STATUS_LOGON_FAILURE",
        "posix_err": "Failed to initialize the SD card",
        "has_sd_card": True,
        "frehd_loaded": "FREHD.ROM not found",

        "color": settings["color"],
        "tz": settings["tz"],
        "ssid": settings["ssid"],
        "passwd": settings["passwd"],
        "smb_url": settings["smb_url"],
        "smb_user": settings["smb_user"],
        "smb_passwd": settings["smb_passwd"]
    }

    return status


class TrsIoRequestHandler(BaseHTTPRequestHandler):
    # Handler for GET requests.
    def do_GET(self):
        # Procedural paths.
        if self.path == "/get-roms":
            return self.handle_get_roms()
        if self.path == "/status":
            return self.handle_status()

        # Redirects.
        if self.path in ["/printer", "/roms"]:
            self.send_response(307)
            self.send_header("Location", self.path + "/")
            self.end_headers()
            return

        # Static paths.
        if self.path.startswith("/printer/"):
            return self.serve_static_files(self.path[9:], "../esp/html/printer")
        if self.path.startswith("/roms/"):
            return self.serve_static_files(self.path[6:], "../esp/elFinder/roms")
        return self.serve_static_files(self.path[1:], "../esp/html")

    # Handler for POST requests.
    def do_POST(self):
        if self.path == "/config":
            return self.handle_config()
        self.send_error(404)

    # Serve static files from a local directory.
    def serve_static_files(self, path, directory):
        while path.startswith("/"):
            path = path[1:]
        if path == "":
            path = "index.html"
        path = os.path.join(directory, path)
        # print(path)

        try:
            contents = open(path, "rb").read()
        except Exception as e:
            # print(e)
            self.send_error(404)
            return

        file_extension = os.path.splitext(path)[1].lower()
        mime_type = EXT_TO_MINE_TYPE.get(file_extension, "application/octet-stream")

        self.send_response(200)
        self.send_header("Content-type", mime_type)
        self.send_header("Content-Length", str(len(contents)))
        self.end_headers()
        self.wfile.write(contents)

    def handle_get_roms(self):
        data = {
            "roms": [
                "trs80m13diag.bin",
                "level2.bin",
                "rsl2.bin",
                "xdrom-full.bin",
                "level1.bin",
                "model3.bin",
                "model3-frehd.bin",
                "rsl2-frehd.bin",
                "xrom-full.bin"
            ],
            "selected": [
                4,
                0,
                6,
                0,
                0
            ]
        }
        self.send_json(data)

    def handle_config(self):
        length = int(self.headers["content-length"])
        request = json.loads(self.rfile.read(length))
        writeSettings(request)
        self.send_json(makeStatus())

    def handle_status(self):
        self.send_json(makeStatus())

    def send_json(self, data):
        self.send_response(200)
        self.send_header("Content-type", "application/json")
        self.end_headers()
        self.wfile.write(bytes(json.dumps(data), "utf-8"))

def main():
    hostname = "localhost"
    port = 8134
    httpd = HTTPServer((hostname, port), TrsIoRequestHandler)
    print(f"Serving at http://{hostname}:{port}/")

    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()
    print("\n")

main()

