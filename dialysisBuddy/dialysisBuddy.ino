/*****************************************************************/
/* dialysisBuddy.ino                                                      
/* Author: MIT Dialysis Team, Fall 2017                                           
/* The main dialysis buddy program    
/* ***************************************************************/

#define RESETLINE     30
#define DisplaySerial Serial1

#include <SPI.h>
#include <SD.h>       // this is needed for display
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ILI9340.h>
#include <SoftwareSerial.h>
#include <Keypad.h>
#include "Math.h"
#include "page.h"
#include "section.h"
#include "errors.h"
#include "session.h"
#include "calculations.h"
#include "keyboard.h"
#include "bitmaps.h"
#include "pageOperations.h"
#include "buttons.h"
#include "process.h"

#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10
#define SD_CS 4
const int TxPin = 18; //TX1 on Mega

Adafruit_ILI9340 screen = Adafruit_ILI9340(TFT_CS, TFT_DC, TFT_RST);
SoftwareSerial mySerial = SoftwareSerial(255, TxPin);
//Keypad kpd;

word x, y ; // Touchscreen coordinates (keeping this in case we need to resurrect the touchscreen later)
int sectionNum = 0; // Global variable governing the section number; start at section "0".
int pageNum = 0; // Global variable governing the page number of a given section; start at page "0".
boolean inHomePage = true; // Tells us whether or not we're in the home page
Session currentSession = {0, 0, 0, 0, {0, 0}, {0, 0}, {0, 0}, {0, 0}, 0, 0, 0, 0}; // Initialize the patient's current session values.
int currentPage = 0;
int currentSection = 0;
int currentSubsection = 0;

// Prepare the 4duino for program deployment
void setup()
{
  Serial.begin(9600);
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);
  
  screen.begin();
  screen.fillScreen(ILI9340_BLUE);
  
  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("failed!");
    return;
  }
  
  Serial.println("OK!");
  pinMode(TxPin, OUTPUT);
  digitalWrite(TxPin, HIGH);
  delay(100);
  mySerial.begin(9600);
  mySerial.write(12);                 // Clear             
  mySerial.write(17);                 // Turn backlight on
  delay(5);                           // Required delay
  delay(3000);                        // Wait 3 seconds
  mySerial.print("Welcome to your");  // First line
  mySerial.write(13);                 // Carriage return
  mySerial.print("Dialysis Buddy!");   // Second line

  bmpDraw("main.bmp", 0, 0); 

  //goHome();
  
} // end Setup **do not alter, remove or duplicate this line**

// The main program loop
void loop()
{  
   // Launch opening menu behavior
   int menuChoice = readButtons();
   delay(200) ;    
   process(menuChoice);
}




