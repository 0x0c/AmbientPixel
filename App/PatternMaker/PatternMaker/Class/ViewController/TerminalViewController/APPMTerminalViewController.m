//
//  TerminalViewController.m
//  PatternMaker
//
//  Created by Akira Matsuda on 10/17/15.
//  Copyright © 2015 Akira Matsuda. All rights reserved.
//

#import "AppDelegate.h"
#import "APPMTerminalViewController.h"
#import "APPMPacket.h"

@interface APPMTerminalViewController ()

@property (nonatomic, assign) UInt8 destination;
@property (nonatomic, assign) APPMPatternFlag flag;
@property (nonatomic, assign) APPMPatternColor color;

@end

@implementation APPMTerminalViewController

static NSArray *flagTitles;
static NSArray *colorTitles;

#pragma mark - UIPickerViewDelegate

- (void)viewDidLoad
{
	[super viewDidLoad];
	self.title = @"Terminal";
	
	flagTitles = @[@"Glow", @"Blink", @"TurnOff"];
	colorTitles = @[@"Red", @"Green", @"Blue", @"Orange", @"Purple", @"Indigo", @"White", @"Off"];
}

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
	return 3;
}

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component
{
	NSString *title = nil;
	if (component == 0) {
		title = [NSString stringWithFormat:@"%ld", (long)row];
	}
	else if (component == 1) {
		title = flagTitles[row];
	}
	else {
		title = colorTitles[row];
	}
	
	return title;
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
	if (component == 0) {
		self.destination = row;
	}
	else if (component == 1) {
		self.flag = row;
	}
	else {
		self.color = row;
	}
}

#pragma mark - UIPickerViewDataSource

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{
	NSInteger row = 0;
	if (component == 0) {
		row = 8;
	}
	else if (component == 1) {
		row = flagTitles.count;
	}
	else {
		row = colorTitles.count;
	}
	
	return row;
}

#pragma mark -

- (IBAction)sendPacket:(id)sender
{
	AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
	APPMPixel *master = delegate.masterPixel;
	[master send:[APPMPacket packetWithDestination:self.destination flag:self.flag color:self.color]];
}

@end
