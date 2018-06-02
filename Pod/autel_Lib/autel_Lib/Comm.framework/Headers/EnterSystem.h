#ifndef ENTERSYSTEM_H_HEADER_INCLUDED_B97E151B
#define ENTERSYSTEM_H_HEADER_INCLUDED_B97E151B
#include "SendFrame.h"
#include "ErrorCode.h"

/******************************************************************************

    Copyright (c) 2007, AUTEL Ltd,.Co

    All rights reserved.

    文件名称：EnterSystem.h EnterSystem.cpp

    档 标 识：

    摘    要：记录进入ECU诊断系统方式

    用    途：


    历史记录：
    ---------------------------------------------------------------------------
     时     间     作者    版本号     操    作    内    容
    ---------------------------------------------------------------------------
     2007.6.26     王长喜    1.0      创建此类。
     2007.7.5      王长喜    1.0      完成编码，编译通过

*******************************************************************************/
class CEnterSystem
{
  public:
/*
        进入系统模式
        EM_UNKNOW -- 未定义
        EM_ADDRESS_CODE -- 地址码模式
        EM_QUICK_ENTER -- 快速进入模式
        EM_TP20 -- TP20模式
*/
    enum tagENTER_MODE {
        EM_UNKNOW = 0,
        EM_ADDRESS_CODE = 1,
        EM_QUICK_ENTER = 2,
        EM_TP20 = 3,
        EM_TP16 = 4
    };

	typedef struct {
		W_U16 id;
		W_U16 ft_id;
		W_U16 target_addr;		
		W_U8 addr_code;
		W_U8 system_id;
	}TP16PARAM, *PTP16PARAM;

    // 进入参数
    union tagENTER_PARAMETER
    {
        struct tagAddressCode{
			unsigned long FiveBaudrateMode;
			unsigned long W0;
			unsigned long W1;
			unsigned long W2;
			unsigned long W3;
			unsigned long W4;			
			unsigned long Baudrate;
			unsigned long AddrCode;		
			unsigned long Flags;		
			bool b5KeyWord;



//             U16 m_uWaitTimeBeforSendAddress;
//             U16 m_u0x55OverTime;
//             U16 m_uReceiveKwOverTime;
//             U16 m_uKw2ReverseWaitTime;
//             U16 m_uReceiveReverseAddressOverTime;
//             // 地址码
//             U8 m_ucAddress;
//             // 地址码进入参数
//             U32 m_u32Parameter;
//             // 地址码波特率
//             FLOAT m_fBps;
        } AddressCode;
        struct tagQuickEnter {
            // 电平拉低时间
            W_I16 m_iLowVoltageTime;
            // 电平拉高时间
            W_I16 m_iHighVoltageTime;
            // 执行等待稳定时间
            W_I16 m_iWaitTime;
        } Quick;
        struct tagTp20Can {
            // 目标地址
            BYTE m_ucTpTargetAddress;
            // 应用层ID
            BYTE m_ucAppLayerID;
            W_U16 m_uReceptionID;
			W_U16 m_uOpeningID;
        } Tp20Can;
       
		TP16PARAM Tp16Can;
    };

    typedef union tagENTER_PARAMETER ENTER_PARAMETER;

    /*
     EM_UNKNOW       -- 未定义
     EM_ADDRESS_CODE -- 地址码
     EM_QUICK_ENTER  -- 快速进入
     EM_TP20         -- TP20
    */
    typedef enum tagENTER_MODE ENTER_MODE;

