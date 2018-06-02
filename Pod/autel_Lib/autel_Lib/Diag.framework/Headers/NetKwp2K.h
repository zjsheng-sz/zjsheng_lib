// NetKwp2K.h: interface for the CNetKwp2K class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETKWP2K_H__9AD8266A_A1B1_4D77_8B8D_536955DFE04B__INCLUDED_)
#define AFX_NETKWP2K_H__9AD8266A_A1B1_4D77_8B8D_536955DFE04B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetLayerBase.h"
#include "ReceiveFrame.h"	// Added by ClassView
#include "Binary.h"	// Added by ClassView
#include "NegativeResponse.h"	// Added by ClassView

class CNetKwp2K : public CNetLayerBase  
{
public:
	virtual CNetLayerBase* NewSelf();
	using CNetLayerBase::Init;
	using CNetLayerBase::SendReceive;
	virtual W_ErrorCode KeepLink(W_I16 iKeepTime, CSendFrame KeepLinkFrame);

	void SetShowNegativeResponseWaitMessageBox(bool bIsShow);

   /*-----------------------------------------------------------------------------
    功    能：发一帧收一帧
    参数说明：CBinary binSend – 发送给ECU命令
    返 回 值：ECU回复的一帧数据
    说    明：无
    -----------------------------------------------------------------------------*/
	virtual CBinary SendReceive(CBinary binSend);


   /*-----------------------------------------------------------------------------
    功    能：发一帧收一帧
    参数说明：CSendFrame sfSend – 发送给ECU命令
    返 回 值：ECU回复的一帧数据
    说    明：无
    -----------------------------------------------------------------------------*/
	virtual CReceiveFrame SendReceive(CSendFrame sfSend);



   /*-----------------------------------------------------------------------------
    功    能：发一多发送帧接收一多接收帧
    参数说明：CMultiSendFrame msfSend – 发送给ECU命令
    返 回 值：ECU回复的一多接收帧
    说    明：无
    -----------------------------------------------------------------------------*/
	virtual CMultiReceiveFrame SendReceive(CMultiSendFrame msfSend) ;


	virtual CReceiveFrame Init(W_U8 uAddressCode, CSendFrame SendFrame);


	virtual	CReceiveFrame Init(W_I16 iWaitTime, W_I16 iLowTime, W_I16 iHighTime, CSendFrame SendFrame);
    void SetEcuAddr(W_U8 ucAddr);
	
	void Destroy();
	CNetKwp2K();
	virtual ~CNetKwp2K();

protected:
	CNegativeResponse nrNegResponse;
};

#endif // !defined(AFX_NETKWP2K_H__9AD8266A_A1B1_4D77_8B8D_536955DFE04B__INCLUDED_)
