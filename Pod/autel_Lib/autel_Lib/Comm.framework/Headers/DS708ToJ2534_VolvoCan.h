#pragma once

#include "DS708ToJ2534Base.h"

class CDS708ToJ2534_VolvoCan : public CDS708ToJ2534Base
{
public:
	CDS708ToJ2534_VolvoCan(void);
	virtual ~CDS708ToJ2534_VolvoCan(void);


	virtual bool CreateConnect(unsigned long uiBps, unsigned long Flags = 0);


	long StartFilter(CBinary binMask,CBinary binPattern,CBinary binFlowCtl);
	virtual W_ErrorCode SetFilterOrFrameDistinguish(const CFilterOrFrameDistinguish &FilterOrFrameDistinguish);

	//virtual W_ErrorCode SetIoPort (W_U8 ucIoInputPort,
	//	unsigned char uIoOutputPort,
	//	W_U8 ucWorkVoltage = 12,
	//	W_U32 uParameter = IOP_SAME_SIGNAL_MAIN_AND_ASSIST_LINE|IOP_INPUT_POSITIVE_LOGIC|IOP_OUTPUT_POSITIVE_LOGIC,
	//	W_FLOAT fCompareVoltage = 0.0
	//	);


	virtual CReceiveFrame SendReceive(CSendFrame SendFrame);
	virtual W_ErrorCode KeepLink(W_I16 iKeepTime, CSendFrame KeepLinkFrame);
	void InitKLine();// 初始化K线

	//virtual CBinary SendReceive(CBinary binCommand);

	//virtual CReceiveFrame EnterSystem(CEnterSystem SystemEnter);


	union tagCanSourceDestAddress {
		W_U16 u16ExistAddress;
		struct {
			W_U8 ucToolsAddress;
			W_U8 ucEcuAddress;
		};
	} m_EcuToolAddress;



	// 是否填充CAN帧的未使用部分
	bool m_bFillCanFrame;

	// 用什么字节填充CAN的未使用部分
	BYTE m_ucFillByte;

	// FlowControlFrame
	BYTE m_aucCanFlowControl[10];

	bool m_b06F1;//  是否是06F1

	unsigned long m_uiChanelID_KLine;			// 通道ID
	unsigned long m_uiProtocolID_KLine;		// 协议ID
	unsigned long m_ulPeriodMsgID_KLine;		// 周期消息id

	unsigned short m_ulLinkKLineTickCount;
	CSendFrame m_sfKLinkKeep;
	unsigned short m_ulLinkCanLinkTickCount;
	CSendFrame m_sfCanLinkKeep;

public:
	/*-----------------------------------------------------------------------------
	功    能：Check if this frame is 7F78 or not
	参    数：CBinary ,received fram from ecu.
	返 回 值：true for 7f78 or not
	说    明：none
	-----------------------------------------------------------------------------*/
	virtual bool Is7F78(CBinary bin);
	void SendWholeFrame(CBinary binSendFrame);
	BYTE m_ucFormatByte;
	bool m_bEnableFormatByte;// 格式化字节是否有效
	/*-----------------------------------------------------------------------------
	功    能：发送一个CAN数据帧
	参数说明：CBinary binSendFrame        发送帧
	返 回 值：错误代码
	说    明：包含填充过程
	-----------------------------------------------------------------------------*/
	virtual W_ErrorCode SendOneFrame(CBinary binSendFrame);
	CReceiveFrame KwpSendReceive(CSendFrame sfSendFrame);
	CBinary KwpSendReceive(CBinary binSendFrame);
    CBinary ReceiveOneWholeFrame();
	CBinary ReceiveOneFrame();
	unsigned char m_ucFilterRevData;
};
