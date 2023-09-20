
void presentation() {
  if (!ble_connection) bleKeyboard.begin();
  byte mode = 0, temp = 100;
  bool home = 0;
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.drawBitmap(10, 20, presentation_icon, 24, 24, 1);
  text("PRESENT", 40, 16);
  text(" MODE ", 46, 34);
  if (ble_connection) oled.drawBitmap(119, 0, Bluetooth_Logo, 8, 8, 1);
  oled.display();
  bool ub = 0, db = 0;
  while (1) {
    if (ble_connection != bleKeyboard.isConnected()) {
      ble_connection = bleKeyboard.isConnected();
      (ble_connection) ? oled.drawBitmap(119, 0, Bluetooth_Logo, 8, 8, 1) : oled.drawBitmap(119, 0, no_connection, 8, 8, 0);
      oled.display();
    }

    byte s = push(SW);
    byte b = push(BW);

    if (ble_connection) {

      if (!digitalRead(down)) {
        (side_press(db) == 1) ? db = 1 : db = 0;
        bleKeyboard.write(KEY_LEFT_ARROW);
      } else db = 0;

      if (!digitalRead(up)) {
        (side_press(ub) == 1) ? ub = 1 : ub = 0;
        bleKeyboard.write(KEY_RIGHT_ARROW);
      } else ub = 0;

      if (s == 1) bleKeyboard.write(KEY_PAGE_UP);
      else if (s == 2) bleKeyboard.write(KEY_HOME);
      if (b == 1) bleKeyboard.write(KEY_PAGE_DOWN);
    }
    if (b == 2) return;
  }
}

void media() {
  if (!ble_connection) bleKeyboard.begin();
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.drawBitmap(10, 20, media_icon, 24, 24, 1);
  text(" MEDIA ", 40, 16);
  text("CONTROL", 40, 34);
  oled.display();
  if (ble_connection) oled.drawBitmap(119, 0, Bluetooth_Logo, 8, 8, 1);
  oled.display();
  while (1) {
    if (ble_connection != bleKeyboard.isConnected()) {
      ble_connection = bleKeyboard.isConnected();
      (ble_connection) ? oled.drawBitmap(119, 0, Bluetooth_Logo, 8, 8, 1) : oled.drawBitmap(119, 0, no_connection, 8, 8, 0);
      oled.display();
    }
    byte s = push(SW);
    byte b = push(BW);
    byte u = push(up);
    byte d = push(down);

    if (ble_connection) {
      if (u == 1)
        for (byte i = 0; i < 5; i++)
          bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
      else if (u == 2) bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);

      if (d == 1)
        for (byte i = 0; i < 5; i++)
          bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
      else if (d == 2) bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);

      if (s == 1) bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
      else if (s == 2) bleKeyboard.write(KEY_MEDIA_MUTE);
      if (b == 1) bleKeyboard.write(KEY_PAGE_DOWN);
    }
    if (b == 2) return;
  }
}

void steering() {
  bool ub = 1, db = 1, sb = 1, bb = 1;
  if (!ble_connection) bleKeyboard.begin();
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.drawBitmap(10, 20, steering_icon, 24, 24, 1);
  text(" STEER ", 40, 16);
  text("CONTROL", 40, 34);
  oled.display();
  if (ble_connection) oled.drawBitmap(119, 0, Bluetooth_Logo, 8, 8, 1);
  oled.display();
  while (1) {
    if (ble_connection != bleKeyboard.isConnected()) {
      ble_connection = bleKeyboard.isConnected();
      (ble_connection) ? oled.drawBitmap(119, 0, Bluetooth_Logo, 8, 8, 1) : oled.drawBitmap(119, 0, no_connection, 8, 8, 0);
      oled.display();
      if (!ble_connection) bleKeyboard.begin();
    }
    if (ble_connection) {
      if (!digitalRead(down)) {
        if (db) {
          bleKeyboard.press(KEY_LEFT_ARROW);
          db = 0;
        }
      } else {
        if (!db) {
          bleKeyboard.release(KEY_LEFT_ARROW);
          db = 1;
        }
      }

      if (!digitalRead(up)) {
        if (ub) {
          bleKeyboard.press(KEY_RIGHT_ARROW);
          ub = 0;
        }
      } else {
        if (!ub) {
          bleKeyboard.release(KEY_RIGHT_ARROW);
          ub = 1;
        }
      }

      if (!digitalRead(SW)) {
        if (sb) {
          bleKeyboard.press(KEY_UP_ARROW);
          sb = 0;
        }
      } else {
        if (!sb) {
          bleKeyboard.release(KEY_UP_ARROW);
          sb = 1;
        }
      }

      if (!digitalRead(BW)) {
        if (bb) {
          bleKeyboard.press(KEY_DOWN_ARROW);
          bb = 0;
        }
      } else {
        if (!bb) {
          bleKeyboard.release(KEY_DOWN_ARROW);
          bb = 1;
        }
      }
    } else bleKeyboard.releaseAll();
  }
}