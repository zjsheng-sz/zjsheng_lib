//
//  Solution.swift
//  JSLeetCode_Swift
//
//  Created by autel on 2018/5/9.
//  Copyright © 2018年 autel. All rights reserved.
//

import Cocoa


/*
 1234
 5123
 9512
 */


//-2,-1,0,1,2,3


class Solution: NSObject {
    
    
    func nextGreaterElement(_ findNums: [Int], _ nums: [Int]) -> [Int] {

        var resultArr = [Int]()

        
        
        for i in 0..<findNums.count {

            var tmp = -1;
            
            if i < nums.count {
                
                for j in i..<nums.count{
                
                    var isInFindNums = false
                    for k in 0...i {
                        if findNums[k] == nums[j] { isInFindNums = true}
                    }
                
                    if nums[j] > findNums[i] && !isInFindNums {tmp = nums[j]; break}
                }
            }
            
            

            resultArr.append(tmp)
        }

        return resultArr;
    }
    
//    func nextGreaterElement(_ findNums: [Int], _ nums: [Int]) -> [Int] {
//        var dict = [Int: Int]()
//        var stack = [Int]()
//        nums.forEach {
//            while (!stack.isEmpty && stack.last ?? 0 < $0) {
//                dict[stack.popLast() ?? 0] = $0
//            }
//            stack.append($0)
//        }
//        return findNums.map { dict[$0] ?? -1 }
//    }
    
}

