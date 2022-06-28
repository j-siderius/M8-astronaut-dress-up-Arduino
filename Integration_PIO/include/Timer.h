#pragma once

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
    /*!
    @brief  Timer contructor initializes timer and delay
    @param  delay   Delay between timer intervals
    @return Timer object
*/
    Timer(int delay)
    {
        this->delay = delay;
        this->previousTime = 0;
        this->runTimer = true;
    }

    /*!
        @brief  Timer contructor initializes timer, delay and callback function
        @param  delay   Delay between timer intervals
        @param  callback    Callback function when timer hits
        @return Timer object
    */
    Timer(int delay, void (*callback)())
    {
        this->delay = delay;
        this->previousTime = 0;
        this->runTimer = true;
        this->callback = callback;
    }

    /*!
        @brief  Timer contructor initializes timer, delay and callback function with integer parameter
        @param  delay   Delay between timer intervals
        @param  callback    Callback function when timer hits, including int parameter
        @return Timer object
    */
    Timer(int delay, void (*callbackInt)(int))
    {
        this->delay = delay;
        this->previousTime = 0;
        this->runTimer = true;
        this->callbackInt = callbackInt;
    }

    /*!
        @brief  Checks if timer is ready to run
        @param  time    Current time, to be compared with internal previous time
        @return Boolean true if timer is ready, else false
    */
    bool check(unsigned long time)
    {
        if (runTimer)
        {
            if (time > previousTime + delay)
            {
                previousTime = time;
                return true;
            }
            else
            {
                return false;
            }
        }
        return false;
    }

    /*!
        @brief  Checks if timer is ready and runs specified callback when it is
        @param  time    Current time, to be compared with internal previous time
        @return Boolean true if timer is ready, else false
    */
    bool runCheck(unsigned long time)
    {
        if (check(time))
        {
            callback();
            return true;
        }
        return false;
    }

    /*!
        @brief  Checks if timer is ready and runs specified callback when it is
        @param  time    Current time, to be compared with internal previous time
        @param  param   Callback parameter
        @return Boolean true if timer is ready, else false
    */
    bool runCheck(unsigned long time, int param)
    {
        if (check(time))
        {
            callbackInt(param);
            return true;
        }
        return false;
    }

    /*!
        @brief  Changes the delay from initialization
        @param  delay   Delay between timer intervals
    */
    void changeDelay(int delay)
    {
        this->delay = delay;
    }

    /*!
        @brief  Changes the callback function from initialization
        @param  callback   Callback function when timer hits
    */
    void changeCallback(void (*callback)())
    {
        this->callback = callback;
    }

    /*!
        @brief  Changes the callback function from initialization
        @param  callback   Callback function when timer hits
    */
    void changeCallback(void (*callbackInt)(int))
    {
        this->callbackInt = callbackInt;
    }

    /*!
        @brief  Sets the internal boolean to enable running of the timer
    */
    void start()
    {
        this->runTimer = true;
    }

    /*!
        @brief  Sets the internal boolean to disable running of the timer
    */
    void stop()
    {
        this->runTimer = false;
    }
};