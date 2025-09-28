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
  bool ub = 0, db = 0, lb = 0, rb = 0;
  while (1) {
    if (ble_connection != bleKeyboard.isConnected()) {
      ble_connection = bleKeyboard.isConnected();
      (ble_connection) ? oled.drawBitmap(119, 0, Bluetooth_Logo, 8, 8, 1) : oled.drawBitmap(119, 0, no_connection, 8, 8, 0);
      oled.display();
    }

    byte s = push(SW);

    if (ble_connection) {

      if (!digitalRead(left)) {
        (cont_press(lb, left) == 1) ? lb = 1 : lb = 0;
        bleKeyboard.write(KEY_LEFT_ARROW);
      } else lb = 0;

      if (!digitalRead(right)) {
        (cont_press(rb, right) == 1) ? rb = 1 : rb = 0;
        bleKeyboard.write(KEY_RIGHT_ARROW);
      } else rb = 0;

      if (!digitalRead(up)) {
        (cont_press(ub, up) == 1) ? ub = 1 : ub = 0;
        bleKeyboard.write(KEY_PAGE_UP);
      } else ub = 0;

      if (!digitalRead(down)) {
        (cont_press(db, down) == 1) ? db = 1 : db = 0;
        bleKeyboard.write(KEY_PAGE_DOWN);
      } else db = 0;

      if (s == 1) bleKeyboard.write(KEY_HOME);
      else if (s == 2) return;
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
    byte u = push(up);
    byte d = push(down);
    byte l = push(left);
    byte r = push(right);

    if (ble_connection) {
      if (u == 1) bleKeyboard.write(KEY_UP_ARROW);
      else if (u == 2) bleKeyboard.write(KEY_PAGE_UP);

      if (d == 1) bleKeyboard.write(KEY_DOWN_ARROW);
      else if (d == 2) bleKeyboard.write(KEY_PAGE_DOWN);

      if (l == 1)
        for (byte i = 0; i < 5; i++)
          bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
      else if (d == 2) bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);

      if (r == 1)
        for (byte i = 0; i < 5; i++)
          bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
      else if (d == 2) bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);

      if (s == 1) bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
      else if (s == 2) return;
    }
    if (b == 2) return;
  }
}

void steering() {
  bool ub = 1, db = 1, lb = 1, rb = 1;
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


    byte r = push(SW);
    if (r == 2) {
      bleKeyboard.releaseAll();
      return;
    }

    if (ble_connection) {
      if (r == 1) bleKeyboard.write(KEY_RETURN);
      if (!digitalRead(down)) {
        if (db) {
          bleKeyboard.press(KEY_DOWN_ARROW);
          db = 0;
        }
      } else {
        if (!db) {
          bleKeyboard.release(KEY_DOWN_ARROW);
          db = 1;
        }
      }

      if (!digitalRead(up)) {
        if (ub) {
          bleKeyboard.press(KEY_UP_ARROW);
          ub = 0;
        }
      } else {
        if (!ub) {
          bleKeyboard.release(KEY_UP_ARROW);
          ub = 1;
        }
      }

      if (!digitalRead(left)) {
        if (lb) {
          bleKeyboard.press(KEY_LEFT_ARROW);
          lb = 0;
        }
      } else {
        if (!lb) {
          bleKeyboard.release(KEY_LEFT_ARROW);
          lb = 1;
        }
      }

      if (!digitalRead(right)) {
        if (rb) {
          bleKeyboard.press(KEY_RIGHT_ARROW);
          rb = 0;
        }
      } else {
        if (!rb) {
          bleKeyboard.release(KEY_RIGHT_ARROW);
          rb = 1;
        }
      }
    }

    else bleKeyboard.releaseAll();
  }
}