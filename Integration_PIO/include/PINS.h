#pragma once

const int temperatureColdPin = 2;
const int temperatureHotPin = 3;
const int dialOxygenPin = 16;
const int dialGForcePin = 14;
const int dialPressurePin = 15;
const int vapeMosfetPin = 5;
const int vapeFanMosfetPin = 4;
const int multiplexerSelectPin1 = 8;
const int multiplexerSelectPin2 = 7;
const int multiplexerSelectPin3 = 6;
const int buttonLEDPin = 17;
const int buttonSwitchPin = 18;  // pin 18 needed for interrupt sequence

const int generalLEDPin = 9;
const int ringLEDPin = 10;
const int travelLEDPin = 11;
const int toxicityLEDPin = 12;
const int tempLEDPin = 13;

// Analog pins (mapped according to schema below)
const int multiplexerReadPin1 = 54;
const int multiplexerReadPin2 = 55;
const int multiplexerReadPin3 = 56;
const int humidifierMosfetPin = 57;
const int smellMosfetPin = 58;

/* Analog pin mapping on Arduino Mega2560
A0 = D54
A1 = D55
A2 = D56
A3 = D57
A4 = D58
A5 = D59
A6 = D60
A7 = D61

A8 = D62
A9 = D63
A10 = D64
A11 = D65
A12 = D66
A13 = D67
A14 = D68
A15 = D69
 */