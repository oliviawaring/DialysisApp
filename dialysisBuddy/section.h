struct Section
{
  char *title;
  Section *subsections;
  Page *pages;
  //boolean acceptsInput;
  //double inputVal; // yup, cuz the way we've designed it there's only one per page, yeah?
};
