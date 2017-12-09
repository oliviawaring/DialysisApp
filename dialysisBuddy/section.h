/**** section.h ****/

struct Subsection
{
  Page *pages;
  int numPages;
};

struct Section
{
  Page *pages;
  int numPages;
  Subsection *subsections;
};

