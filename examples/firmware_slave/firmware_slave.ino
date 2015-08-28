#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <skInfraredCOM.h>
#include <AmbientPixel.h>

uint8_t device_id = 0x01;
AmbientPixel::Pixel pixel(device_id, AmbientPixel::Pixel::Vertex::Triangle);
void setup()
{
   // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{
  // uint8_t data[16] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f};
  AmbientPixel::Packet echo_packet(pixel.packet_id(), AmbientPixel::Packet::Type::Echo, NULL, 0, AmbientPixel::Packet::Dest::Broadcast);
  
  uint8_t port_no = 0;
  pixel.send(port_no, echo_packet);
  
  delay(1000);
}

