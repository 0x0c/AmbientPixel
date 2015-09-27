#include <iostream>
#include <string>
#include "AmbientPixel.h"

// #ifndef AmbientPixel_Define
// #define ap_bit_compare(a, b) (a & b) == b
// #endif

namespace AmbientPixel
{
	bool ap_bit_compare(int a, int b, int position, int length) {
		unsigned char a_s = a << position;
		unsigned char b_s = b << position;
		a_s = a_s >> (8 - length);
		b_s = b_s >> (8 - length);

		return a_s == b_s;
	}

	bool ap_bit_compare_flag(int a, int b) {
		return ap_bit_compare(a, b, 3, 2);
	}

	bool ap_bit_compare_control_flag(int a, int b) {
		return ap_bit_compare(a, b, 5, 3);
	}

	// -------------------------- Pixel --------------------------
	Pixel::Pixel(int number_of_vertex) {
		this->number_of_vertex = number_of_vertex;
		this->device_id = 0;
		this->flag = 0;
		this->color = 0;
		this->port_0 = nullptr;
		this->port_1 = nullptr;
		this->port_2 = nullptr;
	}

	void Pixel::send(int port_no, AmbientPixel::Packet *packet) {
		AmbientPixel::Pixel *p = this->pixel_for_index(port_no);
		if (p) {
			p->receive(port_no, (int)packet->packet_data());
		}
		else {
			std::cout << ">> " << this->device_id << " : Send failed. (port : " << port_no << ")" << std::endl;
		}
	}

	void Pixel::receive(int port_no, int data) {
		std::cout << ">> " << this->device_id << " : received data : " << static_cast<std::bitset<8> >(data) << std::endl;

		// パケット受信時の処理を書く。
		// Flagに応じて分岐する
		if (ap_bit_compare_flag(data, AmbientPixel::Pixel::Flag::Control)) {
			if (ap_bit_compare_control_flag(data, AmbientPixel::Pixel::ControlFlag::Network)) {
				// NWパケット
				if (this->configured == false) {
					this->configured = true;
					this->device_id = (int)(data >> 5);
					
					// Acceptする
					std::cout << ">> " << this->device_id << " : Accept(" << this->device_id << ")" << std::endl;
					Packet p = Packet(this->device_id << 5, Pixel::Flag::Control, Pixel::ControlFlag::Accept);
					this->send(port_no, &p);

					if (this->device_id < 7) {
						// Device IDを+1してフォワードする
						std::cout << ">> " << this->device_id << " : Forward" << std::endl;
						Packet p0 = Packet((this->device_id + 1) << 5, Pixel::Flag::Control, Pixel::ControlFlag::Network);
						Packet p1 = Packet((this->device_id + 2) << 5, Pixel::Flag::Control, Pixel::ControlFlag::Network);
						this->send((port_no + 1) % 3, &p0);
						this->send((port_no + 2) % 3, &p1);
					}
				}
				else {
					// Denyする
					std::cout << ">> " << this->device_id << " : Deny" << std::endl;
					Packet p = Packet(this->device_id << 5, Pixel::Flag::Control, Pixel::ControlFlag::Deny);
					this->send(port_no, &p);
				}
			}
			else if (ap_bit_compare_control_flag(data, AmbientPixel::Pixel::ControlFlag::Reset)) {
				// RSTパケット
				this->configured = false;
				this->device_id = 0;
				
				// 隣接デバイスIDをクリアする
				this->adjacent_device_id[0] = 0;
				this->adjacent_device_id[1] = 0;
				this->adjacent_device_id[2] = 0;

				// フォワードする
				std::cout << ">> " << this->device_id << " : Reset" << std::endl;
				Packet p = Packet(0, Pixel::Flag::Control, Pixel::ControlFlag::Reset);
				this->send((port_no + 1) % 3, &p);
				this->send((port_no + 2) % 3, &p);
			}
			else if (ap_bit_compare_control_flag(data, AmbientPixel::Pixel::ControlFlag::Accept)) {
				// ACCパケット
				// 隣接デバイスIDを登録
				this->adjacent_device_id[port_no] = (int)(data >> 5);
				std::cout << ">> " << this->device_id << " : ACC : port(" << port_no << ") : adj_device_id(" << this->adjacent_device_id[port_no] << ")" << std::endl;
			}
			else if (ap_bit_compare_control_flag(data, AmbientPixel::Pixel::ControlFlag::Deny)) {
				// DNYパケット
			}
		}
		else  {
			if ((uint8_t)(data >> 5) == this->device_id) {
				// 自分宛てのパケット
				std::cout << ">> " << this->device_id << " : Packet destination" << std::endl;
				if (ap_bit_compare_flag(data, AmbientPixel::Pixel::Flag::TurnOff)) {
					// 消灯
					this->change_led(Pixel::Flag::TurnOff, this->color);
				}
				else {
					if (ap_bit_compare_flag(data, AmbientPixel::Pixel::Flag::Glow)) {
						// グロー
						this->change_led(Pixel::Flag::Glow, Pixel::Color::Red);
					}
					else if (ap_bit_compare_flag(data, AmbientPixel::Pixel::Flag::Blink)) {
						// 点滅
						this->change_led(Pixel::Flag::Blink, Pixel::Color::Red);
					}
				}
			}
			else {
				// 自分宛てでないパケット
				// 隣接するデバイスIDが大きいポートからフォワードする
				Packet p = Packet(data);
				if (this->adjacent_device_id[(port_no + 1) % 3] < this->adjacent_device_id[(port_no + 2) % 3]) {
					std::cout << ">> " << this->device_id << " : Forward to " << this->adjacent_device_id[(port_no + 2) % 3] << std::endl;
					this->send((port_no + 2) % 3, &p);
				}
				else {
					std::cout << ">> " << this->device_id << " : Forward to " << this->adjacent_device_id[(port_no + 1) % 3] << std::endl;
					this->send((port_no + 1) % 3, &p);
				}
			}
		}
	}

