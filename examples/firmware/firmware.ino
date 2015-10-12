#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <skInfraredCOM.h>
#include <Adafruit_NeoPixel.h>
#include <AmbientPixel.h>

using namespace AmbientPixel;

uint8_t device_id = 0b00000001; // 0b00000000 ~ 0b00000111まで上位3bitを使用
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
  /*
	uint8_t data = pixel.watch(cnt);
	if(data != 0) {
	    pixel.receive(cnt, data);
	}
 */
	//cnt = (cnt + 1) % 3;
}

void serialEvent()
{
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

    case 'r': {
      pixel.send(0, Packet::packet_data(0b01000000, Pixel::Flag::Glow, Pixel::Color::Red));
      pixel.send(0, Packet::packet_data(0b01100000, Pixel::Flag::Glow, Pixel::Color::Red));
      pixel.send(0, Packet::packet_data(0b10000000, Pixel::Flag::Glow, Pixel::Color::Red));

      //pixel.receive(0, Packet::packet_data(0b00100000, Pixel::Flag::Glow, Pixel::Color::Red));
    }
      break;
    case 'g': {
      pixel.send(0, Packet::packet_data(0b01000000, Pixel::Flag::Glow, Pixel::Color::Green));
      pixel.send(0, Packet::packet_data(0b01100000, Pixel::Flag::Glow, Pixel::Color::Green));
      pixel.send(0, Packet::packet_data(0b10000000, Pixel::Flag::Glow, Pixel::Color::Green));

      //pixel.receive(0, Packet::packet_data(0b00100000, Pixel::Flag::Glow, Pixel::Color::Green));
    }
      break;
    case 'b': {
      pixel.send(0, Packet::packet_data(0b01000000, Pixel::Flag::Glow, Pixel::Color::Blue));
      pixel.send(0, Packet::packet_data(0b01100000, Pixel::Flag::Glow, Pixel::Color::Blue));
      pixel.send(0, Packet::packet_data(0b10000000, Pixel::Flag::Glow, Pixel::Color::Blue));

      pixel.receive(0, Packet::packet_data(0b00100000, Pixel::Flag::Glow, Pixel::Color::Blue));
    }
      break;
    case 'o': {
      pixel.send(0, Packet::packet_data(0b01000000, Pixel::Flag::TurnOff, Pixel::Color::Off));
      pixel.send(0, Packet::packet_data(0b01100000, Pixel::Flag::TurnOff, Pixel::Color::Off));
      pixel.send(0, Packet::packet_data(0b10000000, Pixel::Flag::TurnOff, Pixel::Color::Off));

      //pixel.receive(0, Packet::packet_data(0b00100000, Pixel::Flag::TurnOff, Pixel::Color::Off));
    }
      break;
    case 'R': {
      pixel.send(0, Packet::packet_data(0b01000000, Pixel::Flag::Blink, Pixel::Color::Red));
      pixel.send(0, Packet::packet_data(0b01100000, Pixel::Flag::Blink, Pixel::Color::Red));
      pixel.send(0, Packet::packet_data(0b10000000, Pixel::Flag::Blink, Pixel::Color::Red));

      //pixel.receive(0, Packet::packet_data(0b00100000, Pixel::Flag::Blink, Pixel::Color::Red));
    }
      break;
    case 'G': {
      pixel.send(0, Packet::packet_data(0b01000000, Pixel::Flag::Blink, Pixel::Color::Green));
      pixel.send(0, Packet::packet_data(0b01100000, Pixel::Flag::Blink, Pixel::Color::Green));
      pixel.send(0, Packet::packet_data(0b10000000, Pixel::Flag::Blink, Pixel::Color::Green));

      //pixel.receive(0, Packet::packet_data(0b00100000, Pixel::Flag::Blink, Pixel::Color::Green));
    }
      break;
    case 'B': {
      pixel.send(0, Packet::packet_data(0b01000000, Pixel::Flag::Blink, Pixel::Color::Blue));
      pixel.send(0, Packet::packet_data(0b01100000, Pixel::Flag::Blink, Pixel::Color::Blue));
      pixel.send(0, Packet::packet_data(0b10000000, Pixel::Flag::Blink, Pixel::Color::Blue));

      //pixel.receive(0, Packet::packet_data(0b00100000, Pixel::Flag::Blink, Pixel::Color::Blue));
    }
      break;
    default:
      break;
  }
  Serial.flush();
}
