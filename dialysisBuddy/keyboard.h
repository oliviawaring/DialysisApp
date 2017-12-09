/**** keyboard.h ****/

//extern Picaso_Serial_4DLib Display;
extern Adafruit_ILI9340 screen;

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
   double num = 0;
   int postDecVal = 0; // Tracks whether we have added a decimal point yet, and how far along we are.
   while (key != 'D') // we have to change this to a button press, eventually... dayum, that's going to be complicated HOW AM I GOING TO DO THIS OMG
   // it's okay... i was gonna have to overhaul this anyway, cuz it can't be the D thing...
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
                  num = num + ((key - '0') * exponentiate(0.1, postDecVal));
                  postDecVal++;
               }
               else 
                  num = num * 10 + (key - '0');
               char value[] = {key, '\0'};
               Serial.print(value);
               Serial.print("are we here?");
               screen.fillScreen(ILI9340_RED);
              /* screen.setCursor(100, 100);
               screen.setTextColor(ILI9340_WHITE);  
               screen.setTextSize(4);
               screen.println("hi");*/
//               Display.putstr(value); 
               Serial.print("why are we not printing?");
               break;
            }
            case '.': 
               postDecVal++;
               screen.print(".");
//               Display.putstr(".");
               break;
            case 'A': 
               // this is going to have to read as green at some point...
               break;
            case 'B': 
               // and this will eventually represent red... AAAH. 
               break;
            case '#': case 'C': case 'D':
               return num;
               break;
         }
      }
      key = kpd.getKey();
   }
   return num;
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


