#pragma once
class DataLogging{
public:
	/*-------------------------------------------------------
	功    能：开始记录														
	参数说明：strAddInfo 需要追加的信息，如果已经开始记录，相对AddInfo，否则相当于先开始记录，再调用AddInfo
				strTitle DataLogging的标题，只有第一次开启时有效，否则将被忽略
				strReason DataLogging的成因，只有第一次开启时有效，否则将被忽略
				pReserve 保留后续扩展使用，NULL表示所有模块公用一个DataLogging；非空时，每调用一次stop则产生一个DataLogging
	返 回 值：成功返回true，否则返回false
	说    明：诊断程序开始在Stop之前多次调用该函数，但只有第一次调用该函数时才开启记录，标题和原因才有效，否则将忽略标题和原因，
				相当于调用AddInfo(strAddInfo)
	-------------------------------------------------------*/
	static bool Start(string const& strAddInfo, string const& strTitle = string(), string const& strReason = string(), void* pReserve = NULL);

	/*-------------------------------------------------------
	功    能：追加信息到DataLogging														
	参数说明：strAddInfo 需要追加的信息
				pReserve 保留后续扩展使用，目前必须为NULL
	返 回 值：成功返回true，否则返回false
	说    明：如果已经开始记录，则直接将文本追加到DataLoging文件中，此时返回true，否则忽略调用，返回false
	-------------------------------------------------------*/
	static bool AddInfo(string const& strAddInfo, void* pReserve = NULL);

	/*-------------------------------------------------------
	功    能：停止记录														
	参数说明：pReserve 保留后续扩展使用，目前必须为NULL
	返 回 值：成功返回true，否则返回false
	说    明：停止记录后，后台会静默发送DataLogging到服务器
	-------------------------------------------------------*/
	static bool Stop(void* pReserve = NULL);

	/************************************************************************/
	/* 功  能： 关闭用户日志  add  [2017/03/31 A15386]
	/* 参  数： pReserve 保留后续扩展使用，目前必须为NULL
	/* 返回值： 成功返回true，否则返回false
	/* 说  明： 该接口真正的关闭日志，并写入到文件中.
	/************************************************************************/
	static bool StopUserLog(void* pReserve = NULL);

	/*-------------------------------------------------------
	功    能：设置循环队列大小														
	说    明：不设置，默认为2000
	-------------------------------------------------------*/
	static void SetQueueSize(unsigned int Size);
	
	/*-------------------------------------------------------
	功    能：设置日志文件大小														
	说    明：无
	-------------------------------------------------------*/
	static void SetDataLoggingFileMaxLen(unsigned long size);
	
	/*-------------------------------------------------------
	功    能：使能或禁止数据入队														
	说    明：为true是暂停。为false时数据继续入队
	-------------------------------------------------------*/
	static void Pause(bool state);
	/*-------------------------------------------------------
	功    能：设置标题											
	说    明：2014-3-3 Add
	-------------------------------------------------------*/
	static void SetDataLogTitle(string const& strTitle);
	/*-------------------------------------------------------
	功    能：设置原因											
	说    明：2014-3-3 Add
	-------------------------------------------------------*/
	static void SetDataLogReason(string const& strReason);
	
};