//This program moves servos according to an individual mapping
//g-force; oxygen; pressure;

#ifndef DialServos_h
#define DialServos_h

#include <Arduino.h>
#include <Servo.h>
#include "Timer.h"



class DialServos 
{
    
  private: //needs update, move variables elsewhere
    int nrSrv = 3; //number of servos connected
    int startPin; //first pin used on arduino, the other servos should be connected to the following pins

    //variables passed from main, used as placeholders here
    float planetGForce;
    int gInt = planetGForce*10;
    float oxygenFloat;

    float pressure; 
    bool startAni; //toggle start up animation
    bool launchConfirm; //toggle rocket launching animation
    int startGrav=300; //gravity at the start of the launch 

   // Timer launchTime = Timer(50, launchDials); 

    unsigned long prevMillis = 0;
    int dgr = 0;
    bool goUp = true;

    int pos[3] = {0,0,0} ;      // variable to store the servo positions ??
    Servo servos[3];            // Servo objects

  public:

    DialServos(int startPin){
      this->startPin = startPin;
    };

    void runServos() {
      unsigned long curTime = millis();
      if (startAni == true){
        startUp(curTime);
      }
      else if (launchConfirm == true && startAni == false){
        //launchTime.runCheck(curTime);   
      }
      else if (startAni == false && launchConfirm == false) {
        setDials(gInt, oxygenFloat, pressure); 
        startGrav = 1;
      }  
    }

    void startUp(unsigned long ms){   //sweeps the dials from zero to the max and back  

      if (ms - prevMillis > dgr/4 && dgr<180 && goUp == true){

          for (int i = 0; i < nrSrv; i++ ){
          servos[i].write(dgr);
          } 
        goUp = true;
        prevMillis = ms;
        dgr++;
        
      }
      if (ms - prevMillis > 50 && goUp == true && dgr == 180){
        goUp = false;
      }

      if (ms - prevMillis > dgr/4 && dgr>0 && goUp == false){
          for (int i = 0; i < nrSrv; i++ ){
          servos[i].write(dgr);
          } 
        prevMillis = ms;
        dgr--;
      }
      if (ms - prevMillis > 100 && dgr==0 && goUp == false){
        startAni = false;
        prevMillis = ms;
      }
      
    }

    void launchDials(){
      unsigned long curTime = millis();
      for (int i = 1; i<nrSrv; i++){
        int rand = random (10,170);
        servos[i].write(rand);
      }
      int mapGrav = map(startGrav,0,1000,0,180);
      if (startGrav > 0){
        servos[0].write(mapGrav);
        startGrav --;
      }    
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
      // add randomness to increase realism  
    }

};

#endif