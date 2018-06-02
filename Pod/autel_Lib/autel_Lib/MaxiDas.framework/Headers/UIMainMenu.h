#pragma once
#include "UIPubDefine.h"



class ImpMainMenu;
class __MYEXPORT__ CUIMainMenu
{
public:
	CUIMainMenu(void);
	~CUIMainMenu(void);

	CUIMainMenu(CUIMainMenu const&);
	CUIMainMenu const& operator = (CUIMainMenu const&);

	/*
	** 功    能:初始化激活界面数据，由底层库在显示界面之前调用
	** 参    数:无
	** 返 回 值:无
	** 说	 明:无
	*/
	void Init();

	/*
	** 功    能:启动显示首页界面 
	** 参    数:
	* @param nPara 预留参数
	** 返 回 值:用户按下的按键,上面宏定义中的值和-1(回退)
	** 说	 明:无
	*/
	int Show(int nPara = SHOW_DEFALUT);

	/*
	** 功    能:添加一条菜单项数据
	** 参    数:
	* @param nItemID	序号ID,必须是上面宏定义中的
	* @param strDesc	菜单显示的字符
	* @param bVisible	是否可见
	** 返 回 值: true 添加成功 false添加失败(id已经存在)
	** 说	 明:
	*/
	bool AddItem(int nItemID, const string& strDesc,  bool bVisible = true);

private:
	ImpMainMenu *m_pImpMainMenu;
};
