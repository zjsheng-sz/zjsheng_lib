//
//  Fibonacci.h
//  JSLeetCode_ObjectC
//
//  Created by autel on 2018/9/12.
//  Copyright © 2018年 autel. All rights reserved.
//

/*
 转换：尾部递归可以很方便的转换成一个简单循环，完成相同的任务
 
 缺点：最常见的一个问题就是深度递归会造成堆栈溢出的错误
 
 优点：递归的程序实现看上去要比非递归的实现简捷得多
 
 避免：重复调用
*/

#ifndef Fibonacci_h
#define Fibonacci_h

#include <stdio.h>

long long fabonacci(int n);
long long fabonacciREC(int n);

#endif /* Fibonacci_h */
