# ユースケース
## ＜プログレスバー＞
各メーターの値をプログレスバー状に並べたデバイスに表示する。

### 使うAPI
住宅API(エネルギー系)

太陽光発電、蓄電池
### 目的・メリット
数値でなく、もっと感覚的に消費量、蓄積量を知る。

## だれ
家族全員

## いつ
一日中

## どこで
どこでも。
キッチン・風呂場・エアコンの下？



### 表示する項目
- ガス
- 水
- 電気

デバイス数に対してパーセントで表示。

## ＜前日日のUP、DOWN表示＞
各メーターの量を前日と比べたUP、DOWNだけでシンプルに表示する

### 使うAPI
住宅API(エネルギー系)

水道メーター、ガスメーター、分電盤
### 目的・メリット
数値でなく、もっと感覚的に消費量、蓄積量を知る。

## だれ
家族全員

## いつ
一日の終わり

## どこで
どこでも。
キッチン・風呂場・エアコンの下？



### 表示する項目
- ガス
- 水
- 電気

↑↓で表示


## ＜目標までの節約の達成率を表示する＞
六角形にデバイスを並べて、目標金額までの達成率を表示する

全てに色がついたら目標達成

### 使うAPI
太陽光発電売却電力量(日)、消費電気料（日）

### 目的・メリット
スマートハウスにすることでどの程度お得になったのかを感覚的に知ることができる

達成率を競うゲームのような感覚を与えることで家族全員の省エネ意識につながる
## だれ
家族全員

## いつ
食事の時間とかの話のネタに

## どこで
食卓から見えるところ
