#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <QTRSensors.h>
#include <PID_v1.h>;

#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  2  // average 2 analog samples per sensor reading
#define EMITTER_PIN             QTR_NO_EMITTER_PIN  // emitter is controlled by digital pin 2

// sensors 0 through 7 are connected to analog inputs 0 through 7, respectively
QTRSensorsAnalog qtra((unsigned char[]) {8,9,10,11,12,13,14,15}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];


//Define PID variables
double pidSetpoint, pidInput, pidOutput;

//Define motor speed variables for PID
int leftSideSpeed, rightSideSpeed;

//Give the PID pointers to the variables along with the current constants
PID myPID(&pidInput, &pidOutput, &pidSetpoint,20,0,0, DIRECT);



Adafruit_MotorShield AFMSbot(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers

// Connect two steppers with 200 steps per revolution (1.8 degre
// to the top shield
Adafruit_StepperMotor *stepperfr = AFMStop.getStepper(400, 1); //Top M1 and M2
Adafruit_StepperMotor *stepperfl = AFMStop.getStepper(400, 2); //Top M3 and M4

// Connect one stepper with 200 steps per revolution (1.8 degree)
// to the bottom shield
Adafruit_StepperMotor *stepperbr = AFMSbot.getStepper(400, 1); //Bottom M1 and M2
Adafruit_StepperMotor *stepperbl = AFMSbot.getStepper(400, 2); //Bottom M3 and M4
unsigned int timer;


void forwardstep1() {  
  stepperfr->onestep(FORWARD, DOUBLE);
}
void backwardstep1() {  
  stepperfr->onestep(BACKWARD, DOUBLE);
}
// wrappers for the second motor!
void forwardstep2() {  
  stepperfl->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {  
  stepperfl->onestep(BACKWARD, DOUBLE);
}
// wrappers for the third motor!
void forwardstep3() {  
  stepperbr->onestep(FORWARD, DOUBLE);
}
void backwardstep3() {  
  stepperbr->onestep(BACKWARD, DOUBLE);
}
void forwardstep4() {  
  stepperbl->onestep(FORWARD, DOUBLE);
}
void backwardstep4() {  
  stepperbl->onestep(BACKWARD, DOUBLE);
}



AccelStepper StepperFR(forwardstep1, backwardstep1);
AccelStepper StepperFL(forwardstep2, backwardstep2);
AccelStepper StepperBR(forwardstep3, backwardstep3);
AccelStepper StepperBL(forwardstep4, backwardstep4);



void rturn(){
  timer = millis();
  while ((millis() - timer) < 2000){
    StepperFL.runSpeed();
    StepperFR.runSpeed();
    StepperBL.runSpeed();
    StepperBR.runSpeed();
  }
  StepperFR.setSpeed(-2000);
  StepperFL.setSpeed(-2000);
  StepperBR.setSpeed(-2000);
  StepperBL.setSpeed(-2000);
  timer = millis();
  while ((millis() - timer) < 2000){
    StepperFL.runSpeed();
    StepperFR.runSpeed();
    StepperBL.runSpeed();
    StepperBR.runSpeed();
  }
  reverse();
}

void lturn(){
  timer = millis();
  while ((millis() - timer) < 2000){
    StepperFL.runSpeed();
    StepperFR.runSpeed();
    StepperBL.runSpeed();
    StepperBR.runSpeed();
  }
  StepperFR.setSpeed(1000);
  StepperFL.setSpeed(1000);
  StepperBR.setSpeed(1000);
  StepperBL.setSpeed(1000);
  
  timer = millis();
  while ((millis() - timer) < 2000){
    StepperFL.runSpeed();
    StepperFR.runSpeed();
    StepperBL.runSpeed();
    StepperBR.runSpeed();
  } 
  reverse();
}
void turnAround(){
  StepperFR.setSpeed(1000);
  StepperFL.setSpeed(1000);
  StepperBR.setSpeed(1000);
  StepperBL.setSpeed(1000);
  
  timer = millis();
  while ((millis() - timer) < 4000){
    StepperFL.runSpeed();
    StepperFR.runSpeed();
    StepperBL.runSpeed();
    StepperBR.runSpeed();
  } 
  reverse();
}

void forward(){
 StepperFR.setSpeed(1000);
 StepperFL.setSpeed(-1000);
 StepperBR.setSpeed(1000);
 StepperBL.setSpeed(-1000); 
}

void reverse(){
 StepperFR.setSpeed(-1000);
 StepperFL.setSpeed(1000);
 StepperBR.setSpeed(-1000);
 StepperBL.setSpeed(1000);  
}

void strafe(float inc){
  if(inc < 0){
      StepperFR.setSpeed(-1000);
      StepperFL.setSpeed(1000);
      StepperBR.setSpeed(1000);
      StepperBL.setSpeed(-1000);
  }else{
    
      StepperFR.setSpeed(1000);
      StepperFL.setSpeed(-1000);
      StepperBR.setSpeed(-1000);
      StepperBL.setSpeed(1000);
  }
 //inc to seconds  
}

void setup()
{  
  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield
  
  leftSideSpeed = 4000;
  rightSideSpeed = 4000;
   
  StepperFL.setMaxSpeed(5000.0);
  StepperFL.setAcceleration(1000.0);
  StepperFL.setSpeed(1000);
  
  StepperFR.setMaxSpeed(5000.0);
  StepperFR.setAcceleration(1000.0);
  StepperFR.setSpeed(-1000);
  
  StepperBR.setMaxSpeed(5000.0);
  StepperBR.setAcceleration(1000.0);
  StepperBR.setSpeed(-1000);
  
  StepperBL.setMaxSpeed(5000.0);
  StepperBL.setAcceleration(1000.0);
  StepperBL.setSpeed(1000); 
  
  //Sensor array start/////////////////////////////
  /////////////////////////////////////////////////
    pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  
  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  
  //Sensor Array Finish////////////////////////
  /////////////////////////////////////////////
  
  //PID "init"//
    //init PID variables
pidSetpoint = 3000;
pidInput = qtra.readLine(sensorValues);

//start up PID
myPID.SetMode(AUTOMATIC);

//End PID init//

    StepperFL.runSpeed();
    StepperFR.runSpeed();
    StepperBL.runSpeed();
    StepperBR.runSpeed();


}


void loop(){
  
    int position = qtra.readLine(sensorValues);
    pidInput = position;
    myPID.Compute();
  
 int leftSS = map(leftSideSpeed, 0, 5000, 1000, 4000);
 int rightSS = map(rightSideSpeed, 0, 5000, 1000, 4000);
   
    if(position < pidSetpoint){

                 rightSS = rightSideSpeed + pidOutput;
           leftSS = 0 + rightSideSpeed/2;

           StepperFR.setSpeed(-rightSideSpeed);
           StepperFL.setSpeed(leftSideSpeed);
           StepperBR.setSpeed(-rightSideSpeed);
           StepperBL.setSpeed(leftSideSpeed);


      
    }
    
    else if(position > pidSetpoint){
                
           leftSS = leftSideSpeed + pidOutput;
           rightSS = leftSideSpeed/2;
           StepperFR.setSpeed(-rightSideSpeed);
           StepperFL.setSpeed(leftSideSpeed);
           StepperBR.setSpeed(-rightSideSpeed);
           StepperBL.setSpeed(leftSideSpeed);
            
    }
    Serial.print(leftSideSpeed);
    Serial.print("\t");
    Serial.print(rightSideSpeed);
    Serial.println();
    
            
     
    StepperFL.runSpeed();
    StepperFR.runSpeed();
    StepperBL.runSpeed();
    StepperBR.runSpeed();
}
