#ifndef MULTIRECEIVEFRAME_H_HEADER_INCLUDED_B97E00F3
#define MULTIRECEIVEFRAME_H_HEADER_INCLUDED_B97E00F3
#include "Binary.h"
#include "ReceiveFrame.h"

/******************************************************************************

    Copyright (c) 2007, AUTEL Ltd,.Co
  
    All rights reserved.

    文件名称：MultiReceiveFrame.h MultiReceiveFrame.cpp

    档 标 识：《MaxScan详细设计说明书》

    摘    要：处理并存贮多个接收帧
            
    用途：
    

    历史记录：
    ---------------------------------------------------------------------------
     时     间    作者    版本号      操    作    内    容
    ---------------------------------------------------------------------------
     2007.6.27    王长喜  1.0         创建此类。

*******************************************************************************/

class CMultiReceiveFrame
{
  public:
	  CReceiveFrame GetAt(W_I16 iPosition) const;
	  W_I16 GetSize() const;
    /*-----------------------------------------------------------------------------
      功    能：添加数据
      参数说明：CMultiReceiveFrame& MultiReceiveFrame -- 多接收帧
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    void Add(CMultiReceiveFrame& MultiReceiveFrame);

    /*-----------------------------------------------------------------------------
      功    能：添加数据
      参数说明：CReceiveFrame ReceiveFrame -- 接收帧
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    void Add(CReceiveFrame ReceiveFrame);

    /*-----------------------------------------------------------------------------
      功    能：将二进制数据做为一个接收帧加入
      参数说明：CBinary bin -- ECU数据
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    void Add(CBinary bin);

    /*-----------------------------------------------------------------------------
      功    能：清空数据
      参数说明：无
      返 回 值：无
      说    明：无
    -----------------------------------------------------------------------------*/
    void Clear();

    /*-----------------------------------------------------------------------------
      功    能：取得一个ECU数据帧
      参数说明：W_I16 iPosition -- 数据帧位置
      返 回 值：接收帧的引用
      说    明：无
    -----------------------------------------------------------------------------*/
    CReceiveFrame& operator[](W_I16 iPosition);

    void operator=(const CMultiReceiveFrame& right);

    CMultiReceiveFrame();
    CMultiReceiveFrame(const CMultiReceiveFrame& right);
    virtual ~CMultiReceiveFrame();


protected:
    vector <CReceiveFrame> m_MultiReceiveFrame;
};



#endif /* MULTIRECEIVEFRAME_H_HEADER_INCLUDED_B97E00F3 */
