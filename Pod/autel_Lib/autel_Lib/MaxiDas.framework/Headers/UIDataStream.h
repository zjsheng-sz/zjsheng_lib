#pragma once

//SHOW返回事件值 从公共头文件中移动到这里
#define PRE_CHANNEL			2000
#define NEXT_CHANNEL		2001
//-3 这个不知道是哪个宏


#include "UIPubDefine.h"
#include "Binary.h"
#include "resource.h"

class ImpDataStream;
class __MYEXPORT__ CUIDataStream
{
public:
	CUIDataStream();
	~CUIDataStream();

	CUIDataStream(CUIDataStream const&);
	CUIDataStream const& operator = (CUIDataStream const&);
	/*
	** 功    能:初始化激活界面数据，由底层库在显示界面之前调用
	** 参    数:无
	** 返 回 值:无
	** 说	 明:无
	*/
	void Init();

	/*
	** 功    能:启动显示数据流界面
	** 参    数:
	* @param nPara	预留
	** 返 回 值:用户按下的按键,-1为回退
	** 说	 明:无
	*/
	int Show_ml(int nPara = SHOW_DEFALUT);

	/*
	** 功    能:添加数据流
	** 参    数:
	* @param strName	名字
	* @param strUnit	单位
	* @param strRef		取值范围
	** 返 回 值: 当前项, -1表示添加失败
	** 说	 明:无
	*/
	int AddItem(const string &strName, const string &strPID, const string &strUnit, string const& strRef);

	/*
	** 功    能:更改数据流名称
	** 参    数:
	* @param nItemID	数据流序号
	* @param strName	名字
	** 返 回 值:
	*@param true		成功
	*@param false		失败
	** 说	 明:无
	*/
	bool SetName(int nItemID, const string& strName);

	/*
	** 功    能:更改数据流的值
	** 参    数:
	* @param nItemID	数据流序号
	* @param strValue	数据流值
	* @param isDigit	是否为数字值
	** 返 回 值:
	*@param true		成功
	*@param false		失败
	** 说	 明:无
	*/
	bool SetItem_ml(int nItemID, const string& strValue, bool bDigit = false, bool bSupport = true);

	/*
	** 功    能:更改数据流的单位
	** 参    数:
	* @param nItemID	数据流序号
	* @param strUnit	单位
	** 返 回 值:
	*@param true		成功
	*@param false		失败
	** 说	 明:无
	*/
	bool SetUnit_ml(int nItemID, const string& strUnit);
	/*
	** 功    能:更改数据流取值范围
	** 参    数:
	* @param nItemID	数据流序号
	* @param strRef		取值范围
	** 返 回 值:
	*@param true		成功
	*@param false		失败
	** 说	 明:无
	*/
	bool SetRef(int nItemID, const string &strRef);

	/*
	** 功    能:添加数据流
	** 参    数:
	* @param nItemID		数据流序号
	* @param bExistHelpInfo	是否有帮助信息
	* @param strHelpInfo	帮助信息
	** 返 回 值:
	*@param true		成功
	*@param false		失败
	** 说	 明:无
	*/
	bool SetHelp(int nItemID, bool bExistHelpInfo, const string& strHelpInfo = "");

	/*
	**功    能：获取所有能需要更新的项
	**参数说明：
	* @paramvctSelected   输出所有需要更新的项
	**返 回 值：
	*@param true		成功
	*@param false		失败
	**说    明：无
	*/
	//bool GetItemUpdate(vector<int>& vctSelected);

	/*
	**功    能：某一项数据流是否需要更新
	**参数说明：
	* @param nItemID	数据流序号
	**返 回 值：
	*@param true		需要更新
	*@param false		不需要更新
	**说    明：无
	*/
	bool ItemNeedUpdate(int nItemID);

	/*
	**功    能：获取数据流的总数
	**参数说明：无
	**返 回 值：数据流总数
	**说    明：无
	*/
	//unsigned int GetItemCount();

	/*
	**功    能：取值范围是否可见
	**参数说明：
	*@param bVisibled true可见; false 不可见
	**返 回 值：无
	**说    明：无
	*/
	void EnableRefCol(bool bVisibled);

