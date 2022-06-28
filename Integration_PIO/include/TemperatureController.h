#pragma once

#include <Arduino.h>

class TemperatureController
{
private:
    int temperatureState = 0;
    int pinCold, pinHot;

public:
    /*!
      @brief  TemperatureController contructor initializes the pins and turns them off by default
      @param  pinCold  Pin where the cold element is attached
      @param  pinHot  Pin where the hot element is attached
      @return TemperatureController object
    */
    TemperatureController(int pinCold, int pinHot)
    {
        this->pinCold = pinCold;
        this->pinHot = pinHot;

        pinMode(pinCold, OUTPUT);
        digitalWrite(pinCold, LOW);
        pinMode(pinHot, OUTPUT);
        digitalWrite(pinHot, LOW);
    }

    /*!
      @brief  Set the temperature
      @param  temperature temperature to be set (in granular scale: 0, 1, 2)
    */
    void setTemperature(int temperature)
    {
        this->temperatureState = temperature;
    }

    /*!
      @brief  Turn on the temperature according to the temperature scale
    */
    void tempOn()
    {
        // calculate the human perception
        if (temperatureState == 0)
        {
            // too cold
            digitalWrite(pinCold, HIGH);
        }
        else if (temperatureState == 1)
        {
            // normal
            digitalWrite(pinCold, HIGH);
            digitalWrite(pinHot, HIGH);
        }
        else if (temperatureState == 2)
        {
            // too hotÌ
            digitalWrite(pinHot, HIGH);
        }
    }

    /*!
      @brief  Turn off all temperature sources
    */
    void tempOff()
    {
        digitalWrite(pinCold, LOW);
        digitalWrite(pinHot, LOW);
    }
};
