#ifndef NETKwp1281_H_HEADER_INCLUDED_B968DB53
#define NETKwp1281_H_HEADER_INCLUDED_B968DB53
#include "NegativeResponse.h"
#include "NetLayerBase.h"


/******************************************************************************

    Copyright (c) 2007, AUTEL Ltd,.Co

    All rights reserved.

    文件名称：NetIso1281.h NetKwp1281.cpp

    档 标 识：

    摘    要：本类是所有实现Kwp1281网络层的功能

    用    法：1、声明初始化：   
                 CNetKwp1281 NetKwp1281;
                 NetKwp1281.Init();
              2、完成具体通信：
                 NetKwp1281.SendReceive(...);
              3、不再使用，最后消毁
                 NetKwp1281.Destroy();

    历史记录：
    ---------------------------------------------------------------------------
     时     间   作者    版本号   操    作    内    容
    ---------------------------------------------------------------------------
     2007.8.14   韩炜    1.0      创建此类
     2007.8.21   韩炜    1.0      编写实现代码
     2007.10.17  王长喜  1.0      加入NewSelf()

*******************************************************************************/
class CNetKwp1281 : public CNetLayerBase
{
  public:

    using CNetLayerBase::Init;
    using CNetLayerBase::SendReceive;
    
    /*-----------------------------------------------------------------------------
      功    能：完成初始化功能，进入系统
      参    数：W_U8 uAddressCode -- 进入系统的地址码
                CSendFrame SendFrame -- 发送帧，缺省值为CSendFrame(CBinary("\x03\x00\x09\x03",4),1)
      返 回 值：接收帧内容
      说    明：执行是否成功通过CErrorCode类查询
    -----------------------------------------------------------------------------*/
	virtual CReceiveFrame Init(W_U8 uAddressCode, CSendFrame SendFrame=CSendFrame(CBinary("\x03\x00\x09\x03",4), CSendFrame::SF_AUTO_DISTINGUISH) );
	virtual CBinary SendReceive(CBinary binSend);//2011-05-17 Add jar
	virtual CReceiveFrame SendReceive(CSendFrame SendFrame);//2011-05-17 Add jar

    /*-----------------------------------------------------------------------------
      功    能：退出系统
      参    数：无
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    virtual void Destroy();

    /*-----------------------------------------------------------------------------
    功    能：1281协议专用发一帧收一帧或多帧（0帧）
    参数说明：CSendFrame SendFrame – 发送帧
    返 回 值：接收帧
    说    明：无
    -----------------------------------------------------------------------------*/
 //   virtual CReceiveFrame SendReceive(CSendFrame SendFrame);
  	virtual CNetLayerBase* NewSelf();

    CNetKwp1281();
    virtual ~CNetKwp1281();
};



#endif /* NETKwp1281_H_HEADER_INCLUDED_B968DB53 */