	void Pixel::change_led(int flag, int color) {
		this->flag = flag;
		this->color = color;
		std::cout << ">> " << "change_led flag : " << Pixel::flag_str(this->flag) << ", color : " << Pixel::color_str(this->color) << std::endl;
	}

	Pixel* Pixel::pixel_for_index(int port_no) {
		AmbientPixel::Pixel *p = nullptr;
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

		return p;
	}

	int Pixel::port_of_pixel(Pixel *p) {
		int port_no = -1;
		if (p == this->port_0) {
			port_no = 0;
		}
		else if (p == this->port_1) {
			port_no = 1;
		}
		else if (p == this->port_2) {
			port_no = 2;
		}

		return port_no;
	}

	void Pixel::dump_pixel(std::string indentation) {
		this->dumped = true;
		std::cout << indentation << "device id : " << this->device_id << ", flag : " << Pixel::flag_str(this->flag) << ", color : " << Pixel::color_str(this->color) << std::endl;
	}

	void Pixel::dump_network(std::string indentation) {
		this->dump_pixel(indentation);
		if (this->port_0 && this->port_0->dumped == false) {
			this->port_0->dump_network(indentation + '\t');
		}
		if (this->port_1 && this->port_1->dumped == false) {
			this->port_1->dump_network(indentation + '\t');
		}
		if (this->port_2 && this->port_2->dumped == false) {
			this->port_2->dump_network(indentation + '\t');
		}
	}

	void Pixel::dump_clear() {
		this->dumped = false;
		if (this->port_0 && this->port_0->dumped == true) {
			this->port_0->dump_clear();
		}
		if (this->port_1 && this->port_1->dumped == true) {
			this->port_1->dump_clear();
		}
		if (this->port_2 && this->port_2->dumped == true) {
			this->port_2->dump_clear();
		}
	}

	std::string Pixel::flag_str(int flag) {
		std::string str = "Unknown";
		switch (flag) {
			case Pixel::Flag::TurnOff: {
				str = "TurnOff";
			}
				break;
			case Pixel::Flag::Glow: {
				str = "Glow";
			}
				break;
			case Pixel::Flag::Blink: {
				str = "Blink";
			}
				break;
			case Pixel::Flag::Control: {
				str = "Control";
			}
				break;
		}

		return str;
	}

	std::string Pixel::color_str(int flag) {
		std::string str = "Unknown";
		switch (flag) {
			case Pixel::Color::Red: {
				str = "Red";
			}
				break;
			case Pixel::Color::Blue: {
				str = "Blue";
			}
				break;
			case Pixel::Color::Green: {
				str = "Green";
			}
				break;
			case Pixel::Color::Orange: {
				str = "Orange";
			}
				break;
			case Pixel::Color::Yellow: {
				str = "Yellow";
			}
				break;
			case Pixel::Color::Purple: {
				str = "Purple";
			}
				break;
			case Pixel::Color::Indigo: {
				str = "Indigo";
			}
				break;
			case Pixel::Color::White: {
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

	Packet::Packet(int bit) {
		this->device_id = bit >> 5;
		this->flag = bit << 3 >> 6;
		this->color = bit << 5 >> 5;
	};

	// 1byteのパケットデータを取得する
	int Packet::packet_data() {
		return this->device_id | this-> flag | this->color;
	}

	void Packet::dump() {
		std::cout << "device id : " << this->device_id << ", flag : " << Pixel::flag_str(this->flag) << ", color : " << Pixel::color_str(this->color);
	}
};
