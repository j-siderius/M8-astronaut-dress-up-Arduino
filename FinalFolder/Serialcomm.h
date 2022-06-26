#ifndef Serialcomm_h
#define Serialcomm_h

#include <Arduino.h>

class Serialcomm
{
private:
    static const int maxFunctions = 20;
    struct Func {
      char call;
      void (*callback)();
    };
    Func functions[maxFunctions];
    int index = 0;
    int byteTimeout = 2;

public:
    Serialcomm();
    void addFunction(char call, void (*callback)());
    void updateSerial();
    void checkCalls(char incomingByte);
    void confirmReceived(char call);
    int readInt(int numberDecimals);
    char readChar(int numberChars);
    String readLine();
    bool readBool();
    void sendChar(char call);
    void sendChars(char calls[], int arrLen);
    void sendBool(bool boo);
    void sendIntArray(int intArray[], int arrLen);
    void sendBoolArray(bool boolArray[], int arrLen);
};

#endif