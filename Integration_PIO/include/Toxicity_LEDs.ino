#include <Arduino.h>

#include <FastLED.h>

#define toxicityLEDPin 12
#define toxicityLEDNr 6

int comp1[] = {10, 0, 20, 100, 0, 30};
int comp2[] = {0, 0, 0, 1, 80, 19};

class ToxicityLED {
  private:
    CRGB leds[toxicityLEDNr];

    int CO2Pos, N2Pos, O2Pos, CH4Pos, H2Pos, HEPos;
    int CO2Percent, N2Percent, O2Percent, CH4Percent, H2Percent, HEPercent;
    int brightnessPLED[6] = {1, 1, 1, 1, 1, 1};
    int brightness = 0;

  public:
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
      FastLED.clear();
      leds[CO2Pos].r = CO2Percent * brightnessPLED[0];
      leds[N2Pos].r = N2Percent * brightnessPLED[1];
      leds[O2Pos].r = O2Percent * brightnessPLED[2];
      leds[CH4Pos].r = CH4Percent * brightnessPLED[3];
      leds[H2Pos].r = H2Percent * brightnessPLED[4];
      leds[HEPos].r = HEPercent * brightnessPLED[5];
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
      return (HEPercent);
    }
};

ToxicityLED toxicity = ToxicityLED(5, 4, 3, 0, 2, 1);

void setup() {
  Serial.begin(9600);
  Serial.print("starting");
}

void loop() {
  
  toxicity.setTotalBrightness(255);
  toxicity.setPercentages(comp2);
  toxicity.displayToxicity();
}
