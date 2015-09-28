#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <skInfraredCOM.h>
#include <Adafruit_NeoPixel.h>
#include <AmbientPixel.h>

using namespace AmbientPixel;

Pixel pixel(AmbientPixel::Pixel::Vertex::Triangle);

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);
}

void loop()
{
	if(Serial.available()){
		// アプリからパケットを受信
		char data = Serial.read();
		switch (data) {
		    case 'a': {
				Serial.println("NW");
				pixel.send(0, Packet::packet_data(0b00100000, Pixel::Flag::Control, Pixel::ControlFlag::Network));
				pixel.send(1, Packet::packet_data(0b01000000, Pixel::Flag::Control, Pixel::ControlFlag::Network));
				pixel.send(2, Packet::packet_data(0b01100000, Pixel::Flag::Control, Pixel::ControlFlag::Network));
		    }
		      break;
		    case 'b': {
				Serial.println("Send Glow:Red");
				pixel.send(0, Packet::packet_data(0b00100000, Pixel::Flag::Glow, Pixel::Color::Red));
		    }
		      break;
		    default:
		      break;
		}
	}

	for(int i = 0; i < pixel.number_of_vertex; i++){
		// 各ポートを監視する
		uint8_t data = pixel.watch(i);
		if(data != 0){
		    pixel.receive(i, data);
		}
	}
}