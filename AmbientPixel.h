#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <vector>
#include <skInfraredCOM.h>
#include <Adafruit_NeoPixel.h>

namespace AmbientPixel
{
	class Packet
	{
	public:
		struct Dest {
			enum {
				Broadcast = 255,
			};
		};
		// 送信元デバイスID
		unsigned char from;
		// 送信先デバイスID
		unsigned char dest;
		// パケットID
		unsigned char id;
		// データ
		unsigned char *data;
		// データ長
		int length;

		Packet(unsigned char id, unsigned char *data, int length, unsigned char dest) {
			this->id = id;
			this->data = data;
			this->length = length;
			this->dest = dest;
		};
		
		void append(unsigned char *data, unsigned char length) {
			// パケットのデータ部にデータを追加する
			this->length += length;
		}
	};

	class Pixel
	{
	private:
		// Masterの方向のポート
		// このポートをたどるとMasterへたどり着く
		char master_port;
		// フルカラーLED制御用変数
		Adafruit_NeoPixel led;
		// 送信・受信ポート
		std::vector<skInfraredCOM *> ports;
		// ポートに対応するデバイスID
		std::vector<unsigned char> port_device_id;
		// パケットの受信数
		unsigned char packet_sequence_count;
		// デバイスID
		unsigned char device_id;
		// 頂点数
		unsigned char number_of_vertex;
		// ロック用変数
		bool block;

		void port_close() {
			// 隣り合う受信モジュールで受信しないようにロックを掛ける
			this->block = true;
		}

		void port_open() {
			// 受信モジュールでデータを受信できるようにロックを解除
			this->block = false;
		}

		void operation(unsigned char op) {
			// 他ノードから送られてきたデータに応じて処理を実行する
			// op(命令)は事前に定義する
		}

		void send(unsigned char port_no, unsigned char data, unsigned char send_to) {
			this->ports[port_no]->Send(send_to, data);
		}

		unsigned char _receive() {
			if (this->block) {
				return 0;
			}
			// return this->ir_port->Recive(this->device_id);
			return 0;
		}

	public:
		struct Vertex {
			enum {
				Triangle = 3,
				// Rectangle = 4,
				// Pentagon = 5,
				// Hexagon = 6,
				NumberOfMaximumVertex = 3,
			};
		};

		Pixel(unsigned char device_id, unsigned char number_of_vertex) {
			if (number_of_vertex <= AmbientPixel::Pixel::Vertex::NumberOfMaximumVertex) {
				for (int i = 0; i < number_of_vertex; ++i) {
					this->ports.push_back(new skInfraredCOM(i * 2, i * 2 + 1));
				}
				this->packet_sequence_count = 0;
				this->device_id = device_id;
				if (this->device_id == 0) {
					this->master_port = -1;
				}
				this->number_of_vertex = number_of_vertex;
				this->led = = Adafruit_NeoPixel(1, 13, NEO_GRB + NEO_KHZ800);
			}
		}

		// データを送信する
		void send(unsigned char port_no, Packet packet) {
			if (port_no < this->number_of_vertex) {
				this->port_close();
				// 最初にパケットの情報をおくる必要がある？
				for (int i = 0; i < packet.length; ++i) {
					this->send(port_no, packet.data[i], packet.dest);
					// 10msだけ待機が必要
					delay(10);
				}
				this->port_open();
			}
		}

		// データを受信する
		// Packet receive() {
		// 	return NULL;
		// }

		// 実行状態へ移行
		void start() {
			// パターンデータからLEDを点灯させる
		}

		// 待機状態へ移行
		void wait() {	
			// パターンデータの受信待ち
		}

		// パターンデータを伝搬させる
		void forward(unsigned char port_no, Packet p) {
			// パケットをport_noの辺からデータを送信する
		}

		unsigned char packet_id() {
			return this->packet_sequence_count++;
		}
	};
}
