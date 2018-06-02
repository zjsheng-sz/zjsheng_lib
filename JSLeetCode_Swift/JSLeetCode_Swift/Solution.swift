//
//  Solution.swift
//  JSLeetCode_Swift
//
//  Created by autel on 2018/5/9.
//  Copyright © 2018年 autel. All rights reserved.
//

import Cocoa

class Solution: NSObject {
    
    
    func flipAndInvertImage(_  A: [[Int]]) -> [[Int]] {
        
        var B = [[Int]]()
        
        for  i in 0..<A.count {
            
            for j in 0 ..< A[i].count{
                
                
                B[i][j] = A[i][A[j].count - 1 - j]
                B[i][A[j].count - 1 - j] = A[i][j]
                B[i][j] = 1 - B[i][j]

            }
        }
        
        
        return A;
    }
    
    func uniqueMorseRepresentations(_ words: [String]) -> Int {
        
        let morses = [".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]

        var resultArrresultArr = Array<String>()
        
        for word:String in words {
            
            var morseWord = ""
            
            for character:Character in word {
                
                let a:Character = "a"
                
                let morse = morses[character.toInt() - a.toInt()]
                
                morseWord += morse
            }
            
            if resultArrresultArr.contains(morseWord) == false {
                
                resultArrresultArr.append(morseWord)
            }
            
        }
        
        print(resultArrresultArr)
        
        return resultArrresultArr.count
    }

}


extension Character{
    func toInt() -> Int {
        var intFromCharacter:Int = 0
        
        for scalar in String(self).unicodeScalars {
            intFromCharacter = Int(scalar.value)
            
        }
        return intFromCharacter
        
    }
    
}
