#pragma once
#include "DS708ToJ2534Base.h"

class CDS708ToJ2534_NoStdKL:
	public CDS708ToJ2534Base
{
public:
	CDS708ToJ2534_NoStdKL(void);
	virtual ~CDS708ToJ2534_NoStdKL(void);

	virtual W_ErrorCode SetIoPort(unsigned char ucIoInputPort, 
		unsigned char uIoOutputPort,
		unsigned char ucWorkVoltage /* = 12 */, 
		unsigned int uParameter, 
		float fCompareVoltage /* = 0.0 */ );

	
	virtual CReceiveFrame SendReceive(CSendFrame SendFrame);

	virtual W_ErrorCode SetTiming(vector<SCONFIG>& vctTiming, unsigned long PacketTimeout);

	/*-----------------------------------------------------------------------------
	功    能：设置过滤条件或帧长识别方法
	参数说明：FilterOrFrameReceive        过滤条件或帧长识别方法参数
	返 回 值：错误代码
	说    明：调用者：CEcuInterface::SetProtocol()
	-----------------------------------------------------------------------------*/
	virtual W_ErrorCode SetFilterOrFrameDistinguish(const CFilterOrFrameDistinguish &FilterOrFrameDistinguish);

	bool Is7F78(CBinary bin);

};



