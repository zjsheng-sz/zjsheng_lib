#ifndef AUTCPlusPlusInterface_Comm_hpp
#define AUTCPlusPlusInterface_Comm_hpp

#include <stdio.h>

#include <string>
#include <vector>
#include <map>

using namespace std;

/******************************** VdtPublic **************************************/
class VdtPublicInterface_comm{                                                                  //注：VdtPublic分两部分
public:                                                                                         //注：这个是comm库的
    //判断VCI是否连接上
    static bool IsVCIConnected();
    //设置VCI连接
    static void SetVCIConnected(bool bConnected);
    //设置VCI书否自动连接
    static void SetVCIAutoConnect(bool isAutoConnect);
    //启动VCI固件升级
    static void StartVCIFirmwareUpdate(string updateFilePath);
    //获取ECU电池电压
    static double GetEcuBatteryVoltage();
    //获取VCI固件版本
    static string GetVCIFirmwareVersion(string ver);
    //获取VCI版本号
    static string GetVCIVersion(string ver);
    static string GetVCISoftwareVersion(string ver);
    //获取序列号
    static string GetVCISerial();
};







#endif /* AUTCPlusPlusInterface_Comm_hpp */
