#pragma once
#ifdef WIN32
	#include "PassThru.h"
#else
	#include "saej2534_func.h"
#endif
//#include "stdAfx.h"
#ifndef DF_CHANNEL
#define DF_CHANNEL
typedef struct {
    unsigned long protocol;
    unsigned long channel;  
    unsigned short pp;
    unsigned short ss;
    unsigned long rcvtimeout;  
    unsigned long sndtimeout;
}CHANNEL, *PCHANNEL;
#endif

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

class CDevInterface
{
public:
    CDevInterface(void);
    virtual ~CDevInterface(void);

	long Open(char* devName, unsigned long& devID);

    long Close();

    long CreateConnect(unsigned long &ProtocolID, unsigned long &Flags, unsigned long &BaudRat, unsigned long& ChannelID);
    long AutoCreateConnect(unsigned long &ProtocolID, unsigned long &Flags, unsigned long &BaudRat, unsigned long& ChannelID);

    long Disconnect(unsigned long &ChannelID);

    long SendMessage(unsigned long &ChannelID, PPASSTHRU_MSG pMsg, unsigned long &MsgNums, unsigned long Timeout=0);

    long RecvMessage(unsigned long &ChannelID, PPASSTHRU_MSG pMsg, unsigned long &MsgNums, unsigned long Timeout=0);

    long StartPeriodMessage(unsigned long &ChannelID, PPASSTHRU_MSG pMsg, unsigned long &PeriodID, unsigned long &TimeInterval);

    long StopPeriodMessage(unsigned long &ChannelID, unsigned long &PeriodID);

    long ClearPeriodMessage(unsigned long& ChannelID);

    long StartFilter(
        unsigned long &ProtocolID,
		unsigned long &ftType,
		unsigned long &ftID,
        PPASSTHRU_MSG pMaskMsg,
        PPASSTHRU_MSG pPatternMsg,
        PPASSTHRU_MSG pFlowCtrlMsg = NULL        
        );

    long StopFilter(unsigned long &ChannelID, unsigned long &ftID);

    long ClearFilter(unsigned long &ChannelID);

    long SetProgramVoltage(unsigned long PinNum, unsigned long voltage);

    long GetProgramVoltage(unsigned long PinNum);  

	long GetVBATT();

    long SetConfig(unsigned long &ChannelID, vector<SCONFIG> &ParamConfig);

    long GetConfig(unsigned long &ChannelID, vector<SCONFIG> &ParamConfig);

	long SetConfig(unsigned long &ChannelID, unsigned long Param, unsigned long Value);
    long FiveBaudInit(unsigned long &ChannelID, unsigned char Address, unsigned char &KeyWord1, unsigned char &KeyWork2);
	long FiveBaudInit(unsigned long &ChannelID,unsigned char Address,unsigned char *pKeyWord,unsigned long ulBufLen );

    long FashInit(unsigned long &ChannelID, PPASSTHRU_MSG pInMsg = NULL, PPASSTHRU_MSG pOutMsg = NULL);

    long ReadBatVoltage(unsigned long &voltage);    

    long AddFuncAddr(unsigned long &ChannelID, vector<unsigned char> &FuncAddr);

    long DelFuncAddr(unsigned long &ChannelID, vector<unsigned char> &FuncAddr);

	long SetNodeAddr(unsigned long &ChannelID, unsigned char NodeAddr);

    long SetSwCanSpeedMode(unsigned long &ChannelID, bool HiSpeed = false);

    long SetPollResponse(unsigned long &ChannelID, vector<unsigned char>PollMsg);

    long BecomeMaster(unsigned long &ChannelID, unsigned char &PollID);

    long StartRepeateMessage(unsigned long &ChannelID, PREPEAT_MSG_SETUP pRepeateMsg, unsigned long &RepeateID);

    long QueryRepeateMessage(unsigned long &ChannelID, unsigned long &RepeateID, unsigned long &state);

    long StopRepeateMessage(unsigned long &ChannelID, unsigned long &RepeateID);

    long ProtectAddress(unsigned long &ChannelID, vector<unsigned char> &ProtectAddr);

    long Generic(unsigned long &ChannelID, unsigned int GenericId, unsigned int DataSize, void *pData);

    long RequestConnect(unsigned long &ChannelID, vector<unsigned char> &RequestMsg);

    long TearDownConnect(unsigned long &ChannelID, vector<unsigned char> &ConnectData);

    long GetDeviceConfig(vector<SCONFIG> &devConfig);

    long SetDeviceConfig(vector<SCONFIG> &devConfig);

    long GetDeviceInfo(vector<SPARAM> &devInfo);

    long GetProtocolInfo(unsigned long ChannelID, vector<SPARAM> &protocolInfo);

    long ClearFuncAddr(unsigned long &ChannelID);    

    long ClearRcvBuffer(unsigned long &ChannelID);

    long ClearSndBuffer(unsigned long &ChannelID);

    long GetChannelCnts(void);

	long ReadVersion
		( 
		char *pFirmwareVersion,
		char *pDllVersion, 
		char *pApiVersion 
		);

	long AutoBaudrateDetect(unsigned long &ChannelID, unsigned char Address, unsigned char &KeyWord1, unsigned char &KeyWork2);

	long AutoBaudrateDetect(unsigned long &ChannelID, unsigned char Address, unsigned char *pKeyWord,unsigned long ulBufLen);
	long GetPinVoltage(unsigned long PinNumber, unsigned long& Voltage);

	long EnablePullMode(unsigned long& ChannelID, unsigned long& Mode);
	long GetSerial(char *szVCISWver, char *szVCIHWver, char *szVCISerial, char *szVCIManufacturerTime, char *szVCIPassWord);
public:   

    vector<CHANNEL> m_vctChannel;

private:

    unsigned long IsConnected(unsigned long &ChannelID);

    unsigned long m_DeviceID;

    unsigned long m_PinComplex;

    unsigned long m_PinProgramVoltage;  

    unsigned long m_GenericModeSwitch;/*RequestConnect的接口可以切换成作为通用接口,0 - RequestConnect, 1 - Generic*/
    
#ifdef WIN32
    CPassThru* m_pPassThru;
#endif
};

