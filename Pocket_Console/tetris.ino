int left_key = down;
int right_key = up;
int change = left;
int speed = right;
#define WIDTH 64
#define HEIGHT 128
const char pieces_S_l[2][2][4] = { { { 0, 0, 1, 1 }, { 0, 1, 1, 2 } }, { { 0, 1, 1, 2 }, { 1, 1, 0, 0 } } };
const char pieces_S_r[2][2][4] = { { { 1, 1, 0, 0 }, { 0, 1, 1, 2 } }, { { 0, 1, 1, 2 }, { 0, 0, 1, 1 } } };
const char pieces_L_l[4][2][4] = { { { 0, 0, 0, 1 }, { 0, 1, 2, 2 } }, { { 0, 1, 2, 2 }, { 1, 1, 1, 0 } }, { { 0, 1, 1, 1 }, { 0, 0, 1, 2 } }, { { 0, 0, 1, 2 }, { 1, 0, 0, 0 } } };
const char pieces_Sq[1][2][4] = { { { 0, 1, 0, 1 }, { 0, 0, 1, 1 } } };
const char pieces_T[4][2][4] = { { { 0, 0, 1, 0 }, { 0, 1, 1, 2 } }, { { 0, 1, 1, 2 }, { 1, 0, 1, 1 } }, { { 1, 0, 1, 1 }, { 0, 1, 1, 2 } }, { { 0, 1, 1, 2 }, { 0, 0, 1, 0 } } };
const char pieces_l[2][2][4] = { { { 0, 1, 2, 3 }, { 0, 0, 0, 0 } }, { { 0, 0, 0, 0 }, { 0, 1, 2, 3 } } };
const short MARGIN_TOP = 19;
const short MARGIN_LEFT = 3;
const short SIZE = 5;
const short TYPES = 6;
word currentType, nextType, rotation;
short pieceX, pieceY;
short piece[2][4];
int interval = 20;
long timer, delayer;
boolean grid[10][18];
boolean b1, b2, b3;

void tetris() {
  oled.setRotation(3);
  oled.clearDisplay();
  drawLayout();
  oled.display();
  randomSeed(analogRead(32) / 4);
  nextType = random(TYPES);
  generate();
  timer = millis();
  while (1) {
    if (push(SW)) ESP.restart();
    if (millis() - timer > interval) {
      checkLines();
      refresh();
      if (nextCollision()) {
        for (short i = 0; i < 4; i++)
          grid[pieceX + piece[0][i]][pieceY + piece[1][i]] = 1;
        generate();
      }

      else pieceY++;
      timer = millis();
    }


    if (!digitalRead(left_key)) {
      if (b1) {
        if (!nextHorizontalCollision(piece, -1)) {
          pieceX--;
          refresh();
        }
        b1 = false;
      }
    } else b1 = true;


    if (!digitalRead(right_key)) {
      if (b2) {
        if (!nextHorizontalCollision(piece, 1)) {
          pieceX++;
          refresh();
        }
        b2 = false;
      }


    } else b2 = true;

    (!digitalRead(speed)) ? interval = 20 : interval = 400;

    if (!digitalRead(change)) {
      if (b3) {
        if (rotation == getMaxRotation(currentType) - 1 && canRotate(0)) rotation = 0;
        else if (canRotate(rotation + 1)) rotation++;
        copyPiece(piece, currentType, rotation);
        refresh();
        b3 = false;
        delayer = millis();
      }
    } else if (millis() - delayer > 50) b3 = true;
  }
}



void checkLines() {
  boolean full;
  for (short y = 17; y >= 0; y--) {
    full = true;
    for (short x = 0; x < 10; x++) full = full && grid[x][y];
    if (full) {
      breakLine(y);
      y++;
    }
  }
}


void breakLine(short line) {
  for (short y = line; y >= 0; y--)
    for (short x = 0; x < 10; x++)
      grid[x][y] = grid[x][y - 1];
  for (short x = 0; x < 10; x++) grid[x][0] = 0;
  score += 10;
}


void refresh() {
  oled.clearDisplay();
  drawLayout();
  drawGrid();
  drawPiece(currentType, 0, pieceX, pieceY);
  oled.display();
}


