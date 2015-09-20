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
	
	void Pixel::send(uint8_t port_no, uint8_t packet) {
		this->ports[port_no]->Send(port_no, (unsigned char)packet);
	}

	void Pixel::receive(uint8_t data) {
		// TODO: 受診時の処理の実装
	}

	uint8_t Pixel::watch(uint8_t port_no) {
		return this->ports[port_no]->Recive(this->device_id);
	}

	// TODO:
	// LEDを点灯させる
	void Pixel::change_led(uint8_t flag, uint8_t color) {

	}

	// -------------------------- Packet --------------------------
	uint8_t Packet::packet_data(uint8_t device_id, uint8_t flag, uint8_t color) {
		return device_id | flag | color;
	}
};
