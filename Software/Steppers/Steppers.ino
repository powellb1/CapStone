
int dirPin  = 3; 
int stepperPin = 2; 
void setup () 
{   
pinMode (dirPin, OUTPUT);   
pinMode (stepperPin, OUTPUT); 
}

void step (boolean dir, int steps) 
{   
digitalWrite (dirPin, dir);   
delay (50);   
for (int i = 0; i <steps; i ++) 
{     
digitalWrite (stepperPin, HIGH);     
delayMicroseconds (75 );     
digitalWrite (stepperPin, LOW);     
delayMicroseconds (75);   
} 
}
void loop () 
{   
step (true, 5000);   
delay (500);   
step (false, 10000);   
delay (500); 
}




















