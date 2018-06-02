#pragma once

#include <string>
#include <vector>
using namespace std;
#include "Binary.h"
#include "pubmarc.h"

__MYEXPORT__ bool FileIsExist(const string& strFile);


/*
 *	从text.tab中获取文本
 */
__MYEXPORT__ string GetStringFromTab(CBinary const& binKey, const string &strDefaultValue);

/*
 *	设置/获取VIN码
 */
__MYEXPORT__ void SetVinCode(string const& strVin);
__MYEXPORT__ const string& GetVinCode();


/*
 *	过滤字符szFilt
 */
__MYEXPORT__ void FiltSpecialChar(const string& strSrc, string& strDes, const char szFilt);

__MYEXPORT__ string const& GetOBDVehicle(void);
/*
 *	获取车型标记，为车型文件夹名称
 */
__MYEXPORT__ string const& GetCurrentVehicle(void);

/*
 *	获取车型所在目录，对于链接车，为目标车目录，入mini，此时获得的路径是mini的路径
 */
__MYEXPORT__ string const& GetCurVehicleFolder(void);
//20150916 Add gongjiyue 增加接口可获取诊断软件版本号， 平台版本号，VCI版本号， 连接方式(蓝牙，有线，如果能区分J2534，蓝牙盒子就更好)等接口
/*
 *	获取诊断软件版本号
 */
__MYEXPORT__ string const& GetMaxiSysVersion(void);

/*
 *	获取诊断软件版本号
 */
__MYEXPORT__ string const& GetCurrentCarVersion(void);

/*
 *	获取VCI固件版本号
 */
__MYEXPORT__ string const& GetVCISoftwareVersion(void);

/*
 *	获取VCI软件版本号
 */
__MYEXPORT__ string const& GetVCIFirmwareVersion(void);

/*
 *	获取VCI版本号
 */
__MYEXPORT__ string const& GetVCIVersion(void);

/*
 *	区分J2534，蓝牙盒子等
 */
/*
所有盒子的类型
static string VCI_FLASH_PRO = "MAXISYS"; 
static string VCI_BT_BOX = "MFBT"; 
static string VCI_FLASH_PRO_NEW = "FLASHPRO2"; 
static string VCI_BT_BOX_NEW = "BTBOX2"; 
static string VCI_MAXIFLASH_ELITE = "MAXIFLASH-ELITE"; 
static string VCI_MVCI_V100 = "MVCI-V100"; 
*/
__MYEXPORT__ string const& GetJ2534Mode(void);
//20150916 Add gongjiyue 增加接口可获取诊断软件版本号， 平台版本号，VCI版本号， 连接方式(蓝牙，有线，如果能区分J2534，蓝牙盒子就更好)等接口
/*
 *	获取scan目录
 */
__MYEXPORT__ string const& GetScanPath();

/*
 *	获取诊断程序所在目录，对于链接车，为目标车目录，入mini，此时获得的路径是bmw的路径
 */
__MYEXPORT__ string const& GetExePath();

/*
 *	获取当前语言缩写，入cn、en等
 */
__MYEXPORT__ string const& GetCurLanguage();

/*
 *	获取当前公英制
 */
__MYEXPORT__ string const& GetCurUnitType();

/*
 *	获取当前时间，该接口未实现
 */
__MYEXPORT__ string GetCurDateTime(string const& strYMDSep, string const& strHMSSep);

/*
 *	格式化时间输出，该接口未实现
 */
__MYEXPORT__ string GetDateTime(time_t tm, string const& strYMDSep, string const& strHMSSep);

/*
 *	判断一个文件或者文件夹是否存在
 */
__MYEXPORT__ bool IsExist(const string& strFile);

// add by zys 2016/08/03	文件是否真实存在
__MYEXPORT__ bool IsFileRealExist(const string& strFile);
// end

#ifndef _WIN32
__MYEXPORT__ void Sleep(unsigned long ulMilliseconds);
#endif

/*
 *	以二进制格式化输出数字
 */
__MYEXPORT__ string ToStringByBinary(long lValue);

