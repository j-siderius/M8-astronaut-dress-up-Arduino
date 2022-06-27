// Class for the dynamic led strip indicating travelling time


#include "Timer.h"
#include <FastLED.h>

// define strip parameters
#define NUM_LEDS 20
#define LED_ADDR 8

class TravelLight
{
  private:
    CRGB leds[NUM_LEDS];

    // define function variables
    //bool travelLEDon = true; //now called launching as global 
    int index = 0;
    
    Timer travelLEDtimer;

  public:
    TravelLight();

    // timer object
    
    void Travelrun(bool launchConfirm) {
      // check if the travelLED is active and then check if we can update it
      if (launchConfirm) travelLEDtimer.runCheck(millis());
    }    
    void travelLED() {
      // turn all LEDS off
      FastLED.clear(true);

      // set the LEDS to corresponding colors (incl followers)
      if (index < NUM_LEDS) leds[index].setRGB(255, 255, 255);
      if (index > 0) leds[index - 1].setRGB(200, 200, 200);
      if (index > 1) leds[index - 2].setRGB(150, 150, 150);
      if (index > 2) leds[index - 3].setRGB(100, 100, 100);

      // increase the index if we did not finish the strip yet + tail length
      if (index < NUM_LEDS + 3) index++;
      // reset the index to loop around (or set exiting function here)
      else index = 0;

      // show the LEDs
      FastLED.show();
    }

    void ini() {
      // initialise the LED strip
      FastLED.addLeds<NEOPIXEL, LED_ADDR>(leds, NUM_LEDS);
      FastLED.clear(true);
      //this->travelLEDtimer = Timer(0, &TravelLight::travelLED);
      // change the speed of the LED travel
      // TODO: this is subject to change e.g. implement this function call inside of the data handler
      travelLEDtimer.changeDelay(200);
    }

};
