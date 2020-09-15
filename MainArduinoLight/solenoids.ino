#include <Wire.h>

void SendSolenoidCommand( byte command){
  Wire.beginTransmission(2);
  Wire.write(command);
  Wire.endTransmission();
}
//SOLENOID ARDUINO COMMAND REQUESTS
//10- RampABall, 20- TestSolenoid, 30- Unable Flippers, 40- Enable Flippers
void RampABall(){
  nbBallFired++;
  //send a Launch command to the Solenoid arduino
  SendSolenoidCommand(10);
}

void ShootABall(){
  nbBallFired++;
  //send a Shoot command to the Solenoid arduino
  SendSolenoidCommand(90);
}

void ShootABallOnly(){
  //send a Shoot command to the Solenoid arduino
  SendSolenoidCommand(100);
}

void ResetSolenoids(){
  //send a Shoot command to the Solenoid arduino
  SendSolenoidCommand(200);
}

void RingSmallChime(){
  SendSolenoidCommand(110);
}

void RingMediumChime(){
  SendSolenoidCommand(120);
}

void RingLargeChime(){
  SendSolenoidCommand(130);
}


void EnableFlippers(){
  //send a Launch command to the Solenoid arduino
  SendSolenoidCommand(40);
}
void DisableFlippers(){
  //send a Launch command to the Solenoid arduino
  SendSolenoidCommand(30);
}
void DisableKickers(){
  //send a Launch command to the Solenoid arduino
  SendSolenoidCommand(80);
}
void FireKickout1(){
  //send a Launch command to the Solenoid arduino
  SendSolenoidCommand(50);
  ballCatchedInHole1 = false;
  timeInHole1 = 0;
}
void FireKickout2(){
  //send a Launch command to the Solenoid arduino
  SendSolenoidCommand(60);
  ballCatchedInHole2 = false;
  timeInHole2 = 0;
}
void TestSolenoids(){
  //Begin and send test signal
  Wire.beginTransmission(2);
  Wire.write(20);
  Wire.endTransmission();
  lcd.setCursor(0, 1);
  lcd.print("Sending test....");
  delay(24000);
  lcd.setCursor(0, 1);
  lcd.print("Done!-");

}
void EmptyAllBalls(){
  RampABall();
  delay(3000);
}


void SendSolenoidData(byte data){
  //Begin and send test signal
  Wire.beginTransmission(2);
  Wire.write(data);
  Wire.endTransmission();
}
