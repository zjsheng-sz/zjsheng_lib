//
//  JSOperationController.m
//  Multithread
//
//  Created by autel on 2018/1/10.
//  Copyright © 2018年 zhongjiasheng. All rights reserved.
//

//https://www.jianshu.com/p/0b0d9b1f1f19

#import "JSOperationController.h"

@implementation JSOperationController


//任务依赖
- (void)dependentOperation{
    
    //1.任务一：下载图片
    NSBlockOperation *operation1 = [NSBlockOperation blockOperationWithBlock:^{
        NSLog(@"下载图片 - %@", [NSThread currentThread]);
        [NSThread sleepForTimeInterval:1.0];
    }];
    
    //2.任务二：打水印
    NSBlockOperation *operation2 = [NSBlockOperation blockOperationWithBlock:^{
        NSLog(@"打水印   - %@", [NSThread currentThread]);
        [NSThread sleepForTimeInterval:1.0];
    }];
    
    //3.任务三：上传图片
    NSBlockOperation *operation3 = [NSBlockOperation blockOperationWithBlock:^{
        NSLog(@"上传图片 - %@", [NSThread currentThread]);
        [NSThread sleepForTimeInterval:1.0];
    }];
    
    //4.设置依赖
    [operation2 addDependency:operation1];      //任务二依赖任务一
    [operation3 addDependency:operation2];      //任务三依赖任务二
    
    //5.创建队列并加入任务
    NSOperationQueue *queue = [[NSOperationQueue alloc] init];
    [queue addOperations:@[operation3, operation2, operation1] waitUntilFinished:NO];
    
}


//基本操作
- (void)basicOperation{
    
    
//    //1.创建NSBlockOperation对象
//    NSBlockOperation *blockOperation = [NSBlockOperation blockOperationWithBlock:^{
//        NSLog(@"%@", [NSThread currentThread]);
//    }];
//    [blockOperation start];
    
    
    //1.创建NSBlockOperation对象
    NSBlockOperation *invocationOperation = [NSBlockOperation blockOperationWithBlock:^{
        NSLog(@"%@", [NSThread currentThread]);
    }];
    
    //添加多个Block
    for (NSInteger i = 0; i < 5; i++) {
        [invocationOperation addExecutionBlock:^{
            NSLog(@"第%ld次：%@", i, [NSThread currentThread]);
        }];//addExecutionBlock 方法必须在 start() 方法之前执行，否则就会报错：
    }
    //2.开始任务
    [invocationOperation start];
    
    
//    NSOperationQueue *mainQueue = [NSOperationQueue mainQueue];
//
//    //1.创建一个其他队列
//    NSOperationQueue *queue = [[NSOperationQueue alloc] init];
//
//    //2.创建NSBlockOperation对象
//    NSBlockOperation *operation = [NSBlockOperation blockOperationWithBlock:^{
//        NSLog(@"%@", [NSThread currentThread]);
//    }];
//
//    //3.添加多个Block
//    for (NSInteger i = 0; i < 5; i++) {
//        [operation addExecutionBlock:^{
//            NSLog(@"第%ld次：%@", i, [NSThread currentThread]);
//        }];
//    }
//    //4.队列添加任务
//    [queue addOperation:operation];
    
    
}

- (void)run{
    
    NSLog(@"%@",[NSThread currentThread]);
}

@end
