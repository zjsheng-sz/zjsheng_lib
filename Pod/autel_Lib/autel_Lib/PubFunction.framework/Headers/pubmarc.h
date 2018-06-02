#pragma once
//#include <jni.h>
//#include <android/log.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


const int RT_Back					=(-1);
const int RT_OK						=(1);
const int RT_Cancel					=(-1);

#define DF_Save     1000
#define DF_Print      1001


typedef unsigned long COLORREF;
#ifndef RGB
#define RGB(r,g,b)          ((COLORREF)(((unsigned char)(r)|((unsigned short int)((unsigned char)(g))<<8))|(((unsigned long)(unsigned char)(b))<<16)))
#endif


#define BackColor RGB(0, 0, 0)
#define WhiteColor RGB(255, 255, 255)

#define RedColor RGB(255, 0, 0)
#define GreenColor RGB(0, 255, 0)
#define BlueColor RGB(0, 0, 255)

#define YellowColor RGB(255, 0, 255)
#define YellowColor2 RGB(255, 255, 0)
#define YellowColor3 RGB(0, 255, 255)

#define GrayColor RGB(192, 192, 192)


#define DS_STD  0
#define DS_VW   1



const unsigned int IDBase = 100;
const unsigned int IDMax = 1000;

#define __MYEXPORT__   __attribute__ ((visibility("default")))

#define assert(_Expression)     ((void)0)
#define ASSERT(_Expression) assert(_Expression)

typedef unsigned int UINT;
#define W_ErrorCode                  W_I16

#define W_VU8                        volatile W_U8
#define W_VU16                       volatile W_U16
#define W_VU32                       volatile W_U32

#define BYTE                         W_U8
#define W_INT                        int

typedef signed char W_I8;                         
typedef short W_I16;                        
typedef int W_I32;                        
typedef unsigned char W_U8;                         
typedef unsigned short W_U16;                       
typedef unsigned int W_U32;                        
typedef unsigned long ULONG;						 
typedef unsigned char UCHAR;					 
typedef  bool UBOOL;
// #include "JniPublic.h"
//using namespace JniPublic;