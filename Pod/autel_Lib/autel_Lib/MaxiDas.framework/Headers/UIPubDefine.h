#ifndef _H_UIPUBDEFINE_2017224_100954_H__
#define _H_UIPUBDEFINE_2017224_100954_H__

#include "pubmarc.h"
#include <string>
#include <vector>
using namespace std;


// 主菜单显示定义
#define MENU_ID_DTC_CODE 			 0x0
#define	MENU_ID_CLEAR_CODE 			 0x1
#define MENU_ID_PREPARE_REPORT 		 0x2
#define	MENU_ID_EMISSION_CHECK		 0x3//排放检测
#define	MENU_ID_EXHAUST_GAS_CHECK 	 0x4//废气检测
#define	MENU_ID_FREEZE_FRAME		 0x5//冻结帧
#define	MENU_ID_CAR_INFORMATION	 	 0x6
#define	MENU_ID_MIL_STATUS_RECORD 	 0x7//工况记录
#define	MENU_ID_DATA_STREAM			 0x8//数据流
// end


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


// 检测状态定义
#define CHECK_STATE_NOT_CHECK				0x0 /**还未检测状态*/		
#define CHECK_STATE_CHECKING				0x1 /**检测中状态**/			
#define CHECK_STATE_FINISHED_PASSED			0x2 /***检测通过*/		
#define CHECK_STATE_FINISHED_NOT_PASSED		0x3 /**检测不通过*/			
#define CHECK_STATE_FINISHED_PROBLEM		0x4 /**有问题*/		
#define CHECK_STATE_FINISHED_NOT_SUPPORTED  0x5 /**不支持*/ 


// UIMessageBox定义
#ifndef DT_CENTER
	#define DT_LEFT_VCENTER			0x00	//居左并垂直居中
	#define DT_CENTER				0x01	//居中
	#define DT_RIGHT_VCENTER		0x02	//居右并垂直居中
	#define DT_TOP					0x03	//居顶
	#define DT_BOTTOM				0x04	//居底
	#define DT_CENTER_HORIZONTAL	0x05	//居中并且横向居中
#endif

#define MSGBOX_TYPE_WARNING			0x500  //警告类型
#define MSGBOX_TYPE_INFO			0x501  //提示类型
#define MSGBOX_TYPE_QUESSTION		0x502  //问号类型
#define MSGBOX_TYPE_ERROR			0x503  //错误类型
#define MSGBOX_TYPE_PROGRESS		0x504  //有进度的进度对话框类型
#define MSGBOX_TYPE_WAITING			0x505  //无进度的等待进度对话框类型
#define MSGBOX_TYPE_LIST_MENU   	0x506  //列表菜单对话框
#define MSG_BOX_TYPE_LIST_KEY_VALUE_INF  0x507 //列表键值对信息


// end UIMessageBox定义

// 选择车辆年款
#define CARANDYEAR_DEFAULT          0
// end 选择车辆年款 

// 工况检测 定义
#define MS_START_CHECK      	    0x00    //开始检测
// end 工况检测


// Show的返回值定义
#define RT_BACK			-1			// 回退
#define RT_OK			1
#define RT_CANCLE		-1
#define RT_DEFAULT		-9			// 默认值
#define RT_STOP_CHECK	0			// 停止检测
#define RT_START_CHECK	1			// 开始检测
#define RT_TIME_OUT		-2			// 对话框定时返回
// end Show的返回值定义

// Show的参数定义
#define SHOW_DEFALUT	-1		// 默认值
#define SHOW_RETURN		0		// 不阻塞等待
#define SHOW_WAITE		1		// 阻塞等待

#define SHOW_CARINFO_SHOW   0		// 从最外层UI直接进入车辆信息
#define SHOW_DTC_CARINFO_SHOW   1   // 从故障码进入车辆信息

// end Show的参数定义

#define SET_VIN_CODE		1//设置VIN码
#define SET_BRANDYEAR	2//设置年份和品牌


//SHOW通用事件，针对于全部UI中的show返回值 
#define RT_IS_APP_CALL     1000


//NativeCallAppReturnJSON 中 uiCtl 字段的标识
#define UI_CONTROL_NAME_CARS_INF            "CarsInfInterface"         //车辆信息接口名字
#define UI_CONTROL_NAME_DATASTREAM          "DataStreamInterface"      //数据流接口名字
#define UI_CONTROL_NAME_DTC                 "DtcInterface"             //故障码接口名字
#define UI_CONTROL_NAME_EMISSON             "EmissionInterface"        //排放检测
#define UI_CONTROL_NAME_EXHAUST_GAS_CHECK   "ExhaustGasCheckInterface" //废弃检测
#define UI_CONTROL_NAME_FREEZE_FRAME        "FreezeFrame"              //冻结帧
#define UI_CONTROL_NAME_HM_PG_MENU          "HmPgMenuInterface"        //首页menu
#define UI_CONTROL_NAME_MESSAGE_BOX         "MessageBoxInterface"      //消息对话框
#define UI_CONTROL_NAME_MIL_STATUS_CHECK    "MILStatusCheckInterface"  //工况检测
#define UI_SELECT_CARANDYEAR_INTERFACE      "SelectCarAndYearInterface"//选择车辆与年款

#define UI_DEFAULT_PUBLIC_INTERFACE         "DefaultPublicInterface"   //普通通用的 就是不属于其它组件的，就属于这个组件

//纯粹的界面显示
#define UI_GROUPLIST_JNIINTERFACE           "UIGroupListJniInterface"  //新的LIST控件显示

#endif // _H_UIPUBDEFINE_2017224_100954_H__