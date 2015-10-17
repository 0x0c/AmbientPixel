//
//  APPMPatternCollectionViewController.m
//  PatternMaker
//
//  Created by Akira Matsuda on 9/18/15.
//  Copyright (c) 2015 Akira Matsuda. All rights reserved.
//

#import "APPMPatternCollectionViewController.h"
#import "FontAwesomeKit.h"
#import "APPMProgressPatternViewController.h"
#import "APPMTerminalViewController.h"
#import "APPMPatternCollectionCell.h"
#import "APPMSettingViewController.h"

@interface APPMPatternCollectionViewController ()

@end

@implementation APPMPatternCollectionViewController

static NSString * const reuseIdentifier = @"Cell";

- (void)viewDidLoad
{
	[super viewDidLoad];
	self.title = @"PatternMaker";
	[self.collectionView registerNib:[UINib nibWithNibName:NSStringFromClass([APPMPatternCollectionCell class]) bundle:nil] forCellWithReuseIdentifier:reuseIdentifier];
	
	self.collectionView.backgroundColor = [UIColor colorWithRed:0.9866 green:0.9773 blue:0.996 alpha:1.0];
	self.collectionView.delaysContentTouches = NO;
	UICollectionViewFlowLayout *layout = (UICollectionViewFlowLayout *)self.collectionView.collectionViewLayout;
	layout.minimumLineSpacing = 4.0;
	layout.minimumInteritemSpacing = 5.0;
	layout.itemSize = CGSizeMake(CGRectGetWidth(self.view.frame) / 2.0 - 11.0, 150);
	
	UIBarButtonItem *settingButton = [[UIBarButtonItem alloc] initWithTitle:@"Setting" style:UIBarButtonItemStylePlain target:self action:@selector(showSettingViewController:)];
	self.navigationItem.rightBarButtonItem = settingButton;
}

- (void)didReceiveMemoryWarning
{
	[super didReceiveMemoryWarning];
	// Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

#pragma mark <UICollectionViewDataSource>

- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView
{
	return 1;
}


- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section
{
	return 2;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
	APPMPatternCollectionCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:reuseIdentifier forIndexPath:indexPath];
	// Configure the cell
	if (indexPath.row == 0) {
		cell.thumbnailImageView.image = [[FAKFontAwesome dashboardIconWithSize:CGRectGetWidth(self.view.frame) / 8] imageWithSize:CGSizeMake(CGRectGetWidth(self.view.frame) / 4, CGRectGetWidth(self.view.frame) / 4)];
		cell.titleLabel.text = @"Dashboard";
	}
	else {
		cell.thumbnailImageView.image = [[FAKFontAwesome terminalIconWithSize:CGRectGetWidth(self.view.frame) / 8] imageWithSize:CGSizeMake(CGRectGetWidth(self.view.frame) / 4, CGRectGetWidth(self.view.frame) / 4)];
		cell.titleLabel.text = @"Terminal";
	}
	
	return cell;
}

#pragma mark <UICollectionViewDelegate>

- (UIEdgeInsets)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout insetForSectionAtIndex:(NSInteger)section
{
	return UIEdgeInsetsMake(8, 8, 8, 8);
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath
{
	if (indexPath.row == 0) {
		APPMProgressPatternViewController *viewController = [[UIStoryboard storyboardWithName:@"Main" bundle:nil] instantiateViewControllerWithIdentifier:NSStringFromClass([APPMProgressPatternViewController class])];
		[self.navigationController pushViewController:viewController animated:YES];
	}
	else {
		APPMTerminalViewController *viewController = [[UIStoryboard storyboardWithName:@"Main" bundle:nil] instantiateViewControllerWithIdentifier:NSStringFromClass([APPMTerminalViewController class])];
		[self.navigationController pushViewController:viewController animated:YES];	
	}
}

- (void)collectionView:(UICollectionView *)colView didHighlightItemAtIndexPath:(NSIndexPath *)indexPath
{
	UICollectionViewCell *cell = [colView cellForItemAtIndexPath:indexPath];
	[UIView animateWithDuration:0.25 animations:^{
		cell.alpha = 0.7;
	}];
	[UIView animateWithDuration:0.25 delay:0 usingSpringWithDamping:0.6 initialSpringVelocity:0.8 options:UIViewAnimationOptionCurveLinear animations:^{
		cell.transform = CGAffineTransformMakeScale(0.9, 0.9);
	} completion:nil];
}

- (void)collectionView:(UICollectionView *)colView didUnhighlightItemAtIndexPath:(NSIndexPath *)indexPath
{
	UICollectionViewCell *cell = [colView cellForItemAtIndexPath:indexPath];
	[UIView animateWithDuration:0.25 animations:^{
		cell.alpha = 1;
	}];
	[UIView animateWithDuration:0.25 delay:0 usingSpringWithDamping:0.6 initialSpringVelocity:0.8 options:UIViewAnimationOptionCurveLinear animations:^{
		cell.transform = CGAffineTransformMakeScale(1, 1);
	} completion:nil];
}

#pragma mark -

- (void)showSettingViewController:(id)sender
{
	APPMSettingViewController *viewController = [[UIStoryboard storyboardWithName:@"Main" bundle:nil] instantiateViewControllerWithIdentifier:NSStringFromClass([APPMSettingViewController class])];
	UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:viewController];
	[self presentViewController:navigationController animated:YES completion:nil];
}

@end
