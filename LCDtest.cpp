// include LCD library
#include <LiquidCrystal_I2C.h>

// object for LCD
// @warning THIS OBJECT CANNOT BE MADE OUTSIDE OF MAIN FILE!
// @note  lcd object must be made before making the DestinationLCD object
LiquidCrystal_I2C lcd(0x27, 16, 2);

// include the LCD library
#include "DestinationLCD.h";

// make LCD object
DestinationLCD destination;


void setup()
{
  // initialise the LCD
  destination.LCDinit();
  // set the initial LCD text
  destination.LCDupdate("Earth");
}

void loop()
{
  // TODO: delete testing code
  delay(2000);  // Arbitrary test delay to show functionality
  // change the planet text, this function only needs to be called when we want to update, not on a regular interval!
  destination.LCDupdate("Mercury");
}
