/******************************************************************************
文件名称：SearchString.h SearchString.cpp

档 标 识：

摘    要：负责查询大文本文件中的某段字符串

用    途：


历史记录：
查询注意事项：
使用步骤：
2010年3月29日  李审霖       
步骤一:建立索引,用户修改并运行批处理文件ConverTool.bat.用户只需要修改文件名如D:\ProgramTest\jlr_text_name1.txt

步骤二:把D:\ProgramTest下的文件夹jlr_text_name1拷贝到diag.exe同级目录,禁止该目录下的任何文件,因为该目录保存
的是查询字符串需要的所有信息,*.tab为*.txt经过特殊转换+加密后的数据,*.idx是索引信息文件

步骤三: 使用示例请参照函数声明
---------------------------------------------------------------------------
时     间    作者    版本号      操    作    内    容
---------------------------------------------------------------------------
2010-1-23    李审霖  1.0         创建该类
2014-01-08   颜家松  2.0		 重构此类，实现跨平台以及支持融合文件
*******************************************************************************/
#pragma once
#include "pubmarc.h"
#include <string>
#include <vector>
using namespace std;

class ImpSearchString;

class __MYEXPORT__  CSearchString
{
public:
	CSearchString(void);
	~CSearchString(void);

	/*-----------------------------------------------------------------------------
	功    能： 设置用户打开的tab文件名

	参数说明：	strFileName 文件名称

	返 回 值: FALSE-failed， TRUE-succeed

	说    明：
	-----------------------------------------------------------------------------*/
	bool OpenTabFile(const string& strFileName);

	/*-----------------------------------------------------------------------------
	功    能： 打开索引文件以供查询

	参数说明：	vctColum 索引文件

	返 回 值: FALSE-failed， TRUE-succeed

	说    明：
	-----------------------------------------------------------------------------*/
	bool OpenIndexFile(const vector<int>& vctColum);
	/*-----------------------------------------------------------------------------
	功    能： 在文件中搜索指定列的指定字符串,并且保存查询到的行数据

	参数说明：	bQueryOneLine 只获取查询到的第一行
				vctStrSearch      搜索字符串容器
				vctColumSearch    搜索字符串对应的列容器
				vctStrLeach      过滤掉的字符串
				vctColumLeach    过滤掉字符串的对应列容器
				vctItemString 搜索到的数据
	返 回 值: FALSE-failed， TRUE-succeed

	说    明：vctStr vctColum 是一一对应的
	-----------------------------------------------------------------------------*/
	bool SearchString(vector<vector<string> >& vctItemString,
		              const bool bQueryOneLine, 
					  const vector<string>& vctStrSearch, 
					  const vector<int>& vctColumSearch,
					  const vector<string>& vctStrLeach = vector<string>(0), 
					  const vector<int>& vctColumLeach = vector<int>(0));

	/*-----------------------------------------------------------------------------
	功    能： 在文件中搜索指定列的指定字符串,并且保存查询到的行数据

	参数说明：	nMinColum      从nMinColum列开始
				nMaxColum    到nMaxColum列结束
				vctStrSearch 待搜索列的数据
				vctItemString 搜索到的数据
				bQueryOneLine 只获取查询到的第一行
	返 回 值: FALSE-failed， TRUE-succeed

	说    明：
	-----------------------------------------------------------------------------*/
	bool SearchString(vector<vector<string> >& vctItemString,
		            const bool bQueryOneLine,
	                const int nMinColum, 
		            const int nMaxColum,
					const vector<string>& vctStrSearch);


	/*-----------------------------------------------------------------------------
	功    能： 关闭索引文件,用户如果不用时,可以显示调用关闭函数,否则只有析构时才调用

	参数说明：	无
	返 回 值:无

	说    明：
	-----------------------------------------------------------------------------*/
	void CloseIndexFile(void);

	/*-----------------------------------------------------------------------------
	功    能： 关闭tab文件

	参数说明：	无
	返 回 值:无

	说    明：
	-----------------------------------------------------------------------------*/
	void CloseTabFile(void);
private:
	ImpSearchString* m_pImp;
};



