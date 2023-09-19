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
  byte cl = 0, b = 1, p = 5, flag = 0, list = 8, temp = 1;
  while (1) {
    if (cl != temp) {
      cl = temp;
      oled.clearDisplay();
      display_icon(cl);
      oled.display();
    }

    if (!digitalRead(up)) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      temp++;
      if (temp > list) temp = 1;
    }

    else if (!digitalRead(down)) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      temp--;
      if (temp < 1) temp = list;
    }

    else flag = 0;

    byte r = push(SW);
    if (r) return cl;
    r = push(BW);
    if (r) return 0;
  }
}

void text(String t, byte x, byte y) {
  oled.setCursor(x, y);
  oled.print(t);
}