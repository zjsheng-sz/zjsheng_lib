//
//  UniqueMorseCodeWords.c
//  JSLeetCode_ObjectC
//
//  Created by autel on 2018/9/12.
//  Copyright © 2018年 autel. All rights reserved.
//

#include "UniqueMorseCodeWords.h"
#include <stdlib.h>
#include <string.h>


#define MaxWordLength 12
#define MaxMorseLenghth 4

void test_uniqueMorseRepresentations(void){
    
    char *a[] = {"trmj","cgo","nyj","cqm","cgo","nyj","nyj","kpo","cqm","cgo","kpo","kwj",\
        "cmatt","cmj","nyj","kpo","kwj","cgo","ntpo","nnqm","kwj","cqm","kpo","cmj",\
        "kpo","kpo","ctkm","cmj","kpo","coir","kwbn","nkgf","kamef","kjsn","kagf",\
        "mmexf","ocaer","ocrr","mquf","okuf","zkmtc","zymke","dvmnie","nhmgei","nhoth",\
        "cgji","cgji","okuf","mmexf","mquf","ocaer","ocrr","fbmo","ftsom","fithve","ffiif",
        "imzez","uosz","uosz","imzez","hyxip","hkzbg","hyxip","hkzbg","aejwo","aumwo","reoemo",\
        "zeldg","zfrp","girenp","pthf","eqhf","acsf","pbef","atlhn","pbef","pbef","wlif","kjaetd",\
        "nycz","kjaez","pbtoi","acutz","akvtz","pfj","wefj","adrj","anfj","wvum","pfj","abxm","pfj",
        "wsnj","pido","pfj","pfj","ezrj","puio","wsnj","pfj"};
    
    printf("uniqueMorseRepresentations:%d\n",uniqueMorseRepresentations(a, 100));
    
}

int uniqueMorseRepresentations(char** words, int wordsSize){
    
    char *morses[] = {".-","-...","-.-.","-..",".","..-.","--.","....",\
        "..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.",\
        "...","-","..-","...-",".--","-..-","-.--","--.."};
    
    char *resultArr[100];
    
    int resultCount = 0;
    
    for (int i = 0; i < wordsSize; i ++) {
    
        char *word = words[i];
        
        char *p = word;
        
        char *result = (char *)malloc(MaxMorseLenghth * MaxWordLength * sizeof(char));
        
        memset(result, 0, MaxMorseLenghth * MaxWordLength);
        
        while (*p != '\0') {
            
            char *morse = morses[*p - 'a'];
            
            strcat(result,morse);
            
            p++;
            
        }
        
        int isInArr = 0;
        
        for (int j = 0; j < resultCount; j++) {
            
            char *tmp = resultArr[j];
        
            
            if (strcmp(tmp, result) == 0) {
                
                isInArr = 1;
                
                break;
            }
        }
        
        if (isInArr == 0) {
            resultArr[resultCount ++] = result;
        }
        
    }
    
    return resultCount;
    
}

