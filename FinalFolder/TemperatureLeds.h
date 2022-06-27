/*
This program handles the thermometer leds
*/

#include <FastLED.h>
#include "Timer.h"


class TempLed {
  private:
    
    int dPin;
    int numLeds = 16;
  /*
  Creates variables (variable for temperature should be passed from the serial to void turnon
  */
    CRGB leds[16];
    int temperature;
    int brightness;
    
  public:
  
    TempLed (int dPin){
      this->dPin =dPin;
    }
    /*
    Turns leds on. Also pass temperature through this method
    */
    void turnOn() {
      int ledDisplay = numLeds * float(temperature + 200) / 700 + 1;
      for (int i = 0; i < int(ledDisplay); i++) {
        leds[i].r = i * brightness;
        leds[i].g = 1.5 * (numLeds / 2 - abs(numLeds / 2 - i)) * brightness;
        leds[i].b = (numLeds - i) * brightness;
      }
      FastLED.show();
    }
    /*
    Turns leds off. 
    */
    void turnOff() {
      for (int i = 0; i < numLeds; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
      }
      FastLED.show();
    }
};
