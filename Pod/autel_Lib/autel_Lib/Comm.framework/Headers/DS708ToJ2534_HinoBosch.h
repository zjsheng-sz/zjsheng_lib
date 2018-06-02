#pragma once
#include "DS708ToJ2534Base.h"

#define KWP1281_ECUID_MSGS	(1<<24)
class CDS708ToJ2534_HinoBosch :
	public CDS708ToJ2534Base
{
public:
	CDS708ToJ2534_HinoBosch(void);
	virtual ~CDS708ToJ2534_HinoBosch(void);

	virtual bool CreateConnect(unsigned long uiBps, unsigned long Flags = 0);

	virtual  W_ErrorCode SetIoPort (W_U8 ucIoInputPort,
		W_U8 uIoOutputPort,
		W_U8 ucWorkVoltage = 12,
		W_U32 uParameter = IOP_SAME_SIGNAL_MAIN_AND_ASSIST_LINE|IOP_INPUT_POSITIVE_LOGIC|IOP_OUTPUT_POSITIVE_LOGIC,
		W_FLOAT fCompareVoltage = 0.0
		);

	unsigned long m_uiChanelID_Hino;			// 通道ID
	unsigned long m_ulPeriodMsgID;		// 周期消息id

	//	unsigned short m_ulLinkKLineTickCount;
	//	CSendFrame m_sfKLinkKeep;
	//	unsigned short m_ulLinkCanLinkTickCount;
	//	CSendFrame m_sfCanLinkKeep;



	virtual CReceiveFrame AddressCodeEnter(CEnterSystem SystemEnter);

	virtual CBinary SendReceive(CBinary binCommand);

	virtual CReceiveFrame SendReceive(CSendFrame SendFrame);

	virtual W_ErrorCode KeepLink(W_I16 iKeepTime, CSendFrame KeepLinkFrame);

	virtual W_ErrorCode SetTiming(vector<SCONFIG>& vctTiming, unsigned long PacketTimeout);

	/*-----------------------------------------------------------------------------
	功    能：发送一帧数据
	参数说明：CBinary binSendFrame -- 发送帧
	返 回 值：错误代码
	说    明：无
	-----------------------------------------------------------------------------*/
	//virtual W_ErrorCode SendOneFrame(CBinary binSendFrame);

	/*-----------------------------------------------------------------------------
	功    能：设置过滤条件或帧长识别方法
	参数说明：FilterOrFrameReceive        过滤条件或帧长识别方法参数
	返 回 值：错误代码
	说    明：调用者：CEcuInterface::SetProtocol()
	-----------------------------------------------------------------------------*/
	virtual W_ErrorCode SetFilterOrFrameDistinguish(const CFilterOrFrameDistinguish &FilterOrFrameDistinguish);


protected:
	static unsigned char m_bPacketSN;

};



