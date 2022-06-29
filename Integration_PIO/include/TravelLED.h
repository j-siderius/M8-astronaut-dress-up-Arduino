#pragma once

// Class for the dynamic led strip indicating travelling time

#include <FastLED.h>
#include "Timer.h"

// define strip parameters
#include "PINS.h"
#define travelLEDnr 20

class TravelLED
{
private:
  int index = 0;
  CRGB leds[travelLEDnr];
  Timer travelLEDtimer = Timer(200);
  int maxTime;

public:
  /*!
  @brief Constructor for the Travel LED
  @param  maxTime Max time it may take to complete the travel path in ms
  @note   dataPin cannot be defined in the constructor, do that in the class!!
  @return TravelLED object
  */
  TravelLED(int maxTime)
  {
    this->maxTime = maxTime;

    FastLED.addLeds<NEOPIXEL, travelLEDPin>(leds, travelLEDnr);
    FastLED.clear();
  }

  /*!
  @brief Updates the travel time according to the distance
  @param  distance Distance to the planet
  */
  void setTravelTime(int distance) {
    int delay = (log(distance + 1) / log(5000) * maxTime) / 20;
    travelLEDtimer.changeDelay(delay);
  }

  /*!
  @brief Runs the travelTimer and updates if it is time
  */
  void run()
  {
    if (travelLEDtimer.check(millis()))
    {
      travelLED();
    }
  }

  /*!
  @brief  update the Travel LED
  */
  void travelLED()
  {
    // turn all LEDS off
    FastLED.clear(true);

    // set the LEDS to corresponding colors (incl followers)
    if (index < travelLEDnr)
      leds[index].setRGB(255, 255, 255);
    if (index > 0)
      leds[index - 1].setRGB(200, 200, 200);
    if (index > 1)
      leds[index - 2].setRGB(150, 150, 150);
    if (index > 2)
      leds[index - 3].setRGB(100, 100, 100);

    // increase the index if we did not finish the strip yet + tail length
    if (index < travelLEDnr + 3)
      index++;
    // reset the index to loop around (or set exiting function here)
    else
      index = 0;

    // show the LEDs
    FastLED.show();
  }
};
