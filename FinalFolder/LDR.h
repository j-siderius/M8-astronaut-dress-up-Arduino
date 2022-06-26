#ifndef LDR_h
#define LDR_h

#include <Arduino.h>

class LDR
{
private: 
  //Mulitplexer control pins
  int dPin[6];


  //Muliplex Analog in in "Z" pin
  char zPin[3];


  //Output value arrays
  float Output [3][8] ={
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  };

  //binary arrays, 0 means the value at the LDR is under the threshold and the object is in its place
  int BinOutput [3][8] ={
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  };

  //threshold
  float thresh = 1.5; 
  // 1.5v of voltage is a good estimate of threshold betwen the v of an ldr that is blacked out and one that isn't
  // might need adjustment acoording to test results

public:
  LDR (int dPin[6], char zPin[3]){
    this->dPin[6] = dPin[6];
    this->zPin[3] = zPin[3];

  };
  
  //function to fetch new LDR values and store in Arrays 


  void updateArrays() {
    for ( int n = 0; n<3; n++){
      for(int i = 0; i<8; i++){
        Output[n][i] = readLDR(i, zPin[n], n);
        if (Output[n][i]<= thresh){
          BinOutput[n][i] = 1;
        }
        else {
          BinOutput [n][i] = 0;
        }
      }    
    }
  }

  //function returning the float value of individuals LDRs
  float readLDR(int channel, char zPin, int sect){

    int muxChannel[8][3]={
      {0,0,0}, //channel 0
      {1,0,0}, //channel 1
      {0,1,0}, //channel 2
      {1,1,0}, //channel 3
      {0,0,1}, //channel 4
      {1,0,1}, //channel 5
      {0,1,1}, //channel 6
      {1,1,1}, //channel 7
    };

    //loop through the 3 bits
    for(int i = 0+sect; i < 3+sect; i ++){
      digitalWrite(dPin[i], muxChannel[channel][i]);
    }

    //read the value at the Z pin
    int val = analogRead(zPin);

    //return the value
    float voltage = (val * 5.0) / 1024.0; //use for voltage
    //return val;
    return voltage;  
}
};




#endif