/*
 *	以十进制格式化输出数字
 */
__MYEXPORT__ string ToStringByDecimal(double dValue);
__MYEXPORT__ string ToStringByDecimal(long lValue);
__MYEXPORT__ string ToStringByDecimal(bool bValue);
template<typename T>
__MYEXPORT__ string ToStringByDecimal(T value)
{
	long lValue = value;
	return ToStringByDecimal(lValue);
}

/*
 *	将十进制表示的数字转换为数字类型
 */
__MYEXPORT__ long StringToLongByDecimal(string const& strValue);
__MYEXPORT__ string DoubleToStringByDecimal(double dValue, int nRadixReserve);
__MYEXPORT__ double StringToDoubleByDecimal(string const& strValue);

/*
*	获取当前时间
*/
__MYEXPORT__ time_t GetCurTime();

__MYEXPORT__ void RunScan();


/*
 *	大小写转换
 */
__MYEXPORT__ char ToLower(char c);
__MYEXPORT__ char ToUpper(char c);
__MYEXPORT__ string ToLower(string const& strSour);
__MYEXPORT__ string ToUpper(string const& strSour);
__MYEXPORT__ bool IsFileRealExist(const string& strFile);
#ifndef _WIN32
__MYEXPORT__ char* _ltoa(long lValue, char* pBuf, int radix);
__MYEXPORT__ unsigned long GetTickCount();
#endif

#ifndef _WIN32
__MYEXPORT__ char* _itoa(int _Value, char* _Dest, int _Radix);
#endif

/*
 *	用户是否开启了Demo功能，已经停用
 */
__MYEXPORT__ bool IsDemo();

/*
 *	用户是否开启了DataLogging功能
 */
__MYEXPORT__ bool IsDataLogging();

/*
 *	获取上次诊断记录设置的记录
 */
__MYEXPORT__ vector<string> GetReuseValues();

/*
 *	上次下载文件解开，上传接口已经停用
 */
__MYEXPORT__ bool UpLoadFile(string const& strLoc, string const& strRemote, bool bSilence);
__MYEXPORT__ bool DownLoadFile(string const& strRemote, string const& strLoc);
__MYEXPORT__ bool DownLoadFiles(vector<string> const& vctRemote, vector<string> const& vctLoc);
__MYEXPORT__ bool DownLoadFiles_Ex(vector<string> const& vctRemote, vector<string> const& vctLoc, vector<long> const& vctremoteFileSizes);
/*
 *	二次加密使用
 */
__MYEXPORT__ void UseComposeFile(bool bUse = true);

/*
 *	是否启用了二次加密
 */
__MYEXPORT__ bool IsUseComposeFile();

/*
 *	获取诊断进入方式
 */
#define DIAG_ENTER_TYPE_NOMAL		(0)
#define DIAG_ENTER_TYPE_AUTOVIN		(1)
#define DIAG_ENTER_TYPE_HISTORY		(2)

__MYEXPORT__ int GetDiagEnterType();

/*
 *	诊断编程服务信息，必须先调用GetDiagProgramSvrName，然后调用GetDiagProgramSvrPort，否则得到的端口未必是正确的
 */
__MYEXPORT__ string const& GetDiagProgramSvrName();
__MYEXPORT__ unsigned int GetDiagProgramSvrPort();

/*
 *	获取序列号接口，目前未启用
 */
__MYEXPORT__ string const& GetSerialNumber();

/*
 *	将Unicode转换为asc格式
 */
__MYEXPORT__ string UnicodeToString(wstring const& strSour);

/*
 *	获取操作系统版本信息http://10.240.4.2/svn/Develop/AllProject/MY808/DiagSoftware/SYSTEM_PROGRAM/tags/System_Program_V1.20
 */
__MYEXPORT__ string GetOSVersion();

/*
*	设置wifi状态
*/
__MYEXPORT__ void SetWifiEnableStatus(bool enable);

/*
*	询问wifi是否可用
*/
__MYEXPORT__ bool IsWifiEnable();