     #define ES_ACP_AUTO  0xFFFFFFFF
     #define ES_ACP_MASK_KW_REVERSE_TO_ECU  0x0003 //KW取反发回掩码
     #define ES_ACP_KW2_REVERSE_TO_ECU      0x0002 //KW2取反发回
     #define ES_ACP_KW1_REVERSE_TO_ECU      0x0001 //KW1取反发回
     #define ES_ACP_MASK_BYTE_KW            0x000C //接收KW字数量掩码
     #define ES_ACP_2_BYTE_KW               0x0004 //接收2个KW字, 接收KW最大等待时间500mS
     #define ES_ACP_5_BYTE_KW               0x0008 //接收5个KW字, 接收KW最大等待时间2500mS
     #define ES_ACP_RECEIVE_ADDRESS_REVERSE 0x0010 //接收地址码取反
     #define ES_ACP_MASK_RECEIVE_FRAME      0x0060 //接收帧数量掩码
     #define ES_ACP_ONE_FRAME               0x0020 //接收一帧数据
     #define ES_ACP_MULTI_FRAME             0x0040 //接收多帧数据
     #define ES_ACP_AUTO_BPS                0x0080 //自动识别波特率
     #define ES_KEEP_ASSIST_LINE            0x0100 //保持辅助通信线
     //#define ES_ACP_200BPS_INSTEADOF_5BPS   0x0200 //200BPS进入,2016/1/28新增需求  2016-4-20注释，不使用此接口
     #define ES_ISO_CITROEN                 0x0800 //ISO CITROEN特殊协议,串口波特率固定为9600   Genbay added on 2009-02-28
     #define ES_ISO_CITROEN_PARAMETER       (ES_ISO_CITROEN|ES_ACP_2_BYTE_KW| ES_ACP_AUTO_BPS| ES_ACP_ONE_FRAME) //ISO CITROEN特殊协议,串口波特率固定为9600   Genbay added on 2009-03-05
     #define BUADRATE_ISO_CITROEN           9600   //ISO CITROEN特殊协议,串口波特率固定为9600   Genbay added on 2009-02-28
      
    /*-----------------------------------------------------------------------------
      功    能：地址码进入方式
      参数说明：W_U8 uAddressCode -- 地址码
                W_U32 uParameter -- 进入参数
                    //ES_ACP_ Enter System  Address Code Parameter
                  #define ES_ACP_AUTO                    0xFFFFFFFF //全部自动识别，包括协议
                    ===========================================
                     KW1  KW2 | 协议
                    ----------+--------------------------------
                      01 8A   | KWP1281 -- KW2取反，收多帧
                      AB 03   | KWP1281
                      08 08   | ISO9141 -- KW2取反，地址码取反，不接收数据帧
                      94 94   | ISO9141
                     大于2000 | KWP2000 -- 同ISO9141
                              |
                      51 80   | K81 -- KW2取反，接收数据帧,ECU不停的回，直到打断
                      52 80   | K82 -- KW2取反，25~30mS内接收一帧数据，
                    ===========================================
                  #define ES_ACP_MASK_KW_REVERSE_TO_ECU    0x0003 //KW取反发回掩码
                    #define ES_ACP_KW2_REVERSE_TO_ECU      0x0002 //KW2取反发回
                    #define ES_ACP_KW1_REVERSE_TO_ECU      0x0001 //KW1取反发回
                  #define ES_ACP_MASK_BYTE_KW            0x000C //接收KW字数量掩码
                    #define ES_ACP_2_BYTE_KW               0x0004 //接收2个KW字, 接收KW最大等待时间500mS
                    #define ES_ACP_5_BYTE_KW               0x0008 //接收5个KW字, 接收KW最大等待时间2500mS
                  #define ES_ACP_RECEIVE_ADDRESS_REVERSE 0x0010 //接收地址码取反
                  #define ES_ACP_MASK_RECEIVE_FRAME      0x0060 //接收帧数量掩码
                    #define ES_ACP_ONE_FRAME               0x0020 //接收一帧数据
                    #define ES_ACP_MULTI_FRAME             0x0040 //接收多帧数据
                W_FLOAT fBps -- 波特率
                W_U16 uWaitTimeBeforSendAddress -- 发送地址码前高电平等待时间，缺省为400毫秒
                W_U16 u0x55OverTime -- 接收0x55的最大等待时间，缺省为300毫秒
                W_U16 uReceiveKwOverTime -- 接收KW的最大等待时间，缺省为20毫秒
                W_U16 uKw2ReverseWaitTime -- KW2取反发回时间，缺省为50毫秒
                W_U16 uReceiveReverseAddressOverTime -- 接收地址码超时最大等待时间，缺省为50毫秒
      返 回 值：无
      说    明：
    -----------------------------------------------------------------------------*/
    void AddressCodeMode (W_U8 uAddressCode,
                          W_U32 uParameter = ES_ACP_AUTO,
                          W_FLOAT fBps = 5,
                          W_U16 uWaitTimeBeforSendAddress = 400,
                          W_U16 u0x55OverTime = 300,
                          W_U16 uReceiveKwOverTime = 20,
                          W_U16 uKw2ReverseWaitTime = 50,
                          W_U16 uReceiveReverseAddressOverTime = 50
                        );

