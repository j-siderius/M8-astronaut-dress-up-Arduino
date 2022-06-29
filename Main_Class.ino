#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// include custom classes
#include "Timer.h"
#include "Mosfet.h"
#include "SerialComm.h"
#include "TemperatureController.h"
#include "TemperatureLED.h"
#include "ServoController.h"
#include "TravelLED.h"
#include "FireRing.h"
#include "Multiplexer.h"
#include "GeneralLighting.h"

// pin definitions
// TODO: CHANGE THESE TO ACTUAL PIN DEFINITIONS
#define temperatureColdPin 20
#define temperatureHotPin 21
#define dialOxygenPin 23
#define dialGForcePin 24
#define dialPressurePin 25
#define vapeMosfetPin 26
#define vapeFanMosfetPin 27
#define fanMosfetPin 28
#define hairdryerMosfetPin 29
#define multiplexerSelectPin1 30
#define multiplexerSelectPin2 31
#define multiplexerSelectPin3 32
#define multiplexerReadPin1 33
#define multiplexerReadPin2 34
#define multiplexerReadPin3 35
#define humidifierMosfetPin 36
#define smellMosfetPin 37

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
Mosfet humidifierMosfet = Mosfet(humidifierMosfetPin);
Mosfet smellMosfer = Mosfet(smellMosfetPin);
TemperatureController tempFan = TemperatureController(temperatureColdPin, temperatureHotPin);
TemperatureLED tempLED = TemperatureLED();
TravelLED travelLED = TravelLED();
FireRing fireLED = FireRing();
GeneralLight generalLED = GeneralLight();
ServoController oxygenServo = ServoController(dialOxygenPin, 0, 100);
ServoController gforceServo = ServoController(dialGForcePin, 0, 3);
ServoController pressureServo = ServoController(dialPressurePin, 0, 1000, true);
Multiplexer multiplexer8 = Multiplexer(multiplexerSelectPin1, multiplexerSelectPin2, multiplexerSelectPin3, multiplexerReadPin1, 8);
Multiplexer multiplexer16 = Multiplexer(multiplexerSelectPin1, multiplexerSelectPin2, multiplexerSelectPin3, multiplexerReadPin2, multiplexerReadPin3, 16);

void setup() {
  Serial.begin(9600);
  comm = Serialcomm();
  LCDinit();
}

void loop() {
  comm.checkCalls();

  switch (comm.getFlow())
  {
    //on earth
    case 0:
      /* 
      - general lighting guiding user
      - button lighting up
      - displaying accurate data of earth on dashboard
      - also fog for gasgiant
      - detecting planet!!!!!!!!
      - detecting astronaut!!!!!!!
      - the rest is off
      */
      break;

    //launching
    case 1:
      /*
      - start launch (fire led ring + smoke)!!!!!!
      - disabling planet selection/astronaut selection
      - displaying accurate data of earth on dashboard
      - synchronizing: launchconfirm, travel time
      */
      break;

    //traveling
    case 2:
      /* 
      - travel lighting
      - displaying space data (everything to 0 or whacky stuff)
      */
      break;

    //landed on planet
    case 3:
      /*
      - displaying accurate planet data
      - displaying granular experience-of-astronaut-data
      */
      break;

    //death
    case 4:
      /*
      - do nothing (all special shit gets done by python
      */
      break;

    //survived
    case 5:
      /*
      - do nothing (all special shit gets done by python
      */
      break;
  }
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
