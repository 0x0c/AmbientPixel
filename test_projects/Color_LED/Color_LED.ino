// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
//#include <StandardCplusplus.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            10

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1
#define COLORNUM 10 //色の種類

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

/*
int color[10];

static class pix{
  public:
  int r, g, b;
  pix(int red, int green, int blue);
};

pix::pix(int red, int green, int blue){
    int r = red;
    int g = green;
    int b = blue;
  }

  pix A(100, 0, 0); //red
  pix B(0, 100, 0); //green
  pixel int color[2](0, 0, 100); //blue
  pixel int color[3](100, 100, 0); //yellow
  pixel int color[4](100, 0, 100); //perple
*/

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(200);

}

void loop() {
  // st:開始の色 en:終了の色 playtime:再生時間(s) repeat:繰り返し回数
  // 色 1:red,2:green,3:blue,4:orange,5:yellow,6:perple,7:indigo
  rainbow(1,2,2,5);//赤→緑
  rainbow(2,6,2,5);//緑→紫
  rainbow(6,2,2,5);//紫→緑
  //delay(5000);
  
}


// switch版
// st:開始の色 en:終了の色 playtime:再生時間(s) repeat:繰り返し回数
void rainbow(int st, int en, int playtime, int repeat){
  float str, stg, stb;
  float enr, eng, enb;

  switch(st){
    case 1:
    //red
      str = 100;
      stg = 0;
      stb = 0;
      break;
    //green
    case 2:
      str = 0;
      stg = 100;
      stb = 0;
      break;
    //blue
    case 3:
      str = 0;
      stg = 0;
      stb = 100;
      break;
    case 4:
    //orange
      str = 100;
      stg = 50;
      stb = 0;
      break;
    //yellow
    case 5:
      str = 100;
      stg = 100;
      stb = 0;
      break;
    //perple
    case 6:
      str = 100;
      stg = 0;
      stb = 100;
      break;
    //indigo
    case 7:
      str = 0;
      stg = 50;
      stb = 100;
      break;
    default:
      break;
  }

  switch(en){
    case 1:
    //red
      enr = 100;
      eng = 0;
      enb = 0;
      break;
    //green
    case 2:
      enr = 0;
      eng = 100;
      enb = 0;
      break;
    //blue
    case 3:
      enr = 0;
      eng = 0;
      enb = 100;
      break;
    case 4:
    //orange
      enr = 100;
      eng = 50;
      enb = 0;
      break;
    //yellow
    case 5:
      enr = 100;
      eng = 100;
      enb = 0;
      break;
    //perple
    case 6:
      enr = 100;
      eng = 0;
      enb = 100;
      break;
    case 7:
      enr = 0;
      eng = 50;
      enb = 100;
      break;
    default:
      break;
  }


  float dr, dg, db;
  float pt = 1000*playtime/255;

//
  dr = (enr - str)/255;
  dg = (eng - stg)/255;
  db = (enb - stb)/255;
  
  for(int j=0; j<repeat; j++){
    for(int i=0; i <255; i++){

      float r = str + (dr*i);
      float g = stg + (dg*i);
      float b = stb + (db*i);

      pixels.setPixelColor(0, r, g, b);
      pixels.show();
      delay(pt);
    }
  }
}



