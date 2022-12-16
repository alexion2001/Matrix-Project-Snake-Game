
const byte dinPin = 13;
const byte clockPin = 12;
const byte loadPin = 10;


const int delayMainMenuAnimation = 300;

LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); //DIN, CLK, LOAD, No. DRIVER

byte matrixBrightness = 2;

const byte SNAKE[][8] = {
{
  B01111000,
  B11001100,
  B11100000,
  B01110000,
  B00011100,
  B11001100,
  B01111000,
  B00000000
},{
  B11000110,
  B11100110,
  B11110110,
  B11011110,
  B11001110,
  B11000110,
  B11000110,
  B00000000
},{
  B00110000,
  B01111000,
  B11001100,
  B11001100,
  B11111100,
  B11001100,
  B11001100,
  B00000000
},{
  0b11100110,
  0b01100110,
  0b01101100,
  0b01111000,
  0b01101100,
  0b01100110,
  0b11100110,
  0b00000000
},{
  0b11111110,
  0b01100010,
  0b01101000,
  0b01111000,
  0b01101000,
  0b01100010,
  0b11111110,
  0b00000000
}};

const int snakeSize = 5;

const byte smiley[8] = {
  0b00111100,
  0b01000010,
  0b10100101,
  0b10000001,
  0b10100101,
  0b10011001,
  0b01000010,
  0b00111100
};

const byte checkSign[][8] = {
{
  0b00000000,
  0b00000001,
  0b00000010,
  0b00000100,
  0b10001000,
  0b01010000,
  0b00100000,
  0b00000000
}};

void greetingsMatrix() {
  lc.clearDisplay(0);
  for (int letter = 0; letter < snakeSize; letter++){
    for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, SNAKE[letter][row]);
  }
  delay(delayMainMenuAnimation);
  }
  
}

void menuMatrix() { //smiley face
  lc.clearDisplay(0);
  for (int row = 0; row < matrixSize; row++) {
  lc.setRow(0, row, smiley[row]);
  }
    
}

void gameOverMatrix() { 
  lc.clearDisplay(0);
  for (int row = 0; row < matrixSize; row++) {
  lc.setRow(0, row, checkSign[row]);
  }
    
}


// GAME MODE
void updateByteMatrix() {
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, matrixByte[row]);
  }
}
void updateMatrix() {
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      lc.setLed(0, row, col, matrix[row][col]);
    }
  }
}

void resetMatrix() {
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      matrix[row][col] = 0;
    }
  }
}



 