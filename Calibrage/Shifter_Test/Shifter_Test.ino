//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 23 Mar 2010                                 
//  Version : 2.0                                             
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                           
//****************************************************************


//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

int rowA_Pin = 7;
int rowB_Pin = 6;
int rowC_Pin = 5;
int rowD_Pin = 4;
int rowE_Pin = 3;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  pinMode(rowA_Pin, OUTPUT);
  pinMode(rowB_Pin, OUTPUT);
  pinMode(rowC_Pin, OUTPUT);
  pinMode(rowD_Pin, OUTPUT);
  pinMode(rowE_Pin, OUTPUT);
  
  //Serial.begin(9600); 
  
}

int numberToDisplay = 127;
int freq = 2;

byte matrix2D[7][5]={
 {0,0,0,0,0},
 {0,0,0,0,0},
 {0,0,0,0,0},
 {0,0,0,0,0},
 {0,0,0,0,0},
 {0,0,0,0,0},
 {0,0,0,0,0}
};

const byte letter_A[7][5]={
 {1,1,1,1,1},
 {1,1,1,1,1},
 {1,1,1,1,1},
 {1,1,1,1,1},
 {1,1,1,1,1},
 {1,1,1,1,1},
 {1,1,1,1,1}
};
byte letter_B[7][5]={
 {1,1,1,1,0},
 {1,0,0,0,1},
 {1,0,0,0,1},
 {1,1,1,1,0},
 {1,0,0,0,1},
 {1,0,0,0,1},
 {1,1,1,1,0}
};
byte letter_C[7][5]={
 {0,0,1,1,0},
 {0,1,0,0,1},
 {1,0,0,0,1},
 {1,0,0,0,0},
 {1,0,0,0,1},
 {0,1,0,0,1},
 {0,0,1,1,0}
};

const byte coeur[7][5]={
 {0,0,0,0,0},
 {0,1,0,1,0},
 {1,0,1,0,1},
 {1,0,0,0,1},
 {0,1,0,1,0},
 {0,0,1,0,0},
 {0,0,0,0,0}
};

const byte coeur2[7][5]={
 {0,0,0,0,0},
 {0,0,0,0,0},
 {0,1,1,1,0},
 {0,1,1,1,0},
 {0,0,1,0,0},
 {0,0,0,0,0},
 {0,0,0,0,0}
};

int time = 0;

void loop() {
  /*time++;
  
  if(time > 150){
    time = 0;
  }else if(time > 100){
    //displayMotif(coeur);
    displayLetter('C');
  }else if(time > 50){
    //displayMotif(coeur);
    displayLetter('B');
  }else{
    //displayMotif(coeur2);
    displayLetter('A');
  }*/
   //displayLetter('A');
   
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xFF);  
  digitalWrite(latchPin, HIGH);
  delay(1000);

}

void displayLetter(char letter){
  switch(letter){
   case 'A':  displayMotif(letter_A); break;
   case 'B':  displayMotif(letter_B); break;
   case 'C':  displayMotif(letter_C); break;
  }
  
}
void displayMotif(const byte matrix[7][5]){
  setMotif(matrix);

  rowA();
  displayLine(0);
  BlankLine();
  
  rowB();
  displayLine(1);
  BlankLine();
  
  rowC();
  displayLine(2);
  BlankLine();
  
  rowD();
  displayLine(3);
  BlankLine();
  
  rowE();
  displayLine(4);
  BlankLine();
}
void setMotif(const byte matrix[7][5]){
 for(short row = 0; row < 7 ; row ++){
   for(short column = 0; column < 5 ; column ++){
     matrix2D[row][column] = matrix[row][column];
   }
 } 
}
void BlankLine(){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);  
  digitalWrite(latchPin, HIGH);
  delay(freq);
}

void displayLine(short index){
  int currentLine = 0;
  for(short i = 0; i < 7; i++){
    currentLine = currentLine | (matrix2D[i][index] << i);
  }
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, currentLine);  
  digitalWrite(latchPin, HIGH);
  delay(freq);
}
void rowA(){
  digitalWrite(rowA_Pin, LOW);
  digitalWrite(rowB_Pin, HIGH);
  digitalWrite(rowC_Pin, HIGH);
  digitalWrite(rowD_Pin, HIGH);
  digitalWrite(rowE_Pin, HIGH); 
}
void rowB(){
  digitalWrite(rowA_Pin, HIGH);
  digitalWrite(rowB_Pin, LOW);
  digitalWrite(rowC_Pin, HIGH);
  digitalWrite(rowD_Pin, HIGH);
  digitalWrite(rowE_Pin, HIGH); 
}
void rowC(){
  digitalWrite(rowA_Pin, HIGH);
  digitalWrite(rowB_Pin, HIGH);
  digitalWrite(rowC_Pin, LOW);
  digitalWrite(rowD_Pin, HIGH);
  digitalWrite(rowE_Pin, HIGH); 
}
void rowD(){
  digitalWrite(rowA_Pin, HIGH);
  digitalWrite(rowB_Pin, HIGH);
  digitalWrite(rowC_Pin, HIGH);
  digitalWrite(rowD_Pin, LOW);
  digitalWrite(rowE_Pin, HIGH); 
}
void rowE(){
  digitalWrite(rowA_Pin, HIGH);
  digitalWrite(rowB_Pin, HIGH);
  digitalWrite(rowC_Pin, HIGH);
  digitalWrite(rowD_Pin, HIGH);
  digitalWrite(rowE_Pin, LOW); 
}
