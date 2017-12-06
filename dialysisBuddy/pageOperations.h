/*****************************************************************/
/* pageOperations.h                                             
/* Author: MIT Dialysis Team, Fall 2017                                           
/* Encodes operations for moving between sections and pages   
/* ***************************************************************/

extern int sectionNum;
//extern int pageNum;
extern boolean inHomePage;
extern Keypad kpd;
extern Adafruit_ILI9340 screen;
//extern Picaso_Serial_4DLib Display;

const char *helpText = "Do you need help?"; 
const char *homeText = "Welcome to your in-home dialysis buddy! Select from among the following options by pressing the corresponding number on your keypad:\n1. Setup\n2. Treatment\n3. Error Codes"; 
const int NUM_SECTIONS = 6; // These are numbered in the way that makes sense to humans. We will have to compensate for array indexing in code. 
const int TREATMENT = 1;
const int SETUP = 2;
const int LAUNCH = 3;
const int END = 4;
const int COMMON = 5;
const int ERRORS = 6;
int inErrors = false;
char *currentText = "";
int currentPage = 0;
int currentSection = 0;
int currentSubSection = 0;
 
extern Session currentSession;
extern Error errorDictionary[4];

// The text associated with pages and sections get defined here. (This is not ideal... But reading in strings from an external text file is proving to be prohibitievely complicated. Stay tuned.)
/*Page setupPages[8] = {{"setup1.bmp", false, NULL},
                 {"setup2.bmp", false, NULL},
                 {"This is dialysis instruction 3. Cannulate.", false, NULL},
                 {"End of setup instructions. Press back to return home.", false, NULL}};

Page valuePages[4] = {{"Enter the patient's current weight (in kg) and press SELECT: \n", true, NULL},
                      {"Enter the patient's target weight (in kg) and press SELECT: \n", true, NULL},
                      {"Enter the patient's treatment time (in hours) and press SELECT: \n", true, NULL},
                      {"End of treatment value input. Press back to return home.", false, NULL}};

Page errorPages[2] = {{"Enter the error code (color and number) press SELECT: \n", true, NULL},
                      {"Error code not found. Please try again. The correct format of an error code is a color (A for green, B for red) followed by an integer.", true, NULL}};                      
*/

Page setup1 = {"setup1.bmp", false, NULL, 0};
Page setup2 = {"setup2.bmp", false, NULL, 0};
Page setup3 = {"setup3.bmp", false, NULL, 0};
Page setup4 = {"setup4.bmp", false, NULL, 0};
Page setup5 = {"setup5.bmp", false, NULL, 0};
Page setup6 = {"setup6.bmp", false, NULL, 0};
Page setup7 = {"setup7.bmp", false, NULL, 0};
Page setup8 = {"setup8.bmp", false, NULL, 0};

Page prime1 = {"prime1.bmp", false, NULL, 0};
Page connect1 = {"connect1.bmp", false, NULL, 0};
Page settings1 = {"settings1.bmp", false, NULL, 0};
Page launch1 = {"launch1.bmp", false, NULL, 0};
Page end1 = {"end1.bmp", false, NULL, 0};

Page hypo1 = {"hypo1.bmp", false, NULL, 0};
Page bolus1 = {"bolus1.bmp", false, NULL, 0};
Page clot1 = {"clot1.bmp", false, NULL, 0};
Page remove1 = {"remove1.bmp", false, NULL, 0};
Page fluid1 = {"fluid1.bmp", false, NULL, 0};
Page lab1 = {"lab1.bmp", false, NULL, 0};

Page treatment1 = {NULL, true, "Enter the patient's current weight (in kg) and press SELECT: \n", 0};
Page treatment2 = {NULL, true, "Enter the patient's target weight (in kg) and press SELECT: \n", 0};
Page treatment3 = {NULL, true, "Enter the patient's treatment time (in hours) and press SELECT: \n", 0};

