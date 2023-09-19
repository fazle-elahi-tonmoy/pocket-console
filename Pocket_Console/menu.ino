String menu_show(byte a) {
  if (a == 1) return "PRESENTATION MODE ";
  else if (a == 2) return "MEDIA CONTROL     ";
  else if (a == 3) return "DIGITAL STOPWATCH ";
  else if (a == 4) return "FLAPPY BIRD GAME  ";
  else if (a == 5) return "SPACE WAR GAME    ";
  else if (a == 6) return "DX BALL GAME      ";
  else if (a == 7) return "SNAKE GAME        ";
  else if (a == 8) return "TETRIS GAME       ";
}


byte menu() {
  oled.clearDisplay();
  oled.invertDisplay(false);
  oled.setTextSize(1);
  oled.display();
  byte cl = 0, b = 1, p = 5, flag = 0, list = 8, temp = 1;
  while (1) {
    if (cl != temp) {
      cl = temp;
      oled.clearDisplay();
      int j = 0;
      for (byte i = b; i <= p; i++) {
        (i == cl) ? oled.setTextColor(0, 1) : oled.setTextColor(1);
        text(menu_show(i), 2, j + 2);
        j += 12;
      }
      oled.display();
    }

    if (!digitalRead(up)) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      temp++;
      if (temp > p) {
        p = temp;
        b = p - 4;
      }
      if (temp > list) {
        temp = 1;
        b = temp;
        p = b + 4;
      }
    }

    else if (!digitalRead(down)) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      temp--;
      if (temp < b) {
        b = temp;
        p = b + 4;
      }
      if (temp < 1) {
        temp = list;
        p = temp;
        b = p - 4;
      }
    }

    else flag = 0;

    byte r = push(SW);
    if (r) {
      oled.clearDisplay();
      oled.display();
      if (r == 1) return cl;
      else if (r == 2) return 0;
    }
  }
}

void text(String t, byte x, byte y) {
  oled.setCursor(x, y);
  oled.print(t);
}