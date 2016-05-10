/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo1, myservo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos1 = 0;    // variable to store the servo position
int pos2 = 0;

float angle = 0;

int tpos1 = 0;

void setup() {
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(8);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  /*for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    myservo2.write(pos);
    delay(100);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100);                       // waits 15ms for the servo to reach the position
  }*/
  
  myservo1.write(pos1);              
  myservo2.write(pos2);
  
  delay(2000);
  while(1){
    /*
    pos1 = 18000;
    tpos1 += (pos1-tpos1)/100;
    myservo1.write(tpos1/100); */
    
    angle += 0.05;
    tpos1 = (1+ sin(angle))*90;
    myservo1.write(tpos1);
    delay(10);
  }
}
