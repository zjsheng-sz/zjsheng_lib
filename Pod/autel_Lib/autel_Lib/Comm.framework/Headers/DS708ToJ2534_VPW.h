#pragma once

#include "DS708ToJ2534Base.h"

class CDS708ToJ2534_VPW : public CDS708ToJ2534Base
{
public:
	CDS708ToJ2534_VPW(void);
	virtual ~CDS708ToJ2534_VPW(void);

	//long StartFilter(CBinary binMask,CBinary binPattern,CBinary binFlowCtl);

	W_ErrorCode SetIoPort (W_U8 ucIoInputPort,
		unsigned char uIoOutputPort,
		W_U8 ucWorkVoltage = 12,
		W_U32 uParameter = IOP_SAME_SIGNAL_MAIN_AND_ASSIST_LINE|IOP_INPUT_POSITIVE_LOGIC|IOP_OUTPUT_POSITIVE_LOGIC,
		W_FLOAT fCompareVoltage = 0.0
		);
	
	virtual CReceiveFrame SendReceive(CSendFrame SendFrame);
	//virtual CReceiveFrame EnterSystem(CEnterSystem SystemEnter);

	virtual W_ErrorCode KeepLink(W_I16 iKeepTime, CSendFrame KeepLinkFrame);



	virtual W_ErrorCode SetFilterOrFrameDistinguish(const CFilterOrFrameDistinguish &FilterOrFrameDistinguish);

	// 2013-02-20 从DS708移植d
	unsigned char m_ucMaskFt[10][12];
	unsigned char  m_ucPatternFt[10][12];
	unsigned char  m_ucLengthFt[10];
	unsigned char  m_ucNumberFt;

};
