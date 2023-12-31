byte hour = 0, minute = 0, second = 0, decimal = 0;
uint32_t m = millis();

void stop_watch() {
  while (1) {
    oled.setTextSize(2);
    drawStop();
    while (digitalRead(SW))
      if (push(BW)) return;
    while (!digitalRead(SW))
      ;
resume:
    m = millis();
    while (digitalRead(SW)) {
      time_count();
      drawStop();
    }
    while (!digitalRead(SW))
      ;

    while (1) {
      byte b = push(BW);
      if (b == 1) {
        hour = 0;
        minute = 0;
        second = 0;
        decimal = 0;
        break;
      } else if (b == 2) return;
      if (push(SW)) goto resume;
    }
  }
}

void drawStop() {
  oled.clearDisplay();
  text("STOPWATCH", 11, 12);
  oled.setCursor(04, 36);
  oled.print(String(hour) + ":");
  (minute < 10) ? oled.print("0" + String(minute) + ":") : oled.print(String(minute) + ":");
  (second < 10) ? oled.print("0" + String(second) + ".") : oled.print(String(second) + ".");
  (decimal < 10) ? oled.print("0" + String(decimal)) : oled.print(decimal);
  oled.display();
}

void time_count() {
  if (millis() - m >= 1000) {
    m += 1000;
    second++;
    if (second > 59) {
      second = 0;
      minute++;
    }
    if (minute > 59) {
      minute = 0;
      hour++;
    }
  }
  decimal = (millis() - m) / 10;
}