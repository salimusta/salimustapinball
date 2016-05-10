#include <SoftwareSerial.h>// import the serial library

SoftwareSerial Genotronex(10, 11); // RX, TX
int ledpin=13; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer

void setup() {
  // put your setup code here, to run once:
  Genotronex.begin(9600);
  Genotronex.println("Bienvenue Bro");
  pinMode(ledpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   if (Genotronex.available()){
      BluetoothData=Genotronex.read();
       if(BluetoothData=='1'){   // if number 1 pressed ....
           digitalWrite(ledpin,1);
           Genotronex.println("LED  WESH On D13 ON ! ");
       }
        if (BluetoothData=='0'){// if number 0 pressed ....
          digitalWrite(ledpin,0);
           Genotronex.println("LED  WESH On D13 Off ! ");
        }
        
        if (BluetoothData=='2'){// if number 0 pressed ....
          
           Genotronex.println("BLINKING");
           
           digitalWrite(ledpin,0); delay(500);
           digitalWrite(ledpin,1); delay(500);
           digitalWrite(ledpin,0); delay(500);
           digitalWrite(ledpin,1); delay(500);
           digitalWrite(ledpin,0); delay(500);
           digitalWrite(ledpin,1); delay(500);
        }
        
        
    }
    delay(100);// prepare for next data ...
}
