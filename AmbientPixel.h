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

	class Packet
	{
	public:
		struct Dest {
			enum {
				Broadcast	= 255,
			};
		};

		// struct Type {
		enum Type : uint8_t {
			Echo		= 0,
			Pattern 	= 1,
			// 2 は未定義
			Data		= 3,
			Int			= 4,
			Int_Cast	= 5,
			Run 		= 6,
			Reset		= 7
		};
		// };

		// 送信元デバイスID
		uint8_t from;
		// 送信先デバイスID
		uint8_t dest;
		// パケットID
		uint8_t id;
		// パケットタイプ
		Packet::Type type;
		// データ
		uint8_t *data;
		// データ長
		uint8_t length;

		Packet(AmbientPixel::Packet::Type type, uint8_t *data, int length, uint8_t dest) {
			this->type = type;
			this->data = data;
			this->length = length;
			this->dest = dest;
		};

		Packet(AmbientPixel::Packet::Type type, uint8_t length) {
			this->type = type;
			this->data = (uint8_t *)malloc(sizeof(uint8_t) * length);
			this->length = length;
		}

		// ヘッダデータ(Baseパケット)の生成
		uint8_t packet_header() {
			// TODO:
			return (uint8_t)(this->type << 5 | this->length);
		}

		static uint8_t parse_type(uint8_t data) {
			return data >> 5;
		}
	};

	struct Pattern
	{
		ColorAttr start_color;
		ColorAttr end_color;
		uint8_t duration;
		uint8_t repeat_count;
	};

	class Pixel
	{
	private:
		enum State {
			Running		= 0,
			Waiting		= 1,
			Receiving	= 2,
			Interactive	= 3
		};

		// 状態
		State state;
		// 受信したデータ
		// ここにReceiving時に受け取ったデータを格納していく
		// ポートごとに保持
		std::vector<Packet *>received_packet;

		// パターンストア
		std::vector<Pattern> pattern_store;
		// Masterの方向のポート
		// このポートをたどるとMasterへたどり着く
		uint8_t master_port;
		// フルカラーLED制御用変数
		Adafruit_NeoPixel led;

		// 送信・受信ポート
		std::vector<skInfraredCOM *> ports;

		// ポートに対応するデバイスID
		// 実際に必要か謎
		std::vector<uint8_t> port_device_id;

		// 自分のデバイスID
		uint8_t device_id;
		// 頂点数
		uint8_t number_of_vertex;

		void _send(uint8_t port_no, uint8_t data, uint8_t send_to) {
			this->ports[port_no]->Send(send_to, data);
		}

		uint8_t _receive() {
			// TODO:
			// 受信したデータを_operationに応じてステートマシンを動かす
			// return this->ir_port->Recive(this->device_id);
			return 0;
		}

		void _operation(Packet::Type op) {
			// 他ノードから送られてきたデータに応じて処理を実行する
			// op(命令)は事前に定義する
			// ステートマシンの処理はここに実装する
		}

	public:
		struct Vertex {
			enum {
				Triangle = 3,
				// Rectangle = 4,
				// Pentagon = 5,
				// Hexagon = 6,
			};
		};

		Pixel(uint8_t device_id, uint8_t number_of_vertex) {
			this->state = Waiting;
			for (uint8_t i = 0; i < number_of_vertex; ++i) {
				this->ports.push_back(new skInfraredCOM(i * 2, i * 2 + 1));
			}
			this->device_id = device_id;
			if (this->device_id == 0) {
				this->master_port = -1;
			}
			this->number_of_vertex = number_of_vertex;
			this->led = Adafruit_NeoPixel(1, 13, NEO_GRB + NEO_KHZ800);
			this->led.setBrightness(200);

		}

		// LEDを点灯させる
		void transform_color(AmbientPixel::ColorAttr start_color, AmbientPixel::ColorAttr end_color, uint8_t duration, uint8_t repeat_count) {
			float pt = duration / 255.0 * 1000;
			float dr = (end_color.red - start_color.red) / 255.0;
			float dg = (end_color.green - start_color.green) / 255.0;
			float db = (end_color.blue - start_color.blue) / 255.0;

			for(uint8_t j = 0; j < repeat_count; j++){
				for(uint8_t i = 0; i < 255; i++){
					float r = start_color.red + (dr * i);
					float g = start_color.green + (dg * i);
					float b = start_color.blue + (db * i);

					this->led.setPixelColor(0, r, g, b);
					this->led.show();
					delay(pt);
				}
			}
		}

		void exec_pattern(AmbientPixel::Pattern pattern) {
			this->transform_color(pattern.start_color, pattern.end_color, pattern.duration, pattern.repeat_count);
		}

		// データを送信する
		void send_packet(uint8_t port_no, Packet packet) {
			if (port_no < this->number_of_vertex) {
				packet.from = this->device_id;
				// Baseパケットの送信
				this->_send(port_no, packet.packet_header(), packet.dest);
				delay(10);
				// Dataパケットの送信
				for (uint8_t i = 0; i < packet.length * 2; ++i) {
					// データの前後を分割して送信
					uint8_t d = (Packet::Data << 5) | (packet.data[i / 2] >> (4 * (i % 2)));
					this->_send(port_no, d, packet.dest);
					// 10msだけ待機が必要
					delay(10);
				}
			}
		}

		// TODO:
		void perform() {
			// 状態に応じて処理を実行する。
			// loop関数内で呼び出す
			if (this->state == Pixel::Running) {
				for (int i = 0; i < this->pattern_store.size(); ++i) {
					Pattern p = this->pattern_store.at(i);
					this->exec_pattern(p);
				}
			}
			else if (this->state == Pixel::Waiting) {
				this->_operation((Packet::Type)Packet::parse_type(this->_receive()));
			}
			else if (this->state == Pixel::Receiving) {

			}
			else if (this->state == Pixel::Interactive) {

			}
		}

		// TODO:
		// 実行状態へ移行
		void run() {
			// パターンデータからLEDを点灯させる
		}

		// TODO:
		// 待機状態へ移行
		void wait() {
			// パターンデータの受信待ち
		}

		// TODO:
		// 状態をリセット
		void teadown() {
			// ステータはWaiting
			// 受信中のパケットは破棄
		}

		// TODO:
		// パケットをフォワードする
		void forward(uint8_t port_no, Packet p) {
			// パケットをport_noの辺からデータを送信する
		}
	};
}