Page msetup = {"msetup.bmp", false, NULL, 0};
Page mlaunch = {NULL, false, NULL, 0};
Page mend = {NULL, false, NULL, 0};
Page mcommon = {"mcommon.bmp", false, NULL, 0};
Page errorsearch = {NULL, true, "Enter the error code (color and number) press SELECT: \n", 0};
Page help = {NULL, false, "Do you need immediate assistance?\nCall your clinician or dial 911.", 0};

Section setup_subs[NUM_SECTIONS] = {{{setup1, setup2, setup3, setup4, setup5, setup6, setup7, setup8, NULL}, 0, NULL},
                       {{prime1, NULL}, 0, NULL},
                       {{connect1, NULL}, 0, NULL},
                       {{settings1, NULL}, 0, NULL}, 
                       {{launch1, NULL}, 0, NULL},
                       {{end1, NULL}, 0, NULL}};

Section common_subs[NUM_SECTIONS] = {{{hypo1, NULL}, 0, NULL},
                       {{bolus1, NULL}, 0, NULL},
                       {{clot1, NULL}, 0, NULL},
                       {{remove1, NULL}, 0, NULL}, 
                       {{fluid1, NULL}, 0, NULL},
                       {{lab1, NULL}, 0, NULL}};

Section sections[NUM_SECTIONS] = {{{treatment1, treatment2, treatment3, NULL}, 4, NULL},
                       {{msetup, NULL}, 0, setup_subs},
                       {{mlaunch, NULL}, 0, NULL},
                       {{mend, NULL}, 0, NULL}, 
                       {{mcommon, NULL}, 0, common_subs},
                       {{errorsearch, NULL}, 0, NULL}};

void goHome() 
{
  inHomePage = true;
  bmpDraw("main.bmp", 0, 0); 
}

Page* getCurrentPages()
{
  Page *pages;
  if (currentSection < NUM_SECTIONS) 
  {
     if (sections[currentSection].subsections == NULL)
     {
        pages = sections[currentSection].pages;
     }
     else
     {
        pages = sections[currentSection].subsections[currentSubSection].pages;
     }
  }
  return pages;
}

//need to put checks in place so you can't "NEXT" when you've reached the end of a section
//MAKE SURE YOU DON'T HAVE AN OFF BY ONE ERROR IN YOUR SECTION AND PAGE NUMBERS
void goNext() 
{  
  Page *pages = getCurrentPages();
  if (pages[currentPage + 1] != NULL)
     currentPage = currentPage + 1;
}

void goBack() 
{
  Page *pages = getCurrentPages();
  if ((currentPage == 0) && (currentSubSection > 0))
  {
     currentPage = 0;
     currentSubSection--; // THIS IS NOT RIGHT.
  }
  if (currentPage.previous != NULL)
     currentPage = currentPage.previous;
  else
     goHome();
}

void getHelp() 
{
  void fillScreen(uint16_t color);
  screen.print("Do you need help?");
}

void showPage()
{
  if (currentPage.fileName != NULL)
  {
     bmpDraw(currentPage.fileName, 0, 0);
  }

  else if (currentPage.prompt != NULL)
  {
    void fillScreen(uint16_t color);
     screen.print(currentPage.prompt);
  }
 
  /*Section thisSection = sections[sectionNum-1];
  Page thisPage = thisSection.pages[pageNum-1];
  if (inErrors)
  {
      Error thisErrorPage = errorDictionary[pageNum-1];
//      Display.putstr(thisErrorPage.errorText);
  }
  else 
  {  
//      Display.putstr(currentText); // print the relevant text
      currentText = "";
      bmpDraw("setup.bmp", 0, 0);
  }*/
  
  if (currentPage.acceptsInput) // if we're in a bmp this should NOT happen. Add a check. 
   {
      char key = kpd.getKey();
      Serial.print(sectionNum);
      switch(sectionNum)
      {
         case TREATMENT: 
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
  

}
                       
void goToSection(int section)
{
   pageNum = 1; // Reset the global page number to 1, since we're starting at the beginning of a section.
   if (section <= NUM_SECTIONS)
   {
      sectionNum = section;
      showPage();
   }
}


