#pragma once
#include <string>
using namespace std;
#include "MaxiPlatform.h"
////////////////////////////////////////////////////////////////////////////////
//文件名  : DiagVinExport.h
//创建者  : 梁培鹏
//功能描述: 提供给车系调用的
//
//更新履历: 2017-6-27 14:31 梁培鹏 新建
//
////////////////////////////////////////////////////////////////////////////////
/**
* 启动在线VIN码
* @param vin           vin码
* @param vehicleBrand  车系名称
* @param vehicleAre    车系所在的区域  美国(USA)：0，欧洲(Europe)：1，日本(Asia)：2，其他(Domestic)：3
* @return              返回vin码解析结果。若要将结果上传给安卓，则去调用MaxiDas/VdtPublicCall.h/SetDecordVINOnLineResult(string)
*/
__MYEXPORT__ string StartVinDecordOnLine(const string & vin, const string & vehicleBrand, const string & vehicleAre);


//
//功能:   判断一辆车在使用在线VIN码时候是否需要连接入系统通信获取信息
//参数:   vehicleBrand   车系品牌
//返回值: true表示需要
//
__MYEXPORT__ bool IsVehicleNeedComm(const string & vehicleBrand);