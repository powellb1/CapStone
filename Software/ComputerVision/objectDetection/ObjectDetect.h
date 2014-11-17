#ifndef ObjectDetect_h
#define ObjectDetect_h

#include <NewPing.h>

class ObjectDetect
{
public:
	ObjectDetect(int trigPin, int echoPin);
	void approach();
	void whatObj(int incomingByte);
	void forward();
	void backward();
	void shuffle();
private:
	int _trigPin;
	int _echoPin;
	boolean completed;
	boolean inRange;
	NewPing sonar;

};