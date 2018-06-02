#ifndef NETLAYERBASE_H_HEADER_INCLUDED_B97C9B4E
#define NETLAYERBASE_H_HEADER_INCLUDED_B97C9B4E
#include "Binary.h"
#include "CheckSum.h"
#include "MultiReceiveFrame.h"
#include "MultiSendFrame.h"
#include "PackUnpack.h"
#include "ReceiveFrame.h"
#include "IncorporateReceiveFrame.h"
#include "EcuInterface.h"

/******************************************************************************

    Copyright (c) 2007, AUTEL Ltd,.Co

    All rights reserved.

    文件名称：NetLayerBase.h NetLayerBase.cpp

    档 标 识：

    摘    要：本类是所有实现网络层的基类，并实现共性的、最常用的功能

    用途：


    历史记录：
    ---------------------------------------------------------------------------
     时     间   作者    版本号   操    作    内    容
    ---------------------------------------------------------------------------
     2007.7.13   王长喜  1.0      创建此类。
     2007.8.23   李 宏            增加SetCommTime
     2007.12.17  班洪立           增加 SetEcuId 和2个 SetToolId
     2008.3.18   班洪立           为Tp20协议网络层，在CNetLayerBase里增加函数
                                  CReceiveFrame Init(W_U8 ucTpTargetAddress, W_U8 ucAppLayerID)
     2008.9.17   王长喜           加入7F 78否定回答最大次数，缺省-1即无限个
                                  SetReceiveNegativeResponseMaxNumber();
     2008.9.17   王长喜           加入设置属性相关函数
                                   virtual W_ErrorCode SetProperty(W_U32 uProperty);
                                   virtual W_U32 GetProperty();
	 2008.11.1   王长喜  1.0      修改SendIncorporateReceive(CSendFrame SendFrame)
	                              加入出错处理
	 2008.11.3   王长喜  1.0      修改GetProtocolType()函数，加入出错重试代码
	 2008.11.3   王长喜  1.0      修改SetFilterOrFrameDistinguish，加入出错处理
	
     
*******************************************************************************/
class CNetLayerBase
{
  public:
  	
    /*-----------------------------------------------------------------------------
      功    能：设置属性
      参    数：uProperty
      返 回 值：错误代码
      说    明：属性值按BIT设置，每个BIT一个含义
    -----------------------------------------------------------------------------*/
 	  virtual W_ErrorCode SetProperty(W_U32 uProperty);
 	  virtual W_U32 GetProperty();
 	  
    /*-----------------------------------------------------------------------------
      功    能：设置接收否定回答的最大次数
      参    数：最大次数
      返 回 值：无
      说    明：如果设定值小于等于0，则为无限次
    -----------------------------------------------------------------------------*/
    virtual void SetReceiveNegativeResponseMaxNumber(W_I32 iTimes =-1);
	/*-----------------------------------------------------------------------------
      功    能：设置是否显示等待界面
      参    数：true -- 显示， false -- 不显示
      返 回 值：无
      说    明：默认值为显示.
    -----------------------------------------------------------------------------*/
	virtual void SetShowNegativeResponseWaitMessageBox(bool bIsShow = true);
	/*-----------------------------------------------------------------------------
      功    能：设置是否存在否定响应
      参    数：true -- 显示， false -- 不显示
      返 回 值：无
      说    明：默认值为显示.
    -----------------------------------------------------------------------------*/
	virtual void SetNegativeResponse(bool bIsShow = true);
    /*-----------------------------------------------------------------------------
      功    能：产生自身的一个新实例
      参    数：无
      返 回 值：网络层指针
      说    明：所有派生类中必须重载本函数
    -----------------------------------------------------------------------------*/
    virtual CNetLayerBase * NewSelf() = 0;

    /*-----------------------------------------------------------------------------
      功    能：取得链路层协议类型
      参    数：无
      返 回 值：链路层协议类型
      说    明：无
    -----------------------------------------------------------------------------*/
    W_U16 GetProtocolId();

