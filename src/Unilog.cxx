#include "BuiltinSerial.cxx"

#ifndef ___SRC_UNILOG___
#define ___SRC_UNILOG___
namespace Unilog {//////

struct Config {
  IPAddress MULTICAST_ADDRESS;
  IPAddress MULTICAST_PORT;
};

struct Object {
  Config const & CFG;
  BuiltinSerial::Object & builtinSerial;
  WiFiUDP udp; // FIXME;
  Object(Config const & CFG, BuiltinSerial::Object & builtinSerial):
    CFG(CFG),
    builtinSerial(builtinSerial)
  {}
  void snprintfLn(char * buf, size_t size, char const * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, size, fmt, args);
    va_end(args);
    writeLn(buf);
  }
  void writeLn(char const * str) {
    builtinSerial.write(str);
    builtinSerial.write("\n");
    udp.beginPacketMulticast(
      CFG.MULTICAST_ADDRESS,
      CFG.MULTICAST_PORT,
      WiFi.localIP() // FIXME
    );
    udp.write(str);
    udp.write("\n");
    udp.endPacket();
  }
};

}////// namespace Unilog
#endif//___SRC_UNILOG___
