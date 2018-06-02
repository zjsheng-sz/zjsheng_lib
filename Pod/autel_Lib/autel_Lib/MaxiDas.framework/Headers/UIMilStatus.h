#pragma once

#include "UIPubDefine.h"
#include "Binary.h"
//SHOW返回事件值 从公共头文件中移动到这里
#define MS_START_CHECK      	    0x00    //开始检测

class ImpMilStatus;
class __MYEXPORT__ CUIMILStatus
{
public:
	CUIMILStatus();
	~CUIMILStatus();

	CUIMILStatus(CUIMILStatus const&);
	CUIMILStatus const& operator = (CUIMILStatus const&);

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
	** 返 回 值:用户按下的按键,-1为回退
	** 说	 明:无
	*/
	int Show(int nPara = SHOW_DEFALUT);

	/*
	** 功    能:通知本次检测结束 
	** 参    数:无
	** 返 回 值:无
	** 说	 明:无
	*/
	void NotifyCheckingOver();


	/**
	* 添加一条工况记录
	* @param strGroupName			检测组名描述
	* @param strItemName			工况记录项名称
	* @param strItemValueDes		工况记录项状态或者数值
	* 返回值：当前项id
	*/
    int AddItem(const CBinary &binGroupNameId, const CBinary &binItemNameId, const CBinary &binItemValueDesId);
    int AddItem(const CBinary &binGroupNameId, const CBinary &binItemNameId, const string &strItemValueDes);
    int AddItem(const CBinary &binGroupNameId, const string &strItemName, const string &strItemValueDes);
    int AddItem(const string &strGroupName, const string &strItemName, const string &strItemValueDes);
	/**
	* 更新一条工况记录
	* @param nItemID				检测项标记ID
    * @param strItemName			工况记录项名称
    * @param strItemValueDes		工况记录项状态或者数值
    */
    bool SetItem(int nItemID, int statusId, const CBinary &binItemNameId, const CBinary &binItemValueDesId);
    bool SetItem(int nItemID, int statusId, const CBinary &binItemNameId, const string &strItemValueDes);
    bool SetItem(int nItemID, int statusId, const string &strItemName, const string &strItemValueDes);
    //单个设置
    bool SetItemStatus(int nItemID, int statusId);
    bool SetItemName(int nItemID, const string &strItemName);
    bool SetItemValueDes(int nItemID, const string &strItemValueDes);


private:
   ImpMilStatus* m_pImpMILStatus;

};
