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

public:
    /*!
    @brief  Constructor for the multiplexer class, define pins here
    @param  mPin1   Multiplexer pin 1
    @param  mPin2   Multiplexer pin 2
    @param  mPin3   Multiplexer pin 3
    @param  aPin    Multiplexer read pin
    @param  arraySize   Size of multiplexer array, should be 8 or 16
    @return Multiplexer object
    */
    Multiplexer(int mPin1, int mPin2, int mPin3, int aPin, int arraySize)
    {
        this->selectPins[0] = mPin1;
        this->selectPins[1] = mPin2;
        this->selectPins[2] = mPin3;
        this->readPin1 = aPin;
        this->arraySize = arraySize;

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
    @param  arraySize   Size of multiplexer array, should be 8 or 16!
    @return Multiplexer object
    */
    Multiplexer(int mPin1, int mPin2, int mPin3, int aPin1, int aPin2, int arraySize)
    {
        this->selectPins[0] = mPin1;
        this->selectPins[1] = mPin2;
        this->selectPins[2] = mPin3;
        this->readPin1 = aPin1;
        this->readPin2 = aPin2;
        if (arraySize == 8 || arraySize == 16)
        {
            this->arraySize = arraySize;
        } else {
            return;
        }

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
                selectMuxPin(pin);                   // Select pin
                inputs8[pin] = analogRead(readPin1); // and read analog value
            }
        }
        else if (arraySize == 16)
        {
            for (byte pin = 0; pin <= 7; pin++)
            {
                selectMuxPin(pin);                        // Select pin
                inputs16[pin] = analogRead(readPin1);     // and read analog value
                inputs16[pin + 8] = analogRead(readPin2); // and read analog value
            }
        }
    }

    /*!
    @brief  Function to fetch the values of the multiplexer array
    @return Array of LDR values, based on the arraySize set in constructor, if arraySize is not supported, returns -1
    */
    float *readValues()
    {
        if (arraySize == 8)
        {
            return inputs8;
        }
        else if (arraySize == 16)
        {
            return inputs16;
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
};