#include <Wire.h>

//SOLENOID ARDUINO COMMAND REQUESTS
//10- RampABall, 20- TestSolenoid, 30- Unable Flippers, 40- Enable Flippers
void RampABall(){
  //send a Launch command to the Solenoid arduino
  Wire.beginTransmission(2);
  Wire.write(10);
  Wire.endTransmission();
}

void EnableFlippers(){
  //send a Launch command to the Solenoid arduino
  Wire.beginTransmission(2);
  Wire.write(40);
  Wire.endTransmission();
}
void DisableFlippers(){
  //send a Launch command to the Solenoid arduino
  Wire.beginTransmission(2);
  Wire.write(30);
  Wire.endTransmission();
}
void DisableKickers(){
  //send a Launch command to the Solenoid arduino
  Wire.beginTransmission(2);
  Wire.write(80);
  Wire.endTransmission();
}
void FireKickout1(){
  //send a Launch command to the Solenoid arduino
  Wire.beginTransmission(2);
  Wire.write(50);
  Wire.endTransmission();
}
void FireKickout2(){
  //send a Launch command to the Solenoid arduino
  Wire.beginTransmission(2);
  Wire.write(60);
  Wire.endTransmission();
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

void SendSolenoidRampInfo(){
  Wire.beginTransmission(2);
  Wire.write(70);
  Wire.endTransmission();
}
