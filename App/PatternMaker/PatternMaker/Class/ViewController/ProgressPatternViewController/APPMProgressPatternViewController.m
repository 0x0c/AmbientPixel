//
//  APPMProgressPatternViewController.m
//  PatternMaker
//
//  Created by Akira Matsuda on 9/18/15.
//  Copyright (c) 2015 Akira Matsuda. All rights reserved.
//

#import "APPMProgressPatternViewController.h"
#import "AppDelegate.h"
#import "APPMPixel.h"
#import "APPMHousingAPIGateway.h"

typedef NS_ENUM(NSUInteger, APPMProgressPatternMode) {
	APPMProgressPatternModeWater = 0,
	APPMProgressPatternModeGas = 1,
	APPMProgressPatternModeBattery = 2,
};

@interface APPMProgressPatternViewController () <UIPickerViewDelegate, UIPickerViewDataSource>

@property (strong, nonatomic) IBOutlet UIPickerView *pickerView;
@property (nonatomic, strong) NSTimer *requestTimer;
@property (nonatomic, assign) APPMPatternColor color;
@property (nonatomic, assign) APPMProgressPatternMode mode;

@end

@implementation APPMProgressPatternViewController

static NSArray *pickerTitles;
static NSArray<NSString *> *commands;

- (void)viewDidLoad
{
	[super viewDidLoad];
	self.title = @"Progress";
	pickerTitles = @[@"水の使用量",
				  @"ガスの使用量",
				  @"蓄電池残量"];
	commands = @[@"/smart/history?type=get&key=waterConsumption&target=2014121530",
			   @"/smart/history?type=get&key=gasConsumption&target=2014121530",
			   @"/smart/rest/request?deviceid=lite.battery_1_1&type=get&key=soc"];
	self.mode = APPMProgressPatternModeBattery;
}

- (void)dealloc
{
	[self.requestTimer invalidate];
}

#pragma mark - UIPickerViewDelegate

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
	return 1;
}

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
	return pickerTitles[row];
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
	self.mode = row;
	switch (row) {
		case 0: {
			self.color = APPMPatternColorBlue;
		}
			break;
		case 1: {
			self.color = APPMPatternColorGreen;
		}
			break;
		case 2: {
			self.color = APPMPatternColorOrange;
		}
			break;
		default:
			break;
	}
}

#pragma mark - UIPickerViewDataSource

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{
	return pickerTitles.count;
}

#pragma mark - 

- (void)scheduleAPIRequest
{
	if (self.requestTimer) {
		[self.requestTimer invalidate];
	}
	// 30分間隔
	self.requestTimer = [NSTimer scheduledTimerWithTimeInterval:60 * 30 target:self selector:@selector(readData) userInfo:nil repeats:YES];
}

- (void)readData
{
	NSError *e = nil;
	HousingApi *result = [[APPMHousingAPIGateway sharedInstance] sendCommand:commands[self.mode] timeoutInterval:10 error:&e];
	if (e == nil) {
		// pixelの表示を更新
		AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
		APPMPixel *master = delegate.masterPixel;
		switch (self.mode) {
			case APPMProgressPatternModeWater: {
				NSArray *data = [result getResponseData:kLocalElementResultset,
							  kLocalElementDataSet, kLocalElementData, nil];
				NSDictionary *d = data.lastObject;
				NSInteger value = [d[kLocalElementValue] integerValue] / 100;
				for (UInt8 i = 0; i < value; i++) {
					[master send:[APPMPacket packetWithDestination:i flag:APPMPatternFlagGlow color:self.color]];
				}
				break;
			}
			case APPMProgressPatternModeGas: {
				NSArray *data = [result getResponseData:kLocalElementResultset,
								  kLocalElementDataSet, kLocalElementData, nil];
				NSDictionary *d = data.lastObject;
				NSInteger value = [d[kLocalElementValue] integerValue] / 100;
				for (UInt8 i = 0; i < value; i++) {
					[master send:[APPMPacket packetWithDestination:i flag:APPMPatternFlagGlow color:self.color]];
				}
				break;
			}
			case APPMProgressPatternModeBattery: {
				NSDictionary *data = [result getResponseData:kLocalElementResultset,
								  kLocalElementDataSet, kLocalElementData, nil];
				NSInteger value = [data[kLocalElementValue] integerValue] / 100;
				for (UInt8 i = 0; i < value; i++) {
					[master send:[APPMPacket packetWithDestination:i flag:APPMPatternFlagGlow color:self.color]];
				}
				break;
			}
			default: {
				break;
			}
		}
	}
}

@end
