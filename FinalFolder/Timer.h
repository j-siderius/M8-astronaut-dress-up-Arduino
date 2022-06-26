#ifndef Timer_h
#define Timer_h

#include <Arduino.h>

class Timer
{
private:
    unsigned long previousTime;
    int delay;
    bool runTimer;
    void (*callback)();
    void (*callbackInt)(int);

public:
    Timer(int delay);
    Timer(int delay, void (*callback)());
    Timer(int delay, void (*callbackInt)(int));
    bool check(unsigned long time);
    bool runCheck(unsigned long time);
    bool runCheck(unsigned long time, int param);
    void changeDelay(int delay);
    void changeCallback(void (*callback)());
    void changeCallback(void (*callbackInt)(int));
    void start();
    void stop();
};

#endif