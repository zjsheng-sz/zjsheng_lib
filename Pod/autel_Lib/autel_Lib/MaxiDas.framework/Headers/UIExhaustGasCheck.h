#pragma once
//SHOW返回事件值 从公共头文件中移动到这里
#define RT_DEFAULT		-9			// 默认值
#define RT_STOP_CHECK	0			// 停止检测
#define RT_START_CHECK	1			// 开始检测

#define LIST_ITEM_QUICK_ENTRANCE_BASE   0X400 //快速进入组的初始值 返回item的初始累加值



#include "UIPubDefine.h"



class ImpExhaustGasCheck;
class __MYEXPORT__ CUIExhaustGasCheck
{
public:
	CUIExhaustGasCheck();
	~CUIExhaustGasCheck();

	CUIExhaustGasCheck(CUIExhaustGasCheck const&);
	CUIExhaustGasCheck const& operator = (CUIExhaustGasCheck const&);
	/*
	** 功    能:初始化激活界面数据，由底层库在显示界面之前调用
	** 参    数:无
	** 返 回 值:无
	** 说	 明:无
	*/
	void Init();

	/*
	** 功    能:启动显示废气检测界面
	** 参    数:
	*@param nPara  预留参数
	** 返 回 值:用户按下的按键,-1为回退
		#define RT_STOP_CHECK	0			// 停止检测
		#define RT_START_CHECK	1			// 开始检测
	** 说	 明:
	*/
	int Show_ml(int nPara = SHOW_DEFALUT);

	/*
	** 功    能:通知本次检测结束
	** 参    数:无
	** 返 回 值:无
	** 说	 明:无
	*/
	void NotifyCheckingOver();

	/*
	** 功    能:界面显示前，添加初始要显示的检测项数据
	** 参    数:
	* @param nItemID		检测项ID
	* @param nStatus		检测项所处状态值
	* @param strGroupName	检测项所在模块组描述
	* @param strItemName	检测项名称
	* @param strItemValue	检测项当前值
	* @param strMin			最小值
	* @param strMaxi		最大值
	* @param strItemUnit	检测项的单位
	** 返 回 值: 当前项id
	** 说	 明:无
	*/
	int AddItem(int nStatus, const string& strGroupName, const string& strItemName, const string& strItemValue, 
		const string& strMin, const string& strMax, const string& strItemUnit);

	/*
	** 功    能: 更新当前检测项的值
	** 参    数:
	* @param nItemId	检测项ID
	* @param strCurValue			检测项当前值
	** 返 回 值:无
	** 说	 明:无
	*/

	bool SetItem(int nItemId, const string& strItemValue);
	/*
	** 功    能: 更新当前检测项的检测进度和相关检测状态信息
	** 参    数:
	* @param nItemId	检测项ID
	* @param strRef		检测项范围
	** 返 回 值:无
	** 说	 明:无
	*/
	bool SetRef(int nItemId, const string& strMin, const string& strMax);

	/*
	** 功    能: 更新当前检测项的检测状态
	** 参    数:
	* @param nItemId	检测项ID
	* @param status		检测项所处状态值
	** 返 回 值:无
	** 说	 明:无
	*/
	bool SetStatus(int nItemId, int nStatus);

	/************************************************************************/
	/* 功  能：设置单位
	/* 参  数：@nItemId：id, @strUnit:单位
	/* 返回值：
	/* 说  明：
	/************************************************************************/
	bool SetUnit(int nItemId, const string& strUnit);



    //////////////////////////////////////////////////////////////////////////908移植UILIST begin

    /*-----------------------------------------------------------------------------
	功  能：显示组件
	参  数：bReturnImmediately 是否立即返回
	返回值：如果用户点击了按钮，在返回按钮编号
		    如果用户点击退出按钮，返回RT_Back
			如果用户点击了快速进入小按钮，则 被点击的项编号 = 返回值-LIST_ITEM_QUICK_ENTRANCE_BASE
			否则返回-10
	说  明：无
	-------------------------------------------------------------------------*/
    W_I16 Show(bool bReturnImmediately = false);
    W_I16 Show(int iData);     

	/*-----------------------------------------------------------------------------
	功  能：初始化，设置标题，设置列数及列宽
	参  数：
	strTitleText：标题
	vctColWidthPercent：列宽百分比
	返回值：无
	说  明：调用其他函数之前先调用该函数
	-------------------------------------------------------------------------*/
	void Init(const string &strTitleText, std::vector<unsigned char> vctColWidthPercent);

	/*-----------------------------------------------------------------------------
	功  能：设置第0行是否锁定作为列表标题
	参  数：
	bLock：是否锁定
	返回值：无
	说  明：无
	-------------------------------------------------------------------------*/
	void SetLockFirstRow(bool bLock);

	/************************************************************************/
	/* 功  能： 设置某列为单位列
	/* 参  数：	nValueCol: 值的列序号，从0开始
				nUnitCol：单位的列序号，从0开始
	/* 返回值： bool类型，如果nValueCol与nUnitCol相等，则返回false，否则true
	/* 说  明： 设置了单位列，则会自动进行公英制转换。注意：调用该函数后SetSubItem必须先设置单位，然后才设置值 add by zys 2016/11/08
	/************************************************************************/
	bool SetValueAndUnitColumn(int nValueCol, int nUnitCol);

