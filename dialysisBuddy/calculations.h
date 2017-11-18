double calculateBMI(Page page1, Page page2)
{
  double weight = page1.inputVal;
  double height = page2.inputVal;
  double bmi = 703 *  weight / (height * height);
  return bmi;
}

double exponentiate(double x, int y) //this exists in the math library already... remove later
{
  double num = x;
  while (y > 1)
  {
     num = num * x;
     y--; 
  }
  return num;
}

void double2string(char *number, double n)
{
   char integers[6] = {'0','0','0','0','0','0'};
   char fractions[6] = {'0','0','0','0','0','0'};
   int i = 5; //related to that length... we'll work it out... CODE CODE CODE!
   double integral; // this is, numerically, the integer part
   double fractional = modf(n, &integral);
   int integralI = (int)integral; //this is TERRIBLE code. Please just let it work for now.
   while (integralI > 0)
   {
      integers[i] = ((int)fmod(integralI,10)) + '0';
      integralI=integralI/10;
      i--;
   }
   int k = 0;
   int q = 5 - i;
  // Serial.print("fractional\n");
  // Serial.print(fractional);
   while (q > 0)
   {
       fractional = fractional * 10;
       //Serial.print(floor(fractional));
       //Serial.print((int)floor(fractional));
       fractions[k] = ((int)floor(fractional)) + '0';
       fractional = fmod(fractional,1);
       k++;
       q--;
   }
   int j = 0; // the length of the final array
   while ((j < 6) && (i < 6))
   {
      number[j] = integers[i+1];
      j++;
      i++;
   }
   if (j != 6)
   {
      number[j-1] = '.';
      j++;
   }
   j--;
   int p = 0;
   while ((j < 6) && (p < 6)) 
   {
      number[j] = fractions[p];
      j++;
      p++;  
   }
   return number;
}