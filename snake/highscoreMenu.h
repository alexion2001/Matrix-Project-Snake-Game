int smallLet1;
int smallLet2;
int smallLet3;

//message delay
const int messageTime = 3000;

void showPlace(int newIndex) {
  Serial.println("in scor");

  lcd.clear();
  lcd.setCursor(7, 0);

  char first = name[0];
  char second = name[1];
  char third = name[2];
  lcd.print(first);
  lcd.print(second);
  lcd.print(third);

  lcd.setCursor(0, 1);

  lcd.print("Your place is: ");
  lcd.print(newIndex);

  delay(messageTime);
  readScore();  //update score in memory
  mainMenu();
}

void sortScore() {
  readScore();

  //find the index
  int newIndex = 0;
  while (newIndex < 5 && highscore[newIndex] > score) {
    newIndex++;
  }

  newIndex++;
  int playerAddress = newIndex * adressPerPlayer;

  for (int index = lastPos; index > playerAddress + 4; index = index - 4) {  // move to right and insert
    //read the player before
    int playerBefore = index - 4;
    int letter1 = EEPROM.read(playerBefore - 3);
    int letter2 = EEPROM.read(playerBefore - 2);
    int letter3 = EEPROM.read(playerBefore - 1);
    int playerScore = EEPROM.read(playerBefore);
    //move the player to the right
    EEPROM.update(index, playerScore);
    EEPROM.update(index - 3, letter1);
    EEPROM.update(index - 2, letter2);
    EEPROM.update(index - 1, letter3);
  }

  playerAddress++;
  //insert the new player
  EEPROM.update(playerAddress, name[0]);
  EEPROM.update(playerAddress + 1, name[1]);
  EEPROM.update(playerAddress + 2, name[2]);
  EEPROM.update(playerAddress + 3, score);

  showPlace(newIndex);
}



void setName() {
  lcd.createChar(3, arrows[arrowBoth]);
  lcd.createChar(4, arrows[arrowLeft]);
  lcd.createChar(5, arrows[arrowRight]);

  nameChange = false;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set name & press");

  lcd.setCursor(5, 1);

  if (currentLetter == 0) {  //keep the current letter big and the rest small
    smallLet1 = name[0];
    smallLet2 = name[1] + 32;
    smallLet3 = name[2] + 32;

  } else if (currentLetter == 1) {  //keep the current letter big and the rest small

    smallLet1 = name[0] + 32;
    smallLet2 = name[1];
    smallLet3 = name[2] + 32;
  } else {  //keep the current letter big and the rest small

    smallLet1 = name[0] + 32;
    smallLet2 = name[1] + 32;
    smallLet3 = name[2];
  }
  char first = smallLet1; //convert to String
  char second = smallLet2;
  char third = smallLet3;

  lcd.write(4);
  lcd.print(first);
  lcd.print(second);
  lcd.print(third);
  lcd.write(5);

  lcd.setCursor(13, 1);
  lcd.write(3);
}