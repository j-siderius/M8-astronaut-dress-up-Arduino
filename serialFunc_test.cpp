#include <Arduino.h>

#include "Serialcomm.h"

Serialcomm comm;

void funcA() {
  Serial.println("Function A");
}

void funcB() {
  int var = comm.readVar(3);
  Serial.print("Function B: ");
  Serial.println(var);
}

void funcC() {
  bool boo = comm.readBool();
  Serial.print("Function C: ");
  Serial.println(boo ? "true" : "false");
}

void setup() {
  Serial.begin(9600);
  comm = Serialcomm();

  comm.addFunction('A', funcA);
  comm.addFunction('B', funcB);
  comm.addFunction('C', funcC);
}

void loop() {
  comm.updateSerial();
}
