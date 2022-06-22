/*
 This is the code for the lcd display. Changing curPlanet will change the name of the planet displayed.
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

String curPlanet;
String prevPlanet;

void setup() {
  curPlanet = "Mercury";
  
  lcd.begin();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  if(curPlanet != prevPlanet){
    lcd.clear();
  }
  prevPlanet = curPlanet;
  
  lcd.setCursor(2, 0);
  lcd.print("Destination:");

  lcd.setCursor(2, 1);
  lcd.print(curPlanet);

  //The following lines are just for testing purposes
  delay(500);
  curPlanet = "Earth";

}
