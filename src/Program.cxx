#include "Tmp.cxx"
#include "Ota.cxx"
#include "Wifi.cxx"
#include "Unilog.cxx"
#include "Display.cxx"
#include "BuiltinSerial.cxx"

#ifndef ___SRC_PROGRAM___
#define ___SRC_PROGRAM___
namespace Program {//////

struct Config {
  BuiltinSerial::Config BUILTIN_SERIAL;
  Wifi::Config WIFI;
  Unilog::Config UNILOG;
  Display::Config DISPLAY;
  char const * BUILD_TIME;
  IPAddress MULTICAST_IP;
  uint32_t MULTICAST_PORT;
  uint32_t CHIP_ID;
};

struct Object {
  Config const & CFG;
  Object(Config const & CFG):
    CFG(CFG),
    builtinSerial(CFG.BUILTIN_SERIAL),
    wifi(CFG.WIFI),
    unilog(CFG.UNILOG, builtinSerial),
    display(CFG.DISPLAY),
    ota(display)
  {
    Tmp::with([&](Tmp::Buf buf) {
      snprintf(buf, Tmp::size, "ID: %d", CFG.CHIP_ID);
      display.writeRow(0, buf);
    });
    Tmp::with([&](Tmp::Buf buf) {
      snprintf(buf, Tmp::size, "build: %s", CFG.BUILD_TIME);
      display.writeRow(1, buf);
    });
    display.transfer();
    while (!wifi.connected()) {
      delay(1000);
      builtinSerial.write(".");
    }
    builtinSerial.write("\n");
    udp.beginMulticast(
      wifi.ip(),
      CFG.MULTICAST_IP,
      CFG.MULTICAST_PORT
    );
    display.clear();
    display.writeRow(0, WiFi.localIP().toString().c_str());
    display.transfer();
  }

  int nextPingAt = 0;
  void run() {
    wifi.run();
    ota.run();
    int size = udp.parsePacket();
    if (size && udp.remoteIP() != wifi.ip()) {
      Tmp::with([&](Tmp::Buf buf) {
        int len = udp.read(buf, 256 - 1);
        if (len > 0) {
          char buf2[256];
          buf[len] = 0;
          unilog.snprintfLn(buf2, 256, "recv: %s", buf);
          display.clear();
          display.writeRow(0, wifi.ip().toString().c_str());
          display.writeRow(1, buf);
          display.transfer();
        }
      });
    }
    const int ms = millis();
    if (ms > nextPingAt) {
      Tmp::with([&](Tmp::Buf buf) {
        unilog.snprintfLn(buf, Tmp::size, "send: %s", buf);
        snprintf(buf, Tmp::size, "%d/\n%d", ms, CFG.CHIP_ID);
        udp.beginPacketMulticast(
          CFG.MULTICAST_IP,
          CFG.MULTICAST_PORT,
          wifi.ip()
        );
        udp.write(buf);
        udp.endPacket();
      });
      nextPingAt = ms + 1000;
    }
  }

  private:
    BuiltinSerial::Object builtinSerial;
    Wifi::Object wifi;
    Ota::Object ota;
    Unilog::Object unilog;
    Display::Object display;
    WiFiUDP udp; // FIXME
};

}////// namespace Program
#endif//___SRC_PROGRAM___
