
#include <PID_v1.h>

//Define pins for QRE1113s
int QRE1Pin = 6;
int QRE2Pin = 5;
int QRE3Pin = 4;
int QRE4Pin = 3;
int QRE5Pin = 2;


//Pins for Motors
int dcLeft = 10;
int dcRight = 9;

//Static motor speed
int static leftSpeed;
int static rightSpeed;

//For PID
double pidSetpoint, pidInput, pidOutput;
PID pid(&pidInput, &pidOutput, &pidSetpoint, 1,0,0, DIRECT);


void setup() {
  Serial.begin(9600);
  pinMode(dcLeft, OUTPUT);
  pinMode(dcRight, OUTPUT);

  
  //PID setup
  pidInput = 3000;
  pidSetpoint = 0;
  pid.SetMode(AUTOMATIC);
  
}

void loop() {
  
  //Read values of QREs
  int QRE1val = readQRE(QRE1Pin);
  int QRE2val = readQRE(QRE2Pin);
  int QRE3val = readQRE(QRE3Pin);
  int QRE4val = readQRE(QRE4Pin);
  int QRE5val = readQRE(QRE5Pin);
  
  //Average values for PID
 
   pidInput = (QRE1val*-2 + QRE2val*-1 + QRE3val*0 + QRE4val*1 + QRE5val*2);
   pid.Compute();
   
     
  //Adjust motors based off of values from QREs
 // if((leftSpeed + pidOutput) >= 0 && (rightSpeed + pidOutput) >= 0){
   //  analogWrite(dcLeft, leftSpeed + pidOutput);
     ///analogWrite(dcRight, rightSpeed + pidOutput);
//  }
 
 //Print QRE values
 Serial.print(QRE1val);
 Serial.print("\t");
 Serial.print(QRE2val);
 Serial.print("\t");
 Serial.print(QRE3val);
 Serial.print("\t");
 Serial.print(QRE4val);
 Serial.print("\t");
 Serial.print(QRE5val);
 Serial.print("\n");
 
 //Print pid vals
 Serial.print("Sensor array value: ");
 Serial.print(pidInput);
 Serial.print("\t");
 Serial.print("PID output value: ");
 Serial.print(pidOutput);
 Serial.print("\n\n");
  
  
}


//Function based off of code found at bildr.org/2011/06/qre1113-arduino
int readQRE(int QRENum){
  
  long time;
  int diff;
  
  //Basic setup to charge capacitor then read the release.
  pinMode(QRENum, OUTPUT);
  digitalWrite(QRENum, HIGH);
  delayMicroseconds(10);
  pinMode(QRENum, INPUT);
  
  //Arbitrary time to use for calculating difference
  time = micros();
  
  //This while times how long the inputis high but will quit if nothing happens after 3 miliseconds.
  while(digitalRead(QRENum) == HIGH && (micros()-time < 3000)){
  diff = micros() - time;
  }  
  
  return diff;
}





void stop(){
 
 analogWrite(dcLeft, 0);
 analogWrite(dcRight, 0);
}
