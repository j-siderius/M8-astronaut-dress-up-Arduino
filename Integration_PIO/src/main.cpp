#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// include custom classes
#include "Timer.h"
#include "Mosfet.h"
#include "SerialComm.h"
#include "TemperatureController.h"
#include "TemperatureLED.h"

// pin definitions
#define temperatureColdPin 20
#define temperatureHotPin 21
#define temperatureLEDPin 22

// object definitions
Serialcomm comm;
// WARNING: LCD implementation currently in main due to incompatibility and errors
// TODO: fix if time
LiquidCrystal_I2C lcd(0x27, 16, 2);
String planetName;
void LCDinit(), LCDupdate();
// LCD implementation ^^^
TemperatureController tempFan = TemperatureController(temperatureColdPin, temperatureHotPin);
TemperatureLED tempLED = TemperatureLED(temperatureLEDPin);

void setup() {
  Serial.begin(9600);  
  comm = Serialcomm();
  LCDinit();
}

void loop() {
  delay(1000);
  tempLED.setTemperature(10);
  tempLED.turnOn();
  delay(1000);
  tempLED.turnOff();

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