    //////////////////////////////////////////////////////////////////////////2017/05/18 添加四个新接口
    void SetItemPID(int nItem, const string & pid); //允许show之前调用
    void SetItemGroupName(int nItem, const string  & groupName); //允许show之前调用
    vector<int> QueryAllVisibleItems();
    void SetItemSupport(int nItem, bool isSupport); //允许show之前调用
    void SetItemDescription(int nItem, const string  & description); //允许show之前调用


    //////////////////////////////////////////////////////////////////////////908移植 begin
    
    /*-----------------------------------------------------------------------------
	功    能: 初始化
	参数说明: strTitle & binTitle        标题
			  ui16Type                   忽略
	返 回 值:无
	说    明: 无
	-------------------------------------------------------------------------*/
	void Init(const string &strTitle, W_U16 ui16Type = 0);
	void Init(CBinary const& binTitle, W_U16 ui16Type = 0);
	/*-----------------------------------------------------------------------------
	功    能: 设置按钮文本, 默认设置ID_Btn_OK_的文本
	参数说明: strBtnText         按钮文本
	nButtonID          按钮ID
	返 回 值:无
	说    明: 无
	2009年10月27日14:50:48
	-------------------------------------------------------------------------*/
	void SetButtonText(const string& strBtnText, const unsigned int nButtonID = ID_Btn_OK_);

	/*-----------------------------------------------------------------------------
	功    能: 设置参考值列
	参数说明: bVisibled					为true时显示，否则不显示
				bLimitValueFromRef		参考值为包含最大最小值的字符串  
				strSeparator			最大最小值之间的分隔符
	返 回 值: 无                  
	说    明: 1.EnableReferenceColumn()该函数务必在add() SetItem()调用之前(2010-2-25)
	-------------------------------------------------------------------------*/
	void EnableReferenceColumn(bool bVisibled, bool bFromReferenceName = false, string const& strSeparator = "...");
	


	/*-----------------------------------------------------------------------------
	功    能: 添加一条数据流项
	参数说明: binDataStreamID			数据流ID
				binUnitID               数据流单位ID 
	返 回 值: -1						添加失败
				0-n                     添加成功
	说    明: 无
	2007-9-18 11:32:50
    //必须放在SHOW前面调用
	-------------------------------------------------------------------------*/
	W_I16 Add(CBinary const& binDataStreamID, CBinary const& binUnitID = CBinary(), string const& strReferenceName = string());


	/*-----------------------------------------------------------------------------
	功    能: 添加一条数据流项
	参数说明:
	返 回 值: 
	说    明: 使用者如果传入参考值，那么传入的参考值必须符合以下规范，否则会弹出异常
	因为在程序内部如果要替代所有空格效率会比较低下,所以传入的数值不要有空格
	(如果用户本意并没有传递参考值时,只要有0.00的情况出现就是因为参考值有空格引起的)
	如果需要添加新的格式，请通知
	ok/cancel/yes/no 如果用户需要设置参考值为指定字符串,则需用/隔开,如果value值不再该范围,会显示红色
	（99,100是任意数字）
	100
	100.0
	<100
	<=100
	>100
	>=100
	<=99:>=100
	<=99:>100
	<99:>=100
	<99:>100
	99...100
	[99...100]
	(99...100)
	[99...100)
	(99...100]
	2010-1-4 15:01:05
	-------------------------------------------------------------------------*/
	W_I16 Add(const string &strDsName,const string &strDsUnit=string(), string const& strReferenceName = string());
	//W_I16 Add(const string &strDsName);

