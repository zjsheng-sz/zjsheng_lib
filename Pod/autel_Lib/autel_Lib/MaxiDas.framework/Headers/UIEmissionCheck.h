#pragma once

//SHOW返回事件值 从公共头文件中移动到这里
#define RT_DEFAULT		-9			// 默认值
#define RT_STOP_CHECK	0			// 停止检测
#define RT_START_CHECK	1			// 开始检测


//AddItem SetItem 的 state 检测状态定义
#define CHECK_STATE_NOT_CHECK               0x0     //还未检测状态
#define CHECK_STATE_CHECKING                0x1     //检测中状态
#define CHECK_STATE_FINISHED_PASSED         0x2     //检测完成
#define CHECK_STATE_FINISHED_NOT_PASSED     0x3     //检测不通过
#define CHECK_STATE_FINISHED_PROBLEM        0x4     //检测未完成
#define CHECK_STATE_FINISHED_NOT_SUPPORTED  0x5     //不支持
#define CHECK_STATE_FINISHED_LIGHT_ON       0x6     //故障灯亮
#define CHECK_STATE_FINISHED_LIGHT_OFF      0x7     //故障灯灭



#include "UIPubDefine.h"
#include "Binary.h"



class ImpEmissionCheck;
class __MYEXPORT__ CUIEmissionCheck
{
public:
	CUIEmissionCheck();
	~CUIEmissionCheck();

	CUIEmissionCheck(CUIEmissionCheck const&);
	CUIEmissionCheck const& operator = (CUIEmissionCheck const&);

	/*
	** 功    能:初始化激活界面数据
	** 参    数:无
	** 返 回 值:无
	** 说	 明:无
	*/
	void Init();

	/*
	** 功    能:启动显示排放检测界面
	** 参    数:
	* @param nPara	预留
	** 返 回 值:用户按下的按键,-1为回退
	** 说	 明:#define RT_BACK			-1			// 回退
				#define RT_STOP_CHECK		0		// 停止检测
				#define RT_START_CHECK		1		// 开始检测
	*/
	int Show_ml(int nPara = SHOW_DEFALUT);

	/*
	** 功    能:通知本次检测结束
	** 参    数:无
	** 返 回 值:无
	** 说	 明:无
	*/
	void NotifyCheckingOver();

	/**
	* 功    能:添加一项检测模块信息
	**参    数:
	* @param nState			检测项当前状态
	* @param strGroupName 	检测项所在模块组描述
	* @param strItemName	检测项名字
	* @param strDescribe	检测项相关描述信息
	** 返 回 值: 当前项的下标
	** 说	 明: nState取值如下：
        #define CHECK_STATE_NOT_CHECK               0x0     //还未检测状态
        #define CHECK_STATE_CHECKING                0x1     //检测中状态
        #define CHECK_STATE_FINISHED_PASSED         0x2     //检测完成
        #define CHECK_STATE_FINISHED_NOT_PASSED     0x3     //检测不通过
        #define CHECK_STATE_FINISHED_PROBLEM        0x4     //检测未完成
        #define CHECK_STATE_FINISHED_NOT_SUPPORTED  0x5     //不支持
        #define CHECK_STATE_FINISHED_LIGHT_ON       0x6     //故障灯亮
        #define CHECK_STATE_FINISHED_LIGHT_OFF      0x7     //故障灯灭
	*/
	int AddItem_ml(int nState, const string& strGroupName, const string& strItemName, const string& strDescribe);

	/**
	* 用于设置当前检测项的相关检测进度、状态信息
	* @param state
	* @param unitName
	* @param troubleCode
	*/
	bool SetItem_ml(int nItemID, int nState, const string& strTroubleCode);


    int GetItemCount_ml();

    //////////////////////////////////////////////////////////////////////////908移植ActTest begin

    /*-----------------------------------------------------------------------------
	功    能: 设置第一行是否锁定
	参数说明: bLock                 是否锁定
	返 回 值: 无
	说    明: 无
	-------------------------------------------------------------------------*/
	void SetLockFirstRow(bool bLock);

	/*-----------------------------------------------------------------------------
	功    能: 初始化
	参数说明: strTitle                 标题
			  ui16Type                 DS_VW时，ESC按钮显示为OK，否则为ESC
			  bShowUnitAlways		   是否总是显示单位，即使为非数值情况下
	返 回 值: 无
	说    明: 无
	-------------------------------------------------------------------------*/
	void Init (const string &strTitle, W_U16 ui16Type = DS_STD, bool bShowUnitAlways = false);
	void Init (CBinary binTitle, W_U16 ui16Type = DS_STD, bool bShowUnitAlways = false);

	/*-----------------------------------------------------------------------------
	功    能: 添加一个按钮
	参数说明: binID					名称ID
				strCaption			按钮名称
				bLock				此参数不起作用,如果要设置功能请用下面三个参数的
	返 回 值: -1                    添加失败
				0-n                 添加成功
	说    明: 无
	-------------------------------------------------------------------------*/
	W_I16 AddButton (CBinary binID, bool bLock = false);
	W_I16 AddButton (const string &strCaption, bool bLock = false);

	/*-----------------------------------------------------------------------------
	功    能: 设置按钮文本并可设置是否是固定不移动的
	参数说明: strBtnText     按钮文本
			  bEnable        按钮是否可用
			  isLocked		 按钮是否锁定不可移动
	返 回 值:无
	说    明:无
	-----------------------------------------------------------------------------*/
	W_I16 AddButton(string strBtnText, bool bEnable, bool isLocked);
	/*-----------------------------------------------------------------------------
	功    能: 修改按钮名称
	参数说明: iBtnIndex				按钮编号
				binID				名称ID
				strCaption			按钮名称
	返 回 值: -1                    添加失败
				0-n                 添加成功
	说    明: 无
	-------------------------------------------------------------------------*/
	void SetButtonText(W_I16 iBtnIndex, const string &strCaption);

