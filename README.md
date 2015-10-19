# AmbientPixel a.k.a SmartPixel
SmartPixelはすでに同じ名前のサービスがあったのでAmbientPixelに改名
ピクセルのメタファを持ち合わせる三角形のデバイス

**Specification Version : 0.0.2**

## Requirements

- Arduino
- 赤外線LED
- [赤外線リモコン受信モジュール](http://akizukidenshi.com/catalog/g/gI-00622/)
- [マイコン内蔵RGB LED](http://akizukidenshi.com/catalog/g/gM-08414/)

## Dependencies

- C++拡張
	- [StandardCplusplus](https://github.com/0x0c/StandardCplusplus)
- 赤外線通信ライブラリ（修正版）
	- [skInfraredCOM](https://github.com/0x0c/skInfraredCOM)
- フルカラーLED制御ライブラリ
	- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
	
## Getting Started

Arduinoで動作するプログラムを開発する前に幾つか追加しなければならないライブラリがある。

1. `StandartCplusplus`と`skInfraredCOM`、`Adafruit_NeoPixel`をArduinoのライブラリに追加する
2. `AmbientPixel`のリポジトリをcloneし、Arduinoのライブラリに追加する

## Hardware
###　プロトタイプ1号
縦にした時、Arduino Pro Miniが地面につく辺を基準とする。
LEDが付いている方を正面とする。

- 構成
	- Arduino Pro Mini 3.3V 8MHz
	- マイコン内蔵ＲＧＢＬＥＤモジュール（AE-WS2812B）
	- 赤外線LED 3個
	- 赤外線リモコン受信モジュール 3個
	- 電池ソケット（JST PH 2P）
	- 足用のピンヘッダ 3本
- ピン配置(PIO)
	- 赤外線LED→基準から右回りで2, 3, 4
	- 受信モジュール→基準から右回りで11, 12, 13
	- LEDのデータ線→10
- サイズ
	- 一辺 : 65.8 mm
	- 高さ : 56.8 mm
	
###　プロトタイプ2号
P板で発注した基板を用いた試作。
JSTコネクタが上、コネクタのプリントがされている方を正面とする。
フルカラーLEDのピン配置をミスったので、DIとDOを適当な導線でつなぐ必要がある。
Arduino Pro Mini 3.3V 8MHzとArduino Pro Mini 5.0V 16MHzが混在。もしかしたら、3.3V 8MHzを調達しなおし、ハンダ付けし直す必要が有るかもしれない。
動作周波数をすべて同じにしたい。

電源スイッチを取り付け忘れたので、後でハンダ付けする必要がある。

- サイズ
	- 一辺 : 65.8 mm
	- 高さ : 56.8 mm

### パケット

`Docs/markdown/Packet.md`を参照

### 伝搬アルゴリズム

ブロードキャストし、デバイスIDが一致するデバイスが受理する

## デモアプリケーション

`Docs/markdown/Examples.md`を参照
