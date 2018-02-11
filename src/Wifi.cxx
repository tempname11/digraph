#ifndef ___SRC_WIFI___
#define ___SRC_WIFI___
namespace Wifi {//////

struct Config {
  char const * SSID_NAME;
  char const * SSID_PASSWORD;
};

struct Object {
  Config const & CFG;
  Object(Config const & CFG): CFG(CFG) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(CFG.SSID_NAME, CFG.SSID_PASSWORD);
  }
  void run() {}
  bool connected() {
    return WiFi.status() == WL_CONNECTED;
  }
  IPAddress ip() {
    return WiFi.localIP();
  }
};

}////// namespace Wifi
#endif//___SRC_WIFI___
