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
	self.layer.cornerRadius = 8;
	self.layer.borderColor = [UIColor lightGrayColor].CGColor;
	self.layer.borderWidth = 1;
}

@end
