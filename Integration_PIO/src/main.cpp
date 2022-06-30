#include <Arduino.h>
#include "LiquidCrystal_I2C.h"

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
// GeneralLight generalLED = GeneralLight();
ToxicityLED toxicLED = ToxicityLED(5, 4, 3, 0, 2, 1);
ServoController oxygenServo = ServoController(dialOxygenPin, 0, 100);
ServoController gforceServo = ServoController(dialGForcePin, 0, 3);
ServoController pressureServo = ServoController(dialPressurePin, 0, 1000, true);
Multiplexer multiplexer8 = Multiplexer(multiplexerSelectPin1, multiplexerSelectPin2, multiplexerSelectPin3, multiplexerReadPin1, 20);
Multiplexer multiplexer16 = Multiplexer(multiplexerSelectPin1, multiplexerSelectPin2, multiplexerSelectPin3, multiplexerReadPin2, multiplexerReadPin3, 20);
// PlanetDetector detector = PlanetDetector(100);

// function definitions
void turnOffEverything();

// main variables
bool planetSelected = false;
bool launching = false;
bool inSpace = false;
bool landed = false;
bool doorOpen = false;
int launchSequenceIndex = 0;

// Timers
Timer prelaunchTimer = Timer(5000);
Timer ascensionTimer = Timer(5000);
Timer travelTimer = Timer(0);
Timer doorOpenTimer = Timer(3333);
Timer deadOrAliveTimer = Timer(7000);
// DURATIONS
// prelaunch: 5s
// in space: 5s
// traveltime = traveltime
// opening hatch: 2s
// death/alive: 7s

void setup()
{
  Serial.begin(9600);

  Serial.println("Starting...");

  comm = SerialController();

  Serial.println("Initialized");
}

void loop()
{
  Serial.print("MUX8: ");
  multiplexer8.NEWreadMux8(); 
  for (int i = 0; i < 8; i++)
  {
    Serial.print("\t\t");
    Serial.print(multiplexer8.values8bit[i]);
  }
  Serial.println();

  // Serial.print("MUX16: ");
  // multiplexer16.NEWreadMux16(); 
  // for (int i = 0; i < 16; i++)
  // {
  //   Serial.print("\t");
  //   Serial.print(multiplexer16.values16bit[i]);
  // }
  // Serial.println();
  delay(500);
}

// void setup()
// {
//   Serial.begin(9600);
//   Serial.println("Starting...");
//   comm = SerialController();
//   LCDinit();

//   turnOffEverything();
//   pinMode(buttonLEDPin, OUTPUT);

//   Serial.println("Initialized");
// }

// void loop()
// {
//   comm.updateSerial();

//   switch (comm.getFlowState())
//   {
//   // on earth
//   case 0:
//     turnOffEverything();

//     LCDupdate("...");

//     digitalWrite(buttonLEDPin, HIGH);

//     if (!planetSelected)
//     { // if no planet is currently selected
//       if (multiplexer8.hasChanged())
//       {                              // check if the multiplexer has changed
//         char planetFuncDef[] = "PA"; // send the current planet values if they have changed
//         comm.sendChars(planetFuncDef, sizeof(planetFuncDef));
//         comm.sendBoolArray(multiplexer8.readValues(), sizeof(8));
//       }
//       if (detector.getPlanetDetected())
//         planetSelected = true; // if a planet is selected, save this
//     }
//     else
//     { // if a planet is selected
//       if (digitalRead(buttonSwitchPin))
//       {
//         comm.sendChar('L'); // send launching command to Python
//         comm.sendBool(true);
//       }

//       if (multiplexer16.hasChanged())
//       {                              // check if the multiplexer has changed
//         char planetFuncDef[] = "AA"; // send the current astronaut values if they have changed
//         comm.sendChars(planetFuncDef, sizeof(planetFuncDef));
//         comm.sendBoolArray(multiplexer16.readValues(), sizeof(16));
//       }
//     }

