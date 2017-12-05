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
#include "Keypad.h"
#include "Math.h"
#include "page.h"
#include "section.h"
#include "errors.h"
#include "session.h"
#include "calculations.h"
#include "keyboard.h"
#include "pageOperations.h"
#include "buttons.h"
#include "bitmaps.h"

#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10
#define SD_CS 4

Adafruit_ILI9340 screen = Adafruit_ILI9340(TFT_CS, TFT_DC, TFT_RST);
//TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
//Keypad kpd;

word x, y ; // Touchscreen coordinates (keeping this in case we need to resurrect the touchscreen later)
int sectionNum = 0; // Global variable governing the section number; start at section "0".
int pageNum = 0; // Global variable governing the page number of a given section; start at page "0".
boolean inHomePage = true; // Tells us whether or not we're in the home page
Session currentSession = {0, 0, 0, 0, {0, 0}, {0, 0}, {0, 0}, {0, 0}, 0, 0, 0, 0}; // Initialize the patient's current session values.

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

  bmpDraw("main.bmp", 0, 0);
  
 // pinMode(RESETLINE, OUTPUT);       // Display reset pin
 // digitalWrite(RESETLINE, 1);       // Reset Display, using shield
 // delay(100);                       // Wait for it to be recognised
 // digitalWrite(RESETLINE, 0);       // Release Display Reset, using shield
 // delay(4000) ;                     // Give display time to startup

 // screen.begin();
 // yield();

  // Start display as Serial lines should have 'stabilised'
 // DisplaySerial.begin(200000) ;     // Hardware serial to Display, same as SPE on display is set to
 // Display.TimeLimit4D = 5000 ;      // 5 second timeout on all commands
  
  //Display.gfx_ScreenMode(PORTRAIT); // change manually if orientation changes
  // pinMode(13, OUTPUT);
  //Display.touch_Set(TOUCH_ENABLE); // enable the touch screen
  // makePages(); We might use this function later... 

  // Initialize SD card
//  while (!Display.media_Init())
  {
    //Display.gfx_Cls();
     delay(300);
     //Display.putstr("Please insert SD card");
     delay(300);
  }
  goHome();
} // end Setup **do not alter, remove or duplicate this line**

// The main program loop
void loop()
{  
   // Launch opening menu behavior
   if (inHomePage)
   {
//      bmpDraw("main.bmp", 0, 0);
      Serial.print("home!\n");
      Serial.print(sectionNum);
      Serial.print(pageNum);
      int menuChoice = kpd.getKey() - '0';
      Serial.print(menuChoice);
      if (menuChoice > 0) 
      {
         goToSection(menuChoice);
         inHomePage = !inHomePage; 
      }
   }
   
  readButtons(); // Read button input
  delay(200) ; 
}




