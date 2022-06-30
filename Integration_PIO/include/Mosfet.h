#pragma once

#include <Arduino.h>

class Mosfet {
  private:
    int pin;
  public:
    /*!
      @brief  Constructor for mostfet driver
      @param  pin Pin where the mosfet is connected
      @returns    Mosfet class object
    */
    Mosfet(int pin) {
      this->pin = pin;
    }

/**
 * @brief setup the pins
 * 
 */
    void begin() {
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
    }

    /*!
      @brief  turns the Mosfet on
    */
    void turnOn() {
      digitalWrite(pin, HIGH);
    }

    /*!
      @brief  turns the Mosfet on
    */
    void turnOff() {
      digitalWrite(pin, LOW);
    }
};
