#include <iostream>
#include "AmbientPixel.h"

using namespace AmbientPixel;

void test()
{
	// TODO:
	// 1.Pixelの形に対応するように、VirtualPixelインスタンスを生成する。（VirtualPixelを作り、right）
	// 2.生成したインスタンスにMasterからNWパケットを送信する。
	// 3.ネットワーク全体の状態（Device IDが幾つになったか、LEDの状態はどうなっているか）を表示する。dumpメソッドをMasterのPixelで呼び出す。
	// 4.適当にPatternパケットを流してLEDの状態を変化させる。
	// 5.再度ネットワーク全体の状態を表示する。

	int device_id = 0;
	VirtualPixel *master = new VirtualPixel(device_id, 3);
	VirtualPixel *slave0 = new VirtualPixel(++device_id, 3);
	master->port_0 = slave0;
	VirtualPixel *slave1 = new VirtualPixel(++device_id, 3);
	master->port_1 = slave1;
	VirtualPixel *slave2 = new VirtualPixel(++device_id, 3);
	master->port_2 = slave2;

	master->dump_network();
}

int main(int argc, char const *argv[])
{
	std::cout << "Pixel Simulator" << std::endl;
	test();
	std::cout << "Finish" << std::endl;

	return 0;
}
