#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <skInfraredCOM.h>
#include <Adafruit_NeoPixel.h>
#include <AmbientPixel.h>

AmbientPixel::Pixel pixel(AmbientPixel::Pixel::Vertex::Triangle);
void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);
}

void loop()
{
	delay(1000);
}

