#ifndef ECUINTERFACE_H_HEADER_INCLUDED_B97E65A3
#define ECUINTERFACE_H_HEADER_INCLUDED_B97E65A3
#include "adsStd.h"
#include "Binary.h"
#include "EnterSystem.h"
#include "ReceiveFrame.h"
#include "SendFrame.h"
#include "FilterOrFrameDistinguish.h"
#include "MultiReceiveFrame.h"
#include "MultiSendFrame.h"
//#include "KeepLink.h"
#include "NetLayer.h"
#include "DS708ToJ2534Base.h"
#include <string>

#ifndef WIN32
#include "JniPublic.h"
using namespace JniPublic;
#include "public.h"
#endif

#define USE_J2534

//20150910 add by gongjiyue 增加识别连接方式返回参数对照 
#define	VCI_NONE		0	//没有连接
#define	VCI_USB			1   //USB连接方式
#define	VCI_BLUETOOTH	2   //蓝牙连接方式
#define	VCI_ETHERNET	3   //网络连接方式
#define	VCI_FIFO		4   //NamePipe连接方式

//20150910 add by gongjiyue 增加识别连接方式返回参数对照 
/******************************************************************************

    Copyright (c) 2008, AUTEL Ltd,.Co

    All rights reserved.

    文件名称：EcuInterface_ForDiagProg.h EcuInterface_ForDiagProg.cpp

    档 标 识：

    摘    要：供诊断程序员调用的ECU通信接口

              说明：在 Begin 和 End 之间调用ECU通信相关函数时，其返回值无意义

    用    途：模拟 MaxiDiag 函数调用的上位机通信程序

    历史记录：
    ---------------------------------------------------------------------------
     时     间    作者    版本号    操    作    内    容
    ---------------------------------------------------------------------------
	2012-12-01  余世均、潘相熙

*******************************************************************************/

class CEcuInterface
{
  public:
#ifdef WIN32
	  #define MyPrintf(...) TRACE(__VA_ARGS__)
#else
	  #define MyPrintf(...) LOGI(__VA_ARGS__)
#endif
	  virtual ERRORCODE SetFuncAddrFilter(vector<unsigned char>& vct_func_addr);

	  virtual ERRORCODE SetFuncAddrFilter(unsigned char FuncAddr);

	  virtual ERRORCODE SetNodeAddr(unsigned char NodeAddr);

	  virtual ERRORCODE ClearFuncAddrFilter();

/*-----------------------------------------------------------------------
 因 中国通用 2002 赛欧连发三次后，ECU便不再回数据
 发一帧或发两帧都可以

 而opel 1997 又必须发三次

------------------------------------------------------------------------*/

	void SetK8182EndFrameSendTimes(unsigned char Cnt);

	/*-----------------------------------------------------------------------------
      功    能：启动晶振
      参数说明：无
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    void SetPinClk(unsigned char pin);

	/*-----------------------------------------------------------------------------
      功    能：J2534暂停与恢复接口
      参数说明：无
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
	void EnableDevInterface(bool state);

	// 设置vci状态
	void SetVCIStatus(bool bVCIStatus);

	// 设置电池电压
	void SetBattVoltage(double dVoltage);

    /*-----------------------------------------------------------------------------
      功    能：取得通信协议ID
      参数说明：无
      返 回 值：通信协议ID
      说    明：无
    -----------------------------------------------------------------------------*/
    W_U16 GetProtocolId();

    /*-----------------------------------------------------------------------------
      功    能：初始化上下位机通信接口
      参数说明：无
      返 回 值：成功 -- false, 失败 -- true
      说    明：初始化上下位机通信成员对象，严禁诊断程序员调用
    -----------------------------------------------------------------------------*/
    bool Init();//外部调用
	bool InitMyself();// 仅通信库使用
	//bool GetVCIConnected();

    /*-----------------------------------------------------------------------------
      功    能：消毁上下位机通信使用资源
      参数说明：无
      返 回 值：无
      说    明：本函数在诊断程序框架中调用，严禁诊断程序员调用
    -----------------------------------------------------------------------------*/
    void Destroy();
	static void DeviceDisConnectd();// 设备已断开

	static unsigned long GetVCIInfoCommModel();



	// 设置链路层，仅ecuinterface本身使用
	bool SetProtocolBpsIo();

	void SetProtocolID(unsigned int uiProtocolID);

    /*-----------------------------------------------------------------------------
      功    能：进入系统
      参数说明：CSystemEnter SystemEnter进入系统参数
      返 回 值：进入系统接收帧
      说    明：无
    -----------------------------------------------------------------------------*/
    CReceiveFrame EnterSystem(CEnterSystem SystemEnter);

/*
    ST_VOLTAGE_HIGH_LOW -- 取得电平高低
    ST_VOLTAGE_VALUE    -- 取得电压值，单位:0.1 V
*/
    typedef enum tagStatusType
    {
        ST_VOLTAGE_HIGH_LOW = 0, // 电平高低
        ST_VOLTAGE_VALUE    = 1  // 电压值
    } StatusType;

    /*-----------------------------------------------------------------------------
      功    能：取得某引脚状态
      参数说明：W_U8 uIoPort – 引脚号
                StatusType eStatusWay 取值类型，缺省为ST_VOLTAGE_HIGH_LOW,即电平高低，
                    ST_VOLTAGE_HIGH_LOW -- 取得电平高低，返回值0表示低电平，非0表示高电平
                    ST_VOLTAGE_VALUE    -- 取得电压值，返回值单位:0.1 V
      返 回 值：电平或电压值
      说    明：无
    -----------------------------------------------------------------------------*/
    W_I16 GetStatus(W_U8 ucIoPort, StatusType eStatusWay = ST_VOLTAGE_HIGH_LOW);

    /*-----------------------------------------------------------------------------
          功    能：设置/取消下位机固定链路保持
          参数说明：W_INT16 iKeepTime – 链路保持时间间隔
                    CSendFrame KeepLinkFrame -- 链路保持帧，缺省为CSendFrame ()
          返 回 值：错误代码
          说    明：如链路保持时间为0，则取消链路保持
    -----------------------------------------------------------------------------*/
    W_ErrorCode SalveFixedKeepLink(W_I16 iKeepTime, CSendFrame KeepLinkFrame  = CSendFrame());
    
    /*-----------------------------------------------------------------------------
      功    能：设置/取消链路保持
      参数说明：W_INT16 iKeepTime – 链路保持时间间隔
                CSendFrame KeepLinkFrame -- 链路保持帧，缺省为CSendFrame ()
      返 回 值：错误代码
      说    明：如链路保持时间为0，或发送帧内容为空白，则取消链路保持
    -----------------------------------------------------------------------------*/
    W_ErrorCode KeepLink(W_I16 iKeepTime, CSendFrame KeepLinkFrame = CSendFrame());

    /*-----------------------------------------------------------------------------
    功    能：发一帧收一帧
    参数说明：CBinary binSendCmd – 发送给ECU命令
    返 回 值：ECU回复的一帧数据
    说    明：无
    -----------------------------------------------------------------------------*/
    CBinary SendReceive(CBinary binSendCmd);

