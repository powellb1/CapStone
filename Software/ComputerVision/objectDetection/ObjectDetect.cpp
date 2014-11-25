#include "ObjectDetect.h"



ObjectDetect::ObjectDetect(int trigPin, int echoPin)
{
  _trigPin=trigPin;
  _echoPin=echoPin;
  _spead = 255;
  _speedpinA = 9;
  _pinI1 = 8;
  _pinI2 = 11;
  pinMode(_pinI1,OUTPUT);
  pinMode(_pinI2,OUTPUT);
  pinMode(_speedpinA,OUTPUT);

}

void ObjectDetect::approach(float uS)
{
  int incomingByte;


  if (((float)(uS / US_ROUNDTRIP_CM) >= 4.1 && (float)(uS / US_ROUNDTRIP_CM) <= 4.3) && !inRange)
  {
    inRange = true;
    forward();
    Serial.write('C');
  }

  while (inRange && !completed)
  {
    while (Serial.available() > 0)
    {
      incomingByte = Serial.read();
      if (incomingByte == 'X')
      {
        //digitalWrite(LED, HIGH);
        shuffle();
        //digitalWrite(LED, LOW);
      }
      else if (incomingByte > 48 && incomingByte < 52)
      {
        whatObj(incomingByte);
      }

      if (completed)
      {
        backward();
        Serial.write('C');
      }
    }

  }


}

//used to determine where we're moving to. Need to put in values as to how far to move
//laterally
void ObjectDetect::whatObj(int incomingByte)
{
  incomingByte = incomingByte - 48;
  switch (incomingByte)
  {
  case 1:
    {
      Serial.write('E');
      break;
    }
  case 2:
    {
      Serial.write('R');
      break;
    }
  case 3:
    {
      Serial.write('S');
      break;
    }
  }
  completed = true;

}

void ObjectDetect::forward()
{
  analogWrite(_speedpinA, _spead);//input a simulation value to set the speed
  digitalWrite(_pinI2, LOW);//turn DC Motor A move anticlockwise
  digitalWrite(_pinI1, HIGH);
}
void ObjectDetect::backward()//
{
  analogWrite(_speedpinA, _spead);//input a simulation value to set the speed
  digitalWrite(_pinI2, HIGH);//turn DC Motor A move clockwise
  digitalWrite(_pinI1, LOW);
}

void ObjectDetect::shuffle()
{
  Serial.parseFloat();
  //Do movement things
  delay(1000);
  Serial.write('M');
  //digitalWrite(etch, LOW);

}

void ObjectDetect::reset()
{
  completed = false; 
}

