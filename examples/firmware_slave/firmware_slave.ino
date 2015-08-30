#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <skInfraredCOM.h>
#include <Adafruit_NeoPixel.h>
#include <AmbientPixel.h>

AmbientPixel::Pixel *pixel;
void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);
}

void loop()
{
	if(pixel == NULL){
		if(Serial.available()){
		    uint8_t device_id = Serial.read();
		    pixel = new AmbientPixel::Pixel(device_id, AmbientPixel::Pixel::Vertex::Triangle);
		}
	}
	else {
		pixel->perform();
	}
}

