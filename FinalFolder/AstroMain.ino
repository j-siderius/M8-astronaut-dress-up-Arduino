//main code for the Astronaut installation

#include <Servo.h>
#include "LiquidCrystal_I2C.h"
#include "Timer.h"
#include "Serialcomm.h"
#include "LDR.h"
#include "DialServos.h"
#include "DestinationLCD.h"
#include "TemperatureLeds.h"


//All pin definitions go here

int ldrD[6] = { 2, 3, 4, 5, 6, 7 };
char ldrA[3] = { A0, A1, A2 };

int servPin = 8;  //first pin of servos. other servos have to be attatched at ascending pin numbers




//create objects
LDR LDRs(ldrD, ldrA);
//DialServos DashServos(servPin);
DestinationLCD destination();



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  LDRs.updateArrays();
}