    /*-----------------------------------------------------------------------------
      功    能：是否解包从ECU接收数据
      参    数：bool bIsUnpack -- 解包为true，不解包为false
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    virtual void EnableUnpack(bool bIsUnpack=true);

    /*-----------------------------------------------------------------------------
      功    能：是否打包发给ECU数据
      参    数：bool bIsPack -- 打包为true，不打包为false
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    virtual void EnablePack(bool bIsPack=true);

    /*-----------------------------------------------------------------------------
      功    能：完成初始化功能，进入系统
      参    数：W_I16 iInitMode -- 在存大多种进入系统方式时，确定进入系统方式
      返 回 值：错误代码
      说    明：1、设置通信协议类型；
                2、设置接收过滤条件或帧识别数据；
                3、设置ECU通信时间参数；
                4、设置帧打包/解包格式；
                5、设置校验和计算方式；
                6、进入系统，返回成功否；
    -----------------------------------------------------------------------------*/
//    virtual CReceiveFrame Init(W_I16 iInitMode = 0);
    virtual CReceiveFrame Init();
    virtual CReceiveFrame Init(W_U8 ucTpTargetAddress, W_U8 ucAppLayerID);
    virtual CReceiveFrame Init(W_U8 uAddressCode, CSendFrame SendFrame=CSendFrame(CBinary("",0),0));
    virtual CReceiveFrame Init(W_I16 iWaitTime, W_I16 iLowTime, W_I16 iHighTime, CSendFrame SendFrame);
    virtual CReceiveFrame Init(CSendFrame SendFrame); //lhadd_2007_10_12

    /*-----------------------------------------------------------------------------
      功    能：退出系统
      参    数：无
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    virtual void Destroy();

    /*-----------------------------------------------------------------------------
      功    能：设置模式，根据协议的不同而定
      参    数：W_I16 iMode -- 模式字
      返 回 值：错误代码
      说    明：当协议存在多种处理方式或打包方式时间使用，其参数程序员根据协议具体
                要求自行定义
    -----------------------------------------------------------------------------*/
    virtual W_ErrorCode SetMode(W_I16 iMode);

    /*-----------------------------------------------------------------------------
      功    能：接收一帧数据
      参    数：无
      返 回 值：ECU回复的一帧数据
      说    明：在ECU回无数据帧时使用
    -----------------------------------------------------------------------------*/
    virtual CBinary Receive();

    /*-----------------------------------------------------------------------------
    功    能：发一帧收一帧
    参数说明：CBinary binSendCmd – 发送给ECU命令
    返 回 值：ECU回复的一帧数据
    说    明：无
    -----------------------------------------------------------------------------*/
    virtual CBinary SendReceive(CBinary binSend);

    /*-----------------------------------------------------------------------------
    功    能：发一帧收一帧或多帧（0帧）
    参数说明：CSendFrame SendFrame – 发送帧
    返 回 值：接收帧
    说    明：无
    -----------------------------------------------------------------------------*/
    virtual CReceiveFrame SendReceive(CSendFrame SendFrame);

    /*-----------------------------------------------------------------------------
    功    能：发多帧收多帧
    参数说明：CSendFrame SendFrame – 发送帧
    返 回 值：多接收帧
    说    明：无
    -----------------------------------------------------------------------------*/
    virtual CMultiReceiveFrame SendReceive(CMultiSendFrame SendFrame);

    /*-----------------------------------------------------------------------------
    功    能：发一帧收一帧或多帧（0帧）
    参数说明：CSendFrame SendFrame – 发送帧
    返 回 值：接收帧
    说    明：无
    -----------------------------------------------------------------------------*/
    virtual CIncorporateReceiveFrame SendIncorporateReceive(CSendFrame SendFrame);

    /*-----------------------------------------------------------------------------
      功    能：设置/取消链路保持
      参数说明：W_INT16 iKeepTime – 链路保持时间间隔
                CSendFrame KeepLinkFrame -- 链路保持帧，缺省为CSendFrame ()
      返 回 值：错误代码
      说    明：如链路保持时间为0，或发送帧内容为空白，则取消链路保持
    -----------------------------------------------------------------------------*/
    virtual W_ErrorCode KeepLink(W_I16 iKeepTime, CSendFrame KeepLinkFrame = CSendFrame());


