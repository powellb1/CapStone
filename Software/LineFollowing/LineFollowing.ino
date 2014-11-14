/* The QTR array code is based off of example code provided by
pololu. www.pololu.com
*/

#include <QTRSensors.h>
#include <PID_v1.h>
#include <AccelStepper.h>



AccelStepper stepperFR(1,2,8);
AccelStepper stepperFL(1,3,12);
AccelStepper stepperBR(1,5,4);
AccelStepper stepperBL(1,6,7);


#define NUM_SENSORS             6  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  1  // average 4 analog samples per sensor reading
#define EMITTER_PIN             QTR_NO_EMITTER_PIN  // no emitter connected

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {0, 1, 2, 3, 4, 5},                 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];


//Define PID variables
double pidSetpoint, pidInput, pidOutput;

//Give the PID pointers to the variables along with the current constants
PID myPID(&pidInput, &pidOutput, &pidSetpoint,1,0,0, DIRECT);


void setup()
{
  
  //Stepper test
  stepperFR.setMaxSpeed(5000);
  stepperFR.setAcceleration(1000);
  stepperFR.setSpeed(5000);
  
  stepperFL.setMaxSpeed(5000);
  stepperFL.setAcceleration(1000);
  stepperFL.setSpeed(5000);
  
  stepperBR.setMaxSpeed(5000);
  stepperBR.setAcceleration(1000);
  stepperBR.setSpeed(5000);
  
  stepperBL.setMaxSpeed(5000);
  stepperBL.setAcceleration(1000);
  stepperBL.setSpeed(5000);
  
  
  
  delay(500);
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
pidSetpoint = 1000;
pidInput = qtra.readLine(sensorValues);

//start up PID
myPID.SetMode(AUTOMATIC);
}




void loop()
{
  
  // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
  // To get raw sensor values, call:
  //  qtra.read(sensorValues); instead of unsigned int position = qtra.readLine(sensorValues);
  unsigned int position = qtra.readLine(sensorValues);
  pidInput = position;
  myPID.Compute();
  
 
  stepperFR.runSpeed();
  stepperFL.runSpeed();
  stepperBL.runSpeed();
  stepperBR.runSpeed();
  
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
