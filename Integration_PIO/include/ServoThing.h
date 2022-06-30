#include <Servo.h>

class ServoThing
{
private:
    int pin;
    float minValue, maxValue;
    Servo servo;
    bool logScale;

public:
    /*!
@brief  Constructor for the servo
@param  pin         Pin where the servo is connected
@param  minValue    Minimal expected value to be passed to this servo / dial
@param  maxValue    Maximal expected value to be passed to this servo / dial
@return ServoController object
*/
    ServoThing(int pin, float minValue, float maxValue)
    {
        this->pin = pin;
        this->minValue = minValue;
        this->maxValue = maxValue;
        this->logScale = false;
    }

    /*!
    @brief  Constructor for the servo
    @param  pin         Pin where the servo is connected
    @param  minValue    Minimal expected value to be passed to this servo / dial
    @param  maxValue    Maximal expected value to be passed to this servo / dial
    @param  log         Boolean for enabling log mapping
    @warning    If logarithmic scale is enabled, the minValue will be put to 0!
    @return ServoController object
    */
    ServoThing(int pin, float minValue, float maxValue, bool log)
    {
        this->pin = pin;
        this->logScale = log;
        if (logScale)
            this->minValue = 0;
        else
            this->minValue = minValue;
        this->maxValue = maxValue;
    }

    /**
     * @brief Starting the servo
     * 
     */
    void begin()
    {
        servo.attach(pin);
    }

    /*!
    @brief  Move the servo to specified position
    @param  value   Input value, will be mapped according to the min- and max value
    */
    void move(float value)
    {
        if (!logScale)
        {
            // normal linear mapping
            int position = map(value, minValue, maxValue, 0, 180);
            servo.write(position);
        }
        else
        {
            // logarithmic mapping
            int position = log(value + 1) / log(maxValue) * 180;
            servo.write(position);
        }
    }
};