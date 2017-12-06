/**** buttons.h ****/

extern int pageNum;
extern int sectionNum;

int readButtons()
{
   int adc_key_in = analogRead(A10); // read the value from the sensor 
   
   // Our buttons centered at these values (when read with a voltmeter): 1002, 833, 663, 496, 331, 165
   // We add approx 50 to those values and check to see if we are close.
   if ((adc_key_in > 1200) || (adc_key_in < 115)) 
      return; // We make this the 1st option for speed reasons since it will be the most likely result
   if (adc_key_in < 215)   
   {
      Serial.print("red - help"); 
      getHelp();
      return 1;
   }
   if (adc_key_in < 381)  
   {
      Serial.print("yellow - home");
      goHome();
      return 2;
   }
   if (adc_key_in < 546)
   {
      Serial.print("purple - back");
      return 3;
   }
   if (adc_key_in < 713)
   {
      Serial.print("green - next");
      goNext(pageNum);
      showPage(); 
      return 4;
   }
   if (adc_key_in < 883)
   {
      Serial.print("blue");
      goBack(pageNum);
      if (pageNum > 0)
         showPage(); 
         return 5;
   }  
   if (adc_key_in < 1052)
   {
      Serial.print("orange");
      goBack(pageNum);
      if (pageNum > 0)
         showPage(); 
         return 6;
   }  
   Serial.print("none"); // when all others fail, return this...
   return 0;
}
