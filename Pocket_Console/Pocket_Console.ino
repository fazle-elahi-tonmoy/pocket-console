#include "libraries.h"
#include "bitmaps.h"
#include "space.h"
#define FRAME_COUNT (sizeof(animation) / sizeof(animation[0]))

#define SW 5
#define BW 12
#define up 17
#define down 19
#define left 16
#define right 18
#define indicator 4
#define buzzer 23
bool ble_connection = 0;
int animate = 0;
uint32_t blink;

void setup() {
  pinMode(SW, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(BW, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(indicator, OUTPUT);
  Serial.begin(115200);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(1);
  for (int i = 0; i < 5; i++) playNote(startupMelody[i], 100);
  blink = millis();
}

void loop() {
  byte r = push(SW);
  if (r) {
    r = menu();
    if (r) {
      if (r == 1) presentation();
      else if (r == 2) media();
      else if (r == 3) steering();
      else if (r == 4) stop_watch();
      else if (r == 5) countdown_timer();
      else if (r == 6) flappy_bird();
      else if (r == 7) space_jam();
      else if (r == 8) snake_game();
      else if (r == 9) DXBall();
      else if (r == 10) tetris();
      for (int i = 0; i < 4; i++) playNote(returnMelody[i], 70);
    }
  }

  r = push(BW);
  if (r == 2) bleKeyboard.begin();

  if (millis() - blink > 20) {
    blink = millis();
    start_screen_refresh();
  }
}

void start_screen_refresh() {
  oled.clearDisplay();
  ble_connection = bleKeyboard.isConnected();
  (ble_connection) ? oled.drawBitmap(119, 0, Bluetooth_Logo, 8, 8, 1) : oled.drawBitmap(119, 0, no_connection, 8, 8, 0);
  oled.drawBitmap(0, 8, animation[animate], 48, 48, 1);
  text("POCKET", 55, 16);
  text("DEVICE", 55, 40);
  oled.display();
  animate = (animate + 1) % FRAME_COUNT;
}

void playNote(int frequency, int duration) {
  tone(buzzer, frequency, duration);
}
