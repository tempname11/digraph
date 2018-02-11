#ifndef ___SRC_DISPLAY___
#define ___SRC_DISPLAY___
namespace Display {//////

struct Config {
  uint32_t I2C_ADDRESS;
  uint32_t CLK_PIN;
  uint32_t SDA_PIN;
};

struct Object {
  Config const & CFG;
  Object(Config const & CFG):
    CFG(CFG),
    ssd1306(
      CFG.I2C_ADDRESS,
      CFG.CLK_PIN,
      CFG.SDA_PIN
    )
  {
    ssd1306.init();
    ssd1306.clear();
    ssd1306.flipScreenVertically();
    ssd1306.setFont(ArialMT_Plain_16);
  }
  // FIXME: message-passing!
  void writeRow(int row, char const * str) {
    ssd1306.drawString(0, row * 16, str);
  }
  void fillRect(int x, int y, int w, int h) {
    ssd1306.fillRect(x, y, w, h);
  }
  void clear() {
    ssd1306.clear();
  }
  void transfer() {
    ssd1306.display();
  }
  private:
    SSD1306 ssd1306;
};

}////// namespace Display
#endif//___SRC_DISPLAY___
