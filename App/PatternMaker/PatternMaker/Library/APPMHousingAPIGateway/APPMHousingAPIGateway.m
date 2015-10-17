//
//  APPMHousingAPIGateway.m
//  PatternMaker
//
//  Created by Akira Matsuda on 9/18/15.
//  Copyright (c) 2015 Akira Matsuda. All rights reserved.
//

#import "APPMHousingAPIGateway.h"

@implementation APPMHousingAPIGateway

+ (instancetype)sharedInstance
{
	static APPMHousingAPIGateway *sharedInstance;
	static dispatch_once_t onceToken;
	dispatch_once(&onceToken, ^{
		sharedInstance = [[self class] new];
	});
	
	return sharedInstance;
}

- (HousingApi *)sendCommand:(NSString *)command timeoutInterval:(NSTimeInterval)timeoutInterval error:(NSError **)error
{
	//接続処理
	HousingApi *housingApi = [HousingApi new];
	//IPアドレス、ポート番号、コマンドを渡すと、ライブラリ内でHTTPリクエストを生成して送信し、応答メッセージを解析する。
	//戻り値には解析後の応答メッセージが格納されている。
	BOOL connectResulst = [housingApi sendCommand:self.ipAddress port:self.port command:command timeoutInterval:timeoutInterval error:error];
	if (connectResulst) {
		//応答メッセージから瞬時電力値を取得する
		//<result>タグの情報を取得します。　引数には、<result>タグまでのXMLタグを全て指定します。「resultset」「result」を設定しています。
		[housingApi getResponseResult:kLocalElementResultset, kLocalElementResult, nil];
	}
	else {
		*error = [NSError errorWithDomain:@"Connection error" code:-1 userInfo:nil];
	}
	
	return housingApi;
}

- (NSDictionary *)currentDataAvg:(BOOL)up
{
	NSError *e;
	NSString *filename = up ? @"current" : @"current_down";
	NSString *jsonString = [NSString stringWithContentsOfFile:[[NSBundle mainBundle] pathForResource:filename ofType:@"txt"] encoding:NSUTF8StringEncoding error:&e];
	NSDictionary *result = nil;
	if (e == nil) {
		result = [NSJSONSerialization JSONObjectWithData:[jsonString dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingAllowFragments error:&e];
	}
	
	return result;
}

@end
