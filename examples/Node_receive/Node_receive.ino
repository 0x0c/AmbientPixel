#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <skInfraredCOM.h>
#include <Adafruit_NeoPixel.h>
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
	AmbientPixel::Packet packet = pixel.receive();
	if (packet != NULL) {
		Serial.println(packet.id, DEC);
		Serial.println(packet.data, DEC);
		Serial.println("---");
	}
}