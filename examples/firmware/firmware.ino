#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <skInfraredCOM.h>
#include <Adafruit_NeoPixel.h>
#include <AmbientPixel.h>

using namespace AmbientPixel;

uint8_t device_id = 2; // 0b00000000 ~ 0b00000111まで上位3bitを使用

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
		delay(200);
		digitalWrite(13, LOW);
		delay(200);
	}
}

int cnt = 0;
void loop()
{
	digitalWrite(13, HIGH);
	delay(20);
	digitalWrite(13, LOW);
	delay(20);
	if(pixel.device_id > 0){
		uint8_t data = pixel.watch(cnt);
		if(data != 0) {
			pixel.receive(cnt, data);
			digitalWrite(13, HIGH);
			delay(20);
			digitalWrite(13, LOW);
			delay(320);
		}
		// cnt = (cnt + 1) % 2;
	}
}

void serialEvent()
{
	char data = Serial.read();
	if((uint8_t)(data >> 5) > 0){
		pixel.send(0, data);
		delay(300);
		pixel.send(1, data);
		delay(300);
		pixel.send(2, data);
	}
	else {
		pixel.receive(0, data);
	}
}
