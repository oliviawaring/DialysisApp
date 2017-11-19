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

double getNumber(char key, Picaso_Serial_4DLib Display)
{
   double num = 0;
   int postDecVal = 0; // tracks whether we have added a decimal point yet, and how far along we are

   while (key != "D")
   {
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
   return num;
}
