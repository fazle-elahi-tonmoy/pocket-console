#include <BleMouse.h>
#include <BleKeyboard.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "SSD1306Wire.h"
#include <Arduino.h>
#include <U8g2lib.h>
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
SSD1306Wire display(0x3c, 21, 22);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
BleKeyboard bleKeyboard("BLE Controller");
BleMouse bleMouse("BLE Mouse");