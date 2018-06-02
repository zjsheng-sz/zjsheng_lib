#pragma once
#include "DS708ToJ2534Base.h"

class CDS708ToJ2534_KWP :
	public CDS708ToJ2534Base
{
public:
	CDS708ToJ2534_KWP(void);
	virtual ~CDS708ToJ2534_KWP(void);

	virtual W_ErrorCode SetIoPort(unsigned char ucIoInputPort, 
		unsigned short uIoOutputPort,
		unsigned char ucWorkVoltage /* = 12 */, 
		unsigned int uParameter, 
		float fCompareVoltage /* = 0.0 */ );

	
	virtual CReceiveFrame SendReceive(CSendFrame SendFrame);

	virtual W_ErrorCode SetTiming(vector<SCONFIG>& vctTiming, unsigned long PacketTimeout);

	virtual W_ErrorCode SetFilterOrFrameDistinguish(const CFilterOrFrameDistinguish &FilterOrFrameDistinguish);
	virtual CReceiveFrame AddressCodeEnter(CEnterSystem SystemEnter);
	bool Is7F78(CBinary bin);

};



