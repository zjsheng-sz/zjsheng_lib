//
//  Fibonacci.c
//  JSLeetCode_ObjectC
//
//  Created by autel on 2018/9/12.
//  Copyright © 2018年 autel. All rights reserved.
//

#include "Fibonacci.h"


long long fabonacciREC(int n){
    
    if (n == 1 || n == 2) {
        return 1;
    }
    
    return fabonacci(n - 1) + fabonacci(n - 2);
    
}


long long fabonacci(int n){
    
    if (n == 1 || n == 2) {
        return 1;
    }
    

    int pre = 1;
    int p = 1;
    
    
    
    for (int i = 3; i <= n; i ++) {
        
        int tmp = p;
        p = p + pre;
        pre = tmp;
        
    }
    
    return p;
}
