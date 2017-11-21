/**** calculations.h ****/

double calculateBMI(double weight, double height)
{
  double bmi = 703 *  weight / (height * height);
  return bmi;
}

double calculateUltraFiltrationRate(double current, double target, double hours)
{
   double ufRate = (current - target) / hours;
   return ufRate;
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

// This is a ridiculous function that should not be necesary but we'll figure it out
void double2string(char *number, double n) 
{
   char integers[6] = {'0','0','0','0','0','0'};
   char fractions[6] = {'0','0','0','0','0','0'};
   int i = 5; // related to that length... we'll work it out... CODE CODE CODE!
   double integral; // this is, numerically, the integer part
   double fractional = modf(n, &integral);
   int integralI = (int)integral; // this is TERRIBLE code. Please just let it work for now.
   while (integralI > 0)
   {
      integers[i] = ((int)fmod(integralI,10)) + '0';
      integralI=integralI/10;
      i--;
   }
   int k = 0;
   int q = 5 - i;
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
