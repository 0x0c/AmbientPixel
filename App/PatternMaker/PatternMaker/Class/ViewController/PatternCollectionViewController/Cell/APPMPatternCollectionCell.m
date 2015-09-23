//
//  APPMPatternCollectionCell.m
//  PatternMaker
//
//  Created by Akira Matsuda on 9/18/15.
//  Copyright (c) 2015 Akira Matsuda. All rights reserved.
//

#import "APPMPatternCollectionCell.h"

@implementation APPMPatternCollectionCell

- (void)awakeFromNib
{
	// Initialization code
	self.layer.cornerRadius = 6;
	self.backgroundColor = [UIColor colorWithRed:0.9953 green:0.9907 blue:1.0 alpha:1.0];
	self.layer.borderWidth = 1;
	self.layer.borderColor = [UIColor colorWithRed:0.8513 green:0.8433 blue:0.8593 alpha:1.0].CGColor;
	self.layer.shadowOffset = CGSizeMake(1, 1);
	self.layer.shadowRadius = 1;
	self.layer.shadowColor = [UIColor blackColor].CGColor;
	self.layer.shadowOpacity = 1.0;
}

@end
