void display_icon(byte base, byte peak, byte a) {
  byte y_pos;
  if (base == 1) {
    if (a >= 1 && a <= 4) oled.drawRect((a - 1) * 32, 0, 32, 32, 1);
    oled.drawBitmap(4, 4, presentation_icon, 24, 24, 1);
    oled.drawBitmap(36, 4, media_icon, 24, 24, 1);
    oled.drawBitmap(68, 4, steering_icon, 24, 24, 1);
    oled.drawBitmap(100, 4, stopwatch_icon, 24, 24, 1);
  }

  if (base == 2 || peak == 2) {
    (base == 2) ? y_pos = 4 : y_pos = 36;
    if (a >= 5 && a <= 8) oled.drawRect((a - 5) * 32, y_pos - 4, 32, 32, 1);
    oled.drawBitmap(4, y_pos, flappy_bird_icon, 24, 24, 1);
    oled.drawBitmap(36, y_pos, space_ship_icon, 24, 24, 1);
    oled.drawBitmap(68, y_pos, dxball_icon, 24, 24, 1);
    oled.drawBitmap(100, y_pos, snake_icon, 24, 24, 1);
  }

  if (base == 3 || peak == 3) {
    (base == 3) ? y_pos = 4 : y_pos = 36;
    if (a >= 9 && a <= 12) oled.drawRect((a - 9) * 32, y_pos - 4, 32, 32, 1);
    oled.drawBitmap(4, y_pos, tetris_icon, 24, 24, 1);
  }
}