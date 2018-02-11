#ifndef ___SRC_BUILTINSERIAL___
#define ___SRC_BUILTINSERIAL___
namespace BuiltinSerial {//////

struct Config {
  uint32_t BAUD_RATE;
};

struct Object {
  Config const & CFG;
  Object(Config const & CFG): CFG(CFG) {
    Serial.begin(CFG.BAUD_RATE);
    Serial.println();
  }
  void snprintf(char * buf, size_t size, char const * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, size, fmt, args);
    va_end(args);
    Serial.print(buf);
  }
  void write(char const * str) {
    Serial.print(str);
  }
};

}////// namespace BuiltinSerial
#endif//___SRC_BUILTINSERIAL___
