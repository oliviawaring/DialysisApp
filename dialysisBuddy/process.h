// using pointers in C is too risky, let's try a WHOLE new approach

extern Keypad kpd;
extern Adafruit_ILI9340 screen;
extern SoftwareSerial lcdScreen;
extern Session currentSession;
double num = 0;
int globalButton = 0;

void displayValue(double num)
{
     screen.fillScreen(ILI9340_BLACK);
     screen.setCursor(0, 0);
     screen.setTextColor(ILI9340_WHITE);  
     screen.setTextSize(2);
     screen.println(num);
}

void process(int n)
{
   Serial.print("Davey\n");
   Serial.print(n);
   Serial.print("\nIn Homepage");
   Serial.print(inHomePage);
   Serial.print("\nIn Content");
   Serial.print(inContent);
   Serial.print("\nIn Setup");
   Serial.print(inSetup);
   Serial.print("\nIn Treatment");
   Serial.print(inTreatment);
   //if ((n > 6) || (oneCycle))
  //    return;
  // else
   //   oneCycle = true;
   if (inContent)
   {
      Serial.print("I am in content");
      if (inTail)
      {
         switch(n)
         {
            case 1: case 2: case 3:
            {
               //nothing happens, there is no next capability
               break;
            }
            case 4: //back - this is going to be REALLY irritating, because we have to account for all the different possibilities... I should draw a diagram
            {
                if (inSetupMenu) // I don't actually think I need this
                {
                    Serial.print("I should not be here\n");
                    bmpDraw("msetup.bmp", 0, 0);
                    inTail = false;
                    inContent = false;
                  //  inSetup = true;
                }
                else if (inTreatment)
                {     
                    // man I really gotta figure this one out... NEED to get these bmps working though... 
                }
                else if (inCommon) 
                {
                    bmpDraw("mcommon.bmp", 0, 0);
                    inTail = false;
                    inContent = false;
                }
                else // in this case, we're in a tail not within a submenu, and the next step directly up is the homepage!!
                // this is a mess, just fyi. But as long as it works. 
                {
                   Serial.print("T1\n");
                   bmpDraw("main.bmp", 0, 0);
                   inTail = false;
                   inHomePage = true;
                   inContent = false;
                }
                break;
            }
            case 5:
            {
               Serial.print("this is maddening\n");
               bmpDraw("main.bmp", 0, 0);
               inHomePage = true;
               inContent = false;
               inCommon = false;
               inSetup = false;
               inTreatment = false;
               break;
            }
            case 6:
            {
               bmpDraw("mhelp.bmp", 0, 0);
               inHelp = true;
               inHomePage = false;
               inContent = false;
               inCommon = false;
               inSetup = false;
               inTreatment = false;
               // should the help page count as being in content?
               break;
            }
            default:
            {
               break;
            }
         }
      }
      else
      {
         Serial.print("I am not in tail");
         switch(n)
         {
            case 1: 
            {
               if (inTreatment)
               {
                  switch(sequenceNum)
                  {
                     case 1:
                     {
                         
                         lcdScreen.write(12); // Clear
                         lcdScreen.print("Target weight:");  // First line
                         lcdScreen.write(13);                 // Carriage return
                         //bmpDraw("tweight.bmp", 0, 0); // WHY is this not displaying. I think I keep bumping up against variations of the same problem... Maybe it is a memory issue?
                         //char key = kpd.getKey(); 
                         char key = kpd.getKey(); 
                         double num = 0;
                         int postDecVal = 0; // Tracks whether we have added a decimal point yet, and how far along we are.
                         int menuChoice = readButtons();
                         while (menuChoice != 1) 
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
                                    lcdScreen.print(value); 
                                    Serial.print("why are we not printing?");
                                    break;
                                 }
                                 case '.': 
                                 {
                                    postDecVal++;
                                    lcdScreen.print(".");
                                    break;
                                 }
                               }
                            }
                            key = kpd.getKey();
                            menuChoice = readButtons();
                            Serial.print(num);
                         }
                         currentSession.targetWeight = num;
                         sequenceNum++;
                         break;
                     }
                     case 2:
                     {
                         lcdScreen.write(12); // Clear
                         lcdScreen.print("Treatment time:");  // First line
                         lcdScreen.write(13);                 // Carriage return
                         char key = kpd.getKey(); 
                         double num = 0;
                         int postDecVal = 0; // Tracks whether we have added a decimal point yet, and how far along we are.
                         int menuChoice = readButtons();
                         while (menuChoice != 1) 
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
                                    lcdScreen.print(value); 
                                    Serial.print("why are we not printing?");
                                    break;
                                 }
                                 case '.': 
                                 {
                                    postDecVal++;
                                    lcdScreen.print(".");
                                    break;
                                 }
                               }
                            }
                            key = kpd.getKey();
                            menuChoice = readButtons();
                            Serial.print(num);
                         }
                         currentSession.treatmentTime = num;
                         sequenceNum++;
                         break;
                     }
                     case 3:
                     {
                         lcdScreen.write(12); // Clear
                         lcdScreen.print("Ultrafilt. rate");  // First line
                         lcdScreen.write(13);                 // Carriage return
                         calculateUltraFiltrationRate();
                         lcdScreen.print(currentSession.ufRate);  
                         sequenceNum++;
                         break;
                     }
                     default:
                     {
                        break;
                     }
                  }
               }
               break;
            }
            case 2:
               break;
            case 3: // next
            {
               Serial.print("I am in next");
               if (inSetup)
               {
                  Serial.print("I am in setup");
                  switch(sequenceNum)
                  {
                     Serial.print("Life is hard");
                     case 1:
                     {
                         bmpDraw("setup2.bmp", 0, 0);
                         sequenceNum++;
                         break;
                     }
                     case 2:
                     {
                         bmpDraw("setup3.bmp", 0, 0);
                         sequenceNum++;
                         break;
                     }
                     case 3:
                     {
                         Serial.print("why am I here???");
                         bmpDraw("setup4.bmp", 0, 0);
                         sequenceNum++;
                         break;
                     }
                     case 4:
                     {
                         bmpDraw("setup5.bmp", 0, 0);
                         sequenceNum++;
                         break;
                     }
                     case 5:
                     {
                         bmpDraw("setup6.bmp", 0, 0);
                         sequenceNum++;
                         break;
                     }
                     case 6:
                     {
                         bmpDraw("setup7.bmp", 0, 0);
                         sequenceNum++;
                         break;
                     }
                     case 7:
                     {
                         bmpDraw("setup8.bmp", 0, 0);
                         break;
                     }
                     case 8:
                     {
                         bmpDraw("setup8.bmp", 0, 0);
                         break;
                     }
                     default:
                     {
                        break;
                     }
                  }
               }
               break;
            }
            case 4: // back
            {     
               if (inTreatment) // okay this patently DOES NOT WORK and I'm just gonna have to live with that I guess...
               {
                  bmpDraw("main.bmp", 0, 0);
                  inHomePage = true;
                  inContent = false;
                  inTreatment = false;
               }
               else if (inSetup)
               {
                  Serial.print("I am in content");
                  switch(sequenceNum)
                  {
                     case 1:
                     {
                         bmpDraw("msetup.bmp", 0, 0);
                         inContent = false;
                         sequenceNum--;
                         break;
                     }
                     case 2:
                     {
                         Serial.print("Am I here? 1");
                         bmpDraw("setup1.bmp", 0, 0);
                         sequenceNum--;
                         break;
                     }
                     case 3:
                     {
                         bmpDraw("setup2.bmp", 0, 0);
                         sequenceNum--;
                         break;
                     }
                     case 4:
                     {
                         bmpDraw("setup3.bmp", 0, 0);
                         sequenceNum--;
                         break;
                     }
                     case 5:
                     {
                         bmpDraw("setup4.bmp", 0, 0);
                         sequenceNum--;
                         break;
                     }
                     case 6:
                     {
                         bmpDraw("setup5.bmp", 0, 0);
                         sequenceNum--;
                         break;
                     }
                     case 7:
                     {
                         bmpDraw("setup6.bmp", 0, 0);
                         sequenceNum--;
                         break;
                     }
                     case 8:
                     {
                         bmpDraw("setup7.bmp", 0, 0);
                         sequenceNum--;
                         break;
                     }
                     default:
                         break;
                     // if we hit case 8 there's something wrong because this should have been flagged in the tail bit
                  }
               }
               else if (inTreatment)
               {
                  switch(sequenceNum)
                  {
                     case 1:
                     {
                         Serial.print("T2\n");
                         bmpDraw("main.bmp", 0, 0);
                         sequenceNum--;
                         break;
                     }
                     case 2:
                     {
                         bmpDraw("cweight.bmp", 0, 0);
                         sequenceNum--;
                         break;
                     }
                     case 3:
                     {
                         Serial.print("\nhelloooo");
                         bmpDraw("tweight.bmp", 0, 0);
                         sequenceNum--;
                         break;
                     }
                      case 4:
                     {
                         bmpDraw("time.bmp", 0, 0);
                         sequenceNum--;
                         break;
                     }
                     default:
                     {
                        break;
                     }
                  }
               }
               break;
            }
            case 5:
            {
               Serial.print("shouldn't be here\n");
               bmpDraw("main.bmp", 0, 0);
               inHomePage = true;
               inContent = false;
               break;
            }
            case 6:
            {
               bmpDraw("mhelp.bmp", 0, 0);
               inHelp = true;
               break;
            }
            default:
            {
               break;
            }
         }
      }
   }   

   //Testing this is going to be a NIGHTMARE... have to make sure all possible paths are working, with all these crazy variables!
   else if (inHomePage)
   {
       Serial.print("ugh!");
       switch(n)
       {
          case 1:
          {
             Serial.print("here!");
             inTreatment = true;
           //  screen.text("Enter the patient's current weight (in kg) and press SELECT: \n",0,0);
             bmpDraw("ventry.bmp", 0, 0);
             char key = kpd.getKey(); 
             lcdScreen.write(12);
             lcdScreen.print("Current weight:");  // First line
             lcdScreen.write(13);     
             //currentSession.currentWeight = getNumber(key);
             double num = 0;
             int postDecVal = 0; // Tracks whether we have added a decimal point yet, and how far along we are.
             int menuChoice = readButtons();
             while (menuChoice != 1) 
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
                        lcdScreen.print(value); 
                        Serial.print("why are we not printing?");
                        break;
                     }
                     case '.': 
                     {
                        postDecVal++;
                        lcdScreen.print(".");
                        break;
                     }
                   }
                }
                key = kpd.getKey();
                menuChoice = readButtons();
                Serial.print(num);
             }
             currentSession.currentWeight = num;
             Serial.print("after\n");
             Serial.print(currentSession.currentWeight);
             sequenceNum = 1; 
             inHomePage = false; 
             inContent = true;
             //n = globalButton;
             break;
          }
          case 2:  
          {
             bmpDraw("msetup.bmp", 0, 0);
             inSetupMenu = true;
             inHomePage = false; 
             break;
          }
          case 3:
          {
             bmpDraw("launch1.bmp", 0, 0);
             inContent = true;
             inTail = true;
             inHomePage = false; 
             break;
          }
          case 4:
          {
             bmpDraw("end1.bmp", 0, 0);
             inContent = true;
             inTail = true;
             inHomePage = false; 
             break;
          }
          case 5:
          {
             Serial.print("gaaqaaaaaah\n");
             bmpDraw("mcommon.bmp", 0, 0);
             inHomePage = false; 
             inCommon = true;
             inContent = false;
             break;
          }
          case 6:
          {
             inErrors = true;
             bmpDraw("ecode.bmp", 0, 0);
             lcdScreen.write(12); // Clear
             lcdScreen.print("Error code:");  // First line
             lcdScreen.write(13);
             char key = kpd.getKey(); 
             ErrorCode ec = {'0', 0, false};
             int num = 0;
             boolean gotColor = false;
             int menuChoice = readButtons();
             int gotNum = 0;
             while (menuChoice != 1) // we have to change this to a button press, eventually... dayum, that's going to be complicated
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
 // Get out of the function entirely - need to try again (maybe there should actually be a subroutine asking for the color...
                         }
                         Serial.print("safe");
                         num = num * 10 + (key - '0');
                         char value[] = {key, '\0'};  
                         lcdScreen.print(value);
