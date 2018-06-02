#ifndef CMENUTREE_H_HEADER_INCLUDED_B99C74B3
#define CMENUTREE_H_HEADER_INCLUDED_B99C74B3
#include <stack>
#include "DataSheet.h"
#include "UIMenu.h"
/******************************************************************************

    Copyright (c) 2007, AUTEL Ltd,.Co

    All rights reserved.

    文件名称：MenuTree.h

    档 标 识：菜单树显示类

    摘    要：当菜单较多，用代码实现较复杂时采用此类实现，此类与菜单库和菜单显示类
              完成多级复杂多级菜单显示

    历史记录：
    ---------------------------------------------------------------------------
    时     间           作者        版本号	  操    作    内    容 
    ---------------------------------------------------------------------------
    2007-6-4 15:03:00  panxiangxi    1.0      创建此类。
    2007-12-6          panxiangxi    1.1      添加对菜单ID是0xFFFFFFFF时 不显示
	2010-1-30          lishenlin     1.2      设置不显示特定ID菜单 ,可以区间不显示特定菜单

    使用范例如下：
    W_I32 MainMenuHandle(W_I32 iTaskId, CBinary idSelectedText)
    {
        。。。
    }

    CMenuTree tree;
    CBinary bin("\x41\xff\x00\x00\x00\x00", 6);
    tree.SetTaskCallBackFunction(MainMenuHandle);
    tree.ShowMenu(bin);

  ****************************************************************************/

#ifdef USE_DLL
class __declspec( dllexport ) CMenuTree
#else
class CMenuTree  
#endif
{
public:
	CMenuTree();
	virtual ~CMenuTree();	 
	
    /*-----------------------------------------------------------------------------
    功    能：显示菜单树
    参数说明：binMenuID             菜单ID(在Menu.tab中查询)
	          strFileName 如果字符串为空,则读取默认的文件,否则读取strFileName指向的文件
    返 回 值：失败返回-1，成功返回0
    说    明：显示前请先调用SetTaskCallBackFunction设置回调函数
    -----------------------------------------------------------------------------*/
	int ShowMenu (CBinary binMenuID,  const string& strFileName = "");

	// 回调函数声明
	typedef W_I32 (*PTaskFun) (W_U32 i32TaskId, CBinary binSelectedTextID);
	typedef W_I32 (*PTaskFun2)(CBinary binTaskID, CBinary binSelectedTextID);
	//颜家松 2012.3.29添加，每显示一次Menu，就调用该回调函数，给用户处理menu组件的机会
	typedef VOID (*PCallWhenShowMenu)(CBinary binTaskID, CUIMenu &uiMenu);
	typedef VOID (*PCallWhenClickSpecialBtn)(CBinary binTaskID);

	/*-----------------------------------------------------------------------------
    功    能：设置回调函数
    参数说明：返回值是W_32,带两个参数W_I32 i16TaskId, CBinary binSelectedTextID
              的函数
    返 回 值：无
    说    明：无
    -----------------------------------------------------------------------------*/
	void SetTaskCallBackFunction(PTaskFun pfnTask);

	void SetTaskCallBackFunction2(PTaskFun2 pfnTask);

	/*-----------------------------------------------------------------------------
	功    能：设置回调函数，当显示一个菜单页面时调用，用户可以藉此调整UIMenu
	参数说明：无
	的函数
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	void SetMenuShowCallBackFunction(PCallWhenShowMenu pfnCallBack);

	/*-----------------------------------------------------------------------------
	功    能：设置回调函数，当用户点击Help时调用，用户做Help操作
	参数说明：无
	的函数
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	void SetSpectialBtnClickCallBackFunction(PCallWhenClickSpecialBtn pfnCallBack);
	/*-----------------------------------------------------------------------------
	功    能：设置不显示特定ID菜单 ,可以区间不显示特定菜单
	参数说明：vctNoUseIDMin 不显示特定ID菜单的最小值容器
	          vctNoUseIDMax 不显示特定ID菜单的最大值容器
			  bIDAmongID    设置使用不显示特定区间菜单功能
	返 回 值：无
	说    明：最大值最小值容器设定必须一一对应,用户在设置vctNoUseIDMin 和vctNoUseIDMax时，不要有交集
	使用例子：
	CMenuTree menuTree;
	vector<UINT> vctNoUseIDMin;
	vector<UINT> vctNoUseIDMax;
	CBinary binMenuID;

	vctNoUseIDMin.push_back(0x00);
	vctNoUseIDMax.push_back(0xff);

	vctNoUseIDMin.push_back(0xfff);
	vctNoUseIDMax.push_back(0xffff);

	menuTree.SetNoUseMenuID(vctNoUseIDMin, vctNoUseIDMax, TRUE);
	menuTree.ShowMenu(binMenuID);
	-----------------------------------------------------------------------------*/
	// 设置不显示特定ID菜单 ,可以设定某些区间不显示菜单 0010150 CMenuTree类的相关需求 李审霖 添加 2010年1月28日11:39:33
	void SetNoUseMenuID(const vector<UINT>& vctNoUseIDMin, const vector<UINT>& vctNoUseIDMax, const BOOL bIDAmongID = FALSE);

protected:
    /*-----------------------------------------------------------------------------
      功    能: 显示一级菜单
      参数说明: binGroup            此级菜单对应的菜单文本ID，子菜单数
                iSelected           选中那一项菜单
      返 回 值: -1为返回上一级菜单,0-n为用户选择了那一级菜单
      说    明: 无
      2007-9-25 9:58:28
      -------------------------------------------------------------------------*/
    int ShowOneLevelMenu(CBinaryGroup &binGroup, int iSelected, unsigned int &uiScrollPos, CUIMenu** ppMenu, const string& strFileName = "");

    // 将其任务ID是0xFFFFFFFF的菜单不显示，删除
    void ProcessNoUseTaskID(CBinaryGroup &binGroup, const string& strFileName = "");
    
    // 菜单级结构
    struct  tgLevel{
        // 菜单ID
		CBinary binMenuID;
        // 菜单选中项
        W_I16 m_i16MenuSelected;
        // 屏幕首选项
        unsigned int m_i16MenuScreenFirstLineItem;        
    };
    // 菜单级结构
    typedef tgLevel  MENU_LEVEL;

    // 多级菜单栈
	stack <MENU_LEVEL> m_stackLevel;
	stack <CUIMenu*> m_stackUIMenu;

	//颜家松 2012.3.29 添加，当显示一个菜单页面时，调用该回调函数，用户可以处理UIMenu的一些初始化工作
	PCallWhenShowMenu m_pfnCallWhenShowMenu;
	//颜家松 2012.3.29 添加，当用户点击Help按钮时，告知用户，由用户处理
	PCallWhenClickSpecialBtn m_pfnCallWhenClickSpecialBtn;

    // 回调函数指针
    PTaskFun    m_pfnTask;
	PTaskFun2    m_pfnTask2;

	// 不显示菜单的最小值
	vector<UINT>  m_vctNoUseIDMin;

	// 不显示菜单的最大值
	vector<UINT>  m_vctNoUseIDMax;

	// 设置了不显示特点ID菜单的区间
	BOOL m_bAmongID;
};
#endif /* CMENUTREE_H_HEADER_INCLUDED_B99C74B3 */
