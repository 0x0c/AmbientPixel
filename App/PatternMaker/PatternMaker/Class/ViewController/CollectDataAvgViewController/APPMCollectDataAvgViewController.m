//
//  APPMCollectDataAvgViewController.m
//  PatternMaker
//
//  Created by Akira Matsuda on 10/20/15.
//  Copyright © 2015 Akira Matsuda. All rights reserved.
//

#import "APPMCollectDataAvgViewController.h"
#import "APPMHousingAPIGateway.h"
#import "AppDelegate.h"

@interface APPMCollectDataAvgViewController ()

@property (strong, nonatomic) IBOutlet UITextView *logView;

@end

@implementation APPMCollectDataAvgViewController

static NSDictionary *data;

- (IBAction)start:(id)sender
{
	AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
	APPMPixel *master = delegate.masterPixel;
	if ([data[@"CollectDataUnit"][@"AvgValue"] integerValue] > 7) {
		[master send:[APPMPacket packetWithDestination:0 flag:APPMPatternFlagGlow color:APPMPatternColorIndigo]];
		[master send:[APPMPacket packetWithDestination:1 flag:APPMPatternFlagGlow color:APPMPatternColorOff]];
	}
	else {
		[master send:[APPMPacket packetWithDestination:0 flag:APPMPatternFlagGlow color:APPMPatternColorOff]];
		[master send:[APPMPacket packetWithDestination:1 flag:APPMPatternFlagGlow color:APPMPatternColorIndigo]];
	}
}

- (IBAction)avg1:(id)sender
{
	data = [[APPMHousingAPIGateway sharedInstance] currentDataAvg:YES];
	self.logView.text = [data description];
}

- (IBAction)avg2:(id)sender
{
	data = [[APPMHousingAPIGateway sharedInstance] currentDataAvg:NO];
	self.logView.text = [data description];
}

@end
