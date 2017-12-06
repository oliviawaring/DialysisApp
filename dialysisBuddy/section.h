/**** section.h ****/

struct Section
{
  Page first;
  int numPages;
  Section *subsections;
};
