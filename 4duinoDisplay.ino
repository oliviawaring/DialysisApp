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

Picaso_Serial_4DLib Display(&DisplaySerial);


// routine to handle Serial errors


const char *strings[] = {"This is dialysis instruction 1. Insert the cartridge.",
                         "This is dialysis instruction 2. Snap and tap.",
                         "This is dialysis instruction 3. Cannulate.",
                         NULL};

const char *helpText = "Do you need help?"; 
const char *homeText = "Welcome to your in-home dialysis buddy!"; 
/*void homeScreen()
{
  Display.gfx_Cls();   // clear screen
  Display.putstr("Welcome to your in-home dialysis portal.") ;  
  Display.gfx_Button(BUTTON_UP, 50, 220, GRAY, WHITE, FONT3, 3, 3, "START") ;

  if(state == TOUCH_RELEASED)                      // if there's a release
  {
    if ((x >= 50) && (x <= 170) && (y >= 220) && (y <= 280))     // Width=200 Height= 60
    {
      BstateBack = !BstateBack ;
      Display.gfx_MoveTo(10,120) ;
      if (BstateBack)   // If button state is ON
      {
        Display.gfx_Button(BstateBack, 20, 40, RED, WHITE, FONT3, 3, 3, "Press Me") ;
        Display.putstr("LED State: ON ") ;
        digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
      }
      else   // If button state is off
      {
         Display.gfx_Button(BstateBack, 20, 40, GRAY, WHITE, FONT3, 3, 3, "Press Me") ;
         Display.putstr("LED State: OFF") ;
         digitalWrite(13, LOW);   // turn the LED on (HIGH is the voltage level)
      }
    }
}*/

void nextpage(int ErrCode, unsigned char Errorbyte)
{
#ifdef LOG_MESSAGES
  const char *Error4DText[] = {"OK\0", "Timeout\0", "NAK\0", "Length\0", "Invalid\0"} ;
  LOG_MESSAGES.print(F("Serial 4D Library reports error ")) ;
  LOG_MESSAGES.print(Error4DText[ErrCode]) ;
  if (ErrCode == Err4D_NAK)
  {
    LOG_MESSAGES.print(F(" returned data= ")) ;
    LOG_MESSAGES.println(Errorbyte) ;
  }
  else
    LOG_MESSAGES.println(F("")) ;
  while (1) ; // you can return here, or you can loop
#else
  // Pin 13 has an LED connected on most Arduino boards. Just give it a name
#define led 13
  while (1)
  {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(200);                // wait for a second
  }
#endif
}
// end of routine to handle Serial errors



word BstateBack, BstateNext, BstateHelp ;
word x, y ;
int page = 0;
void goNext(int & page) ;
void goBack(int & page) ;
void getHelp() ;
void goHome() ;
boolean inHomePage = true;

