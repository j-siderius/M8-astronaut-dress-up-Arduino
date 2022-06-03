#include "Timer.h"

/*!
    @brief  Timer contructor initializes timer and delay
    @param  delay   Delay between timer intervals
    @return Timer object
*/
Timer::Timer(int delay)
{
    this->delay = delay;
    this->previousTime = 0;
    this->runTimer = true;
}

/*!
    @brief  Checks if timer is ready to run
    @param  time    Current time, to be compared with internal previous time
    @return Boolean true if timer is ready, else false
*/
bool Timer::check(unsigned long time)
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
    @brief  Changes the delay from initialization
    @param  delay   Delay between timer intervals
*/
void Timer::changeDelay(int delay)
{
    this->delay = delay;
}

/*!
    @brief  Sets the internal boolean to enable running of the timer
*/
void Timer::start()
{
    this->runTimer = true;
}

/*!
    @brief  Sets the internal boolean to disable running of the timer
*/
void Timer::stop()
{
    this->runTimer = false;
}