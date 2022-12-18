
const byte dinPin = 13;
const byte clockPin = 12;
const byte loadPin = 10;


const int delayAnimation = 300;
const int delayStartingAnimation = 1000;

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

const byte checkSign[8] = {
  0b00000000,
  0b00000001,
  0b00000010,
  0b00000100,
  0b10001000,
  0b01010000,
  0b00100000,
  0b00000000
  };

const byte wrench[8] = {
  
  0b00001100,
  0b00011000,
  0b00011001,
  0b00011111,
  0b00111110,
  0b01110000,
  0b11100000,
  0b11000000
  };

const byte cup[8] = {

  0b01111110,
  0b11111111,
  0b11111111,
  0b01111110,
  0b00111100,
  0b00011000,
  0b00011000,
  0b00111100
  };

const uint8_t digits[][8] = {
{
  0b00000000,
  0b00011000,
  0b00011000,
  0b00111000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b01111110
},{
  0b00000000,
  0b00111100,
  0b01100110,
  0b00000110,
  0b00001100,
  0b00110000,
  0b01100000,
  0b01111110
},{
  0b00000000,
  0b00111100,
  0b01100110,
  0b00000110,
  0b00011100,
  0b00000110,
  0b01100110,
  0b00111100
}};


void greetingsMatrix() {
  lc.clearDisplay(0);
  for (int letter = 0; letter < snakeSize; letter++){
    for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, SNAKE[letter][row]);
  }
  delay(delayAnimation);
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

void settingsMatrix() { 
  lc.clearDisplay(0);
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, wrench[row]);
  }
    
}

void winningMatrix() { 
  lc.clearDisplay(0);
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, cup[row]);
  }
    
}

void startingMatrix() { 
  lc.clearDisplay(0);
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, digits[2][row]);
  }
   delay(delayAnimation);

   lc.clearDisplay(0);
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, digits[1][row]);
  }

   delay(delayAnimation);

   lc.clearDisplay(0);
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, digits[0][row]);
  }

   delay(delayAnimation);
    
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



 