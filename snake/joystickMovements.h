//pins
const int xPin = A5;
const int yPin = A4;
const int pinSw = 2;

const int minThreshold = 200;
const int maxThreshold = 600;
int xValue = 0;
int yValue = 0;
bool swState = HIGH;

//debounce
long lastTime = 0;
long lastJoyTime = 0;
int interval = 50;
byte reading = LOW;
byte joyState = LOW;
byte lastReading = LOW;
byte joyReading = LOW;
byte lastJoyReading = HIGH;
bool joyMoved = false;



// variable for the game

// const byte moveInterval = 100;
// unsigned long long lastMoved = 0;


void readFromJoystick() {

  //joystick button
  reading = digitalRead(pinSw);

  if (reading != lastReading) {
    lastTime = millis();
  }

  if (millis() - lastTime > interval) {
    if (reading != swState) {
      swState = reading;
      if (swState == LOW) {
        if (inMainMenu) {  //we are in main menu
          enterMainMenu();
        } else if (inSettings) {
          //we are in setting menu
          enterSettingsOptions(currentSetting);
        } else if (inGame) {
          //we are in game mode
          // no button push
        } else if (inScore) {
          //we are in new score menu
          //when button exit this menu
          sortScore();
        } else if (inScroll) {
          mainMenu();
        }
      }
    }
  }
  lastReading = reading;


  ///joystick movements
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);

  if ((xValue > minThreshold && xValue < maxThreshold) || (yValue > minThreshold && yValue < maxThreshold)) {
    joyReading = LOW;
  }
  if ((xValue < minThreshold || xValue > maxThreshold) || (yValue < minThreshold || yValue > maxThreshold)) {
    joyReading = HIGH;
  }

  if (joyReading != lastJoyReading) {
    lastJoyTime = millis();
  }

  if (millis() - lastJoyTime > interval)
    if (joyReading != joyState) {
      joyState = joyReading;
      if (joyReading == HIGH)
        joyMoved = false;
    }

  if (xValue > maxThreshold && joyMoved == false) {  // in sus
    joyMoved = true;
    if (inMainMenu) {  //we are in main menu
      if (currentOption > firstPosition) {
        currentOption--;
        mainMenu();
      }
    } else if (inSettings) {
      //we are in setting menu
      if (currentSetting > firstPosition) {
        currentSetting--;
        enterSettings();
      }
    } else if (inGame) {
      //we are in game mode
      if (snakeDirection != -1 || snakeLen == 2) {  // no 180 degree turn
        snakeDirection = 1;
      }
      //  if (xPos > 0) {
      //     xPos--;
      //   }
      //   else {
      //     xPos = matrixSize - 1;
      //   }
    } else if (inScore) {
      //we are in new score menu
      //change to next letter
      if (name[currentLetter] > 65) {  // A code in ASCII
        name[currentLetter]--;
        nameChange = true;
      } else {
        name[currentLetter] = 90;  //Z
        nameChange = true;
      }
    }
  }
  if (xValue < minThreshold && joyMoved == false) {  //in jos
    joyMoved = true;
    if (inMainMenu) {  //we are in main menu
      if (currentOption < lastPosition) {
        currentOption++;
        mainMenu();
      }
    } else if (inSettings) {
      //we are in setting menu
      if (currentSetting < lastSettingsPosition) {
        currentSetting++;
        enterSettings();
      }
    } else if (inGame) {
      //we are in game mode

      if (snakeDirection != 1 || snakeLen == 2) {  // no 180 degree turn
        snakeDirection = -1;
      }
      // if (xPos < matrixSize - 1) {
      //   xPos++;
      // }
      // else {
      //   xPos = 0;
      // }
    } else if (inScore) {
      //we are in new score menu
      //change to prev letter
      if (name[currentLetter] < 90) {  //Z code in ASCII
        name[currentLetter]++;
        nameChange = true;
      } else {
        name[currentLetter] = 65;
        nameChange = true;
      }
    }
  }
  if (yValue > maxThreshold && joyMoved == false) {  // in dreapta
    joyMoved = true;
    if (inSettings) {
      moveToRight(currentSetting);
    } else if (inGame) {
      //we are in game mode
      if (snakeDirection != -2 || snakeLen == 2) {  // no 180 degree turn
        snakeDirection = 2;
      }

      //  if (yPos < matrixSize - 1) {
      //     yPos++;
      //   }
      //   else {
      //     yPos = 0;
      //   }
    } else if (inScore) {
      //we are in new score menu
      //change to next chr
      if (currentLetter < 2) {
        currentLetter++;
        nameChange = true;
      }
    }
  }
  if (yValue < minThreshold && joyMoved == false) {  //in stanga
    joyMoved = true;

    if (inSettings) {
      //move the level bar to left
      moveToLeft(currentSetting);
    } else if (inGame) {
      //we are in game mode
      if (snakeDirection != 2 || snakeLen == 2) {  // no 180 degree turn
        snakeDirection = -2;
      }

      //  if (yPos > 0) {
      //     yPos--;
      //   }
      //   else {
      //     yPos = matrixSize - 1;
      //   }

    } else if (inScore) {
      //we are in new score menu
      //change to prev chr
      if (currentLetter > 0) {
        currentLetter--;
        nameChange = true;
      }
    }
  }

  lastJoyReading = joyReading;
}