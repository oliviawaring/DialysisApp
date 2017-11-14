//
// NB! This is a file generated from the .4Dino file, changes will be lost
//     the next time the .4Dino file is built
//
// Define LOG_MESSAGES to a serial port to send SPE errors messages to. Do not use the same Serial port as SPE
//#define LOG_MESSAGES Serial

#define RESETLINE     30
#define BUTTON1       10 
#define BUTTON2       11
#define BUTTON3       12  
#define BUTTON4       13 

#define DisplaySerial Serial1


#include "Picaso_Serial_4DLib.h"
#include "Picaso_Const4D.h"
#include "Keypad.h"


Picaso_Serial_4DLib Display(&DisplaySerial);


// routine to handle Serial errors

#define buttonPin1   10 
#define buttonPin2   11 
#define buttonPin3   12  
#define buttonPin4   13 

const char *helpText = "Do you need help?"; 
const char *homeText = "Welcome to your in-home dialysis buddy!"; 
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'.','0','#','D'}
};
byte rowPins[ROWS] = { 2, 3, 4, 5 };
byte colPins[COLS] = { 6, 7, 8, 9 }; 

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

struct Page
{
  char *text;
  boolean acceptsInput;
};

Page pages[4] = {{"This is dialysis instruction 1. Insert the cartridge.", false},
                 {"This is dialysis instruction 2. Snap and tap.", false},
                 {"This is dialysis instruction 3. Cannulate.", false},
                 {"Enter the patient's weight: \n", true}};
 
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
int pageNum = 0;
void goNext(int & page) ;
void goBack(int & page) ;
void getHelp() ;
void goHome() ;
boolean inHomePage = true;

void setup()
{
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON4, INPUT);
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
  Display.putstr(pages[0].text );// Start with LED OFF
  byte state ;
  goHome();
  
  state = Display.touch_Get(TOUCH_STATUS);               // get touchscreen status
  //-----------------------------------------------------------------------------------------
  if((state == TOUCH_PRESSED) || (state == TOUCH_MOVING))                       // if there's a press, or it's moving
  {
    x = Display.touch_Get(TOUCH_GETX);
    y = Display.touch_Get(TOUCH_GETY);
  }
  pageNum = 0;

} // end Setup **do not alter, remove or duplicate this line**


void showPage(int pageNum)
{
  Display.gfx_Cls();   // clear screen
  Display.putstr(pages[pageNum].text) ;
  Display.gfx_Button(BstateBack, 100, 300, RED, BLACK, FONT3, 1, 1, "Help") ;
  Display.gfx_Button(BstateNext, 20, 300, GRAY, WHITE, FONT3, 1, 1, "Back") ;
  Display.gfx_Button(BstateHelp, 180, 300, GRAY, WHITE, FONT3, 1, 1, "Next") ;
  //int v1 = getNumber();
  //int v2 = getNumber();
  //Display.putstr(("v1 %d\n", v1));
  //Display.putstr(("v2 %d\n", v2));
  //int v3 = v1 + v2;
  //Display.putstr(("add %d", v3));
  //Serial.print(v1 * v2);
}

double exponentiate(double x, int y)
{
  double num = x;
  while (y > 1)
  {
     num = num * x;
     y--; 
  }
  return num;
  Serial.print(num);
}

double getNumber(char key)
{
   double num = 0;
   int postDecVal = 0; // tracks whether we have added a decimal point yet, and how far along we are

   while (key != "D")
   {
      //Serial.print("in GetNumber\n");
      Serial.print(key);
      if(key)
      {
         switch (key) 
         {
            case NO_KEY:
               break;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
               if (postDecVal > 0)
               {
                  Serial.print("\n yo yo");
                  double decimalBit = exponentiate(0.1, postDecVal);
                  Serial.println(decimalBit);
                  num = num + ((key - '0') * exponentiate(0.1, postDecVal));
                  postDecVal++;
               }
               else 
                  num = num * 10 + (key - '0');
               char stuff[] = {key, '\0'};
               Display.putstr(stuff); 
               break;
            }
            case '.': 
               postDecVal++;
               Serial.print("\n decimal point registered");
               Serial.print(postDecVal);
               Display.putstr(".");
               break;
            case '#': case 'A': case 'B': case 'C': case 'D':
               return num;
               break;
         }
         Serial.print("This is our number: ");
         Serial.print(num);
      }
      key = kpd.getKey();
   }
//   Serial.print(num);
   return num;
   return 0;
}

void loop()
{  
   byte touchState ;
   byte buttonState1 = digitalRead(BUTTON1);
   byte buttonState2 = digitalRead(BUTTON2);
   byte buttonState3 = digitalRead(BUTTON3);
   byte buttonState4 = digitalRead(BUTTON4);

   double v1 = 0;
   if (pages[pageNum].acceptsInput)
   {
      char key = kpd.getKey();
      v1 = getNumber(key);
      Serial.print("hello!\n");
      Serial.print(v1);
   }

   //so, touchscreen won't work on a page where the keypad is activated... Intersting. Not sure HOW worth it it would be to debug this, since we're dispensing with the touchpad soon anyway.
   //what happens if user accidently hits a letter while entering a number (right now it resets so they have to start again, but that's not terribly clear)
   touchState = Display.touch_Get(TOUCH_STATUS);               // get touchscreen status
  //-----------------------------------------------------------------------------------------
  if((touchState == TOUCH_PRESSED) || (touchState == TOUCH_MOVING))                       // if there's a press, or it's moving
  {
    x = Display.touch_Get(TOUCH_GETX);
    y = Display.touch_Get(TOUCH_GETY);
  }

  //-----------------------------------------------------------------------------------------
  if (!inHomePage)
  {
      if(touchState == TOUCH_RELEASED)                      // if there's a release
     {
        if ((x >= 20) && (x <= 70) && (y >= 300) && (y <= 320))     // Width=200 Height= 60
        {
           goBack(pageNum);
           showPage(pageNum);
        }
        else if ((x >= 100) && (x <= 150) && (y >= 300) && (y <= 320))
        {
           getHelp();     
        }
        else if ((x >= 180) && (x <= 210) && (y >= 300) && (y <= 320)) 
        {
           goNext(pageNum);
           showPage(pageNum);
        }
     } 
    /* if (buttonState1 == HIGH) 
     {
         goBack(page);
         showPage(page);
     }
     else if (buttonState2 == HIGH) 
     {
         goNext(page);
         showPage(page);
     }
     else if (buttonState3 == HIGH) 
     {
         getHelp();
     }
     else if (buttonState4 == HIGH) 
     {
         goHome();
     }*/
  }
  else
  {
    if(touchState == TOUCH_RELEASED)                      // if there's a release
     {
        if ((x >= 80) && (x <= 140) && (y >= 100) && (y <= 130))     // Width=200 Height= 60
        {
           showPage(0);
           inHomePage = !inHomePage; 
        }
     }
  }
}

void goNext(int &pageNum) 
{  
  //BstateNext = !BstateNext ;
  if ((pageNum == 0) || (pageNum != 4)) // this way of checking wheter we've reached the end is hacky
     pageNum++;
  Serial.print(pageNum);
}

void goBack(int &pageNum) 
{
  //BstateBack = !BstateBack ;
  if (pageNum != 0)
     pageNum--;
  Serial.print(pageNum);
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

