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
	struct ColorAttr
	{
		uint8_t red;
		uint8_t green;
		uint8_t blue;
	};

#define AmbientPixelColorAttrRed	{100, 0, 0}
#define AmbientPixelColorAttrGreen	{0, 100, 0}
#define AmbientPixelColorAttrBlue	{0, 0, 100}
#define AmbientPixelColorAttrOrange	{100, 50, 0}
#define AmbientPixelColorAttrYellow	{100, 100, 0}
#define AmbientPixelColorAttrPerple	{100, 0, 100}
#define AmbientPixelColorAttrIndigo	{0, 50, 100}
#define AmbientPixelColorAttrWhite	{100, 100, 100}

	class Packet;
	class Pixel
	{
	private:
		// フルカラーLED制御用変数
		Adafruit_NeoPixel led;
		// 送信・受信ポート
		std::vector<skInfraredCOM *> ports;
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

		Pixel(uint8_t number_of_vertex);
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
