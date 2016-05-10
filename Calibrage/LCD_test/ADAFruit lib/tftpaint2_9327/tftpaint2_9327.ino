// This sketch has been Refurbished by BUHOSOFT
// Original code provided by Smoke And Wires
// http://www.smokeandwires.co.nz
// This code has been taken from the Adafruit TFT Library and modified
//  by us for use with our TFT Shields / Modules
// For original code / licensing please refer to
// https://github.com/adafruit/TFTLCD-Library

// adapted sketch by niq_ro from http://arduinotehniq.blogspot.com/
// ver. 1m5 - 13.11.2014, Craiova - Romania

#define DEBUG 1

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
// #define LCD_CS A3 // Chip Select goes to Analog 3
// #define LCD_CD A2 // Command/Data goes to Analog 2
// #define LCD_WR A1 // LCD Write goes to Analog 1
// #define LCD_RD A0 // LCD Read goes to Analog 0

// #define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

//#define DEBUG
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4


#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin
//ili9327
//#define XM A1
//#define YP A2
//#define XP 7
//#define YM 6

#define TS_MINX 118L //150,150
#define TS_MINY 166L //75, 120
#define TS_MAXX 954L //920
#define TS_MAXY 859L //950

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 600);

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
//#define ROZ     0xFD20
#define ROZ     0xFBE0
#define GRI     0xBDF7
// http://stackoverflow.com/questions/13720937/c-defined-16bit-high-color
// http://wiibrew.org/wiki/U16_colors

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

//9327 400x240
//#define BOXSIZE 50
//9488
#define BOXSIZE 60
#define PENRADIUS 2
int oldcolor, currentcolor;
int ics;
uint16_t identifier;

void setup(void) {
  Serial.begin(9600);
  Serial.println(F("Paint!"));
  
  tft.reset();
  identifier = 0x9341;

  tft.begin(identifier);

  tft.fillScreen(WHITE);

  tft.fillRect(0, 0, 320, 480, RED); 
  
  tft.setRotation(1);
  tft.setCursor(0, 0);
  tft.setTextColor(CYAN);
  tft.setTextSize(3);
  tft.println(tft.width());
  
  tft.fillCircle(200, 200, 30, CYAN);
  
  tft.fillRect(50, 50, 20, 20, YELLOW);
  
  tft.drawRect(60, 60, 50, 50, WHITE);
  
  drawButton(250, 160, false);
  
  pinMode(13, OUTPUT);
}

#define MINPRESSURE 2
#define MAXPRESSURE 1000

int minY = 999;
int maxY = 0;
int minX = 999;
int maxX = 0;

int ballX = 0;

bool buttonOk_State = false;
bool buttonOk_OldState = false;

void loop()
{
  digitalWrite(13, HIGH);
  // Recently Point was renamed TSPoint in the TouchScreen library
  // If you are using an older version of the library, use the
  // commented definition instead.
  // Point p = ts.getPoint();
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  //pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //pinMode(YM, OUTPUT);

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  buttonOk_State = false;
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    if(p.x > maxX) maxX = p.x;
    if(p.y > maxY) maxY = p.y;
    if(p.x < minX) minX = p.x;
    if(p.y < minY) minY = p.y;
    
    /*Serial.print("minX = "); Serial.print(minX); Serial.print("\n");
    Serial.print("maxX = "); Serial.print(maxX); Serial.print("\n");
    Serial.print("minY = "); Serial.print(minY); Serial.print("\n");
    Serial.print("maxY = "); Serial.print(maxY); Serial.print("\n");
    
    Serial.print("or("); Serial.print(p.x);
    Serial.print(", "); Serial.print(p.y);
    Serial.println(")\n");
    */
    unsigned long screenX = (p.x - TS_MINX ) * 48000L / ((TS_MAXX - TS_MINX) * 100L);
    unsigned long screenY = 320 - ((p.y - 166L ) * 32000L / 69300L);
    
    /*Serial.print("calc("); Serial.print(screenX);
    Serial.print(", "); Serial.print(screenY);
    Serial.println(")\n");*/
    
    tft.fillCircle(screenX, screenY, 1, CYAN);
    
    //Test for OK button
    
    if(screenX < 340 && screenX > 240 && screenY > 160 && screenY < 210){
      buttonOk_State = true;
    }
    
  }
  
  if(buttonOk_OldState != buttonOk_State){
    Serial.println("NEW "); Serial.println(buttonOk_State); Serial.println("\n");
      drawButton(250, 160, buttonOk_State);
  }
  
  tft.fillCircle(ballX, 160, 10, RED);
  ballX+=1;
  tft.fillCircle(ballX, 160, 10, WHITE);
  
  buttonOk_OldState = buttonOk_State;
  delay(100);
 
}

void drawButton(short x, short y, bool state){
  if(state) tft.fillRect(x, y, 100, 50, WHITE);
  else{
    tft.fillRect(x, y, 100, 50, RED);
    tft.drawRect(x, y, 100, 50, WHITE);
    
  }
  
  tft.setCursor(x+10, y+10);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("OK");
  
}