void drawGrid() {
  for (short x = 0; x < 10; x++)
    for (short y = 0; y < 18; y++)
      if (grid[x][y])
        oled.fillRect(MARGIN_LEFT + (SIZE + 1) * x, MARGIN_TOP + (SIZE + 1) * y, SIZE, SIZE, SSD1306_WHITE);
}


bool nextHorizontalCollision(short piece[2][4], int amount) {


  for (short i = 0; i < 4; i++) {
    short newX = pieceX + piece[0][i] + amount;
    if (newX > 9 || newX < 0 || grid[newX][pieceY + piece[1][i]]) return true;
  }
  return false;
}


bool nextCollision() {
  for (short i = 0; i < 4; i++) {
    short y = pieceY + piece[1][i] + 1;
    short x = pieceX + piece[0][i];
    if (y > 17 || grid[x][y]) return true;
  }
  return false;
}


void generate() {
  currentType = nextType;
  nextType = random(TYPES);
  (currentType != 5) ? pieceX = random(9) : pieceX = random(7);
  pieceY = 0;
  rotation = 0;
  copyPiece(piece, currentType, rotation);
}


void drawPiece(short type, short rotation, short x, short y) {
  for (short i = 0; i < 4; i++)
    oled.fillRect(MARGIN_LEFT + (SIZE + 1) * (x + piece[0][i]), MARGIN_TOP + (SIZE + 1) * (y + piece[1][i]), SIZE, SIZE, SSD1306_WHITE);
}


void drawNextPiece() {
  short nPiece[2][4];
  copyPiece(nPiece, nextType, 0);
  for (short i = 0; i < 4; i++)
    oled.fillRect(50 + 3 * nPiece[0][i], 4 + 3 * nPiece[1][i], 2, 2, SSD1306_WHITE);
}


void copyPiece(short piece[2][4], short type, short rotation) {
  switch (type) {
    case 0:  //L_l
      for (short i = 0; i < 4; i++) {
        piece[0][i] = pieces_L_l[rotation][0][i];
        piece[1][i] = pieces_L_l[rotation][1][i];
      }
      break;
    case 1:  //S_l
      for (short i = 0; i < 4; i++) {
        piece[0][i] = pieces_S_l[rotation][0][i];
        piece[1][i] = pieces_S_l[rotation][1][i];
      }
      break;
    case 2:  //S_r
      for (short i = 0; i < 4; i++) {
        piece[0][i] = pieces_S_r[rotation][0][i];
        piece[1][i] = pieces_S_r[rotation][1][i];
      }
      break;
    case 3:  //Sq
      for (short i = 0; i < 4; i++) {
        piece[0][i] = pieces_Sq[0][0][i];
        piece[1][i] = pieces_Sq[0][1][i];
      }
      break;
    case 4:  //T
      for (short i = 0; i < 4; i++) {
        piece[0][i] = pieces_T[rotation][0][i];
        piece[1][i] = pieces_T[rotation][1][i];
      }
      break;
    case 5:  //l
      for (short i = 0; i < 4; i++) {
        piece[0][i] = pieces_l[rotation][0][i];
        piece[1][i] = pieces_l[rotation][1][i];
      }
      break;
  }
}


short getMaxRotation(short type) {
  if (type == 1 || type == 2 || type == 5) return 2;
  else if (type == 0 || type == 4) return 4;
  else if (type == 3) return 1;
  else return 0;
}


boolean canRotate(short rotation) {
  short piece[2][4];
  copyPiece(piece, currentType, rotation);
  return !nextHorizontalCollision(piece, 0);
}


void drawLayout() {
  oled.drawLine(0, 15, WIDTH, 15, SSD1306_WHITE);
  oled.drawRect(0, 0, WIDTH, HEIGHT, SSD1306_WHITE);
  drawNextPiece();
  char text[6];
  itoa(score, text, 10);
  drawText(text, getNumberLength(score), 7, 4);
}


short getNumberLength(int n) {
  short counter = 1;
  while (n >= 10) {
    n /= 10;
    counter++;
  }
  return counter;
}


void drawText(char text[], short length, int x, int y) {
  oled.setTextSize(1);               // Normal 1:1 pixel scale
  oled.setTextColor(SSD1306_WHITE);  // Draw SSD1306_WHITE text
  oled.setCursor(x, y);              // Start at top-left_key corner
  oled.cp437(true);                  // Use full 256 char 'Code Page 437' font
  for (short i = 0; i < length; i++)
    oled.write(text[i]);
}