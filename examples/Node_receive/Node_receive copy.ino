#include <skInfraredCOM.h>
#include <AmbientPixel.h>

AmbientPixel::Pixel pixel(0x01);
void setup()
{
 	// put your setup code here, to run once:
 	Serial.begin(9600);
}

void loop()
{
	// put your main code here, to run repeatedly:
	unsigned char data = pixel.receive();
	if (data != 0) {
		Serial.println(data, DEC);
	}
}