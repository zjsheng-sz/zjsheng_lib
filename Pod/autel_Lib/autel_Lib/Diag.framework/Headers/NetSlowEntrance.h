// NetSlowEntrance.h: interface for the CNetSlowEntrance class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETSLOWENTRANCE_H__4719907D_01D1_4A81_B19E_8A01F0B0AB9C__INCLUDED_)
#define AFX_NETSLOWENTRANCE_H__4719907D_01D1_4A81_B19E_8A01F0B0AB9C__INCLUDED_

#include "NetLayerBase.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNetSlowEntrance : public CNetLayerBase  
{
public:
	CNetSlowEntrance();
	virtual ~CNetSlowEntrance();
	CReceiveFrame Init(W_U8 uAddressCode, CSendFrame SendFrame=CSendFrame(CBinary("",0),0));
	CNetLayerBase *m_pNetLayer;
        using CNetLayerBase::Init;
    virtual CNetLayerBase* NewSelf();
    void Destroy();
    virtual W_ErrorCode SetMode(W_I16 iMode);
    virtual CBinary Receive();
    virtual CBinary SendReceive(CBinary binSend);
    virtual CReceiveFrame SendReceive(CSendFrame SendFrame);
    virtual CMultiReceiveFrame SendReceive(CMultiSendFrame SendFrame);
    virtual CIncorporateReceiveFrame SendIncorporateReceive(CSendFrame SendFrame);
    W_ErrorCode KeepLink(W_I16 iKeepTime, CSendFrame KeepLinkFrame = CSendFrame());
   /* void SetCommTime (W_FLOAT fReceiveMaxByte2ByteInterval_P1,
                             W_FLOAT fReceiveFrameMaxWaitTime_P2,
                             W_FLOAT fSendFrameInterval_P3,
                             W_FLOAT fSendByte2Byte_P4,
                             W_FLOAT fReceivePacketOverTime
                             );*/
    void SetFilterOrFrameDistinguish(CFilterOrFrameDistinguish FilterOrFrameDistinguish);
// 	W_U16 GetProtocolId();
	void EnableUnpack(bool bIsUnpack=true);
	void EnablePack(bool bIsPack=true);
	CNetSlowEntrance::TimePara* GetCommTimePointer ();
	W_ErrorCode SetToolId(W_U32 uToolId);
	void SetEcuId(W_U8 uEcuId);
	void SetShowNegativeResponseWaitMessageBox(bool bIsShow);
};

#endif // !defined(AFX_NETSLOWENTRANCE_H__4719907D_01D1_4A81_B19E_8A01F0B0AB9C__INCLUDED_)
