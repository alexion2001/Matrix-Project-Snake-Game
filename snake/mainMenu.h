//LCD pins
const byte RS = 9;
const byte enable = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);


byte lcdCols = 16;
byte lcdRows = 2;

//sub menus options
String const mainMenuOptions[] = { "START", "GAME INFO", "HIGH SCORE", "SETTINGS", "ABOUT" };
String const settingsOptions[] = { "DIFFICULTY", "LCD CONTRAST", "LCD BRIGHTNESS", "MTX BRIGHTNESS", "SOUNDS", "RESET HIGHSCORE", "EXIT" };

//current option
int currentOption = 0;
int currentSetting = 0;

//menus boundaries
const int firstPosition = 0;
const int lastPosition = sizeof(mainMenuOptions) / sizeof(String) - 1;
const int lastSettingsPosition = sizeof(settingsOptions) / sizeof(String) - 1;

//highscore variables
int highscore[5];
char highscoreName[15];


//delay time
const int delayMainMenu = 1500;
const int scoreDelay = 1000;

const byte arrows[][8] = {
  { 0b00000,
    0b00100,
    0b01010,
    0b10001,
    0b00000,
    0b00000,
    0b00000,
    0b00000 },
  { 0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b10001,
    0b01010,
    0b00100,
    0b00000


  },
  { 0b00100,
    0b01010,
    0b10001,
    0b00000,
    0b00000,
    0b10001,
    0b01010,
    0b00100 }
};

const uint8_t LEVELS[][8] = {
  { 0b00000,
    0b11111,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b11111,
    0b00000 },
  { 0b00000,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b00000 }
};


const int arrowUp = 0;
const int arrowDown = 1;
const int arrowBoth = 2;


void greetings() {
  lcd.begin(lcdCols, lcdRows);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Are you ready");
  lcd.setCursor(0, 1);
  lcd.print("for some SNAKE ?");

  greetingsMatrix();
}

void mainMenu() {
  //set def values for main menu
  inMainMenu = true;
  inGame = false;
  inSettings = false;
  inScore = false;
  inScroll = false;

  menuMatrix();

  lcd.createChar(3, arrows[arrowBoth]);
  lcd.createChar(2, arrows[arrowUp]);
  lcd.createChar(1, arrows[arrowDown]);

  lcd.clear();
  lcd.setCursor(4, 0);  //title
  lcd.print("MAIN MENU");

  lcd.setCursor(1, 1);  //current option
  lcd.print(">");
  lcd.print(mainMenuOptions[currentOption]);

  lcd.setCursor(14, 1);
  //print up or down arrow
  if (currentOption == firstPosition) {
    lcd.write(1);
  } else if (currentOption == lastPosition) {
    lcd.write(2);
  } else {
    lcd.write(3);
  }
  delay(100);
}


void about() {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print(mainMenuOptions[currentOption]);  // title


  delay(delayMainMenu / 2);
  int delayOnScroll = 350;
  int printCharacters = 25;

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Title: Snake Game");  //about
  lcd.setCursor(1, 1);
  lcd.print("Author: Alexandra Ion, Git: alexion2001");

  for (int positionCounter = 0; positionCounter < printCharacters; positionCounter++) {  // autoscroll to left

    lcd.scrollDisplayLeft();

    delay(delayOnScroll);
  }

  delay(delayMainMenu);

  mainMenu();
}


void info() {
  int delayOnScroll = 350;
  int printCharacters = 20;

  //title
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print(mainMenuOptions[currentOption]);
  delay(delayMainMenu / 2);
  // Instruction 1
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("  Move the snake with the joystick.");

  for (int positionCounter = 0; positionCounter < printCharacters; positionCounter++) {  //autoscroll to left
    lcd.scrollDisplayLeft();
    delay(delayOnScroll);
  }
  delay(delayMainMenu / 2);
  // Instruction 2
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("  Eat as much food as possible.");

  for (int positionCounter = 0; positionCounter < printCharacters; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(delayOnScroll);
  }
  delay(delayMainMenu / 2);
  // Instruction 3
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("  Food points:");
  lcd.setCursor(1, 1);
  lcd.print("  Easy: 1, Medium: 2, Hard: 3");

  for (int positionCounter = 0; positionCounter < printCharacters; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(delayOnScroll);
  }
  delay(delayMainMenu / 2);
  // Instruction 4
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("  Avoid the bombs on hard mode");

  for (int positionCounter = 0; positionCounter < printCharacters; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(delayOnScroll);
  }
  delay(delayMainMenu / 2);

  mainMenu();  // return to main menu
}

void readScore() {
  int indexInHighscore = 0;

  for (int index = 5; index < lastPos; index = index + 4) {  // get de top 5 highscore
                                                             //read the name
   

    int letter1 = EEPROM.read(index);
    int letter2 = EEPROM.read(index + 1);
    int letter3 = EEPROM.read(index + 2);

    //read the score
    char first = letter1;
    char second = letter2;
    char third = letter3;


    highscore[index / 4 - 1] = EEPROM.read(index + 3); //score
    highscoreName[indexInHighscore] = first;
    highscoreName[indexInHighscore + 1] = second;
    highscoreName[indexInHighscore + 2] = third;

    indexInHighscore += 3;

    
  }
}

