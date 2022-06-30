#pragma once

#include <Arduino.h>

#include <Wire.h>
#include <VL53L0X.h>

class PlanetDetector
{
private:
    VL53L0X sensor;
    uint16_t range;

public:
    uint16_t distance = 10000;

    /*!
    @brief  Planetdetector will check for a planet in the pedestal
    @param  range   Range at which a planet is considered present in the pedestal (in mm)
    @return PlanetDetector object
    */
    PlanetDetector(int range)
    {
        this->range = range;
    }

    /**
     * @brief starts the detector
     *
     */
    void begin()
    {
        Wire.begin();
        sensor.setTimeout(500);
        if (!sensor.init())
        {
            Serial.println("Failed to detect and initialize sensor!");
            while (1)
            {
            }
        }
        sensor.setMeasurementTimingBudget(20000); // enable high speed mode
    }
    /*!
    @brief  reads the sensor value into the class variable
    */
    void readSensor()
    {
        distance = sensor.readRangeSingleMillimeters();
    }

    /*!
    @brief  checks if a planet is detected in the pedestal or not
    @return boolean true is planet is detected, false if not
    */
    bool getPlanetDetected()
    {
        if (distance < range)
            return true;
        else
            return false;
    }
};