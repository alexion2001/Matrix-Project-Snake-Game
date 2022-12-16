int difficultyLevel;
int contrastLevel;
int brightnessLevel;
int matrixIntensityLevel;
bool soundMode;

//address in EEPROM
const int difficultyLevelAddress = 0;
const int contrastLevelAddress = 1;
const int brightnessLevelAddress = 2;
const int matrixIntensityLevelAddress = 3;
const int soundModeAddress = 4;

// current lcd display
bool inMainMenu = true; //default 
bool inGame = false;
bool inSettings = false;

bool firstFood = false;

int level;

const byte matrixSize = 8;
bool matrixChanged = true;

// moving dot position
byte xPos = 0;
byte yPos = 0;
byte xLastPos = 0;
byte yLastPos = 0;


//random dot
int randomX = 0;
int randomY = 0;
int randomBombX = 0;
int randomBombY = 0;
const int minValue = 0;
const int maxValue = 8;

byte matrix[matrixSize][matrixSize] = {
  {0, 0, 0, 0, 0, 0, 0, 0}, //0
  {0, 0, 0, 0, 0, 0, 0, 0}, //1
  {0, 0, 0, 0, 0, 0, 0, 0}, //2
  {0, 0, 0, 0, 0, 0, 0, 0}, //3
  {0, 0, 0, 0, 0, 0, 0, 0}, //4
  {0, 0, 0, 0, 0, 0, 0, 0}, //5
  {0, 0, 0, 0, 0, 0, 0, 0}, //6
  {0, 0, 0, 0, 0, 0, 0, 0}  //7
};

byte matrixByte[matrixSize] = {
  B00000000,
  B01000100,
  B00101000,
  B00010000,
  B00010000,
  B00010000,
  B00000000,
  B00000000
};

const int maxDots = 64;
const int coordNumber = 2;
int snake[maxDots][coordNumber]; // the snake dots pos
int snakeDirection;
int snakeLen = 1;

//score
int score = 0;
bool dead = false;

#include <LiquidCrystal.h>
#include <LedControl.h> 
#include <EEPROM.h>

#include "matrixAnimation.h"
#include "highscoreMenu.h"
#include "mainMenu.h"
#include "settingsMenu.h"
#include "subMenus.h"
#include "joystickMovements.h"
#include "demoGame.h"




// EERPROM
//0 - difficulty level
//1 - contrast
//2 - lcd bright
//3 - matrix bright
//4 - sound 
//5-7 player 1
//   567 - name letters numbers
//    8 - score
//9-12 player 2
//13-16 player 3
//17-20 player 4
//21-24 player 5


void setup() {

  lc.shutdown(0, false); // turn off power saving, enables display
  lc.clearDisplay(0);// clear screen

  pinMode(RS, OUTPUT);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(pinSw, INPUT_PULLUP);

  
  //read from EEPROM
  difficultyLevel = EEPROM.read(difficultyLevelAddress); 
  contrastLevel = EEPROM.read(contrastLevelAddress);
  brightnessLevel = EEPROM.read(brightnessLevelAddress);
  matrixIntensityLevel = EEPROM.read(matrixIntensityLevelAddress);
  soundMode = EEPROM.read(soundModeAddress);

  analogWrite(brightnessPin, brightnessLevels[brightnessLevel]);
  analogWrite(contrastPin, contrastLevels[contrastLevel]);
  lc.setIntensity(0,intensityLevels[matrixIntensityLevel]);

  greetings();
  mainMenu();
  Serial.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  readFromJoystick();
  if (inGame){
    blinkFood(); 
    checkUpdate(); // update score and matrix
  }
 
}
