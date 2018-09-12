//
//  JSGCDController.m
//  Multithread
//
//  Created by autel on 2018/1/10.
//  Copyright © 2018年 zhongjiasheng. All rights reserved.
//

#import "JSGCDController.h"

@implementation JSGCDController

- (void)deadlockTest{
    
    [self deadlock1];
    [self deadlock2];
    [self deadlock3];
    [self deadlock4];
    [self deadlock5];

}


- (void)deadlock1 {
    
    NSLog(@"1"); // 任务1
    
    dispatch_sync(dispatch_get_main_queue(), ^{
        
        NSLog(@"2"); // 任务2
        
    });
    NSLog(@"3"); // 任务3
}

- (void)deadlock2{
    
    NSLog(@"1"); // 任务1
    
    dispatch_sync(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
        
        sleep(3.0);
        NSLog(@"2"); // 任务2
        
    });
    
    NSLog(@"3"); // 任务3
    
}


//1,2/5,
- (void) deadlock3{
    
    dispatch_queue_t queue = dispatch_queue_create("com.demo.serialQueue", DISPATCH_QUEUE_SERIAL);
    
    NSLog(@"1"); // 任务1
    
    dispatch_async(queue, ^{
        
        NSLog(@"2"); // 任务2
        
        dispatch_sync(queue, ^{
            
            NSLog(@"3"); // 任务3
            
        });
        
        NSLog(@"4"); // 任务4
        
    });
    
    NSLog(@"5"); // 任务5
    
}

//1,5,2,3,4
-(void)deadlock4{
    
    NSLog(@"1"); // 任务1
    
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        
        NSLog(@"2"); // 任务2
        
        dispatch_sync(dispatch_get_main_queue(), ^{
            
            NSLog(@"3"); // 任务3
            
        });
        
        NSLog(@"4"); // 任务4
        
    });
    
    NSLog(@"5"); // 任务5
}

//4,1,2,3
- (void)deadlock5{
    
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        
        NSLog(@"1"); // 任务1
        
        dispatch_sync(dispatch_get_main_queue(), ^{
            
            NSLog(@"2"); // 任务2
            
        });
        
        NSLog(@"3"); // 任务3
        
    });
    
    NSLog(@"4"); // 任务4
    
    while (1) {
        
    }
    
    NSLog(@"5"); // 任务5
}

@end

