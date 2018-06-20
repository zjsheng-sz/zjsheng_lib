//
//  main.m
//  JSLeetCode_ObjectC
//
//  Created by autel on 2018/5/9.
//  Copyright © 2018年 autel. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Solution.h"
void selectSort(int A[], int N);
void bubbleSort(int A[], int N);

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        
        int a[10] = {45,48,24,24,57,87,118,21,54,54};
        
//        selectSort(a, 10);
        bubbleSort(a, 10);
        
        for (int i = 0; i < 10; i++) {
            printf("%d,",a[i]);
        }
        
    }
    return 0;
}

//插入排序

//冒泡排序
void bubbleSort(int A[], int N){
 
    for (int i = 0; i < N - 1; i++) {

        for (int j = 0; j < N - i - 1; j++) {
        
            if (A[j] > A[j+1]) {
                
                int tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
            }
        }
    }
}

//选择排序
void selectSort(int A[], int N){
    
    for (int i = 0; i < N - 1; i++) {
        
        for (int j = i; j < N; j++) {
            
            if (A[i] > A[j]) {
                int tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
            
        }
    }
}


