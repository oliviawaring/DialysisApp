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
#include "Math.h"


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
int NUM_PAGES = 6; // can't define an array with a variable though... shucks

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//////////////
      //analog reading of buttons through pin A0
int adc_key_in  = 0;
int button_pressed = 0;
#define btnBLACK1    0
#define btnYELLOW    1
#define btnGREEN     2
#define btnWHITE    3
#define btnBLUE      4
#define btnBLACK2    5
#define btnNONE      6
int read_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 if (adc_key_in > 1000) return btnNONE; 
 if (adc_key_in < 170)   return btnBLACK1;  
 if (adc_key_in < 341)  return btnYELLOW; 
 if (adc_key_in < 511)  return btnGREEN; 
 if (adc_key_in < 682)  return btnWHITE; 
 if (adc_key_in < 852)  return btnBLUE;
 if (adc_key_in < 1023)  return btnBLACK2;   
 return btnNONE;  // when all others fail, return this...
}
///////////////

struct Page
{
  char *text;
  boolean acceptsInput;
  double inputVal; // yup, cuz the way we've designed it there's only one per page, yeah?
};

Page pages[6] = {{"This is dialysis instruction 1. Insert the cartridge.", false, NULL},
                 {"This is dialysis instruction 2. Snap and tap.", false, NULL},
                 {"This is dialysis instruction 3. Cannulate.", false, NULL},
                 {"Enter the patient's weight (in pounds) and press Enter (D): \n", true, NULL},
                 {"Enter the patient's height (in inches) and press Enter (D): \n", true, NULL},
                 {"The patient's body mass index (BMI) is: \n", false, NULL}};
 
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

double calculateBMI()
{
  double weight = pages[3].inputVal;
  double height = pages[4].inputVal;
  double bmi = 703 *  weight / (height * height);
  return bmi;
}

void double2string(char *number, double n)
{
   char integers[6] = {'0','0','0','0','0','0'};
   char fractions[6] = {'0','0','0','0','0','0'};
   int i = 5; //related to that length... we'll work it out... CODE CODE CODE!
   double integral; // this is, numerically, the integer part
   double fractional = modf(n, &integral);
   int integralI = (int)integral; //this is TERRIBLE code. Please just let it work for now.
   while (integralI > 0)
   {
      integers[i] = ((int)fmod(integralI,10)) + '0';
      integralI=integralI/10;
      i--;
   }
   int k = 0;
   int q = 5 - i;
  // Serial.print("fractional\n");
  // Serial.print(fractional);
   while (q > 0)
   {
       fractional = fractional * 10;
       //Serial.print(floor(fractional));
       //Serial.print((int)floor(fractional));
       fractions[k] = ((int)floor(fractional)) + '0';
       fractional = fmod(fractional,1);
       k++;
       q--;
   }
   //WHY DOES PRINTING TO SERIAL MATTER FOR THE DISPLAY AAAAAH
   //Serial.print("integers\n");
   //Serial.print(integers);
  // Serial.print("fractions\n");
  // Serial.print(fractions);
  // Serial.print("\n");
   int j = 0; // the length of the final array
   while ((j < 6) && (i < 6))
   {
      number[j] = integers[i+1];
      j++;
      i++;
   }
   if (j != 6)
   {
      number[j-1] = '.';
      j++;
   }
   j--;
   int p = 0;
   while ((j < 6) && (p < 6)) 
   {
      number[j] = fractions[p];
      j++;
      p++;  
   }
   
   //while 
   //int fractionalI = (int)(fractional * exponentiate(10, potentialFractionalSize)
  /* Serial.print(number[0]);
   Serial.print("Davey\n");
      Serial.print(number[1]);
   Serial.print("Davey\n");
      Serial.print(number[2]);
   Serial.print("Davey\n");
      Serial.print(number[3]);
   Serial.print("Davey\n");
      Serial.print(number[4]);
   Serial.print("Davey\n");
      Serial.print(number[5]);
   Serial.print("Davey\n"); */
   return number;
}

void showPage(int pageNum, double val)
{
  Display.gfx_Cls();   // clear screen
  Display.putstr(pages[pageNum].text) ;
  if (val != (double)NULL)
  {
     Serial.print("Davey");
     //char value[] = {val, '\0'};
     //Serial.print(value);
     char answer[] = {'0','0','0','0','0','0'};
     double2string(answer, val);
     Serial.print(answer);
     Display.putstr(answer);
  }
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

double exponentiate(double x, int y) //this exists in the math library already... remove later
{
  double num = x;
  while (y > 1)
  {
     num = num * x;
     y--; 
  }
  return num;
  //Serial.print(num);
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
               char value[] = {key, '\0'};
               Display.putstr(value); 
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
   Serial.print(pageNum);
   return num;

}

void loop()
{  
   byte touchState ;
   byte buttonState1 = digitalRead(BUTTON1);
   byte buttonState2 = digitalRead(BUTTON2);
   byte buttonState3 = digitalRead(BUTTON3);
   byte buttonState4 = digitalRead(BUTTON4);

 ///////////////////
 button_pressed = read_buttons();
 switch (button_pressed)               // depending on which button was pushed, we perform an action
 {
   case btnBLACK1:
     {Serial.print("BLACK1");
     break;}
   case btnYELLOW:
     {Serial.print("YELLOW");
     break;}
   case btnGREEN:
     {Serial.print("GREEN");
     break;}
   case btnWHITE:
     {Serial.print("WHITE");
     break;}
    case btnBLUE:
     {Serial.print("BLUE");
     break;}
   case btnBLACK2:
     {Serial.print("BLACK2");
     break;}
     }
 ////////////////////
   double v1 = 0;
   
   if (pages[pageNum].acceptsInput)
   {
      //Serial.print(pageNum);
      char key = kpd.getKey();
      pages[pageNum].inputVal = getNumber(key);
      goNext(pageNum);
      Serial.print(pageNum);
      if (pageNum == 5) //THIS IS MEGA HACKY, WE WILL NOT DO THIS IN THE ACTUAL PROGRAM
      {
         double bmi = calculateBMI();
         Serial.print("calculating BMI");
         showPage(pageNum, bmi);
      }
      else
         showPage(pageNum, NULL);
      //Serial.print("hello!\n");
      //Serial.print(pageNum);
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
           showPage(0, NULL);
           inHomePage = !inHomePage; 
        }
     }
  }
}

void goNext(int &pageNum) 
{  
  //BstateNext = !BstateNext ;
  if ((pageNum == 0) || (pageNum != NUM_PAGES)) // this way of checking wheter we've reached the end is hacky
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
