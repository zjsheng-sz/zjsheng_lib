//
//  NumberOfLinesToWriteString.c
//  JSLeetCode_ObjectC
//
//  Created by autel on 2018/9/12.
//  Copyright © 2018年 autel. All rights reserved.
//

#include "NumberOfLinesToWriteString.h"
#include <stdlib.h>


void test_numberOfLines(void){

    int widths[26] = {4,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
    
    char *s = "abcdefghijk";
    
    int returnSize = 0;
    
    int *array = numberOfLines(widths, 26, s, &returnSize);
    
    printf("numberOfLines:%d,%d\n",array[0],array[1]);

}


int* numberOfLines(int* widths, int widthsSize, char* S, int* returnSize){
    
    char *p = S;
    
    int lineNumbers = 1;
    int lineWordNum = 0;
    
    while (*p != '\0') {
        
        int tmpNum = widths[*p - 'a'];
    
        if (lineWordNum + tmpNum <= 100) {
            lineWordNum += tmpNum;
            
        }else{
            
            lineWordNum = tmpNum;
            lineNumbers ++;
            
        }
        
        p ++;
    }
    
    int *res = (int *)malloc(sizeof(int) * 2);
    
    res[0] = lineNumbers;
    res[1] = lineWordNum;
    
    return res;
    
}
