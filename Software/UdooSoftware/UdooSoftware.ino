
#include <PID_v1.h>

//Define pins for QRE1113s
#define QRE1Pin  5
#define QRE2Pin  6
#define QRE3Pin  7
#define QRE4Pin  8
#define QRE5Pin  9

//Pins for Motors
int dcLeft = 3;
int dcRight = 4;

//For PID
double pidSetpoint, pidInput, pidOutput;
PID pid(&pidInput, &pidOutput, &pidSetpoint, 2,0,0, DIRECT);


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
