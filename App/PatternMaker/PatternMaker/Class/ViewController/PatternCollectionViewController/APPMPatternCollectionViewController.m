//
//  APPMPatternCollectionViewController.m
//  PatternMaker
//
//  Created by Akira Matsuda on 9/18/15.
//  Copyright (c) 2015 Akira Matsuda. All rights reserved.
//

#import "APPMPatternCollectionViewController.h"
#import "APPMPatternCollectionCell.h"

@interface APPMPatternCollectionViewController ()

@end

@implementation APPMPatternCollectionViewController

static NSString * const reuseIdentifier = @"Cell";

- (void)viewDidLoad
{
	[super viewDidLoad];
	[self.collectionView registerNib:[UINib nibWithNibName:NSStringFromClass([APPMPatternCollectionCell class]) bundle:nil] forCellWithReuseIdentifier:reuseIdentifier];
	
	self.collectionView.delaysContentTouches = NO;
	UICollectionViewFlowLayout *layout = (UICollectionViewFlowLayout *)self.collectionView.collectionViewLayout;
	layout.minimumLineSpacing = 4.0;
	layout.minimumInteritemSpacing = 5.0;
	layout.itemSize = CGSizeMake(CGRectGetWidth(self.view.frame) / 2.0 - 11.0, 150);
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
	return 5;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
	APPMPatternCollectionCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:reuseIdentifier forIndexPath:indexPath];
	// Configure the cell
	
	return cell;
}

#pragma mark <UICollectionViewDelegate>

/*
// Uncomment this method to specify if the specified item should be highlighted during tracking
- (BOOL)collectionView:(UICollectionView *)collectionView shouldHighlightItemAtIndexPath:(NSIndexPath *)indexPath {
	return YES;
}
*/

/*
// Uncomment this method to specify if the specified item should be selected
- (BOOL)collectionView:(UICollectionView *)collectionView shouldSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    return YES;
}
*/

/*
// Uncomment these methods to specify if an action menu should be displayed for the specified item, and react to actions performed on the item
- (BOOL)collectionView:(UICollectionView *)collectionView shouldShowMenuForItemAtIndexPath:(NSIndexPath *)indexPath {
	return NO;
}

- (BOOL)collectionView:(UICollectionView *)collectionView canPerformAction:(SEL)action forItemAtIndexPath:(NSIndexPath *)indexPath withSender:(id)sender {
	return NO;
}

- (void)collectionView:(UICollectionView *)collectionView performAction:(SEL)action forItemAtIndexPath:(NSIndexPath *)indexPath withSender:(id)sender {
	
}
*/

- (UIEdgeInsets)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout insetForSectionAtIndex:(NSInteger)section
{
	return UIEdgeInsetsMake(8, 8, 8, 8);
}

- (void)collectionView:(UICollectionView *)colView didHighlightItemAtIndexPath:(NSIndexPath *)indexPath
{
	UICollectionViewCell *cell = [colView cellForItemAtIndexPath:indexPath];
	[UIView animateWithDuration:0.25 animations:^{
		cell.alpha = 0.7;
	}];
	[UIView animateWithDuration:0.25 delay:0 usingSpringWithDamping:0.6 initialSpringVelocity:0.8 options:UIViewAnimationOptionCurveLinear animations:^{
		cell.transform = CGAffineTransformMakeScale(0.95, 0.95);
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

@end
