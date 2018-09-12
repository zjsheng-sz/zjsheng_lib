//
//  Sort.h
//  JSLeetCode_ObjectC
//
//  Created by autel on 2018/9/12.
//  Copyright © 2018年 autel. All rights reserved.
//

//思想是最重要的

#ifndef Sort_h
#define Sort_h

#include <stdio.h>
#include <stdlib.h>

void selectSort(int A[], int N); //选择排序
void bubbleSort(int A[], int N); //冒泡排序
void insertSort(int A[], int N); //插入排序
void shellSort(int A[], int N);  //希尔排序
void heapSort(int A[], int N);   //堆排序
void mergeSort(int A[], int N);  //归并排序
void quickSort(int A[], int N);  //快速排序

#endif /* Sort_h */
