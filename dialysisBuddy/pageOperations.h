/*****************************************************************/
/* pageOperations.h                                             
/* Author: MIT Dialysis Team, Fall 2017                                           
/* Encodes operations for moving between sections and pages   
/* ***************************************************************/

extern int sectionNum;
//extern int pageNum;
extern boolean inHomePage;
extern boolean oneCycle;
boolean inSetup = false;
boolean inCommon = false;
boolean inTail = false;
boolean inTreatment = false;
boolean inContent = false;
boolean inErrors = false;
int sequenceNum = 0;
boolean inHelp = false;
extern Keypad kpd;
extern Adafruit_ILI9340 screen;
extern int currentPage;
extern int currentSection;
extern int currentSubsection;
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
char *currentText = "";

 
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

/*

// A null Page
Page nullPage = {"", false, NULL, 0};
Page nullPages[2] = {nullPage, nullPage};
Subsection nullSubsection = {nullPages, 0};
Subsection nullSubsections[2] = {nullSubsection, nullSubsection};
Section nullSection = {nullPages, 0, nullSubsections};

// The pages
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

Page a1[9] = {setup1, setup2, setup3, setup4, setup5, setup6, setup7, setup8, nullPage};
Page a2[2] = {prime1, nullPage};
Page a3[2] = {connect1, nullPage};
Page a4[2] = {settings1, nullPage};
Page a5[2] = {launch1, nullPage};
Page a6[2] = {end1, nullPage};

Subsection setup_subs[NUM_SECTIONS] = {{a1, 8},
                       {a2, 1},
                       {a3, 1},
                       {a4, 1}, 
                       {a5, 1},
                       {a6, 1}};

Page b1[2] = {hypo1, nullPage};
Page b2[2] = {bolus1, nullPage};
Page b3[2] = {clot1, nullPage};
Page b4[2] = {remove1, nullPage};
Page b5[2] = {fluid1, nullPage};
Page b6[2] = {lab1, nullPage};

Subsection common_subs[NUM_SECTIONS] = {{b1, 1},
                       {b2, 1},
                       {b3, 1},
                       {b4, 1}, 
                       {b5, 1},
                       {b6, 1}};

Page p1[4] = {treatment1, treatment2, treatment3, nullPage};
Page p2[2] = {msetup, nullPage};
Page p3[2] = {mlaunch, nullPage};
Page p4[2] = {mend, nullPage};
Page p5[2] = {mcommon, nullPage};
Page p6[2] = {errorsearch, nullPage};

// Main sections
Section sections[NUM_SECTIONS] = {{p1, 3, nullSubsections},
                       {p2, 1, setup_subs},
                       {p3, 1, nullSubsections},
                       {p4, 1, nullSubsections}, 
                       {p5, 1, common_subs},
                       {p6, 1, nullSubsections}};
*/

void processKeystroke(int n)
{
  return; 
}


void goHome() 
{
  inHomePage = true;
  bmpDraw("setup1.bmp", 0, 0); 
}

/*Page* getCurrentPages()
{
  Page *pages;
  if (currentSection < NUM_SECTIONS) 
  {
     if (sections[currentSection].subsections == NULL)
     {
        Serial.print("heyy");
        *pages = *sections[currentSection].pages;
        Serial.print(pages[currentPage].fileName);
     }
     else
     {
        Serial.print("yoyoy");
        *pages = *sections[currentSection].subsections[currentSubsection].pages;
     }
  }
  Serial.print(pages[currentPage].fileName);
  return pages;
}*/

//need to put checks in place so you can't "NEXT" when you've reached the end of a section
//MAKE SURE YOU DON'T HAVE AN OFF BY ONE ERROR IN YOUR SECTION AND PAGE NUMBERS
void goNext() 
{  /*
  Page *pages = getCurrentPages();
  if (pages[currentPage + 1].fileName != nullPage.fileName)
     currentPage = currentPage + 1;*/
}

void goBack() 
{
  /*
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
     */
  return;
}

void getHelp() 
{
  void fillScreen(uint16_t color);
  screen.print("Do you need help?");
}

/*
void showPage()
{
  //Page *pages = getCurrentPages();
  Serial.print(currentSection);
  Serial.print("helloooo\n");
  Serial.print(currentPage);
 // Serial.print(pages[currentPage].fileName);
  if ((sections[currentSection].subsections)->numPages == nullSubsection.numPages)
     {
        Serial.print("heyy");
        Serial.print((sections[currentSection].pages)[currentPage].fileName);
        bmpDraw((sections[currentSection].pages)[currentPage].fileName, 0, 0);
       // Serial.print(pages[currentPage].fileName);
     }
     else
     {
        Serial.print("yoyoy");
        bmpDraw(((sections[currentSection].subsections)[currentSubsection].pages)->fileName, 0, 0);
       // *pages = *sections[currentSection].subsections[currentSubSection].pages;
     }

     
 // if (pages[currentPage].fileName != nullPage.fileName)
 // {
 //    bmpDraw(pages[currentPage].fileName, 0, 0);
 // }

  /*else if (pages[currentPage].prompt != nullPage.prompt)
  {
    void fillScreen(uint16_t color);
     screen.print(pages[currentPage].prompt);
  }*/
 
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
  
 /* if (pages[currentPage].acceptsInput) // if we're in a bmp this should NOT happen. Add a check. 
   {
      char key = kpd.getKey();
      Serial.print(sectionNum);
      switch(sectionNum)
      {
         case TREATMENT: 
         {
            switch (currentPage)
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
               currentPage = 2;
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
                  currentPage = thisError.page; // But going back should bring you back to the search page, NOT the previous error in the dictionary
                  inErrors = true;
                  showPage();
                  break;
               }
            }
            break;
         }
      }*/
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
  //}
  /*if (val != (double)NULL)
  {
     char answer[] = {'0','0','0','0','0','0'};
     double2string(answer, val);
     Serial.print(answer);
     Display.putstr(answer);
  }
  
}*/
                       
/*void goToSection(int section)
{
   currentPage = 1; // Reset the global page number to 1, since we're starting at the beginning of a section. Not 
   if (section <= NUM_SECTIONS)
   {
      sectionNum = section;
      showPage();
   }
}*/


