/**** buttons.h ****/

extern int pageNum;
extern int sectionNum;

void readButtons()
{
   int adc_key_in = analogRead(A0); // read the value from the sensor 
   
   // Our buttons centered at these values (when read with a voltmeter): 201, 406, 611, 818, 1023.
   // We add approx 50 to those values and check to see if we are close.
   if ((adc_key_in > 1200) || (adc_key_in < 151)) 
      return; // We make this the 1st option for speed reasons since it will be the most likely result
   if (adc_key_in < 251)   
   {
      Serial.print("help");
      getHelp(pageNum);
   }
   if (adc_key_in < 456)  
   {
      Serial.print("back");
   }
   if (adc_key_in < 661)
   {
      Serial.print("go");
   }
   if (adc_key_in < 868)
   {
      Serial.print("down");
      goNext(pageNum);
      showPage(); 
   }
   if (adc_key_in < 1073)
   {
      Serial.print("up");
      goBack(pageNum);
      if (pageNum > 0)
         showPage(); 
   }  
   Serial.print("none"); // when all others fail, return this...
}
