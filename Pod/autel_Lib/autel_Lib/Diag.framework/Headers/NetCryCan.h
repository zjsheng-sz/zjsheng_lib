// NetCryCan.h: interface for the CNetCryCan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NetCryCan_H__95653791_926C_42AB_BC95_460D6377A361__INCLUDED_)
#define AFX_NetCryCan_H__95653791_926C_42AB_BC95_460D6377A361__INCLUDED_

#include "Binary.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetLayerBase.h"
#include "ReceiveFrame.h"		// Added by ClassView
//#include "LinkBaseCan.h"		// Added by ClassView
#include "NegativeResponse.h"	// Added by ClassView
/******************************************************************************

    Copyright (c) 2007, AUTEL Ltd,.Co

    All rights reserved.

    文件名称：NetCryCan.h NetCryCan.cpp

    档 标 识：

    摘    要：本类是所有实现ISO-9141网络层的功能

    用    法：1、声明初始化：   
                 CNetCryCan NetCryCan;
                 NetCryCan.Init();
              2、完成具体通信：
                 NetCryCan.SendReceive(...);
              3、不再使用，最后消毁
                 NetCryCan.Destroy();

    历史记录：
    ---------------------------------------------------------------------------
     时     间   作者    版本号   操    作    内    容
    ---------------------------------------------------------------------------

*******************************************************************************/

class CNetCryCan : public CNetLayerBase  
{
	
public:
 	virtual CNetLayerBase* NewSelf();

    using CNetLayerBase::Init;
    using CNetLayerBase::SendReceive;
	/*-----------------------------------------------------------------------------
      功    能：完成初始化功能，进入系统
      参    数：CSendFrame SendFrame -- 发送帧，缺省值为CSendFrame(CBinary("\x07\xdf\x08\x02\x01\x00\xff\xff\xff\xff\xff",11))
      返 回 值：接收帧内容
      说    明：执行是否成功通过CErrorCode类查询
    -----------------------------------------------------------------------------*/	
	virtual CReceiveFrame Init();
	/*-----------------------------------------------------------------------------
      功    能：完成初始化功能，进入系统
      参    数：CSendFrame SendFrame -- 发送帧，
				SendFrame进入帧格式：11位CAN CBinary("\x07\xdf\x08\x02\x01\x00\xff\xff\xff\xff\xff",11)
				29位CAN CBinary("\x18\xDB\x33\xF1\x08\x02\x01\x00\xff\xff\xff\xff\xff",13)实际命令格式
				29位CAN CBinary("\x98\xDB\x33\xF1\x08\x02\x01\x00\xff\xff\xff\xff\xff",13)发送命令格式 将0x18 || 0x80得到。
				命令字后为填充字节，NetCryCan取命令字后第一个字节，如果无填充字节，则不需填加
				命令字长度为7，如果后续帧有填充字节，则在帧最后加填充字节。目前MAXSCAN支持的填充字仅有两种：
				0x00||0xFF,其它填充字不支持
      返 回 值：接收帧内容
      说    明：执行是否成功通过CErrorCode类查询
    -----------------------------------------------------------------------------*/
	virtual CReceiveFrame Init(CSendFrame SendFrame);
	/*-----------------------------------------------------------------------------
    功    能：发一帧收一帧或多帧
    参数说明：CSendFrame sfSend – 发送给ECU命令
    返 回 值：ECU回复的一帧数据
    说    明：无
    -----------------------------------------------------------------------------*/	
	virtual CReceiveFrame SendReceive(CSendFrame sfSend);
	/*-----------------------------------------------------------------------------
    功    能：发一帧收一帧
    参数说明：CSendFrame sfSend – 发送给ECU命令
    返 回 值：ECU回复的一帧数据
    说    明：无
    -----------------------------------------------------------------------------*/	
	virtual CBinary SendReceive(CBinary binSend);
   /*-----------------------------------------------------------------------------
    功    能：设置链路保持
    参数说明：W_I16 iKeepTime  链路保持时间
			  CSendFrame KeepLinkFrame 链路保持命令
    返 回 值：
    说    明：执行是否成功通过CErrorCode类查询
    -----------------------------------------------------------------------------*/
	virtual W_ErrorCode KeepLink(W_I16 iKeepTime, CSendFrame KeepLinkFrame);
	/*-----------------------------------------------------------------------------
      功    能：退出系统
      参    数：无
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    void Destroy();
	CNetCryCan();
	virtual ~CNetCryCan();
	CPackUnpack* GetPackObj()
	{
		return &m_PackUnpack;
	}
protected:
	CNegativeResponse nrNegResponse;
};

#endif // !defined(AFX_NetCryCan_H__95653791_926C_42AB_BC95_460D6377A361__INCLUDED_)
