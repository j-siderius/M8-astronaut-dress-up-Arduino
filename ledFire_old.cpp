#include <Adafruit_NeoPixel.h>

#define PIN 13
#define CNT 16

Adafruit_NeoPixel strip = Adafruit_NeoPixel(CNT, PIN, NEO_GRB + NEO_KHZ800);

uint32_t fire_color   = strip.Color ( 80,  40,  10);
uint32_t off_color    = strip.Color (  0,  0,  0);

class NeoFire
{
  Adafruit_NeoPixel &strip;
  public:

  NeoFire(Adafruit_NeoPixel&);
  void Draw();
  void Clear();
  void AddColor(uint8_t position, uint32_t color);
  void SubstractColor(uint8_t position, uint32_t color);
  uint32_t Blend(uint32_t color1, uint32_t color2);
  uint32_t Substract(uint32_t color1, uint32_t color2);
};

NeoFire::NeoFire(Adafruit_NeoPixel& n_strip)
: strip (n_strip)
{
}

///
/// Set all colors
///
void NeoFire::Draw(){
  Clear();
  
  for(int i=0;i<CNT;i++)
    {
    AddColor(i, fire_color);
    int r = random(50);
    uint32_t diff_color = strip.Color (r/2, r-r/4, r);
    SubstractColor(i, diff_color);
    }
    
  strip.show();
}

///
/// Set color of LED
///
void NeoFire::AddColor(uint8_t position, uint32_t color){
  uint32_t blended_color = Blend(strip.getPixelColor(position), color);
  strip.setPixelColor(position, blended_color);
}

///
/// Set color of LED
///
void NeoFire::SubstractColor(uint8_t position, uint32_t color){
  uint32_t blended_color = Substract(strip.getPixelColor(position), color);
  strip.setPixelColor(position, blended_color);
}

uint32_t NeoFire::Blend(uint32_t color1, uint32_t color2){
  uint8_t r1,g1,b1;
  uint8_t r2,g2,b2;
  uint8_t r3,g3,b3;
  
  r1 = (uint8_t)(color1 >> 16),
  g1 = (uint8_t)(color1 >>  8),
  b1 = (uint8_t)(color1 >>  0);
  
  r2 = (uint8_t)(color2 >> 16),
  g2 = (uint8_t)(color2 >>  8),
  b2 = (uint8_t)(color2 >>  0);
  
  return strip.Color(constrain(r1+r2, 0, 255), constrain(g1+g2, 0, 255), constrain(b1+b2, 0, 255));
}

uint32_t NeoFire::Substract(uint32_t color1, uint32_t color2){
  uint8_t r1,g1,b1;
  uint8_t r2,g2,b2;
  uint8_t r3,g3,b3;
  int16_t r,g,b;
  
  r1 = (uint8_t)(color1 >> 16),
  g1 = (uint8_t)(color1 >>  8),
  b1 = (uint8_t)(color1 >>  0);
  
  r2 = (uint8_t)(color2 >> 16),
  g2 = (uint8_t)(color2 >>  8),
  b2 = (uint8_t)(color2 >>  0);
  
  r=(int16_t)r1-(int16_t)r2;
  g=(int16_t)g1-(int16_t)g2;
  b=(int16_t)b1-(int16_t)b2;
  if(r<0) r=0;
  if(g<0) g=0;
  if(b<0) b=0;
  
  return strip.Color(r, g, b);
}

void NeoFire::Clear(){
  for(uint16_t i=0; i<strip.numPixels (); i++)
    strip.setPixelColor(i, off_color);
}

NeoFire fire(strip);

void setup(){
  strip.begin();
  strip.show();
}

void loop(){
  fire.Draw();
  delay(random(50,150));
}
