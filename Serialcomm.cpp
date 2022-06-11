#include "Serialcomm.h"

/*!
  @brief  Serial comm constructor sets up serial port
  @warning  THIS LIBRARY CANNOT START THE PORT; add Serial.begin([baudrate]); in setup() yourself!
  @param  baud  Baud rate of serial port
  @return Serialcomm object
*/
Serialcomm::Serialcomm() {
  Serial.println("Serialcomm init");
}

/*!
  @brief  Add a new function to the serial communication protocol
  @param  index  Index of the function in the list
  @param  call   Character that calls this function
  @param  callback  Function that will be called when call is registered
*/
void Serialcomm::addFunction(int index, char call, void (*callback)()) {
  this->functionCall[index] = call;
  this->functionCallback[index] = callback;
}

/*!
  @brief  Update the callback function of specific call
  @param  index  Index of the function in the list
  @param  callback  Function that will be called when call is registered
*/
void Serialcomm::updateFunctionCallback(int index, void (*callback)()) {
  this->functionCallback[index] = callback;
}

/*!
  @brief  Update serial port and read incoming byte
*/
void Serialcomm::updateSerial() {
  while (Serial.available() > 0) {
    char incomingByte = Serial.read();
    this->checkCalls(incomingByte);
  }
}

/*!
  @brief  Loops though all registered calls and runs the associated function if call is found
  @throws Error when call is not recognized
*/
void Serialcomm::checkCalls(char incomingByte) {
  if (incomingByte >= 33 && incomingByte < 127) {
    for (int i = 0; i < sizeof(functionCall) - 1; i++) {
      if (incomingByte == functionCall[i]) {
        functionCallback[i]();
        return;
      }
    }

    // disable to avoid abmiguity
    Serial.print("Function '");
    Serial.print(incomingByte);
    Serial.println("' not found");
  }
}

/*!
  @brief  Reads the specified amount of bytes from serial port and returns the variable as an int
  @returns integer of variable from serial
  @throws Timeout when not enough bytes are received within the byteTimeout time
*/
int Serialcomm::readVar(int numberDecimals) {
  int timeOut = byteTimeout * numberDecimals;
  char buf[numberDecimals];
  int variable;
  
  Serial.setTimeout(timeOut);

  Serial.readBytes(buf, numberDecimals);
  variable = String(buf).toInt();
  
  Serial.setTimeout(1000);

  return variable;
}

/*!
  @brief  Reads the boolean from the serial port and returns it
  @returns Boolean from variable
*/
bool Serialcomm::readBool() {
  return Serial.read();
}