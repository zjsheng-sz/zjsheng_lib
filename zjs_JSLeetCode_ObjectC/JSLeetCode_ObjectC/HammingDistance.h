//
//  HammingDistance.h
//  JSLeetCode_ObjectC
//
//  Created by autel on 2018/9/12.
//  Copyright © 2018年 autel. All rights reserved.
//

/*
 
 https://leetcode.com/problems/hamming-distance/description/
 
 https://www.cnblogs.com/911/archive/2008/05/20/1203477.html 位运算符的使用
 
 The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
 
 Given two integers x and y, calculate the Hamming distance.
 
 Note:
 0 ≤ x, y < 231.
 
 Example:
 
 Input: x = 1, y = 4
 
 Output: 2
 
 Explanation:
 1   (0 0 0 1)
 4   (0 1 0 0)
        ↑   ↑
 
 The above arrows point to positions where the corresponding bits are different.
 */

#ifndef HammingDistance_h
#define HammingDistance_h

#include <stdio.h>

void test_hammingDistance(void);
int hammingDistance(int x, int y);

#endif /* HammingDistance_h */
