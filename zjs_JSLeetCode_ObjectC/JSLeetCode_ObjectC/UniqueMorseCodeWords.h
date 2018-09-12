//
//  UniqueMorseCodeWords.h
//  JSLeetCode_ObjectC
//
//  Created by autel on 2018/9/12.
//  Copyright © 2018年 autel. All rights reserved.
//

/*
 International Morse Code defines a standard encoding where each letter is mapped to a series of dots and dashes, as follows: "a" maps to ".-", "b" maps to "-...", "c" maps to "-.-.", and so on.
 
 For convenience, the full table for the 26 letters of the English alphabet is given below:
 
 [".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]
 Now, given a list of words, each word can be written as a concatenation of the Morse code of each letter. For example, "cab" can be written as "-.-.-....-", (which is the concatenation "-.-." + "-..." + ".-"). We'll call such a concatenation, the transformation of a word.
 
 Return the number of different transformations among all words we have.
 
 Example:
 Input: words = ["gin", "zen", "gig", "msg"]
 Output: 2
 Explanation:
 The transformation of each word is:
 "gin" -> "--...-."
 "zen" -> "--...-."
 "gig" -> "--...--."
 "msg" -> "--...--."
 
 There are 2 different transformations, "--...-." and "--...--.".
 */

#ifndef UniqueMorseCodeWords_h
#define UniqueMorseCodeWords_h

#include <stdio.h>

int uniqueMorseRepresentations(char** words, int wordsSize);

void test_uniqueMorseRepresentations(void);

#endif /* UniqueMorseCodeWords_h */
