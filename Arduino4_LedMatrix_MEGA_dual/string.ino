

byte getCharLength(char l, byte fontType){
  byte len = 0;
  if(fontType == FONT_NORMAL){
    if(l >= 65 && l <=90){
       if( l == 'E' || l == 'F' || l == 'L') len += 6;
       else if(l == 'I') len += 3;
       else if(l == 'J' || l == 'M' || l == 'N' || l == 'Q' || l == 'W') len += 8;
       else len += 7;
     }else if(l == '!' || l == '.' || l == ':'){
       len += 3;
     }else if(l == '-'){
       len += 4;
     }else if(l == '@'){
       len += 8;
     }else if(l == '+' || l == '_'){
       len += 7;
     }else if(l == ' '){
       len += 2;
     }else if(l >= 48 && l <=57){
       len += 8;
     }
  }else if(fontType == FONT_SMALL){
    if(l >= 65 && l <=90){
      if( l == 'I' || l == 'X' || l == 'Y') len += 3;
      else if( l == 'M' || l == 'T' || l == 'W') len += 5;
      else len += 4;
    }else if(l == ' '){
       len += 1;
    }else if(l >= 48 && l <=57){
       len += 4;
    }else if(l == '<' || l == '>' || l == '+'){
       len += 3;
    }else if(l == '.'){
       len += 1;
    }
  }
  return len;
}

byte getStringLength(char *str, byte fontType){
  byte len = 0;
  while(*str){
    len += getCharLength(*str++, fontType);
  }
  return len;
}

byte getStringLengthAt(char *str, byte index, byte fontType){
  byte len2 = 0;
  byte temp = index;
  while(*str && temp >= 0 && temp < 20){
    len2 += getCharLength(*str++, fontType);
    temp--;
  }
  return len2;
}

void centerString(unsigned char *targetBmp, char *str, short startypos){
  byte nameLength = getStringLength(str, FONT_NORMAL);
  drawString(targetBmp, str, ((64-nameLength)/2)+1, startypos, 50); 
}

