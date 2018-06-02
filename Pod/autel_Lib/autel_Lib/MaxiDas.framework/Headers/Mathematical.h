// Mathematical.h: interface for the CMathematical class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATHEMATICAL_H__94DE6B97_E722_4626_97B4_FD406F11739E__INCLUDED_)
#define AFX_MATHEMATICAL_H__94DE6B97_E722_4626_97B4_FD406F11739E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#pragma warning(   disable   :   4786   ) 

#include <string>
#include <stack>
using namespace std;
#define DEBUG_PC_VERSION

#include "pubmarc.h"
/*-----------------------------------------------------------------------------

    Copyright (c) 2007, AUTEL Ltd,.Co

    All rights reserved.

    文件名称:Mathematical.h

    档 标 识:V1.0AX

    摘    要: 数据表达式类
             1. 可完成中缀表达式式到后缀表达式的转换
             2. 后缀表达式求值

    历史记录:
    ---------------------------------------------------------------------------
    时     间           作者   版本号	  操    作    内    容 
    ---------------------------------------------------------------------------
    2007-8-27 10:59:40  panxiangxi    1.0      创建此类。

  -------------------------------------------------------------------------*/
/*
支持符号如下:
                    ()
                    !
                    ~
                    /  *  %
                    +-
                    << >>
                    >   >=  <   <=
                    ==  !=
                    &
                    ^
                    |
                    &&
                    ||
                    ?:
                    BYTE[1]
                    BYTE[1]BIT[1]
                    CHAR[1]
                    "A" // 字符串仅用在双目运算符中
*/

/*
表达式求值的经典算法

编写代码对算术表达式求值的经典方法由 Donald Knuth 描述于 1962 年（请参阅 参考资料）。Knuth 将此概括为三个步骤： 

对中缀表达式进行语法分析 
中缀表达式到后缀表达式的转换 
对后缀表达式求值 
注意到我们谈到的这个经典算法有些简化：算术表达式只包含操作数、二元操作符和一种括号。此外，对于每个操作数和操作符，只用单个字符表示，使语法分析直观。

表达式表示法



算术表达式中最常见的表示法形式有 中缀、前缀和 后缀表示法。中缀表示法是书写表达式的常见方式，而前缀和后缀表示法主要用于计算机科学领域。 

中缀表示法 
中缀表示法是算术表达式的常规表示法。称它为 中缀表示法是因为每个操作符都位于其操作数的中间，这种表示法只适用于操作符恰好对应两个操作数的时候（在操作符是二元操作符如加、减、乘、除以及取模的情况下）。对以中缀表示法书写的表达式进行语法分析时，需要用括号和优先规则排除多义性。 

Syntax: operand1 operator operand2
Example: (A+B)*C-D/(E+F)
 


前缀表示法 
前缀表示法中，操作符写在操作数的前面。这种表示法经常用于计算机科学，特别是编译器设计方面。为纪念其发明家 ― Jan Lukasiewicz（请参阅 参考资料），这种表示法也称 波兰表示法。 

Syntax  : operator operand1 operand2
Example : -*+ABC/D+EF
 


后缀表示法 
在后缀表示法中，操作符位于操作数后面。后缀表示法也称 逆波兰表示法（reverse Polish notation，RPN），因其使表达式求值变得轻松，所以被普遍使用。 

Syntax  : operand1 operand2 operator
Example : AB+C*DEF+/-
 


前缀和后缀表示法有三项公共特征：

操作数的顺序与等价的中缀表达式中操作数的顺序一致 
不需要括号 
操作符的优先级不相关 
中缀表达式到后缀表达式的转换

要把表达式从中缀表达式的形式转换成用后缀表示法表示的等价表达式，必须了解操作符的优先级和结合性。 优先级或者说操作符的强度决定求值顺序；优先级高的操作符比优先级低的操作符先求值。 如果所有操作符优先级一样，那么求值顺序就取决于它们的 结合性。操作符的结合性定义了相同优先级操作符组合的顺序（从右至左或从左至右）。 

Left associativity  : A+B+C = (A+B)+C
Right associativity : A^B^C = A^(B^C)
 


转换过程包括用下面的算法读入中缀表达式的操作数、操作符和括号：

初始化一个空堆栈，将结果字符串变量置空。 
从左到右读入中缀表达式，每次一个字符。 
如果字符是操作数，将它添加到结果字符串。 
如果字符是个操作符，弹出（pop）操作符，直至遇见开括号（opening parenthesis）、优先级较低的操作符或者同一优先级的右结合符号。把这个操作符压入（push）堆栈。 
如果字符是个开括号，把它压入堆栈。 
如果字符是个闭括号（closing parenthesis），在遇见开括号前，弹出所有操作符，然后把它们添加到结果字符串。 
如果到达输入字符串的末尾，弹出所有操作符并添加到结果字符串。 
后缀表达式求值
 
对后缀表达式求值比直接对中缀表达式求值简单。在后缀表达式中，不需要括号，而且操作符的优先级也不再起作用了。您可以用如下算法对后缀表达式求值：

初始化一个空堆栈 
从左到右读入后缀表达式 
如果字符是一个操作数，把它压入堆栈。 
如果字符是个操作符，弹出两个操作数，执行恰当操作，然后把结果压入堆栈。如果您不能够弹出两个操作数，后缀表达式的语法就不正确。 
到后缀表达式末尾，从堆栈中弹出结果。若后缀表达式格式正确，那么堆栈应该为空。
*/