    /*-----------------------------------------------------------------------------
    功    能：设置ECU通信时间参数
    参数说明：W_FLOAT fReceiveMaxByte2ByteInterval_P1 接收帧字节间最大间隔时间
              W_FLOAT fReceiveFrameMaxWaitTime_P2  -- 接收帧最大等待时间
              W_FLOAT fSendFrameInterval_P3 -- 发送帧时间间隔
              W_FLOAT fSendByte2Byte_P4 -- 发送帧字节间间隔
              W_FLOAT fReceivePacketOverTime -- 接收数据包超时时间;
    返 回 值：错误代码
    说    明：单位：毫秒
    -----------------------------------------------------------------------------*/
    virtual void SetCommTime (W_FLOAT fReceiveMaxByte2ByteInterval_P1,
                              W_FLOAT fReceiveFrameMaxWaitTime_P2,
                              W_FLOAT fSendFrameInterval_P3,
                              W_FLOAT fSendByte2Byte_P4,
                              W_FLOAT fReceivePacketOverTime);

    /*-----------------------------------------------------------------------------
      功    能：设置过滤条件
      参    数：FilterOrFrameDistinguish    过滤条件对象
      返 回 值：无
      说    明：
    -----------------------------------------------------------------------------*/
    virtual void SetFilterOrFrameDistinguish(CFilterOrFrameDistinguish FilterOrFrameDistinguish);

    /*-----------------------------------------------------------------------------
      功    能：设置ECU地址
      参数说明：uEcuId                      ECU地址
      返 回 值：无
      说    明：必须先设置打包模式，再设置设置ID
    -----------------------------------------------------------------------------*/
    virtual void SetEcuId(W_U8 uEcuId);

    /*-----------------------------------------------------------------------------
      功    能：设置设备地址
      参数说明：uToolId                     设备地址
                  CAN协议--11bit ID最高位为0，低11bit有效，其它位必须为0
                         --29bit ID最高位为1，低29bit有效，其它位必须为0
                  其它协议有效值0~255
      返 回 值：无
      说    明：必须先设置打包模式，再设置设置ID
    -----------------------------------------------------------------------------*/
    virtual W_ErrorCode SetToolId(W_U32 uToolId);

    /*-----------------------------------------------------------------------------
      功    能：设置设备地址
      参数说明：binToolId                   设备地址
                  CAN协议 -- 11bit ID长度为2字节
                          -- 29bit ID长度为4字节
                  其它协议--       ID长度为1字节
      返 回 值：无
      说    明：必须先设置打包模式，再设置设置ID
    -----------------------------------------------------------------------------*/
    virtual W_ErrorCode SetToolId(CBinary binToolId);
	

	/*-----------------------------------------------------------------------------
      功    能：取得最后一次设置的目标地址
      参数说明：无
      返 回 值：最后一次设置的EcuID
      说    明：无
    -----------------------------------------------------------------------------*/
	virtual W_U8 GetEcuId(void);

	void StartMonitor(map<unsigned long, CMonitorPara> CMonitorParameter,unsigned int MonitorCycle);
	void StartMonitor(map<unsigned long, CMonitorPara> CMonitorParameter);
	void StartMonitor(void);
	unsigned long GetMonitorDataSize(void);
	CReceiveFrame GetMonitorData(void);
	bool StopMonitor(void);

    CNetLayerBase();
    virtual ~CNetLayerBase();

  public:
    typedef struct tagTimePara
    {
        W_FLOAT m_fReceiveMaxByte2ByteInterval_P1;
        W_FLOAT m_fReceiveFrameMaxWaitTime_P2;
        W_FLOAT m_fSendFrameInterval_P3;
        W_FLOAT m_fSendByte2Byte_P4;
        W_FLOAT m_fReceivePacketOverTime;
    } TimePara;

    virtual CNetLayerBase::TimePara* GetCommTimePointer ();

	CEcuInterface m_EcuInterface;
  protected:
    bool m_bSendPack;
    bool m_bReceiveUnpack;
    // 打包/解包类
    CPackUnpack m_PackUnpack;
    // ECU通信接口
    //CEcuInterface m_EcuInterface;
    // 过滤条件
    CFilterOrFrameDistinguish m_FilterOrFrameDistinguish;

    TimePara m_TimePara;

	// wcx add 9/17/2008
    W_I32 m_iNegativeResponseTimes;
    W_U32 m_u32Property;
    // wcx add end 
    // jar add 19/01/2008
    bool m_bNegativeResponse;
	W_U8 m_uEcuID;
};



#endif /* NETLAYERBASE_H_HEADER_INCLUDED_B97C9B4E */
