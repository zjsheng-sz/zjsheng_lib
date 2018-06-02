#pragma once
#ifndef TPMSInterface_H_20170331_084922
#define TPMSInterface_H_20170331_084922
#include "Binary.h"
#include <unistd.h>
#include <string>
#include "MultiSendFrame.h"
#include "MultiReceiveFrame.h"
#include "ReceiveFrame.h"
#include "SendFrame.h"



typedef pthread_mutex_t CRITICAL_SECTION;
#define InitializeCriticalSection(lock) pthread_mutex_init(lock, NULL);
#define EnterCriticalSection(lock) pthread_mutex_lock(lock);
#define LeaveCriticalSection(lock) pthread_mutex_unlock(lock);
#define DeleteCriticalSection(lock) pthread_mutex_destroy(lock);


 class	CTPMSInterface
 {
 public:
	 
	 static CTPMSInterface* GetInstance();
	 /*-----------------------------------------------------------------------------
	 功    能：析构函数
	 参数说明：无
	 返 回 值：无
	 说    明：判断new TTYS指针是否存为NULL，不是的话销毁new TTYS同时将指针设为NULL
	 -----------------------------------------------------------------------------*/
	 virtual ~CTPMSInterface();
	 /*-----------------------------------------------------------------------------
	 功    能：打开COM口，并设置COM口参数和端口状态
	 参数说明：无
	 返 回 值：成功返回TRUE,失败返回FALSE
	 说    明：无
	 -----------------------------------------------------------------------------*/
	 bool Init();
	 /*-----------------------------------------------------------------------------
	 功    能：关闭串口
	 参数说明：无
	 返 回 值：无
	 说    明：销毁 new TTYS同时将指针设为NULL.
	 -----------------------------------------------------------------------------*/
	 void Destroy();
	 /*-----------------------------------------------------------------------------
	 功    能：设置串口参数
	 参数说明：
				nBaudRate: 波特率(2400、4800、9600、921600(默认))
				nBits:数据位(7、8(默认))
				nEvent:奇偶校验位('O'、'N'(默认)、'E');
				nStop:停止位(1(默认)、2)
				nFlow_Ctrl:数据流控制
	 返 回 值：无
	 说    明：初始化已经设置参数，这里是更改串口参数
	 -----------------------------------------------------------------------------*/
	 bool SetUart(int nBaudRate=921600, int nBits=8, char nEvent='N', int nStop=1,int nFlow_Ctrl=0);

	 /*-----------------------------------------------------------------------------
	 功    能：接受和发送数据
	 参数说明：
				binSendCmd:发送的命令
	 返 回 值：返回的数据
	 说    明：无
	 -----------------------------------------------------------------------------*/
	 CBinary SendReceive(CBinary &binSendCmd);

	  /*-----------------------------------------------------------------------------
	 功    能：发送数据
	 参数说明：
				binSendCmd:发送的命令
	 返 回 值：返回的数据
	 说    明：无
	 -----------------------------------------------------------------------------*/
	 bool Send(CBinary &binSendCmd);
	  /*-----------------------------------------------------------------------------
	 功    能：接受数据
	 参数说明：无		
	 返 回 值：接收的命令
	 说    明：无
	 -----------------------------------------------------------------------------*/
	 CBinary Receive();
	 /*-----------------------------------------------------------------------------
	 功    能：设置读超时时间
	 参数说明：
				TimeOutSec：没有接收到字节数但是时间到即返回(单位 s)
				TimeOutUsec：没有接收到字节数但是时间到即返回(单位 us)
	 返 回 值：无
	 说    明：
	 -----------------------------------------------------------------------------*/
	 void SetCommTime(int TimeOutSec,int TimeOutUsec);
 	 /*-----------------------------------------------------------------------------
	 功    能：获取超时时间
	 参数说明：
				TimeOutSec：没有接收到字节数但是时间到即返回(单位 s)
				TimeOutUsec：没有接收到字节数但是时间到即返回(单位 us)
	 返 回 值：无
	 说    明：
	 -----------------------------------------------------------------------------*/
	 void GetCommTime(int &TimeOutSec,int &TimeOutUsec);
	 /*-----------------------------------------------------------------------------
	 * 名称：    Get_BautRate 
	 * 功能：    获取波特率 
	 * 入口参数：无
	 * 出口参数：当前波特率 
	 -----------------------------------------------------------------------------*/
	 int Get_BautRate(void);
 protected:

 private:
	 CRITICAL_SECTION CriticalLock;
	 CTPMSInterface();
	 char const* strComName;	//串口地址名称
	 bool IsOpen;		//是否成功打开
 };

#endif