#include "AmbientPixel.h"

namespace AmbientPixel
{
	bool ap_bit_compare(uint8_t a, uint8_t b, int position, int length) {
		uint8_t a_s = (a << position) >> (8 - length);
		uint8_t b_s = (b << position) >> (8 - length);

		return a_s == b_s;
	}

	bool ap_bit_compare_flag(uint8_t a, uint8_t b) {
		return ap_bit_compare(a, b, 3, 2);
	}

	bool ap_bit_compare_control_flag(uint8_t a, uint8_t b) {
		return ap_bit_compare(a, b, 5, 3);
	}

	// -------------------------- ColorAttr --------------------------
	ColorAttr::ColorAttr(uint8_t red, uint8_t green, uint8_t blue) {
		this->red = red;
		this->green = green;
		this->blue = blue;
	}

	// -------------------------- Port --------------------------
	Port::Port(skInfraredCOM *com, uint8_t adjacent_device_id) {
		this->com = com;
		this->adjacent_device_id = adjacent_device_id;
	}

	// -------------------------- Pixel --------------------------
	Pixel::Pixel(uint8_t number_of_vertex) {
		// for (uint8_t i = 0; i < number_of_vertex; ++i) {
		// 	this->ports.push_back(new skInfraredCOM(0, 0));
		// }

		// プロトタイプ2号のピン配置
		this->ports.push_back(Port(new skInfraredCOM(2, 11), 0));
		this->ports.push_back(Port(new skInfraredCOM(3, 12), 0));
		this->ports.push_back(Port(new skInfraredCOM(3, 12), 0));

		this->configured = false;
		this->device_id = 0;
		this->number_of_vertex = number_of_vertex;
		this->led = Adafruit_NeoPixel(1, 10, NEO_GRB + NEO_KHZ800);
		this->led.setBrightness(200);
	}
	
	void Pixel::send(uint8_t port_no, uint8_t packet) {
		Port p = this->ports[port_no];
		p.com->Send(port_no, (unsigned char)packet);
	}

	void Pixel::receive(uint8_t port_no, uint8_t data) {
		// TODO: 受信時の処理の実装
		// Flagに応じて分岐する
		if (ap_bit_compare_flag(data, AmbientPixel::Pixel::Flag::Control)) {
			if (ap_bit_compare_control_flag(data, AmbientPixel::Pixel::ControlFlag::Network)) {
				// NWパケット
				if (this->configured == false) {
					this->configured = true;
					this->device_id = (uint8_t)(data >> 5);
					// Acceptする
					uint8_t p = Packet::packet_data(this->device_id << 5, Pixel::Flag::Control, Pixel::ControlFlag::Accept);
					this->send(port_no, p);

					if (this->device_id < 7) {
						// Device IDを+1してフォワードする
						uint8_t p0 = Packet::packet_data((this->device_id + 1) << 5, Pixel::Flag::Control, Pixel::ControlFlag::Network);
						uint8_t p1 = Packet::packet_data((this->device_id + 2) << 5, Pixel::Flag::Control, Pixel::ControlFlag::Network);
						this->send((port_no + 1) % 3, p0);
						this->send((port_no + 2) % 3, p1);
					}
				}
				else {
					// Denyする
					uint8_t p = Packet::packet_data(this->device_id << 5, Pixel::Flag::Control, Pixel::ControlFlag::Deny);
					this->send(port_no, p);
				}
			}
			else if (ap_bit_compare_control_flag(data, AmbientPixel::Pixel::ControlFlag::Reset)) {
				// RSTパケット
				this->configured = false;
				this->device_id = 0;
				
				// 隣接デバイスIDをクリアする
				this->ports[0].adjacent_device_id = 0;
				this->ports[1].adjacent_device_id = 0;
				this->ports[2].adjacent_device_id = 0;

				// フォワードする
				uint8_t p = Packet::packet_data(0, Pixel::Flag::Control, Pixel::ControlFlag::Reset);
				this->send((port_no + 1) % 3, p);
				this->send((port_no + 2) % 3, p);
			}
			else if (ap_bit_compare_control_flag(data, AmbientPixel::Pixel::ControlFlag::Accept)) {
				// ACCパケット
				// 隣接デバイスIDを登録
				this->ports[port_no].adjacent_device_id = (uint8_t)(data >> 5);
			}
			else if (ap_bit_compare_control_flag(data, AmbientPixel::Pixel::ControlFlag::Deny)) {
				// DNYパケット
			}
		}
		else  {
			if ((uint8_t)(data >> 5) == this->device_id) {
				// 自分宛てのパケット
				if (ap_bit_compare_flag(data, AmbientPixel::Pixel::Flag::TurnOff)) {
					// 消灯
					this->change_led(Pixel::Flag::TurnOff, this->color_at_index((data << 5) >> 5));
				}
				else {
					if (ap_bit_compare_flag(data, AmbientPixel::Pixel::Flag::Glow)) {
						// グロー
						this->change_led(Pixel::Flag::Glow, this->color_at_index((data << 5) >> 5));
					}
					else if (ap_bit_compare_flag(data, AmbientPixel::Pixel::Flag::Blink)) {
						// 点滅
						this->change_led(Pixel::Flag::Blink, this->color_at_index((data << 5) >> 5));
					}
				}
			}
			else {
				// 自分宛てでないパケット
				// 隣接するデバイスIDが大きいポートからフォワードする
				if (this->ports[(port_no + 1) % 3].adjacent_device_id < this->ports[(port_no + 2) % 3].adjacent_device_id) {
					this->send((port_no + 2) % 3, data);
				}
				else {
					this->send((port_no + 1) % 3, data);
				}
			}
		}
	}

