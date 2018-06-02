#ifndef __ADS_STD_H__
#define __ADS_STD_H__

#include "MaxiPlatform.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

//日志库头文件  兼容以前的用法
#include "MaxiLog.h"
using namespace MAXI_LOG;




/******************************************************************************

    Copyright (c) 2007, AUTEL Ltd,.Co

    All rights reserved.

    文件名称：adsStd.h

    档 标 识：《RD070011--MaxScan详细设计说明书--诊断架构与ECU通信分册》 V1.0AX

    摘    要：诊断程序全局定义

    用    途：1、实现诊断程序与平台无关性；
              2、定制裁剪诊断程序

    附加说明：诊断程序员不得修改本文件代码，如需要扩充通知框架维护程序员改进。

    历史记录：
    ---------------------------------------------------------------------------
     时     间    作者    版本号      操    作    内    容
    ---------------------------------------------------------------------------
     2007.6.25    王长喜  1.0         创建此类。

****************************************************************************/
//wangyihua 2012-08-29 use for android start
#ifndef USE_IDE_VC
#define USE_IDE_VC
#endif
//wangyihua 2012-08-29 use for android end
// define system
#ifdef ADS_ALL_SYSTEM
    #define ADS_BASE_SYSTEM
    #define ADS_EXTEND_SYSTEM
#endif //ADS_ALL_SYSTEM

#ifdef ADS_BASE_SYSTEM
    #define ADS_ENG_SYSTEM
    #define ADS_AT_SYSTEM
    #define ADS_ABS_SYSTEM
    #define ADS_SRS_SYSTEM
#endif //ADS_BASE_SYSTEM

#ifdef ADS_EXTEND_SYSTEM
    // other system define
#endif //ADS_EXTEND_SYSTEM



// define function
#ifdef ALL_FUNCTION
    #define ADS_BASE_FUNCTION
    #define ADS_EXTEND_FUNCTION
#endif //ALL_FUNCTION

#ifdef ADS_BASE_FUNCTION
    #define ADS_READ_INFORMATION
    #define ADS_READ_TROUBLE_CODE
    #define ADS_CLEAR_TROUBLE_CODE
    #define ADS_READ_DATA_STREAM
#endif //BASE_FUNCTION

#ifdef ADS_EXTEND_FUNCTION
    //#define ADS_OTHER_FUNCTION define
#endif //ADS_EXTEND_FUNCTION

// config
// config IDE
//#define USE_IDE_VC
//#define USE_IDE_EMBEST
//#define USE_IDE_IAR_WBARM

#ifdef USE_IDE_EMBEST
#  undef USE_IDE_VC
#endif // USE_IDE_EMBEST

#ifdef USE_IDE_IAR_WBARM
#  undef USE_IDE_EMBEST
#  undef USE_IDE_VC
#endif // USE_IDE_IAR_WBARM

typedef unsigned long COLORREF;
#ifndef RGB
#define RGB(r,g,b)          ((COLORREF)(((unsigned char)(r)|((unsigned short int)((unsigned char)(g))<<8))|(((unsigned long)(unsigned char)(b))<<16)))
#endif

// other public define
#define W_U8_MAX_VAL                 0xFF       // W_U8所能表示的最大值
#define W_U16_MAX_VAL                0xFFFF     // W_U32所能表示的最大值
#define W_U32_MAX_VAL                0xFFFFFFFF // W_U32所能表示的最大值

// typedef
//#define W_I8                         signed char
//#define W_I16                        short
//#define W_I32                        int
//#define W_U8                         unsigned char
//#define W_U16                        unsigned short
//#define W_U32                        unsigned int
//#define ULONG						 unsigned long
//#define UCHAR						 unsigned char
//#define UBOOL						 bool

typedef signed char W_I8;                         
typedef short W_I16;                        
typedef int W_I32;                        
typedef unsigned char W_U8;                         
typedef unsigned short W_U16;                       
typedef unsigned int W_U32;                        
typedef unsigned long ULONG;						 
typedef unsigned char UCHAR;					 
typedef  bool UBOOL;					

typedef char const* LPCTSTR;

#ifdef USE_IDE_VC
    #define W_FLOAT                  double
#else
    #define W_FLOAT                  float
#endif

#define W_ErrorCode                  W_I16

#define W_VU8                        volatile W_U8
#define W_VU16                       volatile W_U16
#define W_VU32                       volatile W_U32

#define BYTE                         W_U8
#define W_INT                        int


#define INCLUDE_ALL_LINK_PROTOCOL

//    #define INCLUDE_LINK_ISO
//    #define INCLUDE_LINK_KWP
//    #define INCLUDE_LINK_PWM
//    #define INCLUDE_LINK_VPW
//    #define INCLUDE_LINK_CAN

#ifdef INCLUDE_ALL_LINK_PROTOCOL
    #define INCLUDE_LINK_ISO
    #define INCLUDE_LINK_KWP
    #define INCLUDE_LINK_NORMAL
    #define INCLUDE_LINK_BOSCH
    #define INCLUDE_LINK_CCD
    #define INCLUDE_LINK_CAN
    #define INCLUDE_LINK_TP20
    #define INCLUDE_LINK_PWM
    #define INCLUDE_LINK_VPW
    #define INCLUDE_LINK_NISSAN_OLD
    #define INCLUDE_LINK_VOLVO_CAN
