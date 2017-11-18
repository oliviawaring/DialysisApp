//
// NB! This is a file generated from the .4Dino file, changes will be lost
//     the next time the .4Dino file is built
//
// Define LOG_MESSAGES to a serial port to send SPE errors messages to. Do not use the same Serial port as SPE
//#define LOG_MESSAGES Serial

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

// routine to handle Serial errors

int NUM_PAGES = 6;
word x, y ;
int pageNum = 0;
void goNext(int & page) ;
void goBack(int & page) ;
boolean inHomePage = true;

void setup()
{
  pinMode(RESETLINE, OUTPUT);       // Display reset pin
  digitalWrite(RESETLINE, 1);       // Reset Display, using shield
  delay(100);                       // wait for it to be recognised
  digitalWrite(RESETLINE, 0);       // Release Display Reset, using shield
  delay(4000) ;                     // give display time to startup

  // now start display as Serial lines should have 'stabilised'
  DisplaySerial.begin(200000) ;     // Hardware serial to Display, same as SPE on display is set to
  Display.TimeLimit4D = 5000 ;      // 5 second timeout on all commands

  Display.gfx_ScreenMode(PORTRAIT) ; // change manually if orientation change
  // put your setup code here, to run once:

  pinMode(13, OUTPUT);
  Display.touch_Set(TOUCH_ENABLE);                            // enable the touch screen
//  makePages();
  byte state ;
  /*while (!Display.media_Init())
  {
     Display.gfx_Cls();
     //Display.pause(300);n
     Display.putstr("Please insert SD card");
    //Display.pause(300);
  }*/
  goHome();
  
  /*state = Display.touch_Get(TOUCH_STATUS);               // get touchscreen status
  //-----------------------------------------------------------------------------------------
  if((state == TOUCH_PRESSED) || (state == TOUCH_MOVING))                       // if there's a press, or it's moving
  {
    x = Display.touch_Get(TOUCH_GETX);
    y = Display.touch_Get(TOUCH_GETY);
  }
  pageNum = 0;*/

} // end Setup **do not alter, remove or duplicate this line**

void loop()
{  
   //byte touchState;
   if (inHomePage)
   {
    //Serial.print("in home page");    
    int menuChoice = kpd.getKey() - '0';
    //Serial.print(menuChoice);
    if (menuChoice > 0) 
       goToSection(menuChoice);
    //inHomePage = !inHomePage;
    
  /*  if(touchState == TOUCH_RELEASED)                      // if there's a release
     {
        if ((x >= 80) && (x <= 140) && (y >= 100) && (y <= 130))     // Width=200 Height= 60
        {
           showPage(0, NULL);
           inHomePage = !inHomePage; 
        }
     }
     */
   }
   
   if (pages[pageNum].acceptsInput) // we're not going to need this anymore...
   {
      char key = kpd.getKey();
      pages[pageNum].inputVal = getNumber(key, Display);
      goNext(pageNum);
      Serial.print(pageNum);
      if (pageNum == 5) //THIS IS MEGA HACKY, WE WILL NOT DO THIS IN THE ACTUAL PROGRAM
      {
         double bmi = calculateBMI(pages[3], pages[4]);
         Serial.print("calculating BMI");
         showPage(pageNum, bmi);
      }
      else
         showPage(pageNum, NULL);
   }
   /*if (pageNum == 5)
   {
      double bmi = calculateBMI();
      Serial.print(bmi);
      showPage(pageNum, bmi);*/
     //Serial.print(pageNum);
     //am I supposd to be worrying about malloc and calloc here...?

   //so, touchscreen won't work on a page where the keypad is activated... Intersting. Not sure HOW worth it it would be to debug this, since we're dispensing with the touchpad soon anyway.
   //what happens if user accidently hits a letter while entering a number (right now it resets so they have to start again, but that's not terribly clear)
  /* touchState = Display.touch_Get(TOUCH_STATUS);               // get touchscreen status
  //-----------------------------------------------------------------------------------------
  if((touchState == TOUCH_PRESSED) || (touchState == TOUCH_MOVING))                       // if there's a press, or it's moving
  {
    x = Display.touch_Get(TOUCH_GETX);
    y = Display.touch_Get(TOUCH_GETY);
  }*/

  readButtons(pageNum);
  delay(200) ; // I have qualms about this... let's return!!! 

  //-----------------------------------------------------------------------------------------
  
  /*
      if(touchState == TOUCH_RELEASED)                      // if there's a release
     {
        if ((x >= 20) && (x <= 70) && (y >= 300) && (y <= 320))     // Width=200 Height= 60
        {
           goBack(pageNum);
           showPage(pageNum, NULL);
        }
        else if ((x >= 100) && (x <= 150) && (y >= 300) && (y <= 320))
        {
           getHelp();     
        }
        else if ((x >= 180) && (x <= 210) && (y >= 300) && (y <= 320)) 
        {
           goNext(pageNum);
           showPage(pageNum, NULL);
        }
     } 
     */
}

