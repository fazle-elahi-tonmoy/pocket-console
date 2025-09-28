void space_jam() {
  u8g2.begin();
  byte bb = push(BW);
  while (!bb) {
    u8g2.setFont(u8g2_font_6x10_tr);
    u8g2.setFontDirection(0);
    u8g2.setFontRefHeightAll();
    st_Setup(u8g2.getU8g2());

    while (!bb) {
      bb = push(SW);
      st_Step(y, 0, !digitalRead(right));
      u8g2.firstPage();

      do {
        st_Draw(0);
      } while (u8g2.nextPage());

      if (!digitalRead(up)) y += 2;
      if (!digitalRead(down)) y -= 2;
    }
  }
}