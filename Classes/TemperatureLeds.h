#include <FastLED.h>
#include "Timer.h"
#define NUM_LEDS 16
#define DATA_PIN 13

class tempLed {
  private:
  /*
  Creates variables (variable for temperature should be passed from the serial to void turnon
  */
    CRGB leds[NUM_LEDS];
    int temperature;
    int brightness;
  public:
    /*
    Turns leds on. Also pass temperature through this method
    */
    void turnOn() {
      int ledDisplay = NUM_LEDS * float(temperature + 200) / 700 + 1;
      for (int i = 0; i < int(ledDisplay); i++) {
        leds[i].r = i * brightness;
        leds[i].g = 1.5 * (NUM_LEDS / 2 - abs(NUM_LEDS / 2 - i)) * brightness;
        leds[i].b = (NUM_LEDS - i) * brightness;
      }
      FastLED.show();
    }
    /*
    Turns leds off. 
    */
    void turnOff() {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
      }
      FastLED.show();
    }
};
