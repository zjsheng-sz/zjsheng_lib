#pragma once
////////////////////////////////////////////////////////////////////////////////
//文件名  : PlatformHead.h
//创建者  : 梁培鹏
//功能描述: 跨平台的头文件，用于定义平台宏，其它模块的都包含本头文件
//
//更新履历: 2017-4-7 10:44 梁培鹏 新建
//
////////////////////////////////////////////////////////////////////////////////


#define SYS_PLATFORM_WIN	    0x1         //WINDOWS
#define SYS_PLATFORM_APPLE		0x2         //APPLE
#define SYS_PLATFORM_ANDROID    0x4         //ANDROID
#define SYS_PLATFORM_LINUX      0x8         //LINUX

//系统平台版本的定义
#ifdef _WIN32
	//WINDOW
	#define AUTEL_SYS_WINDOWS
    #define TARGET_PLAT_WINDOWS
    #define SYS_PLATFORM        SYS_PLATFORM_WIN
    #define __MYEXPORT__    
#elif __APPLE__
	//APPLE
	#define AUTEL_SYS_APPLE
    #define TARGET_PLAT_APPLE
    #define SYS_PLATFORM        SYS_PLATFORM_APPLE
    #define __MYEXPORT__    
#else
	#define AUTEL_SYS_ANDROID
    #define TARGET_PLAT_ANDROID
    #define SYS_PLATFORM        SYS_PLATFORM_ANDROID
    #define __MYEXPORT__   __attribute__ ((visibility("default")))
#endif

#ifdef __cplusplus
    //C++
    #define TARGET_CXX
#else
    //C
    #define TARGET_C
#endif

#ifdef AUTEL_SYS_WINDOWS	 // windows
	#include <windows.h>
	#include <io.h>
	#include <direct.h>
//	#include <WinSock2.h>
	#pragma comment(lib, "Ws2_32.lib")
#else						 // linux
	#include <pthread.h>
	#include <unistd.h>
	#include <dirent.h>
	#include <net/if.h>
	#include <sys/ioctl.h>
	#include <arpa/inet.h>
	#include <netdb.h>
    #include <sys/stat.h>
#endif

#ifdef AUTEL_SYS_ANDROID	 // Android
	#include <android/log.h>
#endif
