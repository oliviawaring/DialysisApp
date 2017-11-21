/*****************************************************************/
/* pageOperations.h                                             
/* Author: MIT Dialysis Team, Fall 2017                                           
/* Encodes operations for moving between sections and pages   
/* ***************************************************************/

extern int sectionNum;
extern int pageNum;
extern boolean inHomePage;
extern Keypad kpd;
extern Picaso_Serial_4DLib Display;

const char *helpText = "Do you need help?"; 
const char *homeText = "Welcome to your in-home dialysis buddy! Select from among the following options by pressing the corresponding number on your keypad:\n1. Setup\n2. Treatment\n3. Error Codes"; 
const int NUM_SECTIONS = 3; // These are numbered in the way that makes sense to humans. We will have to compensate for array indexing in code. 
const int SETUP = 1;
const int VALUES = 2;
const int ERRORS = 3;
int inErrors = false;

extern Session currentSession;
extern Error errorDictionary[4];

// The text associated with pages and sections get defined here. (This is not ideal... But reading in strings from an external text file is proving to be prohibitievely complicated. Stay tuned.)
Page setupPages[4] = {{"This is dialysis instruction 1. Insert the cartridge.", false, NULL},
                 {"This is dialysis instruction 2. Snap and tap.", false, NULL},
                 {"This is dialysis instruction 3. Cannulate.", false, NULL},
                 {"End of setup instructions. Press back to return home.", false, NULL}};

Page valuePages[4] = {{"Enter the patient's current weight (in kg) and press SELECT: \n", true, NULL},
                      {"Enter the patient's target weight (in kg) and press SELECT: \n", true, NULL},
                      {"Enter the patient's treatment time (in hours) and press SELECT: \n", true, NULL},
                      {"End of treatment value input. Press back to return home.", false, NULL}};

Page errorPages[2] = {{"Enter the error code (color and number) press SELECT: \n", true, NULL},
                      {"Error code not found. Please try again. The correct format of an error code is a color (A for green, B for red) followed by an integer.", true, NULL}};                      
  
Section sections[NUM_SECTIONS] = {{"Record Treatment Values", 4, NULL, valuePages}, 
                       {"Setup", 4, NULL, setupPages},
                       {"Error Codes", 2, NULL, errorPages}};

void goHome() 
{
  Display.gfx_Cls();   // clear screen
  Display.putstr(homeText) ;
  pageNum = 0;
  inHomePage = true;
}

//need to put checks in place so you can't "NEXT" when you've reached the end of a section
//MAKE SURE YOU DON'T HAVE AN OFF BY ONE ERROR IN YOUR SECTION AND PAGE NUMBERS
void goNext(int &pageNum) 
{  
  if (pageNum != sections[sectionNum-1].numPages)
     pageNum++;
}

void goBack(int &pageNum) 
{
  if (pageNum > 1)
     pageNum--;
  else
  {
     goHome(); // If you back too far out of a section, you should get back to the home screen.
  }
}

void getHelp(int &pageNum) 
{
  goNext(pageNum);
  Display.gfx_Cls();   // clear screen
  Display.putstr(helpText) ;
  //Display.gfx_Button(BstateBack, 0, 100, RED, BLACK, FONT3, 2, 2, "Dial Clinician") ;
}

