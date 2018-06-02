// Expression.h: interface for the CExpression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPRESSION_H__0EC11C10_97A8_4366_85F2_44FA3DEAD8FE__INCLUDED_)
#define AFX_EXPRESSION_H__0EC11C10_97A8_4366_85F2_44FA3DEAD8FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Mathematical.h"
#include "adsStd.h"
#include "Binary.h" 
#include "BinaryGroup.h"

#include "pubmarc.h"
 
__MYEXPORT__ string Calc_Script(CBinary binRevData,W_I16 pos,CBinary binExpress,W_I16 offset);
__MYEXPORT__ void ResetExpression();

__MYEXPORT__ bool isalphaOrNum(char c);
__MYEXPORT__  bool string_replace(string & strBig, const string & strsrc, const string &strdst); 
__MYEXPORT__ CBinaryGroup FindExpress(CBinary bin);

class __MYEXPORT__  CExpression
{
public:
	CExpression();
	virtual ~CExpression();
	bool Calc(const string strExpress, string &strReustl, string &strFormat);


protected:
	// 从括号内取得一个表达式存到strInBracket,同时strSrc 删除 strInBracket部份
	bool GetExpression_FromBracket(string &strSrc, string &strInBracket);	

	// 取=号之后直到分号的内容存到strResult,同时strSrc 删除 strResult部份
	bool GetExpression_FromEqualMark(string &strSrc, string &strResult);
	
	// 取输出格式从注释之间
	bool GetFormat_FromRemark(const string &strSrc, string &strFormat);	

	// 取得case后的表达式
	bool GetExpression_FromCase(string &strSrc, string &strResult);	

	bool CalcOne(string &strSrc, string &strReturn, const string &strFormat);
																	


};

#endif // !defined(AFX_EXPRESSION_H__0EC11C10_97A8_4366_85F2_44FA3DEAD8FE__INCLUDED_)
