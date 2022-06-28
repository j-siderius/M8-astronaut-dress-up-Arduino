/*
This program handles the thermometer leds
*/

#include <FastLED.h>
#include "Timer.h"

class TemperatureLED
{
private:
    /*
    Creates variables (variable for temperature should be passed from the serial to void turnon
    */
    int dataPin; 
    int numLeds = 16;
    CRGB leds[16];
    int temperature = 0;
    int brightness = 10;

public:
    /*!
    @brief Constructor for the temperature led strip
    @param  data_pin    The pin on which the strip is connected
    @return TemperatureLED object
    */
    TemperatureLED(int data_pin)
    {
        this->dataPin = data_pin;
    }
    /*!
    @brief Set the temperature of the LED strip
    @param  temperature     Value of the temperature
    */
    void setTemperature(int temperature) {
        this->temperature = temperature;
    }

    /*
    Turns leds on. Also pass temperature through this method
    */
    void turnOn()
    {
        int ledDisplay = numLeds * float(temperature + 200) / 700 + 1;
        for (int i = 0; i < int(ledDisplay); i++)
        {
            leds[i].r = i * brightness;
            leds[i].g = 1.5 * (numLeds / 2 - abs(numLeds / 2 - i)) * brightness;
            leds[i].b = (numLeds - i) * brightness;
        }
        FastLED.show();
    }
    /*
    Turns leds off.
    */
    void turnOff()
    {
        for (int i = 0; i < numLeds; i++)
        {
            leds[i].r = 0;
            leds[i].g = 0;
            leds[i].b = 0;
        }
        FastLED.show();
    }
};
