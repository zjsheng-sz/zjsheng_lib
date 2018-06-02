#ifndef __DS708_TO_J2534_CumminsJ1939_H__
#define __DS708_TO_J2534_CumminsJ1939_H__

#include "DS708ToJ2534_1939.h"

class CDS708ToJ2534_CumminsJ1939 : public CDS708ToJ2534_1939 
{
public:
	CDS708ToJ2534_CumminsJ1939();
	~CDS708ToJ2534_CumminsJ1939();
	unsigned char Case1Byte6Couter(unsigned char DataIn);
	unsigned char ReqByte8Couter(unsigned char DataIn);
	unsigned char AnsByte8Couter(unsigned char DataIn);
	unsigned char Case1Byte10Couter(unsigned char Byte11, unsigned char DataIn);
	CSendFrame ToSendForm(CSendFrame sndframe_in);
	CReceiveFrame SendReceive(CSendFrame sendframe);
	CReceiveFrame ReceiveOneData(void);
	unsigned long AnalyseOneReceiveFrame(CBinary binRecvData);
	void ResetParam(void);

private:
	unsigned char m_Case1Mode01Cnt;
	unsigned int m_nLastSndLength;
	unsigned int m_nLastRcvLength;
	unsigned char m_AnsByte8Cnt;
	unsigned char m_ReqByte8Cnt;
	unsigned char m_cByte12Cnt;		//01模式计数
	unsigned char m_cByte12Cnt_1x;	//10模式、11模式、12模式计数  陈帝亮2016-02-01修改	
	static unsigned char m_Case1Byte6Cnt;
	static unsigned char m_AnsByte7Cnt;
	CBinary m_binSend;
};


#endif