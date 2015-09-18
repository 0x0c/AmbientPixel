//
//  APPMPixel.m
//  PatternMaker
//
//  Created by Akira Matsuda on 9/18/15.
//  Copyright (c) 2015 Akira Matsuda. All rights reserved.
//

#import "APPMPixel.h"
#import "Konashi.h"

@interface APPMPixel ()

@property (nonatomic, strong) KNSPeripheral *peripheral;

@end

@implementation APPMPixel

- (void)connectWithName:(NSString *)name completionHandler:(void (^)())handler
{
	__weak typeof(self) bself = self;
	[[KNSCentralManager sharedInstance] connectWithName:name timeout:KonashiFindTimeoutInterval connectedHandler:^(KNSPeripheral *connectedPeripheral) {
		bself.peripheral = connectedPeripheral;
		[connectedPeripheral setReadyHandler:^{
			[bself.peripheral uartMode:KonashiUartModeEnable baudrate:KonashiUartBaudrateRate9K6];
			if (handler) {
				handler();
			}
		}];
	}];
}

- (void)send:(APPMPacket *)packet
{
	[self.peripheral uartWriteData:packet.data];
}

@end
