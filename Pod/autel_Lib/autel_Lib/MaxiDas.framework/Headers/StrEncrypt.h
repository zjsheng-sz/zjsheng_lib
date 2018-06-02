//! \file StrEncrypt.h 
//! \brief 定义字符串加解密函数 StringEncrypt/StringDecrypt 

#pragma once 
//#include <Windows.h>
#include <string>
#include "autelprotolxmlbase.h"

//extern "C"{
//! 文字串加密 
/*! 
\ingroup _GROUP_UTILFUNC 
\param srcstr 明文串，支持汉字等各种字符，可包含多个0字符， 
对于UNICODE串要先转换为ANSI串 
\param srclen 明文串的字符数，默认取strlen(srcstr)， 
如果串中包含多个0字符时可指定实际字符数 
\return 生成的加密串，由字母、数字、'_'、'.'组成， 
长度为4的倍数，至少为4，外加0结束符，len= (3 + len(srcstr))/3*4 
*/ 
AUTEL_PROTOL_XML_API std::string StringEncrypt(const char* srcstr, int srclen = -1); 


//! 字符串解密 
/*! 
\ingroup _GROUP_UTILFUNC 
\param srcstr 已加密的串，对于UNICODE串要先转换为ANSI串，字符数应为4的倍数且至少为4 
\return 生成的明文串，长度为 len(srcstr))/4*3。\n 
如果加密时的明文中包含了多个0字符，则此处得到的串中也有这些0字符，可遍历得到全部字符。 
*/ 

AUTEL_PROTOL_XML_API std::string StringDecrypt(const char* srcstr);
//}