#endif


// 点位置变量
struct W_POINT
{
    W_U16    uX;
    W_U16    uY;
	W_POINT():uX(0), uY(0){}
	W_POINT(W_U16 x, W_U16 y):uX(x), uY(y){}
};


struct W_RECT
{
   W_U16 left;
   W_U16 top;
   W_U16 right;
   W_U16 bottom;
   W_RECT():left(0), top(0),right(0),bottom(0){}
   W_RECT(W_U16 l, W_U16 t, W_U16 r, W_U16 b):left(l), top(t), right(r), bottom(b){}
   void SetRect(W_U16 l, W_U16 t, W_U16 w, W_U16 h){left = l, top = t, bottom = top + h, right = left + w;}
} ;


struct W_SIZE
{
    W_I16 cx;
    W_I16 cy;
	W_SIZE():cx(0), cy(0){}
	W_SIZE(W_I16 x, W_I16 y):cx(x), cy(y){}
} ;



// 显示程序使用

// 系统总共有九个按键，分别定义如下，用于返回按键识别
#define KEY_PRESS_UP            0x01
#define KEY_PRESS_DOWN          0x02
#define KEY_PRESS_LEFT          0x03
#define KEY_PRESS_RIGHT         0x04

#define KEY_PRESS_F1            0x05
#define KEY_PRESS_F2            0x06
#define KEY_PRESS_F3            0x07
#define KEY_PRESS_HELP          0x08



#define SCREEN_WIDTH            128         // 0-127
#define SCREEN_HEIGHT           63          // 0-63

//#define FULL_SCREEN_SHOW_TITLE


#define SCROLL_WIDTH            4

#define FONT_NORMAL             0
#define FONT_BIG                1
#define ASIA_NORMAL             2

#define BK_WHITE__TEXT_BLACK    0
#define BK_BLACK__TEXT_WHITE    1
#define TEXT_RECT__BK_BLACK     2


#define DRAW_MODE_TEXT          0
#define DRAW_MODE_HELP          1
#define DRAW_MODE_GRAPHICS      3

#ifndef DT_CENTER
    #define DT_LEFT             0x00000000
    #define DT_CENTER           0x00000001
    #define DT_RIGHT            0x00000002
#endif

#ifndef NULL
    #define NULL                         0
#endif

#define MAX(a,b)                     ((a)>(b)?(a):(b))
#define MIN(a,b)                     ((a)<(b)?(a):(b))
#define ABS(a)                       (((a)>0)?(a):(-(a)))

#define MAKE_UINT16(high, low)       (((high)<<8)|(low))

#include <vector>
#ifdef USE_IDE_VC
    using namespace std;
#endif

#ifdef USE_IDE_VC
    #define __RAMFUNC
    #define __ARM
    #define EXT_C_IT               // extern "C"
#else
    #ifdef OS_PROGRAM
        #define __RAMFUNC           __ramfunc
        #define __ARM               __arm
        #define EXT_C_IT
    #else
        #define __RAMFUNC           __ramfunc
        #define __ARM               __arm
        #define EXT_C_IT            extern "C"
    #endif
#endif

//#ifdef USE_IDE_VC
//#define assert(_Expression)     ((void)0)
//#define ASSERT(s)  assert(s)
//#endif

#ifdef DAS_HOST_PROG
#define MAXI_DAS_PROG
#endif
#ifdef INT_COMM_APP_PROG
#define MAXI_DAS_PROG
#endif
#ifdef INT_COMM_SVR_PROG
#define MAXI_DAS_PROG
#endif

#ifdef USE_IDE_VC
#define FUNC_OUTPUT     //TRACE
#else
#define FUNC_OUTPUT     printf
#define _T(x)           x
#endif

/*-----------------------------------------------------------------------------
  功    能：单步自检报告回调函数类型
  参    数：Param1      unsigned short      单步自检的错误代码
            Param2      int                 有错误码 非0，无错误码 0
            Param3      int                 当前已经测到的错误码数量
  返 回 值：是否退出(非零退出)
  说    明：无
-----------------------------------------------------------------------------*/
typedef int (*PCALLBACK_STEP_CHECK_REPORT)(unsigned short, int, int);

/*-----------------------------------------------------------------------------
  功    能：是否继续等待回调函数类型
  参    数：是否有指定错误码
  返 回 值：是否继续等待
  说    明：无
-----------------------------------------------------------------------------*/
typedef int (*PCALLBACK_IF_CONTINUE_WAIT)(bool);

#define BMW_CAN_ECU_TOOL_ADDRESS                    // wcx add 9/1/2008



// 2013-03-05 add by pxx
#define KEY_PRESS_UP			0x01
#define KEY_PRESS_DOWN			0x02
#define KEY_PRESS_LEFT			0x03
#define KEY_PRESS_RIGHT			0x04

#define KEY_PRESS_F1			0x05
#define KEY_PRESS_F2			0x06
#define KEY_PRESS_F3			0x07
#define KEY_PRESS_HELP		    0x08
#define KEY_ENTER               0x09
#define KEY_ESC                 0x0A

#define LPCTSTR  char*
#define _T(x)		x
#define MAXISYS
//#define toupper	Toupper
//#define toupper	Tolower


#endif //__ADS_STD_H__
