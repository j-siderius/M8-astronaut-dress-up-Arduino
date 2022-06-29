#pragma once

#include <Arduino.h>

class Multiplexer
{
private:
    int selectPins[3];
    int readPin1;
    int readPin2 = 0;
    int arraySize;
    float inputs8[8];
    float inputs16[16];
    int changeThreshold;
    bool changed = false;
    float calibrationValues[16] = {750, 750, 750, 750, 750, 750, 750, 750, 750, 750, 750, 750, 750, 750, 750, 750};

public:
    /*!
    @brief  Constructor for the multiplexer class, define pins here
    @param  mPin1   Multiplexer pin 1
    @param  mPin2   Multiplexer pin 2
    @param  mPin3   Multiplexer pin 3
    @param  aPin    Multiplexer read pin
    @param  changeThreshold When a change is detected
    @return Multiplexer object
    */
    Multiplexer(int mPin1, int mPin2, int mPin3, int aPin, int changeThreshold)
    {
        this->selectPins[0] = mPin1;
        this->selectPins[1] = mPin2;
        this->selectPins[2] = mPin3;
        this->readPin1 = aPin;
        this->arraySize = 8;
        this->changeThreshold = changeThreshold;

        pinMode(selectPins[0], OUTPUT);
        pinMode(selectPins[1], OUTPUT);
        pinMode(selectPins[2], OUTPUT);
        digitalWrite(selectPins[0], LOW);
        digitalWrite(selectPins[1], LOW);
        digitalWrite(selectPins[2], LOW);
        pinMode(readPin1, INPUT);
    }

    /*!
    @brief  Constructor for the multiplexer class, define pins here
    @param  mPin1   Multiplexer pin 1
    @param  mPin2   Multiplexer pin 2
    @param  mPin3   Multiplexer pin 3
    @param  aPin1    Multiplexer read pin 1
    @param  aPin2    Multiplexer read pin 2
    @param  changeThreshold When a change is detected
    @return Multiplexer object
    */
    Multiplexer(int mPin1, int mPin2, int mPin3, int aPin1, int aPin2, int changeThreshold)
    {
        this->selectPins[0] = mPin1;
        this->selectPins[1] = mPin2;
        this->selectPins[2] = mPin3;
        this->readPin1 = aPin1;
        this->readPin2 = aPin2;
        this->arraySize = 16;
        this->changeThreshold = changeThreshold;

        pinMode(selectPins[0], OUTPUT);
        pinMode(selectPins[1], OUTPUT);
        pinMode(selectPins[2], OUTPUT);
        digitalWrite(selectPins[0], LOW);
        digitalWrite(selectPins[1], LOW);
        digitalWrite(selectPins[2], LOW);
        pinMode(readPin1, INPUT);
        pinMode(readPin2, INPUT);
    }

    /*!
    @brief  Read the multiplexer out and store values in array
    */
    void readMux()
    {
        if (arraySize == 8)
        {
            for (byte pin = 0; pin <= 7; pin++)
            {
                selectMuxPin(pin);                        // Select pin
                float measurement = analogRead(readPin1); // and read analog value
                float curValue = inputs8[pin];
                // check if the change is significant
                if (measurement > curValue + changeThreshold || measurement < curValue - changeThreshold)
                {
                    inputs8[pin] = measurement;
                    changed = true;
                }
            }
        }
        else if (arraySize == 16)
        {
            for (byte pin = 0; pin <= 7; pin++)
            {
                selectMuxPin(pin); // Select pin

                float measurement1 = analogRead(readPin1); // and read analog value
                float curValue1 = inputs16[pin];
                // check if the change is significant
                if (measurement1 > curValue1 + changeThreshold || measurement1 < curValue1 - changeThreshold)
                {
                    inputs8[pin] = measurement1;
                    changed = true;
                }

                float measurement2 = analogRead(readPin2); // and read analog value
                float curValue2 = inputs16[pin + 8];
                // check if the change is significant
                if (measurement2 > curValue2 + changeThreshold || measurement2 < curValue2 - changeThreshold)
                {
                    inputs8[pin + 2] = measurement2;
                    changed = true;
                }
            }
        }
    }

    /*!
    @brief  Function to fetch the values of the multiplexer array
    @return Array of LDR values, boolean gives either HIGH or LOW
    */
    bool readValues()
    {
        if (arraySize == 8)
        {
            changed = false;
            bool values[8];
            for (int i = 0; i < 8; i++) {
                if (inputs8[i] > calibrationValues[i]) values[i] = true;
                else values[i] = false;
            }
            return values;
        }
        else if (arraySize == 16)
        {
            changed = false;
            bool values[16];
            for (int i = 0; i < 16; i++) {
                if (inputs16[i] > calibrationValues[i]) values[i] = true;
                else values[i] = false;
            }
            return values;
        }
        else
        {
            return 0;
        }
    }

    // The selectMuxPin function sets the S0, S1, and S2 pins
    // accordingly, given a pin from 0-7.
    /*!
    @brief  Select a specific pin on the multiplexer
    @param  pin which pin to select
    */
    void selectMuxPin(byte pin)
    {
        for (int i = 0; i < 3; i++)
        {
            if (pin & (1 << i))
                digitalWrite(selectPins[i], HIGH);
            else
                digitalWrite(selectPins[i], LOW);
        }
    }

    /**
     * @brief check if the array has changed since the last check
     * @return true or false
     */
    bool hasChanged()
    {
        return changed;
    }

    /**
     * @brief Set the Calibration Values of the multiplexer (should be in the middle of LOW and HIGH measurement)
     * @param calibration  array of calibration values
     * @note even if calibrating a 8x multiplexer, pass an array with 16 spots, just leave last 8 empty
     */
    void setCalibrationValues(float calibration[16])
    {
        for (int i = 0; i < 16; i++)
        {
            calibrationValues[i] = calibration[i];
        }
    }
};