	uint8_t Pixel::watch(uint8_t port_no) {
		Port p = this->ports[port_no];
		return p.com->Recive(this->device_id);
	}

	// TODO: LEDを点灯させる
	void Pixel::change_led(uint8_t flag, AmbientPixel::ColorAttr color) {
		this->led.setPixelColor(0, color.red, color.green, color.blue);
		this->led.show();
	}

	// Private
	AmbientPixel::ColorAttr Pixel::color_at_index(uint8_t index) {
		AmbientPixel::ColorAttr color(100, 0, 0); // Red
		if (ap_bit_compare_control_flag(index, AmbientPixel::Pixel::Color::Green)) {
			color = AmbientPixel::ColorAttr(0, 100, 0);
		}
		else if (ap_bit_compare_control_flag(index, AmbientPixel::Pixel::Color::Blue)) {
			color = AmbientPixel::ColorAttr(0, 0, 100);	
		}
		else if (ap_bit_compare_control_flag(index, AmbientPixel::Pixel::Color::Orange)) {
			color = AmbientPixel::ColorAttr(100, 50, 0);
		}
		else if (ap_bit_compare_control_flag(index, AmbientPixel::Pixel::Color::Yellow)) {
			color = AmbientPixel::ColorAttr(100, 100, 0);
		}
		else if (ap_bit_compare_control_flag(index, AmbientPixel::Pixel::Color::Purple)) {
			color = AmbientPixel::ColorAttr(100, 0, 100);
		}
		else if (ap_bit_compare_control_flag(index, AmbientPixel::Pixel::Color::Indigo)) {
			color = AmbientPixel::ColorAttr(0, 50, 100);
		}
		else if (ap_bit_compare_control_flag(index, AmbientPixel::Pixel::Color::White)) {
			color = AmbientPixel::ColorAttr(100, 100, 100);
		}

		return color;
	}

	// -------------------------- Packet --------------------------
	uint8_t Packet::packet_data(uint8_t device_id, uint8_t flag, uint8_t color) {
		return device_id | flag | color;
	}
};
