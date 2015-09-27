#include <iostream>
#include "AmbientPixel.h"

using namespace AmbientPixel;

void test()
{
	Pixel *master = new Pixel(Pixel::Vertex::Triangle);
	Pixel *slave0 = new Pixel(Pixel::Vertex::Triangle);
	master->port_0 = slave0;
	slave0->port_0 = master;
	Pixel *slave1 = new Pixel(Pixel::Vertex::Triangle);
	slave0->port_1 = slave1;
	Pixel *slave2 = new Pixel(Pixel::Vertex::Triangle);
	slave1->port_2 = slave2;
	Pixel *slave3 = new Pixel(Pixel::Vertex::Triangle);
	slave2->port_0 = slave3;
	Pixel *slave4 = new Pixel(Pixel::Vertex::Triangle);
	slave3->port_1 = slave4;

	std::cout << "--------NW Packet test--------" << std::endl;
	Packet p0 = Packet(0b00100000, Pixel::Flag::Control, Pixel::ControlFlag::Network);
	Packet p1 = Packet(0b01000000, Pixel::Flag::Control, Pixel::ControlFlag::Network);
	Packet p2 = Packet(0b01100000, Pixel::Flag::Control, Pixel::ControlFlag::Network);

	master->send(0, &p0);
	master->send(1, &p1);
	master->send(2, &p2);

	master->dump_network();
	master->dump_clear();

	// LEDの状態がきちんと変更されるかテスト
	std::cout << "--------Change LED test--------" << std::endl;
	master->change_led(Pixel::Flag::Glow, Pixel::Color::Red);
	master->dump_network();
	master->dump_clear();
	master->change_led(Pixel::Flag::Glow, Pixel::Color::Green);
	master->dump_network();
	master->dump_clear();
	master->change_led(Pixel::Flag::Blink, Pixel::Color::Blue);
	master->dump_network();
	master->dump_clear();
	master->change_led(Pixel::Flag::TurnOff, Pixel::Color::Red);
	master->dump_network();
	master->dump_clear();

	// パターンがきちんと伝搬されるかテスト
	std::cout << "--------Pattern Packet test--------" << std::endl;
	Packet p = Packet(0b01100000, Pixel::Flag::Glow, Pixel::Color::Red);
	master->send(0, &p);
	master->dump_network();
	master->dump_clear();
}

int main(int argc, char const *argv[])
{
	std::cout << "Pixel Simulator" << std::endl;
	test();
	std::cout << "Finish" << std::endl;

	return 0;
}
