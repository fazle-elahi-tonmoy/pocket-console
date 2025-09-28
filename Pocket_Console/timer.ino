bool selector = 0, timer_ready = 0, timer_running = 0, timer_alarm = 0;
short int timer_minute = 0, timer_second = 0;
uint32_t alarm_timer, alarm_tone;
bool buzzer_state = 0;

void countdown_timer() {
  oled.clearDisplay();
  oled.setTextSize(3);
  timer_disp();
  bool flag = 0;
  while (1) {
    byte s = push(SW);
    if (s == 1) {
      if (timer_ready == 0) {
        timer_ready = 1;
        timer_running = 1;
        alarm_timer = millis();
        timer_disp();
      }

      else {
        if (timer_alarm) {
          timer_alarm = 0;
          noTone(buzzer);
          timer_disp();
        }

        else {
          if (timer_running) timer_running = 0;
          else if (timer_minute || timer_second) {
            timer_running = 1;
            alarm_timer = millis();
          }
          timer_disp();
        }
      }
    }

    else if (s == 2 && !timer_running) {
      timer_alarm = 0;
      if (timer_minute || timer_second) {
        timer_minute = 0;
        timer_second = 0;
        timer_disp();
      }

      else {
        oled.setTextSize(2);
        return;
      }
    }

    if (!timer_ready) {
      if (!digitalRead(up)) {
        (cont_press(flag, up) == 1) ? flag = 1 : flag = 0;
        if (selector) {
          timer_second++;
          if (timer_second > 59) timer_second = 0;
        }

        else {
          timer_minute++;
          if (timer_minute > 99) timer_minute = 0;
        }
        timer_disp();
      }

      else if (!digitalRead(down)) {
        (cont_press(flag, down) == 1) ? flag = 1 : flag = 0;
        if (selector) {
          timer_second--;
          if (timer_second < 0) timer_second = 59;
        }

        else {
          timer_minute--;
          if (timer_minute < 0) timer_minute = 99;
        }
        timer_disp();
      }

      else flag = 0;
    }

    if (!timer_alarm && !timer_running) {
      if (push(left)) {
        selector = 0;
        timer_ready = 0;
        timer_disp();
      }

      if (push(right)) {
        selector = 1;
        timer_ready = 0;
        timer_disp();
      }
    }

    timer_update();
    alarm(timer_alarm);
  }
}

void timer_disp() {
  oled.clearDisplay();
  (timer_minute < 10) ? text("0" + String(timer_minute) + ":", 20, 20) : text(String(timer_minute) + ":", 20, 20);
  (timer_second < 10) ? oled.print("0" + String(timer_second)) : oled.print(timer_second);
  if (!timer_ready) { (!selector) ? oled.drawRoundRect(15, 15, 43, 30, 5, 1) : oled.drawRoundRect(70, 15, 43, 30, 5, 1); }
  oled.display();
}

void timer_update() {
  if (timer_running) {
    if (millis() - alarm_timer > 1000) {
      alarm_timer = millis();
      timer_second--;
      if (timer_second < 0 && timer_minute > 0) {
        timer_second = 59;
        timer_minute--;
      }
      if (!timer_second && !timer_minute) {
        timer_alarm = 1;
        timer_running = 0;
      }
      timer_disp();
    }
  }
}


void alarm(bool a) {
  if (a && millis() - alarm_tone > 100) {
    alarm_tone = millis();
    buzzer_state = !buzzer_state;
    (buzzer_state) ? tone(buzzer, 1000) : noTone(buzzer);
  }
}