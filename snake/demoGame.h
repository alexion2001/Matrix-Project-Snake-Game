
//blink time
int blinkTime = 350;
int bombBlinkTime = 100;
long lastBlinkTime;
long lastBombBlinkTime;

//snake movements
int moveTime = 350;
int fastMoveTime = 200;
long lastMoveTime;


void generateFood() {
int onSnake;
  //generate new pos
  randomX  = random(minValue, maxValue);
  randomY  = random(minValue, maxValue);
  //avoiding generating the player's position
  onSnake = false;
  for (int pos = 0; pos < snakeLen; pos ++){
    if (randomX == snake[pos][0] && randomY == snake[pos][1]){     // same as a dot from snake
         onSnake = true;
    }
  }
  
  while (onSnake == true){
    randomX  = random(minValue, maxValue);
    randomY  = random(minValue, maxValue);

  onSnake = false;
  for (int pos = 0; pos < snakeLen; pos ++){
    if (randomX == snake[pos][0] && randomY == snake[pos][1]){     // same as a dot from snake
         onSnake = true;
    }
  }
  }
  //turn on new pos
  matrix[randomX][randomY] = 1;
  matrixChanged = true;

  if(difficultyLevel == 2){// generate bomb if difficulty level is hard
          //generate new pos
        randomBombX  = random(minValue, maxValue);
        randomBombY  = random(minValue, maxValue);

        onSnake = false;
          for (int pos = 0; pos < snakeLen; pos ++){
            if (randomBombX == snake[pos][0] && randomBombY == snake[pos][1]){     // same as a dot from snake
                onSnake = true;
            }
          }
        //avoiding generating the player's position
        while (onSnake == true || (randomX == randomBombX && randomY == randomBombY)){
          randomBombX = random(minValue, maxValue);
          randomBombY  = random(minValue, maxValue);

          onSnake = false;
          for (int pos = 0; pos < snakeLen; pos ++){
            if (randomBombX == snake[pos][0] && randomBombY == snake[pos][1]){     // same as a dot from snake
                onSnake = true;
            }
          }
        }
        //turn on new pos
        matrix[randomBombX][randomBombY] = 1;
        matrixChanged = true;
  }
}

void blinkFood(){

  if (millis() - lastBlinkTime > blinkTime) {
  // game logic
      matrix[randomX][randomY] = !matrix[randomX][randomY];
      matrixChanged = true;

      lastBlinkTime = millis();
   }  

   if (difficultyLevel == 2){ // blink bomb if difficulty level is hard
     if (millis() - lastBombBlinkTime > bombBlinkTime) {
     matrix[randomBombX][randomBombY] = !matrix[randomBombX][randomBombY];
     matrixChanged = true;

     lastBombBlinkTime = millis();
     }
   }
}

bool biteTail(){
  for (int pos = 1; pos < snakeLen; pos ++){
    if (snake[0][0] == snake[pos][0] && snake[pos][1] == snake[0][1]){ //head bites the tail
         return true;
    }
  }
  return false;
}
bool newScore(){
   int lastScore = EEPROM.read(24);  //read the last score  
   if (score > lastScore) {// better than last score
    return true;
    }
  return false;
}


void gameFinishMessage(){
  gameOverMatrix();

  if (dead){
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("BOMB"); 

  delay(messageTime / 2);
  }
  else{
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("BITE THE TAIL"); 

  delay(messageTime / 2);
  }

  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Well done!"); 
  lcd.setCursor(0, 1); 
  lcd.print("Your score: "); 
  lcd.print(score); 

  delay(messageTime);
  dead = false;

  //Verify if the new score is in highscore
  if (newScore() == true){ //if yes set name

  currentLetter = 0; //reset the name
  name[0] = 65;
  name[1] = 65;
  name[2] = 65;


  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("New highscore!"); 
  lcd.setCursor(0, 1); 

  delay(messageTime);

  inGame = false;
  inScore = true;  
  nameChange = true;
  setName();
  }
  else{ //else go to main menu
      mainMenu();    
    }

}

void snakePermutation(){ // make the permujtation in snake list of dots
  //turn off the last dot
  matrix[snake[snakeLen - 1][0]][snake[snakeLen - 1][1]] = 0;
  //turn on the new head
  matrix[snake[0][0]][snake[0][1]] = 1;

  // all dots move one pos to right
  for (int pos = snakeLen; pos > 0; pos --){
    snake[pos][0] = snake[pos - 1][0];
    snake[pos][1] = snake[pos - 1][1];
  }
  snake[0][0] = xPos;//update snake Head in array
  snake[0][1] = yPos;


  updateMatrix(); // update led matrix

}

void snakeForward(){ // move snake 1 position forward
  if (snakeDirection == 1) //up
  {
    if (xPos > 0){
      xPos --;
    }
    else{
       xPos = matrixSize - 1;
    }
    
  }
  else if (snakeDirection == -1) //down
  {
    if (xPos < matrixSize - 1){
      xPos ++;
    }
    else{
       xPos = 0;      
    }
  }
  else if (snakeDirection == 2) //right
  {
    if (yPos < matrixSize - 1){
      yPos ++;
    }
    else{
       yPos = 0;
    }

  }
  else{
   if (yPos > 0){
      yPos --;
    }
    else{
       yPos = matrixSize - 1;
    }
  }
}

void checkUpdate(){

  if (difficultyLevel == 0){

      if (millis() - lastMoveTime > moveTime) {
        // game logic

            snakeForward();
            snakePermutation();
            lastMoveTime = millis();
        }  
  }
  else{
     if (millis() - lastMoveTime > fastMoveTime) { //medxium and hard level
  // game logic

      snakeForward();
      snakePermutation(); 
      
      lastMoveTime = millis();
   }  
  }

  if(firstFood){
    randomSeed(analogRead(pinSw));
    generateFood();
    firstFood = false;
  }

  if (randomX == xPos && randomY == yPos){ // eat the food
    xPos = randomX; // eat the dot
    yPos = randomY;
    snakeLen ++;
    snakeForward();
    snakePermutation(); //update snake
    if (difficultyLevel == 0){
        score ++; //update score easy
    }
    else if(difficultyLevel == 1){
        score += 2; //update score medium
    }
    else if(difficultyLevel == 2){
        score += 3; //update score hard
    }
    
    LcdGameUpdate();
    generateFood(); 

  }

  if (difficultyLevel == 2 && (randomBombX == xPos && randomBombY == yPos)){ // eat the bomb
    dead = true;
    LcdGameUpdate(); 
  }

  if (snakeLen == 60){//end game
    gameFinishMessage();
  }
  else if(dead == true || biteTail() == true){
    gameFinishMessage();
  }

  if (matrixChanged == true) {
    // matrix display logic
    updateMatrix();
    matrixChanged = false;
  }
}



