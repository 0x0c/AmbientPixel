#include <Adafruit_NeoPixel.h>
#include <skInfraredCOM.h>

skInfraredCOM Infrared(2, 11);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, 10, NEO_GRB + NEO_KHZ800);
void setup()
{
	Serial.begin(9600);
	pixels.begin();
}

void loop()
{
	unsigned char data = Infrared.Receive(0x0a);
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
