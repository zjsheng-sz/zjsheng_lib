#ifndef __DS708_TO_J2534_J1939_H__
#define __DS708_TO_J2534_J1939_H__

#include "DS708ToJ2534Base.h"
#include <map>

class CDS708ToJ2534_1939 : public CDS708ToJ2534Base 
{
public:
	typedef struct
	{
		unsigned Pgn;
		CReceiveFrame ReceiveFrame;
	}ReceivedBAMdata;

	typedef enum
	{
		ISO9141_K_LINE_ONLEY	= (0x01<<12),
		CAN_ID_BOTH				= (0x01<<11),
		ISO0141_NO_CHECKSUM		= (0x01<<9),
		CAN_29BIT_ID			= (0x01<<8),
	}CONNECT_FLAG;

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

	typedef struct
	{
		unsigned int RemaindFramNum;
		unsigned int ReceiveIndex;
		unsigned int DataNum;
		unsigned long Pgn;
		CReceiveFrame RceivingFrame;
		unsigned long ContinueFrameTimeCount;
	}BamMultFramRceivingBuffer;

	struct 
	{
		unsigned long HeadPgn;
		unsigned long TailPgn;
		unsigned char DstAdress;
		unsigned char SrcAdress;
	} m_SndPara;

	struct 
	{
		map<unsigned long, BamMultFramRceivingBuffer> ReceivingBuffer; 
		map<unsigned long, CBinary> DataBuffer; 
	} m_RcvPara;

	struct
	{
		bool bIsMultFramSending;
		CBinary binCF;
	} m_ContunuFrame;

	typedef struct 
	{
		unsigned long StartTime;
		bool IsTimeout;
	} stAuteSendTimeoutPara;
	

	CDS708ToJ2534_1939(void);
	~CDS708ToJ2534_1939(void);
    W_ErrorCode SetTiming(vector<SCONFIG>& vctTiming, unsigned long PacketTimeout);
	bool CreateConnect(unsigned long uiBps, unsigned long Flags = 0);
	long StartFilter(CBinary binMask,CBinary binPattern,CBinary binFlowCtl = CBinary());
	W_ErrorCode SetFilterOrFrameDistinguish(const CFilterOrFrameDistinguish &FilterOrFrameDistinguish);
	long SetProtectAddress(vector<unsigned char> &FuncAddr);
	W_ErrorCode SetIoPort (W_U8 ucIoInputPort,W_U8 uIoOutputPort,W_U8 ucWorkVoltage ,W_U32 uParameter,W_FLOAT fCompareVoltage);
	CReceiveFrame ThreadHandle(void);
	CReceiveFrame SendReceiveThread(CSendFrame sendframe);
	CReceiveFrame SendReceive(CSendFrame sendframe); // 发送数据
	unsigned long GetTailPGN(CBinary binSend);
	unsigned long GetHeadPGN(CBinary binSend);
	unsigned char GetDstAddress(CBinary binSend);
	unsigned char GetSrcAddress(CBinary binSend);
	unsigned long SetFilter(unsigned char ch1, unsigned char ch2, unsigned char ch3);
	unsigned long SetFilter(unsigned char ch1, unsigned char ch2);
	unsigned long SetFilter_Ext(unsigned char ch2, unsigned char ch3);
	unsigned long SetFilter(unsigned char ch1);
	unsigned long SetFilter(void);
	unsigned long ClearFilter(void);
	ULONG SendDataWithoutClearRcvBuffer(CBinary binData);
	CBinary GerneraContinuFrame(map<unsigned long, BamMultFramRceivingBuffer> ReceivingBuffer, CBinary binContinuReceiveFram);

	CReceiveFrame ReceiveOneDataThread(void);
	virtual CReceiveFrame ReceiveOneData(void);
	CReceiveFrame RecvData(unsigned long ulMsgNum);
	void StartMonitorBase(void);
	bool StartMonitor(map<unsigned long, CMonitorPara> CMonitorParameter);
	bool StartMonitor(void);
	unsigned long GetMonitorDataSize(void);
	CReceiveFrame GetMonitorData(void);
	unsigned long GetMonitorState(void);
	vector<unsigned long> GetNotExitPgn(void);
	map<unsigned long, CMonitorPara> GetRemainPgn(void);
	bool StopMonitor(void);
	void ClearMonitorData(void);
	CReceiveFrame MapToCReceiveFrame(map<unsigned long, CBinary> DataBuffer);
	unsigned int MapToEraseAckFrame(unsigned char SrcAddr);
	CBinary CRrcFrameToCBinary(CReceiveFrame RcvFrame);
	bool IsThreadHandleSetingPgn(unsigned long Pgn);


	CBinary Pick_EC_EB(CBinary binRecvData);
	CBinary Pick_Normal_SF(map<unsigned long, BamMultFramRceivingBuffer> &ReceivingBuffer, CBinary binSend, CBinary binRecvData);

	CReceiveFrame GetMsgImmediately(void);
	virtual unsigned long AnalyseOneReceiveFrame(CBinary binReceive);


	unsigned long GetHeadPGNAddr(CBinary binSend);//20160614 陈刚 增加：带物理地址的PGN
	bool m_bIsThreadHandleEnable;

	map<unsigned long, CMonitorPara> m_SettingBamPara;
	map<unsigned long, BamMultFramRceivingBuffer> m_BamMultFramRceivingBuffer; // <source address, frame>
	map<unsigned long, CBinary> m_ThreadhandleDataBuffer; // <PGN, binary>
	map<unsigned long, unsigned long> m_ThreadhandleDataBuffer_Cnt; // <PGN, binary>
	vector<CBinary> m_vAutoSendData;

	CBinary       Bak;
	unsigned long TimeCount;
	bool          TimeCountFlg;
	bool          AckFlg;
	unsigned long m_ulAutoSendDataEndTime;
	unsigned int m_auteSendCnt;
	unsigned int m_auteSendEndFlag;
	unsigned int m_autoSendWholeTotal;
	bool m_bIsReceiveAllBam;
	unsigned int m_ReceiveBamLength;
	unsigned long m_StartRMonitorTime;
	unsigned long m_EndMonitorTime;
	unsigned long m_ulReqPgn;
	unsigned long m_ulReceiveTimeout;
	CBinary m_binSend_of_SendReceive;
	map<unsigned long, stAuteSendTimeoutPara> m_AuteSendTimeoutPgn;
	unsigned long m_ulThreadHandleExecuteCnt;
	CReceiveFrame m_RetureFrame;
	W_FLOAT m_fReceiveFrameMaxWaitTime_P2_old;
};


#endif