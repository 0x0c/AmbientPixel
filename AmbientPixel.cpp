#include "AmbientPixel.h"

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
		// return ap_bit_compare(a, b, 3, 2);
		uint8_t a_s = a & 0b00011000;
		uint8_t b_s = b & 0b00011000;
		return a_s == b_s;
	}

	bool ap_bit_compare_control_flag(uint8_t a, uint8_t b) {
		// return ap_bit_compare(a, b, 5, 3);
		uint8_t a_s = a & 0b00000111;
		uint8_t b_s = b & 0b00000111;
		return a_s == b_s;
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
		return (device_id << 5) | flag | color;
	}

	// -------------------------- Pixel --------------------------
	Pixel::Pixel(uint8_t number_of_vertex) {
		// プロトタイプ2号のピン配置
		this->ports.push_back(Port(new skInfraredCOM(2, 11), 0));
		this->ports.push_back(Port(new skInfraredCOM(3, 12), 0));
		this->ports.push_back(Port(new skInfraredCOM(4, 11), 0));

		this->configured = false;
		this->device_id = 0;
		this->number_of_vertex = number_of_vertex;
		this->led = Adafruit_NeoPixel(1, 10, NEO_GRB + NEO_KHZ800);
		this->led.setBrightness(255);
		this->led.begin();
	}
	
	void Pixel::send(uint8_t port_no, uint8_t packet) {
		delay(50);
		AP_DEBUG_LOG(">> Send to port : ");
		AP_DEBUG_LOG(port_no);
		AP_DEBUG_LOG(" , data : ");
		AP_DEBUG_LOG_FMT(packet, BIN);
		Port p = this->ports[port_no];
		p.com->Send((uint8_t)(packet >> 5), packet);
		delay(50);
	}

	void Pixel::receive(uint8_t port_no, uint8_t data) {
		// 受信時の処理の実装
		// Flagに応じて分岐する
		AP_DEBUG_LOG_LN("---");
		AP_DEBUG_LOG(">> Receive from port : ");
		AP_DEBUG_LOG(port_no);
		AP_DEBUG_LOG(", data : ");
		AP_DEBUG_LOG_FMT(data, BIN);
		this->change_led(data & 0b00011000, this->color_at_index((data << 5) >> 5));
	}

	uint8_t Pixel::watch(uint8_t port_no) {
		Port p = this->ports[port_no];
		uint8_t data = p.com->Receive(this->device_id);
		return data;
	}

	// LEDを点灯させる
	void Pixel::change_led(uint8_t flag, AmbientPixel::ColorAttr color) {
		AP_DEBUG_LOG(">> Change LED : ");
		this->blink = false;
		if(flag == AmbientPixel::Pixel::Flag::TurnOff) {
			float dr = (color.red - this->current_color.red) / 255.0;
			float dg = (color.green - this->current_color.green) / 255.0;
			float db = (color.blue - this->current_color.blue) / 255.0;
			for(int i = 0; i < 255; i++) {
				float r = this->current_color.red + (dr * i);
				float g = this->current_color.green + (dg * i);
				float b = this->current_color.blue + (db * i);
				this->led.setPixelColor(0, r, g, b);
				this->led.show();
				delay(1);
			}
			this->current_color = color;
		}
		else {
			if (flag == AmbientPixel::Pixel::Flag::Glow) {
				// グロー
				AP_DEBUG_LOG_LN("Glow");
				float dr = (color.red - this->current_color.red) / 255.0;
				float dg = (color.green - this->current_color.green) / 255.0;
				float db = (color.blue - this->current_color.blue) / 255.0;
				for(int i = 0; i < 255; i++) {
					float r = this->current_color.red + (dr * i);
					float g = this->current_color.green + (dg * i);
					float b = this->current_color.blue + (db * i);
					this->led.setPixelColor(0, r, g, b);
					this->led.show();
					delay(1);
				}

				this->current_color = color;
			}
			else if (flag == AmbientPixel::Pixel::Flag::Blink) {
				// 点滅
				AP_DEBUG_LOG_LN("Blink");
				this->blink = true;
				this->led.setPixelColor(0, color.red, color.green, color.blue);
				this->led.show();
				delay(500);
				this->led.setBrightness(0);
				this->led.show();
				delay(500);
				this->led.setBrightness(100);
				this->led.show();
			}
		}
	}

	// Private
	AmbientPixel::ColorAttr Pixel::color_at_index(uint8_t index) {
		AmbientPixel::ColorAttr color(100, 0, 0); // Red
		if (ap_bit_compare_control_flag(index, AmbientPixel::Pixel::Color::Green)) {
			color = AmbientPixel::ColorAttr(0, 100, 0);//change_led()に使用
		}
		else if (ap_bit_compare_control_flag(index, AmbientPixel::Pixel::Color::Blue)) {
			color = AmbientPixel::ColorAttr(0, 0, 100);	
		}
		else if (ap_bit_compare_control_flag(index, AmbientPixel::Pixel::Color::Orange)) {
			color = AmbientPixel::ColorAttr(100, 50, 0);
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
		else if (ap_bit_compare_control_flag(index, AmbientPixel::Pixel::Color::Off)) {
			color = AmbientPixel::ColorAttr(0, 0, 0);
		}


		return color;
	}
};
