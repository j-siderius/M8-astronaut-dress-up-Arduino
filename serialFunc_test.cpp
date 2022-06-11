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
  int boo = comm.readBool();
  Serial.print("Function C: ");
  if (boo) Serial.println("True");
  else Serial.println("False");
}

void setup() {
  Serial.begin(9600);
  comm = Serialcomm();

  comm.addFunction(0, 'A', funcA);
  comm.addFunction(1, 'B', funcB);
  comm.addFunction(2, 'C', funcC);
}

void loop() {
  comm.updateSerial();
}
