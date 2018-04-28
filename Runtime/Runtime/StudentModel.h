//
//  Student.h
//  Runtime
//
//  Created by autel on 2018/1/10.
//  Copyright © 2018年 zhongjiasheng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BaseModel.h"

@interface StudentModel :BaseModel

@property(nonatomic, copy) NSString *name;
@property(nonatomic, copy) NSString *age;

- (void)eat;
- (void)sleep;

@end
