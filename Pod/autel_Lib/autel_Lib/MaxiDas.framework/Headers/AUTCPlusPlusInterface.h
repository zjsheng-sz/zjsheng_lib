#pragma once
////////////////////////////////////////////////////////////////////////////////
//文件名  : AUTCPlusPlusInterface.h
//创建者  : 梁培鹏
//功能描述: 供界面调用内部的事件 界面传递回调函数  目前是仅用于苹果调用（类似于安卓调用C++）
//
//更新履历: 2017-4-26 9:52 梁培鹏 新建
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

/******************************** Public **************************************/
class PublicInterface_OC {
public:
    //除了这个 NativeCallAppReturnJSON 需要设置 下面类的都不需要再设置 统一通过NativeCallAppReturnJSON来传递
    static void SetFunc(void * NativeCallAppReturnJSON, void * AscToUtf8, void * Utf8ToAsc);
};

/******************************** Home **************************************/
class HomeInterface_OC {
public:
    //点击菜单按钮
    static void MenuOnItemClick(int nItem);
    //退出主页按钮
    static void MenuOnEscClick();
    //点击数据流按钮
    static void DataStreamTabBtnClick(); //未实现
    
    static void SetFunc(void *Init
                        , void *Uninit
                        , void *Show
                        , void *AddMenuItem
                        );
};

/******************************** VdtPublic **************************************/
class VdtPublicInterface {
public:
    //是否开启log打印
    static void SetLogSwitch(bool bOpen);
    //设置诊断库存放位置
    static void SetDiagSoPath(string filePath);
    //设置手机诊断平台版本号
    static void SetDiagnoseSysVersion(string ver);
    //设置当前诊断车的名字
    static void SetCurVehicle(string strVehicle);
    //设置当前诊断车所在文件夹的名字
    static void SetCurVehicleFolder(string strFolder);
    //设置当前诊断车的诊断执行库所在的路径
    static void SetCurExePath(string strCurCarPath);
    //设置scan文件夹所在的路径
    static void SetCurScanPath(string strScanPath);
    //设置当前语言
    static void SetCurLanguage(string strCurLanguage);
    //设置当前单位
    static void SetCurUnitType(string strCurUnitType);
    //启动诊断
    static void SetOption(int feedBack);
    //停止诊断
    static void StopScanThread();
    
    static void SetAutoVinParseVehicle(string strVehicle);

    static void AppCallNativeReturnJson(int uiCtlId, int  nativeMathodID, string pramJson);

    static void SetFunc(void *isNetConnected);
};


/******************************** Emission **************************************/
class EmissionInterface_OC {
public:
    static void EscClick();
    static void StartCheck();
    static void StopCheck();
    
    static void SetFunc(void *Init
                        , void *Uninit
                        , void *Show
                        , void *NotifyCheckingOver
                        , void *AddEmissionCheckData
                        , void *UpdateCheckingItemInfo
                        );
};


/******************************** ExhaustGasCheck **************************************/
class ExhaustGasCheckInterface_OC {
public:
    static void EscClick();
    static void StartCheck();
    static void StopCheck();
    
    static void SetFunc(void *Init
                        , void *Uninit
                        , void *Show
                        , void *NotifyCheckingOver
                        , void *AddExhaustGasCheckData
                        , void *UpdateCheckingItemInfo
                        );
};


/******************************** MILStatus **************************************/
class MILStatusCheckInterface_OC {
public:
    static void EscClick();
    static void StartCheck();
    
    static void SetFunc(void *Init
                        , void *Uninit
                        , void *Show
                        , void *NotifyCheckingOver
                        , void *AddMilStatusData
                        , void *UpdateMilStatausItem
                        );
};


/******************************** CarsInf **************************************/
//车辆信息
class CarsInfInterface_OC {
public:
    static void EscClick();
    //设置汽车VIN码
    static void SetVinCode(string vinCode);
    //设置汽车品牌和年份
    static void SetCarBrandAndYear(string year, string brand);

    static void ShowSelectVehicleDialog();


    static void ShowParseVINTipDialog();

    static void SetVehicleBrandAndYearAndArea(string carName, string carBrand, string carYear, string carArea);
    
    static void SetFunc(void *Init
                        , void *Uninit
                        , void *Show
                        , void *ReportVinCodeToUI
                        , void *SetSupportEnhanceAble
                        );
};


/******************************** DTC **************************************/
class DTCInterface_OC {
public:
    static void EscClick();
    //开始扫描
    static void StartScanning();
    //取消扫描
    static void CancelScanning();
    //设置要扫描的子系统
    static void SetScanSubSystem(vector<int> &subSystemIds);
    //清码
    static void ClearCode(int type);
    static void ClearAllCode();
    //跳去冻结帧界面
    static void JumpToShowFreezeFrame();
    //跳去车辆信息界面
    static void JumpToCarsInf();
    //开始进行scanItemId的扫描
    static void StartScanItem(int scanItemId);
    
    static void SetFunc(void *Init
                        , void *Uninit
                        , void *Show
                        , void *AddDTCSubSystem
                        , void *UpdateSubSystemScanState
                        , void *NotifyScanFinished
                        , void *addDTCDataItem
                        , void *ClearCodeSucceed
                        , void *ClearCodeAllSucceed
                        );
};


/******************************** DataStream **************************************/
//数据流
class DataStreamInterface_OC {
public:
    static void EscClick();
    //停止获取数据流
    static void StopGetDataStreamData();
    
    static void SetFunc(void *Init
                        , void *Uninit
                        , void *Show
                        , void *AddDataStreamItem
                        , void *SetDataStreamInfoEx
                        , void *UpdateDataStreamItemValue
                        , void *SetUnit
                        , void *SetRef
                        );
};


/******************************** FreezeFrame **************************************/
class FreezeFrameInterface_OC {
public:
    static void EscClick();
    
    static void SetFunc(void *Init
                        , void *Uninit
                        , void *Show
                        , void *AddFreezeFrameItem
                        , void *NotifyGetFreezeFrameDataFinished
                        );
};


/******************************** MessageBox **************************************/
class MessageBoxInterface_OC {
public:
    static void EscClick();
    static void BtnClick(int nID);
    static void TimerReturn();

    static void StartClick();
    static void YesClick();
    static void NoClick();
    static void OkClick();
    static void CancelClick();
    static void FreeBtnClick(int nBtnID);

    static void SetFunc(void *Init
                        , void *Uninit
                        , void *Show
                        , void *DismissMsgBox
                        , void *SetMessageBoxData
                        , void *SetMsgType
                        , void *SetMsgTitle
                        , void *SetMsgContent
                        , void *SetMsgContentTxtColor
                        , void *SetMsgContentGravityType
                        , void *SetProgress
                        , void *SetWaitMilliseconds
                        , void *SetStrStaticBtnCaption
                        , void *AddMessageKeyValueInf
                        );
};


/******************************** UIGroupList **************************************/
class UIGroupList_OC
{
public:
    static void EscClick();
};