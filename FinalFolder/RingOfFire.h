#include <Arduino.h>

#include "Timer.h"
#include <FastLED.h>

#define NUM_LEDS 16
#define D_PIN 12 //apparently this is neccessary after all

class RingOfFire{
  private:
    //void ledFire();
    //void ledFireInit();
    
    //int dPin;
    // initialize LED array
    CRGB leds[NUM_LEDS];
    //Timer ledFireTimer = Timer(100, ledFire);
    //Timer ledFireTimer = Timer(1000, ledFire);
  public:

    RingOfFire(){
       // initialize LEDs
      FastLED.addLeds<NEOPIXEL, D_PIN>(leds, NUM_LEDS);
      // give each LED a starting color
      for (int i = 0; i < NUM_LEDS; i++)
      {
        // generate random number for green component
        int g = random(0, 256);
        // set LED to default red and random green component
        leds[i].setRGB(255, g, 0);
      }
      // show LEDs
      FastLED.show();
    }
      
    void run()
    {
      unsigned long curTime = millis();
      //ledFireTimer.runCheck(curTime);
    }

    void ledFire()
    {
      // go through all LEDs
      for (int i = 0; i < NUM_LEDS; i++)
      {
        // 1/32 LEDs will turn white
        if (random(33))
        {
          // get current color
          CRGB lastcolor = leds[i];
          // get green component of RGB
          int green = lastcolor.g;
          // generate random number to subtract or add
          int rand = random(-51, 81);
          // change green component by random nr
          green += rand;

          // apply some mapping
          if (green > 255)
            green = 255;
          if (green < 0)
            green = 55;

          // set the LED to new color
          leds[i].setRGB(255, green, 0);
          // generate random number to set brightness
          int bright = random(128);
          // set brightness of LED
          leds[i].subtractFromRGB(bright);
        }
        else
        {
          // set LED to white
          leds[i].setRGB(200, 200, 100);
        }
      }
      // show LEDs
      FastLED.show();
      // add some random delay
      int randDelay = random(100, 250);
      //ledFireTimer.changeDelay(randDelay);
    } 
};
