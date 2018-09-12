//
//  JSRunTime.h
//  Runtime
//
//  Created by autel on 2018/9/7.
//  Copyright © 2018年 zhongjiasheng. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface JSRunTimeTest : NSObject

//1. 动态的添加对象的成员变量和方法,修改属性值和方法

+ (void)addIvar;

+ (void)addMethod;

+ (void)changeIvar;

+ (void)changeMethod;

//2. 动态交换两个方法的实现

+ (void)exchangemethod;

//3. 实现分类也可以添加属性 : Student+Category

//4. 实现NSCoding的自动归档和解档


//5. 实现字典转模型的自动转换: BaseModel

//6. 动态创建一个类(比如KVO的底层实现)

@end
