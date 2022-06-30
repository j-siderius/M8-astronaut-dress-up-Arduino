#include <Arduino.h>

#include <FastLED.h>

#define toxicityLEDPin 12
#define toxicityLEDNr 6

int comp1[] = {10, 0, 20, 100, 0, 30};
int comp2[] = {0, 0, 0, 1, 80, 19};

class ElementsLED {
  private:
    CRGB leds[toxicityLEDNr];

    int CO2Pos, N2Pos, O2Pos, CH4Pos, H2Pos, HEPos;
    int CO2Percent, N2Percent, O2Percent, CH4Percent, H2Percent, HEPercent;
    int brightnessPLED[6] = {1, 1, 1, 1, 1, 1};

  public:
  //Constructor
    ElementsLED(int CO2Pos, int N2Pos, int O2Pos, int CH4Pos, int H2Pos, int HEPos) {
      this->CO2Pos = CO2Pos;
      this->N2Pos = N2Pos;
      this->O2Pos = O2Pos;
      this->CH4Pos = CH4Pos;
      this->H2Pos = H2Pos;
      this->HEPos = HEPos;

      FastLED.addLeds<NEOPIXEL, toxicityLEDPin>(leds, toxicityLEDNr);
      FastLED.clear();
    }

    //Turn on leds
    void displayElements() {
      FastLED.clear();
      leds[CO2Pos].r = CO2Percent * brightnessPLED[0];
      leds[N2Pos].r = N2Percent * brightnessPLED[1];
      leds[O2Pos].r = O2Percent * brightnessPLED[2];
      leds[CH4Pos].r = CH4Percent * brightnessPLED[3];
      leds[H2Pos].r = H2Percent * brightnessPLED[4];
      leds[HEPos].r = HEPercent * brightnessPLED[5];
      leds[CO2Pos].g = CO2Percent * brightnessPLED[0];
      leds[N2Pos].g = N2Percent * brightnessPLED[1];
      leds[O2Pos].g = O2Percent * brightnessPLED[2];
      leds[CH4Pos].g = CH4Percent * brightnessPLED[3];
      leds[H2Pos].g = H2Percent * brightnessPLED[4];
      leds[HEPos].g = HEPercent * brightnessPLED[5];
      leds[CO2Pos].b = CO2Percent * brightnessPLED[0];
      leds[N2Pos].b = N2Percent * brightnessPLED[1];
      leds[O2Pos].b = O2Percent * brightnessPLED[2];
      leds[CH4Pos].b = CH4Percent * brightnessPLED[3];
      leds[H2Pos].b = H2Percent * brightnessPLED[4];
      leds[HEPos].b = HEPercent * brightnessPLED[5];
      FastLED.show();
    }

    //Turn off leds
    void turnOffElements() {
      FastLED.clear();
      leds[CO2Pos].r = 0;
      leds[N2Pos].r = 0;
      leds[O2Pos].r = 0;
      leds[CH4Pos].r = 0;
      leds[H2Pos].r = 0;
      leds[HEPos].r = 0;
      leds[CO2Pos].g = 0;
      leds[N2Pos].g = 0;
      leds[O2Pos].g = 0;
      leds[CH4Pos].g = 0;
      leds[H2Pos].g = 0;
      leds[HEPos].g = 0;
      leds[CO2Pos].b = 0;
      leds[N2Pos].b = 0;
      leds[O2Pos].b = 0;
      leds[CH4Pos].b = 0;
      leds[H2Pos].b = 0;
      leds[HEPos].b = 0;
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

    /*
    void setGranular(int oxygen, int toxicity) {
      if (oxygen == 0) {
        O2Percent = 0;
      }
      if (toxicity == 0) {
        CO2Percent = 0;
        CH4Percent = 0;
      }
    }
    */
};

ElementsLED toxicity = ElementsLED(5, 4, 3, 0, 2, 1);

void setup() {
  Serial.begin(9600);
  Serial.print("starting");
}

void loop() {

  toxicity.setPercentages(comp2);
  toxicity.displayElements();
}
