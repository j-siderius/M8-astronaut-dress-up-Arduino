#include <Arduino.h>

// include custom timer library
#include "Timer.h"

// forward-declare function
void blinkLed();
void blinkLedPin(int pin);

// make timer object and start it with a delay of 1000ms = 1s
Timer ledTimer = Timer(1000);
// make timer object with callback function and delay of 1200ms
Timer ledTimer2 = Timer(1200, blinkLed);
// make timer object with callback function with integer parameter and delay of 1400ms
Timer ledTimer3 = Timer(1400, blinkLedPin);

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  unsigned long curTime = millis();

  // check if the timer has expired and we can run the function
  if (ledTimer.check(curTime)) blinkLed();
  // check if timer has expired and run function if so
  ledTimer2.runCheck(curTime);
  // check if timer has expired and run function with parameter if so
  ledTimer3.runCheck(curTime, LED_BUILTIN);
}

void blinkLed() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void blinkLedPin(int pin) {
  digitalWrite(pin, !digitalRead(pin));
}