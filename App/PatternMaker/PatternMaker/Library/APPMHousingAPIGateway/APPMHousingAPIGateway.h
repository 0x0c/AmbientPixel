//
//  APPMHousingAPIGateway.h
//  PatternMaker
//
//  Created by Akira Matsuda on 9/18/15.
//  Copyright (c) 2015 Akira Matsuda. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HousingApi.h"

@interface APPMHousingAPIGateway : NSObject

@property (nonatomic, strong) NSString *ipAddress;
@property (nonatomic, strong) NSString *port;

+ (instancetype)sharedInstance;
- (HousingApi *)sendCommand:(NSString *)command timeoutInterval:(NSTimeInterval)timeoutInterval error:(NSError **)error;

@end
