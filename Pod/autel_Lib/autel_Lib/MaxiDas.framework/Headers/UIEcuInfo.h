#pragma once
#include "UIPubDefine.h"
#include "Binary.h"

//SHOW返回事件值 这个是旧的 暂时不知道啥意思
const int ECUINFO_BTN_OK = 1;
const int ECUINFO_BTN_CLEAR = 4;
const int ECUINFO_OK_CLICK = -2;
const int ECUINFO_CLEAR_CLICK = -3;



//SHOW返回事件值 新的定义 为了防止冲突 从100开头
#define ECUINFO_JUMP_SELECT_CAR_YEAR        100         // 跳转到车辆年款页面
#define ECUINFO_SHOW_SELECT_VEHICLE_DLG	    101         // 通知显示选择车系对话框
#define ECUINFO_SHOW_PARSE_VIN_TIP_DLG	    102         // 通知显示“会和车辆通讯可能耗时较长，确定要执行吗？”的提示对话框
#define ECUINFO_SET_NAME_BRAND_YEAR_AREA    103         // 通知设置了车系名称 车辆品牌 年款 区域



class ImpCarInfo;
class __MYEXPORT__ CUIEcuInfo
{
public:
	CUIEcuInfo();
	~CUIEcuInfo();

	CUIEcuInfo(CUIEcuInfo const&);
	CUIEcuInfo const& operator = (CUIEcuInfo const&);
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
	int Show_ml(int nPara = SHOW_CARINFO_SHOW);

	/*
	** 功    能:检测到VIN码后将VIN码告诉UI线程
	** 参    数:
	* @param strVinCode	VIN码
	** 返 回 值:用户按下的按键,-1为回退
	** 说	 明:无
	*/
	void ReportVinCodeToUI(string strVinCode);

	/*
	** 功    能:设置是否支持高级功能
	** 参    数:
	* @param bEnable true 支持;false 不支持
	** 返 回 值:用户按下的按键,-1为回退
	** 说	 明:无
	*/
	void EnableSuportEnhance(bool bEnable);

	string GetVinCode();//获取由安卓传过来的Vin码
	string GetBrand();//获取由安卓传过来的品牌
	string GetYear();//获取由安卓传过来的年份



    //////////////////////////////////////////////////////////////////////////908移植UIEcuInfo.h begin

    /*-----------------------------------------------------------------------------
	功    能：初始化菜单
	参数说明：binTitleTextID    对话框标题文本ID(在en_text.tab中查询) 
				strTitleText	标题
				bEobd			是否为EOBD，EOBD做了特殊处理
	返 回 值：无 
	说    明：在文本库中查询,然后调用 void Init(string strTitleText = NULL)
	-----------------------------------------------------------------------------*/
	void Init(const string &strTitleText, bool bEobd = false);
	void Init(CBinary const& binTitleTextID, bool bEobd = false);


	/*-----------------------------------------------------------------------------
	功    能：添加一项
	参数说明：strName				名称
				strValue			值
				binNameID			名称ID

	返 回 值：失败					-1
				成功				添加的位置(0-n)  
	说    明：此时同时进行名称与值的内容排版,结果放入到m_vctString中以供显示调用
	-----------------------------------------------------------------------------*/
	W_I16 Add (const string &strName, const string &strValue);
	W_I16 Add (CBinary binNameID, const string &strValue);

	/*-----------------------------------------------------------------------------
	功    能：修改某项的值
	参数说明：nItem				项编号
			  strValue			值
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	void SetValue(int nItem, string const& strValue);

	/*-----------------------------------------------------------------------------
	功    能：添加一个组
	参数说明：strGroupName				组名称
				binNameID				名组称ID
	返 回 值：无					
	说    明：添加分组功能，将Item划分为不同的组
	-----------------------------------------------------------------------------*/
	void AddGroupName(string const& strGroupName);
	void AddGroupName(CBinary const& binGroupName);

	/*-----------------------------------------------------------------------------
	功    能：显示
	参数说明：无
	返 回 值：如果点击某项则返回点击项 否则返回 NOT_CLICKED_RETURN
	说    明：调用基类ShowTextMode
	历史记录：
	---------------------------------------------------------------------------
	时     间           作者        版本号	  修    改    内    容 
	---------------------------------------------------------------------------
	2009-12-22          李审霖      2.0       解决界面假死现象,调用者需要在
	-----------------------------------------------------------------------------*/
	int Show ();
    int Show(int iData);

	/*-----------------------------------------------------------------------------
	功    能: 设置按钮名称
	参数说明: btnType 对应的按钮，sCaption 名称
	返 回 值: 设置之前的名称
	作    者：颜家松 2011.5.16
	原    因：新增需求
	-------------------------------------------------------------------------*/
	void SetButtonCaption(int btnType, string const& sCaption);

	/*-----------------------------------------------------------------------------
	功    能: 版本信息的两种模式，一种为纯显示，另外一种为可点击进行进一步操作
	参数说明: bEnableMenu为true，可以点击，否则不可点
	          bEnableMenuBtnOk   OK按钮是否可用，已经被忽略
			  bEnableMenuBtnClear  Clear按钮是否可用，已经被忽略
	返 回 值: 无
	-------------------------------------------------------------------------*/
	void EnableMenu(bool bEnableMenu, bool bEnableMenuBtnOk, bool bEnableMenuBtnClear);

	/*-----------------------------------------------------------------------------
	功    能: lshl 添加 0008098 ImpEcuInfo函数能否修改为实时返回值和数据流等相同？目前是只有按键的时候才返回值
			  设置显示视图后如果不按键就立即返回值
	参数说明: bShowThenReturn 是否为非阻塞调用
	返 回 值: 无
	-------------------------------------------------------------------------*/
	void SetShowThenReturn(bool bShowThenReturn = true);

	/*-----------------------------------------------------------------------------
	功    能: 禁用保存功能
	返 回 值: 无
	说    明：已经忽略
	-------------------------------------------------------------------------*/
	void DisableSaveFuction();

	/*-----------------------------------------------------------------------------
	功    能: 设置某项可见（通过自动调整滚动条）
	返 回 值: nItem   待设置项编号
	说    明：无
	-------------------------------------------------------------------------*/
	void EnsureItemVisible(int nItem);
#ifdef PLAY_BACK
	void SetTestTime(time_t tmTest);
	time_t GetTestTime() const;
#endif

    //////////////////////////////////////////////////////////////////////////908移植 end
private:
	ImpCarInfo* m_pImpCarInfo;
};
