#include <NewPing.h>
#include <AccelStepper.h>

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
int etch = 10;
int rubiks = 12;
int incomingByte = 0;
int pot=22;
int trg=3;
int echo=2;
int LED = 4;
boolean camOn=true;
boolean completed = false;
boolean inRange = false;

AccelStepper stepperFR(1,9,8);
AccelStepper stepperFL(1,13,12);
AccelStepper stepperBR(1,7,6);
AccelStepper stepperBL(1,11,10);


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
  
  stepperFR.setMaxSpeed(3000);
  stepperFL.setMaxSpeed(3000);
  stepperBR.setMaxSpeed(3000);
  stepperBL.setMaxSpeed(3000);
  
  Serial.begin(9600);


}

void loop()
{

  delay(50);
  float uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
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
      //strafe to etch 
      Serial.write('E');
      digitalWrite(etch,LOW);
      break;
    } 
  case 2:
    {
      digitalWrite(rubiks,HIGH);
      //strafe to rubiks
      Serial.write('R');
      digitalWrite(rubiks,LOW);
      break;
    } 
  case 3:
    {
      digitalWrite(etch,HIGH);
      digitalWrite(rubiks,HIGH);
      //strafe to simon
      Serial.write('S');
      digitalWrite(etch,LOW);
      digitalWrite(rubiks,LOW);
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
  float dist = Serial.parseFloat();
  //Do movement things
  strafeInches(dist);
  Serial.write('M');
  digitalWrite(etch,LOW);

}

void reset()
{
 inRange = false;
 completed = false; 
}


//Function will strafe the appropriate amount of inches to match the center of Roadie to the challenge.
void strafeInches(float inchesMisaligned){
  
  
  //if correction is to the left
  if(inchesMisaligned < 0){
    stepperFR.setSpeed(200);
    stepperFL.setSpeed(-200);
    stepperBR.setSpeed(-200);
    stepperBL.setSpeed(200);
    
    long timer = millis();
    while((millis() - timer) < 2000){
      
    stepperFR.runSpeed();
    stepperFL.runSpeed();
    stepperBR.runSpeed();
    stepperBL.runSpeed();
    
    
    }
    
      //If correction is to the right
      if(inchesMisaligned > 0){
    stepperFR.setSpeed(-200);
    stepperFL.setSpeed(200);
    stepperBR.setSpeed(200);
    stepperBL.setSpeed(-200);
    
    long timer = millis();
    while((millis() - timer) < 2000){
      
    stepperFR.runSpeed();
    stepperFL.runSpeed();
    stepperBR.runSpeed();
    stepperBL.runSpeed();
    
    
    }

    
  }
  
}
}











