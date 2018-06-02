#pragma once

#include "UIPubDefine.h"
#include "Binary.h"

//SHOW返回事件值 从公共头文件中移动到这里
// 选择车辆年款
#define CARANDYEAR_DEFAULT          0
// end 选择车辆年款 


class ImpSelectCarAndYear;
class __MYEXPORT__ UISelectCarAndYear
{
public:
	UISelectCarAndYear();
	~UISelectCarAndYear();

	UISelectCarAndYear(UISelectCarAndYear const&);
	UISelectCarAndYear const& operator = (UISelectCarAndYear const&);

	/*
	** 功    能:初始化激活界面数据，由底层库在显示界面之前调用
	** 参    数:无
	** 返 回 值:无
	** 说	 明:无
	*/
	void Init();

	/*
	** 功    能:启动显示选择车辆年款页面
	** 参    数:
	* @param iData 
	** 返 回 值:-1为回退
	** 说	 明:无
	*/
	int Show(int iData = CARANDYEAR_DEFAULT);

private:
   ImpSelectCarAndYear* m_pImpSelectCarAndYear;

};
