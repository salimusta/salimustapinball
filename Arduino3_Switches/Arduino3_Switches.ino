#include <Wire.h>

const int I2 = 2;
const int I3 = 3;
const int I4 = 4;
const int I5 = 5;
const int I6 = 6;
const int I7 = 7;

const int D8 = 8;
const int D9 = 9;
const int D10 = 10;
const int D11 = 11;
const int D12 = 12;

void setup() {
  Serial.begin(9600); 
  
  pinMode(D8, OUTPUT);
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);
  pinMode(D11, OUTPUT);
  pinMode(D12, OUTPUT);
 
  pinMode(I2, INPUT);
  pinMode(I3, INPUT);   
  pinMode(I4, INPUT);
  pinMode(I5, INPUT);  
  pinMode(I6, INPUT);
  pinMode(I7, INPUT);
  
  Wire.begin(3);
  Wire.onRequest(requestEvent);
  
}
bool BSW1 = false;
bool BSW2 = false;
bool BSW3 = false;
bool ROSW1 = false;
bool ROSW2 = false;
bool ROSW3 = false;
bool TRIEUR = false;
bool KO2 = false;
bool LOSW = false;
bool RLOSW = false;
bool LLOSW = false;
bool CT = false;
bool CTP = false;
bool RT1 = false;
bool RT1P = false;
bool RT2 = false;
bool LT1 = false;
bool LT2 = false;
bool LT2P = false;
bool KO1 = false;
bool RAMP = false;
bool RAMPA1 = false;
bool RAMPA2 = false;


int ROSW1_State = 0;
int ROSW2_State = 0;
int ROSW3_State = 0;
int BSW1_State = 0;
int BSW2_State = 0;
int BSW3_State = 0;
int KO2_State = 0;
int LOSW_State = 0;
int RLOSW_State = 0;
int LLOSW_State = 0;
int CT_State = 0;
int CTP_State = 0;
int RT1_State = 0;
int RT1P_State = 0;
int RT2_State = 0;
int LT1_State = 0;
int LT2_State = 0;
int LT2P_State = 0;
int KO1_State = 0;
int RAMP_State = 0;
int RAMPA1_State = 0;
int RAMPA2_State = 0;

int ROSW1_Old = 0;
int ROSW2_Old = 0;
int ROSW3_Old = 0;
int BSW1_Old = 0;
int BSW2_Old = 0;
int BSW3_Old = 0;
int KO2_Old = 0;
int LOSW_Old = 0;
int RLOSW_Old = 0;
int LLOSW_Old = 0;
int CT_Old = 0;
int CTP_Old = 0;
int RT1_Old = 0;
int RT1P_Old = 0;
int RT2_Old = 0;
int LT1_Old = 0;
int LT2_Old = 0;
int LT2P_Old = 0;
int KO1_Old = 0;
int RAMP_Old = 0;
int RAMPA1_Old = 0;
int RAMPA2_Old = 0;

short delayMs = 400;

