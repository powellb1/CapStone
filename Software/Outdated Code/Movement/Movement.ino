


//WARNING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//VALUES FOR MOVEMENT MIGHT BE BACKWARDS.
//BECAREFUL WHEN TESTING
//HAS NOT BEEN TESTED YET
#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

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
 //inc to seconds  
}

void setup()
{  
  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield
   
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
}

void loop()
{
    // Change direction at the limits
    // add in line following for the turns just call the functions
    // rturn for right turn
    // lturn for left turn
    // strafe - goes left and + goes right
    // forwards is where the challenge attachments are located
    // backwards is where the line follower is located
    // turnAround does a 180 to the left
    /*
          (Challenge attachments)
        ----------------    
          ----------------
    FL    |              |  FR
          |              |
          |              |
          |              |
          |              |
          |              |
          |              |
    BL    |              |  BR 
          ----------------
                ---
            (Linesenors) 
    */
    delay(3000);
    StepperFL.runSpeed();
    StepperFR.runSpeed();
    StepperBL.runSpeed();
    StepperBR.runSpeed();
    forward();
   
}

