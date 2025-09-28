float wall_x[4];
int empty[4];
int flappy_space = 32;
int passage_width = 30;
int score = 0;
int button_status = 0;
float fx = 30.00;
float fy = 22.00;
int bird_direction = 0;
unsigned long current_timer = 0;
int bird_game = 0;
int frame = 0;

void flappy_bird() {
  display.init();
  for (int i = 0; i < 4; i++) {
    wall_x[i] = 128 + ((i + 1) * flappy_space);
    { empty[i] = random(8, 32); }
  }

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  while (1) {
    display.clear();
    if (bird_game == 0) {
      display.setFont(ArialMT_Plain_16);
      display.drawString(0, 4, "Flappy ");
      display.drawXbm(0, 0, 128, 64, pozadina);
      display.drawXbm(20, 32, 14, 9, ptica);
      display.setFont(ArialMT_Plain_10);
      display.drawString(0, 44, "press to start");
      byte r = push(SW);
      if (r == 1) bird_game = 1;
      else if (r == 2) return;
    }

    if (bird_game == 1) {
      display.setFont(ArialMT_Plain_10);
      display.drawString(3, 0, String(score));

      if (digitalRead(SW) == 0) {
        if (button_status == 0) {
          playNote(selectionMelody[3], 50);
          current_timer = millis();
          bird_direction = 1;
          button_status = 1;
        }
      } else button_status = 0;


      for (int j = 0; j < 4; j++) {
        display.setColor(WHITE);
        display.fillRect(wall_x[j], 0, 6, 64);
        display.setColor(BLACK);
        display.fillRect(wall_x[j], empty[j], 6, passage_width);
      }

      display.setColor(WHITE);
      //  display.fillCircle(fx, fy, 4); // igrac
      display.drawXbm(fx, fy, 14, 9, ptica);

      for (int j = 0; j < 4; j++) {
        wall_x[j] = wall_x[j] - 0.01;
        if (wall_x[j] < -7) {
          score = score + 1;
          digitalWrite(indicator, 1);
          empty[j] = random(8, 32);
          wall_x[j] = 128;
        }
      }
      if ((current_timer + 185) < millis())
        bird_direction = 0;


      if (bird_direction == 0)
        fy = fy + 0.01;
      else
        fy = fy - 0.03;

      if (fy > 63 || fy < 0) {
        for (int i = 0; i < 4; i++) playNote(returnMelody[i], 70);
        bird_game = 0;
        fy = 22;
        display.clear();
        display.setFont(ArialMT_Plain_16);
        display.drawString(25, 12, "Game Over");
        display.setFont(ArialMT_Plain_10);
        display.drawString(25, 40, "Score: " + String(score));
        display.display();
        while (!push(SW))
          ;
        score = 0;
        for (int i = 0; i < 4; i++) {
          wall_x[i] = 128 + ((i + 1) * flappy_space);
          empty[i] = random(4, 30);
        }
      }

      for (int m = 0; m < 4; m++)
        if (wall_x[m] <= fx + 7 && fx + 7 <= wall_x[m] + 6) {


          if (fy < empty[m] || fy + 8 > empty[m] + passage_width) {
            for (int i = 0; i < 4; i++) playNote(returnMelody[i], 70);
            bird_game = 0;
            fy = 22;
            display.clear();
            display.setFont(ArialMT_Plain_16);
            display.drawString(25, 12, "Game Over");
            display.setFont(ArialMT_Plain_10);
            display.drawString(25, 40, "Score: " + String(score));
            display.display();
            while (!push(SW))
              ;
            score = 0;
            for (int i = 0; i < 4; i++) {
              wall_x[i] = 128 + ((i + 1) * flappy_space);
              empty[i] = random(8, 32);
            }
          }
        }
      display.drawRect(0, 0, 128, 64);
    }

    display.display();
  }
}