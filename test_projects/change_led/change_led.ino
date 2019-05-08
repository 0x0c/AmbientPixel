/*******************************************************************************
*  InfrredRecive.pde - 赤外線受信関数の使い方サンプル２                        *
*   ２番に接続された赤外線受信モジュールからデータを受信します。               *
*   受信データはArduinoIDEに送信する。                                         *
*                                                                              *
* ============================================================================ *
*  VERSION DATE        BY                    CHANGE/COMMENT                    *
* ---------------------------------------------------------------------------- *
*  1.00    2011-07-09  きむ茶工房(きむしげ)  Create                            *
*******************************************************************************/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <skInfraredCOM.h>

skInfraredCOM Infrared(-1, 3);

/*******************************************************************************
*  電源起動時とリセットの時だけのみ処理される関数(初期化と設定処理)            *
*******************************************************************************/
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, 10, NEO_GRB + NEO_KHZ800);
void setup()
{
  #if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
     Serial.begin(9600);	// ArduinoIDEと通信する為の初期化処理
     pixels.begin(); // This initializes the NeoPixel library.
}
/*******************************************************************************
*  繰り返し実行される処理の関数(メインの処理)                                  *
*******************************************************************************/

void loop()
{
     unsigned char MyDeviceNo;   // 自局の識別デバイス番号
     unsigned char data;        // 受信した通知情報データ

     MyDeviceNo = 0x0a;
     data= Infrared.Receive(MyDeviceNo); // 受信する
     if (data!= 0) {
          Serial.println(data, DEC) ;     // データを受信したのでＩＤＥに送信する
          // 受信したKeyNoに応じて色を変える
          switch(data % 3) {
            case 0: 
              pixels.setPixelColor(0, pixels.Color(150,0,0)); // Moderately bright green color.
              break;
            case 1:
              pixels.setPixelColor(0, pixels.Color(0,150,0)); // Moderately bright green color.
              break;
            case 2:
              pixels.setPixelColor(0, pixels.Color(0,0,150)); // Moderately bright green color.
              break;
              
          }
          pixels.show(); // This sends the updated pixel color to the hardware.         
     }
}
