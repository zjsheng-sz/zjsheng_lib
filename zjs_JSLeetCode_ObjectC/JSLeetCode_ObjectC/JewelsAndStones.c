//
//  JewelsAndStones.c
//  JSLeetCode_ObjectC
//
//  Created by autel on 2018/9/12.
//  Copyright © 2018年 autel. All rights reserved.
//

#include "JewelsAndStones.h"
#include <string.h>

void test_numJewelsInStones(void){
    
    char *J = "aA";
    char *S = "aAAbbbb";
    
    printf("numJewelsInStones:%d\n",numJewelsInStones(J, S));
    
    
}

int numJewelsInStones(char* J, char* S){
    
    
    char *ps = S;
    char *pj = J;
    int count = 0;
    
    while (*ps != '\0') {
        
        pj = J;
        
        while (*pj != '\0') {
            
            if (*pj == *ps) {
                
                count ++;
            }
            
            pj ++;
        }
        
        ps ++;
    }

    return count;
    
}