/*
*	设置BlueTooth状态
*/
__MYEXPORT__ void SetBlueToothEnableStatus(bool enable);

/*
*	询问BlueTooth是否可用
*/
__MYEXPORT__ bool IsBlueToothEnable();

/*
 *	询问有线网是否配置  	
 */
__MYEXPORT__ bool IsEthernetConfigured();

/*
 *	设置帮助信息
 */
__MYEXPORT__ void SetHelpUrls(vector<string> const& titles, vector<string> const& urls);

/*
*  解压某个zip文件
*/
__MYEXPORT__ bool Unzip(string const& zipFile, string const& unzipFolder);

/*
*  删除某个文件夹
*/
__MYEXPORT__ bool DelFolder(string const& folder);

/*
*  删除某个文件
*/
__MYEXPORT__ bool DelFile(string const& file);

/*
*询问VCI连接状况
*/
__MYEXPORT__ bool IsVCIConnected();

/*
*启动新的诊断，diagFolderName 新诊断软件所在文件夹名称（不是全路径，仅仅是个文件夹名）， soName 待启动so名称， inputFile 传入参数的信息文件， outputFile 输出结果信息文件
*/
__MYEXPORT__ bool StartDiagnose(string const& diagFolderName, string const& soName, string const& inputFile, string const& outputFile);

/*
*获取诊断输入信息文件
*/
__MYEXPORT__ string GetDiagnoseInputFile();

/*
*获取诊断输出信息文件
*/
__MYEXPORT__ string GetDiagnoseOutputFile();


/******************************* add by zys 2015/10/17 ****************************************
* 功    能: 设置/获取 产品类型
* 产品类型的取值： autel_my905，autel_MS908_BSRO，autel_my908v11，Elite，maxisys906，maxisys906ts, maxisys906bt
* modified by yyx 2017/1/14 如果产品类型是ds808则返回maxisys906，为兼容车系软件共用（906和ds808软件一样）
************************************************************************************************/
__MYEXPORT__ string GetProductType();

/******************************* add by yyx 2017/1/14 ****************************************
* 功    能: 设置/获取 产品类型（注原接口为兼容DS808和906行为已改变，以后一律用改接口）
* 产品类型的取值： autel_my905，autel_MS908_BSRO，autel_my908v11，Elite，maxisys906，maxisys906ts, maxisys906bt
************************************************************************************************/
__MYEXPORT__ string GetProductTypeNew();

/*---------------------------------------------------------------------------------------------
* 功    能： 获取Tpms管理程序版本号
----------------------------------------------------------------------------------------------*/
__MYEXPORT__ string const& GetTpmsMgrVersion();

/*---------------------------------------------------------------------------------------------
* 功    能： 查询是否支持TPMS功能
* 参    数：strInputFile 车辆相关信息的文件
* 返 回 值：1--支持， 2--不支持
----------------------------------------------------------------------------------------------*/
__MYEXPORT__ int IsTpmsSupport(const string& strInputFile);

/*---------------------------------------------------------------------------------------------
* 功    能： 启动新的模块，供诊断调用
* 参    数：strSoPathName:  so库全路径名
*			strInputFile:	传入参数的信息文件
*			strOutputFile： 输出结果信息文件
* 返 回 值：true成功，false失败
* 说    明：使用该接口代替StartDiagnose
----------------------------------------------------------------------------------------------*/
__MYEXPORT__ bool StartModule(const string& strSoPathName, const string& strInputFile, const string& strOutputFile);

/*---------------------------------------------------------------------------------------------
* 功    能：TPMS设置车型  add by zys 2015/12/19
* 参    数：strCarVer： tpms车型
* 返 回 值：无
----------------------------------------------------------------------------------------------*/
__MYEXPORT__ void SetTpmsCarVersion(const string& strCarVer);
/* 
add 2016/03/15 客户端车系版本与服务器比较，需要联网
返回值：0表示版本一致(不需要更新)，1表示版本不一致(需要升级)，-1表示其他错误(网络异常，服务器异常，参数不匹配)
*/
__MYEXPORT__ int RpcVehicleVersionCmp();

