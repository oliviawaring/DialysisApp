/**** keyboard.h ****/

//extern Picaso_Serial_4DLib Display;
extern Adafruit_ILI9340 screen;
extern SoftwareSerial lcdScreen;
extern int globalButton;

const byte ROWS = 4; // Four rows on our keypad
const byte COLS = 3; // Four columns on our keypad 

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'.','0','#'}
};

// Connect the pins
byte rowPins[ROWS] = { 51, 41, 43, 47 };
byte colPins[COLS] = { 49, 53, 45 }; 

// Initialize the keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

double getNumber(char key)
{
   double num1 = 0;
   double num2 = 0;
   int postDecVal = 0; // Tracks whether we have added a decimal point yet, and how far along we are.
   int menuChoice = readButtons();
   while (key != 0) 
   {
      if(key)
      {
         Serial.print("\nlettuce");
         Serial.print(key);
         switch (key) 
         {           
            case NO_KEY:
               break;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
               if (postDecVal > 0)
               {
                  double decimalBit = exponentiate(0.1, postDecVal);
                  num1 = num1 + ((key - '0') * exponentiate(0.1, postDecVal));
                  postDecVal++;
               }
               else 
                  num1 = num1 * 10 + (key - '0');
               char value[] = {key, '\0'};
               Serial.print(value);
               Serial.print("are we here?");
               //screen.fillScreen(ILI9340_RED);
              /* screen.setCursor(100, 100);
               screen.setTextColor(ILI9340_WHITE);  
               screen.setTextSize(4);
               screen.println("hi");*/
               lcdScreen.print(value); 
               Serial.print("why are we not printing?");
               break;
            }
            case '.': 
               postDecVal++;
               lcdScreen.print(".");
               break;
            case '#': 
               return num1;
               break;
         }
      }
      key = kpd.getKey();
      menuChoice = readButtons();
      Serial.print(num1);
   }
   return num1;
   globalButton = key;
}



ErrorCode getErrorCode(char key)
{
   ErrorCode ec = {'0', 0, false};
   int num = 0;
   boolean gotColor = false;
   int gotNum = 0;
   while (key != 'D') // we have to change this to a button press, eventually... dayum, that's going to be complicated
   {
      if(key)
      {
          Serial.print(key);
         switch (key) 
         {
           
            case NO_KEY:
               break;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
               Serial.print("so confused");
               if ((!gotColor) || (gotNum > 2))
               {
                  Serial.print("Bad");
                  return ec; // Get out of the function entirely - need to try again (maybe there should actually be a subroutine asking for the color...
               }
               Serial.print("safe");
               num = num * 10 + (key - '0');
               char value[] = {key, '\0'};  
               screen.print(value);
//               Display.putstr(value); 
               gotNum++;
               break;
            }
            case 'A': 
            {
               Serial.print("case A");
               if (gotColor)
                  return ec; // too many color codes! 
               ec.color = 'G'; // Green error code! 
               gotColor = !gotColor;
               screen.print("Green ");
//               Display.putstr("Green ");
               break;
            }
            case 'B': 
            {
               if (gotColor)
                  return ec; // too many color codes! 
               ec.color = 'R'; // Red error code! 
               gotColor = !gotColor;
               screen.print("Red ");
        //       Display.putstr("Red ");
               break;
            }
            case '.': case '#': case 'C': case 'D':
               return ec; // not valid! 
               break;
         }
      }
      key = kpd.getKey();
   }
   Serial.print("did i leave?");
   ec.num = num;
   ec.complete = true;
   return ec;
}


