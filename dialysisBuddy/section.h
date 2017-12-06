/**** section.h ****/

struct Section
{
  Page *pages;
  int numPages;
  Section *subsections;
};