void showPage()
{
  Serial.print("in show page\n");
  Display.gfx_Cls();   // clear screen
  Serial.print(sectionNum);
  Serial.print(pageNum);
  Section thisSection = sections[sectionNum-1];
  Page thisPage = thisSection.pages[pageNum-1];
  if (inErrors)
  {
      Error thisErrorPage = errorDictionary[pageNum-1];
      Display.putstr(thisErrorPage.errorText);
  }
  else 
  {  
      Display.putstr(thisPage.text); // print the relevant text
  }
  
  if (thisPage.acceptsInput)
   {
      char key = kpd.getKey();
      // wait a sec. I'm concerned. this is DEFINITELY not going to work. What am I doing here. This is only one key, yo. 
      // but some variation on this theme did work before.... 
      Serial.print(sectionNum);
      switch(sectionNum)
      {
         case SETUP: 
            //woah! why are you here? There shouldn't be any inputs in this section!  
            break;
         case VALUES:
         {
            switch (pageNum)
            {
               case 1:
                  currentSession.currentWeight = getNumber(key);
                  break;
               case 2:
                  currentSession.targetWeight = getNumber(key);
                  break;
               case 3:
                  currentSession.treatmentTime = getNumber(key);
                  break;
              default: 
                  if (currentSession.treatmentTime != 0)
                     calculateUltraFiltrationRate();
                  break;
            } 
         }
         case ERRORS: 
         {
            Serial.print("in errors!\n");
            ErrorCode errorCode = getErrorCode(key);
            if (!errorCode.complete)
            {
               pageNum = 2;
               showPage();
               break;
            }
            // we need some sort of routine to extract the color and the number...
            char color = errorCode.color;
            int num = errorCode.num;
            int i;
            for (i = 0; i < NUM_ERRORS; i++)
            {
               Serial.print("hi we're happy");
               Error thisError = errorDictionary[i];
               ErrorCode thisCode = thisError.errorCode;
               if ((thisCode.color == color) && (thisCode.num == num))
               {
                  pageNum = thisError.page; // But going back should bring you back to the search page, NOT the previous error in the dictionary
                  inErrors = true;
                  showPage();
                  break;
               }
            }
            break;
         }
      }
      /*goNext(pageNum);
      Serial.print(pageNum);
      if (pageNum == 5) //THIS IS MEGA HACKY, WE WILL NOT DO THIS IN THE ACTUAL PROGRAM
      {
         double bmi = calculateBMI(pages[3], pages[4]);
         Serial.print("calculating BMI");
         showPage(sectionNum, pageNum, bmi);
      }
      else
         showPage(sectionNum, pageNum, NULL);*/
  }
  /*if (val != (double)NULL)
  {
     char answer[] = {'0','0','0','0','0','0'};
     double2string(answer, val);
     Serial.print(answer);
     Display.putstr(answer);
  }*/
  
//  Display.gfx_Button(BstateBack, 100, 300, RED, BLACK, FONT3, 1, 1, "Help") ;
//  Display.gfx_Button(BstateNext, 20, 300, GRAY, WHITE, FONT3, 1, 1, "Back") ;
//  Display.gfx_Button(BstateHelp, 180, 300, GRAY, WHITE, FONT3, 1, 1, "Next") ;
}
                       
void goToSection(int section)
{
   pageNum = 1; // Reset the global page number to 1, since we're starting at the beginning of a section.
   Serial.print(section);
   if (section <= NUM_SECTIONS)
   {
      sectionNum = section;
      Serial.print("\ntesting");
      Serial.print(sectionNum);
      Serial.print("\n");
      showPage();
   }
}


/*
void makePages()
{
    FILE *file;
    char *myBuffer;
    unsigned long fileLen;

    file = fopen("dialysisInstructions.txt", "r");
    if (!file) 
    {
       fprintf(stderr, "Can't open input file\n");
       return;
    }

    //Get file length
    fseek(file, 0, SEEK_END);
    fileLen = ftell(file);
    fseek(file, 0, SEEK_SET);

    //Allocate memory
    myBuffer = (char *)malloc(fileLen+1);
    if (!myBuffer)
    {
       fprintf(stderr, "Memory error!");
                                fclose(file);
       return;
    }

    //Read file contents into buffer
    fread(myBuffer, fileLen, 1, file);
    fclose(file);

    for (int i=0; i < fileLen; i++)
    {
       //while(((char *)myBuffer)[i])
       Serial.print(((char *)myBuffer)[i]);
    }

    //Do what ever with buffer

    free(myBuffer);    
   //fgets(line, 72)
 //   while (fgets(line, 72, ifp) != NULL)
 //   {
 //      if (line)
 //   }
}*/


