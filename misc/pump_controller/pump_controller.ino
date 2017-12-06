//initializations
int breakPin = A0; //use analog input 0 on arduino uno
int breakValue = 1023; //highest analog read
int motor = 11; //use PWM pin 11 on the arduino uno

//Parameters
int systolic_pressure = 30; //mmHg
int diastolic_pressure = 50; //mmHg
int bpm = 60; //heart rate in beats per minute

//Calculations:
//interval calculations
int duration = (bpm/(60*1000)); //miliseconds per beat
//pressure calculations
  //80 is a guess
int systolic = (systolic_pressure/80)*255; //duty cycle of motor for systolic pressure
int diastolic = (diastolic_pressure/80)*255; //duty cycle of motor for diastolic pressure

void setup() {

}

void loop() {
  while(breakValue>10){ //if the button is not depressed
    analogWrite(motor, systolic); //systolic pressure half the interval
    delay(duration/2);
    analogWrite(motor, diastolic); //diastolic pressure half the interval
    delay(duration/2);
    breakValue = analogRead(breakPin); //update breakValue every time it is valid
  }
}
