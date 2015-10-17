#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <skInfraredCOM.h>
#include <Adafruit_NeoPixel.h>
#include <AmbientPixel.h>

using namespace AmbientPixel;

uint8_t device_id = 4; // 0b00000000 ~ 0b00000111まで上位3bitを使用

Pixel pixel(AmbientPixel::Pixel::Vertex::Triangle);

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);
	Serial.println("<<AmbientPixel Start>>");
	pixel.device_id = device_id;
	pinMode(13, OUTPUT);
	for(int i = 0; i < pixel.device_id; i++){
		digitalWrite(13, HIGH);
		delay(100);
		digitalWrite(13, LOW);
		delay(100);
	}
}

int cnt = 0;
void loop()
{
	if(pixel.device_id > 0){
		uint8_t data = pixel.watch(cnt);
		if(data != 0) {
			pixel.receive(cnt, data);
			digitalWrite(13, HIGH);
			delay(20);
			digitalWrite(13, LOW);

		}
		cnt = (cnt + 1) % 2;
	}
}

void serialEvent()
{
	char data = Serial.read();
	pixel.receive(0, data);
	Serial.flush();
}
