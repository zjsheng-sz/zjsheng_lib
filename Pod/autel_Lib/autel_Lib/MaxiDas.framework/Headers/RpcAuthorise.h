/*
 * RpcAuthorise.h
 *
 *  Created on: 2016-1-14
 *      Author: A15386
 */

#ifndef MAXIDAS_JNI_C___RPC_RPCAUTHORISE_H_20160114_114023
#define MAXIDAS_JNI_C___RPC_RPCAUTHORISE_H_20160114_114023

#include <string>
#include <map>
#include "RpcDefine.h"
#include "public.h"
using namespace std;


class __MYEXPORT__ CRpcAuthorise
{
public:
	CRpcAuthorise();
	virtual ~CRpcAuthorise();

public:
	// 是否显示错误提示框，默认显示。应该最先调用它
	void ShowMessageBox(bool bShow = true);

	// 设置IM盒子SN，机器码，防盗专用。其他车系不得调用，RpcCallStart之前调用
	void SetIMInfo(const string& strBoxSn, const string& strBoxCode);


	/* 功  能：RPC调用
	 * @funcInfo: 输入参数, RPCFuncInfo结构体对象。
	 * @pResultInfo:  输出参数，RPCResultInfo结构体对象指针，不能为空。由模块内部对其进行赋值
	 * 返回值：0 成功，1~9999 参照DLLServer的返回值，10000后面的是本模块返回
	 * 说  明：该函数可以多次调用，RpcCallEnd只需调用一次就行了。
	*/
	int RpcCallStart(const RPCFuncInfo& funcInfo, RPCResultInfo* pResultInfo, void *env = NULL);

	//结束RPC调用，会释放资源并清除下载的文件
	void RpcCallEnd(void);

	

private:
	//基础信息
	typedef struct _BaseInfo
	{
		unsigned char szSN[24];					//机器SN
		unsigned char szPassword[8];			//机器注册码
		unsigned char szOSVersion[32];			//OS版本
		unsigned char szMaxiVersion[32];		//管理程序版本
		unsigned char szCarVersion[32];			//车系版本
	}RPCBaseInfo;

	typedef struct _BaseInfo_IM 
	{
		RPCBaseInfo BaseData;
		unsigned char strBoxSN[16];		//盒子SN
		unsigned char strBoxCode[24];	//盒子机器码
	}RPCBaseInfo_IM;

private:
	// 发送认证请求，组包成xml格式发送过去，接收过来的也是xml格式。  0成功,其他失败
	int AuthoriseCheck(void *env = NULL);

	// 认证成功后，发送功能调用(baseInfo + funcInfo)
	int RemoteFunctionCall(const RPCBaseInfo& baseInfo, const RPCFuncInfo& funcInfo, RPCResultInfo* pResultInfo, void *env = NULL);

	// 填充baseInfo结构体
	void FillBaseInfo(RPCBaseInfo& baseInfo, void *env = NULL);

	// 加载libA.so，pParam为NULL，则不调用初始化接口，不为空，则调用初始化接口
	bool LoadALib(const string& strLibAName, void* pParam = NULL, void *env = NULL);

	// 加载libB.so
	bool LoadBLib(const string& strLibBName, const RPCFuncInfo& funcInfo, RPCResultInfo* pResultInfo);


private:
	const string m_strTempPath;
	const string m_strLibAName;

	static unsigned char* m_pTempData;

	vector<string> m_vctDownloadFiles;		// 记录下载的文件
	map<int, string> m_mapFuncIdSoName;		// FuncId与szSoName的映射
	bool m_bIsTest;

};


#endif /* MAXIDAS_JNI_C___RPC_RPCAUTHORISE_H_20160114_114023 */
