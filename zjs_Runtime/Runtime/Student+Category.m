//
//  Student+Category.m
//  Runtime
//
//  Created by autel on 2018/1/10.
//  Copyright © 2018年 zhongjiasheng. All rights reserved.
//

#import "Student+Category.h"
#import <objc/runtime.h>

@implementation StudentModel (Category)

static const char *name;

- (NSString *)firstName{
    
    
    return objc_getAssociatedObject(self, &name);
}

- (void)setFirstName:(NSString *)firstName{
    
 objc_setAssociatedObject(self, &name, firstName, OBJC_ASSOCIATION_COPY_NONATOMIC);
    
}

@end

