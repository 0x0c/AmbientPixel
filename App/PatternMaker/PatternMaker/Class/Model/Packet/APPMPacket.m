//
//  APPMPacket.m
//  PatternMaker
//
//  Created by Akira Matsuda on 9/18/15.
//  Copyright (c) 2015 Akira Matsuda. All rights reserved.
//

#import "APPMPacket.h"

@interface APPMPacket ()

@property (nonatomic, assign) UInt8 destination;
@property (nonatomic, assign) APPMPatternFlag flag;
@property (nonatomic, assign) APPMPatternColor color;

@end

@implementation APPMPacket

+ (instancetype)packetWithDestination:(UInt8)destination flag:(APPMPatternFlag)flag color:(APPMPatternColor)color
{
	APPMPacket *packet = [APPMPacket new];
	packet.destination = destination;
	packet.flag = flag;
	packet.color = color;
	
	return packet;
}

- (NSData *)data
{
	UInt8 destinationBit = self.destination & 0b11100000;
	Byte byte = (UInt8)(destinationBit | self.flag | self.color);
	NSData *data = [NSData dataWithBytes:&byte length:1];
	
	return data;
}

@end
