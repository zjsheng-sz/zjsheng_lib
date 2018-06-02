#ifndef VDTPUBLICCALL_7FA1E53B_A89A_4365_9CA8_6000D9633439_INCLUDED_
#define VDTPUBLICCALL_7FA1E53B_A89A_4365_9CA8_6000D9633439_INCLUDED_
////////////////////////////////////////////////////////////////////////////////
//文件名  : VdtPublicCall.h
//创建者  : 梁培鹏
//功能描述: 模拟一个UI的，用于给车系的直接调用于UI接口
//
//更新履历: 2017-3-15 16:42 梁培鹏 新建
//
////////////////////////////////////////////////////////////////////////////////
#include <map>
using namespace std;
#include "UIPubDefine.h"
#include "ParamToJson.h"

extern string g_vinCode;
extern string g_Brand;  //车辆品牌
extern string g_Year;
extern string g_Name;  //车系名称
extern string g_Area;

class __MYEXPORT__ CVdtPublicCall
{
public:
    /*
	** 功    能:调用界面的公共接口
	** 参    数:
    * @param uiCtl UI 控件名称
    * @param uiMethod UI控件中的方法名称
    * @param pramJson UI控件中的方法参数（JSON格式）
    * @return 返回结果是JSON格式
	** 返 回 值:JSON字符串 内部存了结果
	** 说	 明:无
	*/
    static string CallAppReturnJSON(const string & uiCtl, const string & uiMethod, const string & pramJson);


    /*
    AppCallNativeReturnJson 返回的参数
    */
    static int GetAppCallCtl();         //App界面控件ID
    static int GetAppCallMethodid();    //函数ID
    static string GetAppCallPram();     //传入的参数，JSON格式
    static void  CleanAppCall();        //清空内部保存的参数


    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    //一些全局的 调用界面的

    //
    //
    //功能:   解析VIN码
    //参数:   vinCode   VIN码
    //返回值: "America/Benz|Domestic/GMChina" 以"|"字符串分隔车系，以"/"分隔的区域和车系名
    //
    static string ParseVinByAutoVin(const string & vinCode);



    //
    //功能:   将VIN码 车系品牌 区域 上传给界面
    //参数:   
    //返回值: 
    //
    static void SetVehiceVinBrandAreaToUI(const string & vin, const string & vehicleBrand, const string & vehicleArea, const string & year);

    //
    //功能:   将在线VIN码的解析结果，上传给安卓 2017/06/27
    //参数:   
    //返回值: 
    //
    static void SetDecordVINOnLineResult(const string & strResult, const string & vin, const string & vehicleBrand, const string & vehicleArea);

    //
    //功能:   获取在线VIN码缓存的解析结果
    //参数:   vin           vin码
    //        vehicleName   车系名称
    //        vehicleArea   车系所在的区域  美国 USA：0，Europa：1，亚洲 Asia：2，其他 Domestic：3
    //        mapRet        返回结果，结析的结果是一个MAP
    //返回值: true表示成功 false表示返回的内容有误
    //
    static bool GetDecordVINOnLineResult(const string & vin, const string & vehicleName, const string & vehicleArea, map<string, string> & mapRet);



    //
    //功能:   设置/获取当前通讯协议
    //参数:   
    //返回值: 
    //
    static void SetVehicleProtocol(int protocol);
    static int GetVehicleProtocol();


    //
    //功能:   SelectCarAndYear中的信息 保存到CarInfo(EcuInfo) 中，但这个是需要全局调用，所以安卓设置将也保存一份在这里
    //参数:   
    //返回值: 
    //
    static string GetEcuInfoVinCode();  //获取由安卓传过来的Vin码
    static string GetEcuInfoName();    //获取由安卓传过来的车系名称
    static string GetEcuInfoBrand();    //获取由安卓传过来的品牌
    static string GetEcuInfoYear();     //获取由安卓传过来的年份
    static string GetEcuInfoYArea();     //获取由安卓传过来的区域
    static void SetEcuInfoVinCode(const string & vinCode);
    static void SetEcuInfoName(const string & carName);
    static void SetEcuInfoBrand(const string & brand);
    static void SetEcuInfoYear(const string & year);
    static void SetEcuInfoArea(const string & area);
};

#endif // VDTPUBLICCALL_7FA1E53B_A89A_4365_9CA8_6000D9633439_INCLUDED_
