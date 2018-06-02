#ifndef __AUTEL_PROTOL_XML_BASE__H__
#define __AUTEL_PROTOL_XML_BASE__H__

#ifdef _WIN32

#define __TARGET_PLAT_WIN__

#else

#define __TARGET_PLAT_LINUX__

#endif

#if defined(__TARGET_PLAT_LINUX__)

#include <unistd.h>
#define AUTEL_PROTOL_XML_API
#define _snprintf snprintf

#elif defined( __TARGET_PLAT_WIN__)
#define AUTEL_PROTOL_XML_API __declspec(dllexport)

#endif


#define AUTEL_LIB
#define  __AUTEL_IN
#define  __AUTEL_OUT
#define  __AUTEL_IN_OUT
#define __AUTEL_CONST


// PluginBllMgr 业务分发调度插件
#define  USER_MESSAGE                                                                   0x00000100
#define PLUGIN_MESSAGE_BLLMGR                                                           USER_MESSAGE + 10                                                        // PluginBllMgr 业务分发调度插件
#define PLUGIN_MESSAGE_MASK_BASE_BLLMGR                                                 0x90000000  
#define PLUGIN_MESSAGE_MASK_BASE_BLLMGR_CHECK_VALID_DATE                                PLUGIN_MESSAGE_MASK_BASE_BLLMGR + 2	

#endif