//
//  APPMWeatherPatternViewController.m
//  PatternMaker
//
//  Created by Akira Matsuda on 10/4/15.
//  Copyright © 2015 Akira Matsuda. All rights reserved.
//

#import "APPMWeatherPatternViewController.h"
#import "AppDelegate.h"

@implementation APPMWeatherPatternViewController

static NSDictionary *weahterColor;
static NSString *kSunnyKey = @"sunny";
static NSString *kRainyKey = @"rainy";
static NSString *kCloudyKey = @"cloudy";

- (void)viewDidLoad
{
	[super viewDidLoad];
	weahterColor = @{
				  kSunnyKey : @(APPMPatternColorOrange),
				  kRainyKey : @(APPMPatternColorBlue),
				  kCloudyKey : @(APPMPatternColorWhite)
				  };
}

- (IBAction)sendWeatherPattern:(id)sender
{
	AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
	APPMPixel *master = delegate.masterPixel;
	for (NSInteger i = 0; i < 6; i++) {
		[master send:[APPMPacket packetWithDestination:i flag:APPMPatternFlagGlow color:[weahterColor[kSunnyKey] unsignedCharValue]]];
	}
}

@end
