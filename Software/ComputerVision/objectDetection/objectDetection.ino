#include <NewPing.h>
#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

#define rubixStrafeFromCenter 3.25

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
int trg=23;
int echo=22;
int LED = 32;
boolean camOn=true;
boolean completed = false;
boolean inRange = false;

//time it takes to make the turn needs to be changed
//testing is need to map everything at the speed we plan on running it at




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
  Serial.begin(9600);


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

}

//called when approaching object.
void approach(float uS)
{
  if(((float)(uS/US_ROUNDTRIP_CM)>=4.1 && (float)(uS/US_ROUNDTRIP_CM)<=4.3) && !inRange)
  {
    inRange = true; 
    forward();
    Serial.write('C');
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
        backward();
        Serial.write('C');
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
      digitalWrite(etch,HIGH);
      delay(5000);
      digitalWrite(etch,LOW);
      delay(3000);
      Serial.write('E');
      break;
    } 
  case 2:
    {
      digitalWrite(rubiks,HIGH);
      delay(2000);
      digitalWrite(rubiks,LOW);
      delay(3000);
      Serial.write('R');
      break;
    } 
  case 3:
    {
      digitalWrite(etch,HIGH);
      digitalWrite(rubiks,HIGH);
      delay(2000);
      digitalWrite(etch,LOW);
      digitalWrite(rubiks,LOW);
      delay(3000);
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

}

void forward()
{
  analogWrite(speedpinA,spead);//input a simulation value to set the speed
  analogWrite(speedpinB,spead);
  digitalWrite(pinI2,LOW);//turn DC Motor A move anticlockwise
  digitalWrite(pinI1,HIGH);
}
void backward()//
{
  analogWrite(speedpinA,spead);//input a simulation value to set the speed
  analogWrite(speedpinB,spead);
  digitalWrite(pinI2,HIGH);//turn DC Motor A move clockwise
  digitalWrite(pinI1,LOW);
}

void shuffle()
{
  Serial.parseFloat();
  //Do movement things
  delay(1000);
  Serial.write('M');
  digitalWrite(etch,LOW);

}















