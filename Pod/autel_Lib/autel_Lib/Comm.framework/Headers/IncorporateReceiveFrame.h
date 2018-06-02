#ifndef INCORPORATERECEIVEFRAME_H_HEADER_INCLUDED_B9679407
#define INCORPORATERECEIVEFRAME_H_HEADER_INCLUDED_B9679407
#include "Binary.h"
//#include <vector>

/******************************************************************************

    Copyright (c) 2007, AUTEL Ltd,.Co

    All rights reserved.

    文件名称：Binary.h Binary.cpp

    档 标 识：《MaxScan详细设计说明书》

    摘    要：二进制类，用于数据存贮及高效传递

    用    途：


    历史记录：
    ---------------------------------------------------------------------------
     时     间    作者    版本号      操    作    内    容
    ---------------------------------------------------------------------------
     2007.7.23    王长喜  1.0         创建此类。
     2007.11.29   王长喜  1.0         将成员变量由vector改为固定数组

*******************************************************************************/

class CIncorporateReceiveFrame
{
  public:
    class CEcuData
    {
      public:
        /*-----------------------------------------------------------------------------
          功    能：取得ECU源地址
          参    数：无
          返 回 值：源地址
          说    明：无
        -----------------------------------------------------------------------------*/
        W_U32 GetSourceId();

        /*-----------------------------------------------------------------------------
          功    能：取得合并后的无格式的ECU数据内容
          参    数：无
          返 回 值：合并后的无格式的ECU数据
          说    明：无
        -----------------------------------------------------------------------------*/
        CBinary GetData();

        /*-----------------------------------------------------------------------------
          功    能：添加数据到合并帧中
          参    数：CBinary bin -- 解包后的ECU有效数据
          返 回 值：无
          说    明：无
        -----------------------------------------------------------------------------*/
        void Add(CBinary bin);

        CEcuData& operator=(const CEcuData& right);

        CEcuData();
        CEcuData(const CEcuData& right);
        CEcuData(const CEcuData* pRight);
        CEcuData(W_U32 uSourceId, CBinary m_binEcuData);
        virtual ~CEcuData();

      private:

      protected:
        // ECU 源地址
        W_U32 m_uSourceId;

        // 无格式的合并的ECU数据内容
        CBinary m_binEcuData;
    };

    /*-----------------------------------------------------------------------------
      功    能：取得ECU数量
      参    数：无
      返 回 值：回复数据的ECU个数
      说    明：无
    -----------------------------------------------------------------------------*/
    W_I16 GetSize();

    /*-----------------------------------------------------------------------------
      功    能：取得一个ECU数据
      参    数：W_I16 iPosition -- 序号
      返 回 值：一个ECU数据
      说    明：无
    -----------------------------------------------------------------------------*/
    CIncorporateReceiveFrame::CEcuData& operator[](W_I16 iPosition);

    /*-----------------------------------------------------------------------------
      功    能：添加数据
      参    数：W_U32 uSourceID -- 源地址
                CBinary binData -- 去除格式的数据内容
      返 回 值：无
      说    明：如存在源地址，则数据追加；如在存在则创建
    -----------------------------------------------------------------------------*/
    void Add(W_U32 uSourceID, CBinary binData);

    CIncorporateReceiveFrame& operator=(const CIncorporateReceiveFrame& right);

    CIncorporateReceiveFrame();
    CIncorporateReceiveFrame(const CIncorporateReceiveFrame& right);
    virtual ~CIncorporateReceiveFrame();

  protected:
	W_I16 ReAllocatePointer(W_I16 iNewSize, bool bDeleteAllData=false);

  protected:
    #define ALLOCATE_SIZE_UNIT         8
    CEcuData** m_ppEcuData;
    W_I16 m_iDataNumber;
    W_I16 m_iAllocateNumber;
};



#endif /* INCORPORATERECEIVEFRAME_H_HEADER_INCLUDED_B9679407 */
