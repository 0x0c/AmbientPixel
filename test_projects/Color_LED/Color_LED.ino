// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            10

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(50);
}

void loop() {
  //rainbow(再生時間(s),色パターン)
  //pattern1:赤->緑 2:緑->青 3:青->赤
  rainbow(5, 3, 3); 
  exit(0);
}

void rainbow(uint8_t playtime, int color_pattern, int lop) {
  uint16_t j;
  int col = color_pattern;
  double pt = 1000*playtime/256;
  
  for(int i=0; i<lop; i++){
    for(j=0; j<256; j++) {
      pixels.setPixelColor(0, Wheel(j & 255, col));
      pixels.show();
      delay(pt); //変化時間を操作することができる 1000ms=1s
    }
  }
}
uint32_t Wheel(byte WheelPos, int color) {
    
  switch(color){
    case 1:
      return pixels.Color(255 - WheelPos, WheelPos, 0);
      break;
    case 2:
      return pixels.Color(0, 255 - WheelPos, WheelPos);
      break;
    case 3:
      return pixels.Color(WheelPos, 0, 255 - WheelPos);
    default:
      break;
  }
}


/*  
  WheelPos = 255 - WheelPos;


  
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
*/


/*
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
*/





