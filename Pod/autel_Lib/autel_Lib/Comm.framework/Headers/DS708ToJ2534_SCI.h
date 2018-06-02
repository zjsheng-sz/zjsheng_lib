#pragma once
#include "DS708ToJ2534Base.h"

class CDS708ToJ2534_SCI :
	public CDS708ToJ2534Base
{
public:
	CDS708ToJ2534_SCI(void);
	virtual ~CDS708ToJ2534_SCI(void);

	virtual CReceiveFrame SendReceive(CSendFrame SendFrame);

	virtual W_ErrorCode SetTiming(vector<SCONFIG>& vctTiming, unsigned long PacketTimeout);

	virtual W_ErrorCode SetFilterOrFrameDistinguish(const CFilterOrFrameDistinguish &FilterOrFrameDistinguish);

	virtual W_ErrorCode SetIoPort (W_U8 ucIoInputPort,
		W_U8 uIoOutputPort,
		W_U8 ucWorkVoltage = 12,
		W_U32 uParameter = IOP_SAME_SIGNAL_MAIN_AND_ASSIST_LINE|IOP_INPUT_POSITIVE_LOGIC|IOP_OUTPUT_POSITIVE_LOGIC,
		W_FLOAT fCompareVoltage = 0.0
		);
	bool m_b7812Bps;

};



