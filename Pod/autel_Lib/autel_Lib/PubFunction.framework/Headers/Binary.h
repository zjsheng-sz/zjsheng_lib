﻿#ifndef BINARY_H_HEADER_INCLUDED_B97F362D
#define BINARY_H_HEADER_INCLUDED_B97F362D
#include "adsStd.h"

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
2007.6.27    王长喜  1.0         创建此类。
2007.7.6     王长喜  1.0         编写代码，并编译通过
2007.8.23    王长喜  1.0         加入Find()/Delete()成员函数

*******************************************************************************/
class CBinary
{
public:
	CBinary();
	CBinary(const BYTE* pucContain, W_I16 iLength);
	CBinary(const char* pucContain, W_I16 iLength);
	CBinary(const CBinary& right);
	virtual ~CBinary();
public:
	CBinary& operator = (const CBinary right);
	void operator += (const CBinary right);
	void operator += (BYTE ucValue);
	CBinary operator + (BYTE ucValue);
	CBinary operator + (const CBinary right);
	BYTE operator[](W_I32 iPosition);
	BYTE operator[](W_I32 iPosition)const;

	/*-----------------------------------------------------------------------------
	功    能：删除一个字节
	参数说明：被删除字节位置
	返 回 值：错误代码
	说    明：无
	-----------------------------------------------------------------------------*/
	W_ErrorCode Delete(W_I16 iIndex);

	/*-----------------------------------------------------------------------------
	功    能：查找是否存在指定字节
	参数说明：BYTE ucElement -- 被比较的字节内容
	W_I16 iIndex   -- 查找的起始位置, 缺省从0起始
	返 回 值：如找到则返回字节位置，找不到返回-1
	说    明：无
	-----------------------------------------------------------------------------*/
	W_I16 Find(BYTE ucElement, W_I16 iIndex = 0);

	/*-----------------------------------------------------------------------------
	功    能：比较内容
	参数说明：const CBinary& right 被比较的内容
	返 回 值：大于被比较内容返回+1, 等于返回0, 小于返回1
	说    明：无
	-----------------------------------------------------------------------------*/
	W_I16 Compare(const CBinary& right);
	bool operator==(const CBinary& right);
	bool operator!=(const CBinary& right);
	bool operator<(const CBinary& right);
	bool operator<=(const CBinary& right);
	bool operator>(const CBinary& right);
	bool operator>=(const CBinary& right);

	/*-----------------------------------------------------------------------------
	功    能：比较内容
	参数说明：const CBinary& right 被比较的内容
	iLenToCompare        要比较的长度
	返 回 值：大于被比较内容返回+1, 等于返回0, 小于返回1
	说    明：无
	-----------------------------------------------------------------------------*/
	W_I16 Compare(const BYTE* pucRight, W_I16 iLengthToCompare);

	/*-----------------------------------------------------------------------------
	功    能：清空数据内容
	参数说明：无
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	void Clear();

	/*-----------------------------------------------------------------------------
	功    能：数据内容为空否
	参数说明：是--true, 否--false
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	bool IsEmpty() const;

	/*-----------------------------------------------------------------------------
	功    能：取得数据缓冲区内容指针
	参数说明：无
	返 回 值：数据指针
	说    明：无
	-----------------------------------------------------------------------------*/
	const BYTE* GetBuffer() const;

	/*-----------------------------------------------------------------------------
	功    能：内容中追加数据
	参数说明：const BYTE *pucBuffer -- 数据缓冲区指针, W_I16 iLength -- 数据长度
	返 回 值：错误代码
	说    明：无
	-----------------------------------------------------------------------------*/
	W_ErrorCode Append(const BYTE *pucBuffer, W_I16 iLength);

	/*-----------------------------------------------------------------------------
	功    能：内容中追加数据
	参数说明：const W_VU8 *pucBuffer -- 数据缓冲区指针, W_I16 iLength -- 数据长度
	返 回 值：错误代码
	说    明：无
	-----------------------------------------------------------------------------*/
	W_ErrorCode Append(const W_VU8 *pucBuffer, W_I16 iLength);

	/*-----------------------------------------------------------------------------
	功    能：设置某一个位置内容
	参数说明：W_I32 iPosition -- 数据位置，BYTE ucContain -- 内容
	返 回 值：错误代码
	说    明：无
	-----------------------------------------------------------------------------*/
	W_ErrorCode SetAt(W_I16 iPosition, BYTE ucNewByte);

	/*-----------------------------------------------------------------------------
	功    能：取得一个字节数据
	参数说明：W_I32 iPosition -- 数据位置
	返 回 值：内容字符
	说    明：无
	-----------------------------------------------------------------------------*/
	BYTE GetAt(W_I16 iPosition)const;

	/*-----------------------------------------------------------------------------
	功    能：取得内容尺寸
	参数说明：无
	返 回 值：内容长度
	说    明：无
	-----------------------------------------------------------------------------*/
	W_I16 GetSize() const;

	/*-----------------------------------------------------------------------------
	功    能：设置为数据分配内存尺寸及缺省增加内存块大小
	参数说明：W_I32 nNewSize -- 分配内存尺寸
	W_I32 nGrowBy -- 新增加内存块分配大小，缺省为DEFAULT_GROW_BY
	返 回 值：错误代码
	说    明：无
	-----------------------------------------------------------------------------*/
	W_ErrorCode SetSize(W_I16 nNewSize, W_I16 nGrowBy=DEFAULT_GROW_BY);

	/*-----------------------------------------------------------------------------
	功    能：释放未使用内存
	参数说明：无
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	void FreeExtra(void);


	W_I16 WriteBuffer(char*pSrc, W_I16 iWriteLength);

protected:
	W_ErrorCode NewInstance(W_I16 iNewSize);

protected:
	enum {
		DEFAULT_GROW_BY = 8,
		ALLOCATED_MIN_SIZE = 4
	};

	struct tagContain {
		BYTE *m_pucBinary;
		W_I16 m_iDataLength;
		W_I16 m_iAllocLength;
		W_I16 m_iGrowBy;
		W_I16 m_iCount;
	}* m_pContain;

};
#endif /* BINARY_H_HEADER_INCLUDED_B97F362D */
