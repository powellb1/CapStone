
//Define pins for QRE1113s
int QRE1Pin = 2;
int QRE2Pin = 3;
int QRE3Pin = 4;
int QRE4Pin = 5;
int QRE5Pin = 6;



void setup() {
  Serial.begin(9600);

}

void loop() {
  
  //Read values of QREs
  int QRE1val = readQRE(QRE1Pin);
  int QRE2val = readQRE(QRE2Pin);
  int QRE3val = readQRE(QRE3Pin);
  int QRE4val = readQRE(QRE4Pin);
  int QRE5val = readQRE(QRE5Pin);
  
  //Adjust motors based off of values from QREs
  Serial.println("Readings retreived");
  
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
  while(digRead(QRENum) == HIGH && (micros()-time < 3000)){
  diff = micros() - time;
  }  
  
  return diff;
}
