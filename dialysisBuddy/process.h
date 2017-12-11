// using pointers in C is too risky, let's try a WHOLE new approach

extern Keypad kpd;
extern Adafruit_ILI9340 screen;
extern SoftwareSerial lcdScreen;
extern Session currentSession;
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
                    bmpDraw("msetup.bmp", 0, 0);
                    inTail = false;
                    inContent = false;
                    inSetup = true;
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
                   bmpDraw("main.bmp", 0, 0);
                   inTail = false;
                   inHomePage = true;
                   inContent = false;
                }
                break;
            }
            case 5:
            {
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
                         bmpDraw("tweight.bmp", 0, 0); // WHY is this not displaying. I think I keep bumping up against variations of the same problem... Maybe it is a memory issue?
                         char key = kpd.getKey(); 
                         lcdScreen.write(12);
                         currentSession.targetWeight = getNumber(key);
                         sequenceNum++;
                         break;
                     }
                     case 2:
                     {
                         bmpDraw("time.bmp", 0, 0);
                         char key = kpd.getKey(); 
                         lcdScreen.write(12);
                         currentSession.treatmentTime = getNumber(key);
                         sequenceNum++;
                         break;
                     }
                     case 3:
                     {
                         bmpDraw("disp_uf.bmp", 0, 0);
                         lcdScreen.write(12);
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
               if (inSetup)
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
                     // if we hit case 8 there's something wrong because this should have been flagged in the tail bit
                  }
               }
               else if (inTreatment)
               {
                  switch(sequenceNum)
                  {
                     case 1:
                     {
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
             bmpDraw("cweight.bmp", 0, 0);
             char key = kpd.getKey(); 
             lcdScreen.write(12);
             currentSession.currentWeight = getNumber(key);
             Serial.print("after\n");
             Serial.print(currentSession.currentWeight);
             sequenceNum = 1; 
             inHomePage = false; 
             inContent = true;
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
   /*else if (inTreatment)
   {
   // no... how am I handling the next button?
   // we should probably draw this in somehow. I'll save it for later. 
       Serial.print("ouch\n");
      // bmpDraw("main.bmp", 0, 0); // might be the answer... have to re-display a bmp before text? so I can have a "processing" bmp? BUT WHY. I feel like this might be the same underlying problem...
       // why is this findable in other parts of my code, but not here?!?
       //screen.fillScreen(ILI9340_BLACK);
      // screen.setCursor(0, 0);
      // screen.setTextColor(ILI9340_WHITE);  
      // screen.setTextSize(2);
      // screen.println(num);
       Serial.print(sequenceNum);
       if (sequenceNum == 2)
       {
             Serial.print("am I here?");
             screen.fillScreen(ILI9340_BLACK);
             screen.setCursor(0, 0);
             screen.setTextColor(ILI9340_WHITE);  
             screen.setTextSize(1);
             screen.println("Enter the patient's target weight (in kg) and press SELECT:");
             char key = kpd.getKey(); 
             lcdScreen.write(12);
             currentSession.targetWeight = getNumber(key);
             sequenceNum = 3;
            // break;
      }
       /*   case 3:  
          {  
             screen.fillScreen(ILI9340_BLACK);
             screen.setCursor(0, 0);
             screen.setTextColor(ILI9340_WHITE);  
             screen.setTextSize(1);
             screen.println("Enter the patient's treatment time (in hours) and press SELECT: \n:");
             char key = kpd.getKey(); 
             lcdScreen.write(12);
             currentSession.treatmentTime = getNumber(key);
             sequenceNum = 4;
             break;
          }
          default:
          {
             break;
          }
       }*/
   //}
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
}

// Pretty much everything is messed up right now, I need to draw a chart and tackle this again later. 
// Yeah I legitly ruined EVERYTHING. 
