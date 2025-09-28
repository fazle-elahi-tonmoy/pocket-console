byte push(byte button) {
  int t = 0;
  bool flag = 1;
  if (!digitalRead(button)) {
    delay(50);  //debounce delay
    while (!digitalRead(button)) {
      delay(10);
      t += 10;
      if (t > 500 && flag) playNote(returnMelody[0], 70), flag = 0;
    }
    if (!flag) return 2;
    else if (t > 0) return 1;
  }
  return 0;
}

byte cont_press(byte a, byte pin_number) {
  short int p = 0;
  while (digitalRead(pin_number) == LOW) {
    p++;
    delay(1);
    if (p >= 500 || (a == 1 && p > 100)) return 1;
  }
  return 0;
}
