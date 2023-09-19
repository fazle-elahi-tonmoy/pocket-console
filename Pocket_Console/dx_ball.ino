byte playerX = 12;
const byte playerW PROGMEM = 18;
const byte brick_count PROGMEM = 34;
byte ballX = 30;
byte ballY = 50;
byte ballDirectionX = 1;
byte ballDirectionY = -1;
byte gameScore = 0;
byte enX[brick_count];
byte enY[brick_count];
bool enL[brick_count];

void DXBall() {
  bricks();
  while (1) {
    checkColision();
    checkButtonsGame();
    drawGame();
  }
}

void drawGame() {
  oled.clearDisplay();
  oled.setCursor(40, 0);
  oled.print(gameScore);
  oled.setCursor(2, 0);
  oled.print("Score:");
  oled.drawLine(0, 9, 127, 9, 1);
  oled.drawLine(0, 9, 0, 63, 1);
  oled.drawLine(127, 9, 127, 63, 1);
  oled.fillRect(playerX, 60, playerW, 2, 1);
  oled.fillCircle(ballX, ballY, 1, 1);

  for (int i = 0; i < brick_count; i++)
    if (enL[i] == 1)
      oled.fillRect(enX[i], enY[i], 8, 2, 1);

  oled.display();
}

void checkButtonsGame() {
  if (!digitalRead(down) && playerX > 1) playerX -= 2;
  if (!digitalRead(up) && playerX < 126 - playerW) playerX += 2;
}

void GameReset() {
  ballX = random(1, 126);
  ballY = 50;
  ballDirectionX = 1;
  ballDirectionY = -1;
  for (int i = 0; i < brick_count; i++)
    enL[i] = 1;
}

void gameOver() {
  oled.setTextColor(1);
  oled.clearDisplay();
  oled.setTextSize(2);
  text("GAME OVER", 11, 12);
  text("SCORE:", 11, 36);
  oled.print(gameScore);
  oled.setTextSize(0);
  oled.display();
  while (digitalRead(SW))
    ;
  gameScore = 0;
  GameReset();
}

void checkColision() {
  if (ballX < 1 || ballX > 126)
    ballDirectionX = ballDirectionX * -1;
  if (ballY < 10)
    ballDirectionY = ballDirectionY * -1;

  if (ballY > 60 && ballX > playerX && ballX < playerX + playerW) {
    ballDirectionY = ballDirectionY * -1;
    // (ballX < (2 * playerX + playerW) / 2) ? ballDirectionX = -1 : ballDirectionX = 1;
  }


  for (int i = 0; i < brick_count; i++)
    if (ballX > enX[i] && ballX < enX[i] + 8 && ballY > enY[i] && ballY < enY[i] + 2 && enL[i] == 1) {
      ballDirectionY = ballDirectionY * -1;
      enL[i] = 0;
      gameScore++;
    }

  ballX = ballX + ballDirectionX;
  ballY = ballY + ballDirectionY;

  if (ballY > 64)
    gameOver();

  if (gameScore % brick_count == 0 && gameScore)
    GameReset();
}

void bricks() {
  byte i = 6;
  for (byte j = 0; j < 10; j++)
    enX[j] = i + j * 12;
  i = 10;
  for (byte j = 10; j < 19; j++)
    enX[j] = i + (j - 10) * 12;
  i = 14;
  for (byte j = 19; j < 27; j++)
    enX[j] = i + (j - 19) * 12;
  i = 18;
  for (byte j = 27; j < 34; j++)
    enX[j] = i + (j - 27) * 12;
  i = 14;
  for (byte j = 0; j < 10; j++)
    enY[j] = i;
  i = 18;
  for (byte j = 10; j < 19; j++)
    enY[j] = i;
  i = 22;
  for (byte j = 19; j < 27; j++)
    enY[j] = i;
  i = 26;
  for (byte j = 27; j < 34; j++)
    enY[j] = i;
  for (byte j = 0; j < brick_count; j++)
    enL[j] = 1;
}