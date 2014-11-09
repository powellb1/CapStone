/*
  ObjectDetection
 
 This module will wait for a serial communication from the Pi and turn on
 a corresponding LED.
 
 */

//Pin 13 is for the Etch
//Pin 11 is for Rubiks
int etch = 13;
int rubiks = 11;
int incomingByte = 0;

void setup(){
  //input and output pins
  pinMode(etch,OUTPUT);
  pinMode(rubiks,OUTPUT);
  Serial.begin(9600);


}

void loop()
{
  if(Serial.available()>0)
  {
    incomingByte = Serial.read()-48;
        Serial.println(incomingByte);
    Serial.flush();
    switch(incomingByte)
    {
    case 1:
      {
        digitalWrite(etch,HIGH);
        delay(5000);
        digitalWrite(etch,LOW);
        delay(3000);
        Serial.write('K');
        break;
      } 
    case 2:
      {
        digitalWrite(rubiks,HIGH);
        delay(2000);
        digitalWrite(rubiks,LOW);
        delay(3000);
        Serial.write('K');
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
        Serial.write('K');
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

  }

}


