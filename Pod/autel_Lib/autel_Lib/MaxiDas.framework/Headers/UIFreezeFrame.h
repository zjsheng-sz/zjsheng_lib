#pragma once

//SHOW返回事件值 从公共头文件中移动到这里
#define DF_Save       1000
#define DF_Print      1001



#include "UIPubDefine.h"
#include "Binary.h"


class ImpFreezeFrame;
class __MYEXPORT__ CUIFreezeFrame
{
public:
	CUIFreezeFrame();
	~CUIFreezeFrame();

	CUIFreezeFrame(CUIFreezeFrame const&);
	CUIFreezeFrame const& operator = (CUIFreezeFrame const&);
	/*
	** 功    能:初始化激活界面数据，由底层库在显示界面之前调用
	** 参    数:无
	** 返 回 值:无
	** 说	 明:无
	*/
	void Init();

	/*
	** 功    能:启动显示冻结帧界面
	** 参    数:无
	** 返 回 值:用户按下的按键,-1为回退
	** 说	 明:无
	*/
	int Show_ml(int iData = SHOW_DEFALUT);

	/*
	** 功    能:添加一条冻结帧数据
	** 参    数:
	* @param strItemCode	冻结帧码
	* @param strItemDesc	描述
	* @param strEnValue		英制值
	* @param strMeValue		公制值
	* @param strEnUnit		英制单位
	* @param strMeUnit		公制单位
	** 返 回 值:无
	** 说	 明:无
	*/
	int AddFreezeFrameItem(const string &code, const string &describe,  const string &strEnValue, const string &strMeValue, const string &strEnUnit, const string &strMeUnit);
	/*
	** 功    能:通知获取冻结帧数据结束
	** 参    数:无
	** 返 回 值:无
	** 说	 明:无
	*/
	void NotifyGetFreezeFrameDataFinished();

    /**新添加一个接口
    *可以在show前调用
    * @param nItem
    * @param pidValue
    */
    int SetPidValue(int nItem, const string & pidValue);

    //////////////////////////////////////////////////////////////////////////908移植 begin

    /*-----------------------------------------------------------------------------
	功    能：初始化
	参数说明：binTitleID                    标题文本ID
	// binStdValueLibNameID       标准数据流库名称ID
	// uiType                     标准/大众
	返 回 值： 
	说    明：待以后再实现(Intelli里再实现)
	-----------------------------------------------------------------------------*/
	void Init(CBinary const& binTitleID, W_U16 ui16Type = 0);


	/*-----------------------------------------------------------------------------
	功    能：初始化
	参数说明：strTitleText       对话框标题文本
	返 回 值：无
	说    明：无 
	-----------------------------------------------------------------------------*/
	void Init(const string &strTitle, W_U16 ui16Type = 0);


	/*-----------------------------------------------------------------------------
	功    能: 禁用保存功能
	参数说明: 无
	返 回 值: 无
	说    明: 已经被忽略
	-------------------------------------------------------------------------*/
	void DisableSaveFuction();

	/*-----------------------------------------------------------------------------
	功    能: 显示并选择用户返回
	参数说明: 无
	返 回 值: 无
	说    明: 无
	2007-6-28 11:51:46
	-------------------------------------------------------------------------*/
	W_I16 Show (void);     
    W_I16 Show (int iData);     



	/*-----------------------------------------------------------------------------
	功    能：添加选项
	参数说明：i16Index							那一个项
				binDataStreamID					数据流ID
				strDataStreamValue				数据流值
				binUnitID						单位ID
				strName							名称
				strValue						值
				strUnit							单位
	返 回 值：-1								为不成功    
				等于i16Index为					设置成功
	说    明： 无
	-----------------------------------------------------------------------------*/
	
	W_I16 Add(CBinary const& binDataStreamID, const string &strDataStreamValue=string(), CBinary const& binUnitID=CBinary());
	W_I16 Add(const string &strName,const string &strValue=string(), const string &strUnit=string());

	/*-----------------------------------------------------------------------------
	功    能：设置值
	参数说明：i16Index							那一个项
			  strValue							值
	返 回 值：无
	说    明： 无
	-----------------------------------------------------------------------------*/
	void SetValue(W_I16 nIndex, string const &strValue);

	/*-----------------------------------------------------------------------------
	功    能：设置各列所占比例
	参数说明：
			uFirstColWidthPercent			第一列所占百分比
			uSecondColWidthPercent			第二列所占百分比
	返 回 值：成功返回true，否则返回false
	说    明：无
	作    者：颜家松
	创建日期：2011.12.27
	-----------------------------------------------------------------------------*/
	void SetColWidth(W_I16 uFirstColWidthPercent, W_I16 uSecondColWidthPercent);

	/*-----------------------------------------------------------------------------
	功    能：不详
	参数说明：无							值
	返 回 值：无
	说    明：已经被忽略
	-----------------------------------------------------------------------------*/
	void EnableAutoUnit(bool bEnable);

#ifdef PLAY_BACK
	//颜家松 2012-7-13 添加，在回放状态时，需要记录下测试时间，以便打印时使用
	void SetTestTime(time_t tmTest);
	time_t GetTestTime() const;
#endif

    //////////////////////////////////////////////////////////////////////////908移植 end
private:
	ImpFreezeFrame* m_pImpFreezeFrame;

};