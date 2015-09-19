# AmbientPixel a.k.a SmartPixel
SmartPixelはすでに同じ名前のサービスがあったのでAmbientPixelに改名
ピクセルのメタファを持ち合わせる三角形のデバイス

**Specification Version : 0.0.1**

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

- サイズ
	- 一辺 : 65.8 mm
	- 高さ : 56.8 mm

### パケット

`Docs/markdown/Packet.md`を参照

### 伝搬アルゴリズム

`Docs/markdown/Packet.md`を参照

受け取ったら2つのポートへとりあえずフォワードする。
	
## スケジュール
- 筐体実装
	- 8/17〜8/30(予備：8/30〜9/11)
	- 回路設計完了（8/22）
- 組み込みプログラム実装
	- 8/17〜9/11(予備：9/4〜9/18)
- アプリ実装
	- 8/21〜9/11(予備：9/11〜9/25)
- APIつなぎ込み
	- 9/11〜10/2(予備：10/2〜10/13)
- 全体つなぎ込み
	- 10/2〜10/13

- P板.com基板到着 9/1
	- 増産はSwitch Science PCBでやりたい

## デモアプリケーション

`Docs/markdown/Examples.md`を参照
