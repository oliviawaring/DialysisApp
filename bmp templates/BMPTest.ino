/*****************************************************************/
/* dialysisBuddy.ino                                                      
/* Author: MIT Dialysis Team, Fall 2017                                           
/* Test File  
/* ***************************************************************/

#define RESETLINE     30
#define DisplaySerial Serial1

#include <SPI.h>
#include <SD.h>       // this is needed for display
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ILI9340.h>
#
#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10
#define SD_CS 4

Adafruit_ILI9340 screen = Adafruit_ILI9340(TFT_CS, TFT_DC, TFT_RST);
//Keypad kpd;


// Prepare the 4duino for program deployment
void setup()
{
  Serial.begin(9600);

  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);
  
  screen.begin();

} // end Setup **do not alter, remove or duplicate this line**

// The main program loop
void loop()
{  
  bmpDraw("main.bmp", 0, 0); 
}
