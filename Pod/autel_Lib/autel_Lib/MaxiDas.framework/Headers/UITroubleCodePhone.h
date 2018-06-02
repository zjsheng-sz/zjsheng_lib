#pragma once
#include "UIPubDefine.h"
#include "Binary.h"

//SHOW返回事件值 从公共头文件中移动到这里
// 故障码返回值
#define RT_DTC_START_SCAN		0 // 开始扫描故障码
#define RT_DTC_STOP_SCAN		1 // 停止扫描故障吗
#define RT_DTC_SET_SUBSYSTEMID	2 // 设置需要扫描子系统的ID,可以通过GetScanSubSystemID()接口获取
#define RT_DTC_SET_CLEARTYPE	3 // 设置需要清除故障码的类型,可以通过GetClrDTCType()接口获取
#define RT_DTC_CLEARLL			4 // 清除所有的故障码
#define RT_DTC_JUMPTO_FREEZEUI	5 // 跳到冻结帧界面
#define RT_DTC_JUMPTO_CARINFO	6 // 跳到车辆信息界面
#define RT_DTC_START_SCANITEM	7 // 开始扫描某项
// end 故障码返回值

//show的参数
#define SHOW_DTC_SHOW		    0       // 故障码
#define SHOW_DTC_CLEAR		    1       // 清除故障码
#define SHOW_DTC_NOTLOCK        -2      // 故障码不阻塞
#define SHOW_DTC_CLEAR_NOTLOCK  -3      // 清故障码不阻塞




typedef enum _ScanStatus
{
	SCAN_STATE_UNDO,		//未扫描
	SCAN_STATE_DOING,	//扫描中
	SCAN_STATE_DONE		//扫描完成
}ScanStatus;

typedef enum _DTCItemType
{
	TROUBLE_CODE_TYPE_CONFIRMED = 0,
	TROUBLE_CODE_TYPE_PENDING,	
	TROUBLE_CODE_TYPE_PERMANENT,	
	TROUBLE_CODE_TYPE_ENHANCED	
}DTCItemType;

//////////////////////////////////////////////////////////////////////////移值908 begin
// 故障码显示(一般都这样用)
const int TROUBLE_CODE_DC_SHOW = 0;
// 仅故障码查询使用(此时按上下键将会返回)
const int TROUBLE_CODE_DC_FIND = 1;

// 回调函数声明
class CBinary;
typedef string (*PNoFoundDtcProcess) (CBinary binID);
const int TROUBLE_CODE_BTN_FREEZE_FRAME = 1;
const int TROUBLE_CODE_BTN_HELP = 2;
const int TROUBLE_CODE_BTN_CLEAR_DTC = 3;
const int TROUBLE_CODE_BTN_SAVE = 4;

const int TROUBLE_CODE_HELP_BASE = 0x4000;
const int NEXT_DTC = 0x03;
const int LAST_DTC = 0x04;

#define DF_ClearDTC      1004
#define DF_ClearDTCrt	0x4FFF

const int g_nHelpStartKeyValue = TROUBLE_CODE_HELP_BASE;
//////////////////////////////////////////////////////////////////////////移值908 end


class ImpTroubleCodePhone;
class __MYEXPORT__ CUITroubleCodePhone
{
public:
	CUITroubleCodePhone();
	~CUITroubleCodePhone();

	CUITroubleCodePhone(CUITroubleCodePhone const&);
	CUITroubleCodePhone const& operator = (CUITroubleCodePhone const&);
	/*
	** 功    能:初始化激活界面数据，由底层库在显示界面之前调用
	** 参    数:无
	** 返 回 值:无
	** 说	 明:无
	*/
	void Init();

	/*
	** 功    能:启动显示故障码界面 
	** 参    数:
	* @param nPara 0:故障码;1:清除故障码
		#define SHOW_DTC_SHOW		0		// 故障码
		#define SHOW_DTC_CLEAR		1		// 清楚故障码
	** 返 回 值:
	*	#define RT_BACK					-1 //为回退
		#define RT_DTC_START_SCAN		0 // 开始扫描故障码
		#define RT_DTC_STOP_SCAN		1 // 停止扫描故障吗
		#define RT_DTC_SET_SUBSYSTEMID	2 // 设置需要扫描子系统的ID,可以通过GetScanSubSystemID()接口获取
		#define RT_DTC_SET_CLEARTYPE	3 // 设置需要清除故障码的类型,可以通过GetClrDTCType()接口获取
		#define RT_DTC_CLEARLL			4 // 清除所有的故障码
		#define RT_DTC_JUMPTO_FREEZEUI	5 // 跳到冻结帧界面
	** 说	 明:无
	*/
	int Show(int nPara = SHOW_DTC_SHOW);

