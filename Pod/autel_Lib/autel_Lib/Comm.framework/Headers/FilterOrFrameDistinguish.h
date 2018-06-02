#ifndef FILTERORFRAMEDISTINGUISH_H_HEADER_INCLUDED_B97B7521
#define FILTERORFRAMEDISTINGUISH_H_HEADER_INCLUDED_B97B7521

#define CAN_SEND_STD_MSG_OBJ_NO         30  // 用于发送的标准报文对象号
#define CAN_SEND_EXT_MSG_OBJ_NO         31  // 用于发送的扩展报文对象号
#define CAN_FIRST_RECEIVE_MSG_OBJ_NO    0   // 第一个用于接收的报文对象号
#define CAN_LAST_RECEIVE_MSG_OBJ_NO     127  // 最后一个用于接收的报文对象号
//#define CAN_MAX_FILTER_ID                         64  // CAN协议能够设置的最大的过滤ID数---甘旗20161215

#include "adsStd.h"
#include "Binary.h"
#include "ErrorCode.h"
//#include "assert.h"
//#include "CircleQueue.h"

#ifndef USE_IDE_VC
extern "C"{
#include "can.h"
}
#endif

/******************************************************************************

    Copyright (c) 2007, AUTEL Ltd,.Co

    All rights reserved.

    文件名称：FilterOrFrameReceive.h FilterOrFrameReceive.cpp

    档 标 识：

    摘    要：本类实现链路层帧接收过滤条件设定和帧长度识别方法设定功能

    用    途：


    历史记录：
    ---------------------------------------------------------------------------
     时     间           作者    版本号   操    作    内    容
    ---------------------------------------------------------------------------
     2007-5-18 18:05:41  王长喜    1.0      创建此类。
     2007-7-9            班洪立    1.0      基本完成代码，IAR编译通过
     2008-3-4            班洪立    1.0      在调用ClearCanFilterID时，将过滤模式
                                            设为CAN ID过滤模式
     2008-5-14           班洪立    1.0      为适应MaxiDAS增加函数AppendCanFilterId(W_U32 ulIdStart, W_U32 ulIdEnd)
                                            并将原AppendCanFilterId拆开
     2008.7.25           王长喜    1.0      加入TOYOTA CAN子系统标识字节过波识别条件及相关代码修改
     2008.7.25           王长喜    1.0      加入SetCanSpecialByte();
     2008.7.28           王长喜    1.0      重改operator = ();
     2008.7.28           王长喜    1.0      加入流控制成员变量 W_U8 m_aucCanFlowCtrl[10];
     2008.7.28           王长喜    1.0      加入SetCanFlowControlFrame(CBinary binFlowCtrlContain);
     2008.9.1            王长喜    1.0      加入CAN定义BMW_CAN_ECU_TOOL_ADDRESS及相关代码
     2008.10.9           王长喜    1.0      加入 W_ErrorCode SetVolovD2kMode();
     2008.11.27          王长喜    3.0      验证BMW CAN通过, 加入TOYOTA与BMW CAN兼容接口
     2008.12.5           王长喜    3.21     加入BMW/TOYOTA流控制支持
     2009.1.14           王长喜             加入CAN流控制帧填充否设置字节
     2009-12-27          潘相熙    5.54     加入对vpw多过滤支持,本来应加一种类型的,现时间紧,直接特殊处理
                                            格式为CBinary(), 0x55+0xaa
                                            + [iposition(1BYTE) + 第一种过滤长度(如0x01) + 过滤数据(如0x6C)]
                                            + [iposition(1BYTE) + 第一种过滤长度(如0x01) + 过滤数据(如0xAC)]
                                            结果如下CBinary("\x55\xAA\x00\x01\x6C\x00\x01\xAC", 8).
     2010-05-11          潘相熙    5.72     添加对ford,UBP过滤支持     

*******************************************************************************/
class CFilterOrFrameDistinguish
{
  public:
    ////////////////////////////////////////////////////////////////////////////
    // 过滤方式/帧长识别方式
    // 无过滤条件
    // FFR_NONE = 0,
    // 普通过滤条件--指定位置，指定内容，指定长度
    // FFR_NORMAL = 1,
    // CAN ID 过滤
    // FFR_CAN_ID = 10,
    // 帧长度识别
    // FFR_FRAME_RECEIVE = 50
    enum  emFilterMode {
        // 无过滤条件
        FFD_NONE = 0,
        // 普通过滤条件--指定位置，指定内容，指定长度
        FFD_NORMAL = 1,