//                         Display.putstr(value); 
                         gotNum++;
                         break;
                      }
                      case '.': 
                      {
                         Serial.print("case A");
                         if (gotColor)
                            return ec; // too many color codes! 
                         ec.color = 'Y'; // Green error code! 
                         gotColor = !gotColor;
                         lcdScreen.print("Yellow ");
//                         Display.putstr("Green ");
                         break;
                      }
                      case '#': 
                      {
                         if (gotColor)
                            return ec; // too many color codes! 
                         ec.color = 'R'; // Red error code! 
                         gotColor = !gotColor;
                         lcdScreen.print("Red ");
        //                 Display.putstr("Red ");
                         break;
                      }
                      default:
                         break;
                   }
                }
                menuChoice = readButtons();
                key = kpd.getKey();
             }
             Serial.print("did i leave?");
             ec.num = num;
             ec.complete = true;
             inHomePage = false; 
             bmpDraw("r010_1.bmp", 0, 0);
             break;
          }
          default:
          {
             break;
          }
       }
   }
   else if (inSetupMenu)
   {
       Serial.print("I am in setup yay");
       switch(n)
       {
          case 1:
          {
             Serial.print("Am I here? 2");
             bmpDraw("setup1.bmp", 0, 0);
             sequenceNum = 1;
             inSetup = true;
             inSetupMenu = false;
             inContent = true;
             break;
          }
          case 2:  
          {
             bmpDraw("prime1.bmp", 0, 0);
             inTail = true;
             inSetupMenu = true;
             inContent = true;
             break;
          }
          case 3:
          {
             bmpDraw("connect1.bmp", 0, 0);
             inTail = true;
             inSetupMenu = true;
             inContent = true;
             break;
          }
          case 4:
          {
             bmpDraw("settings1.bmp", 0, 0);
             inTail = true;
             inSetupMenu = true;
             inContent = true;
             break;
          }
          case 5:
          {
             bmpDraw("launch1.bmp", 0, 0);
             inTail = true;
             inSetupMenu = true;
             inContent = true;
             break;
          }
          case 6:
          {
             bmpDraw("end1.bmp", 0, 0);
             inTail = true;
             inSetupMenu = true;
             inContent = true;
             break;
          }
          default:
          {
             break;
          }
       }
   }
   else if (inCommon)
   {
       switch(n)
       {
          case 1:
          {
             bmpDraw("hypo1.bmp", 0, 0);
             inTail = true;
             inContent = true;
             break;
          }
          case 2:  
          {
             bmpDraw("bolus1.bmp", 0, 0);
             inTail = true;
             inContent = true;
             break;
          }
          case 3:
          {
             bmpDraw("clot1.bmp", 0, 0);
             inTail = true;
             inContent = true;
             break;
          }
          case 4:
          {
             bmpDraw("remove1.bmp", 0, 0);
             inTail = true;
             inContent = true;
             break;
          }
          case 5:
          {
             Serial.print("WHY ISN'T THIS WORKING");
             bmpDraw("fluid1.bmp", 0, 0);
             inContent = true;
             inTail = true;
             break;
          }
          case 6:
          {
             bmpDraw("lab1.bmp", 0, 0);
             inTail = true;
             inContent = true;
             break;
          }
          default:
             break;   
      }
   }
   Serial.print("I am exiting this function.\n");
}

