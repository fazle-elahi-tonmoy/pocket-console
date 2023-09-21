byte menu() {
  oled.clearDisplay();
  byte cl = 0, b = 1, p = 2, flag = 0, list = 11, temp = 1, disp;
  while (1) {
    if (cl != temp) {
      cl = temp;
      oled.clearDisplay();
      display_icon(b, p, cl);
      oled.display();
    }

    if (!digitalRead(up)) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      temp++;
      if (temp > list) {
        temp = 1;
        disp = (temp - 1) / 4 + 1;
        b = disp;
        p = b + 1;
      }
      disp = (temp - 1) / 4 + 1;
      if (disp > p) {
        p++;
        b++;
      }
    }

    else if (!digitalRead(down)) {
      (side_press(flag) == 1) ? flag = 1 : flag = 0;
      temp--;
      if (temp < 1) {
        temp = list;
        disp = (temp - 1) / 4 + 1;
        p = disp;
        b = p - 1;
      }

      disp = (temp - 1) / 4 + 1;
      if (disp < b) {
        p--;
        b--;
      }
    }

    else flag = 0;

    byte r = push(SW);
    if (r) {
      for (int i = 0; i < 4; i++) playNote(selectionMelody[i], 50);
      return cl;
    }
    r = push(BW);
    if (r) {
      for (int i = 0; i < 4; i++) playNote(returnMelody[i], 70);
      return 0;}
  }
}

void text(String t, byte x, byte y) {
  oled.setCursor(x, y);
  oled.print(t);
}