#pragma once

#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <vector>
#include <skInfraredCOM.h>
#include <Adafruit_NeoPixel.h>

namespace AmbientPixel
{
	class ColorAttr
	{
	public:
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		ColorAttr();
		ColorAttr(uint8_t red, uint8_t green, uint8_t blue);
	};

	class Port
	{
	public:
		skInfraredCOM *com;
		uint8_t adjacent_device_id;

		Port(skInfraredCOM *com, uint8_t adjacent_device_id);
	};

	class Packet
	{
	public:
		// 1byteのパケットデータを生成する
		static uint8_t packet_data(uint8_t device_id, uint8_t flag, uint8_t color);
	};

	class Pixel
	{
	private:
		// フルカラーLED制御用変数
		Adafruit_NeoPixel led;
		// 送信・受信ポート
		std::vector<Port> ports;
		bool configured;
		bool blink;
		AmbientPixel::ColorAttr current_color;

		AmbientPixel::ColorAttr color_at_index(uint8_t index);
	public:
		struct Flag {
			enum {
				Glow	= 0b00000000,
				Blink 	= 0b00001000,
				TurnOff = 0b00010000,
				Control = 0b00011000
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
				Green 	= 0b00000001,
				Blue	= 0b00000010,
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
		
		// 自分のデバイスID
		uint8_t device_id;
		// 頂点数
		uint8_t number_of_vertex;

		Pixel(uint8_t number_of_vertex);
		// 指定したポートにパケットを送信する
		void send(uint8_t port_no, uint8_t packet);
		void receive(uint8_t port_no, uint8_t data);
		// ポートを監視する
		uint8_t watch(uint8_t port_no);
		// LEDを点灯させる
		void change_led(uint8_t flag, AmbientPixel::ColorAttr color);
	};
}
