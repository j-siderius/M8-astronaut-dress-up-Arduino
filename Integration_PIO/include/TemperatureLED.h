#pragma once

#include <FastLED.h>

#define tempLEDPin 28
#define tempLEDnr 16

class TemperatureLED
{
private:
    CRGB leds[tempLEDnr];
    int temperature = 0;
    int brightness = 10;

public:
    /*!
    @brief Constructor for the temperature led strip
    @note   dataPin cannot be defined in the constructor, do that in the class!!
    @return TemperatureLED object
    */
    TemperatureLED()
    {
        FastLED.addLeds<NEOPIXEL, tempLEDPin>(leds, tempLEDnr);
        FastLED.clear(true);
    }

    /*!
    @brief Set the temperature of the LED strip
    @param  temperature     Value of the temperature
    */
    void setTemperature(int temperature) {
        this->temperature = temperature;
    }

    /*!
    @brief Turns leds on.
    */
    void turnOn()
    {
        int ledDisplay = tempLEDnr * float(temperature + 200) / 700 + 1;
        for (int i = 0; i < int(ledDisplay); i++)
        {
            leds[i].r = i * brightness;
            leds[i].g = 1.5 * (tempLEDnr / 2 - abs(tempLEDnr / 2 - i)) * brightness;
            leds[i].b = (tempLEDnr - i) * brightness;
        }
        FastLED.show();
    }
    
    /*!
    @brief Turns leds off.
    */
    void turnOff()
    {
        for (int i = 0; i < tempLEDnr; i++)
        {
            leds[i].r = 0;
            leds[i].g = 0;
            leds[i].b = 0;
        }
        FastLED.show();
    }
};