	/*
	** 功    能:增加一项子系统，界面显示前调用初始化数据
	** 参    数:
	*@param nItemID			子系统ID
	*@param strSystemName   子系统名称
	** 返 回 值: 返回子系统id
	** 说	 明:无
	*/
	int AddDTCSubSystem(const string& strSubSystemName);

	/*
	** 功    能:更新正在扫描的子系统或者下一个子系统的状态
	** 参    数:
	* @param nStatus		
	* @param nSubSystemID
	** 返 回 值:无
	** 说	 明:无
	*/
	bool SetSubSystemState(int nSubSystemID, ScanStatus nStatus);

	/*
	** 功    能:通知扫描完成
	** 参    数:无
	** 返 回 值:无
	** 说	 明:无
	*/
	void NotifyScanFinished();

	/*
	** 功    能:扫描故障码，底层诊断库每扫描到一个故障码调用一次
	** 参    数:
	* @param nType				故障码所属类型（Confired,Pendding,Permarnent,Enhanced），必须传
	* @param nSubSystemID		故障码所属子系统名称，必须传
	* @param bExistHelp			是否有帮组信息，必须传
	* @param bExistFreezeFrame	是否有冻结帧，必须传
	* @param strDTC				故障码，必须传
	* @param strPID				故障码PID，非必须，有就传
	* @param strDescribe		故障码描述
	* @param strSubSystemName	故障码所属子系统名称，非必传
	* @param vctCauseDescribe	故障码产生可能的原因描述数组
	** 返 回 值:无
	** 说	 明:无
	*/
	bool AddDTCDataItem(DTCItemType nType, int nSubSystemID, 
		bool bExistHelp, bool bExistFreezeFrame, const string& strDTC,
		const string& strPID = string(""), const string& strDescribe = string(""), const string& strSubSystemName = string(""),
		const vector<string>& vctCauseDescribe = vector<string>());

    /*
	** 功    能:通知清除指定故障码成功
	** 参    数:
	* @param subSystemIds		需要清除类型
	** 返 回 值:无
	** 说	 明:暂时不再使用该接口，废弃，内部已注释为空
	*/
    void ClearCodeSucceed(vector<int> nType);

    /*
	** 功    能:通知清除全部故障码成功
	** 参    数:无
	** 返 回 值:无
	** 说	 明:无
	*/
    void ClearCodeAllSucceed();


    ////////////////////////////////////////////////////////////////////////// 移植原908车系接口 begin
    /*-----------------------------------------------------------------------------
	功    能：初始化
	参数说明：strTitle & binTitleID			标题文本
			  i16Style						风格  
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	void Init(const string &strTitle, W_I16 i16Style = TROUBLE_CODE_DC_SHOW, bool bFilter = false);
	void Init(CBinary const& binTitleID, W_I16 i16Style = TROUBLE_CODE_DC_SHOW, bool bFilter = false);


	/*-----------------------------------------------------------------------------
	功    能：添加故障码
	参数说明：binTroubleCodeID & strNumber				故障码Code   
			  binTroubleStatusID & strTroubleStatus     故障码状态
			  bDirectCallFun = false					是否直接调用回调函数
			  strContent								内容
			  bDTCTitle									是否是某类dtc的标题
	返 回 值：成功                          true
			  失败                          false  
	说    明：无
	-----------------------------------------------------------------------------*/
	bool Add(CBinary const& binTroubleCodeID, CBinary const& binTroubleStatusID, bool bDirectCallFun = false, bool bDTCTitle = false);
	bool Add(CBinary const& binTroubleCodeId, const string &strTroubleStatus, bool bDirectCallFun = false, bool bDTCTitle = false);
	bool Add(const string strNumber, const string strContent, const string strStatus, bool bDTCTitle = false);


