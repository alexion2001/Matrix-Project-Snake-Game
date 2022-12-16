
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
String const mainMenuOptions[] = {"START","GAME INFO", "HIGH SCORE", "SETTINGS", "ABOUT"};
String const settingsOptions[] = {"DIFFICULTY","LCD CONTRAST", "LCD BRIGHTNESS", "MTX BRIGHTNESS", "SOUNDS","EXIT"};

//current option
int currentOption = 0;
int currentSetting = 0;

//menus boundaries
const int firstPosition = 0;
const int lastPosition = sizeof(mainMenuOptions)/sizeof(String) - 1;
const int lastSettingsPosition = sizeof(settingsOptions)/sizeof(String) - 1;

//highscore variables
int highscore[5];
String highscoreName[5];
String const alphabet[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
//                          0  1  2                                           


//delay time
const int delayMainMenu = 1500;


const byte arrows[][8] = {
{ 
  0b00000,
  0b00100,
  0b01010,
  0b10001,
  0b00000,
  0b00000,
  0b00000,
  0b00000
},{
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10001,
  0b01010,
  0b00100,
  0b00000
   
  
},{
  0b00100,
  0b01010,
  0b10001,
  0b00000,
  0b00000,
  0b10001,
  0b01010,
  0b00100
}
};

const uint8_t LEVELS[][8] = {
{
  0b00000,
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b00000
},{
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b00000
}};


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
  menuMatrix();
  
//set def values for main menu
 inMainMenu = true; 
 inGame = false;
 inSettings = false;

  lcd.createChar(3, arrows[arrowBoth]);
  lcd.createChar(2, arrows[arrowUp]);
  lcd.createChar(1, arrows[arrowDown]);

  lcd.clear();
  lcd.setCursor(4, 0); //title
  lcd.print("MAIN MENU"); 

  lcd.setCursor(1, 1); //current option
  lcd.print(">");
  lcd.print(mainMenuOptions[currentOption]);

  lcd.setCursor(14, 1); 
  //print up or down arrow
  if (currentOption == firstPosition) {
   lcd.write(1);
  } 
  else if (currentOption == lastPosition) {
   lcd.write(2);
  } 
  else{
    lcd.write(3);
  }
  delay(100);
}