    /*-----------------------------------------------------------------------------
    功    能：发一帧收一帧或多帧（0帧）
    参数说明：CSendFrame SendFrame – 发送帧
    返 回 值：接收帧
    说    明：无
    -----------------------------------------------------------------------------*/
    CReceiveFrame SendReceive(CSendFrame SendFrame);

    /*-----------------------------------------------------------------------------
    功    能：发多帧收多帧
    参数说明：CMultiSendFrame MultiSendFrame – 多发送帧
	          bAllSendThenRev 一次性全发出去然后再收,默认为false发一帧收n帧再发一帧收n帧
    返 回 值：多接收帧
    说    明：无
    -----------------------------------------------------------------------------*/
    CMultiReceiveFrame SendReceive(CMultiSendFrame MultiSendFrame);

    /*
        PB_NONE  -- 无校验
        PB_EVEN  -- 偶校验
        PB_ODD   -- 奇校验
    */
    typedef enum tagPartyBit
    {
        PB_NONE  = 0x00,    //无校验
        PB_ODD   = 0x01,    //奇校验
        PB_EVEN  = 0x02,    //偶校验
        PB_9D    = 0x03    //9位数据模式   潘相熙 2009-10-30 
//        PB_MASK  = 0x03,  //1校验
//        PB_SPACE = 0x04   //0校验
    } PARTY_BIT;

    #define CAN_BPS___15625     15625.0
    #define CAN_BPS___33333     33333.3
    #define CAN_BPS___50000     50000.0
    #define CAN_BPS___83333     83333.3
    #define CAN_BPS__100000     100000.0
    #define CAN_BPS__125000     125000.0
    #define CAN_BPS__250000     250000.0
    #define CAN_BPS__500000     500000.0
    #define CAN_BPS_1000000     1000000.0
    /*-----------------------------------------------------------------------------
      功    能：延时功能
      参数说明：W_FLOAT fBps – 波特率
                  目前CAN协议仅支持如下波特率：
                      CAN_BPS___15625
                      CAN_BPS___33333
                      CAN_BPS___83333
                      CAN_BPS__100000
                      CAN_BPS__125000
                      CAN_BPS__250000
                      CAN_BPS__500000
                      CAN_BPS_1000000
                W_U32 uParameter – 通信相关参数
                  校验位：
                     #define PB_NONE       0x00 //无校验
                     #define PB_EVEN       0x02 //偶校验
                     #define PB_ODD        0x01 //奇校验
                     #define PB_MASK       0x03 //1校验
                     #define PB_SPACE      0x04 //0校验
      返 回 值：错误代码
      说    明：数据位数为8位，必要时再加入一个数据位数参数
                上下位机通信协议中将PARTY_BIT规定为W_U8格式
    -----------------------------------------------------------------------------*/
    W_ErrorCode SetBps(W_FLOAT fBps, PARTY_BIT ePartyBit = PB_NONE);

    /*-----------------------------------------------------------------------------
    功    能：设置ECU通信时间参数
    参数说明：W_FLOAT fReceiveMaxByte2ByteInterval_P1 接收帧字节间最大间隔时间
              W_FLOAT fReceiveFrameMaxWaitTime_P2  -- 接收帧最大等待时间
              W_FLOAT fSendFrameInterval_P3 -- 发送帧时间间隔
              W_FLOAT fSendByte2Byte_P4 -- 发送帧字节间间隔
              W_FLOAT fReceivePacketOverTime -- 接收数据包超时时间;
      返 回 值：错误代码
      说    明：单位：毫秒
                将上下位机通信包超时时间设为比包超时时间大500ms
    -----------------------------------------------------------------------------*/
    W_ErrorCode SetCommTime (W_FLOAT fReceiveMaxByte2ByteInterval_P1,
                             W_FLOAT fReceiveFrameMaxWaitTime_P2,
                             W_FLOAT fSendFrameInterval_P3,
                             W_FLOAT fSendByte2Byte_P4,
                             W_FLOAT fReceivePacketOverTime = -1
                            );


	/*-----------------------------------------------------------------------------
	功    能：使能TP20CAN的定时连路保持
	参    数：bool true:enable,false Disable
	返 回 值：TRUE:succees,FALSE: failure
	说    明：无
	-----------------------------------------------------------------------------*/
	bool Tp20CanLinkKeepEnable(bool bFlag);    //Genbay added on 2009-01-21

	/*-----------------------------------------------------------------------------
	功    能：使能串口中断用来接收
	参    数：bool true:enable,false Disable
	返 回 值：TRUE:succees,FALSE: failure
	说    明：下位机默认为不使用
	-----------------------------------------------------------------------------*/
	bool UARTInterruptEnable(bool bFlag);    //潘相熙added on 2009-7-22



	/*-----------------------------------------------------------------------------
	功    能：链路按固定时间发，只要时间到就发
	参    数：bool true:enable,false Disable
	返 回 值：TRUE:succees,FALSE: failure
	说    明：下位机默认为false
	-----------------------------------------------------------------------------*/
	bool LinkFixedEnable(bool bFlag);    //潘相熙added on 2009-7-22


	bool VolvoSetFormatByte(bool bEnable, unsigned char ucFormatByte);


    /***********************************************************
    *函数名:		long CEcuInterface::SetIso15765FramePad(unsigned char eSetIso15765FramePad)
    *功能:		    设置ISO15765数据强制填充模式
    *输入值:		bSetIso15765FramePad: 0-非强制填充模式；1-强制填充模式，填充字节为0xFF;
                                            2-强制填充模式，填充字节为0x00;
    *返回值:      	long:0-设置成功;1-参数不在有效范围内；
    *作者:		    GAZER
    *创建日期:	    2016.12.20
    *备注:          该接口用于解决在奔驰中发送空帧后立马切换过滤ID时，填充字节的异常问题
    ************************************************************/
    long SetIso15765FramePad(unsigned char eSetIso15765FramePad);

    /***********************************************************
    *函数名:        long CEcuInterface::SetKwpFilter(unsigned int KwpFilterMode,CBinary binKwpFilter)
    *功能:          设置Kwp的过滤器模式与过滤器内容
    *输入值:        KwpFilterMode--过滤器模式:  0-通用模式，所有数据不过滤全部接受，第二输入参数可不填，使用默认值;
                                                1-清除所有，清除前面的过滤器设置，第二输入参数可不填，使用默认值;
                                                2-特殊过滤模式，不论帧长度字节(首字节)，以第2、3字节作过滤;
                                                3-特殊过滤模式，不论帧长度字节(首字节)，以第2个字节作过滤;
                    binKwpFilter--过滤器内容;
    *返回值:        long:0-设置成功;1-设置失败;
    *作者:          GAZER
    *创建日期:      2017.01.11
    *备注:          所用数据全部接受:SetKwpFilter(0),该模式为默认模式，不设置也可自动进入；
                    清除前面过滤器设置:SetKwpFilter(1);
                    以第2、3字节作过滤:SetKwpFilter(1,CBinary("\xXX\xXX\xXX",3));
    ************************************************************/
    long SetKwpFilter(unsigned int KwpFilterMode,CBinary binKwpFilter=CBinary("\x00",1));

