byte receptionFlag = true;

void SendCommandToMaster(byte command){
  commandToSend = command;
}

void requestEvent()
{
  if(requestedScreen == SCREEN_ENTER_NAME){
    if(nameEntered){
      for(byte i = 0 ; i < 10 ; i ++){
        if(name[i] == '-') name[i] = ' ';
      }
      name[10] = '\0';
      Wire.write(name, 11);
    }else if(nameEnterCanceled){
      char temp[11];
      for(byte i = 0 ; i < 11 ; i ++) temp[i] = 39;
      
      Wire.write(temp, 11); 
    }else{
      char temp[11];
      for(byte i = 0 ; i < 11 ; i ++) temp[i] = 40;
      
      Wire.write(temp, 11); 
    }
    
  }else if(requestedScreen == SCREEN_PLAYER_SELECTION){
    Wire.write(nbPlayer);
  }else{
    //byte 0 is the command
    byte bytesTab[] = {commandToSend};
    Wire.write(bytesTab, 1); 
    commandToSend = 0;
  }
}


void receiveEvent(int howMany)
{
  byte priority;
  byte screen;
  if(howMany == 3){
    screen = Wire.read();
    receivedBallNb = Wire.read();
    priority = Wire.read();
    if(priority == PRIORITY_LOW){
      lowPriorityScreen = screen;
    }
    requestedScreen = screen;
  }
  //If only 2 byte, first byte is the type of data, second one is the data
  //This is for example to transmit a countdown value, bumpers hitten state...
  if(howMany == 2){
    byte type = Wire.read();
    if(type == COUNTDOWN){
      countdown = Wire.read();
      
    }else if(type == BUMPER_STATUS){
      bumpersStatus = Wire.read();
      
    }else if(type == NB_HITS){
      nb_hits = Wire.read();
      
    }else if(type == FLIPPERS_STATE){
      byte data = Wire.read();
      
      start_state = data & 1;
      flippers_state = data >> 1;
      
    }else if(type == PSIT_STATE){
      psit_state = Wire.read();
     
    }else if(type == PLAYER_SELECTED){
      currentPlayer = Wire.read();
    
    }else if(type == MAX_PLAYER){
      maxPlayer = Wire.read();
    }
  }
  long newNb = 0;
  //This is when receive the current game's score
  if(howMany == 4){
    byte byte3 = Wire.read();
    byte byte2 = Wire.read();
    byte byte1 = Wire.read();
    byte byte0 = Wire.read();
    
    newNb = byte3;
    newNb = newNb<<8;
    newNb = newNb | byte2;
    newNb = newNb << 8;
    newNb = newNb | byte1;
    newNb = newNb << 8;
    newNb = newNb | byte0;
    
    score = newNb;
  //Score for a specific player's score
  }else if(howMany == 5){
    byte playerId = Wire.read();
    byte byte3 = Wire.read();
    byte byte2 = Wire.read();
    byte byte1 = Wire.read();
    byte byte0 = Wire.read();
    
    newNb = byte3;
    newNb = newNb<<8;
    newNb = newNb | byte2;
    newNb = newNb << 8;
    newNb = newNb | byte1;
    newNb = newNb << 8;
    newNb = newNb | byte0;
    
    playersScore[playerId] = newNb;
  }
  //High Score reception
  byte i = 0;
  if(howMany == 20){
    for(i = 0; i < 5; i++){
      newNb = 0;
      byte byte3 = Wire.read();
      byte byte2 = Wire.read();
      byte byte1 = Wire.read();
      byte byte0 = Wire.read();
      
      newNb = byte3;
      newNb = newNb<<8;
      newNb = newNb | byte2;
      newNb = newNb << 8;
      newNb = newNb | byte1;
      newNb = newNb << 8;
      newNb = newNb | byte0;
      
      if(receptionFlag) scoresTab[i] = newNb;
      else scoresTab[i+5] = newNb;
    }
    
    receptionFlag = !receptionFlag;
  }
  
  //Reception of player names (11 Byte string + 1 Byte index)
  if(howMany == 12){
    byte index = 0;
    char buf[11];
    while (Wire.available()) {
      byte data = Wire.read();
      if(index == 11){
        if(data == 1) strncpy(highscoreName1, buf, 11);
        else if(data == 2) strncpy(highscoreName2, buf, 11);
        else if(data == 3) strncpy(highscoreName3, buf, 11);
        else if(data == 4) strncpy(highscoreName4, buf, 11);
        else if(data == 5) strncpy(highscoreName5, buf, 11);
        else if(data == 6) strncpy(highscoreName6, buf, 11);
        else if(data == 7) strncpy(highscoreName7, buf, 11);
        else if(data == 8) strncpy(highscoreName8, buf, 11);
        else if(data == 9) strncpy(highscoreName9, buf, 11);
        else if(data == 10) strncpy(highscoreName10, buf, 11);
        
      }else{
        buf[index] = data;
      }
      index++;
    }
  }
}

