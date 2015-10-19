//
//  APPMSettingViewController.m
//  PatternMaker
//
//  Created by Akira Matsuda on 9/23/15.
//  Copyright (c) 2015 Akira Matsuda. All rights reserved.
//

#import "APPMSettingViewController.h"
#import "AppDelegate.h"
#import "Konashi.h"
#import "APPMPixel.h"
#import "Constant.h"
#import "JGProgressHUD.h"
#import "JTProgressHUD.h"
#import "APPMHousingAPIGateway.h"

@interface APPMSettingViewController ()

@end

@implementation APPMSettingViewController

- (void)viewDidLoad
{
	[super viewDidLoad];
	self.title = @"Setting";
	self.ipAddressTextField.text = [[NSUserDefaults standardUserDefaults] stringForKey:kIpAddress];
	self.portTextField.text = [[NSUserDefaults standardUserDefaults] stringForKey:kPort];
	self.nameTextField.text = [[NSUserDefaults standardUserDefaults] stringForKey:kName];
	if (self.nameTextField.text.length == 0) {
		self.nameTextField.text = @"Koshian01-f010f5";
	}
	
	UIBarButtonItem *doneButton = [[UIBarButtonItem alloc] initWithTitle:@"Done" style:UIBarButtonItemStyleDone target:self action:@selector(dismiss)];
	self.navigationItem.rightBarButtonItem = doneButton;
}

- (IBAction)save:(id)sender
{
	[[NSUserDefaults standardUserDefaults] setObject:self.ipAddressTextField.text forKey:kIpAddress];
	[[NSUserDefaults standardUserDefaults] setObject:self.portTextField.text forKey:kPort];
	[[NSUserDefaults standardUserDefaults] setObject:self.nameTextField.text forKey:kName];
	JGProgressHUD *HUD = [JGProgressHUD progressHUDWithStyle:JGProgressHUDStyleDark];
	HUD.textLabel.text = @"Saved";
	HUD.position = JGProgressHUDPositionBottomCenter;
	HUD.indicatorView = [JGProgressHUDSuccessIndicatorView new];
	[HUD showInView:self.view];
	[HUD dismissAfterDelay:3.0];
	[APPMHousingAPIGateway sharedInstance].ipAddress = [[NSUserDefaults standardUserDefaults] stringForKey:kIpAddress];
	[APPMHousingAPIGateway sharedInstance].port = [[NSUserDefaults standardUserDefaults] stringForKey:kPort];
}

- (IBAction)connect:(id)sender
{
	[JTProgressHUD showWithStyle:JTProgressHUDStyleGradient];
	APPMPixel *pixel = [(AppDelegate *)[[UIApplication sharedApplication] delegate] masterPixel];
	[pixel connectWithName:self.nameTextField.text completionHandler:^{
		JGProgressHUD *HUD2 = [JGProgressHUD progressHUDWithStyle:JGProgressHUDStyleDark];
		HUD2.textLabel.text = @"Connected";
		HUD2.position = JGProgressHUDPositionBottomCenter;
		HUD2.indicatorView = [JGProgressHUDSuccessIndicatorView new];
		[HUD2 showInView:self.view];
		[HUD2 dismissAfterDelay:3.0];
		[JTProgressHUD hide];
	}];
	dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(KonashiFindTimeoutInterval * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
		[JTProgressHUD hide];
	});
}

- (void)dismiss
{
	[self dismissViewControllerAnimated:YES completion:nil];
}

@end