		FFD_MASKPATTERN = 2,

        // CAN ID 过滤  2008.7.25 王长喜加入支持丰田ID子系统标识字节方式
        FFD_CAN_ID = 10,
        
        // 帧长度识别
        FFD_FRAME_DISTINGUISH = 50,
        // 指定帧长度
        FFD_SPECIFY_FRAME_LEN = 51,
        FFD_VOLVO_D2K         = 52,
        
        // vpw过滤,支持2钟过滤 潘相熙 2009-12-27添加
        FFD_VPW               = 60,
        
        // ford UBP过滤(林肯) 潘相熙 2010-05-11添加
        FFD_FORD_UBP          = 61,

		FFD_GM_ALDL           = 62
		/*P 潘相熙 17:11:27
		潘工：

		你好！
		我们在这边测试GM ALDL链路层时，发现新的链路问题，需要新增ALDA链路层。
		问题：
		在ALDL收发数据时，K线上有其它符合ALDL协议规则，但是不需要的数据出现。最终反应在收到的数据不准，

		杂乱数据：
		A8 59 B1 00 18 00 36 
		30 59 10 00 2A 00 3D 
		90 5A 18 E4 64 02 93 21 91 59 00 00 00 00 16 
		30 59 10 00 2A 00 3D
		正确通讯数据
		F4 56 08 AE 
		F4 56 08 AE 
Req: FA 57 01 00 AE 
Ans: FA 80 01 00 65 01 00 D7 00 ......

	 链路层要求，收发函数上处理。
	 收数据时根据发命令：FA 57 01 00 AE中的FA去收取以FA开头ECU回复的命令，长度为0x57-0x52,0xAE为校验（累加和取反加1）
	 在收数据时，一定要对校验判断，如果不对，则丢掉，再重新收，直到收到符合条件的数据帧，或用P2退出。


	 纪安荣

	 2010-07-09*/

    };
    ////////////////////////////////////////////////////////////////////////////

    /*-----------------------------------------------------------------------------
      功    能：设置成无过滤
      参数说明：无
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    void Clear();

    /*-----------------------------------------------------------------------------
      功    能：缺省构造函数
      参数说明：无
      返 回 值：无
      说    明：设置为无过滤方式
    -----------------------------------------------------------------------------*/
    CFilterOrFrameDistinguish();

    /*-----------------------------------------------------------------------------
      功    能：析构函数
      参    数：无
      返 回 值：
      说    明：
    -----------------------------------------------------------------------------*/
    virtual ~CFilterOrFrameDistinguish();

    /*-----------------------------------------------------------------------------
      功    能：一般过滤方式
      参数说明：W_I16 iPosition             过滤内容位置
                CBinary binContain          过滤内容
      返 回 值：错误代码
      说    明：无
    -----------------------------------------------------------------------------*/
    W_ErrorCode NormalFilter(W_I16 iPosition, CBinary binContain);


    W_ErrorCode MaskPatternFilter(CBinary binContain);
	
    /*-----------------------------------------------------------------------------
      功    能：设置VOLOV D2K 帧长度识别方式
      参数说明：无
      返 回 值：错误代码
      说    明：无
    -----------------------------------------------------------------------------*/
    W_ErrorCode SetVolvoD2kMode();


