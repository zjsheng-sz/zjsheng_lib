//
//  BaseModel.m
//  Runtime
//
//  Created by autel on 2018/4/25.
//  Copyright © 2018年 zhongjiasheng. All rights reserved.
//

#import "BaseModel.h"
#import <objc/runtime.h>

@implementation BaseModel


+ (instancetype)modelWithDic:(NSDictionary *)dic{
    
    BaseModel *baseModel = [[self alloc] init];
    
    //获取所有的keyes
    NSArray *allKeys = dic.allKeys;
    

    //获取所有的properties
    unsigned outCount = 0;
    Ivar *vares = class_copyIvarList([baseModel class], &outCount);

    //如果key在properties中，则将该property的值职key对应的value
    
    for (NSString *key in allKeys) {
        
        for (int i = 0; i < outCount; i ++) {
            
            Ivar var = vares[i];
            NSString *varName = [NSString stringWithCString:ivar_getName(var) encoding:NSUTF8StringEncoding];
            
            if ([[NSString stringWithFormat:@"_%@",key] isEqualToString:varName]) {
             
                object_setIvar(baseModel, var, dic[key]);
                
            
            }
        }
    }
    
    return baseModel;

}

@end
