#pragma once

#include <Arduino.h>

class SerialController
{
private:
    // survival
    bool toxicityGranular, oxygenGranular, gasGiantGranular;
    int temperatureGranular;

    // planet data
    float planetGForce, planetPressure;
    bool planetToxicity, planetGasGiant, planetOxygen;
    int planetTemperature;
    // int planetElementCO2, planetElementN2, planetElementO2, planetElementCH4, planetElementH2, planetElementHe;
    int elements[6];
    String name;

    // mangement variables
    int time, state;
    int byteTimeout = 2;

public:
    // GETTERS
    int getTravelTime()
    {
        return time;
    }

    int getFlowState()
    {
        return state;
    }

    String getPlanetName()
    {
        return name;
    }

    int *getElements()
    {
        return elements;
    }

    bool getToxicity()
    {
        return toxicityGranular;
    }

    bool getOxygen()
    {
        return oxygenGranular;
    }

    int getPlanetOxygen() {
        return elements[3];
    }

    bool getGasGiant()
    {
        return gasGiantGranular;
    }

    int getGranularTemperature()
    {
        return temperatureGranular;
    }

    float getPlanetGForce()
    {
        return planetGForce;
    }

    float getPlanetPressure()
    {
        return planetPressure;
    }

    bool getPlanetToxicity()
    {
        return planetToxicity;
    }

    bool getPlanetGasGiant()
    {
        return planetGasGiant;
    }

    int getPlanetTemperature()
    {
        return planetTemperature;
    }

    // Call functions
    void funcFlow()
    {
        state = readInt(1);
        confirmReceived('F');
    }

    void funcPlanetName()
    {
        name = readLine();
        if (name == "Earth") name = "";
        confirmReceived('N');
    }

    void funcPlanetData()
    {
        String data = readLine();
        // data processing
        //

        // decoding
        // TODO: IDENTIFIER SUBJECT TO CHANGE
        // G-force|Toxic|Oxygen|SurfaceTemperature|GasGiant|CO2|N2|O2|CH4|H2|He|SurfacePressure|Distance
        //     F| T|  O|     K| G|  E|   |   |   |   |   |     P|      D
        // 0.000| 0|  0|  -000| 0| 00| 00| 00| 00| 00| 00| 0.000|  0.000
        // example: F0.908T1O0K-195G1E0|0|0|2|83|15P1000D2867

        int gforceIndex = data.indexOf("F");
        planetGForce = data.substring(gforceIndex + 1, gforceIndex + 6).toFloat() * 1.000; // TODO: accuracy is now only two decimals
        int toxicityIndex = data.indexOf("T");
        planetToxicity = data.substring(toxicityIndex + 1, toxicityIndex + 2).toInt();
        int oxygenIndex = data.indexOf("O");
        planetOxygen = data.substring(oxygenIndex + 1, oxygenIndex + 2).toInt();
        int temperatureIndex = data.indexOf("K");
        planetTemperature = data.substring(temperatureIndex + 1, temperatureIndex + 5).toInt();
        int gasIndex = data.indexOf("G");
        planetGasGiant = data.substring(gasIndex + 1, gasIndex + 2).toInt();
        int elementIndex = data.indexOf("E");
        elements[0] = data.substring(elementIndex + 1, elementIndex + 3).toInt();
        elements[1] = data.substring(elementIndex + 3, elementIndex + 5).toInt();
        elements[2] = data.substring(elementIndex + 5, elementIndex + 7).toInt();
        elements[3] = data.substring(elementIndex + 7, elementIndex + 9).toInt();
        elements[4] = data.substring(elementIndex + 9, elementIndex + 11).toInt();
        elements[5] = data.substring(elementIndex + 11, elementIndex + 13).toInt();
        // planetElementCO2 = data.substring(elementIndex + 1, elementIndex + 3).toInt();
        // planetElementN2 = data.substring(elementIndex + 3, elementIndex + 5).toInt();
        // planetElementO2 = data.substring(elementIndex + 5, elementIndex + 7).toInt();
        // planetElementCH4 = data.substring(elementIndex + 7, elementIndex + 9).toInt();
        // planetElementH2 = data.substring(elementIndex + 9, elementIndex + 11).toInt();
        // planetElementHe = data.substring(elementIndex + 11, elementIndex + 13).toInt();
        int pressureIndex = data.indexOf("P");
        planetPressure = data.substring(pressureIndex + 1, pressureIndex + 6).toFloat() * 1.000; // TODO: accuracy is now only two decimals

        confirmReceived('D');
    }

    void funcTravelTime()
    {
        time = readInt(5);
        confirmReceived('T');
        Serial.print("TravelTime received: "); Serial.println(time);
    }

    void funcAstronautSurvival()
    {
        String survival = readLine();
        /*
        Granular data: an array of 4 variables. Only used once the astronaut has landed on the planet
        first value = toxicity; 0 = no toxic, 1 = toxic
        second value = oxygen; 0 = no oxygen, 1 = oxygen
        third value = temperature; 0 = cold, 1 = normal, 2 is hot
        fourth value = gas giant; 0 = no gas giant, 1 = gas giant
        For example: [0, 1, 2, 0]
        */

        toxicityGranular = survival.substring(1, 2).toInt();
        oxygenGranular = survival.substring(2, 3).toInt();
        temperatureGranular = survival.substring(3, 4).toInt();
        gasGiantGranular = survival.substring(4, 5).toInt();

        confirmReceived('S');
    }

