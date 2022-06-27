//main code for the Astronaut installation

#include <Servo.h>
#include "LiquidCrystal_I2C.h"
#include "Timer.h"
#include "Serialcomm.h"
#include "LDR.h"
#include "DialServos.h"
//#include "DestinationLCD.h"
#include "TemperatureLeds.h"
#include "TravelLight.h"
#include "RingOfFire.h"
//#include "SendFunc.h"
#include "Mosfet.h"


//All pin definitions go here

int ldrD[6] = { 2, 3, 4, 5, 6, 7 };
char ldrA[3] = { A0, A1, A2 };

int servPin = 8;  //first pin of servos. other servos have to be attatched at ascending pin numbers

//int firePin = 11; //pin for the ring of fire, has to be defined in class

int MosfetPin = 12;




//create objects here
Serialcomm Comm;
LDR LDRs(ldrD, ldrA);
DialServos DashServos(servPin);
LiquidCrystal_I2C lcd(0x27, 16, 2);
//DestinationLCD DestLCD; //not working yet
TravelLight TravelLight;
RingOfFire RocketLEDs();
//SendFunc Sending();
Mosfet Mosfet(MosfetPin);


//global variables
//installation status variables
bool launchConfirm = true; //true as for the time after succesful start via launchbutton until planet is reached after predefined time

String planetName;

//remove or change the next arrays to actually fit
bool planets[8] = {true, true, true, true, true, true, true, true};
bool astronaut[12] = {true, true, true, true, true, true, true, true, true, true, true, true};

//Planet/Serial variables


void setup() {
  Serial.begin(9600);
  LCDinit();
}

void loop() {
  // check the serial and if call sign is recognized, run function
  Comm.updateSerial();
  LDRs.updateArrays();
  DashServos.Dialrun(launchConfirm);
  TravelLight.Travelrun(launchConfirm);
  LCDupdate("Mercury");
  


}


//screw it the screen is going in main
void LCDinit() {
      lcd.begin();
      lcd.backlight();
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Destination:");
    }

    /*!
    @brief  updates the destination planet on the LCD screen
    @param  name  new Planet name
    @note does not update the screen if name is the same as current name
    */
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

void Sendinit(){
   
  
  // add functions and their call sign
  Comm.addFunction('F', funcFlow);
  Comm.addFunction('N', funcPlanetName);
  Comm.addFunction('D', funcPlanetData);
  Comm.addFunction('S', funcAstronautSurvival);
  Comm.addFunction('L', funcLaunchConfirm);
  
  // test functions for return
  Comm.addFunction('P', funcPlanetArray);
  Comm.addFunction('A', funcAstronautArray);
}

//-------------------------\\

// flow variable for interaction stage management
void funcFlow(){
  int state = Comm.readInt(1);
  Serial.print("State: ");
  Serial.println(state);
  // state processing
  //
  Comm.confirmReceived('F');
}

// gets planet name to display on LCD
void funcPlanetName(){
  String name = Comm.readLine();
  Serial.print("Planet name: ");
  Serial.println(name);
  // name processing
  //
  Comm.confirmReceived('N');
}

// gets the bulk of data for processing
void funcPlanetData(){
  String data = Comm.readLine();
  Serial.print("Planet data: ");
  Serial.println(data);
  // data processing
  //

  // decoding
  // TODO: IDENTIFIER SUBJECT TO CHANGE
  // G-force|Toxic|Oxygen|SurfaceTemperature|GasGiant|CO2|N2|O2|CH4|H2|He|SurfacePressure|Distance
  //     F| T|  O|     K| G|  E|   |   |   |   |   |     P|      D
  // 0.000| 0|  0|  -000| 0| 00| 00| 00| 00| 00| 00| 0.000|  0.000
  // example: F0.908T1O0K-195G1E0|0|0|2|83|15P1000D2867

  int gforceIndex = data.indexOf("F");
  float planetGForce = data.substring(gforceIndex+1, gforceIndex+6).toFloat() * 1.000;  // TODO: accuracy is now only two decimals
  int toxicityIndex = data.indexOf("T");
  bool planetToxicity = data.substring(toxicityIndex+1, toxicityIndex+2).toInt();
  int oxygenIndex = data.indexOf("O");
  bool planetOxygen = data.substring(oxygenIndex+1, oxygenIndex+2).toInt();
  int temperatureIndex = data.indexOf("K");
  int planetTemperature = data.substring(temperatureIndex+1, temperatureIndex+5).toInt();
  int gasIndex = data.indexOf("G");
  bool planetGasGiant = data.substring(gasIndex+1, gasIndex+2).toInt();
  int elementIndex = data.indexOf("E");
  int planetElementCO2 = data.substring(elementIndex+1, elementIndex+3).toInt();
  int planetElementN2 = data.substring(elementIndex+3, elementIndex+5).toInt();
  int planetElementO2 = data.substring(elementIndex+5, elementIndex+7).toInt();
  int planetElementCH4 = data.substring(elementIndex+7, elementIndex+9).toInt();
  int planetElementH2 = data.substring(elementIndex+9, elementIndex+11).toInt();
  int planetElementHe = data.substring(elementIndex+11, elementIndex+13).toInt();
  int pressureIndex = data.indexOf("P");
  float planetPressure = data.substring(pressureIndex+1, pressureIndex+6).toFloat() * 1.000;  // TODO: accuracy is now only two decimals
  int distanceIndex = data.indexOf("D");
  float planetDistance = data.substring(distanceIndex+1, distanceIndex+6).toFloat() * 1.000;  // TODO: accuracy is now only two decimals

  // TODO: delete debugging print statements
  Serial.print("G-force:"); Serial.println(planetGForce);
  Serial.print("Toxicity:"); Serial.println(planetToxicity);
  Serial.print("Oxygen:"); Serial.println(planetOxygen);
  Serial.print("Temperature:"); Serial.println(planetTemperature);
  Serial.print("Gas giant:"); Serial.println(planetGasGiant);
  Serial.println("Elements:");
  Serial.print("CO2:"); Serial.println(planetElementCO2);
  Serial.print("N2:"); Serial.println(planetElementN2);
  Serial.print("O2:"); Serial.println(planetElementO2);
  Serial.print("CH4:"); Serial.println(planetElementCH4);
  Serial.print("H2:"); Serial.println(planetElementH2);
  Serial.print("He:"); Serial.println(planetElementHe);
  Serial.print("Pressure:"); Serial.println(planetPressure);
  Serial.print("Distance:"); Serial.println(planetDistance);

  Comm.confirmReceived('D');
}

// received bool to check if astronaut survives
void funcAstronautSurvival(){
  bool survival = Comm.readBool();
  Serial.print("Astronaut survival: ");
  Serial.println(survival);
  // processing survival
  //
  Comm.confirmReceived('S');
}

// sends the planet array
void funcPlanetArray(){
  char planetFuncDef[] = "PA";
  Comm.sendChars(planetFuncDef, sizeof(planetFuncDef));
  Comm.sendBoolArray(planets, sizeof(planets));
}

// sends the astronaut part array
void funcAstronautArray(){
  char astronautFuncDef[] = "AA";
  Comm.sendChars(astronautFuncDef, sizeof(astronautFuncDef));
  Comm.sendBoolArray(astronaut, sizeof(astronaut));
}

// checks with Python if we can launch
void funcLaunchCheck(){
  Comm.sendChar('L');
  Comm.sendBool(true);
}

// confirms launch
void funcLaunchConfirm(){
  launchConfirm = Comm.readBool();
  if (launchConfirm)
  {
      Serial.println("Launching");
      // launch is confirmed, timer sync, start!
  }
}