void loop(){
  //DRIVE LINE 11
  digitalWrite(D8, LOW);
  digitalWrite(D9, LOW);
  digitalWrite(D10, LOW);
  digitalWrite(D11, HIGH);
  digitalWrite(D12, LOW);
  delayMicroseconds(delayMs);
  ROSW1_State = digitalRead(I2);
  ROSW2_State = digitalRead(I3);
  ROSW3_State = digitalRead(I4);
  LT2P_State = digitalRead(I5);
  LT2_State = digitalRead(I6);
  RAMPA2_State = digitalRead(I7);
  
  //DRIVE LINE 9
  digitalWrite(D8, LOW);
  digitalWrite(D9, HIGH);
  digitalWrite(D10, LOW);
  digitalWrite(D11, LOW);
  digitalWrite(D12, LOW);
  delayMicroseconds(delayMs);
  RT1_State = digitalRead(I2);
  RT1P_State = digitalRead(I3);
  RT2_State = digitalRead(I4);
  LT1_State = digitalRead(I5);
  KO1_State = digitalRead(I6);
  RAMPA1_State = digitalRead(I7);
  
  //DRIVE LINE 10
  digitalWrite(D8, LOW);
  digitalWrite(D9, LOW);
  digitalWrite(D10, HIGH);
  digitalWrite(D11, LOW);
  digitalWrite(D12, LOW);
  delayMicroseconds(delayMs);
  RAMP_State = digitalRead(I5);
  KO2_State = digitalRead(I2);
  LOSW_State = digitalRead(I3);
  RLOSW_State = digitalRead(I4);
  LLOSW_State = digitalRead(I6);
  
  //DRIVE LINE 12
  digitalWrite(D8, LOW);
  digitalWrite(D9, LOW);
  digitalWrite(D10, LOW);
  digitalWrite(D11, LOW);
  digitalWrite(D12, HIGH);
  delayMicroseconds(delayMs);
  BSW1_State = digitalRead(I2);
  BSW2_State = digitalRead(I3);
  BSW3_State = digitalRead(I4);
  CT_State = digitalRead(I6);
  CTP_State = digitalRead(I5);
  
  if(ROSW1_State != ROSW1_Old){
    if (ROSW1_State == HIGH) Serial.print("ROSW1 ON\n");
    else Serial.print("ROSW1 OFF\n"); 
    ROSW1 = (ROSW1_State == HIGH);
  }
  if(ROSW2_State != ROSW2_Old){
    if (ROSW2_State == HIGH) Serial.print("ROSW2 ON\n");
    else Serial.print("ROSW2 OFF\n");
     ROSW2 = (ROSW2_State == HIGH); 
  }
  if(ROSW3_State != ROSW3_Old){
    if (ROSW3_State == HIGH) Serial.print("ROSW3 ON\n");
    else Serial.print("ROSW3 OFF\n");
     ROSW3 = (ROSW3_State == HIGH); 
  }
  if(BSW1_State != BSW1_Old){
    if (BSW1_State == HIGH) Serial.print("BSW1 ON\n");
    else Serial.print("BSW1 OFF\n"); 
    BSW1 = (BSW1_State == HIGH);
  }
  if(BSW2_State != BSW2_Old){
    if (BSW2_State == HIGH) Serial.print("BSW2 ON\n");
    else Serial.print("BSW2 OFF\n"); 
    BSW2 = (BSW2_State == HIGH);
  }
  if(BSW3_State != BSW3_Old){
    if (BSW3_State == HIGH) Serial.print("BSW3 ON\n");
    else Serial.print("BSW3 OFF\n"); 
    BSW3 = (BSW3_State == HIGH);
  }
  if(RAMP_State != RAMP_Old){
    if (RAMP_State == HIGH) Serial.print("RAMP ON\n");
    else Serial.print("RAMP OFF\n"); 
    RAMP = (RAMP_State == HIGH);
  }
  if(KO2_State != KO2_Old){
    if (KO2_State == HIGH) Serial.print("KO2 ON\n");
    else Serial.print("KO2 OFF\n"); 
    KO2 = (KO2_State == HIGH);
  }
  if(LOSW_State != LOSW_Old){
    if (LOSW_State == HIGH) Serial.print("LOSW ON\n");
    else Serial.print("LOSW OFF\n"); 
    LOSW = (LOSW_State == HIGH);
  }
  if(RLOSW_State != RLOSW_Old){
    if (RLOSW_State == HIGH) Serial.print("RLOSW ON\n");
    else Serial.print("RLOSW OFF\n"); 
    RLOSW = (RLOSW_State == HIGH);
  }
  if(LLOSW_State != LLOSW_Old){
    if (LLOSW_State == HIGH) Serial.print("LLOSW ON\n");
    else Serial.print("LLOSW OFF\n"); 
    LLOSW = (LLOSW_State == HIGH);
  }
  if(CT_State != CT_Old){
    if (CT_State == HIGH) Serial.print("CT ON\n");
    else Serial.print("CT OFF\n"); 
    CT = (CT_State == HIGH);
  }
  if(CTP_State != CTP_Old){
    if (CTP_State == HIGH) Serial.print("CTP ON\n");
    else Serial.print("CTP OFF\n"); 
    CTP = (CTP_State == HIGH);
  }
  if(RT1_State != RT1_Old){
    if (RT1_State == HIGH) Serial.print("RT1 ON\n");
    else Serial.print("RT1 OFF\n"); 
    RT1 = (RT1_State == HIGH);
  }
  if(RT1P_State != RT1P_Old){
    if (RT1P_State == HIGH) Serial.print("RT1P ON\n");
    else Serial.print("RT1P OFF\n"); 
    RT1P = (RT1P_State == HIGH);
  }
  if(RT2_State != RT2_Old){
    if (RT2_State == HIGH) Serial.print("RT2 ON\n");
    else Serial.print("RT2 OFF\n"); 
    RT2 = (RT2_State == HIGH);
  }
  if(LT1_State != LT1_Old){
    if (LT1_State == HIGH) Serial.print("LT1 ON\n");
    else Serial.print("LT1 OFF\n"); 
    LT1 = (LT1_State == HIGH);
  }
  if(LT2_State != LT2_Old){
    if (LT2_State == HIGH) Serial.print("LT2 ON\n");
    else Serial.print("LT2 OFF\n"); 
    LT2 = (LT2_State == HIGH);
  }
  if(LT2P_State != LT2P_Old){
    if (LT2P_State == HIGH) Serial.print("LT2P ON\n");
    else Serial.print("LT2P OFF\n"); 
    LT2P = (LT2P_State == HIGH);
  }
  if(KO1_State != KO1_Old){
    if (KO1_State == HIGH) Serial.print("KO1 ON\n");
    else Serial.print("KO1 OFF\n"); 
    KO1 = (KO1_State == HIGH);
  }
  
  if(RAMPA1_State != RAMPA1_Old){
    if (RAMPA1_State == HIGH) Serial.print("RAMPA1 ON\n");
    else Serial.print("RAMPA1 OFF\n"); 
    RAMPA1 = (RAMPA1_State == HIGH);
  }
  
  if(RAMPA2_State != RAMPA2_Old){
    if (RAMPA2_State == HIGH) Serial.print("RAMPA2 ON\n");
    else Serial.print("RAMPA2 OFF\n"); 
    RAMPA2 = (RAMPA2_State == HIGH);
  }
  
  ROSW1_Old = ROSW1_State;
  ROSW2_Old = ROSW2_State;
  ROSW3_Old = ROSW3_State;
  BSW1_Old = BSW1_State;
  BSW2_Old = BSW2_State;
  BSW3_Old = BSW3_State;
  RAMP_Old = RAMP_State;
  KO2_Old = KO2_State;
  LOSW_Old = LOSW_State;
  RLOSW_Old = RLOSW_State;
  LLOSW_Old = LLOSW_State;
  CT_Old = CT_State;
  CTP_Old = CTP_State;
  RT1_Old = RT1_State;
  RT1P_Old = RT1P_State;
  RT2_Old = RT2_State;
  LT1_Old = LT1_State;
  LT2_Old = LT2_State;
  LT2P_Old = LT2P_State;
  KO1_Old = KO1_State;
  RAMPA1_Old = RAMPA1_State;
  RAMPA2_Old = RAMPA2_State;
}

