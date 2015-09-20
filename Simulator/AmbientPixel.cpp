#include <iostream>
#include <string>
#include "AmbientPixel.h"

namespace AmbientPixel
{
	// -------------------------- Pixel --------------------------
	VirtualPixel::VirtualPixel(int device_id, int number_of_vertex) {
		this->device_id = device_id;
		this->number_of_vertex = number_of_vertex;
		this->flag = 0;
		this->color = 0;
		this->port_0 = nullptr;
		this->port_1 = nullptr;
		this->port_2 = nullptr;
	}

	void VirtualPixel::send(int port_no, AmbientPixel::Packet *packet) {
		AmbientPixel::VirtualPixel *p = nullptr;
		switch (port_no) {
			case 0: {
				p = this->port_0;
			}
				break;
			case 1: {
				p = this->port_1;
			}
				break;
			case 2: {
				p = this->port_2;
			}
				break;
		}

		if (p) {
			p->receive((int)packet->data());
		}
		else {
			std::cout << "Send failed. (port : " << port_no << ")" << std::endl;
		}
	}

	void VirtualPixel::receive(int data) {
		std::cout << "received data :" << data << std::endl;
		// TODO: パケット受信時の処理を書く。
		// LEDを駆動させるときはchange_ledメソッドを用いる。
	}

	void VirtualPixel::change_led(int flag, int color) {
		this->flag = flag;
		this->color = color;
		std::cout << "received flag :" << this->flag << ", color :" << this->color << std::endl;
	}

	void VirtualPixel::dump_pixel(std::string indentation) {
		std::cout << indentation << "device id :" << this->device_id << ", flag :" << this->flag << ", color :" << this->color << std::endl;
	}

	void VirtualPixel::dump_network(std::string indentation) {
		this->dump_pixel(indentation);
		if (this->port_0) {
			this->port_0->dump_network(indentation + '\t');
		}
		if (this->port_1) {
			this->port_1->dump_network(indentation + '\t');
		}
		if (this->port_2) {
			this->port_2->dump_network(indentation + '\t');
		}
	}

	// -------------------------- Packet --------------------------
	Packet::Packet(int device_id, int flag, int color) {
		this->device_id = device_id;
		this->flag = flag;
		this->color = color;
	};

	// 1byteのパケットデータを取得する
	int Packet::data() {
		return this->device_id | this-> flag | this->color;
	}
};
