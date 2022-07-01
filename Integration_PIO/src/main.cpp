#include <Arduino.h>
#include "LiquidCrystal_I2C.h"

#include "ServoThing.h"

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
ToxicityLED toxicLED = ToxicityLED(5, 4, 3, 0, 2, 1);
// ServoController oxygenServo = ServoController(dialOxygenPin, 0, 100);
// ServoController gforceServo = ServoController(dialGForcePin, 0, 3);
// ServoController pressureServo = ServoController(dialPressurePin, 0, 1000, true);
Multiplexer multiplexer8 = Multiplexer(multiplexerSelectPin1, multiplexerSelectPin2, multiplexerSelectPin3, multiplexerReadPin1, 20);
Multiplexer multiplexer16 = Multiplexer(multiplexerSelectPin1, multiplexerSelectPin2, multiplexerSelectPin3, multiplexerReadPin2, multiplexerReadPin3, 20);
PlanetDetector detector = PlanetDetector(60);

// NEW servo controller
ServoThing oxyServo = ServoThing(dialOxygenPin, 0, 100);
ServoThing presServo = ServoThing(dialPressurePin, 0, 1000, true);
ServoThing gfServo = ServoThing(dialGForcePin, 0, 3);

// main variables
bool planetSelected = false;
bool launching = false;
bool inSpace = false;
bool landed = false;
bool doorOpen = false;
bool ending = false;
int launchSequenceIndex = 0;

// Timers
Timer prelaunchTimer = Timer(6250);
Timer doorOpenTimer = Timer(3333);
Timer deadOrAliveTimer = Timer(7000);
// DURATIONS
// prelaunch: 5s
// in space: 5s
// traveltime = traveltime
// opening hatch: 2s
// death/alive: 7s

// ----------------------------------------------- //

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting...");
  comm = SerialController();
  LCDinit();
  LCDupdate("");

  // initialize the servos
  gfServo.begin();
  oxyServo.begin();
  presServo.begin();
  gfServo.move(0);
  oxyServo.move(0);
  presServo.move(0);

  // setup the button
  pinMode(buttonLEDPin, OUTPUT);
  pinMode(buttonSwitchPin, INPUT_PULLUP);

  tempFan.begin();

  // calibrate the multiplexers (1023 is not applicable)
  int calib1[16] = {550, 495, 790, 460, 750, 625, 765, 400, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023};
  multiplexer8.setCalibrationValues(calib1);
  int calib2[16] = {595, 700, 470, 345, 450, 550, 505, 420, 495, 1023, 465, 1023, 550, 1023, 1023, 1023};
  multiplexer16.setCalibrationValues(calib2);

  detector.begin();

  // turnOffEverything();

  // mosfets
  vapeMosfet.begin();
  vapeFanMosfet.begin();
  humidifierMosfet.begin();
  smellMosfet.begin();

  Serial.println("Initialized");
}

// ----------------------------------------------- //