//     /*
//     - general lighting guiding user
//     - button lighting up
//     - displaying accurate data of earth on dashboard
//     - also fog for gasgiant
//     - detecting planet!!!!!!!!
//     - detecting astronaut!!!!!!!
//     - the rest is off
//     */
//     break;

//   // launching
//   case 1:

//     if (launching)
//     {
//       switch (launchSequenceIndex)
//       {
//       case 0:
//         // prelaunch
//         if (prelaunchTimer.check(millis()))
//         {
//           ascensionTimer.start();
//           launchSequenceIndex++;
//         }
//         else
//         {
//           // pre-launch
//           // TODO: change to earth values
//           oxygenServo.move(90);
//           pressureServo.move(10);
//           gforceServo.move(10);
//         }
//         break;

//       case 1:
//         // ascension
//         if (ascensionTimer.check(millis()))
//         {
//           travelTimer.start();
//           launchSequenceIndex++;
//         }
//         else
//         {
//           // launching
//           // TODO: test jitter
//           oxygenServo.jitter();
//           pressureServo.jitter();
//           gforceServo.jitter();

//           fireLED.run();
//           // add smoke etc
//         }
//         break;
//       }
//     }
//     else
//     {
//       turnOffEverything();
//       launching = true;
//       prelaunchTimer.start();
//       launchSequenceIndex = 0;
//     }

//     /*
//     - start launch (fire led ring + smoke)!!!!!!
//     - disabling planet selection/astronaut selection
//     - displaying accurate data of earth on dashboard
//     - synchronizing: launchconfirm, travel time
//     */
//     break;

//   // traveling
//   case 2:
//     if (inSpace)
//     {
//       travelLED.run();
//     }
//     else
//     {
//       inSpace = true;
//       travelTimer.changeDelay(comm.getTravelTime());

//       // set dashboard to space
//       oxygenServo.move(0);
//       gforceServo.move(0);
//       pressureServo.move(0);
//     }

//     /*
//     - travel lighting
//     - displaying space data (everything to 0 or whacky stuff)
//     */
//     break;

//   // landed on planet
//   case 3:
//     if (landed)
//     {
//       // display dashboard lights etc

//       if (doorOpen) // if the door is open, display granular outputs
//       {
//         // granular outputs
//       }

//       // check if the door has already opened
//       if (!doorOpen && doorOpenTimer.check(millis()))
//       {
//         doorOpen = true;
//       }
//     }
//     else
//     {
//       // we have landed, start door open timer
//       landed = true;
//       doorOpenTimer.start();

//       // set dashboard outputs
//       oxygenServo.move(comm.getPlanetOxygen());
//       gforceServo.move(comm.getPlanetGForce());
//       pressureServo.move(comm.getPlanetPressure());
//     }

//     /*
//     - displaying accurate planet data
//     - displaying granular experience-of-astronaut-data
//     */
//     break;

//   // death
//   case 4:
//     /*
//     - do nothing (all special shit gets done by python
//     */
//     break;

//   // survived
//   case 5:
//     /*
//     - do nothing (all special shit gets done by python
//     */
//     break;
//   }
// }

void LCDinit()
{
  lcd.begin();
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

// void turnOffEverything()
// {
//   LCDupdate("");                  // updates the LCD to display no destination
//   humidifierMosfet.turnOff();     // turn off the humidity
//   smellMosfet.turnOff();          // turn off the smell
//   vapeMosfet.turnOff();           // turn off the vape mosfet
//   vapeFanMosfet.turnOff();        // turn off the vape fan
//   tempFan.tempOff();              // turn off temperature output
//   tempLED.turnOff();              // turn off the temperature LEDs
//   generalLED.setBrightness(1, 0); // turn off all general LEDs
//   generalLED.setBrightness(2, 0);
//   generalLED.setBrightness(3, 0);
//   generalLED.setBrightness(4, 0);
//   toxicLED.setTotalBrightness(0); // turn off all toxicity LEDs
//   // oxygenServo.move(0);            // set servos to 0 position
//   // gforceServo.move(0);
//   // pressureServo.move(0);
//   digitalWrite(buttonLEDPin, LOW); // turn off the button LED
// }
