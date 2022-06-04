#include <FastLED.h>
#define NUM_LEDS 16
#define DATA_PIN 8

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    int g = random(0, 256);
    leds[i].setRGB(255, g, 0);
  }
  FastLED.show();
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (random(5)) {
      CRGB lastcolor = leds[i];
      int green = lastcolor.g;
      int rand = random(-100, 101);
      green += rand;

      if (green > 255) green = 255;
      if (green < 0) green = 0;

      leds[i].setRGB(255, green, 0);
    } else {
      leds[i].setRGB(255, 255, 255);
    }
  }
  FastLED.show(); 
  delay(random(50, 150));
}
