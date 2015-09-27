#pragma once

#include <vector>

namespace AmbientPixel
{
	class Packet;
	class Pixel
	{
	protected:
		// 自分のデバイスID
		int device_id;
		// 頂点数
		int number_of_vertex;
		bool configured;

		int flag;
		int color;
		bool dumped;
	public:
		struct Flag {
			enum {
				TurnOff	= 0b00000000,
				Glow 	= 0b00001000,
				Blink 	= 0b00010000,
				Control = 0b00011000,
			};
		};
		
		struct ControlFlag {
			enum {
				Network	= 0b00000000,
				Reset	= 0b00000001,
				Accept	= 0b00000010,
				Deny	= 0b00000011
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
		Pixel *port_0;
		Pixel *port_1;
		Pixel *port_2;

		int adjacent_device_id[3];

		Pixel(int number_of_vertex);
		// 指定のポートにパケットを送信する
		void send(int port_no, AmbientPixel::Packet *packet);
		// データを受信する
		void receive(int port_no, int data);
		// LEDを点灯させる
		void change_led(int flag, int color);

		// Debug
		Pixel* pixel_for_index(int port_no);
		void dump_pixel(std::string indentation);
		void dump_network(std::string indentation = "");
		void dump_clear();
		static std::string flag_str(int flag);
		static std::string color_str(int flag);
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
		Packet(int bit);
		// 1byteのパケットデータを取得する
		int packet_data();
		
		// Debug
		void dump();
	};
}