    /*-----------------------------------------------------------------------------
      功    能：快速进入方式
      参数说明：CSendFrame -- 发送帧
                W_I16 iLowTime -- 低电平时间，缺省25毫秒
                W_I16 iHighTime -- 高电平时间，缺省25毫秒
                W_I16 iWaitTime -- 电平拉低前的稳定时间，缺省300毫秒
      返 回 值：无
      说    明：
    -----------------------------------------------------------------------------*/
    void QuickEnterMode(CSendFrame SendFrame, W_I16 iLowVoltageTime = 25, W_I16 iHighVoltageTime = 25, W_I16 iWaitTime = 300);

    /*-----------------------------------------------------------------------------
      功    能：快速进入方式
      参数说明：W_U8 uTpTargetAddress -- TP目的地址
                W_U8 uAppLayerID -- 应用层协议ID，AL_KWP
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    void Tp20Mode(W_U8 ucTpTargetAddress, W_U8 ucAppLayerID = 1, W_U16 uReceptionID = 0);
    
    void Tp16Mode(PTP16PARAM pParam);

    /*-----------------------------------------------------------------------------
      功    能：地址码进入方式的构造函数
      参数说明：W_U8 uAddressCode -- 地址码
                W_U32 uParameter -- 进入参数
                    //ES_ACP_ Enter System  Address Code Parameter
                  #define ES_ACP_AUTO                    0xFFFFFFFF //全部自动识别，包括协议
                    ===========================================
                     KW1  KW2 | 协议
                    ----------+--------------------------------
                      01 8A   | KWP1281 -- KW2取反，收多帧
                      AB 03   | KWP1281
                      08 08   | ISO9141 -- KW2取反，地址码取反，不接收数据帧
                      94 94   | ISO9141
                     大于2000 | KWP2000 -- 同ISO9141
                              |
                      51 80   | K81 -- KW2取反，接收数据帧,ECU不停的回，直到打断
                      52 80   | K82 -- KW2取反，25~30mS内接收一帧数据，
                    ===========================================
                  #define ES_ACP_MASK_KW_REVERSE_TO_ECU    0x0003 //KW取反发回掩码
                    #define ES_ACP_KW2_REVERSE_TO_ECU      0x0002 //KW2取反发回
                    #define ES_ACP_KW1_REVERSE_TO_ECU      0x0001 //KW1取反发回
                  #define ES_ACP_MASK_BYTE_KW            0x000C //接收KW字数量掩码
                    #define ES_ACP_2_BYTE_KW               0x0004 //接收2个KW字, 接收KW最大等待时间500mS
                    #define ES_ACP_5_BYTE_KW               0x0008 //接收5个KW字, 接收KW最大等待时间2500mS
                  #define ES_ACP_RECEIVE_ADDRESS_REVERSE 0x0010 //接收地址码取反
                  #define ES_ACP_MASK_RECEIVE_FRAME      0x0060 //接收帧数量掩码
                    #define ES_ACP_ONE_FRAME               0x0020 //接收一帧数据
                    #define ES_ACP_MULTI_FRAME             0x0040 //接收多帧数据
                W_FLOAT fBps -- 波特率
                W_U16 uWaitTimeBeforSendAddress -- 发送地址码前高电平等待时间，缺省为400毫秒
                W_U16 u0x55OverTime -- 接收0x55的最大等待时间，缺省为300毫秒
                W_U16 uReceiveKwOverTime -- 接收KW的最大等待时间，缺省为20毫秒
                W_U16 uKw2ReverseWaitTime -- KW2取反发回时间，缺省为50毫秒
                W_U16 uReceiveReverseAddressOverTime -- 接收地址码超时最大等待时间，缺省为50毫秒
      返 回 值：无
      说    明：
    -----------------------------------------------------------------------------*/
    CEnterSystem (W_U8 uAddressCode,
                  W_U32 uParameter,
                  W_FLOAT fBps,
                  W_U16 uWaitTimeBeforSendAddress = 400,
                  W_U16 u0x55OverTime = 1000, //300,
                  W_U16 uReceiveKwOverTime = 500, //20,
                  W_U16 uKw2ReverseWaitTime = 500, //50,
                  W_U16 uReceiveReverseAddressOverTime = 50
                );

