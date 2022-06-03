#include <Arduino.h>

// include custom timer library
#include "Timer.h"

// make timer object and start it with a delay of 1000ms = 1s
Timer ledTimer = Timer(1000);


// forward-declare function
void blinkLed();

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  unsigned long curMillis = millis();

  // check if the timer has expired and we can run the function
  if (ledTimer.check(curMillis)) blinkLed();
}

void blinkLed() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}