    enum tagISO15765SpecialFrameFormat
    {
    	NORMAL_FRAME_FORMATE_FLAG          = 0,//普通模式
    	SPECIAL_FRAME_FORMATE_FLAG         = 1,//标准单报文
    };

   /***********************************************************
    *函数名:	    long CEcuInterface::SetIso15765SpecialKeepLinkFrameFormat(int flag)
    *功能:		    设置ISO15765的链路保持帧为特殊的模式的帧(CAN_SINGLE_CANBUS)
    *输入值:	    flag:tagISO15765SpecialFrameFormat中定义的枚举值
    *返回值:         long:0-设置成功，固定返回成功...
    *作者:		    甘旗
    *创建日期:   [2016-12-30]
    *备注:              当flag为SPECIAL_FRAME_FORMATE_FLAG时，链路保持发送的帧为标准单报文(CAN_SINGLE_CANBUS)
    该函数只设置链路保持的帧，正常发送的数据的帧不会被设置的，正常发送的帧要切换可以
    使用SetCanDataFormat函数。
             注意:当链路保持帧设置为了此模式后在没有进行重新连接的情况下又要改为发送普通模式的
    帧时一定要切换回去(SetIso15765SpecialKeepLinkFrameFormat(NORMAL_FRAME_FORMATE_FLAG));否则的话就还是发送的是
    特殊模式的帧。
    ************************************************************/
    long SetIso15765SpecialKeepLinkFrameFormat(int flag);

	enum tagProtocolPin
	{
		K_LINE          = 0x00,
		CAN_PIN         = 0x10,
		SINGLE_CAN_PIN  = 0x20,
		PWM_PIN         = 0x30,
		VPW_PIN         = 0x40,
		CCD_PIN         = 0x50,
		J1939_PIN		= 0x60,//
		J1708_PIN		= 0x70,
		PROTOCOL_PIN_MASK = 0xF0 //协议类型掩码
	};


	// OBDII对应关系：
	typedef enum tagODBII_PIN
	{
		// 此部分用于K线通信
		OBD2_PIN1             = 0x01,
		OBD2_PIN2             = 0x02,
		OBD2_PIN3             = 0x03,
		OBD2_PIN6             = 0x06,
		OBD2_PIN7             = 0x07,
		OBD2_PIN8             = 0x08,
		OBD2_PIN9             = 0x09,
		OBD2_PIN10            = 0x0A,
		OBD2_PIN11            = 0x0B,
		OBD2_PIN12            = 0x0C,
		OBD2_PIN13            = 0x0D,
		OBD2_PIN14            = 0x0E,
		OBD2_PIN15            = 0x0F,
		OBD2_PIN16            = 0x10,// 2013-08-05为取电压

		// 此部分用于J1850通信
		OBD2_PWM              = 0x020A | PWM_PIN,
		OBD2_VPW              = 0x0200 | VPW_PIN,

		// 此部分用于CCD通信
		OBD2_CCD              = OBD2_PIN15,

		// 此部分用于CAN通信
		OBD2_CAN_PIN1_9       = 0x0109 | CAN_PIN,
		OBD2_CAN_PIN2_10      = 0x020a | CAN_PIN,
		OBD2_CAN_PIN3_11      = 0x030b | CAN_PIN,
		OBD2_CAN_PIN6_14      = 0x060e | CAN_PIN,
		OBD2_CAN_PIN3_8       = 0x0308 | CAN_PIN,
		OBD2_CAN_PIN13_12     = 0x0d0c | CAN_PIN,
		OBD2_CAN_PIN12_13     = 0x0C0D | CAN_PIN,

		OBD2_SINGLE_CAN_PIN1  = 0x0100 | SINGLE_CAN_PIN,

		OBD2_J1939_PIN_3_4	  = 0x0304 | J1939_PIN,
		OBD2_J1939_PIN_6_7    = 0x0607 | J1939_PIN,

		OBD2_J1708_PIN_1_2    = 0x0102 | J1708_PIN,
	} OBDII_PIN;



	// 潘相熙添加2009-06-22 start 高4位为0x80或0x90或0xa0需控制单片机选线
#define DF_38PIN_11_20		0x80
#define DF_38PIN_21_30		0x90
#define DF_38PIN_31_38		0xA0
	typedef enum tagBENZ38_PIN
	{
		// 1-10
		BENZ38_PIN2             = OBD2_PIN8,		// 直连 2009-07-28 添加
		BENZ38_PIN4             = OBD2_PIN14,		// 直连
		BENZ38_PIN5             = OBD2_PIN15,		// 直连
		BENZ38_PIN6             = OBD2_PIN6,		// 直连
		BENZ38_PIN7             = OBD2_PIN7,		// 直连
		//BENZ38_PIN8             = DB15_PIN8,		// 直连
		BENZ38_PIN8             = (((W_U8)0x02)|((W_U8)DF_38PIN_11_20)),// 直连
		BENZ38_PIN10            = OBD2_PIN1,		// 直连

		// 11-20 如需控制接头单片机,高位为0x80
		BENZ38_PIN11            = (((W_U8)0x01)|((W_U8)DF_38PIN_11_20)),
		BENZ38_PIN12            = OBD2_PIN12,
		BENZ38_PIN13            = (((W_U8)0x03)|((W_U8)DF_38PIN_11_20)),
		BENZ38_PIN14            = (((W_U8)0x04)|((W_U8)DF_38PIN_11_20)),
		BENZ38_PIN15            = OBD2_PIN13,
		BENZ38_PIN16            = (((W_U8)0x06)|((W_U8)DF_38PIN_11_20)),
		BENZ38_PIN17            = (((W_U8)0x07)|((W_U8)DF_38PIN_11_20)),
		BENZ38_PIN18            = (((W_U8)0x08)|((W_U8)DF_38PIN_11_20)),
		BENZ38_PIN19            = (((W_U8)0x09)|((W_U8)DF_38PIN_11_20)),
		BENZ38_PIN20            = OBD2_PIN2,

		// 21-30 如需控制接头单片机,高位为0x90
		BENZ38_PIN21            = (((W_U8)0x01)|((W_U8)DF_38PIN_21_30)),
		BENZ38_PIN22            = (((W_U8)0x02)|((W_U8)DF_38PIN_21_30)),                  
		BENZ38_PIN23            = (((W_U8)0x03)|((W_U8)DF_38PIN_21_30)),
		BENZ38_PIN24            = (((W_U8)0x04)|((W_U8)DF_38PIN_21_30)),
		BENZ38_PIN25            = (((W_U8)0x05)|((W_U8)DF_38PIN_21_30)),                 
		BENZ38_PIN26            = (((W_U8)0x06)|((W_U8)DF_38PIN_21_30)),
		BENZ38_PIN27            = (((W_U8)0x07)|((W_U8)DF_38PIN_21_30)),
		BENZ38_PIN28            = (((W_U8)0x08)|((W_U8)DF_38PIN_21_30)),
		BENZ38_PIN29            = (((W_U8)0x09)|((W_U8)DF_38PIN_21_30)),
		BENZ38_PIN30            = OBD2_PIN3,    

		// 31-38 如需控制接头单片机,高位为0xA0
		BENZ38_PIN31            = (((W_U8)0x01)|((W_U8)DF_38PIN_31_38)),
		BENZ38_PIN32            = (((W_U8)0x02)|((W_U8)DF_38PIN_31_38)),                  
		BENZ38_PIN33            = (((W_U8)0x03)|((W_U8)DF_38PIN_31_38)),
		BENZ38_PIN34            = (((W_U8)0x04)|((W_U8)DF_38PIN_31_38)),
		BENZ38_PIN35            = (((W_U8)0x05)|((W_U8)DF_38PIN_31_38)),                 
		BENZ38_PIN36            = (((W_U8)0x06)|((W_U8)DF_38PIN_31_38)),
		BENZ38_PIN37            = (((W_U8)0x07)|((W_U8)DF_38PIN_31_38)),
		BENZ38_PIN38            = (((W_U8)0x08)|((W_U8)DF_38PIN_31_38)),

		BENZ38_PIN9            = (((W_U8)0x09)|((W_U8)DF_38PIN_31_38))


	} BENZ38_PIN;
	// 潘相熙添加2009-06-22 end


