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
}

void loop()
{
    comm.updateSerial();
}

//-------------------------\\

void funcFlow()
{
    int state = comm.readVar(1);
    // state processing
    //
    comm.confirmReceived('F');
}

void funcPlanetName()
{
    String name = comm.readLine;
    // name processing
    //
    comm.confirmReceived('N');
}

void funcPlanetData()
{
    String data = comm.readLine();
    // name processing
    //
    comm.confirmReceived('D');
}

void funcPlanetTravel()
{
    int travelTime = comm.readInt(3);
    // processing traveltime
    //
    comm.confirmReceived('T';)
}

void funcAstronautSurvival()
{
    bool survival = comm.readBool();
    // processing survival
    //
    comm.confirmReceived('S');
}

void funcPlanetArray()
{
    char planetFuncDef[] = "PA";
    comm.sendChars(planetFuncDef);
    comm.sendIntArray(planets);
}

void funcAstronautArray()
{
    char astronautFuncDef[] = "AA";
    comm.sendChars(astronautFuncDef);
    comm.sendIntArray(astronaut);
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
        // launch is confirmed, timer sync, start!
    }
}