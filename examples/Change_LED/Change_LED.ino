#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <skInfraredCOM.h>
#include <Adafruit_NeoPixel.h>
#include <AmbientPixel.h>

uint8_t device_id = 0x01;
AmbientPixel::Pixel node(device_id, AmbientPixel::Pixel::Vertex::Triangle);

void setup()
{
	// put your setup code here, to run once:
}

void loop()
{
	// put your main code here, to run repeatedly:
 	node.transform_color(AmbientPixelColorAttrRed, AmbientPixelColorAttrBlue, 5, 1);
	delay(1000);
}