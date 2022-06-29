#pragma once

#include <Arduino.h>
#include <Servo.h>
#include "Timer.h"

class ServoController
{
private:
    int pin;
    float minValue, maxValue;
    Servo servo;
    bool logScale;
    Timer servoDelay = Timer(100);

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
    @warning    If logarithmic scale is enabled, the minValue will be put to 0!
    @return ServoController object
    */
    ServoController(int pin, float minValue, float maxValue, bool log)
    {
        this->pin = pin;
        this->logScale = log;
        if (logScale)
            this->minValue = 0;
        else
            this->minValue = minValue;
        this->maxValue = maxValue;
        servo.attach(pin);
        // servo.write(90);
    }

    /*!
    @brief  Move the servo to specified position
    @param  value   Input value, will be mapped according to the min- and max value
    */
    void move(float value)
    {
        if (!logScale)
        {
            // normal linear mapping
            int position = map(value, minValue, maxValue, 0, 180);
            servo.write(position);
        }
        else
        {
            // logarithmic mapping
            int position = log(value + 1) / log(maxValue) * 180;
            servo.write(position);
        }
    }

    /*!
    @brief  Randomly jitter the servo
    */
    void jitter()
    {
        if (servoDelay.check(millis()))
        {
            // TODO: implement random jitter program (e.g. for launch)
            int randomPosition = random(45, 135);
            int randomDelay = random(50, 100);
            servo.write(randomPosition);
            servoDelay.changeDelay(randomDelay);
        }
    }
};