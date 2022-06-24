#include <FastLED.h>
#include <Timer.h>
#define NUM_LEDS 16
#define DATA_PIN 13

CRGB leds[NUM_LEDS];

int temperature;
int brightness;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  temperature = 500;
  brightness = 1;
}

void loop() {
  turnOn();
  Timer(500);
  turnOff();
  Timer(500);

}

void turnOn() {
  int ledDisplay = NUM_LEDS * float(temperature + 200) / 700 + 1;
  Serial.println (ledDisplay);
  for (int i = 0; i < int(ledDisplay); i++) {
    leds[i].r = i * brightness;
    leds[i].g = 1.5 * (NUM_LEDS/2 - abs(NUM_LEDS/2 - i)) * brightness;
    leds[i].b = (NUM_LEDS - i) * brightness;
  }
  FastLED.show();
}

void turnOff() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].r = 0;
    leds[i].g = 0;
    leds[i].b = 0;
  }
  FastLED.show();
}
