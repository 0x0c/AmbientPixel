#include "AmbientPixel.h"

namespace AmbientPixel
{
	// -------------------------- Pixel --------------------------
	Pixel::Pixel(uint8_t number_of_vertex) {
		for (uint8_t i = 0; i < number_of_vertex; ++i) {
			this->ports.push_back(new skInfraredCOM(i * 2, i * 2 + 1));
		}
		this->device_id = device_id;
		this->number_of_vertex = number_of_vertex;
		this->led = Adafruit_NeoPixel(1, 13, NEO_GRB + NEO_KHZ800);
		this->led.setBrightness(200);
	}
	
	void Pixel::send(uint8_t port_no, AmbientPixel::Packet *packet) {
		this->ports[port_no]->Send(port_no, (unsigned char)packet->data());
	}

	uint8_t Pixel::receive(uint8_t port_no) {
		return this->ports[port_no]->Recive(this->device_id);
	}

	// TODO:
	// LEDを点灯させる
	void Pixel::change_led(uint8_t flag, uint8_t color) {

	}

	// -------------------------- Packet --------------------------
	Packet::Packet(uint8_t device_id, uint8_t flag, uint8_t color) {
		this->device_id = device_id;
		this->flag = flag;
		this->color = color;
	};

	// 1byteのパケットデータを取得する
	uint8_t Packet::data() {
		return this->device_id | this-> flag | this->color;
	}
};
