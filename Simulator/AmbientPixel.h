#pragma once

#include <vector>

namespace AmbientPixel
{
	class Packet;
	class VirtualPixel
	{
	protected:
		// 自分のデバイスID
		int device_id;
		// 頂点数
		int number_of_vertex;

		int flag;
		int color;
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

		// 送信・受信ポート
		VirtualPixel *port_0;
		VirtualPixel *port_1;
		VirtualPixel *port_2;

		VirtualPixel(int device_id, int number_of_vertex);
		void send(int port_no, AmbientPixel::Packet *packet);
		void receive(int port_no);
		void dump_pixel(std::string indentation);
		void dump_network(std::string indentation = "");

		// LEDを点灯させる
		void change_led(int flag, int color);
	};

	class Packet
	{
	public:
		// 送信先デバイスID
		int device_id;
		// LEDの動作フラグ
		int flag;
		// LEDの色
		int color;

		Packet(int device_id, int flag, int color);
		// 1byteのパケットデータを取得する
		int data();
	};
}
