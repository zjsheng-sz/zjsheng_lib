//
//  BaseModel.h
//  Runtime
//
//  Created by autel on 2018/4/25.
//  Copyright © 2018年 zhongjiasheng. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BaseModel : NSObject

/**
 字典转模型
 
 @param dic 传入字典
 @return    输出模型
 */
+ (instancetype)modelWithDic:(NSDictionary *)dic;

@end
