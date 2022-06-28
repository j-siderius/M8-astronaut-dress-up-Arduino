#pragma once

#include <Arduino.h>

class Serialcomm
{
private:
    static const int maxFunctions = 20;
    struct Func
    {
        char call;
        void (*callback)();
    };
    Func functions[maxFunctions];
    int index = 0;
    int byteTimeout = 2;

public:
    /*!
  @brief  Serial comm constructor sets up serial port
  @warning  THIS LIBRARY CANNOT START THE PORT; add Serial.begin([baudrate]); in setup() yourself!
  @return Serialcomm object
*/
    Serialcomm()
    {
        Serial.println("Serialcomm init");
    }

    /*!
      @brief  Add a new function to the serial communication protocol
      @param  call   Character that calls this function
      @param  callback  Function that will be called when call is registered
    */
    void addFunction(char call, void (*callback)())
    {
        if (index < maxFunctions)
        {
            this->functions[index].call = call;
            this->functions[index].callback = callback;
            index++;
        }
        else
        {
            Serial.print("ERROR: too many functions in serial comm manager, max=");
            Serial.println(maxFunctions);
        }
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
      @throws Error when call is not recognized
    */
    void checkCalls(char incomingByte)
    {
        if (incomingByte >= 33 && incomingByte < 127)
        {
            for (int i = 0; i < index; i++)
            {
                if (incomingByte == functions[i].call)
                {
                    functions[i].callback();
                    return;
                }
            }

            // TODO: disable to avoid abmiguity
            Serial.print("Function '");
            Serial.print(incomingByte);
            Serial.println("' not found");
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
    char* readChar(int numberChars)
    {
        int timeOut = byteTimeout * numberChars;
        char buf[numberChars];
        delay(2);

        Serial.setTimeout(timeOut);

        for (int i = 0; i < numberChars; i++)
        {
            buf[i] = Serial.read();
        }

        Serial.setTimeout(1000);

        return buf;
    }

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
        Serial.println(call); // TODO: check if LN is nescessary
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
        Serial.println(); // TODO: check if this is nescessary
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
        Serial.println(arrLen);
        for (int i = 0; i < arrLen; i++)
        {
            Serial.print(boolArray[i]);
        }
        Serial.println(); // TODO: check if LN is nescessary
    }
};