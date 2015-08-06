#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
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
	int i;
	for (i = 0x30 ; i < 0x7b ; i++) {
		pixel.send((unsigned char)i, spx_send_broadcast);
		delay(10);
	}
}