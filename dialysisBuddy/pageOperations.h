extern int NUM_PAGES;
extern Page pages[];
extern Picaso_Serial_4DLib Display;
const char *helpText = "Do you need help?"; 
const char *homeText = "Welcome to your in-home dialysis buddy! Select from among the following options by pressing the corresponding number on your keypad:\n1. Setup\n2. Treatment\n3. Error Codes"; 
word BstateBack = BUTTON_UP ;
word BstateNext = BUTTON_UP ;
word BstateHelp = BUTTON_UP ;

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

Page pages[6] = {{"This is dialysis instruction 1. Insert the cartridge.", false, NULL},
                 {"This is dialysis instruction 2. Snap and tap.", false, NULL},
                 {"This is dialysis instruction s3. Cannulate.", false, NULL},
                 {"Enter the patient's weight (in pounds) and press Enter (D): \n", true, NULL},
                 {"Enter the patient's height (in inches) and press Enter (D): \n", true, NULL},
                 {"The patient's body mass index (BMI) is: \n", false, NULL}};

Section sections[3] = {{"Setup", NULL, NULL}, 
                       {"Treatment", NULL, pages},
                       {"Error Codes", NULL, NULL}};

void showPage(int pageNum, double val)
{
  Display.gfx_Cls();   // clear screen
  Display.putstr(pages[pageNum].text) ;
  if (val != (double)NULL)
  {
     char answer[] = {'0','0','0','0','0','0'};
     double2string(answer, val);
     Serial.print(answer);
     Display.putstr(answer);
  }
//  Display.gfx_Button(BstateBack, 100, 300, RED, BLACK, FONT3, 1, 1, "Help") ;
//  Display.gfx_Button(BstateNext, 20, 300, GRAY, WHITE, FONT3, 1, 1, "Back") ;
//  Display.gfx_Button(BstateHelp, 180, 300, GRAY, WHITE, FONT3, 1, 1, "Next") ;
}
                       
void goToSection(int sectionNum)
{
   Serial.print("in go to section");
   Serial.print(sectionNum);
   switch (sectionNum) 
   {
      case 1:
      {
        //do stuff
        break;
      }
      case 2:
      {
        showPage(0, NULL);
        break;
      }
      case 3:
      {
        //do stuff
        break;
      }
      default:
      {
        //do stuff
        break;
      }
   }

}

void goNext(int &pageNum) 
{  
  //BstateNext = !BstateNext ;
  //if (pageNum == 0) //|| (pageNum != NUM_PAGES)) // this way of checking whether we've reached the end is hacky
  pageNum++;
  Serial.print(pageNum);
}

void goBack(int &pageNum) 
{
  //BstateBack = !BstateBack ;
  Serial.print("here");
  if (pageNum != 0)
     pageNum--;
  Serial.print(pageNum);
}

void getHelp(int &pageNum) 
{
  goNext(pageNum);
  Display.gfx_Cls();   // clear screen
  Display.putstr(helpText) ;
  Display.gfx_Button(BstateBack, 0, 100, RED, BLACK, FONT3, 2, 2, "Dial Clinician") ;
}

void goHome() 
{
  Display.gfx_Cls();   // clear screen
  Display.putstr(homeText) ;
  Display.gfx_Button(BstateBack, 80, 100, RED, BLACK, FONT3, 2, 2, "Start") ;
}