	/*-----------------------------------------------------------------------------
	功    能：设置Ford 林肯UBP 帧识别方式
	参数说明：无
	返 回 值：错误代码
	说    明：无
	-----------------------------------------------------------------------------*/
	W_ErrorCode SetFordUBPMode();


	/*-----------------------------------------------------------------------------
	功    能：设置GM ALDL帧识别方式
	参数说明：无
	返 回 值：错误代码
	说    明：无
	-----------------------------------------------------------------------------*/
	W_ErrorCode SetGMALDLMode();




    /*-----------------------------------------------------------------------------
      功    能：一般过滤方式的构造函数
      参数说明：W_I16 iPosition             过滤内容位置
                CBinary binContain          过滤内容
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    CFilterOrFrameDistinguish(W_I16 iPosition, CBinary binContain);

	CFilterOrFrameDistinguish(CBinary binContain);

    /*-----------------------------------------------------------------------------
      功    能：追加CAN接收过滤ID段
      参数说明：binIdStart                  过滤ID段的起始ID
                binIdEnd                    过滤ID段的结束ID(为空时表示和起始ID相同)
      返 回 值：错误代码
      说    明：过滤ID或者为11位，或者为29位，低n位有效，高m位为0，首位表示ID类型
                CBinary对象内容为2字节时表示标准ID类型,4字节时表示扩展ID类型
      附加说明：设置到硬件，由硬件判断是否满足过滤条件
                最多能同时设置31次，也就是31个ID段
      示    例：如需接收如下ID: 03EF,07E8,07E9,...07EE,07EF则应如下调用
                // 增加过滤ID:03EF
                Obj.AppendCanFilterId(CBinary("\x03\xEF", 2));
                // 增加过滤ID:07E8,07E9,...07EE,07EF
                Obj.AppendCanFilterId(CBinary("\x07\xE8", 2), CBinary("\x07\xEF", 2));

                //add by 甘旗20161215
                注意:分段设置的时候，每段的区间不能大于10,当此段区间大于10时此段只有第一个
                过滤ID有效,此时可以按照如下2种方式设置，比如设置07E8,07E9,...07EE,07FD(连续的16个)
                过滤ID。
                1、将这16个连续ID区间的分成两个小于10的区间
                    Obj.AppendCanFilterId(CBinary("\x07\xE8", 2), CBinary("\x07\xEF", 2));
                    Obj.AppendCanFilterId(CBinary("\x07\xF0", 2), CBinary("\x07\xFD", 2));
                2、一个一个的设置
                    Obj.AppendCanFilterId(CBinary("\x07\xE8", 2));
                    Obj.AppendCanFilterId(CBinary("\x07\xE9", 2));
                    ......
                    Obj.AppendCanFilterId(CBinary("\x07\xFD", 2));
                不管怎样设置，设置的过滤ID总数不能大于64个，否则
                大于64个的将会无效，显然分段的最大数就是64个了。

                
    -----------------------------------------------------------------------------*/
#ifdef USE_SIMULATOR
W_ErrorCode AppendCanFilterId(CBinary binIdStart, CBinary binIdEnd = CBinary(), W_U32 uiMaskFt = 0x00);
#else    
    W_ErrorCode AppendCanFilterId(CBinary binIdStart, CBinary binIdEnd = CBinary());
#endif    
    
