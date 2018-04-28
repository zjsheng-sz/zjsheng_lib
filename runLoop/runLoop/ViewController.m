//
//  ViewController.m
//  runLoop
//
//  Created by autel on 17/7/29.
//  Copyright © 2017年 zhongjiasheng. All rights reserved.
//

//https://www.jianshu.com/p/2d3c8e084205

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.

//        [self createObserver];
    NSLog(@"%@",[NSRunLoop currentRunLoop]);
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (void)createObserver
{
    CFRunLoopObserverRef observer = CFRunLoopObserverCreateWithHandler(CFAllocatorGetDefault(), kCFRunLoopAllActivities, YES, 0, ^(CFRunLoopObserverRef observer, CFRunLoopActivity activity) {
        NSLog(@"--------%zd", activity);
        
        /*
         kCFRunLoopEntry = (1UL << 0),
         kCFRunLoopBeforeTimers = (1UL << 1),
         kCFRunLoopBeforeSources = (1UL << 2),
         kCFRunLoopBeforeWaiting = (1UL << 5),
         kCFRunLoopAfterWaiting = (1UL << 6),
         kCFRunLoopExit = (1UL << 7),
         kCFRunLoopAllActivities = 0x0FFFFFFFU
         */
    });
    
    CFRunLoopAddObserver(CFRunLoopGetCurrent(), observer, kCFRunLoopDefaultMode);  // 添加监听者，关键！
    CFRelease(observer); // 释放
}



@end
