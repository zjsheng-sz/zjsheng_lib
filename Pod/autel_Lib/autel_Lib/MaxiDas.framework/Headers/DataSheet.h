#ifndef DATASHEET_H_HEADER_INCLUDED_B97BEBF3
#define DATASHEET_H_HEADER_INCLUDED_B97BEBF3
/******************************************************************************

Copyright (c) 2007, AUTEL Ltd,.Co

All rights reserved.

文件名称：CDataSheet.h

档 标 识：数据表组件

摘    要：负责数据表查询

传入要查询的ID，返回查询内容  

5.2.2.1	 命名
表文件名 ：：=  [语言代码] +  "_"  + [功能名称] + ".tab"
语言代码 ：：= "EN"，"CN"　．．．
功能名称 ：：=  数据流表名称，故障码表名称，文本表名称，菜单表名称，命令表名称，
自定义表名称，数据流名称及版本信息项名称的缩写表
数据流表名称 ：：= "DataStream"
数据流缩写表名称 ：：= "DataStreamAb"，数据流名称缩写，与数据流表ID一一对应
故障码表名称 ：：= "TroubleCode"
文本表名称 ：：= "Text"
菜单表名称 ：：= "Menu"
命令表名称 ：：= "Command"
自定义表名称：：= 名称自定义

5.2.2.2	编写结构
数据表的格式为ID +
内容，除命令表和自定义表以外的表ID为六个字节，其中第一个字节表示车系或ECU生产商，
其它五字节为程序员自己定义使用，ID中的各个字节可以是十六进制也可以是十进制。表
内容可以是文本也可以是数值。车系0x00保留，用于共用的标准数据。
5.2.2.3	 存贮结构
数据表内容能通过转换工具转换成方便检索，内容加密的文件形式
数据表 ：：=  [表头] + [索引] + [内容]
表头 ：：= [表标识] + [编译程序版本号] + [诊断程序版本号] + [实际ID长度]
+[被压缩掉ID数量] + [ [ [被压缩掉ID位置] + [被压缩掉ID内容] ] ] + 。。。 ]
+ [加密使用的数据]；
索引 ：：= [ [压缩后ID] + [物理偏移量] ] + 。。。；按ID升序排列
内容 ：：= [ [本条长度] + [ [ [本项长度]+[本项内容] ]+ 。。。 ] + 。。。
5.2.2.4	 访问方式
通过ID标识来获取内容。


历史记录：
---------------------------------------------------------------------------
时     间           作者        版本号	  操    作    内    容
---------------------------------------------------------------------------
2007-6-2 9:20:54  panxiangxi    1.0      创建此类。
2007-7-19         panxiangxi    1.1      CBinaryGroup SearchId(CBinary ID)注释更改  
2007-11-7         panxiangxi    1.2      增加加密
2007-11-10        panxiangxi    1.3      增加对故障码的帮助 
2007-11-10        panxiangxi    1.4      增加对顺序情况的判断，就是当下一个查询ID
与上一个查询ID只差1时速度要快，采用记录上
一个指针位置的办法
2007-11-28        panxiangxi    1.5      添加对数据流短库的支持xx_ds_short.tab   
2008-07-05        panxiangxi    2.0      添加类似数据库中Select while查询接口     
2008-08-20		  panxiangxi    2.1		 添加 SetReadFileToMemery，一次全部读文件到内存中(honda使用)
2008-08-12		  panxiangxi    2.2      添加GetLanguage()取得语言扩展名(honda使用) 
2009-04-09		  panxiangxi	2.3      添加SearchIDEx，主要是用于Honda提速

****************************************************************************/

// test
#include "adsStd.h"
#include <vector>
#include "Binary.h"
#include "BinaryGroup.h"
#include <string>
#include <map>
//#include "WarpFile.h"
using namespace std;

#include "pubmarc.h"