    /*-----------------------------------------------------------------------------
      功    能：设置CAN流控制D
      参数说明：CBinary binFlowCtrlContain流控制帧内容,如为空则使用系统缺省流控制
      返 回 值：错误代码
      说    明：第一个字节为控制字节, 
                       其值 0xFF -- 自动
                            0x40 -- 填充有效设定
                            0x20 -- 填充内容设定
                第二字节必须为: 0x30,
                总长度为4个字节, 否则内容无效.
    -----------------------------------------------------------------------------*/
    W_ErrorCode SetCanFlowControlFrame(CBinary binFlowCtrlContain);

#ifdef BMW_CAN_ECU_TOOL_ADDRESS
    W_ErrorCode SetCanToolsEcuAddress(BYTE ucToolAddress = 0, BYTE ucEcuAddress = 0);
#endif
    /*-----------------------------------------------------------------------------
      功    能：设置CAN识别ID
      参数说明：BYTE ucCanSpecailByte CAN识别ID
      返 回 值：错误代码
      说    明：CAN有效识别ID范围0x40~0xFF, 如果为0则取消设置
    -----------------------------------------------------------------------------*/
    W_ErrorCode SetCanSpecialByte(BYTE ucCanSpecailByte = 0);

    
    /*-----------------------------------------------------------------------------
      功    能：清除所有CAN过滤ID(接收所有帧)
      参数说明：无
      返 回 值：错误代码
      说    明：全部ID有效,如需调用函数AppendCanFilterId来设置过滤ID,必须首先调用此函数
    -----------------------------------------------------------------------------*/
    void ClearCanFilterID();

    /*-----------------------------------------------------------------------------
      功    能：是否为CAN过滤模式
      参数说明：无
      返 回 值：是CAN过滤模式返回true，否则返回false
      说    明：无
    -----------------------------------------------------------------------------*/
    bool IsCanFilterMode();

    /*-----------------------------------------------------------------------------
      功    能：接收数据是否满足过滤条件要求
      参数说明：binDataFrame                从ECU收到的一帧数据
      返 回 值：满足过滤条件--true, 不满足--false
      说    明：无
    -----------------------------------------------------------------------------*/
    bool IsFilterOK(CBinary binDataFrame);

    /*-----------------------------------------------------------------------------
      功    能：接收帧长度识别方式
      参数说明：W_I16 iPosition             长度字节位置
                W_U8 ucMask                 长度字节掩码
                W_I16 iOffset               计算帧加减数值
      返 回 值：错误代码
      说    明：无
    -----------------------------------------------------------------------------*/
    W_ErrorCode FrameDistinguish(W_I16 iPosition, W_U8 ucMask, W_I8 iOffset);

    /*-----------------------------------------------------------------------------
      功    能：接收帧长度识别方式的构造函数
      参数说明：W_I16 iPosition             长度字节位置
                W_U8 ucMask                 长度字节掩码
                W_I16 iOffset               计算帧加减数值
      返 回 值：无
      说    明：实际帧长度 = 长度字节 & ucMask + iOffset
    -----------------------------------------------------------------------------*/
    CFilterOrFrameDistinguish(W_I16 iPosition, W_U8 ucMask, W_I8 iOffset);

    /*-----------------------------------------------------------------------------
      功    能：是否为帧长识别方式或者指定帧长度模式
      参数说明：无
      返 回 值：是帧长识别方式返回true，否则返回false
      说    明：无
    -----------------------------------------------------------------------------*/
    bool IsFrameDistinguishOrSpecifyFrameLen();


	bool IsFilterOK_FORD_UBP(CBinary binDataFrame, CBinary binSend);


    /*-----------------------------------------------------------------------------
      功    能：获得帧长识别类型
      参数说明：无
      返 回 值：帧长识别类型
      说    明：无
    -----------------------------------------------------------------------------*/
    W_U8 GetFrameDistinguishType();

    /*-----------------------------------------------------------------------------
      功    能：获得帧识别方式的长度值位置
      参数说明：无
      返 回 值：帧识别方式的长度值位置
      说    明：无
    -----------------------------------------------------------------------------*/
    inline W_I16 GetFrameDistinguishPosition()
    {
        return m_iPosition;
    }
    /*-----------------------------------------------------------------------------
      说    明：为Hyundai:benix只收0x5B个字节添加-2013-8-20
    -----------------------------------------------------------------------------*/
	inline W_I16 GetFrameDistinguishOffset()
	{
		return m_iOffset;
	}

    /*-----------------------------------------------------------------------------
      功    能：根据帧的长度字节计算实际帧长度
      参数说明：ucLengthByte                帧的长度字节
      返 回 值：实际帧长度
      说    明：如过掩码的低n位为0，则在与运算后须右移n位
    -----------------------------------------------------------------------------*/
    W_I16 GetFrameLengthVal(W_U8 ucLengthByte);

