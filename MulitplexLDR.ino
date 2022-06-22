 /* 
This program reads values of a set of three 8 channel Multiplexers reading 8 LDR sensors each and stores the values in arrays.
Completes threshold comparison for further communication
Based on example by MehranMaleki 
*/


//Mulitplexer control pins
int dPin[6] = {2,3,4,5,6,7};


//Muliplex Analog in in "Z" pin
char zPin[3] = {A0,A1,A2};


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
float thresh = 1.0; // 1v of voltage is a good estimate of threshold betwen the v of an ldr that is blacked out and one that isn't

void setup(){
  for (int i = 0; i<6; i++ ){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);    
  }

  Serial.begin(9600);
}


void loop()
{
  updateArrays();
}

void updateArrays() {
  for ( int n = 0; n<3; n++){
    for(int i = 0; i<8; i++){
      Output[n][i] = readLDR (i, zPin[n], n);
      if (Output[n][i]<= thresh){
        BinOutput[n][i] = 1;
      }
      else {
        BinOutput [n][i] = 0;
      }      
      Serial.print("LDR ");
      Serial.print(n);
      Serial.print(".");
      Serial.print(i);
      Serial.print(" : ");
      Serial.print(Output[n][i]);
      Serial.print("  There? ->   ");
      Serial.println(BinOutput[n][i]);
      delayInLoop(500);

    }    
  }
}



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

void delayInLoop(long microSeconds)
{    
  microSeconds *= 1000;
  const unsigned long start = micros();
   while (true)
   {
       unsigned long now = micros();
       if (now - start >= microSeconds)
       {
           return;
       }
   }
}
