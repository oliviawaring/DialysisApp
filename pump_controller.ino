int breakPin = A0;
int breakValue = 1023; //highest analog read
int motor = 11;

int systolic = 40;
int diastolic = 60;
int bpm = 60;
int duration = 1000/(bpm/60);

void setup() {

}

void loop() {
  for (breakValue>10){ //if the button is not depressed
    analogWrite(motor, systolic);
    delay(duration/2);
    analogWrite(motor, diastolic);
    delay(1000-duration/2);
    breakValue = analogRead(breakPin); //update breakValue
  }
}

