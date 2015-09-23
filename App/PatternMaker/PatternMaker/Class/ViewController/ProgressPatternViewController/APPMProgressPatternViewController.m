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

@interface APPMProgressPatternViewController () <UIPickerViewDelegate, UIPickerViewDataSource>

@property (strong, nonatomic) IBOutlet UIPickerView *pickerView;

@end

@implementation APPMProgressPatternViewController

static NSArray *pickerTitles;

- (void)viewDidLoad
{
	[super viewDidLoad];
	self.title = @"Progress";
	pickerTitles = @[@"水の使用量",
				  @"ガスの使用量",
				  @"蓄電池残量"];
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
	NSLog(@"%@", pickerTitles[row]);
}

#pragma mark - UIPickerViewDataSource

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{
	return pickerTitles.count;
}

#pragma mark - 

@end
