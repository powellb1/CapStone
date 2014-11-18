/* The QTR array code is based off of example code provided by
pololu. www.pololu.com
*/

#include <QTRSensors.h>
#include <PID_v1.h>




#define NUM_SENSORS             8  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  2  // average 4 analog samples per sensor reading
#define EMITTER_PIN             QTR_NO_EMITTER_PIN  // no emitter connected

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {8, 9, 10, 11, 12, 13, 14, 15},                 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];


//Define PID variables
double pidSetpoint, pidInput, pidOutput;

//Give the PID pointers to the variables along with the current constants
PID myPID(&pidInput, &pidOutput, &pidSetpoint, 2, 0.5, 2, DIRECT);


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
  
 if ((LF < 2000) && (interflag == 1)){
   //making a left turn once returning to an intersection that roadie turn left at
   interflag = 0;
   //turn left
      timer = millis();
   while ((millis() - timer) < 2000){
     stepperFL.runSpeed();
     stepperFR.runSpeed();
     stepperBL.runSpeed();
     stepperBR.runSpeed();
   } 
   //turn left 
   stepperFL.setSpeed(-1000);
   stepperFR.setSpeed(1000);
   stepperBL.setSpeed(-1000);
   stepperBR.setSpeed(1000);  
   timer = millis();
   while ((millis() - timer) < 2000){
     stepperFL.runSpeed();
     stepperFR.runSpeed();
     stepperBL.runSpeed();
     stepperBR.runSpeed();
   }
   stepperFL.setSpeed(3000);
   stepperFR.setSpeed(3000);
   stepperBL.setSpeed(3000);
   stepperBR.setSpeed(3000);
   
 }else if ((LF > 5000) && (interflag == 1)){
   //making a right turn once coming back to an intersection that roadie turned right at.
   interflag = 0;
  //turn right        
   timer = millis();
   while ((millis() - timer) < 2000){
     stepperFL.runSpeed();
     stepperFR.runSpeed();
     stepperBL.runSpeed();
     stepperBR.runSpeed();
   }
   //turn right
   stepperFL.setSpeed(1000);
   stepperFR.setSpeed(-1000);
   stepperBL.setSpeed(1000);
   stepperBR.setSpeed(-1000);  
   timer = millis();
   while ((millis() - timer) < 2000){
     stepperFL.runSpeed();
     stepperFR.runSpeed();
     stepperBL.runSpeed();
     stepperBR.runSpeed();
   }
   stepperFL.setSpeed(3000);
   stepperFR.setSpeed(3000);
   stepperBL.setSpeed(3000);
   stepperBR.setSpeed(3000); 
  
 }else if(LF < 2000){  
   timer = millis();
   while ((millis() - timer) < 2000){
     stepperFL.runSpeed();
     stepperFR.runSpeed();
     stepperBL.runSpeed();
     stepperBR.runSpeed();
   } 
   //read line senors and if it dects line after it sets flag
   //readline
   if(LFI > 3000){
     interflag = 1;
   }
   //turn left 
   stepperFL.setSpeed(-1000);
   stepperFR.setSpeed(1000);
   stepperBL.setSpeed(-1000);
   stepperBR.setSpeed(1000);  
   timer = millis();
   while ((millis() - timer) < 2000){
     stepperFL.runSpeed();
     stepperFR.runSpeed();
     stepperBL.runSpeed();
     stepperBR.runSpeed();
   }
   stepperFL.setSpeed(3000);
   stepperFR.setSpeed(3000);
   stepperBL.setSpeed(3000);
   stepperBR.setSpeed(3000);   
 }else if(LF >= 5000){
      
   timer = millis();
   while ((millis() - timer) < 2000){
     stepperFL.runSpeed();
     stepperFR.runSpeed();
     stepperBL.runSpeed();
     stepperBR.runSpeed();
   }
  
   
   if(LFI > 3000){
     interflag = 1;
   }
   //turn right
   stepperFL.setSpeed(1000);
   stepperFR.setSpeed(-1000);
   stepperBL.setSpeed(1000);
   stepperBR.setSpeed(-1000);  
   timer = millis();
   while ((millis() - timer) < 2000){
     stepperFL.runSpeed();
     stepperFR.runSpeed();
     stepperBL.runSpeed();
     stepperBR.runSpeed();
   }
   stepperFL.setSpeed(3000);
   stepperFR.setSpeed(3000);
   stepperBL.setSpeed(3000);
   stepperBR.setSpeed(3000); 
  
 }else if((LF >= 4000) &&(LF < 5000){
  //make corrections to right
  //speeds up right motors and slows down the left motors
  stepperFL.setSpeed(stepperFL.speed() - 100);
  stepperFR.setSpeed(stepperFR.speed() + 100);
  stepperBL.setSpeed(stepperBL.speed() - 100);
  stepperBR.setSpeed(stepperBR.speed() + 100);
 }else if ((LF < 3000) && (LF >= 2000)){  
  //make corrections to the left
  //sppeds up left motors and slows down the right motors 
  stepperFL.setSpeed(stepperFL.speed() + 100);
  stepperFR.setSpeed(stepperFR.speed() - 100);
  stepperBL.setSpeed(stepperBL.speed() + 100);
  stepperBR.setSpeed(stepperBR.speed() - 100);
 }
 
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