   /*-----------------------------------------------------------------------------
       功    能：设置通信端口
       参数说明：
                 W_UINT16 iIoInputPort – 输入引脚    仅用低位字节
                 W_UINT16 iIoOutputPort – 输出引脚;
                      低位字节：主通信线，
                      高位字节：辅助通信线不使用则空白；
                        可使用：MAKE_UINT16 (HIBYTE, LOBYTE)合并；如K线通信–K线使用低字节，L触发则
                      高字节存放L线IO引脚号
                         DB15 PIN DEFINE
                            DB15_PIN1
                            DB15_PIN2
                            DB15_PIN3
                            DB15_PIN5
                            DB15_PIN6
                            DB15_PIN7
                            DB15_PIN8
                            DB15_PIN9
                            DB15_PIN10
                            DB15_PIN11
                            DB15_PIN12
                            DB15_PIN13
                            DB15_PIN14
                            BD15_PWM
                            BD15_VPW
                            BD15_CCD

                          OBD PIN DEFINE
                            OBD2_PIN1             = DB15_PIN1,
                            OBD2_PIN2             = DB15_PIN2,
                            OBD2_PIN3             = DB15_PIN3,
                            OBD2_PIN6             = DB15_PIN6,
                            OBD2_PIN7             = DB15_PIN7,
                            OBD2_PIN8             = DB15_PIN8,
                            OBD2_PIN9             = DB15_PIN9,
                            OBD2_PIN10            = DB15_PIN10,
                            OBD2_PIN11            = DB15_PIN11,
                            OBD2_PIN12            = DB15_PIN12,
                            OBD2_PIN13            = DB15_PIN13,
                            OBD2_PIN14            = DB15_PIN14,
                            OBD2_PIN15            = DB15_PIN5,

                            OBD2_PWM              = DB15_PWM,
                            OBD2_VPW              = DB15_VPW,

                            OBD2_CAN_PIN1_9       = (DB15_PIN1|((W_U8)0x10)),
                            OBD2_CAN_PIN2_10      = (DB15_PIN2|((W_U8)0x10)),
                            OBD2_CAN_PIN3_11      = (DB15_PIN3|((W_U8)0x10)),
                            OBD2_CAN_PIN6_14      = (DB15_PIN6|((W_U8)0x10)),
                            OBD2_CAN_PIN3_8       = (DB15_PIN8|((W_U8)0x10)),
                            OBD2_CAN_PIN13_12     = (DB15_PIN13|((W_U8)0x10)),

                            OBD2_SINGLE_CAN_PIN1  = (DB15_PIN1|((W_U8)0x20)),
                            OBD2_SINGLE_CAN_PIN2  = (DB15_PIN2|((W_U8)0x20)),
                            OBD2_SINGLE_CAN_PIN3  = (DB15_PIN3|((W_U8)0x20)),
                            OBD2_SINGLE_CAN_PIN6  = (DB15_PIN6|((W_U8)0x20)),
                            OBD2_SINGLE_CAN_PIN7  = (DB15_PIN7|((W_U8)0x20)),
                            OBD2_SINGLE_CAN_PIN8  = (DB15_PIN8|((W_U8)0x20)),
                            OBD2_SINGLE_CAN_PIN9  = (DB15_PIN9|((W_U8)0x20)),
                            OBD2_SINGLE_CAN_PIN10 = (DB15_PIN10|((W_U8)0x20)),
                            OBD2_SINGLE_CAN_PIN11 = (DB15_PIN11|((W_U8)0x20)),
                            OBD2_SINGLE_CAN_PIN12 = (DB15_PIN12|((W_U8)0x20)),
                            OBD2_SINGLE_CAN_PIN13 = (DB15_PIN13|((W_U8)0x20)),
                            OBD2_SINGLE_CAN_PIN14 = (DB15_PIN14|((W_U8)0x20))

                   W_INT8 iOutputVoltage 工作电压，缺省：K线通信为12V。
                   W_U32 uParameter – 通信参数 缺省正逻辑输入输出，L线信号与K线同步,
                         即: IOP_L_EQ_K|IOP_INPUT_POSITIVE_LOGIC|IOP_OUTPUT_POSITIVE_LOGIC
                            #define IOP_SAME_SIGNAL_MAIN_AND_ASSIST_LINE    0x01 //L线与K线信号相同
                            #define IOP_INPUT_POSITIVE_LOGIC                0x02 //输入正逻辑
                            #define IOP_OUTPUT_POSITIVE_LOGIC               0x04 //输出正逻辑
                            #define IOP_OUTPUT_REVERSE                      0x08 //输出取反

       返 回 值：错误代码
       说    明：一.  对IO为 CAN, SIGNLE CAN, PWM, VPW, CCD
                  1. 忽略参数W_U8 ucWorkVoltage和W_U32 uParameter;
                  2. 输入/输入必须是同个IO值, 输出的高字节必须空白(0)
                 二. 对K线通信情况
                  1.
    -----------------------------------------------------------------------------*/
    W_ErrorCode SetIoPort (W_U8 ucIoInputPort,
                           W_U16 uIoOutputPort,
                           W_U8 ucWorkVoltage = 12,
                           W_U32 uParameter = IOP_SAME_SIGNAL_MAIN_AND_ASSIST_LINE|IOP_INPUT_POSITIVE_LOGIC|IOP_OUTPUT_POSITIVE_LOGIC,
						   W_FLOAT fCompareVoltage = 0.0
                          );

   /*-----------------------------------------------------------------------------
      功    能：设置输出电平
      参数说明：bool bIsHighVoltage 输出电平否;
                    true -- 输出高电平
                    fasle -- 输出低电平
      返 回 值：无
      说    明：与SetIoPort()设定的输出引脚相关，如无辅助通信线，则设置为主输出引
                脚电平；否则如输出相同则同时变化，不同则仅辅助通信线改变
    -----------------------------------------------------------------------------*/
    void SetOutputVoltage(bool bIsHighVoltage);


