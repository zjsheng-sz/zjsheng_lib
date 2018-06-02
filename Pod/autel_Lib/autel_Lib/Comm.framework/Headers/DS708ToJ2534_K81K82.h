#pragma once
#include "DS708ToJ2534Base.h"

#define KWP1281_ECUID_MSGS	(1<<24)

class CDS708ToJ2534_K81K82 :
	public CDS708ToJ2534Base
{
public:
	CDS708ToJ2534_K81K82(void);
	virtual ~CDS708ToJ2534_K81K82(void);

	virtual W_ErrorCode SetIoPort(unsigned char ucIoInputPort, 
		unsigned short uIoOutputPort,
		unsigned char ucWorkVoltage /* = 12 */, 
		unsigned int uParameter, 
		float fCompareVoltage /* = 0.0 */ );

	
	virtual CReceiveFrame EnterSystem(CSendFrame sendFrame, unsigned char Poll_Id);

	virtual CReceiveFrame SendReceive(CSendFrame SendFrame);


	virtual W_ErrorCode SetTiming(vector<SCONFIG>& vctTiming, unsigned long PacketTimeout);
	virtual W_ErrorCode SetFilterOrFrameDistinguish(const CFilterOrFrameDistinguish &FilterOrFrameDistinguish);

private:
	unsigned char CalcCheckSum(const unsigned char* pData, unsigned int nSize);
public:
	CBinary m_binEnterSys;
	unsigned char  m_ucHead;                 // 识别头
	// 最后一次接收帧长度, 为回复无数帧判断帧有效性使用 2008.9.28王长喜加入
	W_I16 m_iExpectantReceiveFrameLength;
	void FindFrameInterval();
	void EndEcuReturnAlwaysMode(CBinary binStopCommand);
	virtual CBinary ReceiveOneFrame();
	W_ErrorCode SendOneFrame(CBinary binSendFrame);
	W_ErrorCode SendTwoFrames(CBinary binSendFrame);

};



