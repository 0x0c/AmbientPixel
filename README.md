# AmbientPixel a.k.a SmartPixel
SmartPixelはすでに同じ名前のサービスがあったのでAmbientPixelに改名

## Requirements

- Arduino
- 赤外線LED
- [赤外線リモコン受信モジュール](http://akizukidenshi.com/catalog/g/gI-00622/)
- [マイコン内蔵RGB LED](http://akizukidenshi.com/catalog/g/gM-08414/)

## Dependencies

- C++拡張
	- [StandardCplusplus](https://github.com/0x0c/StandardCplusplus)
- 赤外線通信ライブラリ
	- [skInfraredCOM](http://www.geocities.jp/zattouka/GarageHouse/micon/InfraredCOM/InfraredCOM.htm)
- フルカラーLED制御ライブラリ
	- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
	
## Getting Started

Arduinoで動作するプログラムを開発する前に幾つか追加しなければならないライブラリがある。

1. `StandartCplusplus`と`skInfraredCOM`、`Adafruit_NeoPixel`をArduinoのライブラリに追加する
2. `AmbientPixel`のリポジトリをcloneし、Arduinoのライブラリに追加する

## Hardwar
###　プロトタイプ1号
![](https://raw.githubusercontent.com/0x0c/AmbientPixel/master/Asset/Image/p1-1.jpg?token=AAJa196Pg--TfIaPiPlLZ4o6D-owqrLdks5V3VkGwA%3D%3D)
![](https://raw.githubusercontent.com/0x0c/AmbientPixel/master/Asset/Image/p1-2.jpg?token=AAJa1zghC-jrMf7iGu76KpIgHkY2N7V2ks5V3VkiwA%3D%3D)
縦にした時、Arduino Pro Miniが地面につく辺を基準とする。
LEDが付いている方を正面とする。

- ピン配置(PIO)
	- 赤外線LED→基準から右回りで2, 3, 4
	- 受信モジュール→基準から右回りで11, 12, 13
	- LEDのデータ線→10