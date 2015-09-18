//
//  APPMPixel.h
//  PatternMaker
//
//  Created by Akira Matsuda on 9/18/15.
//  Copyright (c) 2015 Akira Matsuda. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "APPMPacket.h"

@interface APPMPixel : NSObject

- (void)connectWithName:(NSString *)name completionHandler:(void (^)())handler;
- (void)send:(APPMPacket *)packet;

@end
