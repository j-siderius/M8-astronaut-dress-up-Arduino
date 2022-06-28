#include <Arduino.h>

// include custom classes
#include "Timer.h"
#include "Mosfet.h"
#include "SerialComm.h"

Serialcomm comm;

void setup() {
  Serial.begin(9600);  
  comm = Serialcomm();
}

void loop() {
  
}
