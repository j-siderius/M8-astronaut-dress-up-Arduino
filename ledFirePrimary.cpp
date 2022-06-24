#include <Arduino.h>

#include "Timer.h"

#include <FastLED.h>
#define NUM_LEDS 16
#define DATA_PIN 8

void ledFire();
void ledFireInit();

// initialize LED array
CRGB leds[NUM_LEDS];
Timer ledFireTimer = Timer(100, ledFire);

void setup()
{
  Serial.begin(9600);

  ledFireInit();
}

void loop()
{
  unsigned long curTime = millis();
  ledFireTimer.runCheck(curTime);
}

void ledFire()
{
  // go through all LEDs
  for (int i = 0; i < NUM_LEDS; i++)
  {
    // 1/8 LEDs will turn white
    if (random(9))
    {
      // get current color
      CRGB lastcolor = leds[i];
      // get green component of RGB
      int green = lastcolor.g;
      // generate random number to subtract or add
      int rand = random(-50, 81);
      // change green component by random nr
      green += rand;

      // apply some mapping
      if (green > 255)
        green = 255;
      if (green < 0)
        green = 0;

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
      leds[i].setRGB(255, 255, 255);
    }
  }
  // show LEDs
  FastLED.show();
  // add some random delay
  int randDelay = random(50, 150);
  ledFireTimer.changeDelay(randDelay);
}

void ledFireInit()
{
  // initialize LEDs
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
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
