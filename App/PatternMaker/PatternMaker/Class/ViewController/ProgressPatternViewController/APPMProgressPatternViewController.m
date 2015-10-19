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
@property (nonatomic, assign) APPMPatternColor color;
@property (nonatomic, assign) APPMProgressPatternMode mode;
@property (strong, nonatomic) IBOutlet UITextView *logView;

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
	commands = @[@"/smart/history?type=get&key=waterConsumption&target=20141215",
			   @"/smart/history?type=get&key=gasConsumption&target=201412",
			   @"/smart/rest/request?deviceid=lite.battery_1_1&type=get&key=soc"];
	self.mode = APPMProgressPatternModeWater;
	self.color = APPMPatternColorBlue;
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

- (IBAction)start:(id)sender
{
	[self readData];
}

- (void)readData
{
	NSError *e = nil;
	HousingApi *result = [[APPMHousingAPIGateway sharedInstance] sendCommand:commands[self.mode] timeoutInterval:10 error:&e];
	if (e == nil) {
		// pixelの表示を更新
		AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
		APPMPixel *master = delegate.masterPixel;
		NSInteger value = 0;
		switch (self.mode) {
			case APPMProgressPatternModeWater: {
				NSArray *data = [result getResponseData:kLocalElementResultset, kLocalElementDataSet, kLocalElementData, nil];
				NSDictionary *d = data.lastObject;
				value = [d[kLocalElementValue] integerValue] / 50;
				self.logView.text = [data description];
				break;
			}
			case APPMProgressPatternModeGas: {
				NSArray *data = [result getResponseData:kLocalElementResultset, kLocalElementDataSet, kLocalElementData, nil];
				NSDictionary *d = data.lastObject;
				value = [d[kLocalElementValue] integerValue] / 100;
				self.logView.text = [data description];
				break;
			}
			case APPMProgressPatternModeBattery: {
				NSDictionary *data = [result getResponseData:kLocalElementResultset, kLocalElementDataSet, kLocalElementData, nil];
				value = [data[kLocalElementValue] integerValue] / 100;
				self.logView.text = [data description];
				break;
			}
			default: {
				break;
			}
		}
		// 4, 5, 0, 1, 2, 3
		NSArray *indexes = @[@(4), @(5), @(0), @(1), @(2), @(3)];
		NSLog(@"%ld", (long)value);
		value = MIN(8 , value);
		for (NSInteger idx = 0; idx < value; idx++) {
			NSNumber *i = indexes[idx];
			[master send:[APPMPacket packetWithDestination:i.integerValue flag:APPMPatternFlagGlow color:self.color]];
		}
		for (NSInteger idx = value; idx < 8 - value; idx++) {
			NSNumber *i = indexes[idx];
			[master send:[APPMPacket packetWithDestination:i.integerValue flag:APPMPatternFlagGlow color:APPMPatternColorOff]];
		}
	}
}

@end