 /*
        PT_NORMAL  -- 一般K/L线通信协议
        PT_KWP     -- KWP协议
        PT_ISO     -- ISO协议
        PT_CAN     -- CAN协议
        PT_1281    -- KWP1281协议
        PT_Tp20Can -- TP20协议
        PT_PWM     -- PWM协议
        PT_VPW     -- VPW协议
        PT_CCD     -- CCD协议
        PT_NISSAN_OLD -- 日产老协议
*/
    typedef enum tagProtocol
    {
#ifdef INCLUDE_LINK_NORMAL
        PT_NORMAL  = 0x0001,
#endif
#ifdef INCLUDE_LINK_KWP
        PT_KWP     = 0x0002,
#endif
#ifdef INCLUDE_LINK_ISO
        PT_ISO     = 0x0003,
#endif
#ifdef INCLUDE_LINK_CAN
        PT_CAN     = 0x0004,
#endif
#ifdef INCLUDE_LINK_BOSCH
        PT_1281    = 0x0005,
#endif
#ifdef INCLUDE_LINK_TP20
        PT_Tp20Can = 0x0006,
#endif
#ifdef INCLUDE_LINK_PWM
        PT_PWM     = 0x0007,
#endif
#ifdef INCLUDE_LINK_VPW
        PT_VPW     = 0x0008,
#endif
#ifdef INCLUDE_LINK_CCD
        PT_CCD     = 0x0009,
#endif
#ifdef INCLUDE_LINK_NISSAN_OLD
        PT_NISSAN_OLD = 0x000A,
#endif
#ifdef INCLUDE_LINK_VOLVO_CAN
        PT_VOLVO_CAN = 0x000B,
#endif
        PT_KW81_KW82 = 0x000C,
        PT_RTMDPLUS  = 0x000D,// 潘相熙 2009-10-30添加
        PT_SCI       = 0x000E,// 潘相熙 2010-03-26添加
        PT_GMLAN_CAN = 0x000F,// 潘相熙 2010-07-06添加
        PT_ALDL      = 0x0010,
        PT_ALDLGM  = 0x0011,//潘相熙 2010-01-20添加
        PT_Tp16Can  = 0x0012,
        PT_FLASH	= 0x0013,
        PT_NANYUE_CAN= 0x0014,// 李卓慧 2015-11-04
        PT_J1708     = 0x0015,// 李卓慧 2015-11-12
        PT_J1939	 = 0x0016,// 李卓慧 2015-11-14
        PT_HinoBosch = 0x0017,// 李卓慧 2015-11-21
        PT_CummisJ1939	 = 0x0018,// 李卓慧 2015-11-25
        PT_DelphiCan	 = 0x0019,// 李卓慧 2015-11-25
        PT_J1708CAT	 = 0x001A,// 瞿松松2016-3-5
        PT_J1708WEBCO15765 = 0x001B,// 瞿松松2016-3-5
        PT_J1708MAXXFORCE =     0x001C,// 瞿松松
        PT_NOSTD_KLINE			=0x001F	,  //GAZER 2016-07-189
        
        __PT_END__   = 0x0020
    } ProtocolType;

    /*-----------------------------------------------------------------------------
      功    能：设置ECU通信协议
      参数说明：W_U16 uProtocolType -- 协议类型
                CFilterOrFrameDistinguish FilterOrFrameDistinguish -- 过滤条件或帧长识别方法
      返 回 值：错误代码
      说    明：无
    -----------------------------------------------------------------------------*/
    W_ErrorCode SetProtocol(ProtocolType eProtocolType, CFilterOrFrameDistinguish FilterOrFrameDistinguish = CFilterOrFrameDistinguish());

    /*-----------------------------------------------------------------------------
      功    能：延时功能
      参数说明：fTime                       延时时间，单位：毫秒
      返 回 值：无
      说    明：延时时间结束后返回
    -----------------------------------------------------------------------------*/
    void Sleep(W_FLOAT fTime);

    /*-----------------------------------------------------------------------------
      功    能：设置单报文对象帧的CAN ID
      参    数：ulTxCanId                   单报文对象发送帧CAN ID
                ulRxCanId                   单报文对象接收帧CAN ID
      返 回 值：
      说    明：本函数用于某些非标准CAN协议的一帧为固定一个报文对象的帧接收，如不再
                需此ID，请将其设为0
    -----------------------------------------------------------------------------*/
    void SetSingleMsgFrmCanID(W_U32 ulTxCanId, W_U32 ulRxCanId);

    /*-----------------------------------------------------------------------------
      功    能：设置CAN 的发送数据格式
      参数说明：无
      返 回 值：无
      说    明：针对长安转向角等非标准的CAN格式设置
    -----------------------------------------------------------------------------*/
    void SetCanDataFormat(unsigned char DataFormat);

    /*-----------------------------------------------------------------------------
      功    能：设置CAN 的流控制模式
      参数说明：mode = 0   正常的流控制模式，0x07DF或者ECUID在0x07E8-0x07EF之间则流控制使用ECUID减8 
                                 mode = 0   0x07DF并且ECUID在0x07E8-0x07EF之间则流控制使用ECUID减8 
      返 回 值：无
      说    明：针对长安汽车
    -----------------------------------------------------------------------------*/
    void SetCanFlowCtrlMode(unsigned char mode);
		
    /*-----------------------------------------------------------------------------
      功    能：构造函数
      参数说明：无
      返 回 值：无
      说    明：分配通信必要资源
    -----------------------------------------------------------------------------*/
    CEcuInterface();

    /*-----------------------------------------------------------------------------
      功    能：析构函数
      参数说明：无
      返 回 值：无
      说    明：释放通信申请的资源
    -----------------------------------------------------------------------------*/
    virtual ~CEcuInterface();

    /*-----------------------------------------------------------------------------
      功    能：清不断接收模式时的缓冲区
      参    数：无
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    void ClearEcuReturnAlwaysBuffer();




	/*-----------------------------------------------------------------------------
	功    能：系统空闲时调用
	参    数：无
	返 回 值：无
	说    明：
	-----------------------------------------------------------------------------*/
	static void OnIdle();


protected:

    /*-----------------------------------------------------------------------------
      功    能：开始新的命令包
      参    数：无
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    void BeginCmdPacket();

    /*-----------------------------------------------------------------------------
      功    能：结束当前命令包后发送接收并定位回复包
	  参    数：无
	  返 回 值：是否成功
	  说    明：无
	  -----------------------------------------------------------------------------*/
	bool EndCmdPacketAndSendReceiveAndSeekRplPacket();