	/*-----------------------------------------------------------------------------
	功  能：添加一个Item
	参  数：
	strText：第0列显示内容
	clrFore：前景色
	clrBack：背景色
	返回值：返回对应的行号
	说  明：无
	-------------------------------------------------------------------------*/
	W_I16 AddItem(string const& strText, COLORREF clrFore = -1, COLORREF clrBack = -1);

	/*-----------------------------------------------------------------------------
	功  能：设置一个Item的第0列
	参  数：
	nRow：行号
	strText：设置内容
	clrFore：前景色
	clrBack：背景色
	返回值：成功返回true
	说  明：无
	-------------------------------------------------------------------------*/
	bool SetItem(W_I16 nRow, string const& strText, COLORREF clrFore = -1, COLORREF clrBack = -1);

	/*-----------------------------------------------------------------------------
	功  能：设置一个Item的SubItem
	参  数：
	nRow：行号
	nCol：列号
	strText：设置内容
	clrFore：前景色
	clrBack：背景色
	返回值：成功返回true
	说  明：如果调用了SetValueAndUnitColumn，必须先设置单位，然后才设置值
	-------------------------------------------------------------------------*/
	bool SetSubItem(W_I16 nRow, W_I16 nCol, string const& strText, COLORREF clrFore = -1, COLORREF clrBack = -1);

	/*-----------------------------------------------------------------------------
	功  能：设置某项的快速进入功能
	参  数：nItem			行号
		    bEnable			是否启用
	返回值：无
	说  明：无
	-------------------------------------------------------------------------*/
	void EnableItemQuickEntrance(int nRow, bool bEnable);

	/*-----------------------------------------------------------------------------
	功  能：删除一个Item
	参  数：
	nRow：行号
	返回值：成功返回true
	说  明：无
	-------------------------------------------------------------------------*/
	bool DelItem(W_I16 nRow);

	/*-----------------------------------------------------------------------------
	功  能：删除所有Item
	参  数：无
	返回值：成功返回true
	说  明：无
	-------------------------------------------------------------------------*/
	bool RemoveAllItem();

	/*-----------------------------------------------------------------------------
	功  能：添加按钮
	参  数：
	strCaption：按钮标题
	返回值：返回按钮编号，从0开始,-1标示失败
	说  明：无
	-------------------------------------------------------------------------*/
	W_I16 AddButton(string const& strText);

	/*-----------------------------------------------------------------------------
	功  能：设置按钮名称
	参  数：
	strCaption：按钮标题
	返回值：成功返回true
	说  明：无
	-------------------------------------------------------------------------*/
	bool SetButtonCaption(W_I16 nBtnIndex, string const& strCaption);

	/*-----------------------------------------------------------------------------
	功  能：设置按钮是否可用
	参  数：
	bEnabled：是否可用
	返回值：成功返回true
	说  明：无
	-------------------------------------------------------------------------*/
	bool SetButtonEnabled(W_I16 nBtnIndex, bool bEnabled);

	/*-----------------------------------------------------------------------------
	功  能：设置按钮是否可见
	参  数：
	bVisibled：是否可见
	返回值：成功返回true
	说  明：无
	-------------------------------------------------------------------------*/
	bool SetButtonVisible(W_I16 nBtnIndex, bool bVisible);

	/*-----------------------------------------------------------------------------
	功  能：获取用户选择的行
	参  数：无
	返回值：返回用户选择的行
	说  明：无
	-------------------------------------------------------------------------*/
	W_I16 GetCurSelectItem();

	/*-----------------------------------------------------------------------------
	功  能：设置ESC按钮名称
	参  数：strText			名称
	返回值：无
	说  明：无
	-------------------------------------------------------------------------*/
	void SetEscBtnText(string const& strText);

	/*-----------------------------------------------------------------------------
	功  能：设置ESC按钮显示状态
	参  数：bVisible		是否显示
	返回值：无
	说  明：无
	-------------------------------------------------------------------------*/
	void SetEscBtnVisible(bool bVisible);

	/*-----------------------------------------------------------------------------
	功  能：设置ESC按钮可用状态
	参  数：bEnable			是否可用
	返回值：无
	说  明：无
	-------------------------------------------------------------------------*/
	void SetEscBtnEnable(bool bEnable);

	// 设置为可选项 add [2016/10/24 A15386]
	void EnableItemSelect(int nRow, bool bEnable);

	// 该行文字居中，默认左对齐 add [2016/10/25 A15386]
	void SetItemTextCenter(int nRow, bool bTextCenter);

	// 设置该行行高，不设置使用默认值 add [2016/10/25 A15386]
	void SetItemHeight(int nRow, int nHeight);

    // 清除选中的行 add [2017/03/03 A16130]
    void ClearSelectItem();
    //////////////////////////////////////////////////////////////////////////908移植 end
private:
	ImpExhaustGasCheck* m_pImpExhaustGasCheck;
};
