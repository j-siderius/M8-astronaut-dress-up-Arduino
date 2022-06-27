#pragma once

#include <Arduino.h>
#include "Mosfet.h"

class TemperatureController {
  private:
    int temperatureState;

  public:
    /*!
      @brief  TemperatureController contructor initializes the pins and turns them off by default
      @param  pinCold  Pin where the cold element is attached
      @param  pinHot  Pin where the hot element is attached
      @return TemperatureController object
    */
    TemperatureController(int pinCold, in pinHot) {
      Mosfet cold = Mosfet(pinCold);
      Mosfet hot = Mosfet(pinHot);
      cold.turnOff();
      hot.turnOff();
      this->temperature = 0;
    }

    /*!
      @brief  Set the temperature
      @param  temperature temperature to be set (in granular scale: -1, 0, 1)
    */
    void setTemperature(int temperature) {
      this->temperature = temperature;
    }

    /*!
      @brief  Turn on the temperature according to the temperature scale
    */
    void tempOn() {
      // calculate the human perception
      if (temperature == -1) {
        // too cold
        cold.turnOn();
      } else if (temperature == 0) {
        // normal
        cold.turnOn();
        hot.turnOn();
      } else if (temperature == 1) {
        // too hot
        hot.turnOn();
      }
    }

    /*!
      @brief  Turn off all temperature sources
    */
    void turnOff() {
      cold.turnOff();
      hot.turnOff();
    }
};
