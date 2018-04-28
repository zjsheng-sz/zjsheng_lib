//
//  ViewController.m
//  JSView
//
//  Created by autel on 2018/4/26.
//  Copyright © 2018年 autel. All rights reserved.
//

#import "ViewController.h"
#import "AppDelegate.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    UIView *view1 = [[UIView alloc] initWithFrame:CGRectMake(20, 20, 300, 300)];
    view1.backgroundColor = [UIColor redColor];
    view1.bounds  = CGRectMake(-20, -20, 300, 300);
    [self.view addSubview:view1];
    
    UIView *view2 = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 200, 200)];
    view2.backgroundColor = [UIColor greenColor];
    [view1 addSubview:view2];
    
    AppDelegate *app = (AppDelegate *)[UIApplication sharedApplication].delegate;
    
    CGRect rect = [view2 convertRect:view2.frame toView:app.window];
    
    NSLog(@"xx");
    
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
