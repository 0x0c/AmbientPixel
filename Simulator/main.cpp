#include <iostream>
#include "AmbientPixel.h"

using namespace AmbientPixel;

void test()
{
	// TODO:
	// 1.Pixelの形に対応するように、Pixelインスタンスを生成する。
	// 2.生成したインスタンスにMasterからNWパケットを送信する。
	// 3.ネットワーク全体の状態（Device IDが幾つになったか、LEDの状態はどうなっているか）を表示する。dump_networkメソッドをMasterのPixelで呼び出す。
	// 4.適当にPatternパケットを流してLEDの状態を変化させる。
	// 5.再度ネットワーク全体の状態を表示する。

	Pixel *master = new Pixel(Pixel::Vertex::Triangle);
	Pixel *slave0 = new Pixel(Pixel::Vertex::Triangle);
	master->port_0 = slave0;
	Pixel *slave1 = new Pixel(Pixel::Vertex::Triangle);
	master->port_1 = slave1;
	Pixel *slave2 = new Pixel(Pixel::Vertex::Triangle);
	master->port_2 = slave2;

	// ここで2を行う
	Packet p0 = Packet(0b00100000, Pixel::Flag::Control, Pixel::ControlFlag::Network);
	Packet p1 = Packet(0b01000000, Pixel::Flag::Control, Pixel::ControlFlag::Network);
	Packet p2 = Packet(0b01100000, Pixel::Flag::Control, Pixel::ControlFlag::Network);

	master->send(0, &p0);
	master->send(1, &p1);
	master->send(2, &p2);
	
	// 3の例
	master->dump_network();

	// 4, 5の例
	// master->change_led(Pixel::Flag::Glow, Pixel::Color::Red);
	// master->dump_network();
}

int main(int argc, char const *argv[])
{
	std::cout << "Pixel Simulator" << std::endl;
	test();
	std::cout << "Finish" << std::endl;

	return 0;
}
