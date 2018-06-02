#ifndef MANUFACTURER_H_HEADER_INCLUDED_B980C1B5
#define MANUFACTURER_H_HEADER_INCLUDED_B980C1B5

/******************************************************************************

    Copyright (c) 2007, AUTEL Ltd,.Co
  
    All rights reserved.

    文件名称：Manufacturer.h Manufacturer.cpp

    档 标 识：《MaxScan详细设计说明书》

    摘    要：诊断程序框架类，所有车系诊断均由本类派生
            
    用途：
    

    历史记录：
    ---------------------------------------------------------------------------
     时     间    作者    版本号      操    作    内    容
    ---------------------------------------------------------------------------
     2007.6.25    王长喜  1.0         创建此类。
     2007.11.7    潘相熙              增加车系名变量  

*******************************************************************************/

#include "adsStd.h"
#include "AppLayerBase.h"
#include "Binary.h"  

#define _CONS(a,b)  a##b              // 用于宏合并，合并后但不加串
#define CONS(a,b)   _CONS(a,b)          // 转换宏 
#define _STR(a)     #a                  // 用于宏再加个""
#define STR(a)      _STR(a)             // 转换宏 


class CManufacturer
{
public:
    /*-----------------------------------------------------------------------------
      功    能：车系诊断入口
      参数说明：无
      返 回 值：错误代码
      说    明：无
    -----------------------------------------------------------------------------*/
    virtual W_ErrorCode MainEntrance();


    /*-----------------------------------------------------------------------------
      功    能：菜单树回调函数
      参数说明：W_I32 idTask 任务ID, 
                CBinary binMenuItemTextId 
      返 回 值：菜单回退级数
      说    明：本函数用于菜单树类缺省回调函数
    -----------------------------------------------------------------------------*/
    virtual W_I32 MenuTreeCallBack(W_U32 idTask, CBinary binMenuItemTextId);

	/*-----------------------------------------------------------------------------
	功    能：菜单树回调函数
	参数说明：CBinary binTaskID 任务ID, 
				CBinary binMenuItemTextId 
	返 回 值：菜单回退级数
	说    明：本函数用于菜单树类缺省回调函数
	-----------------------------------------------------------------------------*/
	virtual W_I32 MenuTreeCallBack64(CBinary binTaskID, CBinary binMenuItemTextId);

    /*-----------------------------------------------------------------------------
      功    能：取得应用层基类指针
      参数说明：无
      返 回 值：应用层基类指针
      说    明：无
    -----------------------------------------------------------------------------*/
    //	CAppLayerBase * GetAppLayer();


    /*-----------------------------------------------------------------------------
      功    能：取得诊断程序版本
      参数说明：无
      返 回 值：诊断程序版本号，请定义一下宏DIAG_VERSION = xx.xx
      说    明：无
    -----------------------------------------------------------------------------*/    
    W_FLOAT GetDiagVersion();
    
protected:
    /*-----------------------------------------------------------------------------
      功    能：扫描存在的诊断系统，并记录之
      参数说明：无
      返 回 值：错误代码
      说    明：如果存在诊断系统，返回EC_SUCCESS
    -----------------------------------------------------------------------------*/
    virtual W_ErrorCode ScanSystem();
    
    /*-----------------------------------------------------------------------------
      功    能：显示车系主菜单
      参数说明：无
      返 回 值：无
      说    明：如果进行系统扫描，则本函数显示内容是动态的，不同汽车显示结果不同。
    -----------------------------------------------------------------------------*/
    virtual void MainProcess();
    
    /*-----------------------------------------------------------------------------
      功    能：创建诊断应用层
      参数说明：W_I16 iSequence -- 系统序号，本车系中所有诊断系统依次排序
      返 回 值：错误代码
      说    明：创建新系统应用层，将其指针赋值给m_pDiagnosisAppLayer；
                如m_pDiagnosisAppLayer不为空，则选释放之。
    -----------------------------------------------------------------------------*/
    virtual W_ErrorCode NewAppLayer(W_I16 iSequence);
   
public:
    CManufacturer();
    virtual ~CManufacturer();
    static CManufacturer* GetCurrentManufacturer();
    char * GetCarName();
    
    
protected:
    // 诊断应用层指针
    CAppLayerBase * m_pDiagnosisAppLayer;
    static CManufacturer* m_pCurrentManufacturer;
    char *m_pszCarName;
   
};

#define adsGetManufacturer()  ( (CONS(C,VEHICLE) *) CManufacturer::GetCurrentManufacturer() )


#endif /* MANUFACTURER_H_HEADER_INCLUDED_B980C1B5 */