	/*-----------------------------------------------------------------------------
	功    能: 修改按钮状态
	参数说明: iBtnIndex				按钮编号
				bEnabled			是否可用
	返 回 值: -1                    添加失败
				0-n                 添加成功
	说    明: 无
	-------------------------------------------------------------------------*/
	bool SetButtonStatus(W_I16 iBtnIndex, bool bEnabled);

	/*-----------------------------------------------------------------------------
	功    能: 添加一条数据流项
	参数说明: binDataStreamID			数据流ID
				binUnitID				单位ID
				strName					名称
				binUnitID				单位ID
	返 回 值: -1						添加失败
				0-n						添加成功
	说    明: 无
	-------------------------------------------------------------------------*/
	//W_I16 Add(CBinary binDataStreamID);
	//W_I16 Add(const string &strName);
	W_I16 Add(CBinary const& binDataStreamID, CBinary const& binUnitID = CBinary());
	W_I16 Add(const string &strName, const string &strUnit = "");

	/************************************************************************
	功    能：设置某行为标题
	参数说明：i16Index                      那一个项
	返 回 值：无
	说    明：无                                                                  
	************************************************************************/
	void SetItemAsTitle(W_I16 iIndex, bool bTitle = true);


	/*-----------------------------------------------------------------------------
	功    能：设置选项
	参数说明：i16Index                      那一个项
	binDataStreamID               数据流ID
	strDataStreamValue            数据流值
	返 回 值：-1                            为不成功    
	等于iIndex为                  设置成功
	说    明：无 
	-----------------------------------------------------------------------------*/
	W_I16 SetItem(W_I16 iIndex, string const& strDataStreamValue);
    bool SetItemState(int iIndex, int nState); //非908的  新添加的


	///*-----------------------------------------------------------------------------
	//功    能：重置单位
	//参数说明：iIndex				那一个项
	//			strUnit				单位
	//返 回 值：-1                    为不成功    
	//	等于iIndex为                 设置成功
	//说    明：无 
	//-----------------------------------------------------------------------------*/
	void SetUnit(W_I16 iIndex, const string &strUnit);

	///*-----------------------------------------------------------------------------
	//功    能：设置名称
	//参数说明：i16Index                      索引
	//		strName							数据流名称
	//返 回 值：-1                            为不成功    
	//		等于iIndex为					设置成功
	//说    明：无 
	//-----------------------------------------------------------------------------*/
	void SetName(const W_I16 nIndex, const string &strName);

	// 禁用ESC按钮
	void EnableEsc(bool bEnable);

	/*-----------------------------------------------------------------------------
	功    能：
	参数说明：
	返 回 值：-1                 退出
	0-n				 按了某个按钮			
	说    明：无
	-----------------------------------------------------------------------------*/
    W_I16 Show();
    W_I16 Show(int iData);

	/*-----------------------------------------------------------------------------
	功    能：取得某个选项是否要更新
	参数说明：iIndex                        那一个项
	返 回 值：true                          需要更新
				false                       不需要更新
	说    明：缓式更新value
	-----------------------------------------------------------------------------*/
	bool GetItemUpdate(W_I16 iIndex);

	/*-----------------------------------------------------------------------------
	功    能：获取当前选项
	参数说明：无                     
	返 回 值：当前选中项  
	说    明：无 
	2010-9-15  lshl add
	-----------------------------------------------------------------------------*/
	W_I16 GetCurSelected(void);


	/*-----------------------------------------------------------------------------
	功    能：设置显示最后一行
	参数说明：无
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	void ScrollToEnd();

	/*-----------------------------------------------------------------------------
	功    能：设置各列宽度
	参数说明：无
	返 回 值：无
	说    明：三个值加起来为100
	-----------------------------------------------------------------------------*/
	bool SetColWidth(W_U16 iColName, W_U16 iColValue, W_U16 iColUnit);

	/*-----------------------------------------------------------------------------
	功    能：设置焦点按钮
	参数说明：无
	返 回 值：无
	说    明：Android上未实现该功能
	-----------------------------------------------------------------------------*/
	void SetButtonFocus(W_I16 iBtnIndex);

	/*-----------------------------------------------------------------------------
	功    能：获取总数
	参数说明：无
	返 回 值：总数
	说    明：无
	-----------------------------------------------------------------------------*/
	int GetItemCount(void);

	/*-----------------------------------------------------------------------------
	功    能：删除某一行
	参数说明：行号
	返 回 值：成功返回true，否则返回false
	说    明：无
	-----------------------------------------------------------------------------*/
	bool DelItem(int nItem);

	/*-----------------------------------------------------------------------------
	功    能：设置当前选择行
	参数说明：待设置行号
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	void SetCurSelected(int nItem);

	/*-----------------------------------------------------------------------------
	功    能：清空
	参数说明：无
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	void Clear();

	// add by zys 2016/03/21 应李良川要求添加获取按钮文本接口
	const string& GetButtonText(int nIndex);
	// 获取按钮个数
	int GetButtonCount();
	// end 2016/03/21

	/*-----------------------------------------------------------------------------
	功    能：在界面上，item是否可以选择。 add by zys 2016/12/20 
	参数说明：bEnable: true-可以选择，false-不能选择
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	void EnableItemClick(bool bEnable);

    //////////////////////////////////////////////////////////////////////////908移植 end
private:
	ImpEmissionCheck *m_pImpEmissionCheck;
};
