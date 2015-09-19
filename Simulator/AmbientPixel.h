#pragma once

#include <vector>

namespace AmbientPixel
{
	class Packet;
	class VirtualPixel
	{
	private:
		// 送信・受信ポート
		VirtualPixel *port_0;
		VirtualPixel *port_1;
		VirtualPixel *port_2;

		// 自分のデバイスID
		uint8_t device_id;
		// 頂点数
		uint8_t number_of_vertex;
	public:
		struct Flag {
			enum {
				Glow	= 0b00000000,
				Blink 	= 0b00001000,
				TurnOff = 0b00010000,
				//	0b00011000 はControlパケット
			};
		};
		struct Color {
			enum {
				Red 	= 0b00000000,
				Blue 	= 0b00000001,
				Green 	= 0b00000010,
				Orange 	= 0b00000011,
				Yellow 	= 0b00000100,
				Purple 	= 0b00000101,
				Indigo 	= 0b00000110,
				White 	= 0b00000111,
			};
		};

		struct Vertex {
			enum {
				Triangle = 3,
				// Rectangle = 4,
				// Pentagon = 5,
				// Hexagon = 6,
			};
		};

		Pixel(uint8_t device_id, uint8_t number_of_vertex);
		void set_pixel(VirtualPixel *pixel, int position);
		void send(uint8_t port_no, AmbientPixel::Packet *packet);
		uint8_t receive(uint8_t port_no);

		// LEDを点灯させる
		void change_led(uint8_t flag, uint8_t color);
		// パケットをフォワードする
		void forward(uint8_t port_no, AmbientPixel::Packet *p);
	};

	class Packet
	{
	public:
		// 送信先デバイスID
		uint8_t device_id;
		// LEDの動作フラグ
		uint8_t flag;
		// LEDの色
		uint8_t color;

		Packet(uint8_t device_id, uint8_t flag, uint8_t color);
		// 1byteのパケットデータを取得する
		uint8_t data();
	};
}
