//
//  RobotReturnToOrigin.c
//  JSLeetCode_ObjectC
//
//  Created by autel on 2018/9/12.
//  Copyright © 2018年 autel. All rights reserved.
//

#include "RobotReturnToOrigin.h"


void test_judgeCircle(void){
    
    char *moves = "UD";
    
    printf("judgeCircle:%d\n",judgeCircle(moves));
}


int judgeCircle(char* moves){
    
    int countL = 0;
    int countU = 0;
    
    char *p  = moves;
    
    while (*p != '\0') {
        
        switch (*p ++) {
            case 'L':
                countL ++;
                break;
            case 'R':
                countL --;
                break;
            case 'U':
                countU ++;
                break;
            case 'D':
                countU --;
                break;
                
            default:
                break;
        }
        
        
    }
    
    if (countL == 0 && countU == 0) {
        return 1;
    }
    
    return 0;
}
