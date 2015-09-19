//
//  HousingApi.h
//  HousingApiLibrary
//
//  Created by Daiwa House Industry Co., Ltd. on 2015/02/05.
//  Copyright (c) 2015 Daiwa House Industry Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HousingApiConstant.h"

@interface HousingApi : NSObject

- (BOOL)sendCommand: (NSString*)ipAddress
               port:(NSString*)portNo
            command:(NSString*)command
    timeoutInterval:(NSTimeInterval)timeoutInterval
              error:(NSError**)error;

- (BOOL) getResponseResult:(NSString*)rootTag
, ...NS_REQUIRES_NIL_TERMINATION;

- (NSString*) getResponseError:(NSString*)rootTag
, ...NS_REQUIRES_NIL_TERMINATION;

- (id) getResponseData:(NSString*)rootTag
, ...NS_REQUIRES_NIL_TERMINATION;

@end

