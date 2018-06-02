/******************************************************************************

Copyright (c) 2012, AUTEL Ltd,.Co

All rights reserved.

文件名称：NetLayerBase.h NetLayerBase.cpp

档 标 识：

摘    要：本类是所有实现网络层的基类，并实现共性的、最常用的功能

用途：


历史记录：
---------------------------------------------------------------------------
时     间   作者    版本号   操    作    内    容
---------------------------------------------------------------------------
2012.8.28   纪安荣  1.0      创建此类。

*******************************************************************************/
#include "Binary.h"
#include "saej2534_func.h"
class CFilter
{
public:
	typedef	enum
	{
		PASS_FILTER=1,
		BLOCK_FILTER,
		FLOW_CONTROL_FILTER,
	}FILTER_TYPE;

	CFilter(ULONG ulProtocolId);
	~CFilter();

	ULONG	m_ulProtocolId;

	ULONG SetFilter(FILTER_TYPE emType,ULONG &ulFilterId,CBinary binMask,CBinary binPattern,CBinary binFlowCtl = CBinary());
	ULONG SetFilter(FILTER_TYPE emType,ULONG &ulFilterId,PPASSTHRU_MSG pstMask,PPASSTHRU_MSG pstPattern,PPASSTHRU_MSG pstFlowCtl);

};

