void display_icon(byte a) {
  if (a < 9) {
    if (a >= 1 && a <= 4) oled.drawRect((a - 1) * 32, 0, 32, 32, 1);
    oled.drawBitmap(4, 4, presentation_icon, 24, 24, 1);
    oled.drawBitmap(36, 4, media_icon, 24, 24, 1);
    oled.drawBitmap(68, 4, stopwatch_icon, 24, 24, 1);
    oled.drawBitmap(100, 4, flappy_bird_icon, 24, 24, 1);
  }
  if (a < 17) {
    if (a >= 5 && a <= 8) oled.drawRect((a - 5) * 32, 32, 32, 32, 1);
    oled.drawBitmap(4, 36, space_ship_icon, 24, 24, 1);
    oled.drawBitmap(36, 36, dxball_icon, 24, 24, 1);
    oled.drawBitmap(68, 36, snake_icon, 24, 24, 1);
    oled.drawBitmap(100, 36, tetris_icon, 24, 24, 1);
  }
}