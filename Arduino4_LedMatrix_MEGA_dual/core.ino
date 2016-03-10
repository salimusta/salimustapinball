short ROW_xPixel;
short ROW_num;
unsigned char Col_num_1;
unsigned char Col_num_2;
unsigned char Col_num_3;
unsigned char Col_num_4;
unsigned char Col_num_5;
unsigned char Col_num_6;
unsigned char Col_num_7;
unsigned char Col_num_8;

short ROW_xPixel_2;
short ROW_num_2;
unsigned char Col_num_1_2;
unsigned char Col_num_2_2;
unsigned char Col_num_3_2;
unsigned char Col_num_4_2;
unsigned char Col_num_5_2;
unsigned char Col_num_6_2;
unsigned char Col_num_7_2;
unsigned char Col_num_8_2;

void shiftOut_Both(unsigned char dataOut1, unsigned char dataOut2){
  for(int i=0;i<=7;i++){
     PORTB &=~(1<<(6));//PB6 = 0 equate digitalWrite(clockPin,LOW); 
     if(dataOut1 & (0x01<<i))  PORTB |=1<<(5); //PB5=1 equate digitalWrite(dataPin,HIGH);
     else  PORTB &=~(1<<(5));//PB5 = 0 equate digitalWrite(clockPin,LOW); 
     PORTB |=1<<(6);//PB6=1 equate digitalWrite(clockPin,HIGH);
     
     PORTB &=~(1<<(4));//PB6 = 0 equate digitalWrite(clockPin,LOW); to PB4
     if(dataOut2 & (0x01<<i))  PORTB |=1<<(3); //PB5=1 equate digitalWrite(dataPin,HIGH); to PB3
     else  PORTB &=~(1<<(3));//PB5 = 0 equate digitalWrite(clockPin,LOW);  to PB3
     PORTB |=1<<(4);//PB6=1 equate digitalWrite(clockPin,HIGH);  to PB4
   }
}


unsigned char Combine_2BitsTo1Bit(unsigned char num,unsigned char *BMP){
  unsigned char Col_num_tem_1;
  unsigned char Col_num_tem_2;
  unsigned int Col_num_tem = 0;
  byte i=0;
  unsigned char Col_num_1bit = 0x00;
  
  Col_num_tem_1 = *(BMP+num);
  Col_num_tem_2 = *(BMP+num+1);
  
  Col_num_tem = Col_num_tem_1;
  Col_num_tem |= (Col_num_tem_2 << 8);
  
 for(i=0;i<8;i++){   
    if(Col_num_tem&(0x0003<<i*2)) Col_num_1bit |= (0x01<<i);
 }
  return ~Col_num_1bit;
}


void copyFrames(unsigned char *source, unsigned char *dest){
  for(short i = 0; i < 512; i++){
    dest[i] = source[i];
  }
}

void copyString(char *source, char *dest, byte size){
  for(short i = 0; i < size; i++){
    dest[i] = source[i];
  }
}

bool compareString(char *source, char *dest, byte size){
  for(short i = 0; i < size; i++){
    if(dest[i] != source[i]) return false;
  }
  
  return true;
}


