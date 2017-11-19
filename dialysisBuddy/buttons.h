#define btnNONE  0
#define btnHELP  1
#define btnBACK  2
#define btnGO    3
#define btnDOWN  4
#define btnUP    5

extern int pageNum;
extern int sectionNum;

void readButtons()
{
 //Serial.print("in buttons");
 //int adc_key_in  = 0;
 int adc_key_in = analogRead(A0);      // read the value from the sensor 
 // Serial.println(adc_key_in);
 // my buttons when read are centered at these valies: 140, 283, 425, 568, 710
 // we add approx 50 to those values and check to see if we are close
 if ((adc_key_in > 1200) || (adc_key_in < 151)) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.0 comment the other threshold and use the one below:

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