	/*-----------------------------------------------------------------------------
	功    能：显示
	参数说明：无  
	返 回 值：-1 退出
	DF_NEXT_DTC 下条故障码
	DF_PRE_DTC   上一条故障码     
	如果连接到服务器查询故障码，则返回-2 add by zys 2016/12/17
	说    明：无
	-----------------------------------------------------------------------------*/ 
	//W_I16 Show(int iSelected = 0); 

	/*-----------------------------------------------------------------------------
	功    能：设置回调函数
	参数说明：返回值是W_32,带两个参数W_I32 i16TaskId, CBinary binSelectedTextID
	的函数
	返 回 值：无
	说    明：无
	-----------------------------------------------------------------------------*/
	void SetDtcCallBackFunction(PNoFoundDtcProcess fnNoFoundDtcProcess);

	/*-----------------------------------------------------------------------------
	功    能: 使存储功能无效
	参数说明: 无
	返 回 值: 无
	说    明: 已经弃用
	-------------------------------------------------------------------------*/
	void DisableSaveFuction();

	/*-----------------------------------------------------------------------------
	功    能: 获取总数
	参数说明: 总数
	返 回 值: 无
	说    明: 无
	-------------------------------------------------------------------------*/
	W_U32 GetDtcCount();

	/*-----------------------------------------------------------------------------
	功    能: 增加按钮
	参数说明: 
			strBtnText 设置按钮文本
			bEnable	   设置按钮可用
			bVisible   设置按钮可见
	返 回 值:返回增加按钮的总数

注意:
	AddButton加的ID是依次是-2，-3，-4，-5......
	-------------------------------------------------------------------------*/
	W_I16 AddButton(string strBtnText, bool bEnable, bool bVisible);

	/*-----------------------------------------------------------------------------
	功    能: 获取当前所选中的项
	参数说明: 无
	返 回 值:当前所选中的项 
	说    明: 无
	-------------------------------------------------------------------------*/
	W_I16 GetCurSelect()const;

	/*-----------------------------------------------------------------------------
	功    能: 设置按钮文本
	参数说明: 设置按钮文本的ID
	返 回 值:为真则设置成功,否则设置不成功,找不到对应的ID 
	说    明: 建议用户只设置冻结帧和帮助按钮文本,其他按钮系统统一设置
	李审霖 添加 2009-12-11 17:11:53
	-------------------------------------------------------------------------*/
	void SetButtonText(const unsigned int nButtonID, const string& strBtnText);
	/*-----------------------------------------------------------------------------
	功	  能：设置列宽比例
	参数说明：
	vctColWidthPercent 列宽比例数组，总计100
	返 回 值：无
	说    明：为了解决bug0024199，颜家松 于2012-6-29添加
	-------------------------------------------------------------------------*/
	void SetColWidthPercent(vector<int> const& vctColWidthPercent);
	/*-----------------------------------------------------------------------------
	功	  能：设置单列显示，只存在code一列
	参数说明：
	vctColWidthPercent 列宽比例数组，总计100
	返 回 值：无
	说    明：李审霖添加 2009年12月15日14:57:20 针对纪工的bug 
			  当用户需要使用help功能时而且视图中仅显示故障码编号一列,该列颜色为黑色
	-------------------------------------------------------------------------*/
	void SetOnlyCodeColumHelp(bool bOnlyCodeHelp);
	bool IsOnlyCodeHelp();

	/*-----------------------------------------------------------------------------
	功	  能：添加dtc系统
	参数说明：strSystem				系统名称
	返 回 值：无
	说    明：颜家松 20130713 添加，增加设置故障码所属系统
	-------------------------------------------------------------------------*/
	void AddDtcSystem(string const& strSystem);

	/******************************************************************************
	add by zys 2016/09/09 添加DTC所属系统，该名称必须是与服务器保持一致的，而不是历史记录那一套
	********************************************************************************/
	void AddDtcSystemId(int nDtcSysId);

	/*-----------------------------------------------------------------------------
	功	  能：清码按钮是否可用
	参数说明：bClearDTC				可用状态
	返 回 值：无
	说    明：无
	-------------------------------------------------------------------------*/
	void EnableClearDTC(bool bClearDTC);

