#pragma once

#include <Arduino.h>
#include "LiquidCrystal_I2C.h"

class DestinationLCD 
{

  private:
    String planetName;

  public:
    /*!
      @brief  initialisation function for the LCD screen
      @warning  THIS CLASS CANNOT START THE LCD OBJECT; add LiquidCrystal_I2C lcd([address], [chars], [columns]); in main yourself!
    */
    void LCDinit() {
      lcd.init();
      lcd.backlight();
      lcd.clear();

      lcd.setCursor(2, 0);
      lcd.print("Destination:");
    }

    /*!
    @brief  updates the destination planet on the LCD screen
    @param  name  new Planet name
    @note does not update the screen if name is the same as current name
    */
    void LCDupdate(String name) {
      if (name != planetName) {
        planetName = name;
        lcd.clear();

        lcd.setCursor(2, 0);
        lcd.print("Destination:");
        lcd.setCursor(2, 1);
        lcd.print(planetName);
      }
    }

};