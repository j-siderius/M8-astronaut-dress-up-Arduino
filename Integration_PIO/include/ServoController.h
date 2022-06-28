#pragma once

#include <Arduino.h>
#include <Servo.h>

class ServoController
{
private:
    int pin;
    float minValue, maxValue;
    Servo servo;
    bool logScale;

public:
    /*!
    @brief  Constructor for the servo
    @param  pin         Pin where the servo is connected
    @param  minValue    Minimal expected value to be passed to this servo / dial
    @param  maxValue    Maximal expected value to be passed to this servo / dial
    @return ServoController object
    */
    ServoController(int pin, float minValue, float maxValue)
    {
        this->pin = pin;
        this->minValue = minValue;
        this->maxValue = maxValue;
        this->logScale = false;
        servo.attach(pin);
        servo.write(90);
    }

    /*!
    @brief  Constructor for the servo
    @param  pin         Pin where the servo is connected
    @param  minValue    Minimal expected value to be passed to this servo / dial
    @param  maxValue    Maximal expected value to be passed to this servo / dial
    @param  log         Boolean for enabling log mapping
    @return ServoController object
    */
    ServoController(int pin, float minValue, float maxValue, bool log)
    {
        this->pin = pin;
        this->minValue = minValue;
        this->maxValue = maxValue;
        this->logScale = log;
        servo.attach(pin);
        servo.write(90);
    }

    /*!
    @brief  Move the servo to specified position
    @param  value   Input value, will be mapped according to the min- and max value
    @warning    When using logaritmic scaling, minValue should be above 0
    */
    void move(float value)
    {
        if (!logScale)
        {
            int position = map(value, minValue, maxValue, 0, 180);
            servo.write(position);
        } else {
            int position = log(value + 1) / log(maxValue) * 180;
            servo.write(position);
        }
    }
};