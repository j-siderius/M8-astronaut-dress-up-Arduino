#pragma once

#include <FastLED.h>

// define stip parameters
#include "PINS.h"
#define generalLEDNr 150

class GeneralLight
{
private:
  CRGB leds[generalLEDNr];

  uint16_t WHITE = 0xFFFF;
  uint16_t RED = 0xF800;
  uint16_t GREEN = 0x07E0;
  uint16_t BLUE = 0x001F;

  int brightness[4] = {255, 255, 255, 255};
  int lowerDivision = 4;
  int middleDivision = 8;
  int upperDivision = 12;

public:
  /*!
  @brief Constructor for the General LED
  @note   dataPin cannot be defined in the constructor, do that in the class!!
  @return GeneralLED object
  */
  GeneralLight()
  {
    FastLED.addLeds<NEOPIXEL, generalLEDPin>(leds, generalLEDNr);
    FastLED.clear();
  }

  /*!
  @brief  Control lighting of Group 1
  @param  completed sets the lighting section to complete or not
  */
  void group1Lighting(bool completed)
  {
    if (completed)
    {
      for (int i = 0; i < lowerDivision; i++)
      {
        leds[i] = GREEN;
        leds[i].subtractFromRGB(255 - brightness[0]);
      }
    }
    else
    {
      for (int i = 0; i < lowerDivision; i++)
      {
        leds[i] = RED;
        leds[i].subtractFromRGB(255 - brightness[0]);
      }
    }
    FastLED.show();
  }

  /*!
  @brief  Control lighting of Group 2
  @param  completed sets the lighting section to complete or not
  */
  void group2Lighting(int completed)
  {
    if (completed)
    {
      for (int i = lowerDivision; i < middleDivision; i++)
      {
        leds[i] = GREEN;
        leds[i].subtractFromRGB(255 - brightness[1]);
      }
    }
    else
    {
      for (int i = lowerDivision; i < middleDivision; i++)
      {
        leds[i] = RED;
        leds[i].subtractFromRGB(255 - brightness[1]);
      }
    }
    FastLED.show();
  }

  /*!
  @brief  Control lighting of Group 3
  @param  completed sets the lighting section to complete or not
  */
  void group3Lighting(int completed)
  {
    if (completed)
    {
      for (int i = middleDivision; i < upperDivision; i++)
      {
        leds[i] = GREEN;
        leds[i].subtractFromRGB(255 - brightness[2]);
      }
    }
    else
    {
      for (int i = middleDivision; i < upperDivision; i++)
      {
        leds[i] = RED;
        leds[i].subtractFromRGB(255 - brightness[2]);
      }
    }
    FastLED.show();
  }

  /*!
  @brief  Control lighting of Group 4
  @param  completed sets the lighting section to complete or not
  */
  void group4Lighting(int completed)
  {
    if (completed)
    {
      for (int i = upperDivision; i < generalLEDNr; i++)
      {
        leds[i] = GREEN;
        leds[i].subtractFromRGB(255 - brightness[3]);
      }
    }
    else
    {
      for (int i = upperDivision; i < generalLEDNr; i++)
      {
        leds[i] = RED;
        leds[i].subtractFromRGB(255 - brightness[3]);
      }
    }
    FastLED.show();
  }

  /*!
  @brief  Set the brightness of a group of LEDs
  @param  group Select the group to change
  @param  brightness  Bightness value between 0 and 255
  */
  void setBrightness(int group, int bright)
  {
    if (group > 0 && group < 5)
    {
      brightness[(group - 1)] = bright;
    }
  }
};