void about() {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print(mainMenuOptions[currentOption]); // title


  delay(delayMainMenu / 2);
  int delayOnScroll = 350;
  int printCharacters = 25;

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Title: Snake Game"); //about
  lcd.setCursor(1, 1);
  lcd.print("Author: Alexandra Ion, Git: alexion2001");

  for (int positionCounter = 0; positionCounter < printCharacters; positionCounter++) { // autoscroll to left
    
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

  for (int positionCounter = 0; positionCounter < printCharacters; positionCounter++) { //autoscroll to left
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
  lcd.print("  Easy: 1, Medium: 1.5, Hard: 2");

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

  mainMenu(); // return to main menu


}

void displayScore(){
  // get de top 5 highscore from EEPROM
  int adressPerPlayer = 4;
  int numberOfPlayers = 5;
  int lastPos = adressPerPlayer * numberOfPlayers;
  lastPos += 4;

  for (int index = 5; index < lastPos; index = index + 4){ // get de top 5 highscore
  //read the name
    int letter1 = EEPROM.read(index);
    int letter2 = EEPROM.read(index + 1);
    int letter3 = EEPROM.read(index + 2);
  //read the score
    highscore[index/4 - 1] = EEPROM.read(index + 3);
    highscoreName[index/4 - 1] = alphabet[letter1] + alphabet[letter2]; 
    highscoreName[index/4 - 1] += alphabet[letter3];

    
  }

  int scoreDelay = 1000;
  //print on display the top 5
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("HIGHSCORE"); //title

  delay(scoreDelay);
  
  lastPos = 5;
  for (int index = 0; index < lastPos; index++){
      String player = String(index + 1) + "."; //print the index of player
      player = player + String(highscoreName[index]); // print the name
      player = player + " ";
      player = player + String(highscore[index]); //print the score

      lcd.clear();
      lcd.setCursor(5, 1);
      lcd.print(player);
      Serial.println(player);
     
      delay(scoreDelay);
  }

   mainMenu(); // return to main menu

}

lcdSoundAnimation(){
        
  lcd.createChar(4, LEVELS[0]); // empty
  lcd.createChar(5, LEVELS[1]); //full
  

//title
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print(settingsOptions[currentSetting]); 

  lcd.setCursor(4, 1);
  if (soundMode){
    lcd.write(4);
    lcd.print("ON");
    
    lcd.write(" ");
    lcd.write(5);
    lcd.print("OFF");
  }
  else{
    lcd.write(5);
    lcd.print("ON");
    
    lcd.write(" ");
    lcd.write(4);
    lcd.print("OFF");
  }
  
  
  lcd.setCursor(15, 1);
  lcd.write(3);
}


lcdDifficultyAnimation(int level){
        
  lcd.createChar(4, LEVELS[0]); // empty
  lcd.createChar(5, LEVELS[1]); //full
  

//title
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print(settingsOptions[currentSetting]); 

  lcd.setCursor(0, 1);
  lcd.print("EASY ");
  for (int lvl = 0; lvl < 3; lvl++){
    if(level >= 0){
      lcd.write(5);
    }
    else{
      lcd.write(4);

    }
    level --;
    
  }
  lcd.print(" HARD");
  
  lcd.setCursor(15, 1);
  lcd.write(3);
}


void lcdSettingsAnimation(int level) {
      
  lcd.createChar(4, LEVELS[0]); // empty
  lcd.createChar(5, LEVELS[1]); //full
  

//title
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(settingsOptions[currentSetting]); 

  lcd.setCursor(4, 1);
  lcd.print("-");
  for (int lvl = 0; lvl < 6; lvl++){
    if(level >= 0){
      lcd.write(5);
    }
    else{
      lcd.write(4);

    }
    level --;
    
  }
  lcd.print("+");
  
  lcd.setCursor(15, 1);
  lcd.write(3);
  
}

void enterSettings(){
  //set value for settings
  inMainMenu = false; 
  inSettings = true;
  inGame = false;
    
  lcd.clear();
  lcd.setCursor(2, 0); //title
  lcd.print("SETTINGS MENU"); 

  lcd.setCursor(0, 1); //current option
  lcd.print(">");
  lcd.print(settingsOptions[currentSetting]);

  lcd.setCursor(15, 1); 
  //print up or down arrow
  if (currentSetting == firstPosition) {
   lcd.write(1);
  } 
  else if (currentSetting == lastSettingsPosition) {
   lcd.write(2);
  } 
  else{
    lcd.write(3);
  }
  delay(100);
  


}
void LcdGameUpdate(){
   //dispaly setup
  lcd.clear();
  lcd.setCursor(0, 0); //title
  lcd.print("SNAKE: GAME MODE"); 

  lcd.setCursor(0, 1); //score
  lcd.print("SCORE:"); 
  lcd.print(score); 

  lcd.setCursor(11, 1); //difficulti level
  lcd.print("LVL:");
  if (difficultyLevel == 0){
    lcd.print("E");
  }
  else  if (difficultyLevel == 1){
    lcd.print("M");
  }
  else if (difficultyLevel == 2){
    lcd.print("H");
  }
}

void resetSnake(){
  snake[0][0] = xPos; //head
  snake[0][1] = yPos;
  
  snake[1][0] = xPos; //head
  snake[1][1] = yPos;
  
  for (int pos = 2; pos < maxDots; pos ++){
    snake[pos][0] = -1;
    snake[pos][1] = -1;
  }
}

void gameSetup() {
  
  snakeLen = 2;
  resetSnake();
  LcdGameUpdate();
  lc.clearDisplay(0);// clear screen
  
}

void enterMainMenu(){
  //enter in current selected option
      if (currentOption == 0) // start
      {
        //start the game
        inMainMenu = false; 
        inGame = true;
        inSettings = false;

        resetMatrix(); //all matrix empty
        
        firstFood = true;
        // matrix[xPos][yPos] = 1; // set start position 
        score = 0;

        gameSetup();

      }
      else if (currentOption == 1) // game info
      { //game info
        info();
      }
      else if (currentOption == 2) // highscore
      {//enter score
        displayScore();       
      }
      else if (currentOption == 3) // settings
      {  //enter settings
         enterSettings();
      }
      else if (currentOption == 4) // about
      { //enter about
        about();
      }
}