    void funcLaunchConfirm()
    {
        bool launchConfirm = readBool();
        if (launchConfirm)
        {
            Serial.println("Launching");
            // launch is confirmed, timer sync, start!
        }
    }

    // Main class functions

    /*!
    @brief  Serial comm constructor sets up serial port
    @warning  THIS LIBRARY CANNOT START THE PORT; add Serial.begin([baudrate]); in setup() yourself!
    @return Serialcomm object
    */
    SerialController()
    {
        Serial.println("Serialcomm init");
    }

    /*!
    @brief  Update serial port and read incoming byte
    */
    void updateSerial()
    {
        while (Serial.available() > 0)
        {
            char incomingByte = Serial.read();
            this->checkCalls(incomingByte);
        }
    }

    /*!
        @brief  Loops though all registered calls and runs the associated function if call is found
        @param  incomingByte  Byte to check for associated function
      */
    void checkCalls(byte incomingByte)
    {
        if (incomingByte >= 33 && incomingByte < 127)
        {
            switch (incomingByte)
            {
            case 'F':
                this->funcFlow();
                break;

            case 'N':
                this->funcPlanetName();
                break;

            case 'D':
                this->funcPlanetData();
                break;

            case 'T':
                this->funcTravelTime();
                break;

            case 'S':
                this->funcAstronautSurvival();
                break;

            case 'L':
                this->funcLaunchConfirm();
                break;
            }
        }
    }

    /*!
    @brief  Reads the specified amount of bytes from serial port and returns the variable as an int
    @param  numberDecimals  Amount of decimals of variable that will be fetched from serial
    @returns Integer of variable from serial
    @throws Timeout when not enough bytes are received within the byteTimeout time
  */
    int readInt(int numberDecimals)
    {
        int timeOut = byteTimeout * numberDecimals;
        char buf[numberDecimals];
        int variable;
        delay(2);

        Serial.setTimeout(timeOut);

        Serial.readBytes(buf, numberDecimals);
        variable = String(buf).toInt();

        Serial.setTimeout(1000);

        return variable;
    }

    /*!
      @brief  Reads the specified amount of bytes from serial port and returns the variable as an char array
      @param  numberChars  Amount of chars of variable that will be fetched from serial
      @returns Char array of variable from serial
      @throws Timeout when not enough bytes are received within the byteTimeout time
    */
    // TODO: fix if time
    // char readChar(int numberChars)
    // {
    //     int timeOut = byteTimeout * numberChars;
    //     char buf[numberChars];
    //     delay(2);

    //     Serial.setTimeout(timeOut);

    //     for (int i = 0; i < numberChars; i++)
    //     {
    //         buf[i] = Serial.read();
    //     }

    //     Serial.setTimeout(1000);

    //     return buf;
    // }

    /*!
      @brief  Reads the boolean from the serial port and returns it
      @returns Boolean from variable
    */
    bool readBool()
    {
        delay(2); // TODO: check if possible to delete the delay
        int boo = Serial.read() - '0';
        return boo ? true : false;
    }

    /*!
      @brief  Reads the serial until a EOF (LF or \ n) character is found
      @returns String from serial
    */
    String readLine()
    {
        return Serial.readStringUntil('\n'); // TODO: confirm this actually works
    }

    /*!
      @brief  Confirms the succesful receipt of call over the serial port
      @param  call  Call character that will be sent for confirmation
    */
    void confirmReceived(char call)
    {
        char confirmMsg[2] = {'C', call};
        Serial.println(confirmMsg); // TODO: check if LN is nescessary
    }

    /*!
      @brief  Sends a single character over the serial port
      @param  call  Call character that will be sent
    */
    void sendChar(char call)
    {
        Serial.print(call); // TODO: check if LN is nescessary
    }

    /*!
      @brief  Sends an array of character over the serial port
      @param  calls  Call character array that will be sent
      @param  arrLen  Lenght of the array, used for looping
    */
    void sendChars(char calls[], int arrLen)
    {
        for (int i = 0; i < arrLen; i++)
        {
            Serial.print(calls[i]);
        }
        // Serial.println(); // TODO: check if this is nescessary
    }

    /*!
      @brief  Sends a boolean over the serial port (as 0 / 1)
      @param  boo  Boolean that will be sent
    */
    void sendBool(bool boo)
    {
        Serial.println(boo); // TODO: check if LN is nescessary
    }

    /*!
      @brief  Sends an interger array over the serial port
      @param  intArray  Integer array that will be sent
      @param  arrLen  Lenght of the array, used for looping
    */
    void sendIntArray(int intArray[], int arrLen)
    {
        for (int i = 0; i < arrLen; i++)
        {
            Serial.print(intArray[i]);
        }
        Serial.println(); // TODO: check if LN is nescessary
    }

    /*!
      @brief  Sends an boolean array over the serial port
      @param  boolArray  Boolean array that will be sent
      @param  arrLen  Lenght of the array, used for looping
    */
    void sendBoolArray(bool boolArray[], int arrLen)
    {
        // Serial.println(arrLen);
        for (int i = 0; i < arrLen; i++)
        {
            Serial.print(boolArray[i]);
        }
        Serial.println(); // TODO: check if LN is nescessary
    }
};