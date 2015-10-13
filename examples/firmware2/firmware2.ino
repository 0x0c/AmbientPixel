#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <skInfraredCOM.h>
#include <Adafruit_NeoPixel.h>
#include <AmbientPixel.h>

using namespace AmbientPixel;

uint8_t device_id = 0b00000010; // 0b00000000 ~ 0b00000111まで上位3bitを使用
Pixel pixel(AmbientPixel::Pixel::Vertex::Triangle);

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);
	Serial.println("<<AmbientPixel Start>>");
	pixel.device_id = device_id;
}

int cnt = 0;
void loop()
{
	uint8_t data = pixel.watch(cnt);
	if(data != 0) {
	    pixel.receive(cnt, data);
	}
	cnt = (cnt + 1) % 3;
}

/*
void serialEvent()
{
	char data = Serial.read();
  pixel.send(0, data);
  Serial.flush();
}
*/
