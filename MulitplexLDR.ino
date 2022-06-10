 /* 
Multiplexer reading 8 LDR sensors and storing value in array
Based on example by MehranMaleki 
*/


//Mulitplexer control pins
int s0 = 2;
int s1 = 3;
int s2 = 4;

//Mux in "Z" pin
int Z_pin = 0;


//Output value array
int Outputs [8] = {0,0,0,0,0,0,0,0};

//thresholds
int thresh = 1; // value needs to be adjusted
int BinOut [8] = {0,0,0,0,0,0,0,0}; // 1: planet gone 0: planet there

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
      Serial.print("Value at channel ");
      Serial.print(i);
      Serial.print("is : ");
      //Serial.println(readLDR(i));
      Outputs [i] = readLDR (i);
      Serial.println(Outputs[i]);
      if (Outputs [i] <= 2){
        BinOut [i] = 0;
      }
      if (Outputs [i] > 2){
        BinOut [i] = 1;
      }
      delayInLoop(500);
      i++;
    }
  for(int b = 0; b < 8; b ++ ){
    Serial.println(BinOut[b]);
  }
 /*int peterDoesNotKnowHowToCode = analogRead(A0); 
 Serial.println(peterDoesNotKnowHowToCode);*/
}




float readLDR(int channel){
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
