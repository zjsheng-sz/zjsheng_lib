/**********************************************************************\
 * rdc_client_base.h
 *
 *  Created on: 2013-7-17
 *      Author: WANG YAN SHUN
 *   Copyright: Autel
 * Description: 用于定义远程诊断客户端基础数据类型
 *
 ***********************************************************************/

#ifdef _WIN32

#define __TARGET_PLAT_WIN__

#else

#define __TARGET_PLAT_LINUX__

#endif

#ifndef __RDC_CLIENT_BASE_H__
#define __RDC_CLIENT_BASE_H__

#define __AUTEL_IN
#define __AUTEL_OUT
#define __AUTEL_IN_OUT

// 网络模块
#define  USER_MESSAGE                                                                   0x00000100
#define  PLUGIN_MESSAGE_NET                                                             USER_MESSAGE + 1
#define  PLUGIN_MESSAGE_MASK_BASE_NET                                                   0x00000000
#define  PLUGIN_MESSAGE_MASK_KEEP_ALIVE_NET                                             PLUGIN_MESSAGE_MASK_BASE_NET + 3


#endif /* __RDC_CLIENT_BASE_H__ */
