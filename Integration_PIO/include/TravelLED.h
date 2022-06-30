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
  int index = travelLEDnr - 1;
  CRGB leds[travelLEDnr];
  Timer travelLEDtimer = Timer(200);
  bool running = false;

public:
  /*!
  @brief Constructor for the Travel LED
  @note   dataPin cannot be defined in the constructor, do that in the class!!
  @return TravelLED object
  */
  TravelLED()
  {
    FastLED.addLeds<NEOPIXEL, travelLEDPin>(leds, travelLEDnr);
    turnOffAll();
  }

  /*!
  @brief Updates the travel time according to the distance
  @param  time Time it takes to to the planet
  */
  void setTravelTime(int time)
  {
    int delay = time / 24;
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
    turnOffAll();
    for (int i = travelLEDnr - 1; i > -1; i--)
    {
      if (i == index)
        leds[i].setRGB(250, 250, 250);
      if (i == index + 1 && index < travelLEDnr - 1)
        leds[i].setRGB(150, 150, 150);
      if (i == index + 2 && index < travelLEDnr - 2)
        leds[i].setRGB(100, 100, 100);
    }
    FastLED.show();

    if (index > -2)
      index--;
    else
      index = travelLEDnr - 1;
  }

  void turnOffAll()
  {
    for (int i = 0; i < travelLEDnr; i++)
    {
      leds[i] = CRGB::Black;
    }
  }
};
