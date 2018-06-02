//
//  main.m
//  JSLeetCode_ObjectC
//
//  Created by autel on 2018/5/9.
//  Copyright © 2018年 autel. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Solution.h"


char* reverseWords(char* s);

int distributeCandies(int* candies, int candiesSize);

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        
        int a[] = {1000,1000,2,1,2,5,3,1};
        
        printf("%d",distributeCandies(a, 8));
        
    }
    return 0;
}



// Definition for a binary tree node.

struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
};

//struct TreeNode* trimBST(struct TreeNode* root, int L, int R) {
//
//
//}