void displayScore() {
  readScore();
   int indexInHighscore = 0;

  //print on display the top 5
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("HIGHSCORE");  //title

  delay(scoreDelay);


  int lastPosArray = 5;
  for (int index = 0; index < lastPosArray; index++) {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("HIGHSCORE");

    lcd.setCursor(3, 1);
    lcd.print(index + 1); //place index
    lcd.print(". ");
    lcd.print(highscoreName[indexInHighscore]); //name
    lcd.print(highscoreName[indexInHighscore + 1]);
    lcd.print(highscoreName[indexInHighscore + 2]);
    lcd.print(" ");
    lcd.print(highscore[index]); //score

    delay(scoreDelay);
    indexInHighscore += 3;
  }

  mainMenu();  // return to main menu
}


void lcdSoundAnimation() {
  //error message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sorry, the sound");
  lcd.setCursor(2, 1);
  lcd.print("is off today");

  lcd.createChar(4, LEVELS[0]);  // empty
  lcd.createChar(5, LEVELS[1]);  //full


  //title
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print(settingsOptions[currentSetting]);

  lcd.setCursor(4, 1);
  if (soundMode) {
    lcd.write(4);
    lcd.print("ON");

    lcd.write(" ");
    lcd.write(5);
    lcd.print("OFF");
  } else {
    lcd.write(5);
    lcd.print("ON");

    lcd.write(" ");
    lcd.write(4);
    lcd.print("OFF");
  }


  lcd.setCursor(15, 1);
  lcd.write(3);
}


void lcdDifficultyAnimation(int level) {

  lcd.createChar(4, LEVELS[0]);  // empty
  lcd.createChar(5, LEVELS[1]);  //full


  //title
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print(settingsOptions[currentSetting]);

  lcd.setCursor(0, 1);
  lcd.print("EASY ");
  for (int lvl = 0; lvl < 3; lvl++) {
    if (level >= 0) {
      lcd.write(5);
    } else {
      lcd.write(4);
    }
    level--;
  }
  lcd.print(" HARD");

  lcd.setCursor(15, 1);
  lcd.write(3);
}


void lcdSettingsAnimation(int level) {

  lcd.createChar(4, LEVELS[0]);  // empty
  lcd.createChar(5, LEVELS[1]);  //full


  //title
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(settingsOptions[currentSetting]);

  lcd.setCursor(4, 1);
  lcd.print("-");
  for (int lvl = 0; lvl < 6; lvl++) {
    if (level >= 0) {
      lcd.write(5);
    } else {
      lcd.write(4);
    }
    level--;
  }
  lcd.print("+");

  lcd.setCursor(15, 1);
  lcd.write(3);
}

void lcdResetHightscore() {
  int defLetter = 65;
  int defScore = 0;
  //update in EEPROM
  for (int index = 5; index < lastPos; index = index + 4) {
    EEPROM.update(index, defLetter);  // def name AAA
    EEPROM.update(index + 1, defLetter);
    EEPROM.update(index + 2, defLetter);
    EEPROM.update(index + 3, defScore);
  }

  //title
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hightscore reset");

  lcd.setCursor(5, 1);
  lcd.print("done");

  delay(scoreDelay);
}

void enterSettings() {
  //set value for settings
  inMainMenu = false;
  inSettings = true;
  inGame = false;
  inScore = false;
  nameChange = false;
  inScroll = false;

  settingsMatrix();

  lcd.clear();
  lcd.setCursor(2, 0);  //title
  lcd.print("SETTINGS MENU");

  lcd.setCursor(0, 1);  //current option
  lcd.print(">");
  lcd.print(settingsOptions[currentSetting]);

  lcd.setCursor(15, 1);
  //print up or down arrow
  if (currentSetting == firstPosition) {
    lcd.write(1);
  } else if (currentSetting == lastSettingsPosition) {
    lcd.write(2);
  } else {
    lcd.write(3);
  }
  delay(100);
}
void LcdGameUpdate() {
  //dispaly setup
  lcd.clear();
  lcd.setCursor(0, 0);  //title
  lcd.print("SNAKE: GAME MODE");

  lcd.setCursor(0, 1);  //score
  lcd.print("SCORE:");
  lcd.print(score);

  lcd.setCursor(11, 1);  //difficulti level
  lcd.print("LVL:");
  if (difficultyLevel == 0) {
    lcd.print("E");
  } else if (difficultyLevel == 1) {
    lcd.print("M");
  } else if (difficultyLevel == 2) {
    lcd.print("H");
  }
}

void resetSnake() {
  snake[0][0] = xPos;  //head
  snake[0][1] = yPos;

  snake[1][0] = xPos;  //head
  snake[1][1] = yPos;

  for (int pos = 2; pos < maxDots; pos++) {
    snake[pos][0] = -1;
    snake[pos][1] = -1;
  }
}

void gameSetup() {

  snakeLen = 2;
  resetSnake();
  LcdGameUpdate();
  lc.clearDisplay(0);  // clear screen
}

void enterMainMenu() {
  //enter in current selected option
  if (currentOption == 0)  // start
  {
    //start the game
    inMainMenu = false;
    inGame = true;
    inSettings = false;
    inScore = false;
    inScroll = false;

    lcd.clear();
    lcd.setCursor(3, 1);  //title
    lcd.print("LOADING...");

    startingMatrix();  //321 starting

    resetMatrix();  //all matrix empty

    firstFood = true;
    score = 0;

    gameSetup();

  } else if (currentOption == 1)  // game info
  {                               //game info
    inScroll = true;
    info();
  } else if (currentOption == 2)  // highscore
  {                               //enter score
    inScroll = true;
    displayScore();

  } else if (currentOption == 3)  // settings
  {                               //enter settings
    enterSettings();
  } else if (currentOption == 4)  // about
  {                               //enter about
    inScroll = true;
    about();
  }
}