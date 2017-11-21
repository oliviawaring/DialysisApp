/**** errors.h ****/

struct ErrorCode
{
  char color;
  int num;
};

struct Error
{
  ErrorCode errorCode;
  char *errorText;
};

Error errorDictionary[4] = {{{'G', 3}, "Check the setup"},
                            {{'G', 14}, "Snap and tap again"},
                            {{'R', 102}, "Oh no! Call 911!"},
                            {NULL, "End of error codes. Press back to return home."}};


