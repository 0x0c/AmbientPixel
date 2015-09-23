//
//  AppDelegate.h
//  PatternMaker
//
//  Created by Akira Matsuda on 8/22/15.
//  Copyright (c) 2015 Akira Matsuda. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "APPMPixel.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (nonatomic, strong) APPMPixel *masterPixel;

@end

