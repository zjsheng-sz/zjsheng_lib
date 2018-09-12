//
//  JSRunTime.m
//  Runtime
//
//  Created by autel on 2018/9/7.
//  Copyright © 2018年 zhongjiasheng. All rights reserved.
//

#import "JSRunTimeTest.h"
#import <objc/runtime.h>
#import "StudentModel.h"

void happyNewYear(id self, SEL _cmd){
    
    NSLog(@"新年快乐");
}


@implementation JSRunTimeTest

+ (void)addIvar{
    
    StudentModel *student = [StudentModel new];
    
//    class_addIvar(<#Class  _Nullable __unsafe_unretained cls#>, <#const char * _Nonnull name#>, <#size_t size#>, <#uint8_t alignment#>, <#const char * _Nullable types#>)
}

+ (void)addMethod{
    
    StudentModel *student = [StudentModel new];

    class_addMethod([student class], @selector(happy), (IMP)happyNewYear, "v@:");
    
    objc_msgSend(student, @selector(happy));
    
}

+ (void)changeIvar{
    
    StudentModel *student = [StudentModel new];
    
    student.name = @"乔布斯";
    
    Ivar ivar = class_getInstanceVariable(object_getClass(student), "_name");
    
    object_setIvar(student, ivar, @"jobs");
    
    
}

+ (void)changeMethod{
    
    
    
}

//2. 动态交换两个方法的实现

+ (void)exchangemethod{
    
    StudentModel *student = [StudentModel new];
    student.name = @"乔布斯";
    
    Method methodEat = class_getInstanceMethod([student class], @selector(eat));
    Method methodSleep = class_getInstanceMethod([student class], @selector(sleep));
    
    method_exchangeImplementations(methodEat, methodSleep);
    
    [student eat];
    [student sleep];
    
}

@end
