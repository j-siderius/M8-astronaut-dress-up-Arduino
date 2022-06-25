// THIS IS AN EXAMPLE CLASS

// @note    Always CamelCase your class names, starting with an uppercase letter (e.g. LightController.h)

#pragma once

#include <Arduino.h>

class ExampleClass
{

private:
    int testInt = 10;
    String name = "Bob";

public:
    /*!
    @brief  This is the constructor function (it does not require a descriptor e.g. void/int/bool!)
    @note   reference internal, private variables in the contructor using the following notation 'this->[variable name]'
    @returns    Example class object
    */
    ExampleClass(String name)
    {
        this->name = name;
    }

    /*!
    @brief  description of the function
    @param  number  description of parameter
    */
    void testFunction(int number)
    {
        int testInt += number;
    }

    /*!
    @brief   description of function
    @param   number  description of parameter
    @return  addition of number plus internal number
    */
    int testNumber(int number)
    {
        return number + testInt;
    }
};