#pragma once

#include <Arduino.h>

class Mosfet {
  private:
    int dPin;
  public:
    /*!
      @brief  Constructor for mostfet driver
      @param  pin Pin where the mosfet is connected
      @returns    Mosfet class object
    */
    Mosfet(int dPin) {
      this->dPin = dPin;
      pinMode(dPin, OUTPUT);
      digitalWrite(dPin, LOW);
    }

    /*!
      @brief  turns the Mosfet on
    */
    void turnOn() {
      digitalWrite(dPin, HIGH);
    }

    /*!
      @brief  turns the Mosfet on
    */
    void turnOff() {
      digitalWrite(dPin, LOW);
    }
};
