#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <skInfraredCOM.h>
#include <Adafruit_NeoPixel.h>
#include <AmbientPixel.h>

// Slaveの時はコメントアウトする
#define Master

using namespace AmbientPixel;

#ifdef Master
uint8_t device_id = 0b00000000; // 0b00000000 ~ 0b00000111まで上位3bitを使用
#else
uint8_t device_id = 0b00000001; // 0b00000000 ~ 0b00000111まで上位3bitを使用
#endif

Pixel pixel(AmbientPixel::Pixel::Vertex::Triangle);

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);
	Serial.println("<<AmbientPixel Start>>");
	pixel.device_id = device_id;
}

void loop()
{
	uint8_t data = pixel.watch(0);
	if(data != 0) {
		pixel.receive(0, data);
	}
}

#ifdef Master
void serialEvent()
{
	char data = Serial.read();
	pixel.send(0, data);
	Serial.flush();
}
#endif
