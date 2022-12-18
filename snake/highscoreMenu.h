
//message delay
const int messageTime = 3000;

void showPlace(int newIndex){
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
  readScore(); //update score in memory
  mainMenu();
  
}

void sortScore(){
  readScore();
   
   //find the index
    int newIndex = 0;
    while (newIndex < 5 && highscore[newIndex] > score){
      newIndex++;
    }

  newIndex++;
  int playerAddress = newIndex * adressPerPlayer;
  
  for (int index = lastPos; index > playerAddress + 4; index = index - 4){ // move to right and insert
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
    
playerAddress ++;
//insert the new player
    EEPROM.update(playerAddress, name[0]);
    EEPROM.update(playerAddress + 1, name[1]);
    EEPROM.update(playerAddress + 2, name[2]);
    EEPROM.update(playerAddress + 3, score);

  showPlace(newIndex);
  
}



void setName(){
  lcd.createChar(3, arrows[arrowBoth]);
  nameChange = false;

  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Set name & press"); 

  lcd.setCursor(6, 1); 

  char first = name[0];
  char second = name[1];
  char third = name[2];
  lcd.print(first);
  lcd.print(second);
  lcd.print(third);

  lcd.setCursor(12, 1); 
  lcd.write(3);

 
  
}