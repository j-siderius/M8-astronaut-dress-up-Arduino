#ifndef Timer_h
#define Timer_h

#include <Arduino.h>

class Timer
{
private:
    unsigned long previousTime;
    int delay;
    bool runTimer;

public:
    Timer(int delay);
    bool check(unsigned long time);
    void changeDelay(int delay);
    void start();
    void stop();
};

#endif