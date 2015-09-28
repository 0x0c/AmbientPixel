#include "AmbientPixel.h"

#define DEBUG 1
#ifdef DEBUG
#define AP_DEBUG_LOG(x) Serial.println(x)
#define AP_DEBUG_LOG_FMT(x, y) Serial.println(x, y)
#else
#define AP_DEBUG_LOG(x)
#define AP_DEBUG_LOG_FMT(x, y)
#endif

namespace AmbientPixel
{
	bool ap_bit_compare(uint8_t a, uint8_t b, int position, int length) {
		uint8_t a_s = a << position;
		uint8_t b_s = b << position;
		a_s = a_s >> (8 - length);
		b_s = b_s >> (8 - length);

		return a_s == b_s;
	}

	bool ap_bit_compare_flag(uint8_t a, uint8_t b) {
		return ap_bit_compare(a, b, 3, 2);
	}

	bool ap_bit_compare_control_flag(uint8_t a, uint8_t b) {
		return ap_bit_compare(a, b, 5, 3);
	}

	// -------------------------- ColorAttr --------------------------
	ColorAttr::ColorAttr() {

	}

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

	// -------------------------- Packet --------------------------
	uint8_t Packet::packet_data(uint8_t device_id, uint8_t flag, uint8_t color) {
		return device_id | flag | color;
	}

	// -------------------------- Pixel --------------------------
	Pixel::Pixel(uint8_t number_of_vertex) {
		// プロトタイプ2号のピン配置
		this->ports.push_back(Port(new skInfraredCOM(2, 11), 0));
		this->ports.push_back(Port(new skInfraredCOM(3, 12), 0));
		this->ports.push_back(Port(new skInfraredCOM(3, 12), 0));

		this->configured = false;
		this->device_id = 0;
		this->number_of_vertex = number_of_vertex;
		this->led = Adafruit_NeoPixel(1, 10, NEO_GRB + NEO_KHZ800);
		this->led.begin();
	}
	
	void Pixel::send(uint8_t port_no, uint8_t packet) {
		AP_DEBUG_LOG("---");
		AP_DEBUG_LOG("Send to port");
		AP_DEBUG_LOG(port_no);
		AP_DEBUG_LOG_FMT(packet, BIN);
		Port p = this->ports[port_no];
		p.com->Send(0, (unsigned char)packet);
		delay(10);
	}

	void Pixel::receive(uint8_t port_no, uint8_t data) {
		// 受信時の処理の実装
		// Flagに応じて分岐する
		AP_DEBUG_LOG("---");
		AP_DEBUG_LOG("Receive from port");
		AP_DEBUG_LOG(port_no);
		if (ap_bit_compare_flag(data, AmbientPixel::Pixel::Flag::Control)) {
			if (ap_bit_compare_control_flag(data, AmbientPixel::Pixel::ControlFlag::Network)) {
				// NWパケット
				AP_DEBUG_LOG("NW packet");
				if (this->configured == false) {
					// Acceptする
					this->configured = true;
					this->device_id = (uint8_t)(data >> 5);
					AP_DEBUG_LOG("Accept");
					AP_DEBUG_LOG(this->device_id);

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
					AP_DEBUG_LOG("Deny");
					uint8_t p = Packet::packet_data(this->device_id << 5, Pixel::Flag::Control, Pixel::ControlFlag::Deny);
					this->send(port_no, p);
				}
			}
			else if (ap_bit_compare_control_flag(data, AmbientPixel::Pixel::ControlFlag::Reset)) {
				// RSTパケット
				AP_DEBUG_LOG("RST packet");
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
				AP_DEBUG_LOG("Send ACC");
				this->ports[port_no].adjacent_device_id = (uint8_t)(data >> 5);
			}
			else if (ap_bit_compare_control_flag(data, AmbientPixel::Pixel::ControlFlag::Deny)) {
				// DNYパケット
			}
		}
		else  {
			if ((uint8_t)(data >> 5) == this->device_id) {
				// 自分宛てのパケット
				this->change_led(Pixel::Flag::Blink, this->color_at_index((data << 5) >> 5));
			}
			else {
				// 自分宛てでないパケット
				// 隣接するデバイスIDが大きいポートからフォワードする
				AP_DEBUG_LOG("Forward");
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
		return p.com->Recive(0);
	}

	// LEDを点灯させる
	void Pixel::change_led(uint8_t flag, AmbientPixel::ColorAttr color) {
		AP_DEBUG_LOG("Change LED");
		this->blink = false;
		this->led.setBrightness(100);
		if (ap_bit_compare_flag(flag, AmbientPixel::Pixel::Flag::TurnOff)) {
			// 消灯
			AP_DEBUG_LOG("Turn off");
			this->led.setBrightness(0);
		}
		else {
			if (ap_bit_compare_flag(flag, AmbientPixel::Pixel::Flag::Glow)) {
				// グロー
				AP_DEBUG_LOG("Glow");
				float duration = 1.0;
				float pt = duration / 255.0 * 1000;
				float dr = (color.red - this->current_color.red) / 255.0;
				float dg = (color.green - this->current_color.green) / 255.0;
				float db = (color.blue - this->current_color.blue) / 255.0;

				for(uint8_t j = 0; j < 255; j++) {
					float r = this->current_color.red + (dr * j);
					float g = this->current_color.green + (dg * j);
					float b = this->current_color.blue + (db * j);

					this->led.setPixelColor(0, r, g, b);
					this->led.show();
					delay(pt);
				}
			}
			else if (ap_bit_compare_flag(flag, AmbientPixel::Pixel::Flag::Blink)) {
				// 点滅
				AP_DEBUG_LOG("Blink");
				this->blink = true;
				this->led.setPixelColor(0, color.red, color.green, color.blue);
			}
		}
		this->led.show();
		this->current_color = color;
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
};
