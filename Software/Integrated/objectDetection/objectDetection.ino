#include <NewPing.h>
#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

#define etchStrafeFromCenter 3.25
#define rubixStrafeFromCenter -2.5
#define simonStrafeFromCenter -5.25

int challengeSeen;

/*
  ObjectDetection
 
 This module will wait for a serial communication from the Pi and turn on
 a corresponding LED.
 
 */

//Pin 13 is for the Etch
//Pin 11 is for Rubiks
#define MAX_DISTANCE 200
int pinI1=8;//define I1 interface
int pinI2=11;//define I2 interface 
int speedpinA=9;//enable motor A
int speedpinB=140;//enable motor B
int spead =255;//define the spead of motor
int etch = 28;
int rubiks = 30;
int incomingByte = 0;
int pot=22;
int trg=23;
int echo=22;
int LED = 32;
boolean camOn=true;
boolean completed = false;
boolean inRange = false;
boolean exitArea = false;


Adafruit_MotorShield AFMSbot(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers

// Connect two steppers with 400 steps per revolution (1.8 degre
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



NewPing sonar(trg,echo,MAX_DISTANCE);

void setup(){
  //input and output pins
  pinMode(pinI1,OUTPUT);
  pinMode(pinI2,OUTPUT);
  pinMode(speedpinA,OUTPUT);
  pinMode(speedpinB,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(etch,OUTPUT);
  pinMode(rubiks,OUTPUT);
  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield

  StepperFL.setMaxSpeed(5000.0);
  StepperFL.setAcceleration(1000.0);
  StepperFL.setSpeed(1000);

  StepperFR.setMaxSpeed(5000.0);
  StepperFR.setAcceleration(1000.0);
  StepperFR.setSpeed(1000);

  StepperBR.setMaxSpeed(5000.0);
  StepperBR.setAcceleration(1000.0);
  StepperBR.setSpeed(-1000);

  StepperBL.setMaxSpeed(5000.0);
  StepperBL.setAcceleration(1000.0);
  StepperBL.setSpeed(-1000); 

  Serial.begin(9600);
  //Serial.println("set up");


}

void loop()
{



  delay(50);

  float uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  //Serial.println((float)(uS/US_ROUNDTRIP_CM));
  if(!completed) //this completed flag would be changed to turned around or something like that
  {
    approach(uS);

  }

  if(completed && exitArea)
  {
    botReverse();
    timer = millis();
    while ((millis() - timer) < 800){
      StepperFL.runSpeed();
      StepperFR.runSpeed();
      StepperBL.runSpeed();
      StepperBR.runSpeed();
    }
    switch(challengeSeen)
    {
    case 1:
      strafe(-etchStrafeFromCenter);
      break;
    case 2:
      strafe(-rubixStrafeFromCenter);
      break;
    case 3:
      strafe(-simonStrafeFromCenter);
      break;
    }
    exitArea=false;
  }

}

//called when approaching object.
void approach(float uS)
{
  if(((float)(uS/US_ROUNDTRIP_CM)>=4.1 && (float)(uS/US_ROUNDTRIP_CM)<=4.3) && !inRange)
  {
    inRange = true; 
    camForward();
    Serial.write('C');
  }
  else
  {
    botForward();
    StepperFL.runSpeed();
    StepperFR.runSpeed();
    StepperBL.runSpeed();
    StepperBR.runSpeed();
  }

  while(inRange && !completed)
  {
    while(Serial.available()>0)
    {
      incomingByte = Serial.read();
      if(incomingByte=='X')
      {
        digitalWrite(LED,HIGH);
        shuffle();
        digitalWrite(LED,LOW);
      }
      else if(incomingByte>48 && incomingByte<52)
      {
        whatObj(incomingByte);
      }

      if(completed)
      {
        botForward();
        timer = millis();
        while ((millis() - timer) < 600){
          StepperFL.runSpeed();
          StepperFR.runSpeed();
          StepperBL.runSpeed();
          StepperBR.runSpeed();
        }
        camBackward();
        Serial.write('C');
        delay(2000);
      }
    }

  }

}

//used to determine where we're moving to. Need to put in values as to how far to move
//laterally
void whatObj(int incomingByte)
{
  incomingByte = incomingByte-48;
  switch(incomingByte)
  {
  case 1:
    {
      strafe(etchStrafeFromCenter);
      challengeSeen = 1;
      Serial.write('E');
      break;
    } 
  case 2:
    {
      strafe(rubixStrafeFromCenter);
      challengeSeen = 2;
      Serial.write('R');
      break;
    } 
  case 3:
    {
      strafe(simonStrafeFromCenter);
      challengeSeen = 3;
      Serial.write('S');
      break;
    } 
  default :
    {
      digitalWrite(etch,HIGH);
      digitalWrite(rubiks,HIGH);
      delay(5000);
      digitalWrite(etch,LOW);
      digitalWrite(rubiks,LOW);
      Serial.write('K');
      delay(1000);
    }
  }
  completed = true;
  exitArea = true;

}

void camForward()
{
  analogWrite(speedpinA,spead);//input a simulation value to set the speed
  analogWrite(speedpinB,spead);
  digitalWrite(pinI2,LOW);//turn DC Motor A move anticlockwise
  digitalWrite(pinI1,HIGH);
}
void camBackward()//
{
  analogWrite(speedpinA,spead);//input a simulation value to set the speed
  analogWrite(speedpinB,spead);
  digitalWrite(pinI2,HIGH);//turn DC Motor A move clockwise
  digitalWrite(pinI1,LOW);
}

void shuffle()
{
  float inc = Serial.parseFloat();
  strafe(inc);
  Serial.write('M');
  digitalWrite(etch,LOW);

}

void strafe(float inc){

  if(inc < 0){
    digitalWrite(LED,HIGH);
    StepperFR.setSpeed(1000);
    StepperFL.setSpeed(1000);
    StepperBR.setSpeed(-1000);
    StepperBL.setSpeed(-1000);
  }

  else{
    StepperFR.setSpeed(-1000);
    StepperFL.setSpeed(-1000);
    StepperBR.setSpeed(1000);
    StepperBL.setSpeed(1000);

  }
  //Run for time based on inches
  long timer = millis();
  while ((millis() - timer) < (1000*(abs(inc)+0.3778)/3.9533)){      
    StepperFL.runSpeed();
    StepperFR.runSpeed();
    StepperBL.runSpeed();
    StepperBR.runSpeed();
  }
  digitalWrite(LED,LOW);
}

void botForward(){
  StepperFR.setSpeed(1000);
  StepperFL.setSpeed(-1000);
  StepperBR.setSpeed(1000);
  StepperBL.setSpeed(-1000); 
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
  botReverse();
}

void botReverse(){
  StepperFR.setSpeed(-1000);
  StepperFL.setSpeed(1000);
  StepperBR.setSpeed(-1000);
  StepperBL.setSpeed(1000);  
}











