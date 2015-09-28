#include <Adafruit_NeoPixel.h>
#include <skInfraredCOM.h>

skInfraredCOM Infrared(2, 11);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, 10, NEO_GRB + NEO_KHZ800);
void setup()
{
	Serial.begin(9600);
	pixels.begin();
}
void loop()
{
	if(Serial.available()){
		Infrared.Send(0x0a, Serial.read());
	}
}
