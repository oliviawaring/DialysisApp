//initializations
int motor = 3; //use PWM pin 11 on the arduino uno

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
    analogWrite(motor, 255); //systolic pressure half the interval
    delay(duration/2);
    analogWrite(motor, 255/2); //diastolic pressure half the interval
    delay(duration/2);
}