	/*-----------------------------------------------------------------------------
	功	  能：设置某项的帮助和冻结帧状态
	参数说明：iIndex						项编号
			  bHaveHelp & bHaveFreezeFrame	是否存在帮助信息及冻结帧
	返 回 值：无
	说    明：无
	-------------------------------------------------------------------------*/
	void SetHelp(W_I16 iIndex, bool bHaveHelp);
	void SetFreezeFrame(W_I16 iIndex, bool bHaveFreezeFrame);

#ifdef PLAY_BACK
	//颜家松 2012-7-13 添加，在回放状态时，需要记录下测试时间，以便打印时使用
private:
	time_t m_tmTest;
public:
	void SetTestTime(time_t tmTest){m_tmTest = tmTest;}
	time_t GetTestTime() const {return m_tmTest;}
#endif

public:
	enum{
		BTN_FREEZE_FRAME = 1,
		BTN_HELP,
		BTN_CLEAR_DTC,
		BTN_SAVE,
	};


    ////////////////////////////////////////////////////////////////////////// 移植原908车系接口 end

    //ML100新接口 对车系

    /**
    * 添加扫描项
    * @param
    * scanItemId 扫描项ID
    * scanItemName 扫描项名字
    * @return void
    用于show之前调用
    */
    int AddScanItem(int scanItemId, const string & scanItemName);

    /**
    * 通知已经完成扫描某项ID为scanItemId的扫描项
    * scanItemId 扫描项ID
    * @return void
    */
    void FinishedScanItem(int scanItemId);

    /**
 	* 添加故障码类型
 	* @param pramJson 
    * troubleCodeTypeId 故障码类型ID
	* troubleCodeTypeName 故障码类型名字
 	* @return 返回空
    用于show之前调用
    */
    int AddTroubleCodeType(int troubleCodeTypeId, const string & troubleCodeTypeName);

    /**
    * 添加清码类型
    * @param pramJson 参数
    * clearTypeId 故障码清码类型ID, 
    * clearTypeName清码类型名字,
    * systemIdGroup 系统名字，要清楚与系统名字相同的故障码
    * @return
    用于show之前调用
    */
    int AddClearCodeType(int clearTypeId, const string & clearTypeName,const vector<int> & systemNameIds = vector<int>());


    /**
    * 添加扫描到的故障码
    * @param pramJson
    * troubleCodeIndex 索引, 
    * troubleCodeId 故障码ID,
    * troubleCodeName 故障码名字,
    * troubleCodeTypeId 所属故障码类型ID,
    * systemName 系统名字
    * @return
    */
    int AddTroubleCode(int troubleCodeIndex, const string & troubleCodeId, const string & troubleCodeName, int troubleCodeTypeId, int systemId = 0);
    int AddTroubleCode(int troubleCodeIndex, const CBinary & troubleCodeId, int troubleCodeTypeId, int systemId = 0);

    /**
    * 设置故障码的帮助信息
    * @param pramJson
    * troubleCodeIndex 故障码的索引 , 
    * helpInfos 该故障码的帮组信息
    * @return
    */
    void SetTroubleCodeHelpInf(int troubleCodeIndex, const vector<string> & helpInfos = vector<string>());

    /**
    * 设置故障码是否有冻结帧，默认没有
    * @param pramJson
    * troubleCodeIndex 故障码索引,
    * isFreezeFrame 是否有冻结帧，默认false
    * @return
    */
    void SetTroubleCodeHasFreezeFrame(int troubleCodeIndex, bool isFreezeFrame);

    /**
    * 完成某项清码类型的故障码清除
    * @param
    * clearType
    * Show之后调用
    * @return
    */
    void FinishedClearTroubleCode(int clearType);

    /**
    * 添加故障码所属系统的名称和系统ID
    * @param systemId
    * @param systemName
    * 当成是在show之前调用(实际上在show前后都可以调用)
    */
    void AddSystemName(int systemId, const string & systemName);

public:
    //一些额外使用的
	//需要清除故障的的类型
	int GetClrDTCType();
    int GetFinishedScanItem();

	//需要扫描的子系统的ID
	vector<int> GetScanSubSystemID();

private:
	ImpTroubleCodePhone *m_pImpTroubleCode;
};