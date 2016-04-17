short menu = 1;

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
      if(menu > 5){
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
    //Serial.print("MENU = ");
    //Serial.print(menu);
    //Serial.print("\n");
  }
  if(leftButton_State != leftButton_State_Old && leftButton_State == HIGH){
    //Serial.print("Button LEFT ON\n");
    //In the main menu
    if(menu/10 == 0){
      menu--;
      if(menu < 1){
        menu = 5;
      }
    }else if(menu/10 == 2){
      menu--;
      if(menu <= 20){
        menu = 27;
      }
    }
    /*Serial.print("MENU = ");
    Serial.print(menu);
    Serial.print("\n");*/
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
    }
  }
  if(BackButton_State != BackButton_State_Old && BackButton_State == HIGH){
    //Serial.print("Button Back ON\n");
    menu = menu/10;
  }
  
  switch(menu){
    case 1:
      printLine("Main Menu", "Reset Scores");
      break;
      case 11:
        printLine("Are you sure?", "Reset scores?");
        break;
    case 2:
      printLine("Main Menu", "Test Mode");
      break;
      case 21:
        printLine("Test Mode", "7-DIGITS");
        break;
      case 22:
        printLine("", "Switches");
        break;
      case 23:
        printLine("", "Solenoids");
        break;
      case 24:
        printLine("", "Led Matrix");
        break;
      case 25:
        printLine("", "Anim Lights");
        break;
      case 26:
        printLine("", "Ambi Lights");
        break;
      case 27:
        printLine("", "Sounds");
        break;
     case 3:
      printLine("Main Menu", "Empty all balls");
      break;
     case 4:
      printLine("Main Menu", "High Scores");
      break;  
     case 5:
      printLine("Main Menu", "Data");
      break; 
      
  }
  
  leftButton_State_Old = leftButton_State;
  rightButton_State_Old = rightButton_State;
  OkButton_State_Old = OkButton_State;
  BackButton_State_Old = BackButton_State;
}
