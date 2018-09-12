//
//  main.m
//  JSLeetCode_ObjectC
//
//  Created by autel on 2018/5/9.
//  Copyright © 2018年 autel. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Fibonacci.h"
#import "JewelsAndStones.h"
#import "UniqueMorseCodeWords.h"
#import "HammingDistance.h"
#import "RobotReturnToOrigin.h"
#import "NumberOfLinesToWriteString.h"


int main(int argc, const char * argv[]) {
    @autoreleasepool {
        

        
//        int a[10] = {45,48,24,24,57,87,118,21,54,54};
//        selectSort(a, 10);
//        bubbleSort(a, 10);
//        insertSort(a, 10);
//        shellSort(a, 10);
//        heapSort(a, 10);
//        mergeSort(a, 10);
//        quickSort(a, 10);
//
//
//        for (int i = 0; i < 10; i++) {
//            printf("%d,",a[i]);
//        }
//        printf("\n");
        
//        printf("k\n");
//        printf("%lld\n",fabonacciREC(1000000));
//        printf("%lld\n",fabonacci(1000000));
        
        test_numJewelsInStones();
        test_uniqueMorseRepresentations();
        test_hammingDistance();
        test_judgeCircle();
        test_numberOfLines();

    }
    return 0;
}




