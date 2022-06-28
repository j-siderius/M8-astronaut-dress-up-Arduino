#include <Arduino.h>

#include "Timer.h"
#include <FastLED.h>

#define ringLEDPin 31
#define ringLEDnr 20

class FireRing
{
private:
    //  initialize LED array
    CRGB leds[ringLEDnr];
    Timer ledFireTimer = Timer(100, ledFire);

public:

    /*!
    @brief  Constructor for the Fire Ring
    @note   dataPin cannot be defined in the constructor, do that in the class!!
    @return Fire ring object
    */
    FireRing()
    {
        // initialize LEDs
        FastLED.addLeds<NEOPIXEL, ringLEDPin>(leds, ringLEDnr);
        // give each LED a starting color
        for (int i = 0; i < ringLEDnr; i++)
        {
            // generate random number for green component
            int g = random(0, 256);
            // set LED to default red and random green component
            leds[i].setRGB(255, g, 0);
        }

        FastLED.clear(true);
        // show LEDs
        FastLED.show();
    }

    /*!
    @brief Runs the fire ring and updates if it is time
    */
    void run()
    {
        unsigned long curTime = millis();
        ledFireTimer.runCheck(curTime);
    }

    /*!
    @brief  Update the fire ring
    */
    void ledFire()
    {
        // go through all LEDs
        for (int i = 0; i < ringLEDnr; i++)
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
        ledFireTimer.changeDelay(randDelay);
    }
};
