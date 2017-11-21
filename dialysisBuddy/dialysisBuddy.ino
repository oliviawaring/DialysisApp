/*****************************************************************/
/* dialysisBuddy.ino                                                      
/* Author: MIT Dialysis Team, Fall 2017                                           
/* The main dialysis buddy program    
/* ***************************************************************/

#define RESETLINE     30
#define DisplaySerial Serial1

#include "Picaso_Serial_4DLib.h"
#include "Picaso_Const4D.h"
#include "Keypad.h"
#include "Math.h"
#include "page.h"
#include "section.h"
#include "calculations.h"
#include "pageOperations.h"
#include "buttons.h"
#include "keyboard.h"

Picaso_Serial_4DLib Display(&DisplaySerial);

word x, y ; // Touchscreen coordinates (keeping this in case we need to resurrect the touchscreen later)
int sectionNum = 0; // Global variable governing the section number; start at section "0".
int pageNum = 0; // Global variable governing the page number of a given section; start at page "0".
boolean inHomePage = true; // Tells us whether or not we're in the home page
void goNext(int & page) ;
void goBack(int & page) ;

// Prepare the 4duino for program deployment
void setup()
{
  pinMode(RESETLINE, OUTPUT);       // Display reset pin
  digitalWrite(RESETLINE, 1);       // Reset Display, using shield
  delay(100);                       // Wait for it to be recognised
  digitalWrite(RESETLINE, 0);       // Release Display Reset, using shield
  delay(4000) ;                     // Give display time to startup

  // Start display as Serial lines should have 'stabilised'
  DisplaySerial.begin(200000) ;     // Hardware serial to Display, same as SPE on display is set to
  Display.TimeLimit4D = 5000 ;      // 5 second timeout on all commands
  
  Display.gfx_ScreenMode(PORTRAIT) ; // change manually if orientation changes
  pinMode(13, OUTPUT);
  Display.touch_Set(TOUCH_ENABLE);                            // enable the touch screen
  // makePages(); We might use this function later... 

  // Initialize SD card
  while (!Display.media_Init())
  {
     Display.gfx_Cls();
     delay(300);
     Display.putstr("Please insert SD card");
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




