#pragma once

#include "FilterOrFrameDistinguish.h"
#include "saej2534_func.h"
#include "DevInterface.h"
#include "NetLayer.h"
#include "SendFrame.h"
#include "ReceiveFrame.h"
#include "EnterSystem.h"
#include "MultiSendFrame.h"
#include <map>

#define DF_SEND_BUFFER_SIZE	255

extern vector<DEVICE_MANAGER> g_vctDevices;		// 指向所有打开的设备
extern PDEVICE_MANAGER g_pCurJ2534Device;		// 指向打开的设备


#define IOP_SAME_SIGNAL_MAIN_AND_ASSIST_LINE    0x01 //L线与K线信号相同
#define IOP_INPUT_POSITIVE_LOGIC                0x02 //输入正逻辑
#define IOP_OUTPUT_POSITIVE_LOGIC               0x04 //输出正逻辑
#define IOP_OUTPUT_REVERSE                      0x08 //输出取反
#define IOP_INPUT_PULLUP_RESISTANCE             0x10 //输入上拉电阻
#define IOP_FET_CK                              0x20 //大电流下拉或晶振

extern CBinary g_binSend;// 因宝马在原来下位机有特殊处理流控制，现加上

class CMonitorPara
{
public:
    unsigned long Pgn;
    unsigned long Timeout; // 超时后退出或发激活帧(仅当SendFrame不为空时)
    CSendFrame SendFrame;
    CMonitorPara(void)
    {
        Pgn = 0;
        Timeout = 1000;
        SendFrame = CSendFrame();
    }
};


enum {
	NORMAL_MODE,
	CUMMINS_MODE
};


#define MAX_NUM_EXPECTED_RESP 50

typedef struct{
    unsigned int ulMode;
    unsigned int ulNumRequestMaskPatternBytes;
    unsigned char RequestMaskData[16];
    unsigned char RequestPatternData[16];
    
    unsigned int ulNumResponseMaskPatternBytes;
    unsigned char ResponseMaskData[16];
    unsigned char ResponsePatternData[16];
}MULTI_REQUEST_EXP_RESP_DATA;

typedef struct{
    unsigned int NumOfExpectedResponse;
    MULTI_REQUEST_EXP_RESP_DATA ExpectedResponseArray[MAX_NUM_EXPECTED_RESP];/*4k左右*/
}MULTI_REQUEST_EXP_RESP;


#ifdef WIN32
	  #define MyPrintf(...) TRACE(__VA_ARGS__)
#else
	  #define MyPrintf(...) LOGI(__VA_ARGS__)
#endif

class CDS708ToJ2534Base
{
public:
	CDS708ToJ2534Base(void);
	virtual ~CDS708ToJ2534Base(void);
	virtual bool CreateConnect(unsigned long uiBps, unsigned long Flags = 0);
	virtual bool AutoCreateConnect(unsigned long uiBps, unsigned long Flags,unsigned long CannelID);

	/*-----------------------------------------------------------------------------
	功    能：设置过滤条件或帧长识别方法
	参数说明：FilterOrFrameReceive        过滤条件或帧长识别方法参数
	返 回 值：错误代码
	说    明：调用者：CEcuInterface::SetProtocol()
	-----------------------------------------------------------------------------*/
	virtual W_ErrorCode SetFilterOrFrameDistinguish(const CFilterOrFrameDistinguish &FilterOrFrameDistinguish);


	virtual W_ErrorCode SetIoPort (W_U8 ucIoInputPort,
		W_U8 uIoOutputPort,
		W_U8 ucWorkVoltage = 12,
		W_U32 uParameter = IOP_SAME_SIGNAL_MAIN_AND_ASSIST_LINE|IOP_INPUT_POSITIVE_LOGIC|IOP_OUTPUT_POSITIVE_LOGIC,
		W_FLOAT fCompareVoltage = 0.0
		);

	virtual W_ErrorCode SetTiming(vector<SCONFIG>& vctTiming, unsigned long PacketTimeout);

	virtual long StartFilter(CBinary binMask,CBinary binPattern);
    /***********************************************************
    *函数名:		long CDS708ToJ2534Base::SetIso15765FramePad(unsigned char bSetIso15765FramePad)
    *功能:		    设置ISO15765数据强制填充模式
    *输入值:		bSetIso15765FramePad: 0-非强制填充模式；1-强制填充模式，填充字节为0xFF;
                                            2-强制填充模式，填充字节为0x00;
    *返回值:      	long:0-设置成功;1-参数不在有效范围内；
    *作者:		    GAZER
    *创建日期:	    2016.12.20
    *备注:          该接口用于解决在奔驰中发送空帧后立马切换过滤ID时，填充字节的异常问题
    ************************************************************/
    long SetIso15765FramePad(unsigned char bSetIso15765FramePad);
	
	/*K线自动慢速进入时，为了提速，将参数一次性设置下去，通过调用此接口可以将中间层的运行环境所用到的参数都设置到VCI
	然后在VCI中运行中间层所要运行的逻辑，在VCI实现协议切换，避免了2次进入，实现提速10-20s；
	*/
    long Abstract5BpsEnterSystemPara(unsigned int Datasize,void *pEnterPara);


	virtual ERRORCODE SetFuncAddrFilter(vector<unsigned char>& vct_func_addr){return STATUS_NOERROR;};

	virtual ERRORCODE SetNodeAddr(unsigned char& NodeAddr){return STATUS_NOERROR;};
	virtual CReceiveFrame SendReceive(CSendFrame SendFrame);

