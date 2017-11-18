extern int NUM_PAGES;
extern Page pages[];
//extern Picaso_Serial_4DLib Display(&DisplaySerial);
const char *helpText = "Do you need help?"; 
const char *homeText = "Welcome to your in-home dialysis buddy!"; 
word BstateBack = BUTTON_UP ;
word BstateNext = BUTTON_UP ;
word BstateHelp = BUTTON_UP ;


void goNext(int &pageNum) 
{  
  //BstateNext = !BstateNext ;
  if ((pageNum == 0) || (pageNum != NUM_PAGES)) // this way of checking wheter we've reached the end is hacky
     pageNum++;
  Serial.print(pageNum);
}

void goBack(int &pageNum) 
{
  //BstateBack = !BstateBack ;
  if (pageNum != 0)
     pageNum--;
  Serial.print(pageNum);
}

void getHelp(Picaso_Serial_4DLib Display) 
{
  Display.gfx_Cls();   // clear screen
  Display.putstr(helpText) ;
  Display.gfx_Button(BstateBack, 0, 100, RED, BLACK, FONT3, 2, 2, "Dial Clinician") ;
}

void goHome(Picaso_Serial_4DLib Display) 
{
  Display.gfx_Cls();   // clear screen
  Display.putstr(homeText) ;
  Display.gfx_Button(BstateBack, 80, 100, RED, BLACK, FONT3, 2, 2, "Start") ;
}

void showPage(int pageNum, double val, Picaso_Serial_4DLib Display)
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
  Display.gfx_Button(BstateBack, 100, 300, RED, BLACK, FONT3, 1, 1, "Help") ;
  Display.gfx_Button(BstateNext, 20, 300, GRAY, WHITE, FONT3, 1, 1, "Back") ;
  Display.gfx_Button(BstateHelp, 180, 300, GRAY, WHITE, FONT3, 1, 1, "Next") ;
}