void DisplayMatrix(unsigned char *BMP)
{
  byte dis_cnt=1;
  unsigned int i;
  
  unsigned char *BMP1 = BMP;
  unsigned char *BMP2 = BMP+256;
 
   for(i=0;i<dis_cnt*16;i++){
     digitalWrite(en_74138_2, HIGH);//Turn off display
     digitalWrite(en_74138, HIGH);//Turn off display
  
    //Col scanning for screen 1
    shiftOut_Both(Col_num_1, Col_num_1_2);
    shiftOut_Both(Col_num_2, Col_num_2_2);
    shiftOut_Both(Col_num_3, Col_num_3_2);
    shiftOut_Both(Col_num_4, Col_num_4_2);
    shiftOut_Both(Col_num_5, Col_num_5_2);
    shiftOut_Both(Col_num_6, Col_num_6_2);
    shiftOut_Both(Col_num_7, Col_num_7_2);
    shiftOut_Both(Col_num_8, Col_num_8_2);
    
    digitalWrite(LATCH_PIN_2, LOW);
    digitalWrite(LATCH_PIN_2, HIGH);
    
    digitalWrite(LATCH_PIN, LOW);
    digitalWrite(LATCH_PIN, HIGH);
  
    //Row scanning for screen 2
    PORTH = ((ROW_xPixel_2 << (0-0) ) & 0X01) | (PORTH & 0XFE);////Write PIN 3(PE5) la_74138 to PH0
    PORTH = ((ROW_xPixel_2 << (1-1) ) & 0X02) | (PORTH & 0XFD);////Write PIN 4(PG5) lb_74138 to PH1
    PORTJ = ((ROW_xPixel_2 >> (2) ) & 0X01) | (PORTJ & 0XFE);////Write PIN 5(PE3) lc_74138 to PJ0
    PORTH = ((ROW_xPixel_2 << (6-3) ) & 0X40) | (PORTH & 0XBF);////Write PIN 5(PH3) ld_74138 to PH6
    
    //Row scanning for screen 1
    PORTE = ((ROW_xPixel << (5-0) ) & 0X20) | (PORTE & 0XDF);////Write PIN 3(PE5) la_74138
    PORTG = ((ROW_xPixel << (5-1) ) & 0X20) | (PORTG & 0XDF);////Write PIN 4(PG5) lb_74138
    PORTE = ((ROW_xPixel << (3-2) ) & 0X08) | (PORTE & 0XF7);////Write PIN 5(PE3) lc_74138
    PORTH = ((ROW_xPixel << (3-3) ) & 0X08) | (PORTH & 0XF7);////Write PIN 5(PH3) ld_74138
     
    digitalWrite(en_74138_2, LOW);//Turn on display 2
    digitalWrite(en_74138, LOW);//Turn on display 1
  
    if(ROW_xPixel_2 ==15 ) ROW_xPixel_2=0; else ROW_xPixel_2++;
    if(ROW_xPixel ==15 ) ROW_xPixel=0; else ROW_xPixel++;
  
   //Single color,2 bits/pixel Screen 2
   Col_num_1_2 = Combine_2BitsTo1Bit((COL_PIXEL/8)*ROW_xPixel_2*2,BMP2);
   Col_num_2_2 = Combine_2BitsTo1Bit((COL_PIXEL/8)*ROW_xPixel_2*2+2,BMP2);
   Col_num_3_2 = Combine_2BitsTo1Bit((COL_PIXEL/8)*ROW_xPixel_2*2+4,BMP2);
   Col_num_4_2 = Combine_2BitsTo1Bit((COL_PIXEL/8)*ROW_xPixel_2*2+6,BMP2);
   Col_num_5_2 = Combine_2BitsTo1Bit((COL_PIXEL/8)*ROW_xPixel_2*2+8,BMP2);
   Col_num_6_2 = Combine_2BitsTo1Bit((COL_PIXEL/8)*ROW_xPixel_2*2+10,BMP2);
   Col_num_7_2 = Combine_2BitsTo1Bit((COL_PIXEL/8)*ROW_xPixel_2*2+12,BMP2);
   Col_num_8_2 = Combine_2BitsTo1Bit((COL_PIXEL/8)*ROW_xPixel_2*2+14,BMP2);
   
   //Single color,2 bits/pixel Screen1
   Col_num_1 = Combine_2BitsTo1Bit((COL_PIXEL/8)*ROW_xPixel*2,BMP1);
   Col_num_2 = Combine_2BitsTo1Bit((COL_PIXEL/8)*ROW_xPixel*2+2,BMP1);
   Col_num_3 = Combine_2BitsTo1Bit((COL_PIXEL/8)*ROW_xPixel*2+4,BMP1);
   Col_num_4 = Combine_2BitsTo1Bit((COL_PIXEL/8)*ROW_xPixel*2+6,BMP1);
   Col_num_5 = Combine_2BitsTo1Bit((COL_PIXEL/8)*ROW_xPixel*2+8,BMP1);
   Col_num_6 = Combine_2BitsTo1Bit((COL_PIXEL/8)*ROW_xPixel*2+10,BMP1);
   Col_num_7 = Combine_2BitsTo1Bit((COL_PIXEL/8)*ROW_xPixel*2+12,BMP1);
   Col_num_8 = Combine_2BitsTo1Bit((COL_PIXEL/8)*ROW_xPixel*2+14,BMP1);
  }
}