	virtual CBinary SendReceive(CBinary binCommand);

	virtual CReceiveFrame EnterSystem(CEnterSystem SystemEnter);
	virtual CReceiveFrame AddressCodeEnter(CEnterSystem SystemEnter);
	virtual CReceiveFrame QuickEnter(CEnterSystem SystemEnter);


    W_ErrorCode SalveFixedKeepLink(short iKeepTime, CSendFrame KeepLinkFrame);    //下位机固定链路维持 GAZER 20161117
	virtual W_ErrorCode KeepLink(W_I16 iKeepTime, CSendFrame KeepLinkFrame);


	unsigned long GetChannelID();
	long ClearRcvBuffer();	
	long ClearSndBuffer();
	ULONG ReadMultiMsg(ULONG &ulMsgNum,PPASSTHRU_MSG pMsg);
	void SetComTime(W_FLOAT fReceiveMaxByte2ByteInterval_P1, 
		W_FLOAT fReceiveFrameMaxWaitTime_P2,
		W_FLOAT fSendFrameInterval_P3,
		W_FLOAT fSendByte2Byte_P4,
		W_FLOAT fReceivePacketOverTime);

	unsigned long m_uiChanelID;			// 通道ID
	unsigned long m_uiProtocolID;		// 协议ID
	unsigned long m_uiBps;
	unsigned long m_ulPeriodMsgID;		// 周期消息id
	unsigned long m_ulFlags;
	unsigned int m_ui708ProtocolType;// 对应DS708协议类型

	unsigned long m_ulPacketTimeout;
	CFilterOrFrameDistinguish m_FilterOrFrameDistinguish;


	W_FLOAT m_fReceiveMaxByte2ByteInterval_P1;
	W_FLOAT m_fReceiveFrameMaxWaitTime_P2;
	W_FLOAT m_fSendFrameInterval_P3;
	W_FLOAT m_fSendByte2Byte_P4;
	W_FLOAT m_fReceivePacketOverTime;

	// wcx add 1/8/2009
protected:
	W_I16 m_iMax7F78;
	W_I16 m_iHaveRev7f78;
public:
	W_ErrorCode SetMax7F78(W_I16 iMaxNumber);
	virtual bool Is7F78(CBinary bin);
	// end 1/8/2009

	// 单报文对象帧ID
	unsigned int m_ulSingleMsgTxFrmCanID;
	unsigned int  m_ulSingleMsgRxFrmCanID; 
	unsigned int  m_ulSingleMsgRxFrmCanID2;

	unsigned int m_CanDataFormat; // 20160201 瞿松松 1=单报文CANBUS，针对长安转向角等非标准CAN
	unsigned int m_CanFlowCtrlMode; // 20160712 quss针对长安汽车

	void SetSingleMsgFrmCanID(unsigned int  ulTxCanId, unsigned int  ulRxCanId);
	void SetProtocolID(unsigned int uiProtocolID);
	long SetPullMode(unsigned int uiPara);
	long SetKLine5V();

	void SetSpecialCanBus(unsigned int  formate);

	void SetCanFlowCtrlMode(unsigned int  mode);
	
	// 转回奇校验
	void CheckKeyToOdd(unsigned char *pKeyWord, unsigned int uiLen = 2);

	// 设置708协议类型
	void Set708ProtocolType(unsigned int uiProtocolType);
	unsigned int Get708ProtocolType();
	// 发送链路保持
	void SendKeepLinkIfNeed();

	//20160814 quss 
	unsigned char SetTP20SpecialT3(unsigned long value);
        
	// 链路保持帧
	CSendFrame          m_sfKeepLinkFrame;
// 	// 潘相熙 2009-12-23添加
// 	CSendFrame          m_sfKeepLinkFrame2;
	// 2013-3-28 add
	CMultiSendFrame     m_mfKeepLinkFrame;
	// 链路保持间隔
	short               m_ulIntervalTickCount;

	bool m_bSendError;	// 是否有发送错误，如有，则不再发送后面数据2013-07-02提速
	bool m_bFirstSend; // 是否是首次发送，因雷诺第一次发进入时需要在200ms以内发送，为胜时间，如首次不清buffer
	unsigned char m_bSetIso15765FramePad;  //ISO15765协议是否强制增加数据填充字节，解决奔驰发送空帧后立即切换过滤器时出
	                                      //现的过的填充异常  ，GAZER 20161220

	static PASSTHRU_MSG m_msgBuffer[DF_SEND_BUFFER_SIZE];

public:
          /*-----------------------------------------------------------------------------
          功    能：设置多请求发送模式
          参    数：模式值
          返 回 值：无
          说    明：
          0 - 作为默认模式,就是正常收发,非多请求发送模式
          1 - 通用模式,数据存放格式:一个字节长度+ 对应长度的类容...最后两个字节的帧数作为校验
          2 - 未定
          ..
          2016-8-27 laihuiqiang
        -----------------------------------------------------------------------------*/
        long SetMultiRequestMode(unsigned int mode);

        long SetMultiRequestExpectedResp(MULTI_REQUEST_EXP_RESP *pExpectedResp);

        long SetMultiRequestIntervalFrameTime(unsigned IntervalFrameTime );
        
        unsigned int m_MultiRequestMode;

        static unsigned int m_KwpFilterMode;  //KWP 过滤器模式

        static CBinary m_binKwpFilter;  //KWP 过滤器内容
        
};
