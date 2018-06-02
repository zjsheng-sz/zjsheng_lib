/**********************************************************************\
 * rdc_client_interface.h
 *
 *  Created on: 2013-7-17
 *      Author: WANG YAN SHUN
 *   Copyright: Autel
 * Description: 
 *
 ***********************************************************************/

#ifndef __RDC_CLIENT_INTERFACE_H__
#define __RDC_CLIENT_INTERFACE_H__

#include "autel_client_base.h"

#if defined(__TARGET_PLAT_LINUX__)

#include <unistd.h>
#define AUTEL_CLIENT_TCP_API
#elif defined( __TARGET_PLAT_WIN__)
#define AUTEL_CLIENT_TCP_API __declspec(dllexport)
#endif


extern "C"{

	/**
	* @brief  组件的业务类型
	* @return 返回代表业务类型的编码
	*/
	AUTEL_CLIENT_TCP_API unsigned int ModuleType();

	/**
	* @brief  组件的实现版本
	* @return 返回版本号
	*/
	AUTEL_CLIENT_TCP_API unsigned int ModuleVersion();



	/**
	* @brief  初始化组件
	* @param [in]  ipAddress           网络通信地址
	* @param [in]  port                网络通信端口
	* @return      >=0：               socketId
	*              < 0:                失败
	*/
	AUTEL_CLIENT_TCP_API long Init(__AUTEL_IN const char* ipAddress, __AUTEL_IN unsigned short port);


	/**
	* @brief 以异步的方式处理数据，如果该数据处理失败 系统会将数据返回给应用层
	* @param[in] service     服务码
	* @param[in] serviceMask 服务掩码
	* @param[in] ptrData     需要被处理的数据.
	* return         ==0：   发送成功
	*                ==-1：  发送失败
	*/
	AUTEL_CLIENT_TCP_API int Send(long socketId, unsigned int service, unsigned int serviceMask, __AUTEL_IN char* ptrData, __AUTEL_IN unsigned int dataLength );
	AUTEL_CLIENT_TCP_API int SendEx(long socketId, unsigned int service, unsigned int serviceMask, __AUTEL_IN char* ptrData, __AUTEL_IN unsigned int dataLength, unsigned int from, unsigned int to, unsigned int id);

	/**
	* @brief  接收网络数据
	* @param[out] ptrData    输出参数 需要通过 ReleaseData 释放资源
	* @param[out] dataLength 输出参数 数据段的长度
	* @return  == 0:操作成功
	*          == -1:操作失败
	*/
	AUTEL_CLIENT_TCP_API int Receive(long socketId, unsigned int* service, unsigned int* serviceMask, char** ptrData, unsigned int& dataLength);
	AUTEL_CLIENT_TCP_API int ReceiveEx(long socketId, unsigned int* service, unsigned int* serviceMask,unsigned int * from, unsigned * to, char** ptrData, unsigned int& dataLength, unsigned int& id);

	/**
	* @brief 释放内部申请的资源
	*/
	AUTEL_CLIENT_TCP_API void ReleaseData(char**ptrData);

	/**
	* @brief  用于清理停止组件内部业务并回收资源
	*/
	AUTEL_CLIENT_TCP_API void UnInit( long socketId );
}

#endif /* __RDC_CLIENT_INTERFACE_H__ */