#define TEXT_TAB            "text.tab"
#define TCODE_TAB           "dtc.tab"
#define DATA_STREAM_TAB     "ds.tab"
#define MENU_TAB            "menu.tab"
#define MASK_TAB            "mask.tab"
#define DTC_HELP_TAB        "dtchelp.tab"
#define DATA_STREAM_SHORT_TAB        "ds_short.tab"


#define RECORD_PRE_BIN      // 记录上一个查询ID，目的是为了提速
#define DECRYPT

// 从标准文本库取得文本
__MYEXPORT__ string adsGetTextFromTextLib(CBinary const& bin);

// 取得标准资源，仅显示程序使用
__MYEXPORT__ string adsGetStdText(CBinary const& bin);
__MYEXPORT__ string adsGetTextFromTextLibEx(CBinary const& bin, const string& strSpilt = "$$");

typedef void (*PDEENCRYPTFUN)(unsigned char * pInBuf, unsigned int nInBufSize);

// modify by zys 2016/08/03
class CReadOnlyFileEx;
//class ReadOnlyFileInterface;
// end

class __MYEXPORT__  CDataSheet  
{
  public:
	  static void ClearVectorText();
	  CDataSheet();
      virtual ~CDataSheet();
    enum  { 
        NULL_FILE = -1,         // 空文件，初始化值
        TEXT_FILE = 0,          // 文本资源文件
        MENU_FILE = 1,          // 菜单文件
        TCODE_FILE = 2,         // 故障码文件
        DATA_STREAM_FILE = 3,   // 数据流文件
        MASK_FILE = 4,          // 掩码文件
        DTC_HELP = 5,           // 故障码帮助
        DATA_STREAM_SHORT_FILE = 6   // 数据流库，长的那一个，只在点帮助时调用
    };   


    typedef struct  
    {
        CBinary bin;
        string strText;
    }TEXT_RES;


    typedef struct
    {
        int iComaparePos;       // 比较位置
        string strCompare;      // 比较串

    }SELECT_CONDITION;
    
    
    static vector <TEXT_RES*> m_vctText;


    /*-----------------------------------------------------------------------------
        功    能：打开文件
        参数说明：strFileName    文件名
        返 回 值：false 为失败 ，true成功
        说    明：无
    -----------------------------------------------------------------------------*/
    bool OpenFile(const string &strFileName);

	    /*-----------------------------------------------------------------------------
        功    能：打开文件
        参数说明：iFileType
            CDataSheet::TEXT_FILEF          = 0,
            CDataSheet::MENU_FILE           = 1,
            CDataSheet::TCODE_FILE          = 2,
            CDataSheet::DATA_STREAM_FILE    = 3
        返 回 值：false 为失败 ，true成功
        说    明：无
    -----------------------------------------------------------------------------*/
    bool OpenFile(W_I16 iFileType);

    /*-----------------------------------------------------------------------------
        功    能：关闭文件
        参数说明：无
        返 回 值：无
        说    明：打开数据表使用完成后请调用此函数关闭文件
    ----------------------------------------------------------------------------*/
    void CloseFile();

    /*-----------------------------------------------------------------------------
        功    能：查询ID返回查询内容
        参数说明：binID         要查询的ID
        返 回 值：CBinaryGroup  其中包含0-n个Binary
        说    明：采用二分查找算法，此函数针对返回值为二个字符串以上或返回值是
                  十六进制数，查询前请确保已正确打开文件  
    -----------------------------------------------------------------------------*/
    CBinaryGroup SearchId(CBinary ID);

	// 此接口目前仅支持SetReadFileToMemery文件
	bool SearchIdEx(CBinary ID, CBinaryGroup &bgResult);


    /*-----------------------------------------------------------------------------
        功    能：取得文本
        参数说明：ID            要查询的ID
        返 回 值：文本串
        说    明：(只限于只有一个串的文本库)，查询前请确保已正确打开文件  
    -----------------------------------------------------------------------------*/
    const string GetText(CBinary ID);



