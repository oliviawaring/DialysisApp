/**** buttons.h ****/

extern boolean inHomePage;
extern int currentPage;
extern int currentSection;
extern int currentSubsection;
boolean oneCycle = false;

int readButtons()
{
   int adc_key_in = analogRead(A10); // read the value from the sensor 
   
   // Our buttons centered at these values (when read with a voltmeter): 1002, 833, 663, 496, 331, 165
   // We add approx 50 to those values and check to see if we are close.
   if ((adc_key_in > 1200) || (adc_key_in < 115)) 
      return; // We make this the 1st option for speed reasons since it will be the most likely result
   oneCycle = false;
   if (adc_key_in < 215)   
   {
      Serial.print("red - help"); 
      if (inHomePage)
      {
         currentSection == 5;
        // showPage();
      }
      else 
      {
        getHelp();
      }
      return 6;
   }
   if (adc_key_in < 381)  
   {
      Serial.print("yellow - home");
      if (inHomePage)
      {
         currentSection == 4;
        // showPage();
      }
      else
      {
         goHome();
      }
      return 5;
   }
   if (adc_key_in < 546)
   {
      Serial.print("purple - back");
      if (inHomePage)
      {
         currentSection == 3;
        // showPage();
      }
      else
      {
        goBack();
      }
      return 4;
   }
   if (adc_key_in < 713)
   {
      Serial.print("green - next");
      if (inHomePage)
      {
         currentSection == 2;
         //showPage(); 
      }
      else
      {
        goNext();
      }
      return 3;
   }
   if (adc_key_in < 883)
   {
      Serial.print("blue");
      if (inHomePage)
      {
        currentSection == 1;
        //showPage(); 
      }
      return 2;
   }  
   if (adc_key_in < 1052)
   {
      Serial.print("orange");
      if (inHomePage)
      {
         currentSection == 0;
        // showPage(); 
      }
      return 1;
   }  
   Serial.print("none"); // when all others fail, return this...
   return 0;
}
