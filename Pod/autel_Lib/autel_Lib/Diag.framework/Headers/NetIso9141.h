#ifndef NETISO9141_H_HEADER_INCLUDED_B968DB53
#define NETISO9141_H_HEADER_INCLUDED_B968DB53
#include "NegativeResponse.h"
#include "NetLayerBase.h"

  
/******************************************************************************

    Copyright (c) 2007, AUTEL Ltd,.Co

    All rights reserved.

    文件名称：NetIso9141.h NetIso9141.cpp

    档 标 识：

    摘    要：本类是所有实现ISO-9141网络层的功能

    用    法：1、声明初始化：   
                 CNetIso9141 NetIso9141;
                 NetIso9141.Init();
              2、完成具体通信：
                 NetIso9141.SendReceive(...);
              3、不再使用，最后消毁
                 NetIso9141.Destroy();

    历史记录：
    ---------------------------------------------------------------------------
     时     间   作者    版本号   操    作    内    容
    ---------------------------------------------------------------------------
     2007.7.13   王长喜  1.0      创建此类
     2007.7.14   王长喜  1.0      编写实现代码
     2007.10.17  王长喜  1.0      加入NewSelf()
     2007.10.24  王长喜  1.0      修改时间参数及相关代码, 并在摸拟平台上调试通过

*******************************************************************************/
class CNetIso9141 : public CNetLayerBase
{
  public: 

    /*-----------------------------------------------------------------------------
      功    能：完成初始化功能，进入系统
      参    数：W_U8 uAddressCode -- 进入系统的地址码, 缺省值为0x33
                CSendFrame SendFrame -- 发送帧，缺省值为CSendFrame(CBinary("\x68\x6A\xF1\x01\x00\xC4",6),1)
      返 回 值：接收帧内容
      说    明：执行是否成功通过CErrorCode类查询
    -----------------------------------------------------------------------------*/
    virtual CReceiveFrame Init(W_U8 uAddressCode, CSendFrame SendFrame=CSendFrame(CBinary("\x68\x6A\xF1\x01\x00\xC4", 6), CSendFrame::SF_AUTO_DISTINGUISH) );
    virtual CReceiveFrame Init();
    using CNetLayerBase::Init;
    
  	virtual CNetLayerBase* NewSelf();
	W_ErrorCode KeepLink(W_I16 iKeepTime, CSendFrame KeepLinkFrame);
	CBinary SendReceive(CBinary binSend);
	CReceiveFrame SendReceive(CSendFrame sfSend);
	CMultiReceiveFrame SendReceive(CMultiSendFrame msfSend);

	void SetShowNegativeResponseWaitMessageBox(bool bIsShow);
    /*-----------------------------------------------------------------------------
      功    能：退出系统
      参    数：无
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    void Destroy();

    CNetIso9141();
    virtual ~CNetIso9141();

protected:
	CNegativeResponse nrNegResponse;
};



#endif /* NETISO9141_H_HEADER_INCLUDED_B968DB53 */