	typedef struct  tgConnect
	{
		// setprotocol
		ProtocolType eProtocolType;
		CFilterOrFrameDistinguish FilterOrFrameDistinguish;
		unsigned short usKeyWord;

		// setbps
		W_FLOAT fBps;
		PARTY_BIT ePartyBit;

		// setioport
		W_U8 ucIoInputPort;
		W_U16 uIoOutputPort;
		bool m_bUseSCI;// 双路通讯，需要使用SCI协议
		W_U8 ucWorkVoltage;
		W_U32 uParameter;// = IOP_SAME_SIGNAL_MAIN_AND_ASSIST_LINE|IOP_INPUT_POSITIVE_LOGIC|IOP_OUTPUT_POSITIVE_LOGIC,
		W_FLOAT fCompareVoltage;

		W_FLOAT fReceiveMaxByte2ByteInterval_P1;
		W_FLOAT fReceiveFrameMaxWaitTime_P2;
		W_FLOAT fSendFrameInterval_P3;
		W_FLOAT fSendByte2Byte_P4;
		W_FLOAT fReceivePacketOverTime;
		vector<unsigned char> vecFuncAddrs;
		unsigned char ucNodeAddr;

		vector<SCONFIG> vctTiming;

		unsigned long ulPacketTimeout;
		unsigned short iMax7F78;
		unsigned int ulTxCanId;
		unsigned int  ulRxCanId;
		unsigned char ucCFByte;// 仅为菲亚特使用，初始化为0x21
		bool m_bLinkFixedEnable;
		unsigned char ucIoVolPin;
		CBinary binJ1939ProtectAddr;
		unsigned char uCandataformat;
		unsigned char uCanFlowCtrlMode; //20160711 quss 因国产车长安流控制帧不需要将bit3置0
		unsigned char uTP20SpecialT3; //20160814 quss 
		unsigned int ulIso15765FlowControlDelayUs; /*2016-12-29 lhq 现代某进口车流控制发送延时需要设置为4ms,此变量提供接口工诊断应用设置*/
		unsigned int ulISO15765SpecialBpsFlag;//解决奇瑞->瑞麒发送50K标准CAN的需求(平台维护流水单号:ZDPT201612080007)---甘旗20161212
		unsigned int ulISO15765BpsValue;//解决奇瑞->瑞麒发送50K标准CAN的需求(平台维护流水单号:ZDPT201612080007)---甘旗20161212
		unsigned int uKeepLinkMode; // 20161228 quss  单报文链路保持标志
	}DF_CONNECT;



public:
	static bool m_bWantToConnect;				  // 是否需要连接，因原来有三个函数，所以需要先存起来，发数据时再打开通路
	static DF_CONNECT m_connectPara;			  // 连接参数
	static CDS708ToJ2534Base *m_pDS708ToJ2534Base;// 指向转换层
	static int m_iConnectIndex;					//重复进入声明时，只有为0时释放 2016-04-11


	//static PDEVICE_MANAGER m_pJ2534Device;		// 指向打开的设备
	//static unsigned long m_uiChanelID;			// 通道ID
	//static unsigned long m_uiProtocolID;		// 协议ID
	//int GetProtocolId();

	// 2008.9.17
	static CMultiSendFrame m_MultiSendFrame;
	typedef  void (*fpCallBackFunction)(const CMultiSendFrame *, const CMultiReceiveFrame *);

	static fpCallBackFunction m_fpCallBackOnFinishCommWithEcu;

public:
	/*-----------------------------------------------------------------------------
	功    能：设置保存通信数据回调函数
	参    数：回调函数指针
	返 回 值：无
	说    明：回调函数执行返回后，函数指针的传入参数即失效
	-----------------------------------------------------------------------------*/
	void SetCallBackAfterCommWithEcu(fpCallBackFunction fpCallBack);

	W_ErrorCode Set7f78MaxReceiveNumber(W_I16 iMaxNumber);
	W_ErrorCode Set7f21MaxReceiveNumber(W_I16 iMaxNumber);

	bool SetCanCFByte(unsigned char ucCFByte);// 设置连续帧起始地址

	long SetConfig(vector<SCONFIG> &ParamConfig);
	/*-----------------------------------------------------------------------------
	函数名:void SetIoStatu(W_U8 ucIoInputPort, unsigned char ucHigh)
	功    能：设置引脚的电压和状态值
	参    数：ucIoInputPort:设置的引脚号;ucHigh:设置的电压值或者状态参数值，详细见说明
	返 回 值：void
	修改:甘旗---[2017-05-06]
	说    明：对ucHigh的参数的说明:调用之前先要分清操作的是哪个引脚，对1,2,9,12,15这些脚的操作与
	其它引脚的操作是不一样的(这个是OBD芯片硬件决定的，反正底层配置不一样，所以这里也要分开说明一下)。

	对于1,2,9,12,15引脚:
        	当ucHigh>=5(5V为界是因为把他作为一个设置有效电压的下限值)的情况:
        	    此时ucHigh的值就是设置的引脚的电压值，比如SetIoStatu(7, 12);就是设置7号脚的电压值为12V。
        	当ucHigh<5的情况:此时这个值如果当做电压的话显然太低，所以就当做状态位来使用了:
        	    ucHigh=0:拉低引脚，比如SetIoStatu(7, 0);表示将7号脚拉低。
        	    ucHigh=1:拉高引脚，比如SetIoStatu(7, 1);表示将7号脚拉高。

       当引脚为非1,2,9,12,15号脚时:
             ucHigh = -3(0xfd):拉低引脚:比如SetIoStatu(13, -3); 表示将13号脚拉低。
             ucHigh = -4(0xfd):拉低引脚:比如SetIoStatu(13, -4); 表示将13号脚拉高。
	      ucHigh = -5(0xfd):拉低引脚:比如SetIoStatu(13, -5); 表示将13号脚复原(复原就是之前设置了拉高/低后需要还原回去)。
	-----------------------------------------------------------------------------*/
	void SetIoStatu(W_U8 ucIoInputPort, unsigned char ucHigh);

	void AutoSetLinkLayer(const unsigned char *pucKw, unsigned int &uParameter, float fBps, bool &bWantToReEnter/*是否需要重进，调用时请给false*/);
#ifdef USE_SIMULATOR		// 仅在模拟工装下使用
	bool SetComPort(int iPort);
#endif

	void SetBenz38Pin(W_U8 ucPin);  // 将 Benz38接头的ucPin管脚 与 DB15中的第11脚 连接起来


	/*-----------------------------------------------------------------------------
	功    能：J1939 专用接口
	参    数：
	返 回 值：
	说    明：
	-----------------------------------------------------------------------------*/
	vector<unsigned long> GetNotExitPgn(void);

	/*-----------------------------------------------------------------------------
	功    能：J1939 专用接口,设置保护地址
	参    数：
	返 回 值：
	说    明：
	-----------------------------------------------------------------------------*/
	W_ErrorCode SetJ1939ProtectAddr(CBinary Addr);

	/*-----------------------------------------------------------------------------
	功    能：J1939 J1708  专用接口,开始监控特定PGN, StopMonitor(void)停止监控, 
	参    数：
	返 回 值：
	说    明：
	-----------------------------------------------------------------------------*/
	void StartMonitor(map<unsigned long, CMonitorPara> CMonitorParameter);


	/*-----------------------------------------------------------------------------
	功    能：J1939 J1708 专用接口,开始监控所有PGN, StopMonitor(void)停止监控, 
				或是设定的超时时间到了,也会停止监控.

	参    数：
	返 回 值：
	说    明：
	-----------------------------------------------------------------------------*/
	void StartMonitor(void);

    
    bool StopMonitor(void);


