/**** page.h ****/

struct Page
{
  char *text;
  boolean acceptsInput;
  double inputVal; // The jury is still out as to whether these last two fields will be necessary; depends on the ultimate design of our program
};

