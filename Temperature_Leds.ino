#include <FastLED.h>
#include <Timer.h>
#define NUM_LEDS 8
#define DATA_PIN 3

CRGB leds[NUM_LEDS];

int temperature;
int brightness;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  temperature = 0;
  brightness = 2;
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
    leds[i].g = (4 - abs(4 - i)) * brightness;
    leds[i].b = (8 - i) * brightness;
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
