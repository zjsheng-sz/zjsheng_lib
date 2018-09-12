//
//  main.m
//  Multithread
//
//  Created by autel on 17/7/31.
//  Copyright © 2017年 zhongjiasheng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JSGCDController.h"


int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        NSLog(@"Hello, World!");
        
        //死锁测试
        JSGCDController *GCDController = [[JSGCDController alloc] init];
        [GCDController deadlockTest];
        
        NSRunLoop *runloop = [NSRunLoop currentRunLoop];
        [runloop run];
        
    }
    return 0;
}