    /*-----------------------------------------------------------------------------
        功    能：取得文本
        参数说明：vctCondition              查询条件
                  vctResult                 存放查询结果    
                  bFoundOneThenReturn       找到一个然后返回  
        返 回 值：文本串
        说    明：(只限于只有一个串的文本库)，查询前请确保已正确打开文件  
    -----------------------------------------------------------------------------*/
    bool SelectWhile(const vector <SELECT_CONDITION> &vctCondition, vector <CBinaryGroup> &vctResult, bool bFoundOneThenReturn = false);



   
    /*-----------------------------------------------------------------------------
        功    能：取得ID个数
        参数说明：
        返 回 值：
        说    明：如未打开文件返回0 
    -----------------------------------------------------------------------------*/
    W_U32 GetBinayrIDCount();


	// 需要在打开文件前调用，设置为一直将文件读到内存中，因邓工本田对速度有很高要求
	void SetReadFileToMemery();

 
    // 设置打开文件时是否添加应用程序路径,true为添加，默认为添加
    void SetAddAppPath(bool bAdd);


   static string m_strWorkDir;
   static void SetWorkDir(const string strWorkDir);
   // add by zys 2016/03/08 获取工作路径
   static const string& GetWorkDir();
   // end

   string GetLanguage();

private:
    struct tagW_FILE
    {
		// modify by zys 2016/08/03
		CReadOnlyFileEx* m_pFile;
        // ReadOnlyFileInterface* m_pFile;
		// end
        //////////////////////////////////////////////////////////////////////
        // V1.0文件头格式，详细参见tabtools编译程序
        // 文件头总计 16 个字节
        // 文件标识                                 // 2 "AT"
        // 数据库版本主版本号
	    unsigned short	uiTabToolsMainVersion;		// 2
        // 数据库版本子版本号
	    unsigned short	uiTabToolsSonVersion;		// 2
        // ID长度
        unsigned char szIDlength;                   // 1
        // 文件版本(从文件中取)
                                                    // 1(保留)
        W_FLOAT fTabVersion;                        // 4  add by zys 由于该变量没有使用，故借用它来存储，高1字节用来存储商用车二次加密标识，高2字节用来存储随机数
        // 总共有多少个ID(查询时使用)
        long iIDTotalCount;                         // 4   
                                                    
        ///////////////////////////////////////////////////////////////////////
        // 诊断程序版本号(从全局变量中取)
        W_FLOAT fDiagVersion;
        // 文件头长度
        int iGagHeadLength;
    };
    typedef struct tagW_FILE W_FILE;

    // 解密一个字符串
    //W_INT Descrypt(vector<CBinary> &vct);
    // 查询文本库缓冲，为了提高效率，查同样的ID直接返回(只适用于GetText)
    //string m_strText;
    // 查询ID缓冲，为了提高效率，查同样的ID直接返回(只适用于GetText)
    //CBinary m_binID;



    // 文件指针
    W_FILE m_WFile;
    // 当打开是同一个文件时不需要多次打开，为了提速
    int m_iOldFileType;



private:
	W_I32 MySeek(W_I32 lOff, W_U32 nFrom);
    W_U32 MyRead( void* lpBuf, W_U32 nCount );

#ifdef RECORD_PRE_BIN
    CBinary m_binLast;      // 上一次查询的ID
    int m_iOldMid;          // 上一次查询到的位置
#endif

    bool m_bAddAppPath;     // 是否添加运行路径

    void DecrypText(unsigned char *pString, int iLength);


    // SelectWhile 用到
    bool GetFromIdPos(unsigned char *pFileData, vector <int> vctIdPos, vector <CBinaryGroup> &vctResult);

	bool OpenFile(const string &strFileName, bool checkLanguage);

	// 2008-08-20添加
	bool m_bReadFileToMemery;
	char *m_pReadFileToMemery;

public:
	// add 2016/11/14
	static void ClearParamInfo();	

    // add 2017/06/21 添加临时目录 优先级比默认的高
    void SetTmpTabPath(const string & path);
    string m_tmpTabPath;

private:
	
};



#endif /* DATASHEET_H_HEADER_INCLUDED_B97BEBF3 */
