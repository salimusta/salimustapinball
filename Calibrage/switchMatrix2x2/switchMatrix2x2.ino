const int input0 = 2;
const int input1 = 3;
const int input2 = 4;

const int drive0 = 11;
const int drive1 = 12;


void setup() {
  Serial.begin(9600); 
  
  pinMode(drive0, OUTPUT);
  pinMode(drive1, OUTPUT);
 
  pinMode(input0, INPUT);
  pinMode(input1, INPUT);   
  pinMode(input2, INPUT);  
}

int buttonA_State = 0;
int buttonB_State = 0;
int buttonC_State = 0;
int buttonD_State = 0;
int buttonE_State = 0;
int buttonF_State = 0;

int buttonA_Old = 0;
int buttonB_Old = 0;
int buttonC_Old = 0;
int buttonD_Old = 0;
int buttonE_Old = 0;
int buttonF_Old = 0;

void loop(){
  //Serial.print("Activate Drive 0...\n");
  digitalWrite(drive0, HIGH);
  digitalWrite(drive1, LOW);
  
  buttonA_State = digitalRead(input0);
  buttonB_State = digitalRead(input1);
  buttonC_State = digitalRead(input2);
  
  delay(10);
  
  //Serial.print("Activate Drive 1...\n");
  digitalWrite(drive0, LOW);
  digitalWrite(drive1, HIGH);
  
  buttonD_State = digitalRead(input0);
  buttonE_State = digitalRead(input1);
  buttonF_State = digitalRead(input2);
  
  delay(10);
  
   //Serial.print("Displaying results...\n");
  
  if(buttonA_State != buttonA_Old){
    if (buttonA_State == HIGH) Serial.print("Button A ON\n");
    else Serial.print("Button A OFF\n"); 
  }
  if(buttonB_State != buttonB_Old){
    if (buttonB_State == HIGH) Serial.print("Button B ON\n");
    else Serial.print("Button B OFF\n"); 
  }
  if(buttonC_State != buttonC_Old){
    if (buttonC_State == HIGH) Serial.print("Button C ON\n");
    else Serial.print("Button C OFF\n"); 
  }
  if(buttonD_State != buttonD_Old){
    if (buttonD_State == HIGH) Serial.print("Button D ON\n");
    else Serial.print("Button D OFF\n"); 
  }
  if(buttonE_State != buttonE_Old){
    if (buttonE_State == HIGH) Serial.print("Button E ON\n");
    else Serial.print("Button E OFF\n"); 
  }
  if(buttonF_State != buttonF_Old){
    if (buttonF_State == HIGH) Serial.print("Button F ON\n");
    else Serial.print("Button F OFF\n"); 
  }
  
  
  
  //delay(2000);
  
  buttonA_Old = buttonA_State;
  buttonB_Old = buttonB_State;
  buttonC_Old = buttonC_State;
  buttonD_Old = buttonD_State;
  buttonE_Old = buttonE_State;
  buttonF_Old = buttonF_State;
  
}
