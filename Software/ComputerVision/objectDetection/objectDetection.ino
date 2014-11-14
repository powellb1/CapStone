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
int pinI3=12;//define I3 interface 
int pinI4=13;//define I4 interface 
int speedpinB=10;//enable motor B
int spead =255;//define the spead of motor
int etch = 13;
int rubiks = 11;
int incomingByte = 0;
int pot=22;
int trg=3;
int echo=2;
boolean inRange = true;
boolean camOn=true;


NewPing sonar(trg,echo,MAX_DISTANCE);

void setup(){
  //input and output pins
  pinMode(pinI1,OUTPUT);
  pinMode(pinI2,OUTPUT);
  pinMode(speedpinA,OUTPUT);
  pinMode(pinI3,OUTPUT);
  pinMode(pinI4,OUTPUT);
  pinMode(speedpinB,OUTPUT);

  pinMode(etch,OUTPUT);
  pinMode(rubiks,OUTPUT);
  Serial.begin(9600);


}

void loop()
{

  delay(50);
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  //Serial.print("Ping: ");
  //Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  //Serial.println("cm");
  if((uS/US_ROUNDTRIP_CM)>=11 && (uS/US_ROUNDTRIP_CM)<=12)
  {
    //digitalWrite(pot,HIGH);
    //delay(5000);
    //digitalWrite(pot,LOW);
    forward();
    Serial.write('C');
    //Serial.println('C');
    do
    {
      if(Serial.available()>0)
      {
        incomingByte = Serial.read()-48;
        if(incomingByte=='M')
        {
          //Movement code
        }
        else
        {
          whatObj();
        }
      }
      uS = sonar.ping();
    }
    while((uS/US_ROUNDTRIP_CM)==11);
    Serial.write('C');
    backward();
  }


}


void whatObj()
{

  //if(Serial.available()>0)
  //{
  incomingByte = Serial.read()-48;
  Serial.flush();
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
  Serial.flush();
  //}

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



