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
#include "ToxicityLED.h"

// pin definitions
#include "PINS.h"

// object definitions
// WARNING: LCD implementation currently in main due to incompatibility and errors
// TODO: fix if time
LiquidCrystal_I2C lcd(0x27, 16, 2);
String planetName;
void LCDinit(), LCDupdate(String name);
// LCD implementation ^^^
SerialController comm;
Mosfet vapeMosfet = Mosfet(vapeMosfetPin);
Mosfet vapeFanMosfet = Mosfet(vapeFanMosfetPin);
Mosfet humidifierMosfet = Mosfet(humidifierMosfetPin);
Mosfet smellMosfet = Mosfet(smellMosfetPin);
TemperatureController tempFan = TemperatureController(temperatureColdPin, temperatureHotPin);
TemperatureLED tempLED = TemperatureLED();
TravelLED travelLED = TravelLED();
FireRing fireLED = FireRing();
GeneralLight generalLED = GeneralLight();
ToxicityLED toxicLED = ToxicityLED(6, 5, 4, 1, 3, 2);
ServoController oxygenServo = ServoController(dialOxygenPin, 0, 100);
ServoController gforceServo = ServoController(dialGForcePin, 0, 3);
ServoController pressureServo = ServoController(dialPressurePin, 0, 1000, true);
Multiplexer multiplexer8 = Multiplexer(multiplexerSelectPin1, multiplexerSelectPin2, multiplexerSelectPin3, multiplexerReadPin1, 20);
Multiplexer multiplexer16 = Multiplexer(multiplexerSelectPin1, multiplexerSelectPin2, multiplexerSelectPin3, multiplexerReadPin2, multiplexerReadPin3, 20);
PlanetDetector detector = PlanetDetector(100);

void turnOffEverything();

void setup()
{
  Serial.begin(9600);
  comm = SerialController();
  LCDinit();
}

void loop()
{
  comm.updateSerial();

  switch (comm.getFlowState())
  {
  // on earth
  case 0:
    turnOffEverything();

    LCDupdate("...");
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

  // launching
  case 1:
    /*
    - start launch (fire led ring + smoke)!!!!!!
    - disabling planet selection/astronaut selection
    - displaying accurate data of earth on dashboard
    - synchronizing: launchconfirm, travel time
    */
    break;

  // traveling
  case 2:
    /*
    - travel lighting
    - displaying space data (everything to 0 or whacky stuff)
    */
    break;

  // landed on planet
  case 3:
    /*
    - displaying accurate planet data
    - displaying granular experience-of-astronaut-data
    */
    break;

  // death
  case 4:
    /*
    - do nothing (all special shit gets done by python
    */
    break;

  // survived
  case 5:
    /*
    - do nothing (all special shit gets done by python
    */
    break;
  }
}

void LCDinit()
{
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(2, 0);
  lcd.print("Destination:");
}

void LCDupdate(String name)
{
  if (name != planetName)
  {
    planetName = name;
    lcd.clear();

    lcd.setCursor(2, 0);
    lcd.print("Destination:");
    lcd.setCursor(2, 1);
    lcd.print(planetName);
  }
}

void turnOffEverything()
{
  LCDupdate("...");           // updates the LCD to display no destination
  humidifierMosfet.turnOff(); // turn off the humidity
  smellMosfet.turnOff();      // turn off the smell
  vapeMosfet.turnOff();       // turn off the vape mosfet
  vapeFanMosfet.turnOff();    // turn off the vape fan
  tempFan.tempOff();          // turn off temperature output
  tempLED.turnOff();          // turn off the temperature LEDs  
  generalLED.setBrightness(1, 0);  // turn off all general LEDs
  generalLED.setBrightness(2, 0);
  generalLED.setBrightness(3, 0);
  generalLED.setBrightness(4, 0);
  toxicLED.setTotalBrightness(0); // turn off all toxicity LEDs
  oxygenServo.move(0);            // set servos to 0 position
  gforceServo.move(0);
  pressureServo.move(0);
}