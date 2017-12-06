#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {' ','0','\n'}
};
byte rowPins[ROWS] = {2, 7, 6, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {3, 8, 5}; //connect to the column pinouts of the keypad
//same pin keypad to arduino, pin1 to 8
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String keyString = "";

void setup(){
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.print(key);
    keyString += key;
  }
}