// add 2016/03/17 获取当前车辆code值
__MYEXPORT__ string GetCurVehicleCode(void *env = NULL);


// add by zys 2016/08/26 设置编码格式，使用完后必须还原
typedef enum _emCharset
{
	CHARSET_ANSI = 0,		// 本地字符集编码
	CHARSET_UTF8			// utf8编码
}AutelCharset;
__MYEXPORT__ void SetCurCharset(int nCharset);
__MYEXPORT__ int GetCurCharset(); 
// end


// 设置车辆相关参数，为key-value对 add 2016/09/07
__MYEXPORT__ void SetCarParameter(const string& strKey, const string& strValue);

// 获取TPMS市场，返回值为：Europe、USA、China。多语言支持  add [2016/10/10 A15386]
__MYEXPORT__ string GetTpmsMarket();


//---------------------------------- end by zys 2015/10/17 -------------------------------------
__MYEXPORT__ bool GetCurUserLicenceStatus();

__MYEXPORT__ double GetLess(double dValue);
__MYEXPORT__ double Getlarger(double dValue);
__MYEXPORT__ bool needDel(char c);
__MYEXPORT__ void trim(string& str);
/************************************************************************************
定义特殊功能
*************************************************************************************/
#define OIL_RESET   		0
#define E_PARK_BRAKE   		1		//Eelectric Park Brake
#define TPMS				2
#define BATTERY				3
#define BRAKE_BLEED			4
#define DPF_SCR				5
#define IMMO_KEYS			6
#define INJECTOR			7
#define STEERING			8
#define SUSPENSION			9
#define THROTTLE 			10
#define WIN_DR_ROOF			11		//Window,door and roof
#define SEATS				12
#define ODOMETER			13
#define LANG_CHANGE			14		//Language Change
#define HEADLAMP			15
#define CHG_TIRE_SIZE		16		//Change tire size
#define TEC_LEARN			17
#define ABSSRS				18
/*
 *	是否由诊断负责设置ECU电压值
 *@para  nUser:
 *	0:由libComm.so负责设置ECU电压值;
 *	1:由于诊断负责设置ECU电压值
 */

__MYEXPORT__ void SetVoltageUser(int nUser);

/*
 *	如果是由诊断负责设置ECU电压值则通过次接口设置
 *@para  ulBatt: Ecu的电压值,单位是(mV)
 */
__MYEXPORT__ void SetEcuBattery(unsigned long ulBatt);

__MYEXPORT__ const int &GetVoltageUser();


__MYEXPORT__ void SetDiagRunPath(const string& strDiagSoPath);
__MYEXPORT__ const string& GetDiagRunPath();


//判断网络是否可用
__MYEXPORT__ bool IsNetworkAvailable(void*env = NULL);

// 获取认证服务器地址，端口，必须先调用GetAuthoriseSvrAddress，然后调用GetAuthoriseSvrPort，否则得到的端口未必是正确的
__MYEXPORT__ string GetRpcServerAddress(const string& strSvrTag,void*env = NULL);
__MYEXPORT__ int GetRpcServerPort(const string& strSvrTag, void*env = NULL);
__MYEXPORT__ bool RpcDownLoadFiles(vector<string> const& vctRemote, vector<string> const& vctLoc, 
					  const string& strFileSvrTag, const string& strMd5CheckTag, void*env = NULL);
// 获取机器SN
__MYEXPORT__ const string& GetMachineSerialNumber(void *env = NULL);

// 获取机器注册码
__MYEXPORT__ const string& GetMachineRegisterCode(void *env = NULL);
__MYEXPORT__ bool DelFile(string const& file);

__MYEXPORT__ string GetVCISWver();//获取VCI软件版本
__MYEXPORT__ string GetVCIHWver();//获取VCI固件版本
__MYEXPORT__ string GetVCISerial();//获取VCI序列号
__MYEXPORT__ string GetVCIManufacturerTime();//获取VCI出厂日期
__MYEXPORT__ string GetVCIPassWord();//获取VCI密码