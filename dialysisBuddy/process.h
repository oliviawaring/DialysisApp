// using pointers in C is too risky, let's try a WHOLE new approach

extern Keypad kpd;
extern Adafruit_ILI9340 screen;
double num = 0;

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
   if ((n > 6) || (oneCycle))
      return;
   else
      oneCycle = true;
   if (inContent)
   {
      if (inTail)
      {
         switch(n)
         {
            case 1: case 2: case 3:
            {
               //nothing happens, there is no next capability
            }
            case 4: //back - this is going to be REALLY irritating, because we have to account for all the different possibilities... I should draw a diagram
            {
                if (inSetup)
                {
                    bmpDraw("setup7.bmp", 0, 0);
                    sequenceNum--;
                    inTail = false;
                }
                else if (inTreatment)
                {     
                    // man I really gotta figure this one out... NEED to get these bmps working though... 
                }
                //else if () // in a certain submenu
               // {
                
                //}
                else // in this case, we're in a tail, and the next step directly up is the homepage!!
                   return;
            }
            case 5:
            {
               bmpDraw("main.bmp", 0, 0);
               inHomePage = true;
               inContent = false;
            }
            case 6:
            {
               bmpDraw("mhelp.bmp", 0, 0);
               inHelp = true;
               // should the help page count as being in content?
            }
            default:
            {
               break;
            }
         }
      }
      else
      {
         switch(n)
         {
            case 1: case 2:
            {
               // these buttons do nothing
            }
            case 3:
            {
               if (inSetup)
               {
                  switch(sequenceNum)
                  {
                     Serial.print("Life is hard");
                     case 1:
                     {
                         bmpDraw("setup2.bmp", 0, 0);
                         sequenceNum++;
                     }
                     case 2:
                     {
                         bmpDraw("setup3.bmp", 0, 0);
                         sequenceNum++;
                     }
                     case 3:
                     {
                         bmpDraw("setup4.bmp", 0, 0);
                         sequenceNum++;
                     }
                     case 4:
                     {
                         bmpDraw("setup5.bmp", 0, 0);
                         sequenceNum++;
                     }
                     case 5:
                     {
                         bmpDraw("setup6.bmp", 0, 0);
                         sequenceNum++;
                     }
                     case 6:
                     {
                         bmpDraw("setup7.bmp", 0, 0);
                         sequenceNum++;
                     }
                     case 7:
                     {
                         bmpDraw("setup8.bmp", 0, 0);
                         inTail = true;
                     }
                     default:
                     {
                        break;
                     }
                  }
               }
            }
            case 4:
            {            
               if (inSetup)
               {
                  switch(sequenceNum)
                  {
                     case 1:
                     {
                         bmpDraw("msetup.bmp", 0, 0);
                         sequenceNum--;
                         break;
                     }
                     case 2:
                     {
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
                     // if we hit case 8 there's something wrong because this should have been flagged in the tail bit
                  }
               }
            }
            case 5:
            {
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
             screen.fillScreen(ILI9340_BLACK);
             screen.setCursor(0, 0);
             screen.setTextColor(ILI9340_WHITE);  
             screen.setTextSize(2);
             screen.println("Enter the patient's current weight (in kg) and press SELECT:");
             sequenceNum = 1;
             char key = 0;
             Serial.print("before");
             //key = kpd.getKey(); 
             //oh my god... getting inputs from keypad makes it no longer possible for the screen to display... hot damn. What now. 
             int menuChoice = readButtons();
             Serial.print("after");
             //int menuChoice = readButtons(); // ugggh this feels vurrry dangerous...
             
             int postDecVal = 0; 
             // I know this is all ugly and redundant and could be SO much more elegant, but that's why we're doing this... Trying to modularize is what got us into trouble in the first place
             
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
                         // there seems to constantly be a 1 in front of this... and none of the 2's, 5's, or 8's work. 
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
                         //screen.setCursor(10, 10);
                         //screen.setTextColor(ILI9340_WHITE);  
                        // screen.setTextSize(4);
                       //  screen.println("hi");
             //               Display.putstr(value); 
                         Serial.print("why are we not printing?");
                         break;
                      }
                      case '.': 
                         postDecVal++;
                         screen.print(".");
//                           Display.putstr(".");
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
                menuChoice = readButtons();
                Serial.print(menuChoice);
                key = kpd.getKey();
             }
             Serial.print(num);

             currentSession.currentWeight = num;
            // displayValue(num); 
             inHomePage = false; 
             Serial.print("\nwhy no loop???");
             break;
             // WHY ARE WE NO LONGER IN THE LOOP. Okay, we're back. it's the display value thing. that's VERY unfortunate. Maybe we can print it on the next go-round?
          }
          case 2:  
          {
             bmpDraw("msetup.bmp", 0, 0);
             inSetup = true;
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
             bmpDraw("mcommon.bmp", 0, 0);
             inHomePage = false; 
             inCommon = true;
             break;
          }
          case 6:
          {
             inErrors = true;
             screen.fillScreen(ILI9340_BLACK);
             screen.setCursor(0, 0);
             screen.setTextColor(ILI9340_WHITE);  
             screen.setTextSize(1);
             screen.println("Enter the error code (color and number) press SELECT: \n");
             sequenceNum = 1;
             char key = kpd.getKey(); 
             getErrorCode(key);
             inHomePage = false; 
             break;
          }
          default:
          {
             break;
          }
       }
   }
   else if (inTreatment)
   {
   // no... how am I handling the next button?
   // we should probably draw this in somehow. I'll save it for later. 
       Serial.print("ouch");
       bmpDraw("main.bmp", 0, 0); // might be the answer... have to re-display a bmp before text? so I can have a "processing" bmp? BUT WHY. I feel like this might be the same underlying problem...
       // why is this findable in other parts of my code, but not here?!?
       screen.fillScreen(ILI9340_BLACK);
       screen.setCursor(0, 0);
       screen.setTextColor(ILI9340_WHITE);  
       screen.setTextSize(2);
       screen.println(num);
       switch(sequenceNum)
       {
          case 2:
          {
             //screen.text("Enter the patient's current weight (in kg) and press SELECT: \n",0,0);
             screen.fillScreen(ILI9340_BLACK);
             screen.setCursor(0, 0);
             screen.setTextColor(ILI9340_WHITE);  
             screen.setTextSize(1);
             screen.println("Enter the patient's current weight (in kg) and press SELECT:");
             sequenceNum++;
             char key = kpd.getKey(); 
             currentSession.targetWeight = getNumber(key);
             break;
          }
          case 3:  
          {
             break;
          }
          default:
          {
             break;
          }
       }
   }
   else if (inSetup)
   {
       switch(n)
       {
          case 1:
          {
             bmpDraw("setup1.bmp", 0, 0);
             sequenceNum = 1;
             inSetup = false;
             inContent = true;
             break;
          }
          case 2:  
          {
             bmpDraw("prime1.bmp", 0, 0);
             inTail = true;
             inSetup = false;
             inContent = true;
             break;
          }
          case 3:
          {
             bmpDraw("connect1.bmp", 0, 0);
             inTail = true;
             inSetup = false;
             inContent = true;
             break;
          }
          case 4:
          {
             bmpDraw("settings1.bmp", 0, 0);
             inTail = true;
             inSetup = false;
             inContent = true;
             break;
          }
          case 5:
          {
             bmpDraw("launch1.bmp", 0, 0);
             inTail = true;
             inSetup = false;
             inContent = true;
             break;
          }
          case 6:
          {
             bmpDraw("end1.bmp", 0, 0);
             inTail = true;
             inSetup = false;
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
       inCommon = false;
       inContent = true;
       switch(n)
       {
          case 1:
          {
             bmpDraw("hypo1.bmp", 0, 0);
          }
          case 2:  
          {
             bmpDraw("bolus1.bmp", 0, 0);
             inTail = true;
          }
          case 3:
          {
             bmpDraw("clot1.bmp", 0, 0);
             inTail = true;
          }
          case 4:
          {
             bmpDraw("remove1.bmp", 0, 0);
             inTail = true;
          }
          case 5:
          {
             bmpDraw("fluid1.bmp", 0, 0);
             inTail = true;
          }
          case 6:
          {
             bmpDraw("lab1.bmp", 0, 0);
             inTail = true;
          }
          default:
          {
             break;
          }
      }
   }
}



