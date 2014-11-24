/* The QTR array code is based off of example code provided by
pololu. www.pololu.com
*/

#include <QTRSensors.h>
#include <PID_v1.h>




#define NUM_SENSORS             6  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             QTR_NO_EMITTER_PIN  // no emitter connected

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {8, 9, 10, 11, 12, 13},                 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];


//Define PID variables
double pidSetpoint, pidInput, pidOutput;

//Give the PID pointers to the variables along with the current constants
PID myPID(&pidInput, &pidOutput, &pidSetpoint,4,0,3, DIRECT);


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
  
  Serial.begin(9600);
    pinMode(pinI1,OUTPUT);
  pinMode(pinI2,OUTPUT);
  pinMode(speedpinA,OUTPUT);
  pinMode(pinI3,OUTPUT);
  pinMode(pinI4,OUTPUT);
  pinMode(speedpinB,OUTPUT);
  
  qtra.calibrate();



  
//init PID variables
pidSetpoint = 3000;
pidInput = qtra.readLine(sensorValues);

//start up PID
myPID.SetMode(AUTOMATIC);

             digitalWrite(pinI2,LOW);//turn DC Motor A move anticlockwise
     digitalWrite(pinI1,HIGH);
          digitalWrite(pinI4,HIGH);//turn DC Motor B move clockwise
     digitalWrite(pinI3,LOW);
     
     speadA = 200;
     speadB = 200;
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
     analogWrite(speedpinA,speadA + pidOutput);
     analogWrite(speedpinB,speadB -pidOutput);    
  }
  
  if(position <3000){
  
     analogWrite(speedpinA,speadA - pidOutput);
     analogWrite(speedpinB,speadB + pidOutput);
  
  }  
  
/*  if(position > 4500){
     Serial.print("Challenge Zone");
     analogWrite(speedpinA,0);
     analogWrite(speedpinB,0);
     delay(500);
     analogWrite(speedpinA,255);
     analogWrite(speedpinB,0);
     delay(400);
    
  }
  
  
  if(sensorValues[0] < 100 && sensorValues[1] < 100 && sensorValues[2] < 100 && sensorValues[3] < 100){
     analogWrite(speedpinA,255);
     analogWrite(speedpinB,0);
     Serial.print("Turning right");
     
    
  }
  */
 /*   if(position>4000){
     analogWrite(speedpinA,0);
     analogWrite(speedpinB,255);
     
    
  }
  */
  
 /*  if(position > 3000){
    
    //backwards
         digitalWrite(pinI2,HIGH);//turn DC Motor A move clockwise
     digitalWrite(pinI1,LOW);
          digitalWrite(pinI4,LOW);//turn DC Motor B move anticlockwise
     digitalWrite(pinI3,HIGH);
     analogWrite(speedpinA,pidOutput);
     analogWrite(speedpinB,pidOutput);
    
  }

  if(position < 3000){
    
    //forwards
             digitalWrite(pinI2,LOW);//turn DC Motor A move anticlockwise
     digitalWrite(pinI1,HIGH);
          digitalWrite(pinI4,HIGH);//turn DC Motor B move clockwise
     digitalWrite(pinI3,LOW);
     analogWrite(speedpinA,pidOutput);
     analogWrite(speedpinB,pidOutput);
    
  }
  */
  
  

 
  
  //Use outputs to work with motors
  
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(); // uncomment this line if you are using raw values
  Serial.println(position); // comment this line out if you are using raw values
  
  Serial.println();
  Serial.println();
  Serial.println(pidOutput);
  
//  delay(250);
  
  
}
