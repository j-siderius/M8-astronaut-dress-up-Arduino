#ifndef Serialcomm_h
#define Serialcomm_h

#include <Arduino.h>

class Serialcomm
{
private:
    struct Func {
      char call;
      void (*callback)();
    };
    Func functions[20];
    int index = 0;
    int byteTimeout = 2;

public:
    Serialcomm();
    void addFunction(char call, void (*callback)());
    void updateSerial();
    void checkCalls(char incomingByte);
    int readVar(int numberDecimals);
    bool readBool();
};

#endif
