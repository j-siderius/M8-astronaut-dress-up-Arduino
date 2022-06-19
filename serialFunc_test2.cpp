#include <Arduino.h>

#include "Serialcomm.h"

Serialcomm comm;

void funcFlow(), funcPlanetName(), funcPlanetData(), funcPlanetTravel(), funcAstronautSurvival(), funcPlanetArray(), funcAstronautArray(), funcLaunchCheck(), funcLaunchConfirm();
bool planets[8] = {true, true, true, true, true, true, true, true};
bool astronaut[12] = {true, true, true, true, true, true, true, true, true, true, true, true};

//-------------------------\\

void setup()
{
    Serial.begin(9600);
    comm = Serialcomm();

    comm.addFunction('F', funcFlow);
    comm.addFunction('N', funcPlanetName);
    comm.addFunction('D', funcPlanetData);
    comm.addFunction('T', funcPlanetTravel);
    comm.addFunction('S', funcAstronautSurvival);
    comm.addFunction('L', funcLaunchConfirm);
    
    // test functions for return
    comm.addFunction('P', funcPlanetArray);
    comm.addFunction('A', funcAstronautArray);
}

void loop()
{
    comm.updateSerial();
}

//-------------------------\\

void funcFlow()
{
    int state = comm.readInt(1);
    Serial.print("State: ");
    Serial.println(state);
    // state processing
    //
    comm.confirmReceived('F');
}

void funcPlanetName()
{
    String name = comm.readLine();
    Serial.print("Planet name: ");
    Serial.println(name);
    // name processing
    //
    comm.confirmReceived('N');
}

void funcPlanetData()
{
    String data = comm.readLine();
    Serial.print("Planet data: ");
    Serial.println(data);
    // data processing
    //

    // decoding
    // TODO: IDENTIFIER SUBJECT TO CHANGE
    // data structure = G0.000T1O1K-000P1C00.00.00Z00
    // G = G-force float 1.234G | T = toxicity 0/1 | O = oxygen 0/1 | K = temperature -123C | P = gas giant 0/1 | C = composition 12C.34H.56N | Z = oxygen composition 12%
    int gforceIndex = data.indexOf("G");
    float planetGForce = data.substring(gforceIndex+1, gforceIndex+6).toFloat() * 1.000;  // TODO: accuracy is now only two decimals
    int toxicityIndex = data.indexOf("T");
    bool planetToxicity = data.substring(toxicityIndex+1, toxicityIndex+2).toInt();
    int oxygenIndex = data.indexOf("O");
    bool planetOxygen = data.substring(oxygenIndex+1, oxygenIndex+2).toInt();
    int temperatureIndex = data.indexOf("K");
    int planetTemperature = data.substring(temperatureIndex+1, temperatureIndex+5).toInt();
    int gasIndex = data.indexOf("P");
    bool planetGasGiant = data.substring(gasIndex+1, gasIndex+2).toInt();
    int compositionIndex = data.indexOf("C");
    String planetComposition = data.substring(compositionIndex+1, compositionIndex+9);
    int oxygenCompIndex = data.indexOf("Z");
    int planetOxygenComposition = data.substring(oxygenCompIndex+1, oxygenCompIndex+3).toInt();

    Serial.print("G-force:"); Serial.println(planetGForce);
    Serial.print("Toxicity:"); Serial.println(planetToxicity);
    Serial.print("Oxygen:"); Serial.println(planetOxygen);
    Serial.print("Temperature:"); Serial.println(planetTemperature);
    Serial.print("Gas giant:"); Serial.println(planetGasGiant);
    Serial.print("Composition:"); Serial.println(planetComposition);
    Serial.print("Oxygen percentage:"); Serial.println(planetOxygenComposition);

    comm.confirmReceived('D');
}

void funcPlanetTravel()
{
    int travelTime = comm.readInt(3);
    Serial.print("Planet travel time: ");
    Serial.println(travelTime);
    // processing traveltime
    //
    comm.confirmReceived('T');
}

void funcAstronautSurvival()
{
    bool survival = comm.readBool();
    Serial.print("Astronaut survival: ");
    Serial.println(survival);
    // processing survival
    //
    comm.confirmReceived('S');
}

void funcPlanetArray()
{
    char planetFuncDef[] = "PA";
    comm.sendChars(planetFuncDef, sizeof(planetFuncDef));
    comm.sendBoolArray(planets, sizeof(planets));
}

void funcAstronautArray()
{
    char astronautFuncDef[] = "AA";
    comm.sendChars(astronautFuncDef, sizeof(astronautFuncDef));
    comm.sendBoolArray(astronaut, sizeof(astronaut));
}

void funcLaunchCheck()
{
    comm.sendChar('L');
    comm.sendBool(true);
}

void funcLaunchConfirm()
{
    bool launchConfirm = comm.readBool();
    if (launchConfirm)
    {
        Serial.println("Launching");
        // launch is confirmed, timer sync, start!
    }
}