class __MYEXPORT__  CMathematical  
{
public:
	CMathematical();
	virtual ~CMathematical();

    /*-----------------------------------------------------------------------------
      功    能: 中缀表达式转成后缀表达式
      参数说明: strInfix    中缀表达式
                strPostfix  后缀表达式
                strError    错误信息，如返回false请查看此信息
      返 回 值: true        成功
                false       失败
                
      说    明: 
      2007-8-29 14:19:18
      -------------------------------------------------------------------------*/
    bool Infix2Postfix(string strInfix, 
        string &strPostfix, 
        string &strError);    


	

    /*-----------------------------------------------------------------------------
    功    能: 中缀表达式求值
    参数说明: strPostfix    中缀表达式，各元素间用空格分开
                            如7*8 传入应为 7 8 * 空格
              strResult     存放返回结果
              strtFormat    格式化，如%s,%.2f,%d等
              pData         BYTE[]所指向的数据
              iDataLength   数据长度
              
                            
    返 回 值: true 为计算成功 false 计算失败
    说    明: 
    2007-8-29 14:14:30
    -------------------------------------------------------------------------*/
    bool PostfixExpressionEvaluation(const string &strPostfix, 
        string &strResult, 
        const string  &strtFormat, 
        unsigned char *pData = NULL,
        int iDataLength = 0);


protected:
#ifdef DEBUG_PC_VERSION
    // 取操作符优先级,数越大优先级越高
    unsigned int GetOperatorPRI(const string &strOperator);

    // 添加一个新的操作符
    void AddOneOperator(const string &str);

    // 表达式是否正解
    bool CheckError(string strInfix, string &strError);
#endif


    // 计算一个操作符，计算结果压回栈中
    bool CalcOneOperator(const string &strOperator);

    // !计算
    bool CalLogicNot(const string &strOperand);
    // ~计算
    bool CalBitReverse(const string &strOperand);


    // 计算两个操作数的情况
    bool CalTwoOperand(const string &strOperand, 
        const string &strOperand1, 
        const string &strOperand2);
    // 计算两个操作数的情况
    bool CalTwoOperand(const string &strOperand, 
                        double f1, 
                        double f2);
    // 计算两个操作数的情况
    bool CalTwoOperand(const string &strOperand, unsigned char uc1, unsigned char uc2);
    // 计算两个操作数的情况
    bool CalTwoOperand(const string &strOperand, int i1, int i2);
	// add by zys 2015.8.31 为了防止超过int取值范围，使用64位int运算
	bool CalTwoOperand(const string &strOperand, long long i1, long long i2);
    // 计算两个操作数的情况
    bool CalThreeOperand(const string &strOperand1, const string &strOperand2, const string &strOperand3);

    // 十六进制字符串转成整数
    int HexStrToInt(const string &str);

    // 字符转换,可以是BYTE[]或BYTE[]BIT[]
    bool ByteDataConver(const string &str, unsigned char &uc);

    // 用于中缀转后缀，用于后缀求值
    stack <string> m_stack;
    string m_strPostfix;
    
private:
    unsigned char *m_pData;
    int m_iDataLength;    

};

#endif // !defined(AFX_MATHEMATICAL_H__94DE6B97_E722_4626_97B4_FD406F11739E__INCLUDED_)
