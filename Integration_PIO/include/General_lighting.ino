#include <FastLED.h>

#define generalLEDNr 15
#define generalLEDPin 3

class GeneralLight {
  private:
    CRGB leds[generalLEDNr];

    uint16_t WHITE   = 0xFFFF;
    uint16_t RED     = 0xF800;
    uint16_t GREEN   = 0x07E0;
    uint16_t BLUE     = 0x001F;

    int brightness1 = 255;
    int brightness2 = 255;
    int brightness3 = 255;
    int brightness4 = 255;
    int lowerDivision = 4;
    int middleDivision = 8;
    int upperDivision = 12;

  public:
    GeneralLight() {
      FastLED.addLeds<WS2811, generalLEDPin, BGR>(leds, generalLEDNr);
      FastLED.clear(true);
    }
    void group1Lighting(int completed) {
      if (completed) {
        for (int i = 0; i < lowerDivision; i++) {
          leds[i] = GREEN;
          leds[i].subtractFromRGB(255 - brightness1);
        }
      } else {
        for (int i = 0; i < lowerDivision; i++) {
          leds[i] = RED;
          leds[i].subtractFromRGB(255 - brightness1);
        }
      }
      FastLED.show();
    }

    void group2Lighting(int completed) {
      if (completed) {
        for (int i = lowerDivision; i < middleDivision; i++) {
          leds[i] = GREEN;
          leds[i].subtractFromRGB(255 - brightness2);
        }
      } else {
        for (int i = lowerDivision; i < middleDivision; i++) {
          leds[i] = RED;
          leds[i].subtractFromRGB(255 - brightness2);
        }
      }
      FastLED.show();
    }

    void group3Lighting(int completed) {
      if (completed) {
        for (int i = middleDivision; i < upperDivision; i++) {
          leds[i] = GREEN;
          leds[i].subtractFromRGB(255 - brightness3);
        }
      } else {
        for (int i = middleDivision; i < upperDivision; i++) {
          leds[i] = RED;
          leds[i].subtractFromRGB(255 - brightness3);
        }
      }
      FastLED.show();
    }

    void group4Lighting(int completed) {
      if (completed) {
        for (int i = upperDivision; i < generalLEDNr; i++) {
          leds[i] = GREEN;
          leds[i].subtractFromRGB(255 - brightness4);
        }
      } else {
        for (int i = upperDivision; i < generalLEDNr; i++) {
          leds[i] = RED;
          leds[i].subtractFromRGB(255 - brightness4);
        }
      }
      FastLED.show();
    }
}

GeneralLight general = GeneralLight();

void setup() {
  // put your setup code here, to run once:
  //general.initialize();
}

void loop() {
  // put your main code here, to run repeatedly:
  general.group1Lighting(true);
  general.group2Lighting(true);
  general.group3Lighting(true);
  general.group4Lighting(false);

  delay(1000);
  general.brightness2 = 0;
}
