/*
 * RpcDefine.h
 *
 *  Created on: 2016-1-14
 *      Author: A15386
 */

#ifndef INCLUDE_MAXIDAS_RPCDEFINE_H_20160114_113832
#define INCLUDE_MAXIDAS_RPCDEFINE_H_20160114_113832


// 0-9999为车系自定义值，其中0-100为车系应用-公用段
enum RPC_ResultCode
{
	RPC_OK = 0,					/*没有错误*/
	RPC_PARAM_ERROR = 10000,	/*参数错误*/
	RPC_NET_ERROR,				/*网络错误*/
	RPC_AUTHORISE_FAILED,		/*验证失败*/
	RPC_DOWNLOAD_FAILED,		/*下载失败*/
	RPC_FUNCTION_NOT_SUPPORT,	/*不支持该功能*/
	RPC_MEMORY_ERROR,			/*内存错误*/
	RPC_LOAD_ALIB_FAILED,		/*A库文件加载打开失败*/
	RPC_LOAD_BLIB_FAILED,		/*A库文件加载打开失败*/
	RPC_GET_SERVER_FAILED,		/*获取服务器地址失败*/
	RPC_UNKNOWN,
	RPC_NETWORK_INVALID,		/* 网络无效（网线或者WiFi没有连接）*/
	// 服务管理-权限类
	RPC_PRODUCT_NOT_REGISTER = 11001,	/* 产品未注册 */
	RPC_AUTHORISE_NOT_PASS,				// 服务授权不通过
	RPC_AUTHORIZE_OUTOFDATA,			// 注册授权已过期
	RPC_SOFTVERSION_TOOLOW,				// 请求的产品软件版本太低
	RPC_NOT_BUY_SOFTKIT,				// 未购买请求的软件包
	// 服务管理-设备被异常使用类
	// 服务管理-获取第三方数据
	RPC_SERVICEID_DBCONNECT_ERROR = 11201,	// 服务ID数据库链接错误
	RPC_SERVICEID_INNER_ERROR,				// 服务ID内部错误
	RPC_CALL_PLATFORM_INTERFACE_ERROR,		// 调用服务平台接口失败
	RPC_CALL_COMM_PROTOCOL_ERROR,			// 调用服务通信协议错误
	RPC_PRODUCTDATA_CHECK_ERROR,			// 产品数据校验错误
	RPC_INPUT_PARAM_ERROR,					// 输入参数错误
	RPC_PRODUCT_DBCONNECT_ERROR,			// 产品数据库链接错误
	RPC_PRODUCT_CHECK_INNER_ERROR,			// 产品校验内部错误
};


//功能调用信息
#pragma pack(push, 1)
typedef struct _FuncInfo
{
	int nFuncID;			//功能ID
	int nSubFuncID;			//子功能ID，如不存在则为-1
	int nDataLen;			//参数长度
	unsigned char* pData;	//参数
}RPCFuncInfo;

//调用结果信息,nNeedDownload == 1,即需要下载，则pData字段给出下载地址列表由“\0”隔开,最后以”\0\0”结尾，其他情况data字段结构由车系自定义
typedef struct _ResultInfo
{
	int nFuncID;			//功能ID
	int nSubFuncID;			//子功能ID，如不存在则为-1
	int nErrorCode;			//错误码，取值与DLLServer返回值一致
	int nNeedDownload;		//是否需要：0 不需要，1需要
	char szSoName[32];		//本地执行so名称，若是远程调用则不需要
	int nDataLen;			//结果长度
	unsigned char* pData;	//结果
}RPCResultInfo;
#pragma pack(pop)

#endif /* INCLUDE_MAXIDAS_RPCDEFINE_H_20160114_113832 */
