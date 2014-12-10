#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <QTRSensors.h>
#include <PID_v1.h>;

#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  2  // average 2 analog samples per sensor reading
#define EMITTER_PIN             QTR_NO_EMITTER_PIN

// sensors 0 through 7 are connected to analog inputs 0 through 7, respectively
QTRSensorsAnalog qtra((unsigned char[]) {8,9,10,11,12,13,14,15}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

//Define motor speed variables for PID
int leftSpeed, rightSpeed;
int baseSpeed = 1000;


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


//time it takes to make the turn needs to be changed
//testing is need to map everything at the speed we plan on running it at
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
}


void setup()
{  
  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield
   
  StepperFL.setMaxSpeed(5000.0);
  StepperFL.setAcceleration(1000.0);
  StepperFL.setSpeed(4000);
  
  StepperFR.setMaxSpeed(5000.0);
  StepperFR.setAcceleration(1000.0);
  StepperFR.setSpeed(-4000);
  
  StepperBR.setMaxSpeed(5000.0);
  StepperBR.setAcceleration(1000.0);
  StepperBR.setSpeed(-4000);
  
  StepperBL.setMaxSpeed(5000.0);
  StepperBL.setAcceleration(1000.0);
  StepperBL.setSpeed(4000); 
  
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
      StepperFL.runSpeed();
    StepperFR.runSpeed();
    StepperBL.runSpeed();
    StepperBR.runSpeed();
  
}

void loop(){
  
  // Sensor array (from viewpoint of chassis going in reverse where line follower is leading.)
  // Array: 7 6 5 4  3  2  1  0
  // Error: 4 3 2 1 -1 -2 -3 -4
  
  int totalError = 0;
  unsigned int position1 = qtra.readLine(sensorValues);
  
  if(sensorValues[0] < 40){
    
    totalError -= 4;
    
  }
  
    if(sensorValues[1] < 40){
    
    totalError -= 3;
    
  }
    if(sensorValues[2] < 40){
    
    totalError -= 2;
    
  }
  
      if(sensorValues[3] < 40){
    
    totalError -= 1;
    
  }
  
      if(sensorValues[4] < 40){
    
    totalError += 1;
    
  }
  
        if(sensorValues[5] < 40){
    
    totalError += 2;
    
  }
        if(sensorValues[6] < 40){
    
    totalError += 3;
    
  }
        if(sensorValues[7] < 40){
    
    totalError += 4;
    
  }
  
  
  if(totalError < 0){
    
    rightSpeed = abs(totalError*baseSpeed);
    leftSpeed = abs(totalError*baseSpeed/2);
    
      StepperFR.setSpeed(-rightSpeed);
  StepperFL.setSpeed(leftSpeed);
  StepperBR.setSpeed(-rightSpeed);
  StepperBL.setSpeed(leftSpeed);  
  }
  
  else if (totalError > 0){
    
    leftSpeed = abs(totalError*baseSpeed);
    rightSpeed = abs(totalError*baseSpeed/2);
    
      StepperFR.setSpeed(-rightSpeed);
  StepperFL.setSpeed(leftSpeed);
  StepperBR.setSpeed(-rightSpeed);
  StepperBL.setSpeed(leftSpeed);   
  }
  
      StepperFL.runSpeed();
    StepperFR.runSpeed();
    StepperBL.runSpeed();
    StepperBR.runSpeed();
  
  
}


