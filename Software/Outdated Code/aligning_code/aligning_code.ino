#include <QTRSensors.h>
#include <AccelStepper.h>

float inchesMisaligned;
AccelStepper stepperFR(1,9,8);
AccelStepper stepperFL(1,13,12);
AccelStepper stepperBR(1,7,6);
AccelStepper stepperBL(1,11,10);


void setup(){
  
  stepperFR.setAcceleration(1000);
  stepperFL.setAcceleration(1000);
  stepperBR.setAcceleration(1000);
  stepperBL.setAcceleration(1000);
  
  
}


void loop(){
  
  strafeInches(inchesMisaligned);
  

  
}




void strafeInches(float inchesMisaligned){
  
  
  //if correction is to the left
  if(inchesMisaligned < 0){
    stepperFR.setSpeed(200);
    stepperFL.setSpeed(-200);
    stepperBR.setSpeed(-200);
    stepperBL.setSpeed(200);
    
    long timer = millis();
    while((millis() - timer) < 2000){
      
    stepperFR.runSpeed();
    stepperFL.runSpeed();
    stepperBR.runSpeed();
    stepperBL.runSpeed();
    
    
    }
    
      //If correction is to the right
      if(inchesMisaligned > 0){
    stepperFR.setSpeed(-200);
    stepperFL.setSpeed(200);
    stepperBR.setSpeed(200);
    stepperBL.setSpeed(-200);
    
    long timer = millis();
    while((millis() - timer) < 2000){
      
    stepperFR.runSpeed();
    stepperFL.runSpeed();
    stepperBR.runSpeed();
    stepperBL.runSpeed();
    
    
    }

    
  }
  
}
}