    /*-----------------------------------------------------------------------------
      功    能：指定帧长度模式
      参    数：nLength                     指定的帧长度
      返 回 值：错误代码
      说    明：无
    -----------------------------------------------------------------------------*/
    W_ErrorCode SpecifyFrameLen(W_I16 nLength);
    

    /*-----------------------------------------------------------------------------
      功    能：指定长度模式构造函数
      参    数：nLength                     指定的帧长度
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    CFilterOrFrameDistinguish(W_I16 nFrameLen);

    CFilterOrFrameDistinguish(const CFilterOrFrameDistinguish& right);
    CFilterOrFrameDistinguish& operator = (const CFilterOrFrameDistinguish right);

	W_ErrorCode SetCan06f1Invalid(bool bInvalid = true);

    friend class CLinkPwm;
    friend class CLinkBaseCan;
    friend class CIntProtocol;
    friend class CLinkVolvoCan;
	friend class CDS708ToJ2534Base;
	friend class CDS708ToJ2534_PWM;
	friend class CDS708ToJ2534_VPW;
	friend class CDS708ToJ2534_15765;
	friend class CDS708ToJ2534_NanyueCan;
	friend class CDS708ToJ2534_1939;
	friend class CDS708ToJ2534_CumminsJ1939;
	friend class CDS708ToJ2534_J1708;
	friend class CDS708ToJ2534_KWP;
	friend class CDS708ToJ2534_SCI;
	friend class CDS708ToJ2534_TP20;
	friend class CDS708ToJ2534_VolvoCan;
	friend class CDS708ToJ2534_ALDL;
	friend class CDS708ToJ2534_ALDLGM;
	friend class CDS708ToJ2534_ISO;
	friend class CDS708ToJ2534_Normal;
	friend class CDS708ToJ2534_K81K82;
	friend class CDS708ToJ2534_TP16;
	friend class CDS708ToJ2534_CanPs;
	friend class CDS708ToJ2534_DelphiCan;
	
	friend class CEcuInterface;

  protected:

    /*-----------------------------------------------------------------------------
      功    能：追加CAN接收过滤ID段
      参数说明：ulIdStart                   过滤ID段的起始ID
                ulIdEnd                     过滤ID段的结束ID
      返 回 值：错误代码
      说    明：
    -----------------------------------------------------------------------------*/
    W_ErrorCode AppendCanFilterId(W_U32 ulIdStart, W_U32 ulIdEnd);

  protected:

    // 过滤方式／帧长识别方式
    W_U8 m_FilterMode;

    // 帧长度字节位置
    W_I16 m_iPosition;

    // 帧长度字节掩码
    W_U8 m_ucMask;

    // 计算帧长度加减数值
    W_I8 m_iOffset;

    // 帧识别内容
    CBinary m_binContain;

    // 指定的帧长度
    W_I16 m_nFrameLen;

    // CAN协议过滤ID组（格式：IdStart0, IdEnd0, IdStart1, IdEnd1 ... IdStartN, IdEndN）
    W_U32* m_puiCanFilterId;

    // CAN协议过滤ID个数，一个ID对为2个ID
    W_I32 m_iCanFilterIdCount;
    
#ifdef BMW_CAN_ECU_TOOL_ADDRESS // wcx add 9/1/2008
    W_U8 m_ucCanToolsAddress;
    W_U8 m_ucCanEcuAddress;
#else
    // wcx add 7/25/2008
    W_U8 m_ucCanSpecialByte;
    // wcx add 7/30/2008
#endif
    
    W_U8 m_aucCanFlowCtrl[10]; //第0字节是有效长度, 余下是内容

public:
	static bool m_bCan06f1Invalid;
};

#endif /* FILTERORFRAMEDISTINGUISH_H_HEADER_INCLUDED_B97B7521 */

