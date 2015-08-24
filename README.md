# AmbientPixel a.k.a SmartPixel
SmartPixelはすでに同じ名前のサービスがあったのでAmbientPixelに改名
ピクセルのメタファを持ち合わせる三角形のデバイス

**Version 0.0.1**

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
![](https://raw.githubusercontent.com/0x0c/AmbientPixel/master/Asset/Image/p1-1.jpg?token=AAJa196Pg--TfIaPiPlLZ4o6D-owqrLdks5V3VkGwA%3D%3D)
![](https://raw.githubusercontent.com/0x0c/AmbientPixel/master/Asset/Image/p1-2.jpg?token=AAJa1zghC-jrMf7iGu76KpIgHkY2N7V2ks5V3VkiwA%3D%3D)
縦にした時、Arduino Pro Miniが地面につく辺を基準とする。
LEDが付いている方を正面とする。

- 構成
	- Arduino Pro Mini 3.3V 8MHz
	- マイコン内蔵ＲＧＢＬＥＤモジュール(AE-WS2812B)
	- 赤外線LED 3個
	- 赤外線リモコン受信モジュール 3個
	- 電池ソケット(JST PH 2P)
	- 足用のピンヘッダ 3本
- ピン配置(PIO)
	- 赤外線LED→基準から右回りで2, 3, 4
	- 受信モジュール→基準から右回りで11, 12, 13
	- LEDのデータ線→10
- サイズ
	- 一辺 : 65.8 mm
	- 高さ : 56.8 mm

## Software
### 状態
- 待機状態（Waiting）
	- データの受信待ち
- 受信状態（Receiving）
	- データを受信中。
	- Waiting状態時にpatternパケットを受け取った時に遷移する。
	- 待機状態中に受け取った最初のパケットから、データ長回だけ受信を行う。
	- 受信し終わったらWaitingへ遷移する。
- 実行状態（Running）
	- ストアに保持しているパターンを順次実行
	- runパケットを受け取った時に遷移する。
- インタラクティブ（Interactive）
	- 受け取ったパターンを即時実行

![](https://raw.githubusercontent.com/0x0c/AmbientPixel/feature/routing/Asset/Image/state.png?token=AAJa1zFFj1_y7HsZ_tm2x_kOhzt3PqwHks5V4-K4wA%3D%3D)


### パケットのデータ構造
#### 基本構造
BaseパケットとDataパケットに大別される。

#### Baseパケット

````
Base packet
|---3bit---|----5bit----|
|---type---|--data len--|
````

- type
	- パケットの種類
		- echo → 000
		- pattern → 001
		- data → 011
		- int → 100
		- int_cast → 101
		- run → 110
		- reset → 111
		- 記載していないビットは予約
- data len
	- データ長(バイト)
		- 1〜32バイト
		- 後続にデータ長*2個だけパケットが続く

#### Dataパケット

````
Data packet
|---3bit---|---4bit---|---1bit---|
|---type---|---data---|--parity--|
````

- type
	- 011
- data
	- データ部
- parity
	- パリティビット(奇数パリティ)

### echoパケット
**Base部**

- type
	- 000
- data len
	- 2
	
**Data部**

````
|---8bit---|
|----to----|
~
|---8bit---|
|---from---|
````

- to
	- 送信先デバイスID
		- masterへの場合は0
		- それ以外はフルビット
- from
	- 送信元デバイスID
		- masterからの場合は0
	
**解説**

echoパケットを受信したらmasterへ向けて返答する。
また、echoパケットを別ポートからフォワードする。

### patternパケット
**Base部**

- type
	- 001
- data len
	- 2〜32
	
**Data部**

````
|---8bit---|
|----to----|
~
|---8bit---|
|--pattern-|
~
...
````

**解説**

### intパケット
**Base部**

- type
	- 100
- data len
	- 0

**Data部**

なし

**解説**

intパケットを受け取ったノードはインタラクティブ状態へ遷移する。

### int_castパケット
**Base部**

- type
	- 101
- data len
	- 0

**Data部**

なし

**解説**

int_castパケットを受け取ったノードはインタラクティブ状態へ遷移する。
また、int_castパケットを別ポートからフォワードする。

### runパケット
**Base部**

- type
	- 110
- data len
	- 0

**Data部**

なし

**解説**

runパケットを受け取ったノードは実行状態へ遷移する。
また、runパケットを別ポートからフォワードする。

### resetパケット
**Base部**

- type
	- 111
- data len
	- 0

**Data部**

なし

**解説**

resetパケットを受け取ったノードは待機状態へ遷移する。
また、resetパケットを別ポートからフォワードする。

### 伝搬アルゴリズム
#### echoパケットによるマップツリー生成
Masterの各辺に対する2分木が作れる気がする。

#### パターンデータ伝搬
patternパケットで伝搬する

#### 指定ノードへのデータ送信
前述で生成したマップツリーから、パケットのdestに応じてforwardする。

### パターン再生ロジック
#### パターンストアへパターンを登録
パターンパケットを受信した順番でパターンストア（配列）に格納する。
runパケットを受信すると順次パターンを実行する。
resetパケットを受信するとストアはクリアされる。

#### パターンストアを順次実行
パターンにしたがってLEDを点灯させる。

#### プリセットパターン

- 点灯
- 点滅
	- 周期
- グロー
	- 点灯
	- 点滅
	
## スケジュール
- 筐体実装
	- 8/17〜8/30(予備：8/30〜9/11)
- 組み込みプログラム実装
	- 8/17〜9/11(予備：9/4〜9/18)
- アプリ実装
	- 8/21〜9/11(予備：9/11〜9/25)
- APIつなぎ込み
	- 9/11〜10/2(予備：10/2〜10/13)
- 全体つなぎ込み
	- 10/2〜10/13