void loop()
{
  comm.updateSerial();

  switch (comm.getFlowState())
  {
  // ---------- PLANET & ASTRONAUT SELECTION ---------- //
  case 0:
    // Serial.println("state 0 selected");

    LCDupdate(comm.getPlanetName());

    digitalWrite(buttonLEDPin, HIGH);

    // --- PLANET SELECTION --- //
    if (!planetSelected)
    {

      generalLED.groupBlue(1);
      generalLED.groupRed(2);
      generalLED.groupRed(3);
      generalLED.groupRed(4);
      generalLED.groupRed(5);

      // --- PLANET CHECK --- //
      multiplexer8.NEWreadMux8();
      multiplexer8.NEWtransformValues8();

      if (multiplexer8.hasChanged())
      {
        Serial.print("PA");
        for (int i = 0; i < 8; i++)
        {
          Serial.print(multiplexer8.bools8bit[i]);
        }
        Serial.println();
      }

      // --- CHECK PLANET DETECTOR --- //
      detector.readSensor();
      // Serial.println(detector.distance);
      if (detector.getPlanetDetected())
        planetSelected = true; // if a planet is selected, save this
    }

    // --- ASTRONAUT SELECTION --- //
    else
    {
      // --- CHECK LAUNCH BUTTON --- //
      if (!digitalRead(buttonSwitchPin))
      {
        comm.sendChar('L'); // send launching command to Python (it determines if we actually launch or not)
        comm.sendBool(true);
      }

      generalLED.groupGreen(1);
      generalLED.groupRed(2);
      generalLED.groupRed(3);
      generalLED.groupRed(4);
      generalLED.groupBlue(5);

      // --- ASTRONAUT CHECK --- //
      multiplexer16.NEWreadMux16();
      multiplexer16.NEWtransformValues16();

      if (multiplexer16.hasChanged())
      {
        Serial.print("AA");
        for (int i = 0; i < 16; i++)
        {
          Serial.print(multiplexer16.bools16bit[i]);
        }
        Serial.println();
      }

      // --- CHECK PLANET DETECTOR --- //
      detector.readSensor();
      // Serial.println(detector.distance);
      if (!detector.getPlanetDetected())
        planetSelected = false; // if a planet is selected, save this
    }

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

  // ---------- LAUNCHING ---------- //
  case 1:

    if (launching)
    {
      switch (launchSequenceIndex)
      {
      // --- PRE LAUNCH --- //
      case 0:

        if (prelaunchTimer.check(millis()))
        {
          // move on to next step if timer has passed
          launchSequenceIndex++;
        }
        else
        {
          // pre-launch
          // Serial.println("pre-launch");
          generalLED.groupGreen(1);
          generalLED.groupRed(2);
          generalLED.groupBlue(3);
          generalLED.groupRed(4);
          generalLED.groupGreen(5);
        }
        break;

      // --- DURING LAUNCH / ASCENSION --- //
      case 1:

        // Serial.println("launching");
        // TODO: test jitter
        // oxygenServo.jitter();
        // pressureServo.jitter();
        // gforceServo.jitter();
        oxyServo.move(0);
        presServo.move(0);
        gfServo.move(0);
        tempLED.turnOffAll();

        generalLED.groupGreen(1);
        generalLED.groupRed(2);
        generalLED.groupBlue(3);
        generalLED.groupRed(4);
        generalLED.groupGreen(5);

        // run rocket animations
        fireLED.run();
        vapeFanMosfet.turnOn();
        // vapeMosfet.turnOn();
        break;
      }
    }

    // --- FIRST CALL --- //
    else
    {
      launching = true;
      prelaunchTimer.start();
      launchSequenceIndex = 0;

      digitalWrite(buttonLEDPin, LOW);

      // set dashboard to earth values
      tempLED.setTemperature(15);
      tempLED.turnOn();
      oxyServo.move(90);
      presServo.move(10);
      gfServo.move(10);

      Serial.println("state 1 selected");
    }

    /*
    - start launch (fire led ring + smoke)!!!!!!
    - disabling planet selection/astronaut selection
    - displaying accurate data of earth on dashboard
    - synchronizing: launchconfirm, travel time
    */
    break;

  // ---------- TRAVELLING ---------- //
  case 2:
    if (inSpace)
    {
      travelLED.run();
      
    }

    // --- FIRST CALL --- //
    else
    {
      inSpace = true;
      travelLED.setTravelTime(comm.getTravelTime());
      travelLED.turnOffAll();
      Serial.println("state 2 selected");

      // set dashboard to space values
      fireLED.turnOffAll();
      oxyServo.move(0);
      gfServo.move(0);
      presServo.move(0);

      tempLED.setTemperature(-500);
      tempLED.turnOn();

      vapeFanMosfet.turnOff();
      vapeMosfet.turnOff();

          generalLED.groupWhite(1);
          generalLED.groupWhite(2);
          generalLED.groupWhite(3);
          generalLED.groupWhite(4);
          generalLED.groupWhite(5);
    }

    /*
    - travel lighting
    - displaying space data (everything to 0 or whacky stuff)
    */
    break;

  // ---------- LANDING ---------- //
  case 3:

    if (landed)
    {
      // display dashboard lights etc
      // Serial.println("landed");

      if (doorOpen) // if the door is open, display granular outputs
      {
        // Serial.println("door open");

        // granular outputs

        tempFan.tempOn();

        // mosfets
        // smellMosfet.turnOn();
        // humidifierMosfet.turnOn();
      }

      // check if the door has already opened
      if (!doorOpen && doorOpenTimer.check(millis()))
      {
        doorOpen = true;
      }
    }

    // --- FIRST CALL --- //
    else
    {
      Serial.println("state 3 selected");
      // we have landed, start door open timer
      landed = true;
      doorOpenTimer.start();

      travelLED.turnOffAll();

      // set dashboard outputs
      oxyServo.move(comm.getPlanetOxygen());
      gfServo.move(comm.getPlanetGForce());
      presServo.move(comm.getPlanetPressure());

      tempFan.setTemperature(comm.getGranularTemperature());

      tempLED.setTemperature(comm.getPlanetTemperature());
      tempLED.turnOn();

      toxicLED.setPercentages(comm.getElements());
      toxicLED.displayElements();
    }

    /*
    - displaying accurate planet data
    - displaying granular experience-of-astronaut-data
    */
    break;

  // death
  case 4:
  // survived
  case 5:
    if (ending)
    {
      // wait until reset
    }
    else
    {
      // Serial.println("state 4 selected");
      tempLED.turnOff();
      tempFan.tempOff();
      travelLED.turnOffAll();
      toxicLED.turnOffElements();

      planetSelected = false;
      launching = false;
      inSpace = false;
      landed = false;
      doorOpen = false;

      vapeMosfet.turnOff();
      vapeFanMosfet.turnOff();
      humidifierMosfet.turnOff();
      smellMosfet.turnOff();

      digitalWrite(buttonLEDPin, LOW);

      LCDupdate("");

      fireLED.turnOffAll();
      oxyServo.move(0);
      gfServo.move(0);
      presServo.move(0);

      generalLED.turnOffAll();

      ending = true;
    }

    /*
    - do nothing (all special shit gets done by python
    */
    break;
  }
}

// ------------ LCD functions ---------- //

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
