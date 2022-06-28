#pragma once

#include <Wire.h>
#include <VL53L0X.h>

class PlanetDetector {
    private:
        VL53L0X sensor;
        uint16_t distance;

    public:
        PlanetDetector() {
            Wire.begin();
            sensor.setTimeout(500);
            sensor.init();
        }

        void readSensor() {
            distance = sensor.readRangeSingleMillimeters();
        }
};