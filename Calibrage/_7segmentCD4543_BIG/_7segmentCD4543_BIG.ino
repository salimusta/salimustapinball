/*
Ce programme pilote 7 afficheurs 7 segments a l aide d un CD4543
*/

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);

  
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  
  //pinMode(13, OUTPUT);
  pinMode(2, INPUT);

}

int button = 0;
int button_old = 0;

int nb = 12345;
int nb_dest = nb;

int tps = 0;

const int freq = 5500;

void loop() {
  // put your main code here, to run repeatedly:
  
  button = digitalRead(2);
  if( button == HIGH && button != button_old){
    Serial.print("BUTTON \n");
    //nb_dest = nb_dest + 50;
  }
  button_old = button;
  //nb2++;
  tps++;
  if(tps >= 1){
   tps = 0;
    if(nb < nb_dest) nb++; 
    if(nb > 99999) nb = 99999;
  }
  
   int Dmiller = nb/10000;
   
   int millier = (nb%10000)/1000;

   int centaine = ((nb%10000)%1000)/100;
 
   int dizaine = (((nb%10000)%1000)%100)/10;
   int unite = nb%10;
   
   //millier = 1;
   //centaine = 2;
   //dizaine = 3;
   //unite = 4;
   
  //UNITES--------
  digitalWrite(7, HIGH);
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
  
  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  
  digitalWrite(12, (dizaine&8)>>3);
  digitalWrite(11, (dizaine&4)>>2);
  digitalWrite(10, (dizaine&2)>>1);
  digitalWrite(9, (dizaine&1));
  
  delayMicroseconds(freq);
  
  //CENTAINE----------
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  
  digitalWrite(12, (centaine&8)>>3);
  digitalWrite(11, (centaine&4)>>2);
  digitalWrite(10, (centaine&2)>>1);
  digitalWrite(9, (centaine&1));
  
  delayMicroseconds(freq);
  
  //MILLIERS
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(3, LOW);
  
  digitalWrite(12, (millier&8)>>3);
  digitalWrite(11, (millier&4)>>2);
  digitalWrite(10, (millier&2)>>1);
  digitalWrite(9, (millier&1));
  
  delayMicroseconds(freq);
  
  //DIZAINE DE MILLIERS
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
  
  digitalWrite(12, (Dmiller&8)>>3);
  digitalWrite(11, (Dmiller&4)>>2);
  digitalWrite(10, (Dmiller&2)>>1);
  digitalWrite(9, (Dmiller&1));
  
  delayMicroseconds(freq);
  
}
