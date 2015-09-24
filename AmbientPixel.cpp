#include "AmbientPixel.h"

#ifndef AmbientPixel_Define
#define ap_BitCompare(a, b) (a & b) == a
#endif

namespace AmbientPixel
{
	// -------------------------- ColorAttr --------------------------
	ColorAttr::ColorAttr(uint8_t red, uint8_t green, uint8_t blue) {
		this->red = red;
		this->green = green;
		this->blue = blue;
	}

	// -------------------------- Pixel --------------------------
	Pixel::Pixel(uint8_t number_of_vertex) {
		// for (uint8_t i = 0; i < number_of_vertex; ++i) {
		// 	this->ports.push_back(new skInfraredCOM(0, 0));
		// }

		// プロトタイプ2号のピン配置
		this->ports.push_back(new skInfraredCOM(2, 11));
		this->ports.push_back(new skInfraredCOM(3, 12));
		this->ports.push_back(new skInfraredCOM(4, 13));

		this->configured = false;
		this->device_id = 0;
		this->number_of_vertex = number_of_vertex;
		this->led = Adafruit_NeoPixel(1, 10, NEO_GRB + NEO_KHZ800);
		this->led.setBrightness(200);
	}
	
	void Pixel::send(uint8_t port_no, uint8_t packet) {
		this->ports[port_no]->Send(port_no, (unsigned char)packet);
	}

	void Pixel::receive(uint8_t data) {
		// TODO: 受信時の処理の実装
		// Flagに応じて分岐する
		if (ap_BitCompare(data, AmbientPixel::Pixel::Flag::Control)) {
			if (ap_BitCompare(data, AmbientPixel::Pixel::ControlFlag::Network)) {
				// NWパケット
				if (this->configured == false) {
					this->configured = true;
					this->device_id = (uint8_t)(data >> 5);
					// TODO: フォワードする
				}
			}
			else if (ap_BitCompare(data, AmbientPixel::Pixel::ControlFlag::Reset)) {
				// RSTパケット
				this->configured = false;
				this->device_id = 0;
				// TODO: フォワードする
			}
		}
		else  {
			if (ap_BitCompare(data, AmbientPixel::Pixel::Flag::TurnOff)) {
				// TODO: 消灯
			}
			else {
				if (ap_BitCompare(data, AmbientPixel::Pixel::Flag::Glow)) {
					// TODO: グロー
				}
				else if (ap_BitCompare(data, AmbientPixel::Pixel::Flag::Blink)) {
					// TODO: 点滅
				}
			}
		}
	}

	uint8_t Pixel::watch(uint8_t port_no) {
		return this->ports[port_no]->Recive(this->device_id);
	}

	// TODO: LEDを点灯させる
	void Pixel::change_led(uint8_t flag, AmbientPixel::ColorAttr color) {
		this->led.setPixelColor(0, color.red, color.green, color.blue);
		this->led.show();
	}

	// Private
	AmbientPixel::ColorAttr Pixel::color_at_index(uint8_t index) {
		AmbientPixel::ColorAttr color(100, 0, 0); // Red
		if (ap_BitCompare(index, AmbientPixel::Pixel::Color::Green)) {
			color = AmbientPixel::ColorAttr(0, 100, 0);
		}
		else if (ap_BitCompare(index, AmbientPixel::Pixel::Color::Blue)) {
			color = AmbientPixel::ColorAttr(0, 0, 100);	
		}
		else if (ap_BitCompare(index, AmbientPixel::Pixel::Color::Orange)) {
			color = AmbientPixel::ColorAttr(100, 50, 0);
		}
		else if (ap_BitCompare(index, AmbientPixel::Pixel::Color::Yellow)) {
			color = AmbientPixel::ColorAttr(100, 100, 0);
		}
		else if (ap_BitCompare(index, AmbientPixel::Pixel::Color::Purple)) {
			color = AmbientPixel::ColorAttr(100, 0, 100);
		}
		else if (ap_BitCompare(index, AmbientPixel::Pixel::Color::Indigo)) {
			color = AmbientPixel::ColorAttr(0, 50, 100);
		}
		else if (ap_BitCompare(index, AmbientPixel::Pixel::Color::White)) {
			color = AmbientPixel::ColorAttr(100, 100, 100);
		}

		return color;
	}

	// -------------------------- Packet --------------------------
	uint8_t Packet::packet_data(uint8_t device_id, uint8_t flag, uint8_t color) {
		return device_id | flag | color;
	}
};
