#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <skInfraredCOM.h>
#include <Adafruit_NeoPixel.h>
#include <AmbientPixel.h>

uint8_t device_id = 0x00;
AmbientPixel::Pixel pixel(device_id, AmbientPixel::Pixel::Vertex::Triangle);
void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);
}

void loop()
{

}
