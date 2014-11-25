#ifndef ObjectDetect_h
#define ObjectDetect_h
#endif
#define MAX_DISTANCE 200;

#include "/usr/share/arduino/libraries/NewPing/NewPing.h"

class ObjectDetect
{
public:
  ObjectDetect(int trigPin, int echoPin);
  void approach(float uS);
  void whatObj(int incomingByte);
  void forward();
  void backward();
  void shuffle();
  void reset();
private:
  int _trigPin;
  int _echoPin;
  boolean completed;
  boolean inRange;
  int _spead;
  int _speedpinA;
  int _pinI1;
  int _pinI2;
  

};

