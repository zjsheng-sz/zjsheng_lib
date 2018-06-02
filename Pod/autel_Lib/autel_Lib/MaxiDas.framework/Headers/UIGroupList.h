#pragma once
#include "UIPubDefine.h"
////////////////////////////////////////////////////////////////////////////////
//文件名  : UIGroupList.h
//创建者  : 梁培鹏
//功能描述: 一个LIST的控件，新写的
//
//更新履历: 2017-6-26 13:58 梁培鹏 新建
//
////////////////////////////////////////////////////////////////////////////////
class ImpGroupList;
class __MYEXPORT__ CUIGroupList
{
public:
	CUIGroupList(void);
	~CUIGroupList(void);

    void Init(const string & title);


    //
    //功能:   添加属性名称 (相当于list的每列的名称)。不会即时更新
    //参数:   
    //返回值: 返回添加后的attr id
    //
    int AddAttriName(const string & attrName);


    //
    //功能:   添加组名称。不会即时更新
    //参数:   
    //返回值: 返回添加后的group id
    //
    int AddGroup(const string & groupName);


    //
    //功能:   添加某个组ID中的一项
    //参数:   
    //返回值: 返回添加后的item id   注：这个是全局唯一 就算是在不同的group中，也不会有相同的
    //
    int AddSubItem(int groupId, const string & itemName);


    //
    //功能:   添加(设置)值。不会即时更新
    //参数:   
    //返回值: 返回添加的值的ID
    //
    int AddAttrVal(int itemId, int attrId, const string & attrVal);


    //
    //功能:   修改值 与上面的添加值相对应
    //参数:   
    //返回值: 
    //
    bool ModifyTitleName(const string & title);
    bool ModifyGroupName(int groupId, const string & groupName);
    bool ModifySubItemName(int itemId, const string & itemName);
    bool ModifyAttributeValue(int itemId, int attrId, const string & attrVal);


    //
    //功能:   修改界面风格
    //参数:   disType = 0 正常风格，disType = 1 表格风格。默认为正常风格
    //返回值: 
    //
    bool ModifyViewDisType(int disType);


    //
    //功能:   在界面中显示最新的内容
    //参数:   
    //返回值: 
    //
    void FreshAllDatas();


    //
    //功能:   显示界面 只显示界面 不更新内容 
    //参数:   iData     值为-2将不阻塞 其它值为阻塞
    //返回值: RT_BACK(-1)为退出，RT_DEFAULT(-9)表示无操作，其它值为安卓的点击事件
    //
    int Show(int iData);


    //
    //功能:   清空之前的全部数据
    //参数:   clearType 1只清空值(group item attrvalue)， 2清空全部(group item attrvalue attrname)
    //返回值: 
    //
    void DataClear(int clearType);
private:
	ImpGroupList *pGroupList;
};
