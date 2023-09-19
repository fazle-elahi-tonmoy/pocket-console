#include <BleKeyboard.h>
#include "display_libraries.h"
#include "bitmaps.h"
#include "space.h"
BleKeyboard bleKeyboard("BLE Controller");
#define FRAME_COUNT (sizeof(animation) / sizeof(animation[0]))

#define SW 26
#define up 19
#define down 0
#define BW 18
#define indicator 13
bool ble_connection = 0;
int animate = 0;
uint32_t blink;

void setup() {
  pinMode(SW, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(BW, INPUT_PULLUP);
  pinMode(indicator, OUTPUT);
  Serial.begin(115200);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(1);
  blink = millis();
}

void loop() {
  byte r = push(SW);
  if (r) {
    r = menu();
    if (r) {
      if (r == 1) presentation();
      else if (r == 2) media();
      else if (r == 3) stop_watch();
      else if (r == 4) flappy_bird();
      else if (r == 5) space_jam();
      else if (r == 6) DXBall();
      else if (r == 7) snake_game();
      else if (r == 8) tetris();
    }
  }
  if (millis() - blink > 20) {
    blink = millis();
    start_screen_refresh();
  }
}

void start_screen_refresh() {
  oled.clearDisplay();
  oled.drawBitmap(0, 8, animation[animate], 48, 48, 1);
  text("POCKET", 55, 12);
  text("DEVICE", 55, 36);
  oled.display();
  animate = (animate + 1) % FRAME_COUNT;
}
