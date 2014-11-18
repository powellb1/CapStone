#include <QTRSensors.h>
#include <PID_v1.h>;


#define NUM_SENSORS             6  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             2  // emitter is controlled by digital pin 2

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {8, 9, 10, 11, 12, 13}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

//Define PID variables
double pidSetpoint, pidInput, pidOutput;

//Give the PID pointers to the variables along with the current constants
PID myPID(&pidInput, &pidOutput, &pidSetpoint,5,0,50, DIRECT);

int pinI1=8;//define I1 interface
int pinI2=11;//define I2 interface 
int speedpinA=9;//enable motor A
int pinI3=12;//define I3 interface 
int pinI4=13;//define I4 interface 
int speedpinB=10;//enable motor B
int static speadA =0;//define the spead of motor
int static speadB =0;


void setup()
{
  delay(500);
      pinMode(pinI1,OUTPUT);
  pinMode(pinI2,OUTPUT);
  pinMode(speedpinA,OUTPUT);
  pinMode(pinI3,OUTPUT);
  pinMode(pinI4,OUTPUT);
  pinMode(speedpinB,OUTPUT);
  
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  
  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtra.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  
  
  delay(1000);
  
  //init PID variables
pidSetpoint = 3000;
pidInput = qtra.readLine(sensorValues);

//start up PID
myPID.SetMode(AUTOMATIC);

             digitalWrite(pinI2,LOW);//turn DC Motor A move anticlockwise
     digitalWrite(pinI1,HIGH);
          digitalWrite(pinI4,HIGH);//turn DC Motor B move clockwise
     digitalWrite(pinI3,LOW);
     
     speadA = 100;
     speadB = 100;
          analogWrite(speedpinA,speadA);
     analogWrite(speedpinB,speadB);  
}


void loop()
{
  // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
  // To get raw sensor values, call:
  //  qtra.read(sensorValues); instead of unsigned int position = qtra.readLine(sensorValues);
  unsigned int position = qtra.readLine(sensorValues);
  
    pidInput = position;
  myPID.Compute();
  
  
  if(position >3000){
     speadA = speadA + pidOutput;
     speadB = speadB - pidOutput;
     analogWrite(speedpinA,speadA);
     analogWrite(speedpinB,speadB);    
  }
  
  if(position <3000){
     speadA = speadA - pidOutput;
     speadB = speadB + pidOutput;
     analogWrite(speedpinA,speadA);
     analogWrite(speedpinB,speadB);
  
  }  
    if(position == 5000){
     Serial.print("Challenge Zone");
     analogWrite(speedpinA,0);
     analogWrite(speedpinB,0);
     delay(4000);
     analogWrite(speedpinA,100);
     analogWrite(speedpinB,0);
     delay(2500);
    
  }else if(sensorValues[0] < 100 && sensorValues[1] < 100 && sensorValues[2] < 100 && sensorValues[3] <100){
     analogWrite(speedpinA,100);
     analogWrite(speedpinB,100);
     delay(300);
     analogWrite(speedpinA,100);
     analogWrite(speedpinB,0);
     Serial.print("Turning right");
     delay(1250);
     
    
  }else if(sensorValues[5] > 4000 && sensorValues[4] > 4000 && sensorValues[3] > 4000 && sensorValues[2] > 4000){
     analogWrite(speedpinA,100);
     analogWrite(speedpinB,100);
     delay(300);
     analogWrite(speedpinA,0);
     analogWrite(speedpinB,100);
     Serial.print("Turning left");
     delay(1250);
     
    
  }
  

  
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(); // uncomment this line if you are using raw values
  Serial.println(position); // comment this line out if you are using raw values
  
 
}