	/*-----------------------------------------------------------------------------
	功    能：J1939 J1708 专用接口,获取已监控到的PGN个数
	参    数：
	返 回 值：
	说    明：
	-----------------------------------------------------------------------------*/
	unsigned long GetMonitorDataSize(void);

	/*-----------------------------------------------------------------------------
	功    能：J1939 J1708 专用接口,获取已监控到的PGN数据
	参    数：
	返 回 值：无
	说    明：
	-----------------------------------------------------------------------------*/
	CReceiveFrame GetMonitorData(void);

	/*-----------------------------------------------------------------------------
	功    能：J1939 J1708 专用接口,获取监控PGN状态，1：正在监控， 0：所有PGN都已遍历完
	参    数：
	返 回 值：无
	说    明：
	-----------------------------------------------------------------------------*/
	unsigned long GetMonitorState(void);

	
	/*-----------------------------------------------------------------------------
	功    能：J1939 J1708 专用接口,获取未完成PGN
	参    数：
	返 回 值：无
	说    明：
	-----------------------------------------------------------------------------*/
	map<unsigned long, CMonitorPara> GetRemainPgn(void);
	

	/*-----------------------------------------------------------------------------
	功    能：J1939 J1708 专用接口,清空监控缓冲
	参    数：
	返 回 值：无
	说    明：
	-----------------------------------------------------------------------------*/
	void ClearMonitorData(void);

	/*-----------------------------------------------------------------------------
	功    能：J1708 专用接口, 设置MODE
	参    数：
	返 回 值：无
	说    明：
	-----------------------------------------------------------------------------*/
	void SetMode(int mode);
	

	/*-----------------------------------------------------------------------------
	功    能：J1708 专用接口, 获取链路保持状态
	参    数：
	返 回 值：1:Err   0:正常
	说    明：
	-----------------------------------------------------------------------------*/
	int GetKeepLinkState(void);

        /**************************************************************************************************/
        //函数名: J1708SetKey
        //功能描述: 用来设置发送和接收的KEY，主要用来做过滤，发送KEY1，
        //                        接收的数据必须对应KEY2，目前主要是volvo需要用到
        //参数说明: key1 -- 请求KEY，和KEY2配对使用
        //                        key2 -- 应答KEY，和KEY1配对使用
        //                        flag -- 表示是否需要过滤PID。0-不需要过滤PID，1-需要过滤PID
        //返回: 无
        //作者: 瞿松松20160304
        /**************************************************************************************************/
        bool J1708SetKey(W_U8 Key1,W_U8 Key2, W_U8 flag);

        /**************************************************************************************************/
        //函数名: J1708SetKey
        //功能描述: 用来设置发送KEY，以区分webco的两种数据格式
        //参数说明: key1 -- 请求KEY
        //返回: 无
        //作者: 瞿松松20160304
        /**************************************************************************************************/
        void J1708SetKey(W_U8 Key1);

        /**************************************************************************************************/
        //函数名: J1708ClearKey
        //功能描述: 清除所有KEY设置
        //参数说明: 无
        //返回: 无
        //作者: 瞿松松20160304
        /**************************************************************************************************/
        void J1708ClearKey(void);
        
        /**************************************************************************************************/
        //函数名: J1708SetLength
        //功能描述: 通过此设置来确认是否存在长度字节
        //参数说明: status = 1 -- 存在长度域; 0 -- 不存在长度域
        //返回: 无
        //作者: 瞿松松20160304
        /**************************************************************************************************/
        void J1708SetLength(bool status);

        /**************************************************************************************************/
        //函数名: J1708CatSetAccessKey
        //功能描述: 用来设置发送和接收的KEY，主要用来做过滤，发送KEY1，
        //                        接收的数据必须对应KEY2
        //参数说明: key1 -- 请求KEY，和KEY2配对使用
        //                        key2 -- 应答KEY，和KEY1配对使用
        //                        flag -- 表示是否需要加密。
        //返回: 无
        //作者: 瞿松松20160307
        /**************************************************************************************************/
        bool J1708CatSetAccessKey(W_U8 Key1,W_U8 Key2, bool flag);

        /**************************************************************************************************/
        //函数名: J1708CatClearKey
        //功能描述: 清除所有KEY设置
        //参数说明: 无
        //返回: 无
        //作者: 瞿松松20160307
        /**************************************************************************************************/
        void J1708CatClearKey(void);

        /**************************************************************************************************/
        //函数名: AddEnterSystemCount
        //功能描述:记录进入系统的次数.目前主要应用在商用车上，应商用车
        //                      存在动态库之间的互相调用，未完全退出系统前，不允许
        //                      释放相关资源
        //参数说明: 无
        //返回: 无
        //作者: 瞿松松20160715
        /**************************************************************************************************/
        void AddEnterSystemCount(void);

        /**************************************************************************************************/
        //函数名: SendTP20Broadcast
        //功能描述:用来发送TP20广播帧(只发不收)，数据发送格式:
        //
        //打开运输模式广播命令
        //02 00 07 fe 23 3b 00 ff aa aa
        //02 00 07 fe 23 3b 00 ff 55 55
        //02 00 07 fe 23 3b 00 ff aa aa
        //02 00 07 fe 23 3b 00 ff 55 55
        //02 00 07 fe 23 3b 00 ff aa aa
        //关闭运输模式广播命令
        //02 00 07 fe 23 3b 00 00 aa aa
        //02 00 07 fe 23 3b 00 00 55 55
        //02 00 07 fe 23 3b 00 00 aa aa
        //02 00 07 fe 23 3b 00 00 55 55
        //02 00 07 fe 23 3b 00 00 aa aa

        //  参考代码
        //	     binSendCmd = CBinary("\x00\x00\x02\x00\xFE\x23\x3b\x00\x00\xaa\xaa", 11); //07长度自动添加
	 //       sendframe.SetSendFrame(binSendCmd, 0); 
	 //       rfRet = EcuInterface.SendTP20Broadcast(sendframe);
	 //
	 //       
        //参数说明: 无
        //返回: 无
        //作者: 瞿松松20160716
        /**************************************************************************************************/
	CReceiveFrame SendTP20Broadcast(CSendFrame SendFrame);
        /**************************************************************************************************/
        //函数名: GetTP20LinkSendPackNum
        //功能描述:获取TP20发送的包计数器
        //参数说明: 无
        //返回: 无
        //作者: 瞿松松20160722
        /**************************************************************************************************/
	unsigned char GetTP20LinkSendPackNum(void);
        /**************************************************************************************************/
        //函数名: SetTP20LinkPara
        //功能描述:设置TP20  T3 ，给软件8部防盗专用
        //参数说明: value   设置的值
        //返回: 
        //作者: 瞿松松20160814
        /**************************************************************************************************/
	void SetTP20SpecialT3(unsigned long value);

	
    /*-----------------------------------------------------------------------------
      功    能：用于控制TP20是否禁止断开连接;
      参    数：开关
      返 回 值：无
      说    明：true - 允许断开连接  false - 禁止断开连接
                            (用于切换标准与非标准时禁止发送0xA8的断开命令到总线)
    -----------------------------------------------------------------------------*/
    void SetTp20DisconnectFlag(bool flag);

