 /* 
This program reads values of a set of double 8 channel Multiplexers reading 8 LDR sensors each and stores the values in arrays.
Completes threshold comparison for further communication
Based on example by MehranMaleki 
*/


//Mulitplexer control pins
int s0 = 2;
int s1 = 3;
int s2 = 4;

//Muliplex Analog in in "Z" pin
int zPlanet = A0;
int zBody = A1;


//Output value arrays
float planetOut [8] = {0,0,0,0,0,0,0,0};
float bodyOut [8] = {0,0,0,0,0,0,0,0};
//binary arrays
int binOutPlanet [8] = {0,0,0,0,0,0,0,0}; // 1: planet gone 0: planet there
int binOutBody [8] = {0,0,0,0,0,0,0,0}; // 1: bodypart gone 0: bodypart there
//threshold
float thresh = 1.0; // 1v of voltage is a good estimate of threshold betwen the v of an ldr that is blacked out and one that isn't

void setup(){
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);

  Serial.begin(9600);
}


void loop()
{
  //Loop through and read all 8 values
  for(int i = 0; i < 8; i ++){
      Serial.print("Value at planet ");
      Serial.print(i);
      Serial.print("is : ");
      //Serial.println(readLDR(i));
      planetOut [i] = readLDR (i,zPlanet);
      Serial.println(planetOut[i]);
      if (planetOut[i] <= thresh){
        binOutPlanet[i] = 0;
      }
      if (planetOut[i] > thresh){
        binOutPlanet[i] = 1;
      }
      delayInLoop(500);
    }
  for(int b = 0; b < 8; b ++ ){
    Serial.println(binOutPlanet[b]);
  }
  for(int i = 0; i < 8; i ++){
      Serial.print("Value at bodypart ");
      Serial.print(i);
      Serial.print("is : ");
      //Serial.println(readLDR(i));
      bodyOut [i] = readLDR (i,zBody);
      Serial.println(bodyOut[i]);
      if (bodyOut[i] <= thresh){
        binOutBody[i] = 0;
      }
      if (bodyOut[i] > thresh){
        binOutBody[i] = 1;
      }
      delayInLoop(500);
    }
  for(int b = 0; b < 8; b ++ ){
    Serial.println(binOutBody[b]);
  }
 /*int peterDoesNotKnowHowToCode = analogRead(A0); 
 Serial.println(peterDoesNotKnowHowToCode);*/
}




float readLDR(int channel, int Z_pin){
  int controlPin[] = {s0, s1, s2};

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

  //loop through the 3 sig
  for(int i = 0; i < 3; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  //read the value at the Z pin
  int val = analogRead(Z_pin);

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