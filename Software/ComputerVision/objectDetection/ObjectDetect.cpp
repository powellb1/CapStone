#include "ObjectDetect.h"

int spead = 255;
int speedpinA = 9;
int pinI1 = 8;
int pinI2 = 11;
#define MAX_DISTANCE 200;

ObjectDetect::ObjectDetect(int trigPin, int echoPin)
{
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, OUTPUT);
	NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

}

void ObjectDetect::approach()
{
	delay(50);
	float uS = sonar.ping();

	if (!completed)
	{
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
	analogWrite(speedpinA, spead);//input a simulation value to set the speed
	digitalWrite(pinI2, LOW);//turn DC Motor A move anticlockwise
	digitalWrite(pinI1, HIGH);
}
void ObjectDetect::backward()//
{
	analogWrite(speedpinA, spead);//input a simulation value to set the speed
	digitalWrite(pinI2, HIGH);//turn DC Motor A move clockwise
	digitalWrite(pinI1, LOW);
}

void ObjectDetect::shuffle()
{
	Serial.parseFloat();
	//Do movement things
	delay(1000);
	Serial.write('M');
	//digitalWrite(etch, LOW);

}
