#pragma once

#include <FastLED.h>

// define stip parameters
#include "PINS.h"
#define generalLEDNr 118

class GeneralLight
{
private:
  CRGB leds[generalLEDNr];

  uint16_t WHITE = 0xFFFF;
  uint16_t RED = 0xF800;
  uint16_t GREEN = 0x07E0;
  uint16_t BLUE = 0x001F;

  // int brightness[4] = {255, 255, 255, 255};
  // int lowerDivision = 4;
  // int middleDivision = 8;
  // int upperDivision = 12;

  // starting LED of each group of LEDs (total 5 groups + end of stip)
  /*
   *           ---3---
   *         2         4
   * ___1___/           \___5___
   *
   *            FRONT
   */
  int groups[6] = {0, 20, 38, 83, 101, 118};

public:
  /*!
  @brief Constructor for the General LED
  @note   dataPin cannot be defined in the constructor, do that in the class!!
  @return GeneralLED object
  */
  GeneralLight()
  {
    FastLED.addLeds<NEOPIXEL, generalLEDPin>(leds, generalLEDNr);
    turnOffAll();
  }

  /**
   * @brief colours a group of LEDs
   *
   * @param group group number (1-5)
   * @param r Red value
   * @param g Green value
   * @param b Blue value
   */
  void colourGroup(int group, int r, int g, int b)
  {
    int nrLeds = groups[group + 1] - groups[group];
    for (int i = 0; i < nrLeds; i++)
    {
      leds[i].setRGB(r, g, b);
    }
    FastLED.show();
  }

  /**
   * @brief turn a group fully Red
   * 
   * @param group group number (1-5)
   */
  void groupRed(int group) {
    int nrLeds = groups[group + 1] - groups[group];
    for (int i = 0; i < nrLeds; i++)
    {
      leds[i] = RED;
    }
    FastLED.show();
  }

  /**
   * @brief turn a group fully Green
   * 
   * @param group group number (1-5)
   */
  void groupGreen(int group) {
    int nrLeds = groups[group + 1] - groups[group];
    for (int i = 0; i < nrLeds; i++)
    {
      leds[i] = GREEN;
    }
    FastLED.show();
  }

  /**
   * @brief turn a group fully Blue
   * 
   * @param group group number (1-5)
   */
  void groupBlue(int group) {
    int nrLeds = groups[group + 1] - groups[group];
    for (int i = 0; i < nrLeds; i++)
    {
      leds[i] = BLUE;
    }
    FastLED.show();
  }

  /**
   * @brief turn a group fully White
   * 
   * @param group group number (1-5)
   */
  void groupWhite(int group) {
    int nrLeds = groups[group + 1] - groups[group];
    for (int i = 0; i < nrLeds; i++)
    {
      leds[i] = WHITE;
    }
    FastLED.show();
  }

  /**
   * @brief Set the Brightness of the full strip
   *
   * @param bright value between 0 and 255 for brightness
   */
  void setBrightness(int bright)
  {
    FastLED.setBrightness(bright);
  }

  /**
   * @brief turn off all LEDs on the strip
   *
   */
  void turnOffAll()
  {
    for (int i = 0; i < generalLEDNr; i++)
    {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
  }

  // /*!
  // @brief  Control lighting of Group 1
  // @param  completed sets the lighting section to complete or not
  // */
  // void group1Lighting(bool completed)
  // {
  //   if (completed)
  //   {
  //     for (int i = 0; i < lowerDivision; i++)
  //     {
  //       leds[i] = GREEN;
  //       leds[i].subtractFromRGB(255 - brightness[0]);
  //     }
  //   }
  //   else
  //   {
  //     for (int i = 0; i < lowerDivision; i++)
  //     {
  //       leds[i] = RED;
  //       leds[i].subtractFromRGB(255 - brightness[0]);
  //     }
  //   }
  //   FastLED.show();
  // }

  // /*!
  // @brief  Control lighting of Group 2
  // @param  completed sets the lighting section to complete or not
  // */
  // void group2Lighting(int completed)
  // {
  //   if (completed)
  //   {
  //     for (int i = lowerDivision; i < middleDivision; i++)
  //     {
  //       leds[i] = GREEN;
  //       leds[i].subtractFromRGB(255 - brightness[1]);
  //     }
  //   }
  //   else
  //   {
  //     for (int i = lowerDivision; i < middleDivision; i++)
  //     {
  //       leds[i] = RED;
  //       leds[i].subtractFromRGB(255 - brightness[1]);
  //     }
  //   }
  //   FastLED.show();
  // }

  // /*!
  // @brief  Control lighting of Group 3
  // @param  completed sets the lighting section to complete or not
  // */
  // void group3Lighting(int completed)
  // {
  //   if (completed)
  //   {
  //     for (int i = middleDivision; i < upperDivision; i++)
  //     {
  //       leds[i] = GREEN;
  //       leds[i].subtractFromRGB(255 - brightness[2]);
  //     }
  //   }
  //   else
  //   {
  //     for (int i = middleDivision; i < upperDivision; i++)
  //     {
  //       leds[i] = RED;
  //       leds[i].subtractFromRGB(255 - brightness[2]);
  //     }
  //   }
  //   FastLED.show();
  // }

  // /*!
  // @brief  Control lighting of Group 4
  // @param  completed sets the lighting section to complete or not
  // */
  // void group4Lighting(int completed)
  // {
  //   if (completed)
  //   {
  //     for (int i = upperDivision; i < generalLEDNr; i++)
  //     {
  //       leds[i] = GREEN;
  //       leds[i].subtractFromRGB(255 - brightness[3]);
  //     }
  //   }
  //   else
  //   {
  //     for (int i = upperDivision; i < generalLEDNr; i++)
  //     {
  //       leds[i] = RED;
  //       leds[i].subtractFromRGB(255 - brightness[3]);
  //     }
  //   }
  //   FastLED.show();
  // }

  // /*!
  // @brief  Set the brightness of a group of LEDs
  // @param  group Select the group to change
  // @param  brightness  Bightness value between 0 and 255
  // */
  // void setBrightness(int group, int bright)
  // {
  //   if (group > 0 && group < 5)
  //   {
  //     brightness[(group - 1)] = bright;
  //   }
  // }
};
