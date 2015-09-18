//
//  APPMPacket.h
//  PatternMaker
//
//  Created by Akira Matsuda on 9/18/15.
//  Copyright (c) 2015 Akira Matsuda. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_OPTIONS(UInt8, APPMPatternFlag) {
	APPMPatternFlagGlow = 0b00000000,
	APPMPatternFlagBlink = 0b00001000,
//	0b00010000 は未定義
	APPMPatternFlagTurnOff = 0b00011000,
};

typedef NS_ENUM(UInt8, APPMPatternColor) {
	APPMPatternColorRed = 0b00000000,
	APPMPatternColorBlue = 0b00000001,
	APPMPatternColorGreen = 0b00000010,
	APPMPatternColorOrange = 0b00000011,
	APPMPatternColorYellow = 0b00000100,
	APPMPatternColorPurple = 0b00000101,
	APPMPatternColorIndigo = 0b00000110,
	APPMPatternColorWhite = 0b00000111,
};

@interface APPMPacket : NSObject

@property (nonatomic, readonly) UInt8 destination;
@property (nonatomic, readonly) APPMPatternFlag flag;
@property (nonatomic, readonly) APPMPatternColor color;

+ (instancetype)packetWithDestination:(UInt8)destination flag:(APPMPatternFlag)flag color:(APPMPatternColor)color;
- (NSData *)data;

@end
