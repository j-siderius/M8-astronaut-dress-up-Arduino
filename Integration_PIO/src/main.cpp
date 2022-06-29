#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// include custom classes
#include "Timer.h"
#include "Mosfet.h"
#include "SerialController.h"
#include "TemperatureController.h"
#include "TemperatureLED.h"
#include "ServoController.h"
#include "TravelLED.h"
#include "FireRing.h"
#include "Multiplexer.h"
#include "GeneralLighting.h"
#include "PlanetDetector.h"

// pin definitions
#include "PINS.h"

// object definitions
// WARNING: LCD implementation currently in main due to incompatibility and errors
// TODO: fix if time
LiquidCrystal_I2C lcd(0x27, 16, 2);
String planetName;
void LCDinit(), LCDupdate();
// LCD implementation ^^^
SerialController comm;
Mosfet vapeMosfet = Mosfet(vapeMosfetPin);
Mosfet vapeFanMosfet = Mosfet(vapeFanMosfetPin);
Mosfet humidifierMosfet = Mosfet(humidifierMosfetPin);
Mosfet smellMosfer = Mosfet(smellMosfetPin);
TemperatureController tempFan = TemperatureController(temperatureColdPin, temperatureHotPin);
TemperatureLED tempLED = TemperatureLED();
TravelLED travelLED = TravelLED(8000);
FireRing fireLED = FireRing();
GeneralLight generalLED = GeneralLight();
ServoController oxygenServo = ServoController(dialOxygenPin, 0, 100);
ServoController gforceServo = ServoController(dialGForcePin, 0, 3);
ServoController pressureServo = ServoController(dialPressurePin, 0, 1000, true);
Multiplexer multiplexer8 = Multiplexer(multiplexerSelectPin1, multiplexerSelectPin2, multiplexerSelectPin3, multiplexerReadPin1, 8);
Multiplexer multiplexer16 = Multiplexer(multiplexerSelectPin1, multiplexerSelectPin2, multiplexerSelectPin3, multiplexerReadPin2, multiplexerReadPin3, 16);
PlanetDetector detector = PlanetDetector(100);

void setup() {
  Serial.begin(9600);  
  comm = SerialController();
  LCDinit();
}

void loop() {
  comm.updateSerial();
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
