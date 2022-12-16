
//pins
const int contrastPin = 11;
const int brightnessPin = 3;



int brightnessLevels[] = {0,50,120,170,210,255};
//              0  1  2   3   4   5
int contrastLevels[] = {170,150,135,120,90,40};

int intensityLevels[] = {1,3,6,9,12,15};

String const difficultyLevels[] = {"Easy", "Medium", "Hard"};

void enterSettingsOptions(int currentSetting){
  //enter in current selected option

  if (currentSetting == 0) // DIFFICULTY
      {

        Serial.print(difficultyLevel);    
        lcdDifficultyAnimation(difficultyLevel); // ANIMATION ON THE LCD
        
        //update in EEPROM
        EEPROM.update(difficultyLevelAddress, difficultyLevel);
        difficultyLevel = EEPROM.read(difficultyLevelAddress);

      }
  else if (currentSetting == 1)// contrast
      {         

        lcdSettingsAnimation(contrastLevel); // ANIMATION ON THE LCD
        analogWrite(contrastPin, contrastLevels[contrastLevel]); // make change on lcd
        
        //update in EEPROM

        EEPROM.update(contrastLevelAddress, contrastLevel);
        contrastLevel = EEPROM.read(contrastLevelAddress);

      } 
  else if (currentSetting == 2)// lsc brightness
      { //move left and write to change
        

        lcdSettingsAnimation(brightnessLevel); // ANIMATION ON THE LCD
        analogWrite(brightnessPin, brightnessLevels[brightnessLevel]); // make change on lcd

        //update in EEPROM

        EEPROM.update(brightnessLevelAddress, brightnessLevel);
        brightnessLevel = EEPROM.read(brightnessLevelAddress);
        
      } 
  else if (currentSetting == 3) // matrix brightnesss
      {
        Serial.print(matrixIntensityLevel);    
        lcdSettingsAnimation(matrixIntensityLevel); // ANIMATION ON THE LCD
        lc.setIntensity(0,intensityLevels[matrixIntensityLevel]);

        //update in EEPROM

        EEPROM.update(matrixIntensityLevelAddress, matrixIntensityLevel);
        brightnessLevel = EEPROM.read(matrixIntensityLevelAddress);
       
      }
  else if (currentSetting == 4) // sound
      {
           lcdSoundAnimation();
           //save to EEPROM
           EEPROM.update(soundModeAddress, soundMode);
           soundMode = EEPROM.read(soundModeAddress);
      }
  else if (currentSetting == 5) // exit to main menu
      {
         mainMenu();
      }
}

void moveToRight(int currentSetting){
   //move the level bar to left
     //change the level I need
if (currentSetting == 0) // DIFFICULTY
      {
        if (difficultyLevel < 2)
        {difficultyLevel++; }
           
      }
  else if (currentSetting == 1)// contrast
      { 
        if (contrastLevel < 5)
        {contrastLevel++; }
        

      } 
  else if (currentSetting == 2)// lsc brightness
      { 
        if (brightnessLevel < 5)
        {brightnessLevel ++; }
          
      } 
  else if (currentSetting == 3) // matrix brightnesss
      {
        { 
        if (matrixIntensityLevel < 5)
        {matrixIntensityLevel ++; }
          
      } 
       
      }
  else if (currentSetting == 4) // sound
      {
        soundMode = true;       

      }
      enterSettingsOptions(currentSetting);

}


void moveToLeft(int currentSetting){
   //move the level bar to left
   if (currentSetting < 5) {
     //change the level I need
if (currentSetting == 0) // DIFFICULTY
      {
        if (  difficultyLevel> 0)
        {  difficultyLevel--; }  
         
      }
  else if (currentSetting == 1)// contrast
      { 
        if (contrastLevel > 0)
        {contrastLevel--; }  
        

      } 
  else if (currentSetting == 2)// lsc brightness
      { 
        if (brightnessLevel > 0)
        {brightnessLevel --; }   
      } 
  else if (currentSetting == 3) // matrix brightnesss
      {
        if (matrixIntensityLevel > 0)
        {matrixIntensityLevel --; }
     
      }
  else if (currentSetting == 4) // sound
      {
          soundMode = false;   
      }

      enterSettingsOptions(currentSetting);
    }

}

