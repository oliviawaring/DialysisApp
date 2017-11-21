extern int sectionNum;
extern int pageNum;
extern boolean inHomePage;
extern Picaso_Serial_4DLib Display;
const char *helpText = "Do you need help?"; 
const char *homeText = "Welcome to your in-home dialysis buddy! Select from among the following options by pressing the corresponding number on your keypad:\n1. Setup\n2. Treatment\n3. Error Codes"; 
word BstateBack = BUTTON_UP ;
word BstateNext = BUTTON_UP ;
word BstateHelp = BUTTON_UP ;

const int NUM_SECTIONS = 3; //these are numbered in the way that makes sense to humans. We will have to compensate for array indexing in code. (same for page numbers?)

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

Page setupPages[4] = {{"This is dialysis instruction 1. Insert the cartridge.", false, NULL},
                 {"This is dialysis instruction 2. Snap and tap.", false, NULL},
                 {"This is dialysis instruction 3. Cannulate.", false, NULL},
                 {"End of setup instructions. Press back to return home.", false, NULL}};

Page valuePages[4] = {{"Enter the patient's current weight (in kg) and press SELECT: \n", true, NULL},
                      {"Enter the patient's target weight (in kg) and press SELECT: \n", true, NULL},
                      {"Enter the patient's treatment time (in hours) and press SELECT: \n", true, NULL},
                      {"End of treatment value input. Press back to return home.", false, NULL}};
  
Section sections[NUM_SECTIONS] = {{"Record Treatment Values", 4, NULL, valuePages}, 
                       {"Setup", 4, NULL, setupPages},
                       {"Error Codes", 2, NULL, NULL}};

//void showPage(int sectionNum, int pageNum, double val)
void showPage()
{
  Display.gfx_Cls();   // clear screen
  Serial.print("show page!\n");
  Serial.print(sectionNum);
  Serial.print(pageNum);
  Section thisSection = sections[sectionNum-1];
  Page thisPage = thisSection.pages[pageNum-1];
  Display.putstr(thisPage.text) ;
  /*
  if (thisPage.acceptsInput) // we're not going to need this anymore...
   {
      char key = kpd.getKey();
      thisPage.inputVal = getNumber(key, Display);
      goNext(pageNum);
      Serial.print(pageNum);
      if (pageNum == 5) //THIS IS MEGA HACKY, WE WILL NOT DO THIS IN THE ACTUAL PROGRAM
      {
         double bmi = calculateBMI(pages[3], pages[4]);
         Serial.print("calculating BMI");
         showPage(sectionNum, pageNum, bmi);
      }
      else
         showPage(sectionNum, pageNum, NULL);
  }
  if (val != (double)NULL)
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
   Serial.print("in go to section");
   Serial.print(section);
   pageNum = 1;
   if (section <= NUM_SECTIONS)
   {
      sectionNum = section;
      showPage();
   }
}

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
     goHome();
  }
}

void getHelp(int &pageNum) 
{
  goNext(pageNum);
  Display.gfx_Cls();   // clear screen
  Display.putstr(helpText) ;
  Display.gfx_Button(BstateBack, 0, 100, RED, BLACK, FONT3, 2, 2, "Dial Clinician") ;
}




