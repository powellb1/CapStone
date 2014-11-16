#include <NewPing.h>

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
  if(!completed)
  {
    approach(uS);

  }
  /*
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
   
   }
   
   }
   
   
   if(completed)
   {
   backward();
   Serial.write('C');
   }
   */

}

void approach(float uS)
{
  if(((float)(uS/US_ROUNDTRIP_CM)>=4 && (float)(uS/US_ROUNDTRIP_CM)<=4.2) && !inRange)
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
  //digitalWrite(pinI4,HIGH);//turn DC Motor B move clockwise
  //digitalWrite(pinI3,LOW);
  digitalWrite(pinI2,LOW);//turn DC Motor A move anticlockwise
  digitalWrite(pinI1,HIGH);
}
void backward()//
{
  analogWrite(speedpinA,spead);//input a simulation value to set the speed
  analogWrite(speedpinB,spead);
  //digitalWrite(pinI4,LOW);//turn DC Motor B move anticlockwise
  //digitalWrite(pinI3,HIGH);
  digitalWrite(pinI2,HIGH);//turn DC Motor A move clockwise
  digitalWrite(pinI1,LOW);
}

void shuffle()
{
  //while(Serial.available()>0)
  Serial.parseFloat();

  delay(1000);
  Serial.write('M');
  digitalWrite(etch,LOW);

}











