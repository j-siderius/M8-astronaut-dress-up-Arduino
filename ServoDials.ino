//This program moves servos according to an individual mapping
//g-force; oxygen; pressure;

#include <Servo.h>
#include <Timer.h>

int nrSrv = 3; //number of servos connected
int startPin = 8; //first pin used on arduino, the other servos should be connected to the following pins

//variables passed from main, used as placeholders here
float planetGForce = 2.0;
int gInt = planetGForce*10;
bool toxicity = true;
bool oxygen = false;
float oxygenFloat = 20;
float pressure = 4; 

bool startani; //toggle start up animation
bool launchConfirm; //toggle rocket launching animation
int startGrav = 1; //gravity at the start of the launch 

Timer waitLoop = Timer(1500, loop); //still doesn't do it for me, sry


int pos[3] = {0,0,0} ;    // variable to store the servo positions
Servo servos[3];            // Servo objects

void setup() {
  Serial.begin(9600);

  for (int i= 0; i<nrSrv; i++){
    servos[i].attach(startPin + i); //connect the servos
  }  

  //set state of animations for testing purposes
  startani = true; 
  launchConfirm = false;
}

void loop() {
  if (startani == true){
    startUp();
  }
  if (launchConfirm == true){
    launchDials();
  }
  else {
    setDials(gInt, oxygenFloat, pressure); 
    startGrav = 1;
  }  
}

void startUp(){   //sweeps the dials from zero to the max and back

  for (int n = 0; n< 180; n++){
      for (int i = 0; i < nrSrv; i++ ){
        servos[i].write(n);
        
     }  
     delayInLoop(n/4);
  }
  delayInLoop(50);
  for (int n = 180; n>0; n--){
      for (int i = 0; i < nrSrv; i++ ){
        servos[i].write(n);
     }    
     delayInLoop(n/4);
  }  
  startani = false;
}

void launchDials(){
  unsigned long curTime = millis();
  for (int i = 1; i<nrSrv; i++){
    int rand = random (10,170);
    servos[i].write(rand);
  }
if (startgrav > 0){
 servos[0].write()  
} 
  delayInLoop(15);
  waitLoop.runCheck(curTime);    
}


void setDials(float grav, float press, float oxy) { //sets the dials to the mapped position; takes the floating values as parameters

  float mapGrav = map(grav,0,25,180,0); //maps gravity, with highest g force in range 25g
  float mapPress = map(press,0,10,180,0); //maps pressure, with highest pressure at 10 bar
  float mapOxy = map(oxy,0,30,180,0); //maps oxygen percentage 
  
  //Serial.println(mapGrav);

  //set the servos
  servos[0].write(mapGrav);
  servos[1].write(mapPress);
  servos[2].write(mapOxy);    

}

//used as a simple delay function
void delayInLoop(long microSeconds)
{    
  microSeconds *= 1000;
  const unsigned long start = micros();
   while (true)
   {
       unsigned long now = micros();
       if (now - start >= microSeconds)
       {
           return;
       }
   }
}
