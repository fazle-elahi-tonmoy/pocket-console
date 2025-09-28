byte menu() {
  oled.clearDisplay();
  for (int i = 0; i < 4; i++) playNote(selectionMelody[i], 50);
  int cl = 0, b = 1, p = 2, flag = 0, list = 10, temp = 1, disp;
  while (1) {
    if (cl != temp) {
      cl = temp;
      oled.clearDisplay();
      display_icon(b, p, cl);
      oled.display();
    }

    if (push(right)) {
      playNote(selectionMelody[3], 50);
      temp++;
      if (temp > list) {
        temp = disp = 1;
        b = disp;
        p = b + 1;
      }

      else {
        disp = (temp - 1) / 4 + 1;
        if (disp > p) {
          p++;
          b++;
        }
      }
    }

    if (push(down)) {
      playNote(selectionMelody[3], 50);
      temp += 4;
      if (temp > list) {
        temp = temp % 4;
        if (temp == 0) temp = 4;
        disp = (temp - 1) / 4 + 1;
        b = disp;
        p = b + 1;
      }

      else {
        disp = (temp - 1) / 4 + 1;
        if (disp > p) {
          p++;
          b++;
        }
      }
    }

    if (push(left)) {
      playNote(returnMelody[3], 70);
      temp--;
      if (temp < 1) {
        temp = list;
        disp = (temp - 1) / 4 + 1;
        p = disp;
        b = p - 1;
      }

      else {
        disp = (temp - 1) / 4 + 1;
        if (disp < b) {
          p--;
          b--;
        }
      }
    }

    if (push(up)) {
      playNote(returnMelody[3], 70);
      temp -= 4;
      if (temp < 1) {
        temp = ((list / 4) + 1) * 4 + temp;
        if (temp > list) temp -= 4;
        disp = (temp - 1) / 4 + 1;
        p = disp;
        b = p - 1;
      }

      else {
        disp = (temp - 1) / 4 + 1;
        if (disp < b) {
          p--;
          b--;
        }
      }
    }

    byte r = push(SW);
    if (r == 1) {
      for (int i = 0; i < 4; i++) playNote(selectionMelody[i], 50);
      return cl;
    }
    if (r == 2) {
      for (int i = 0; i < 4; i++) playNote(returnMelody[i], 70);
      return 0;
    }
  }
}

void text(String t, byte x, byte y) {
  oled.setCursor(x, y);
  oled.print(t);
}