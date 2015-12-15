/*
Ce programme pilote 7 afficheurs 7 segments a l aide d un CD4543
*/
#include <Wire.h>

long nb = 0;
int receivedData = 0;
long nb_dest = nb;
const int freq = 4000;
bool modeIncrementation= false;
int nbBlink = 0;
unsigned long blinkTps = 0;
bool blinkStatus = false;
unsigned long time = millis();

void setup() {
  Serial.begin(9600);
  
  // Data outputs
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  
  //Digit selection outputs
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  
  Wire.begin(1);
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int howMany) {
  long newNb = 0;
  //Byte 3 reserved for special command
  if(howMany == 4){
    byte byte3 = Wire.read();
    byte byte2 = Wire.read();
    byte byte1 = Wire.read();
    byte byte0 = Wire.read();
    
    //Activate blink mode for 10 steps
    if(byte3 == 1){
      nbBlink = 10;
      blinkTps = millis();
      
    //Disable incrementation
    }else if(byte3 == 2){
      modeIncrementation = false;
      
    //Enable incrementation
    }else if(byte3 == 4){
      modeIncrementation = true;
      
    //Parsing number value
    }else{
      newNb = byte3;
      newNb = newNb<<8;
      newNb = newNb | byte2;
      newNb = newNb << 8;
      newNb = newNb | byte1;
      newNb = newNb << 8;
      newNb = newNb | byte0;
      nb_dest = newNb;
    }
  }
}


void loop() {
  time = millis();
  
  //Managing the number incrementation or not
  if(nb < nb_dest) nb += 10;
  else nb= nb_dest;
  if(!modeIncrementation) nb = nb_dest;
  
  //Limitation
  if(nb > 99999) nb = 99999;
  
  //Blink Mode management
  if(nbBlink > 0){
    if(time - blinkTps > 150){
      blinkStatus = !blinkStatus;
      blinkTps = millis();
      nbBlink--;
    }
  }else{
    nbBlink = 0;
    blinkTps = 0;
    blinkStatus = false;
  }
  
  //Parsing number
   int Dmiller = nb/10000;
   int millier = (nb%10000)/1000;
   int centaine = ((nb%10000)%1000)/100;
   int dizaine = (((nb%10000)%1000)%100)/10;
   int unite = nb%10;
   
  //UNITES--------
  if(blinkStatus == false) digitalWrite(7, HIGH);
  else digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  digitalWrite(12, (unite&8)>>3);
  digitalWrite(11, (unite&4)>>2);
  digitalWrite(10, (unite&2)>>1);
  digitalWrite(9, (unite&1));
  
  delayMicroseconds(freq);
  
  //DIZAINE------------
  if(nb > 9){
    digitalWrite(7, LOW);
    if(blinkStatus == false) digitalWrite(6, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(12, (dizaine&8)>>3);
    digitalWrite(11, (dizaine&4)>>2);
    digitalWrite(10, (dizaine&2)>>1);
    digitalWrite(9, (dizaine&1));
    
    delayMicroseconds(freq);
  }
  //CENTAINE----------
  if(nb > 99){
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    if(blinkStatus == false) digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(12, (centaine&8)>>3);
    digitalWrite(11, (centaine&4)>>2);
    digitalWrite(10, (centaine&2)>>1);
    digitalWrite(9, (centaine&1));
    
    delayMicroseconds(freq);
  }
  //MILLIERS
  if(nb > 999){
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
    if(blinkStatus == false) digitalWrite(4, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(12, (millier&8)>>3);
    digitalWrite(11, (millier&4)>>2);
    digitalWrite(10, (millier&2)>>1);
    digitalWrite(9, (millier&1));
    
    delayMicroseconds(freq);
  }
  //DIZAINE DE MILLIERS
  if(nb > 9999){
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    if(blinkStatus == false) digitalWrite(3, HIGH);
    digitalWrite(12, (Dmiller&8)>>3);
    digitalWrite(11, (Dmiller&4)>>2);
    digitalWrite(10, (Dmiller&2)>>1);
    digitalWrite(9, (Dmiller&1));
    
    delayMicroseconds(freq);
    
  }
}