	/*-----------------------------------------------------------------------------
	功    能：设置选项
	参数说明：i16Index							那一个项
				binDataStreamID					数据流ID
				strDataStreamValue				数据流值
				bSetValueColor					设置颜色(用户如果设置为FALSE,strDataStreamValue为特殊字符串不与参考值进行比较,颜色不改变,慎用)
	返 回 值：-1								为不成功    
				等于iIndex为					设置成功
	说    明：无 
	用户可以输入的字符串如下:x123, x123.5, @+x123.5, @-x123.5,@+x, 123.5, -123.5, +123.5, 123.5x, 12345678901235(大于99999999999999999.999即16位数时即认定为字符串)
	@-123.5, @+123.5
	-----------------------------------------------------------------------------*/
	W_I16 SetItem(W_I16 iIndex, const string &strDataStreamValue, bool bSetValueColor = true);
	// add by zys 2015.8.26 添加bTextShow参数，为true的话直接文本方式显示。默认为false，兼容原有方式
	W_I16 SetItemEx(W_I16 iIndex, const string &strDataStreamValue, bool bSetValueColor = true, bool bTextShow = false);
	W_I16 SetUnit(W_I16 iIndex, const string &strUnit);
	void SetTitle(const string &strUnit);
	/*-----------------------------------------------------------------------------
	功    能：设置范围
	参数说明：无
	返 回 值：W_I16     用户按下的按键,-1为回退
	说    明：无
	-----------------------------------------------------------------------------*/
	W_I16 SetRef(W_I16 iIndex, const string &strRef);
	/*-----------------------------------------------------------------------------
	功    能：显示并选择用户返回
	参数说明：无
	返 回 值：W_I16     用户按下的按键,-1为回退
	说    明：可绘制数据流文本和图形
	注意:1.在同一个函数中不能连续调用,否则会引起无法正确捕获键值,导致无法退出界面(2010-2-25)
	-----------------------------------------------------------------------------*/
	W_I16 Show(void);

	/*-----------------------------------------------------------------------------
	功    能：取得选项个数
	参数说明：无
	返 回 值：W_I16        选项的个数
	说    明：无 
	-----------------------------------------------------------------------------*/
	W_I16 GetItemCount();

	/*-----------------------------------------------------------------------------
	功    能：取得某个选项是否要更新
	参数说明：iIndex                        那一个项
	返 回 值：true                          需要更新
	false                         不需要更新
	说    明：无
	-----------------------------------------------------------------------------*/
	bool GetItemUpdate(W_I16 iIndex);

	/*-----------------------------------------------------------------------------
	功    能：获取所有能需要更新的项
	参数说明：vctSelected                   输出所有需要更新的项
	返 回 值：成功返回true，否则返回false
	说    明：无
	-----------------------------------------------------------------------------*/
	bool GetItemUpdate(vector <int> &vctSelected);


	/*-----------------------------------------------------------------------------
	功    能：颜家松 2011.7.6 应 赵哲波需求，增加修改帮助按钮的名称的方法：
	参数说明：iIndex                   项编号
			  bHaveHelp                帮助按钮是否可用
			  strBtnCaption            帮助按钮名称
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	void SetHelp(W_I16 iIndex, bool bHaveHelp, const string& strBtnCaption = "");

	/*-----------------------------------------------------------------------------
	功    能：禁用保存功能
	参数说明：无
	返 回 值：无
	说    明：空实现
	-----------------------------------------------------------------------------*/
	void DisableSaveFuction();


	/*-----------------------------------------------------------------------------
	功    能: 清空所有数据流项
	参数说明: 无
	返 回 值: 无
	说    明: 无
	2007-6-26 15:10:45
	-------------------------------------------------------------------------*/
	void ClearDataStreamVector();

	/*-----------------------------------------------------------------------------
	功    能: 不详
	参数说明: 无
	返 回 值: 无
	说    明: 空实现
	-------------------------------------------------------------------------*/
	void EnableAutoUnit(bool bEnable);

	/*-----------------------------------------------------------------------------
	功    能: 扩展按钮功能启用和关闭
	参数说明: 无
	返 回 值: 无
	说    明: 无
	2007-6-26 15:10:45
	-------------------------------------------------------------------------*/
	void EnableExOK(bool bEnable);

	/*-----------------------------------------------------------------------------
	功    能: DTC自动触发保存功能的开关
	参数说明: 无
	返 回 值: 无
	说    明: 未实现
	-------------------------------------------------------------------------*/
	void EnableDtcEraseRecording(bool bEnable);

	/*-----------------------------------------------------------------------------
	功    能: DTC自动触发保存功能的辅助函数，诊断程序通过该接口设置
	参数说明: 无
	返 回 值: 无
	说    明: 未实现
	-------------------------------------------------------------------------*/
	void SetDTC(int nDtc);

#ifdef PLAY_BACK
	//颜家松 2012-7-13 添加，在回放状态时，需要记录下测试时间，以便打印时使用

	void SetTestTime(time_t tmTest);
	time_t GetTestTime() const;
#endif
    //////////////////////////////////////////////////////////////////////////908移植 end
private:
	ImpDataStream* m_pImpDataStream;
};
