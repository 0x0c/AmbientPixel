#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <skInfraredCOM.h>
#include <Adafruit_NeoPixel.h>
#include <AmbientPixel.h>

using namespace AmbientPixel;

// Slaveの時は0にする
#define MASTER 1
Pixel pixel(AmbientPixel::Pixel::Vertex::Triangle);

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);
}

void loop()
{
#ifdef MASTER
	if(Serial.available()){
		// アプリからパケットを受信
	    char data = Serial.read();
	    pixel.receive(data);
	}
#endif
	for(int i = 0; i < pixel.number_of_vertex; i++){
		// 各ポートを監視する
		uint8_t data = pixel.watch(i);
		if(data != 0){
		    pixel.receive(data);
		}
	}
}

