void display_icon(byte base, byte peak, byte a) {
  byte y_pos;
  if (base == 1) {
    if (a >= 1 && a <= 4) oled.drawRoundRect((a - 1) * 32, 0, 32, 32, 8, 1);
    for (byte i = 0; i < 4; i++) oled.drawBitmap(4 + i * 32, 4, all_icon[i], 24, 24, 1);
  }

  if (base == 2 || peak == 2) {
    (base == 2) ? y_pos = 4 : y_pos = 36;
    if (a >= 5 && a <= 8) oled.drawRoundRect((a - 5) * 32, y_pos - 4, 32, 32, 8, 1);
    for (byte i = 0; i < 4; i++) oled.drawBitmap(4 + i * 32, y_pos, all_icon[i + 4], 24, 24, 1);
  }

  if (base == 3 || peak == 3) {
    (base == 3) ? y_pos = 4 : y_pos = 36;
    if (a >= 9 && a <= 12) oled.drawRoundRect((a - 9) * 32, y_pos - 4, 32, 32, 8, 1);
    for (byte i = 0; i < 2; i++) oled.drawBitmap(4 + i * 32, y_pos, all_icon[i + 8], 24, 24, 1);
  }
}