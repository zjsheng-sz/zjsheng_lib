// NetJ1850Vpw.h: interface for the CNetJ1850Vpw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETJ1850VPW_H__1AB8BA56_5278_4151_8E19_2B222F2DF088__INCLUDED_)
#define AFX_NETJ1850VPW_H__1AB8BA56_5278_4151_8E19_2B222F2DF088__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetLayerBase.h"
#include "NegativeResponse.h"	// Added by ClassView

/******************************************************************************

    Copyright (c) 2007, AUTEL Ltd,.Co

    All rights reserved.

    文件名称：NetIso9141.h NetIso9141.cpp

    档 标 识：

    摘    要：本类是所有实现ISO-9141网络层的功能

    用    法：1、声明初始化：   
                 CNetJ1850Vpw NetJ1850Vpw;
                 NetJ1850Vpw.Init();
              2、完成具体通信：
                 NetJ1850Vpw.SendReceive(...);
              3、不再使用，最后消毁
                 NetJ1850Vpw.Destroy();

    历史记录：
    ---------------------------------------------------------------------------
     时     间   作者    版本号   操    作    内    容
    ---------------------------------------------------------------------------
     2007.10.11   纪安荣  1.0      创建此类
     2007.10.11   纪安荣  1.0      编写实现代码

*******************************************************************************/

class CNetJ1850Vpw : public CNetLayerBase  
{
public:
	CNetJ1850Vpw();
	virtual ~CNetJ1850Vpw();
	virtual CNetLayerBase* NewSelf();


	/*-----------------------------------------------------------------------------
      功    能：完成初始化功能，进入系统
      参    数：CSendFrame SendFrame -- 发送帧，缺省值为CSendFrame(CBinary("\x68\x6A\xF1\x01\x00\x17",6),1)
      返 回 值：接收帧内容
      说    明：执行是否成功通过CErrorCode类查询
    -----------------------------------------------------------------------------*/
    using CNetLayerBase::Init;
	virtual CReceiveFrame Init();
	virtual CReceiveFrame Init(CSendFrame SendFrame);
	W_ErrorCode KeepLink(W_I16 iKeepTime, CSendFrame KeepLinkFrame);
	/*-----------------------------------------------------------------------------
      功    能：退出系统
      参    数：无
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    void Destroy();
protected:
	CNegativeResponse nrNegResponse;

};

#endif // !defined(AFX_NETJ1850VPW_H__1AB8BA56_5278_4151_8E19_2B222F2DF088__INCLUDED_)
