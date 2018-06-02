#pragma once
#include "DS708ToJ2534Base.h"

#define KWP1281_ECUID_MSGS	(1<<24)

class CDS708ToJ2534_ALDL :
	public CDS708ToJ2534Base
{
public:
	CDS708ToJ2534_ALDL(void);
	virtual ~CDS708ToJ2534_ALDL(void);

	virtual W_ErrorCode SetIoPort(unsigned char ucIoInputPort, 
		unsigned short uIoOutputPort,
		unsigned char ucWorkVoltage /* = 12 */, 
		unsigned int uParameter, 
		float fCompareVoltage /* = 0.0 */ );

	
	virtual CReceiveFrame EnterSystem(CSendFrame sendFrame, unsigned char Poll_Id);

	virtual CReceiveFrame SendReceive(CSendFrame SendFrame);
	virtual CBinary SendReceive(CBinary binCommand);


	virtual W_ErrorCode SetTiming(vector<SCONFIG>& vctTiming, unsigned long PacketTimeout);
	virtual W_ErrorCode SetFilterOrFrameDistinguish(const CFilterOrFrameDistinguish &FilterOrFrameDistinguish);

private:
	unsigned char CalcCheckSum(const unsigned char* pData, unsigned int nSize);
	CBinary m_binEnterSys;
	virtual void EndEcuReturnAlwaysMode(CBinary binStopCommand);
	virtual CBinary ReceiveOneFrame();
	virtual void FindFrameInterval();

	/*-----------------------------------------------------------------------------
	功    能：发送一帧数据
	参数说明：CBinary binSendFrame -- 发送帧
	返 回 值：错误代码
	说    明：无
	-----------------------------------------------------------------------------*/
	virtual W_ErrorCode SendOneFrame(CBinary binSendFrame);
	unsigned char m_ucALDLHead;

};