void drawString(unsigned char *targetBmp, char *str, short startxpos, short startypos, byte maxLength){
  short index = 0;
  short xpos = startxpos;
  short ypos = startypos;
  if(maxLength == 0) return;
  while(str[index] != '\0' && index <= maxLength){
    if(str[index] == 'A') {drawMotif(targetBmp, letterA, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == 'B') {drawMotif(targetBmp, letterB, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == 'C') {drawMotif(targetBmp, letterC, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == 'D') {drawMotif(targetBmp, letterD, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == 'E') {drawMotif(targetBmp, letterE, xpos, ypos, 5, 9); xpos += 6;}
    else if(str[index] == 'F') {drawMotif(targetBmp, letterF, xpos, ypos, 5, 9); xpos += 6;}
    else if(str[index] == 'G') {drawMotif(targetBmp, letterG, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == 'H') {drawMotif(targetBmp, letterH, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == 'I') {drawMotif(targetBmp, letterI, xpos, ypos, 2, 9); xpos += 3;}
    else if(str[index] == 'J') {drawMotif(targetBmp, letterJ, xpos, ypos, 7, 9); xpos += 8;}
    else if(str[index] == 'K') {drawMotif(targetBmp, letterK, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == 'L') {drawMotif(targetBmp, letterL, xpos, ypos, 5, 9); xpos += 6;}
    else if(str[index] == 'M') {drawMotif(targetBmp, letterM, xpos, ypos, 7, 9); xpos += 8;}
    else if(str[index] == 'N') {drawMotif(targetBmp, letterN, xpos, ypos, 7, 9); xpos += 8;}
    else if(str[index] == 'O') {drawMotif(targetBmp, letterO, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == 'P') {drawMotif(targetBmp, letterP, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == 'Q') {drawMotif(targetBmp, letterQ, xpos, ypos, 7, 9); xpos += 8;}
    else if(str[index] == 'R') {drawMotif(targetBmp, letterR, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == 'S') {drawMotif(targetBmp, letterS, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == 'T') {drawMotif(targetBmp, letterT, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == 'U') {drawMotif(targetBmp, letterU, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == 'V') {drawMotif(targetBmp, letterV, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == 'W') {drawMotif(targetBmp, letterW, xpos, ypos, 7, 9); xpos += 8;}
    else if(str[index] == 'X') {drawMotif(targetBmp, letterX, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == 'Y') {drawMotif(targetBmp, letterY, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == 'Z') {drawMotif(targetBmp, letterZ, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == '!') {drawMotif(targetBmp, symbolExclamation, xpos, ypos, 2, 9); xpos += 3;}
    else if(str[index] == '.') {drawMotif(targetBmp, symbolPoint, xpos, ypos, 2, 9); xpos += 3;}
    else if(str[index] == '-') {drawMotif(targetBmp, symbolDash, xpos, ypos, 3, 9); xpos += 4;}
    else if(str[index] == ':') {drawMotif(targetBmp, symbolDeuxPoints, xpos, ypos, 2, 9); xpos += 3;}
    else if(str[index] == '+') {drawMotif(targetBmp, symbolPlus, xpos, ypos, 6, 9); xpos += 7;}
    else if(str[index] == '_') {drawMotif(targetBmp, symbolUnderscore, xpos, ypos, 7, 9); xpos += 8;}
    else if(str[index] == '@') {drawMotif(targetBmp, symbolRect, xpos, ypos, 7, 9); xpos += 8;}
    else if(str[index] == '1') {drawMotif(targetBmp, number1, xpos, ypos-1, 7, 11); xpos += 8;}
    else if(str[index] == '2') {drawMotif(targetBmp, number2, xpos, ypos-1, 7, 11); xpos += 8;}
    else if(str[index] == '3') {drawMotif(targetBmp, number3, xpos, ypos-1, 7, 11); xpos += 8;}
    else if(str[index] == '4') {drawMotif(targetBmp, number4, xpos, ypos-1, 7, 11); xpos += 8;}
    else if(str[index] == '5') {drawMotif(targetBmp, number5, xpos, ypos-1, 7, 11); xpos += 8;}
    else if(str[index] == '6') {drawMotif(targetBmp, number6, xpos, ypos-1, 7, 11); xpos += 8;}
    else if(str[index] == '7') {drawMotif(targetBmp, number7, xpos, ypos-1, 7, 11); xpos += 8;}
    else if(str[index] == '8') {drawMotif(targetBmp, number8, xpos, ypos-1, 7, 11); xpos += 8;}
    else if(str[index] == '9') {drawMotif(targetBmp, number9, xpos, ypos-1, 7, 11); xpos += 8;}
    else if(str[index] == '0') {drawMotif(targetBmp, number0, xpos, ypos-1, 7, 11); xpos += 8;}
    else if(str[index] == ' ') {xpos += 2;}
    index++;
  }
}

void drawSmallString(unsigned char *targetBmp, char *str, short startxpos, short startypos, byte maxLength){
  short index = 0;
  short xpos = startxpos;
  short ypos = startypos;
  if(maxLength == 0) return;
  while(str[index] != '\0' && index <= maxLength){
    if(str[index] == 'A') {drawMotif(targetBmp, smallLetterA, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'B') {drawMotif(targetBmp, smallLetterB, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'C') {drawMotif(targetBmp, smallLetterC, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'D') {drawMotif(targetBmp, smallLetterD, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'E') {drawMotif(targetBmp, smallLetterE, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'F') {drawMotif(targetBmp, smallLetterF, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'G') {drawMotif(targetBmp, smallLetterG, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'H') {drawMotif(targetBmp, smallLetterH, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'I') {drawMotif(targetBmp, smallLetterI, xpos, ypos, 3, 7); xpos += 4;}
    else if(str[index] == 'J') {drawMotif(targetBmp, smallLetterJ, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'K') {drawMotif(targetBmp, smallLetterK, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'L') {drawMotif(targetBmp, smallLetterL, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'M') {drawMotif(targetBmp, smallLetterM, xpos, ypos, 5, 7); xpos += 6;}
    else if(str[index] == 'N') {drawMotif(targetBmp, smallLetterN, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'O') {drawMotif(targetBmp, smallLetterO, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'P') {drawMotif(targetBmp, smallLetterP, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'Q') {drawMotif(targetBmp, smallLetterQ, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'R') {drawMotif(targetBmp, smallLetterR, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'S') {drawMotif(targetBmp, smallLetterS, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'T') {drawMotif(targetBmp, smallLetterT, xpos, ypos, 5, 7); xpos += 6;}
    else if(str[index] == 'U') {drawMotif(targetBmp, smallLetterU, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'V') {drawMotif(targetBmp, smallLetterV, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == 'W') {drawMotif(targetBmp, smallLetterW, xpos, ypos, 5, 7); xpos += 6;}
    else if(str[index] == 'X') {drawMotif(targetBmp, smallLetterX, xpos, ypos, 3, 7); xpos += 4;}
    else if(str[index] == 'Y') {drawMotif(targetBmp, smallLetterY, xpos, ypos, 3, 7); xpos += 4;}
    else if(str[index] == 'Z') {drawMotif(targetBmp, smallLetterZ, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == '1') {drawMotif(targetBmp, smallNumber1, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == '2') {drawMotif(targetBmp, smallNumber2, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == '3') {drawMotif(targetBmp, smallNumber3, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == '4') {drawMotif(targetBmp, smallNumber4, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == '5') {drawMotif(targetBmp, smallNumber5, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == '6') {drawMotif(targetBmp, smallNumber6, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == '7') {drawMotif(targetBmp, smallNumber7, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == '8') {drawMotif(targetBmp, smallNumber8, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == '9') {drawMotif(targetBmp, smallNumber9, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == '0') {drawMotif(targetBmp, smallNumber0, xpos, ypos, 4, 7); xpos += 5;}
    else if(str[index] == '<') {drawMotif(targetBmp, smallInf, xpos, ypos, 3, 7); xpos += 4;}
    else if(str[index] == '>') {drawMotif(targetBmp, smallSup, xpos, ypos, 3, 7); xpos += 4;}
    else if(str[index] == '.') {drawMotif(targetBmp, smallPoint, xpos, ypos, 1, 7); xpos += 2;}
    else if(str[index] == '+') {drawMotif(targetBmp, smallPlus, xpos, ypos, 3, 7); xpos += 4;}
    else if(str[index] == ' ') {xpos += 1;}
    index++;
  }
}
