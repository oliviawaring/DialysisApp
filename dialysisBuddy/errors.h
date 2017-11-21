/**** errors.h ****/

struct ErrorCode
{
  char color;
  int num;
  boolean complete;
};

struct Error
{
  ErrorCode errorCode;
  char *errorText;
  int page; // But this page has to be kept offset by one, since the "search" page counts as page 1... yikes
  // Is there a way we can encode that programmatically so that we avoid weird off by one errors?
};

const int NUM_ERRORS = 4; // we added one so we can have a buffer page (THIS FEELS SO MESSY)
Error errorDictionary[NUM_ERRORS] = {{{'G', 3, true}, "Check the setup", 2},
                            {{'G', 14, true}, "Snap and tap again", 3},
                            {{'R', 102, true}, "Oh no! Call 911!", 4},
                            {NULL, "End of error codes. Press back to return home.", 0}};


