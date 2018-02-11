#include <ArduinoOTA.h>
#include <SSD1306.h>
#undef DISPLAY
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "Program.cxx"

Program::Config const CFG = {
 /* .BUILTIN_SERIAL = */ {
   /* .BAUD_RATE = */ 9600
 },
 /* .WIFI = */ {
   /* .SSID_NAME = */ "lucidity",
   /* .SSID_PASSWORD = */ "bEjS9uxC"
 },
 /* .UNILOG = */ {
   /* .MULTICAST_IP = */ { 239, 82, 66, 1 },
   /* .MULTICAST_PORT = */ 8266
 },
 /* .DISPLAY = */ {
   /* .I2C_ADDRESS = */ 0x3c,
   /* .SDA_PIN = */ D3,
   /* .CLK_PIN = */ D4,
 },
 /* .BUILD_TIME = */ __TIME__,
 /* .MULTICAST_IP = */ { 239, 82, 66, 239 },
 /* .MULTICAST_PORT = */ 8267,
 /* .CHIP_ID = */ ESP.getChipId(),
};

char memory[sizeof(Program::Object)];
void setup() { new(memory) Program::Object(CFG); }
void loop() { reinterpret_cast<Program::Object *>(memory)->run(); }
