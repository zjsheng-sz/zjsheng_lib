//
//  HammingDistance.c
//  JSLeetCode_ObjectC
//
//  Created by autel on 2018/9/12.
//  Copyright © 2018年 autel. All rights reserved.
//

#include "HammingDistance.h"

void test_hammingDistance(void){
    
    printf("hammingDistance:%d\n",hammingDistance(1, 4));
    
}

//1.取异或。  2.循环>>, 比较个位是否为1

int hammingDistance(int x, int y){
    
    int resultCount = 0;
    
    int tmp = x ^ y;
    
    while (tmp != 0) {
        
        if ((tmp & 1) == 1) {
            resultCount ++;
        }
        
        tmp = tmp >> 1;

    }
    
    return resultCount;
}
