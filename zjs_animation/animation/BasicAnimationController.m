//
//  ViewController.m
//  animation
//
//  Created by autel on 2018/1/11.
//  Copyright © 2018年 autel. All rights reserved.
//

//https://www.jianshu.com/p/5abc038e4d94

#import "BasicAnimationController.h"

@interface BasicAnimationController ()
@property (weak, nonatomic) IBOutlet UIView *cartCenterView;
@property (weak, nonatomic) IBOutlet UIView *centerShowView;

@end

@implementation BasicAnimationController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


//普通动画
- (IBAction)normalAnimation:(id)sender {
    
    
//    [UIView animateWithDuration:1.0 animations:^{
//
//        self.cartCenterView.frame = self.centerShowView.frame;
//    }];
//
//    [UIView animateWithDuration:1.0 animations:^{
//
//        self.cartCenterView.frame = self.centerShowView.frame;
//    } completion:^(BOOL finished) {
//        NSLog(@"动画结束");
//    }];
    
    
    [UIView animateWithDuration:1.0 delay:1.0 options:UIViewAnimationOptionCurveEaseInOut animations:^{
        [UIView setAnimationRepeatCount:3.0];
        self.cartCenterView.frame = self.centerShowView.frame;
    } completion:^(BOOL finished) {
        NSLog(@"动画结束");
    }];
    
}

//spring动画
- (IBAction)springAnimation:(id)sender {
    
    [UIView animateWithDuration:1.0 delay:1.0 usingSpringWithDamping:0.5 initialSpringVelocity:100 options:UIViewAnimationOptionCurveLinear animations:^{
        self.cartCenterView.frame = self.centerShowView.frame;
    } completion:^(BOOL finished) {
        NSLog(@"动画结束");
    }];
    
}

/*
 UIViewKeyframeAnimationOptionCalculationModeLinear     //运算模式 :连续
 UIViewKeyframeAnimationOptionCalculationModeDiscrete   //运算模式 :离散
 UIViewKeyframeAnimationOptionCalculationModePaced      //运算模式 :均匀执行
 UIViewKeyframeAnimationOptionCalculationModeCubic      //运算模式 :平滑
 UIViewKeyframeAnimationOptionCalculationModeCubicPaced //运算模式 :平滑均匀
 */

//关键帧动画
- (IBAction)keyframeAnimation:(id)sender {
    
    [UIView animateKeyframesWithDuration:9.0 delay:0.f options:UIViewKeyframeAnimationOptionCalculationModeLinear animations:^{
        [UIView addKeyframeWithRelativeStartTime:0.f relativeDuration:1.0 / 4 animations:^{
            self.centerShowView.backgroundColor = [UIColor colorWithRed:0.9475 green:0.1921 blue:0.1746 alpha:1.0];
        }];
        [UIView addKeyframeWithRelativeStartTime:1.0 / 4 relativeDuration:1.0 / 4 animations:^{
            self.centerShowView.backgroundColor = [UIColor colorWithRed:0.1064 green:0.6052 blue:0.0334 alpha:1.0];
        }];
        [UIView addKeyframeWithRelativeStartTime:2.0 / 4 relativeDuration:1.0 / 4 animations:^{
            self.centerShowView.backgroundColor = [UIColor colorWithRed:0.1366 green:0.3017 blue:0.8411 alpha:1.0];
        }];
        [UIView addKeyframeWithRelativeStartTime:3.0 / 4 relativeDuration:1.0 / 4 animations:^{
            self.centerShowView.backgroundColor = [UIColor colorWithRed:0.619 green:0.037 blue:0.6719 alpha:1.0];
        }];
    } completion:^(BOOL finished) {
        NSLog(@"动画结束");
    }];
    
}

//转场动画
- (IBAction)transformAnimation:(id)sender {
    
//    [UIView transitionWithView:self.centerShowView duration:1.0 options:UIViewAnimationOptionTransitionCrossDissolve animations:^{
//        self.centerShowView.backgroundColor = [UIColor redColor];
//    } completion:^(BOOL finished) {
//        NSLog(@"动画结束");
//    }];
    
    UIView *newCenterShowView = [[UIView alloc] initWithFrame:self.centerShowView.frame];
    newCenterShowView.backgroundColor = [UIColor blueColor];

    [UIView transitionFromView:self.centerShowView toView:newCenterShowView duration:1.0 options:UIViewAnimationOptionTransitionFlipFromTop completion:^(BOOL finished) {
        NSLog(@"动画结束");
    }];
    
//    UIViewAnimationOptionTransitionFlipFromLeft    = 1 << 20,
//    UIViewAnimationOptionTransitionFlipFromRight   = 2 << 20,
//    UIViewAnimationOptionTransitionCurlUp          = 3 << 20,
//    UIViewAnimationOptionTransitionCurlDown        = 4 << 20,
//    UIViewAnimationOptionTransitionCrossDissolve   = 5 << 20,
//    UIViewAnimationOptionTransitionFlipFromTop     = 6 << 20,
//    UIViewAnimationOptionTransitionFlipFromBottom  = 7 << 20,

}

@end
