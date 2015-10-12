#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <skInfraredCOM.h>
#include <Adafruit_NeoPixel.h>
#include <AmbientPixel.h>

using namespace AmbientPixel;

uint8_t device_id = 0b00000110; // 0b00000000 ~ 0b11100000まで上位3bitを使用
Pixel pixel(AmbientPixel::Pixel::Vertex::Triangle);

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);
	Serial.println("<<AmbientPixel Start>>");
	pixel.device_id = device_id;
}

int cnt = 0;
void loop()
{
	uint8_t data = pixel.watch(cnt);
	if(data != 0) {
	    pixel.receive(cnt, data);
	}
	cnt = (cnt + 1) % 3;
}

void serialEvent()
{
	// アプリからパケットを受信
	char data = Serial.read();
	switch (data) {
		case '-': {
			pixel.send(0, Packet::packet_data(0b00000000, Pixel::Flag::Control, Pixel::ControlFlag::Reset));
			pixel.send(1, Packet::packet_data(0b00000000, Pixel::Flag::Control, Pixel::ControlFlag::Reset));
			pixel.send(2, Packet::packet_data(0b00000000, Pixel::Flag::Control, Pixel::ControlFlag::Reset));
		}
			break;
		case '=': {
			pixel.send(0, Packet::packet_data(0b00100000, Pixel::Flag::Control, Pixel::ControlFlag::Network));
			pixel.send(1, Packet::packet_data(0b01000000, Pixel::Flag::Control, Pixel::ControlFlag::Network));
			pixel.send(2, Packet::packet_data(0b01100000, Pixel::Flag::Control, Pixel::ControlFlag::Network));
		}
			break;
		case '1': {
			pixel.send(0, Packet::packet_data(0b00100000, Pixel::Flag::Glow, Pixel::Color::Red));
		}
			break;
		case '2': {
			pixel.send(0, Packet::packet_data(0b00100000, Pixel::Flag::Glow, Pixel::Color::Green));
		}
			break;
		case '3': {
			pixel.send(0, Packet::packet_data(0b00100000, Pixel::Flag::Glow, Pixel::Color::Blue));
		}
			break;
		case '4': {
			pixel.send(0, Packet::packet_data(0b00100000, Pixel::Flag::TurnOff, NULL));
		}
			break;

		case 'a': {
			pixel.send(0, Packet::packet_data(0b01000000, Pixel::Flag::Glow, Pixel::Color::Red));
		}
			break;
		case 'b': {
			pixel.send(0, Packet::packet_data(0b01000000, Pixel::Flag::Glow, Pixel::Color::Green));
		}
			break;
		case 'c': {
			pixel.send(0, Packet::packet_data(0b01000000, Pixel::Flag::Glow, Pixel::Color::Blue));
		}
			break;
		case 'd': {
			pixel.send(0, Packet::packet_data(0b01000000, Pixel::Flag::TurnOff, NULL));
		}
			break;
		default:
			break;
	}
	Serial.flush();
}
