/**** keyboard.h ****/

//extern Picaso_Serial_4DLib Display;

const byte ROWS = 4; // Four rows on our keypad
const byte COLS = 4; // Four columns on our keypad 

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'.','0','#','D'}
};

// Connect the pins
byte rowPins[ROWS] = { 2, 3, 4, 5 };
byte colPins[COLS] = { 6, 7, 8, 9 }; 

// Initialize the keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

double getNumber(char key)
{
   double num = 0;
   int postDecVal = 0; // Tracks whether we have added a decimal point yet, and how far along we are.

   while (key != 'D') // we have to change this to a button press, eventually... dayum, that's going to be complicated
   {
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
                  double decimalBit = exponentiate(0.1, postDecVal);
                  num = num + ((key - '0') * exponentiate(0.1, postDecVal));
                  postDecVal++;
               }
               else 
                  num = num * 10 + (key - '0');
               char value[] = {key, '\0'};
//               Display.putstr(value); 
               break;
            }
            case '.': 
               postDecVal++;
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
//               Display.putstr("Green ");
               break;
            }
            case 'B': 
            {
               if (gotColor)
                  return ec; // too many color codes! 
               ec.color = 'R'; // Red error code! 
               gotColor = !gotColor;
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


