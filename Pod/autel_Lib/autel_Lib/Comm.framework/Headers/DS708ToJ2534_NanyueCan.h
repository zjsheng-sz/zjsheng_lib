﻿#pragma once

#include "DS708ToJ2534Base.h"

class CDS708ToJ2534_NanyueCan : public CDS708ToJ2534Base
{
public:
	CDS708ToJ2534_NanyueCan(void);
	virtual ~CDS708ToJ2534_NanyueCan(void);

	typedef enum
	{
		ISO9141_K_LINE_ONLEY	= (0x01<<12),
		CAN_ID_BOTH				= (0x01<<11),
		ISO0141_NO_CHECKSUM		= (0x01<<9),
		CAN_29BIT_ID			= (0x01<<8),
	}CONNECT_FLAG;
	
	typedef enum
	{
		OBD2_PIN1				= 1,
		OBD2_PIN2				= 2,
		OBD2_PIN3				= 3,
		OBD2_PIN6				= 6,
		OBD2_PIN7				= 7,
		OBD2_PIN8				= 8,
		OBD2_PIN9				= 9,
		OBD2_PIN10				= 10,
		OBD2_PIN11				= 11,
		OBD2_PIN12				= 12,
		OBD2_PIN13				= 13,
		OBD2_PIN14				= 14,
		OBD2_PIN15				= 15,

		OBD2_PWM		  = ((2<<8)+10),
		OBD2_VPW		  = (2<<8),

		OBD2_CAN_PIN1_9			= ((1<<8)+9),
		OBD2_CAN_PIN2_10		= ((2<<8)+10),
		OBD2_CAN_PIN3_11		= ((3<<8)+11),
		OBD2_CAN_PIN6_14		= ((6<<8)+14),
		OBD2_CAN_PIN3_8			= ((3<<8)+8),
		OBD2_CAN_PIN13_12		= ((13<<8)+12),
		OBD2_CAN_PIN12_13		= ((12<<8)+13),

		OBD2_SINGLE_CAN_PIN1  = (1<<8),
		OBD2_SINGLE_CAN_PIN2  = (2<<8),
		OBD2_SINGLE_CAN_PIN3  = (3<<8),
		OBD2_SINGLE_CAN_PIN6  = (6<<8),
		OBD2_SINGLE_CAN_PIN7  = (7<<8),
		OBD2_SINGLE_CAN_PIN8  = (8<<8),
		OBD2_SINGLE_CAN_PIN9  = (9<<8),
		OBD2_SINGLE_CAN_PIN10 = (10<<8),
		OBD2_SINGLE_CAN_PIN11 = (11<<8),
		OBD2_SINGLE_CAN_PIN12 = (12<<8),
		OBD2_SINGLE_CAN_PIN13 = (13<<8),
		OBD2_SINGLE_CAN_PIN14 = (14<<8),

	}OBD2_PIN;

	typedef enum
	{
		TX_SCI_TX_VOLTAGE			= (0x01<<23),
		TX_SCI_MODE					= (0x01<<22),
		TX_WAIT_P3_MIN_ONLY			= (0x01<<9),
		TX_CAN_29BIT_ID				= (0x01<<8),//29位CAN标志
		TX_ISO15765_ADDR_TYPE		= (0x01<<7),//扩展地址(除了29位地址后，还有一个字节的地址。
		TX_ISO15765_FRAME_PAD		= (0x01<<6),//一帧数据后面是否需要填充位（只能填充00）
		TX_SW_CAN_HV			    = (0x01<<10)
	}SEND_FLAG;

	typedef enum
	{
		RX_CAN_29BIT_ID				= (0x01<<8),
		RX_ISO15765_ADDR_TYPE		= (0x01<<7),
		RX_IOS15765_PADDING_ERROR	= (0x01<<4),
		RX_TX_INDICATION			= (0x01<<3),
		RX_BREAK					= (0x01<<2),
		RX_START_OF_MESSAGE			= (0x01<<1),
		RX_MSG_TYPE					= 0x01,
	}RECV_STATUS;

	virtual bool CreateConnect(unsigned long uiBps, unsigned long Flags = 0);
	long StartFilter(CBinary binMask,CBinary binPattern,CBinary binFlowCtl);
	virtual W_ErrorCode SetFilterOrFrameDistinguish(const CFilterOrFrameDistinguish &FilterOrFrameDistinguish);
	unsigned char CalCntByte(unsigned char);
	virtual CReceiveFrame SendReceive(CSendFrame SendFrame);
	void SetFlowCtrlAuto(unsigned int val);
	void SetPadByte(unsigned char pad);

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

	unsigned char m_Cnt[16];
	unsigned char m_SendCntByte;

public:
	/*-----------------------------------------------------------------------------
	功    能：Check if this frame is 7F78 or not
	参    数：CBinary ,received fram from ecu.
	返 回 值：true for 7f78 or not
	说    明：none
	-----------------------------------------------------------------------------*/
	virtual bool Is7F78(CBinary bin);

};
