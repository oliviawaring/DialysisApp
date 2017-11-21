/**** section.h ****/

struct Section
{
  char *title;
  int numPages;
  Section *subsections;
  Page *pages;
};