void setup()
{
 pinMode(RESETLINE, OUTPUT);       // Display reset pin
digitalWrite(RESETLINE, 1);       // Reset Display, using shield
  delay(100);                       // wait for it to be recognised
digitalWrite(RESETLINE, 0);       // Release Display Reset, using shield
// Uncomment when using ESP8266
//  pinMode(ESPRESET, OUTPUT);        // ESP reset pin
//  digitalWrite(ESPRESET, 1);        // Reset ESP
//  delay(100);                       // wait for it t
//  digitalWrite(ESPRESET, 0);        // Release ESP reset
  delay(4000) ;                     // give display time to startup

  // now start display as Serial lines should have 'stabilised'
  DisplaySerial.begin(200000) ;     // Hardware serial to Display, same as SPE on display is set to
  Display.TimeLimit4D = 5000 ;      // 5 second timeout on all commands
  Display.Callback4D = nextpage ;

// uncomment if using ESP8266
//  ESPserial.begin(115200) ;         // assume esp set to 115200 baud, it's default setting
                                    // what we need to do is attempt to flip it to 19200
                                    // the maximum baud rate at which software serial actually works
                                    // if we run a program without resetting the ESP it will already be 19200
                                    // and hence the next command will not be understood or executed
//  ESPserial.println("AT+UART_CUR=19200,8,1,0,0\r\n") ;
//  ESPserial.end() ;
//  delay(10) ;                         // Necessary to allow for baud rate changes
//  ESPserial.begin(19200) ;            // start again at a resonable baud rate
  Display.gfx_ScreenMode(PORTRAIT) ; // change manually if orientation change
  // put your setup code here, to run once:

  pinMode(13, OUTPUT);
  Display.touch_Set(TOUCH_ENABLE);                            // enable the touch screen
  BstateBack = BUTTON_UP ;
  BstateNext = BUTTON_UP ;
  BstateHelp = BUTTON_UP ;
  
  Display.gfx_Cls();   // clear screen
  Display.gfx_Button(BstateBack, 100, 300, RED, BLACK, FONT3, 1, 1, "Help") ;
  Display.gfx_Button(BstateNext, 20, 300, GRAY, WHITE, FONT3, 1, 1, "Back") ;
  Display.gfx_Button(BstateHelp, 180, 300, GRAY, WHITE, FONT3, 1, 1, "Next") ;

  Display.txt_Width(1);
  Display.txt_Height(1);
  Display.gfx_MoveTo(0,0) ;
  Display.putstr("Here we have an instruction related to dialysis. Yay! What fun.") ;      
  Display.putstr(strings[0]);// Start with LED OFF
  byte state ;
  goHome();
  state = Display.touch_Get(TOUCH_STATUS);               // get touchscreen status
  //-----------------------------------------------------------------------------------------
  if((state == TOUCH_PRESSED) || (state == TOUCH_MOVING))                       // if there's a press, or it's moving
  {
    x = Display.touch_Get(TOUCH_GETX);
    y = Display.touch_Get(TOUCH_GETY);
  }
  page = 0;

} // end Setup **do not alter, remove or duplicate this line**


void showPage(int page)
{
  Display.gfx_Cls();   // clear screen
  Display.putstr(strings[page]) ;
  Display.gfx_Button(BstateBack, 100, 300, RED, BLACK, FONT3, 1, 1, "Help") ;
  Display.gfx_Button(BstateNext, 20, 300, GRAY, WHITE, FONT3, 1, 1, "Back") ;
  Display.gfx_Button(BstateHelp, 180, 300, GRAY, WHITE, FONT3, 1, 1, "Next") ;
}

void loop()
{  
   byte state ;

   state = Display.touch_Get(TOUCH_STATUS);               // get touchscreen status
  //-----------------------------------------------------------------------------------------
  if((state == TOUCH_PRESSED) || (state == TOUCH_MOVING))                       // if there's a press, or it's moving
  {
    x = Display.touch_Get(TOUCH_GETX);
    y = Display.touch_Get(TOUCH_GETY);
  }

  //-----------------------------------------------------------------------------------------
  if (!inHomePage)
  {
     if(state == TOUCH_RELEASED)                      // if there's a release
     {
        if ((x >= 20) && (x <= 70) && (y >= 300) && (y <= 320))     // Width=200 Height= 60
        {
           goBack(page);
           showPage(page);
        }
        else if ((x >= 100) && (x <= 150) && (y >= 300) && (y <= 320))
        {
           getHelp();     
        }
        else if ((x >= 180) && (x <= 210) && (y >= 300) && (y <= 320)) 
        {
           goNext(page);
           showPage(page);
        }
     }
  }
  else
  {
    if(state == TOUCH_RELEASED)                      // if there's a release
     {
        if ((x >= 80) && (x <= 140) && (y >= 100) && (y <= 130))     // Width=200 Height= 60
        {
           showPage(0);
           inHomePage = !inHomePage; 
        }
     }
  }
}

void goNext(int &page) 
{  
  //BstateNext = !BstateNext ;
  if (page == 0)
  {
    Serial.println("I'm inside the loop");
    page++;
  }
  else if (strings[page + 1] != NULL ) 
  {
    page++;
  }
  Serial.print(page);
}

void goBack(int &page) 
{
  //BstateBack = !BstateBack ;
  if (page != 0)
  {
    page--;
  }
  Serial.print(page);
}

void getHelp() 
{
  Display.gfx_Cls();   // clear screen
  Display.putstr(helpText) ;
  Display.gfx_Button(BstateBack, 0, 100, RED, BLACK, FONT3, 2, 2, "Dial Clinician") ;
}

void goHome() 
{
  Display.gfx_Cls();   // clear screen
  Display.putstr(homeText) ;
  Display.gfx_Button(BstateBack, 80, 100, RED, BLACK, FONT3, 2, 2, "Start") ;
}







