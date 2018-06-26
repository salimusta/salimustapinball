short menu = 1;
int tempVolume = 0;
void ManageMaintenanceMode(){
  //Reading menu buttons
  leftButton_State = digitalRead(leftBoutonPin);
  rightButton_State = digitalRead(rightBoutonPin);
  OkButton_State = digitalRead(OkBoutonPin);
  BackButton_State = digitalRead(BackBoutonPin);
  
  if(rightButton_State != rightButton_State_Old && rightButton_State == HIGH){
    //Serial.print("Button RIGHT ON\n");
    //in the main menu
    if(menu/10 == 0){
      menu++;
      if(menu > 8){
        menu = 1;
      }
    //In the 1 sub menu
    }
    else if(menu/10 == 2){
      menu++;
      if(menu >= 28){
        menu = 21;
      }
    }
    else if(menu/10 == 5){
      menu++;
      if(menu >= 59){
        menu = 51;
      }
    }else if(menu == 61){
      tempVolume += 5;
      if(tempVolume > 100) tempVolume = 100;
      SetVolume(tempVolume);
      PlaySound(DESIREHEY, true);
    }else if(menu == 71){
      freePlay = !freePlay;
    }
    Serial.print("MENU = ");
    Serial.print(menu);
    Serial.print("\n");
  }
  if(leftButton_State != leftButton_State_Old && leftButton_State == HIGH){
    //Serial.print("Button LEFT ON\n");
    //In the main menu
    if(menu/10 == 0){
      menu--;
      if(menu < 1){
        menu = 8;
      }
    }
    else if(menu/10 == 2){
      menu--;
      if(menu <= 20){
        menu = 27;
      }
    }
    else if(menu/10 == 5){
      menu--;
      if(menu <= 50){
        menu = 58;
      }
    }else if(menu == 61){
      tempVolume -= 5;
      if(tempVolume < 0) tempVolume = 0;
      SetVolume(tempVolume);
      PlaySound(DESIREHEY, true);
    }else if(menu == 71){
      freePlay = !freePlay;
    }
  }
  if(OkButton_State != OkButton_State_Old && OkButton_State == HIGH){
    //Serial.print("Button OK ON\n");
    if( menu == 1){
      menu = 11;
    }else if( menu == 2){
      menu = 21;
    }else if( menu == 3){
      EmptyAllBalls();
    }else if( menu == 4){
      //Display scores
      SendHighScores();
      delay(200);
      DisplayScreen(SCREEN_HIGHSCORES, PRIORITY_LOW);
      delay(200);
    }else if( menu == 5){
      menu = 51;
    }else if( menu == 6){
      menu = 61;
      tempVolume = volume;
    }else if( menu == 7){
      menu = 71;
    }else if( menu == 8){
      maintenanceMode = false;
    }else if( menu == 11){
      //Reset Scores
      ResetScoreMemory();
      printLine("YES", "Erasing scores");
      delay(2000);
      printLine("YES", "DONE");
      delay(1000);
      SendHighScores();
      menu = menu/10;
      
    }else if( menu == 21){
      TestScore();
    }else if( menu == 22){
      TestSwitches();
    }else if( menu == 23){
      TestSolenoids();
    }else if( menu == 24){
      TestLedMatrix();
    }else if( menu == 25){
      TestAnimLights();
    }else if( menu == 26){
      TestAmbiLights();
    }else if( menu == 27){
      TestSounds();
    }else if( menu == 51) {
      //Action when first  
      //Display Number of Bumpers
      char buf[8];
      sprintf(buf, "%ld", ReadPinballData(0));
      printLine("Ball Fired", buf);
      delay(2000);
    }else if( menu == 52) {
      char buf[8];
      sprintf(buf, "%ld", ReadPinballData(1));
      printLine("Bumper Fired", buf);
      delay(2000);
    }else if( menu == 53) {
      char buf[8];
      sprintf(buf, "%ld", ReadPinballData(2));
      printLine("Target Got", buf);
      delay(2000);
    }else if( menu == 54) {
      char buf[8];
      sprintf(buf, "%ld", ReadPinballData(3));
      printLine("Game Played", buf);
      delay(2000);
    }else if( menu == 55) {
      char buf[8];
      sprintf(buf, "%ld", ReadCredit());
      printLine("Current Credit", buf);
      delay(2000);
     }else if( menu == 56) {
      char buf[8];
      sprintf(buf, "%ld", ReadTotalCredit());
      printLine("Total Bank", buf);
      delay(2000);
    }else if( menu == 57) {
      printLine("Erasing...", "");
      ResetPinballData();
      delay(2000);
      printLine("Erasing...", "Done!");
      delay(1000);
    }else if( menu == 58) {
      printLine("Erasing...", "");
      ResetCredit();
      delay(2000);
      printLine("Erasing...", "Done!");
      delay(1000);
    }else if(menu == 61){
      volume = tempVolume;
      WriteVolume(volume);
      delay(500);
      SetVolume(volume);
      delay(500);
      menu = menu/10;
    }else if(menu == 71){
      menu = menu/10;
    }
  }
  if(BackButton_State != BackButton_State_Old && BackButton_State == HIGH){
    //Serial.print("Button Back ON\n");
    if(menu == 61) {
      SetVolume(volume);
    }
    menu = menu/10;
  }
  
  switch(menu){
    case 1:
      printLine("Main Menu", "1.Reset Scores");
      break;
      case 11:
        printLine("Are you sure?", "Reset scores?");
        break;
    case 2:
      printLine("Main Menu", "2.Test Mode");
      break;
      case 21:
        printLine("Test Mode", "1.7-DIGITS");
        break;
      case 22:
        printLine("", "2.Switches");
        break;
      case 23:
        printLine("", "3.Solenoids");
        break;
      case 24:
        printLine("", "4.Led Matrix");
        break;
      case 25:
        printLine("", "5.Anim Lights");
        break;
      case 26:
        printLine("", "6.Ambi Lights");
        break;
      case 27:
        printLine("", "7.Sounds");
        break;
     case 3:
      printLine("Main Menu", "3.Empty balls");
      break;
     case 4:
      printLine("Main Menu", "4.High Scores");
      break;  
     case 5:
      printLine("Main Menu", "5.Rom Data");
      break;
      case 51:
        printLine("Data", "1.Ball Fired");
        break;
      case 52:
        printLine("Data", "2.Bumper Fired");
        break;
      case 53:
        printLine("Data", "3.Targets Got");
        break;
      case 54:
        printLine("Data", "4.Total Game");
        break;
      case 55:
        printLine("Data", "5.Actual Credit");
        break;
      case 56:
        printLine("Data", "6.Total Credit");
        break;
      case 57:
        printLine("Data", "7.Reset Data");
        break;
      case 58:
        printLine("Data", "8.Reset Credit");
        break;
   case 6:
      printLine("Main Menu", "6.Volume");
      break;
      case 61:
        char buf[8];
        sprintf(buf, "%i", tempVolume);
        printLine("Volume", buf);
        break;
   case 7:
      printLine("Main Menu", "7.Free Play");
      break;
      case 71:
        if (freePlay) printLine("FreePlay", "ON");
        else printLine("FreePlay", "OFF");
        break;
   case 8:
    printLine("Main Menu", "8.Exit");
    break;
  }
  
  leftButton_State_Old = leftButton_State;
  rightButton_State_Old = rightButton_State;
  OkButton_State_Old = OkButton_State;
  BackButton_State_Old = BackButton_State;
}