void requestEvent()
{
  //write a byte like 
  //order starting from bit 0: BSW1, BSW2, BSW3, ROSW1, ROSW2, ROSW3, TRIEUR, KO2
  byte response = KO2;
  response = (response << 1) | TRIEUR;
  response = (response << 1) | ROSW3;
  response = (response << 1) | ROSW2;
  response = (response << 1) | ROSW1;
  response = (response << 1) | BSW3;
  response = (response << 1) | BSW2;
  response = (response << 1) | BSW1;
  
  //order starting from bit 0: LOSW, RLOSW, LLOSW, CT, CTP, RT1, RT1P, RT2
  byte response2 = RT2;
  response2 = (response2 << 1) | RT1P;
  response2 = (response2 << 1) | RT1;
  response2 = (response2 << 1) | CTP;
  response2 = (response2 << 1) | CT;
  response2 = (response2 << 1) | LLOSW;
  response2 = (response2 << 1) | RLOSW;
  response2 = (response2 << 1) | LOSW;
  
  //order starting from bit 0: LT1, LT2, LT2P, KO1, RAMP1, RAMP2
  byte response3 = RAMPA2;
  response3 = (response3 << 1) | RAMPA1;
  response3 = (response3 << 1) | KO1;
  response3 = (response3 << 1) | LT2P;
  response3 = (response3 << 1) | LT2;
  response3 = (response3 << 1) | LT1;
  
  byte bytesTab[] = {response, response2, response3};
  
  Wire.write(bytesTab, 3); 
}
