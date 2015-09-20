#include <iostream>
#include <string>
#include "AmbientPixel.h"

namespace AmbientPixel
{
	// -------------------------- Pixel --------------------------
	VirtualPixel::VirtualPixel(int number_of_vertex) {
		this->number_of_vertex = number_of_vertex;
		this->device_id = 0;
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
		std::cout << "change_led flag :" << this->flag_str(this->flag) << ", color :" << this->color_str(this->color) << std::endl;
	}

	void VirtualPixel::dump_pixel(std::string indentation) {
		std::cout << indentation << "device id :" << this->device_id << ", flag :" << this->flag_str(this->flag) << ", color :" << this->color_str(this->color) << std::endl;
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

	std::string VirtualPixel::flag_str(int flag) {
		std::string str = "Unknown";
		switch (flag) {
			case VirtualPixel::Flag::TurnOff: {
				str = "TurnOff";
			}
				break;
			case VirtualPixel::Flag::Glow: {
				str = "Glow";
			}
				break;
			case VirtualPixel::Flag::Blink: {
				str = "Blink";
			}
				break;
			case VirtualPixel::Flag::Control: {
				str = "Control";
			}
				break;
		}

		return str;
	}

	std::string VirtualPixel::color_str(int flag) {
		std::string str = "Unknown";
		switch (flag) {
			case VirtualPixel::Color::Red: {
				str = "Red";
			}
				break;
			case VirtualPixel::Color::Blue: {
				str = "Blue";
			}
				break;
			case VirtualPixel::Color::Green: {
				str = "Green";
			}
				break;
			case VirtualPixel::Color::Orange: {
				str = "Orange";
			}
				break;
			case VirtualPixel::Color::Yellow: {
				str = "Yellow";
			}
				break;
			case VirtualPixel::Color::Purple: {
				str = "Purple";
			}
				break;
			case VirtualPixel::Color::Indigo: {
				str = "Indigo";
			}
				break;
			case VirtualPixel::Color::White: {
				str = "White";
			}
				break;
		}

		return str;
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
