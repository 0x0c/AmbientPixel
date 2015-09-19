#include <iostream>
#include "AmbientPixel.h"

namespace AmbientPixel
{
	// -------------------------- Pixel --------------------------
	VirtualPixel::VirtualPixel(uint8_t device_id, uint8_t number_of_vertex) {
		this->device_id = device_id;
		this->number_of_vertex = number_of_vertex;
	}

	void VirtualPixel::set_pixel(VirtualPixel *pixel, int position) {
		switch (position) {
			case 0: {
				this->port_0 = pixel;
			}
				break;
			case 1: {
				this->port_1 = pixel;
			}
				break;
			case 1: {
				this->port_2 = pixel;
			}
				break;
		}
	}
	void VirtualPixel::send(uint8_t port_no, AmbientPixel::Packet *packet) {
		if (this->ports[port_no] != NULL) {
			this->ports[port_no]->receive((unsigned char)packet->data());
		}
		else {
			std::cout << "Send failed. (port : " + port_no + ")" << std::endl;
		}
	}

	void VirtualPixel::receive(uint8_t data) {
		std::cout << "received data :" + data << std::endl;
		// TODO: パケット受信時の処理を書く。
		// LEDを駆動させるときはchange_ledメソッドを用いる。
	}

	void VirtualPixel::change_led(uint8_t flag, uint8_t color) {
		this->flag = flag;
		this->color = color;
		std::cout << "received flag :" + this->flag + ", color :" + this->color << std::endl;
	}

	void dump(int indentation) {
		std::string indent = new std::string;
		for (int i = 0; i < indentation; ++i) {
			indent += '\t';
		}
		std::cout << indent + "device id :" + this->device_id + ", flag :" + this->flag + ", color :" + this->color << std::endl;
		if (this->port_0 != NULL) {
			this->port_0->dump(indentation + 1);
		}
		if (this->port_1 != NULL) {
			this->port_1->dump(++indentation + 1);
		}
		if (this->port_2 != NULL) {
			this->port_2->dump(++indentation + 1);
		}
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
