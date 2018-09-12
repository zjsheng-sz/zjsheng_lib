//
//  CoreAnimationController.m
//  animation
//
//  Created by autel on 2018/1/11.
//  Copyright © 2018年 autel. All rights reserved.
//

//https://www.jianshu.com/p/d05d19f70bac


#import "CoreAnimationController.h"

@interface CoreAnimationController ()

@property (weak, nonatomic) IBOutlet UIView *cartCenterView;
@property (weak, nonatomic) IBOutlet UIView *centerShowView;

@end

@implementation CoreAnimationController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
 核心动画的优点有：
    1）性能强大，使用硬件加速，可以同时向多个图层添加不同的动画效果
 　　2）接口易用，只需要少量的代码就可以实现复杂的动画效果。
 　　3）运行在后台线程中，在动画过程中可以响应交互事件（UIView动画默认动画过程中不响应交互事件）。
 
 
 核心动画类中可以直接使用的类有：
 
 CABasicAnimation
 　　CAKeyframeAnimation
 　　CATransition
 　　CAAnimationGroup
 　　CASpringAnimation
 
 CAAnimation / CAAnimationGroup
               CATransition
               CAPropertyAnimation / CABasicAnimation  / CASpringAnimation
                                     CAKeyframeAnimation
 
 1.初始化CAAnimation对象
   + (instancetype)animation;
   + (instancetype)animationWithKeyPath:(nullable NSString *)path;
 2.设置动画的相关属性
 3.动画的添加和移除
 - (void)addAnimation:(CAAnimation *)anim forKey:(nullable NSString *)key;
 - (void)removeAnimationForKey:(NSString *)key;
 - (void)removeAllAnimations;
 ４、核心动画类的常用属性
 duration：动画的持续时间
 　　repeatCount        ：动画的重复次数
 　　timingFunction     ：动画的时间节奏控制
    fillMode           ：视图在非Active时的行为
 　　removedOnCompletion：动画执行完毕后是否从图层上移除，默认为YES（视图会恢复到动画前的状态），可设置为NO（图层保持动画执行后的状态，前提是fillMode设置为kCAFillModeForwards）
 　　beginTime          ：动画延迟执行时间（通过CACurrentMediaTime() + your time 设置）
 　　delegate           ：代理
             代理方法如下：
             - (void)animationDidStart:(CAAnimation *)anim;  //动画开始
             - (void)animationDidStop:(CAAnimation *)anim finished:(BOOL)flag; //动画结束
 
 */




//普通动画
- (IBAction)normalAnimation:(id)sender {

    CABasicAnimation * ani = [CABasicAnimation animationWithKeyPath:@"position"];
    ani.toValue = [NSValue valueWithCGPoint:self.centerShowView.center];
//    ani.removedOnCompletion = NO;
//    ani.fillMode = kCAFillModeForwards;
    ani.duration = 2.0;
    ani.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
    [self.cartCenterView.layer addAnimation:ani forKey:@"PostionAni"];
    
    
}

//spring动画
- (IBAction)springAnimation:(id)sender {
    
    CASpringAnimation * ani = [CASpringAnimation animationWithKeyPath:@"bounds"];
    ani.mass = 10.0; //质量，影响图层运动时的弹簧惯性，质量越大，弹簧拉伸和压缩的幅度越大
    ani.stiffness = 5000; //刚度系数(劲度系数/弹性系数)，刚度系数越大，形变产生的力就越大，运动越快
    ani.damping = 100.0;//阻尼系数，阻止弹簧伸缩的系数，阻尼系数越大，停止越快
    ani.initialVelocity = 5.f;//初始速率，动画视图的初始速度大小;速率为正数时，速度方向与运动方向一致，速率为负数时，速度方向与运动方向相反
    ani.duration = ani.settlingDuration;
    ani.toValue = [NSValue valueWithCGRect:self.centerShowView.bounds];
//    ani.removedOnCompletion = NO;
//    ani.fillMode = kCAFillModeForwards;
    ani.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
    [self.cartCenterView.layer addAnimation:ani forKey:@"boundsAni"];
    
}

//关键帧动画
- (IBAction)keyframeAnimation:(id)sender {

    CAKeyframeAnimation * ani = [CAKeyframeAnimation animationWithKeyPath:@"position"];
    ani.duration = 4.0;
//    ani.removedOnCompletion = NO;
//    ani.fillMode = kCAFillModeForwards;
    ani.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
    NSValue * value1 = [NSValue valueWithCGPoint:CGPointMake(150, 200)];
    NSValue *value2=[NSValue valueWithCGPoint:CGPointMake(250, 200)];
    NSValue *value3=[NSValue valueWithCGPoint:CGPointMake(250, 300)];
    NSValue *value4=[NSValue valueWithCGPoint:CGPointMake(150, 300)];
    NSValue *value5=[NSValue valueWithCGPoint:CGPointMake(150, 200)];
    ani.values = @[value1, value2, value3, value4, value5];
    [self.centerShowView.layer addAnimation:ani forKey:@"PostionKeyframeValueAni"];

    
}

//转场动画
- (IBAction)transformAnimation:(id)sender {
    
    /*
     CA_EXTERN NSString * const kCATransitionFade
     CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
     CA_EXTERN NSString * const kCATransitionMoveIn
     CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
     CA_EXTERN NSString * const kCATransitionPush
     CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
     CA_EXTERN NSString * const kCATransitionReveal
     CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
     
    CA_EXTERN NSString * const kCATransitionFromRight
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
    CA_EXTERN NSString * const kCATransitionFromLeft
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
    CA_EXTERN NSString * const kCATransitionFromTop
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
    CA_EXTERN NSString * const kCATransitionFromBottom
    CA_AVAILABLE_STARTING (10.5, 2.0, 9.0, 2.0);
     */
    
    
    CATransition * ani = [CATransition animation];
    ani.type = kCATransitionReveal;
    ani.subtype = kCATransitionFromLeft;
    ani.removedOnCompletion = YES;
    ani.duration = 1.5;
    self.centerShowView.backgroundColor = [UIColor blueColor];
//    self.centerShowView.image = [UIImage imageNamed:@"Raffle"];
    [self.centerShowView.layer addAnimation:ani forKey:@"transitionAni"];
    
}


- (IBAction)groupAnimation:(id)sender {
    
    CABasicAnimation * posAni = [CABasicAnimation animationWithKeyPath:@"position"];
    posAni.toValue = [NSValue valueWithCGPoint:self.centerShowView.center];
    
    CABasicAnimation * opcAni = [CABasicAnimation animationWithKeyPath:@"opacity"];
    opcAni.toValue = [NSNumber numberWithFloat:0.7];
    
    CABasicAnimation * bodAni = [CABasicAnimation animationWithKeyPath:@"bounds"];
    bodAni.toValue = [NSValue valueWithCGRect:self.centerShowView.bounds];
    
    CAAnimationGroup * groupAni = [CAAnimationGroup animation];
    groupAni.animations = @[posAni, opcAni, bodAni];
    groupAni.duration = 2.0;
//    groupAni.fillMode = kCAFillModeForwards;
//    groupAni.removedOnCompletion = NO;
    groupAni.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
    [self.cartCenterView.layer addAnimation:groupAni forKey:@"groupAni"];
    
}

@end
