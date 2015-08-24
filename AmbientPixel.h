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
		struct Type {
			enum {
				Echo	= 0,
				Pattern = 1,
				Data	= 3,
				Run		= 6,
				Reset	= 7
			};
		};

		// 送信元デバイスID
		uint8_t from;
		// 送信先デバイスID
		uint8_t dest;
		// パケットID
		uint8_t id;
		// パケットタイプ
		AmbientPixel::Packet::Type type;
		// データ
		uint8_t *data;
		// データ長
		uint8_t length;

		Packet(uint8_t id, AmbientPixel::Packet::Type type, uint8_t *data, int length, uint8_t dest) {
			this->id = id;
			this->type = type;
			this->data = data;
			this->length = length;
			this->dest = dest;
		};

		uint8_t head()
		{
			return (uint8_t)(this->type << 5 | this->length)
		}
	};

	class Pattern
	{
	public:
		Pattern();
		~Pattern();
	};

	class Pixel
	{
	private:
		enum State {
			Run,
			Wait
		};
		// 状態
		AmbientPixel::Pixel::State state;
		// パターンストア
		std::vector<Pattern> pattern_store;
		// Masterの方向のポート
		// このポートをたどるとMasterへたどり着く
		char master_port;
		// フルカラーLED制御用変数
		Adafruit_NeoPixel led;
		// 送信・受信ポート
		std::vector<skInfraredCOM *> ports;
		// ポートに対応するデバイスID
		std::vector<uint8_t> port_device_id;
		// パケットの受信数
		uint8_t packet_sequence_count;
		// デバイスID
		uint8_t device_id;
		// 頂点数
		uint8_t number_of_vertex;
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

		void operation(AmbientPixel::Packet::Type op) {
			// 他ノードから送られてきたデータに応じて処理を実行する
			// op(命令)は事前に定義する
		}

		void _send(uint8_t port_no, uint8_t data, uint8_t send_to) {
			this->ports[port_no]->Send(send_to, data);
		}

		uint8_t _receive() {
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
			};
		};

		Pixel(uint8_t device_id, uint8_t number_of_vertex) {
			this->state = AmbientPixel::Pixel::State::Wait;
			for (uint8_t i = 0; i < number_of_vertex; ++i) {
				this->ports.push_back(new skInfraredCOM(i * 2, i * 2 + 1));
			}
			this->packet_sequence_count = 0;
			this->device_id = device_id;
			if (this->device_id == 0) {
				this->master_port = -1;
			}
			this->number_of_vertex = number_of_vertex;
			this->led = Adafruit_NeoPixel(1, 13, NEO_GRB + NEO_KHZ800);
		}

		// データを送信する
		void send(uint8_t port_no, Packet packet) {
			if (port_no < this->number_of_vertex) {
				this->port_close();
				// Baseパケットの送信
				this->_send(port_no, packet.head(), packet.dest);
				delay(10);
				// Dataパケットの送信
				for (uint8_t i = 0; i < packet.length * 2; ++i) {
					// データの前後を分割して送信
					uint8_t d = (AmbientPixel::Packet::Type::Data << 5) | (packet.data[i / 2] >> (4 * (i % 2);
					this->_send(port_no, d, packet.dest);
					// 10msだけ待機が必要
					delay(10);
				}
				this->port_open();
			}
		}

		// 実行状態へ移行
		void start() {
			// パターンデータからLEDを点灯させる
		}

		// 待機状態へ移行
		void wait() {	
			// パターンデータの受信待ち
		}

		// パターンデータを伝搬させる
		void forward(uint8_t port_no, Packet p) {
			// パケットをport_noの辺からデータを送信する
		}

		uint8_t packet_id() {
			return this->packet_sequence_count++;
		}
	};
}
