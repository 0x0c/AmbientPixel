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
	Serial.println("<<AmbientPixel Start>>");
}

void loop()
{
	for(int i = 0; i < pixel.number_of_vertex; i++) {
		// 各ポートを監視する
		uint8_t data = pixel.watch(i);
		if(data != 0) {
			Serial.println(data, BIN);
		    pixel.receive(i, data);
		}
		delay(50);
	}
}

void serialEvent()
{
	// アプリからパケットを受信
	char data = Serial.read();
	switch (data) {
		case 'a': {
			pixel.receive(0, Packet::packet_data(0b00000000, Pixel::Flag::Glow, Pixel::Color::Red));
		}
			break;
		case 'b': {
			pixel.receive(0, Packet::packet_data(0b00000000, Pixel::Flag::Glow, Pixel::Color::Green));
		}
			break;
		case 'c': {
			pixel.receive(0, Packet::packet_data(0b00000000, Pixel::Flag::Glow, Pixel::Color::Blue));
		}
			break;
		case 'd': {
			pixel.receive(0, Packet::packet_data(0b00000000, Pixel::Flag::Blink, Pixel::Color::Blue));
		}
			break;
		case 'e': {
			pixel.receive(0, Packet::packet_data(0b00000000, Pixel::Flag::TurnOff, NULL));
		}
			break;
		default:
			break;
	}
	Serial.flush();
}
