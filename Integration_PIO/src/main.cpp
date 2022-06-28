#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// include custom classes
#include "Timer.h"
#include "Mosfet.h"
#include "SerialComm.h"
#include "TemperatureController.h"
#include "TemperatureLED.h"
#include "ServoController.h"

// pin definitions
#define temperatureColdPin 20
#define temperatureHotPin 21
#define temperatureLEDPin 22
#define dialOxygenPin 23
#define dialGForcePin 24
#define dialPressurePin 25
#define vapeMosfetPin 26
#define vapeFanMosfetPin 27
#define fanMosfetPin 28
#define hairdryerMosfetPin 29

// object definitions
// WARNING: LCD implementation currently in main due to incompatibility and errors
// TODO: fix if time
LiquidCrystal_I2C lcd(0x27, 16, 2);
String planetName;
void LCDinit(), LCDupdate();
// LCD implementation ^^^
Serialcomm comm;
Mosfet vapeMosfet = Mosfet(vapeMosfetPin);
Mosfet vapeFanMosfet = Mosfet(vapeFanMosfetPin);
Mosfet fanMosfet = Mosfet(fanMosfetPin);
Mosfet hairdryerMosfet = Mosfet(hairdryerMosfetPin);
TemperatureController tempFan = TemperatureController(temperatureColdPin, temperatureHotPin);
TemperatureLED tempLED = TemperatureLED(temperatureLEDPin);
ServoController oxygenServo = ServoController(dialOxygenPin, 0, 100);
ServoController gforceServo = ServoController(dialGForcePin, 0, 3);
ServoController pressureServo = ServoController(dialPressurePin, 0, 1000, true);

void setup() {
  Serial.begin(9600);  
  comm = Serialcomm();
  LCDinit();
}

void loop() {
  
}

void LCDinit() {
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(2, 0);
  lcd.print("Destination:");
}

void LCDupdate(String name) {
      if (name != planetName) {
        planetName = name;
        lcd.clear();

        lcd.setCursor(2, 0);
        lcd.print("Destination:");
        lcd.setCursor(2, 1);
        lcd.print(planetName);
      }
    }