    /**************************************************************************************************/
    //函数名: SetChevroletSaiOuSendDelay
    //功能描述:设置雪佛兰赛欧3发送延时,2015年中国通用赛欧3发送机通信异常,
    //                       因为当接收帧到发送帧(P3)时间过短时,ECU不响应，调用此函数后
    //                       将会自动延时5ms
    //参数说明: 
    //返回: 
    //作者: 瞿松松20160927
    /**************************************************************************************************/
    void SetChevroletSaiOuSendDelay(bool status);
    bool isKWP1281Renter(void);
    
    /*********************************************************
    *函数名:		    bool CEcuInterface::SetISO15765SpecialBps(int special_flag, int bps)
    *功能:		    设置标准CAN一些特殊波特率的函数
    *输入值:		    special_flag:特殊波特率时此值一定要非0，special_bps:波特率值
    *返回值:      	    void    
    *作者:		    甘旗
    *创建日期:	    [2016-12-12]
    *备注:ISO15765协议下一些特殊的波特率需要特殊处理。比如当为50k bps
    时，需要调用此函数才行。否则底层会把这些特殊波特率的标准
    CAN协议转化成容错CAN。
    用法:50K的标准CAN调用示例:
    SetISO15765SpecialBps(1, 50000);
    *********************************************************/
    void SetISO15765SpecialBps(int special_flag, int special_bps);

    /*-----------------------------------------------------------------------------
      功    能：设置多请求发送模式,设置之后可以调用原来的网络层发送接口进行发送；但是组包格式必须按照
                        规定的来组，下面将有说明;发送完毕多请求之后，需要设置0模式,恢复正常收发;
                        接口目的是减少VCI和上位机之间的交互,可以提高通讯效率;
      参    数：模式值
      返 回 值：无
      说    明：
      0 - 作为默认模式,就是正常收发,非多请求发送模式
      1 - 通用模式,数据存放格式(发送和接收格式一致,1个请求对1个回应,不支持广播发送):
            一个字节长度+字节长度对应的数据+.....+最后两个字节的帧数作为校验(高字节在前,低字节在后)
            |1 byte length=m| m byte data|1 byte length=n|n byte data|........|1byte RequestNum High Byte|1byte RequestNum Low Byte|
      2 - 未定
      ..
      
            2016-8-30 赖辉强
    -----------------------------------------------------------------------------*/
    enum
    {
        NORMAL_ONE_REQUEST_MODE = 0,         /*一次发送一个请求的模式*/
        GENERIC_MULTI_REQUEST_MODE = 1,     /*一次发送多个请求的通用模式1*/
    };
    
    long SetMultiRequestMode(unsigned int mode);

    /*-----------------------------------------------------------------------------
     SetMultiRequestExpectedResp:
      功    能：设置多请求发送的期望回应，
                            匹配方式:
                            在收到ECU数据之后
                            先匹配发送给ECU的请求数据，看此请求数据是否需要匹配处理，如果匹配失败，就不对接收进行匹配
                            如果匹配到，再对此数据的ECU 响应数据进行匹配，如果匹配失败，则继续发送后面的请求数据
                            如果也匹配到，就执行匹配到后的动作,例如停止发送
      参    数：
            vector<EXPECT_RESPONSE_SETUP_PARAM>,
            1.对发送的数据匹配
                RequestMask是需要匹配字节的掩码,
                RequestPattern是需要匹配字节的内容,
                匹配成功算法:
                    (RequestMask[i] & RequestPattern[i]) == (RequestMask[i] & SendData[i])
                注:RequestMask 和RequestPattern的字节数必须一样
            
            2.对接收的数据匹配
                ExptRespMask是需要匹配字节的掩码,
                ExptRespPattern是需要匹配字节的内容,
                匹配成功算法:
                    (ExptRespMask[i] & ExptRespPattern[i]) == (ExptRespMask[i] & RecvData[i])
                注:ExptRespMask 和ExptRespPattern的字节数必须一样
                
            3.Mode 模式是匹配到后的动作:
                1 - 是停止发送,并将匹配到的数据和之前接收到的数据一并返回
            
            RequestMask、RequestPattern、ExptRespMask、ExptRespPattern的字节数最大是16
            vector数量最大50
            
      返 回 值：0 - 设置成功,  
                                other value - 设置失败
      说    明：
            可以设置多个过滤条件,max = 50;
            现支持匹配到任意一组就停止发送,(mode = 1);
            匹配到之后会将匹配到的结果和匹配之前收到的结果返回;
            
            2016-8-30 赖辉强
    -----------------------------------------------------------------------------*/
    enum
    {
        MATCH_STOP_REQUEST = 1,         /*匹配到就停止继续请求*/
        MATCH_CONTINUE_REQUEST = 2, /*匹配到就继续发送请求*/    
    };

    typedef struct tg_ExptResp
    {
        CBinary RequestMask;
        CBinary RequestPattern;
        CBinary ExptRespMask;
        CBinary ExptRespPattern;
        unsigned int Mode;
    }EXPECT_RESPONSE_SETUP_PARAM;
    
    long SetMultiRequestExpectedResp(vector<EXPECT_RESPONSE_SETUP_PARAM> ExpectedResp);
    void SetMultiRequestExpectedRespFrameIntervalTime(int FrameIntervalTime);
	
	/***********************************************************
    *函数名:		bool CEcuInterface::ClearRcvBuffer(void)
    *功能:		    清除VCI缓存区
    *输入值:		
    *返回值:      	
    *作者:		    quss
    *创建日期:	    2016.12.24
    *备注:          GM无穷帧需要按需清除接收缓存,以保证接收到最新的数据
    ************************************************************/
    bool ClearRcvBuffer(void);
	
    /*-----------------------------------------------------------------------------
        函数名: SetIso15765FlowControlDelay(unsigned int Us);
        功能描述: 设置发送流控制之前的延时,即接收到首帧和发送流控制之间的时间间隔;
                                还有发送完一个block之后发送流控制的间隔也是此值
        参数说明: 单位是us
        返回: 
                0 -正确
                其他值 - 错误
        作者: 赖辉强20161229
    -----------------------------------------------------------------------------*/
    long SetIso15765FlowControlDelay(unsigned int Us);
	
    private:
        int m_ulEnterFlag;  // CEcuInterface类中判断是否由ISO9141进入了KWP1281的标志

    /**************************************************************************************
    *函数名:		long CEcuInterface::Abstract5BpsEnterSystemPara(CEnterSystem EnterSystem)
    *功能:		       提取5bps系统进入前需要设置下去的参数
    *输入值:		EnterSystem:诊断车系那边调用传入的类，里面包含传入的参数
    *返回值:      	long
    *作者:		       甘旗
    *创建日期:	2017.1.11
    *备注:          
    *************************************************************************************/
    long Abstract5BpsEnterSystemPara(CEnterSystem EnterSystem);

};

#endif  // #ifndef ECUINTERFACE_H_HEADER_INCLUDED_B97E65A3
