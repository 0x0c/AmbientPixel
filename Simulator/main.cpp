#include <iostream>
#include "AmbientPixel.h"

using namespace AmbientPixel;

void test()
{
	// TODO:
	// 1.Pixelの形に対応するように、VirtualPixelインスタンスを生成する。
	// 2.生成したインスタンスにMasterからNWパケットを送信する。
	// 3.ネットワーク全体の状態（Device IDが幾つになったか、LEDの状態はどうなっているか）を表示する。dump_networkメソッドをMasterのPixelで呼び出す。
	// 4.適当にPatternパケットを流してLEDの状態を変化させる。
	// 5.再度ネットワーク全体の状態を表示する。

	// 1の例
	VirtualPixel *master = new VirtualPixel(VirtualPixel::Vertex::Triangle);
	VirtualPixel *slave0 = new VirtualPixel(VirtualPixel::Vertex::Triangle);
	master->port_0 = slave0;
	VirtualPixel *slave1 = new VirtualPixel(VirtualPixel::Vertex::Triangle);
	master->port_1 = slave1;
	VirtualPixel *slave2 = new VirtualPixel(VirtualPixel::Vertex::Triangle);
	master->port_2 = slave2;

	// ここで2を行う
	
	// 3の例
	master->dump_network();

	// 4, 5の例
	master->change_led(VirtualPixel::Flag::Glow, VirtualPixel::Color::Red);
	master->dump_network();
}

int main(int argc, char const *argv[])
{
	std::cout << "Pixel Simulator" << std::endl;
	test();
	std::cout << "Finish" << std::endl;

	return 0;
}
