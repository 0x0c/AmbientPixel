#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <skInfraredCOM.h>
#include <AmbientPixel.h>

AmbientPixel::Pixel pixel(0x01, AmbientPixel::Pixel::Vertex::Triangle);
void setup()
{
 	// put your setup code here, to run once:
 	Serial.begin(9600);
}

void loop()
{
	unsigned char data[16] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f};
	AmbientPixel::Packet packet(pixel.packet_id(), data, 16, AmbientPixel::Packet::Dest::Broadcast);
	pixel.send(0, packet);
	delay(1000);
}
