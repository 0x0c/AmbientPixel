//
//  APPMPacket.h
//  PatternMaker
//
//  Created by Akira Matsuda on 9/18/15.
//  Copyright (c) 2015 Akira Matsuda. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(UInt8, APPMPatternFlag) {
	APPMPatternFlagGlow = 0b00000000,
	APPMPatternFlagBlink = 0b00001000,
	APPMPatternFlagTurnOff = 0b00010000,
	APPMPatternFlagControl = 0b00011000,
};

typedef NS_ENUM(UInt8, APPMPatternColor) {
	APPMPatternColorRed = 0b00000000,
	APPMPatternColorGreen = 0b00000001,
	APPMPatternColorBlue = 0b00000010,
	APPMPatternColorOrange = 0b00000011,
	APPMPatternColorPurple = 0b00000100,
	APPMPatternColorIndigo = 0b00000101,
	APPMPatternColorWhite = 0b00000110,
	APPMPatternColorOff = 0b00000111,
};

@interface APPMPacket : NSObject

@property (nonatomic, readonly) UInt8 destination;
@property (nonatomic, readonly) APPMPatternFlag flag;
@property (nonatomic, readonly) APPMPatternColor color;

+ (instancetype)packetWithDestination:(UInt8)destination flag:(APPMPatternFlag)flag color:(APPMPatternColor)color;
- (NSData *)data;

@end
