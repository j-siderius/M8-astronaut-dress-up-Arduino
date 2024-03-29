#include <Arduino.h>

// including the serial class
#include "Serialcomm.h"

// making serial object
Serialcomm comm;

// making placeholder functions and array
void funcFlow(), funcPlanetName(), funcPlanetData(), funcAstronautSurvival(), funcPlanetArray(), funcAstronautArray(), funcLaunchCheck(), funcLaunchConfirm();
bool planets[8] = {true, true, true, true, true, true, true, true};
bool astronaut[12] = {true, true, true, true, true, true, true, true, true, true, true, true};

//-------------------------\\

void setup()
{
    // serial port can only be opened in main sketch
    Serial.begin(9600);
    comm = Serialcomm();

    // add functions and their call sign
    comm.addFunction('F', funcFlow);
    comm.addFunction('N', funcPlanetName);
    comm.addFunction('D', funcPlanetData);
    comm.addFunction('S', funcAstronautSurvival);
    comm.addFunction('L', funcLaunchConfirm);
    
    // test functions for return
    comm.addFunction('P', funcPlanetArray);
    comm.addFunction('A', funcAstronautArray);
}

void loop()
{
    // check the serial and if call sign is recognized, run function
    comm.updateSerial();
}

//-------------------------\\

// flow variable for interaction stage management
void funcFlow()
{
    int state = comm.readInt(1);
    Serial.print("State: ");
    Serial.println(state);
    // state processing
    //
    comm.confirmReceived('F');
}

// gets planet name to display on LCD
void funcPlanetName()
{
    String name = comm.readLine();
    Serial.print("Planet name: ");
    Serial.println(name);
    // name processing
    //
    comm.confirmReceived('N');
}

// gets the bulk of data for processing
void funcPlanetData()
{
    String data = comm.readLine();
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

    comm.confirmReceived('D');
}

// received bool to check if astronaut survives
void funcAstronautSurvival()
{
    String survival = comm.readLine();
    Serial.print("Astronaut survival: ");
    Serial.println(survival);
    /*
    Granular data: an array of 4 variables. Only used once the astronaut has landed on the planet
    first value = toxicity; 0 = no toxic, 1 = toxic
    second value = oxygen; 0 = no oxygen, 1 = oxygen
    third value = temperature; 0 = cold, 1 = normal, 2 is hot
    fourth value = gas giant; 0 = no gas giant, 1 = gas giant
    For example: [0, 1, 2, 0]
    */

    byte toxicityGranular = survival.substring(1, 2)
    byte oxygenGranular = survival.substring(2, 3)
    byte temperatureGranular = survival.substring(3, 4)
    byte gasGiantGranular =  survival.substring(4, 5)
    
    comm.confirmReceived('S');
}
    
// sends the planet array
void funcPlanetArray()
{
    char planetFuncDef[] = "PA";
    comm.sendChars(planetFuncDef, sizeof(planetFuncDef));
    comm.sendBoolArray(planets, sizeof(planets));
}

// sends the astronaut part array
void funcAstronautArray()
{
    char astronautFuncDef[] = "AA";
    comm.sendChars(astronautFuncDef, sizeof(astronautFuncDef));
    comm.sendBoolArray(astronaut, sizeof(astronaut));
}

// checks with Python if we can launch
void funcLaunchCheck()
{
    comm.sendChar('L');
    comm.sendBool(true);
}

// confirms launch
void funcLaunchConfirm()
{
    bool launchConfirm = comm.readBool();
    if (launchConfirm)
    {
        Serial.println("Launching");
        // launch is confirmed, timer sync, start!
    }
}
