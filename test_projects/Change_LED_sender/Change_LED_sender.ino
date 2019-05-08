#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <skInfraredCOM.h>

skInfraredCOM Infrared(-1, 3);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, 10, NEO_GRB + NEO_KHZ800);
void setup()
{
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
	Serial.begin(9600);
	pixels.begin();
}
void loop()
{
	data= Infrared.Receive(0x0a);
	if (data!= 0) {
		Serial.println(data, DEC);
		switch(data % 3) {
			case 0: 
				pixels.setPixelColor(0, pixels.Color(150,0,0));
			break;
			case 1:
				pixels.setPixelColor(0, pixels.Color(0,150,0));
			break;
			case 2:
				pixels.setPixelColor(0, pixels.Color(0,0,150));
			break;
		}
		pixels.show();
	}
}
