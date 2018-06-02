//
//  Solution.m
//  JSLeetCode_ObjectC
//
//  Created by autel on 2018/5/9.
//  Copyright © 2018年 autel. All rights reserved.
//

#import "Solution.h"

@implementation Solution

- (NSInteger)uniqueMorseRepresentations:(NSArray *)words {
    
    NSArray *morses = @[@".-",@"-...",@"-.-.",@"-..",@".",@"..-.",@"--.",@"....",@"..",@".---",@"-.-",@".-..",@"--",@"-.",@"---",@".--.",@"--.-",@".-.",@"...",@"-",@"..-",@"...-",@".--",@"-..-",@"-.--",@"--.."];

    NSMutableArray *resultArr = [[NSMutableArray alloc] init];
    
    for (NSString *word in words) {
        
        NSMutableString *morseWord = [[NSMutableString alloc] init];
        
        for (int i = 0; i < word.length; i++) {
            
            char charactor = [word characterAtIndex:i];
            
            NSString *morsesStr = morses[charactor - 'a'];
            
            [morseWord appendString:morsesStr];
        }
        
        if (![resultArr containsObject:morseWord]) {
            [resultArr addObject:morseWord];;
        }

    }
    
    return  resultArr.count;
}

@end
