#include "Display.cxx"

#ifndef ___SRC_OTA___
#define ___SRC_OTA___
namespace Ota {//////

struct Object {
  Display::Object & display; // FIXME
  Object(Display::Object & display):
    display(display)
  {
    ArduinoOTA.onProgress([&](unsigned int progress, unsigned int total) {
      display.clear();
      display.writeRow(0, "OTA in progress...");
      display.fillRect(0, 24, 128 * progress / total, 40);
      display.transfer();
    });
    ArduinoOTA.begin();
  }
  void run() {
    ArduinoOTA.handle();
  }
};

}////// namespace Ota
#endif//___SRC_OTA___
