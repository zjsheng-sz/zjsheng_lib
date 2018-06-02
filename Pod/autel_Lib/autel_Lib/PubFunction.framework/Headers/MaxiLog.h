#pragma once
////////////////////////////////////////////////////////////////////////////////
//文件名  : MaxiLog.h
//创建者  : 梁培鹏
//功能描述: 跨平台的日志打印 提供基础的与封装的打印函数，提供C方式的。现在先提供安卓版本的日志，以后会将该函数替换这些宏
//
//更新履历: 2017-4-7 10:55 梁培鹏 新建
//
////////////////////////////////////////////////////////////////////////////////

#include "MaxiPlatform.h"

// 控制台打印标记 
#define MAXILOG_TAG     "DEFAULT"

#ifdef TARGET_CXX
#include <string>
using namespace std;
namespace MAXI_LOG
{}
extern "C"{
#endif

    //日志级别
    typedef enum _enum_MAXI_LOG_
    {
        MAXILOG_INFO = 0,          //信息
        MAXILOG_WARN = 1,          //警告
        MAXILOG_ERROR = 2,          //错误
        MAXILOG_FATAL = 3,          //致命
    }emMAXI_LOGTYPE;



    //新的日志打印宏
    #define PRINI(...)  MaxiPrint(MAXILOG_INFO, MAXILOG_TAG, __VA_ARGS__)
    #define PRINW(...)  MaxiPrint(MAXILOG_WARN, MAXILOG_TAG, __VA_ARGS__)
    #define PRINE(...)  MaxiPrint(MAXILOG_ERROR, MAXILOG_TAG, __VA_ARGS__)

    #define PRINT_T(TAG, ...)  MaxiPrint(MAXILOG_INFO, TAG, __VA_ARGS__)
    #define PRINT_T(TAG, ...)  MaxiPrint(MAXILOG_INFO, TAG, __VA_ARGS__)
    #define PRINT_T(TAG, ...)  MaxiPrint(MAXILOG_INFO, TAG, __VA_ARGS__)


    //对以前旧的LOGI进行重定义 兼容旧的
    #define LOGI    PRINI
    #define LOGW    PRINW
    #define LOGE    PRINE
    #define JNITRACE(tag, msg)  PRINTTRACE_T(tag, msg) 
    #define ATRACE(tag, msg)    PRINTTRACE_T(tag, msg) 

    #define ALOGI    PRINI
    #define ALOGW    PRINW
    #define ALOGE    PRINE


    // 是否打印日志 由于NDK下C 是没有bool，所以使用int。输入值只管 0 与 非0
    void __MYEXPORT__ EnableLogMessage(int control);



    //功能:     打印日志 最基础的函数 直接可调用
    //参数:     @nLevel    emMAXI_LOGTYPE 的值
    //          @pszTag    标记头
    //          @pszMsg    日志内容
    //返回值:   该函数会在内部自动记录时间与线程id
    //注意:     如果调用该函数，从第三个参数开始，必须严格像printf一样
    __MYEXPORT__ void MaxiPrint(int nLevel, const char * pszTag, const char * fmt, ...);


#ifdef TARGET_CXX
    };

    #define PRINTTRACE(msg)  CPrintTrace trace((MAXILOG_TAG), (msg));
    #define PRINTTRACE_T(tag, msg)  CPrintTrace trace((tag), (msg));

    //用于函数开始与结束时自动打印的类 在函数开始时创建一个类对象即可
    //尽量不要直接使用 使用上面的宏定义  PRINTTRACE 与 PRINTTRACE_T
    class __MYEXPORT__ CPrintTrace
    {
    public:
        CPrintTrace(const string & pszTag, const string & pszMsg);
        ~CPrintTrace();

    private:
        string  m_pszTag;
        string  m_pszMsg;
    };
#endif