    /*-----------------------------------------------------------------------------
      功    能：快速进入方式的构造函数
      参数说明：CSendFrame -- 发送帧
                W_I16 iLowTime -- 低电平时间，缺省25毫秒
                W_I16 iHighTime -- 高电平时间，缺省25毫秒
                W_I16 iWaitTime -- 电平拉低前的稳定时间，缺省300毫秒
      返 回 值：无
      说    明：
    -----------------------------------------------------------------------------*/
    CEnterSystem(CSendFrame SendFrame, W_I16 iLowVoltageTime = 25, W_I16 iHighVoltageTime = 25, W_I16 iWaitTime = 300);

    /*-----------------------------------------------------------------------------
      功    能：TP20CAN进入方式的构造函数
      参数说明：W_U8 uTpTargetAddress -- TP目的地址
                W_U8 uAppLayerID -- 应用层协议ID，AL_KWP
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    CEnterSystem(W_U8 ucTpTargetAddress, W_U8 ucAppLayerID = 1, W_U16 uReceptionID = 0x0300);
	W_ErrorCode SetOpeningID(W_U16 uOpeningID);
	
    CEnterSystem(PTP16PARAM pParam);

    /*-----------------------------------------------------------------------------
      功    能：缺省构造函数
      参数说明：无
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    CEnterSystem();

    /*-----------------------------------------------------------------------------
      功    能：判断进入系统方式
      参数说明：方式字
      返 回 值：是否
      说    明：无
    -----------------------------------------------------------------------------*/
    bool IsMode(W_U16 uMode);

    /*-----------------------------------------------------------------------------
      功    能：取得进入系统方式字
      参数说明：无
      返 回 值：方式字
      说    明：无
    -----------------------------------------------------------------------------*/
    W_U16 GetMode();

    /*-----------------------------------------------------------------------------
      功    能：取得进入系统发送帧
      参数说明：无
      返 回 值：发送帧
      说    明：无
    -----------------------------------------------------------------------------*/
    CSendFrame GetSendFrame();

    /*-----------------------------------------------------------------------------
      功    能：取得进入系统参数
      参数说明：无
      返 回 值：进入系统参数
      说    明：无
    -----------------------------------------------------------------------------*/
    ENTER_PARAMETER* GetParameter();


	unsigned int m_uParameter;

  public:
    // 进入命令
    CSendFrame m_EnterSystemSendFrame;

    // 进入系统方式
    CEnterSystem::ENTER_MODE m_eEnterMode;

    // 进入参数
    CEnterSystem::ENTER_PARAMETER m_EnterParameter;

};



#endif /* ENTERSYSTEM_H_HEADER_INCLUDED_B97E151B */
