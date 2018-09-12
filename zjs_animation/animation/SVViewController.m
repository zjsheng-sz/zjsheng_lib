//
//  SVViewController.m
//  zjs_animation
//
//  Created by autel on 2018/9/4.
//  Copyright © 2018年 autel. All rights reserved.
//

#import "SVViewController.h"
#import <SVProgressHUD.h>

NSString * const ZJSSVTestString = @"ZJSSVTestString";


@interface SVViewController ()

@end

@implementation SVViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
//    [SVProgressHUD setDefaultMaskType:SVProgressHUDMaskTypeBlack];
//    [SVProgressHUD setDefaultStyle:SVProgressHUDStyleDark];
//    [SVProgressHUD setRingThickness:6.0];
//    [SVProgressHUD setDefaultAnimationType:SVProgressHUDAnimationTypeNative];
//    [SVProgressHUD setGraceTimeInterval:5.0];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - action

- (IBAction)show:(id)sender {
    
    [SVProgressHUD show];

}

- (IBAction)showWithStatus:(id)sender {
    
    [SVProgressHUD showWithStatus:ZJSSVTestString];
}

- (IBAction)showProgress:(id)sender {
    
    [SVProgressHUD showProgress:0.5];
}

- (IBAction)showProgressWithStatus:(id)sender {
    [SVProgressHUD showProgress:0.5 status:ZJSSVTestString];
}

- (IBAction)showInfoWithStatus:(id)sender {
    
    [SVProgressHUD showInfoWithStatus:ZJSSVTestString];
}
- (IBAction)showSuccessWithStatus:(id)sender {
    
    [SVProgressHUD showSuccessWithStatus:ZJSSVTestString];
    
}
- (IBAction)showErrorWithStatus:(id)sender {
    
    [SVProgressHUD showErrorWithStatus:ZJSSVTestString];
    
}
- (IBAction)showImageWithStatus:(id)sender {
    
    
    [SVProgressHUD showImage:nil status:ZJSSVTestString];
    
}
- (IBAction)dismiss:(id)sender {
  
    [SVProgressHUD dismiss];
}


@end
