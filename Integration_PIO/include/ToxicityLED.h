#pragma once

#include <Arduino.h>
#include <FastLED.h>

#include "PINS.h"
#define toxicityLEDNr 6

class ToxicityLED {
  private:
    CRGB leds[toxicityLEDNr];

    int CO2Pos, N2Pos, O2Pos, CH4Pos, H2Pos, HEPos;
    int CO2Percent, N2Percent, O2Percent, CH4Percent, H2Percent, HEPercent;
    int brightnessPLED[6] = {1, 1, 1, 1, 1, 1};
    int brightness = 0;

  public:
  /**
   * @brief Construct a new Toxicity L E D object
   * 
   * @param CO2Pos Value for CO2
   * @param N2Pos etc
   * @param O2Pos 
   * @param CH4Pos 
   * @param H2Pos 
   * @param HEPos 
   */
    ToxicityLED(int CO2Pos, int N2Pos, int O2Pos, int CH4Pos, int H2Pos, int HEPos) {
      this->CO2Pos = CO2Pos;
      this->N2Pos = N2Pos;
      this->O2Pos = O2Pos;
      this->CH4Pos = CH4Pos;
      this->H2Pos = H2Pos;
      this->HEPos = HEPos;

      FastLED.addLeds<NEOPIXEL, toxicityLEDPin>(leds, toxicityLEDNr);
      FastLED.clear();
    }

    void displayToxicity() {
      leds[CO2Pos] = CO2Percent * brightnessPLED[0];
      leds[N2Pos] = N2Percent * brightnessPLED[1];
      leds[O2Pos] = O2Percent * brightnessPLED[2];
      leds[CH4Pos] = CH4Percent * brightnessPLED[3];
      leds[H2Pos] = H2Percent * brightnessPLED[4];
      leds[HEPos] = HEPercent * brightnessPLED[5];
      for (int i = 0; i < toxicityLEDNr; i++) {
        leds[i].subtractFromRGB(255 - brightness);
      }
      FastLED.show();
    }

    void setPercentages(int percentages[6]) {
      CO2Percent = percentages [0];
      N2Percent = percentages [1];
      O2Percent = percentages [2];
      CH4Percent = percentages [3];
      H2Percent = percentages [4];
      HEPercent = percentages [5];
    }

    void setTotalBrightness(int bright) {
      brightness = bright;
    }

    void setGranular(int oxygen, int toxicity) {
      if (oxygen == 0) {
        O2Percent = 0;
      }
      if (toxicity == 0) {
        CO2Percent = 0;
        CH4Percent = 0;
      }
    }

    int returnValue() {
      return (CO2Percent);
    }
};