void EmptyMatrix(unsigned char *bmp){
  for(short i = 0; i < 512; i++){
    bmp[i] = 0;
  }
}

void drawMotif(unsigned char *frame, unsigned char motif[], short motifx, short motify, short width, short height){ 
  for(short y = 0; y < height; y++){
    for(short x = 0; x < width; x++){
      short tabIndex = ((motify+y)*16) + ((motifx+x)/4);
      byte pixel = ( motif[y] >> ((width-1)-x) ) & 0x01;
      
      if(pixel == 1  && motifx+x < 64 && motifx+x >= 0 && motify+y < 32 && motify+y >= 0){
        byte currentPixel = frame[tabIndex];        
        byte newPixel = currentPixel | (3 << (((motifx+x)%4)*2))  ;        
        frame[tabIndex] = newPixel;
      }
    }
  }  
}

void drawBigMotif(unsigned char *frame, unsigned short motif[], short motifx, short motify, short width, short height){ 
  for(short y = 0; y < height; y++){
    for(short x = 0; x < width; x++){
      short tabIndex = ((motify+y)*16) + ((motifx+x)/4);
      byte pixel = ( motif[y] >> ((width-1)-x) ) & 0x01;
      
      if(pixel == 1  && motifx+x < 64 && motifx+x >= 0 && motify+y < 32 && motify+y >= 0){
        byte currentPixel = frame[tabIndex];        
        byte newPixel = currentPixel | (3 << (((motifx+x)%4)*2))  ;        
        frame[tabIndex] = newPixel;
      }
    }
  }  
}

void drawVeryBigMotif(unsigned char *frame, unsigned long motif[], short motifx, short motify, short width, short height){ 
  for(short y = 0; y < height; y++){
    for(short x = 0; x < width; x++){
      short tabIndex = ((motify+y)*16) + ((motifx+x)/4);
      byte pixel = ( motif[y] >> ((width-1)-x) ) & 0x01;
      
      if(pixel == 1  && motifx+x < 64 && motifx+x >= 0 && motify+y < 32 && motify+y >= 0){
        byte currentPixel = frame[tabIndex];        
        byte newPixel = currentPixel | (3 << (((motifx+x)%4)*2))  ;        
        frame[tabIndex] = newPixel;
      }
    }
  }  
}

void drawRect(unsigned char *frame, short motifx, short motify, byte width, byte height){ 
  for(short y = 0; y < height; y++){
    for(short x = 0; x < width; x++){
      short tabIndex = ((motify+y)*16) + ((motifx+x)/4);
      
      if(motifx+x < 64 && motifx+x >= 0 && motify+y < 32 && motify+y >= 0){
        byte currentPixel = frame[tabIndex];        
        byte newPixel = currentPixel | (3 << (((motifx+x)%4)*2))  ;        
        frame[tabIndex] = newPixel;
      }
    }
  }  
}

void drawInvertRect(unsigned char *frame, short motifx, short motify, byte width, byte height){ 
  for(short y = 0; y < height; y++){
    for(short x = 0; x < width; x++){
      short tabIndex = ((motify+y)*16) + ((motifx+x)/4);
      
      if(motifx+x < 64 && motifx+x >= 0 && motify+y < 32 && motify+y >= 0){
        byte currentPixel = frame[tabIndex];  
        byte info =  (currentPixel >> (((motifx+x)%4)*2)  ) & 1;
        info = !info;
        byte newPixel ;
        if(info == 1) newPixel= currentPixel | (3 << (((motifx+x)%4)*2))  ; 
        if(info == 0) newPixel= currentPixel & ~(3 << (((motifx+x)%4)*2))  ;        
        frame[tabIndex] = newPixel;
      }
    }
  }  
}
