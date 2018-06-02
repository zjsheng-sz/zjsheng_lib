#ifndef CSTRING_H
#define CSTRING_H

#include <cstdio> 
#include <iostream> 
#include <string>
using namespace std;

class CString 
{ 
public: 

/*声明构造函数 Begin*/ 
 CString(); 
 CString(const char *pStr); 
 CString(const CString &CStringSrc); 
 CString(string const &stringSrc); 
 CString(const char ch, const unsigned int uiRepeat = 1); 
 CString(const char *pStr, unsigned int uiLen, unsigned int uiBegin = 0); 
 CString(CString &CStringSrc, unsigned int uiLen, unsigned int uiBegin = 0); 
 /*声明构造函数 End*/ 
  
 /*声明析构函数 Begin*/ 
 ~CString(); 
 /*声明析构函数 End*/ 

 /*声明成员函数 Begin*/ 
 unsigned int GetLength(void)const; 
 char *GetBuffer(void) const; 
 bool IsEmpty(void); 
 void Empty(void); 
 char GetAt(unsigned int uiIndex); 
 void SetAt(unsigned int uiIndex, char ch); 
 //用于比较的函数 
 int Compare(const char *str); 
 int Compare(CString &Str); 
 int CompareNoCase(const char *str); 
 int CompareNoCase(CString &Str); 
 //字符串截取函数 
 CString &Right(unsigned int uiLength); 
 CString &Left(unsigned int uiLength); 
 CString &Mid(unsigned int uiBegin); 
 CString &Mid(unsigned int uiBegin, unsigned int uiLength); 
 //大小转换函数 
 CString &MakeUpper(void); 
 CString &MakeLower(void); 
 CString &MakeReverse(void); 
 //字符串修饰(包括置换,删除,添加等) 
 CString &Replace(char chOld, char chNew); 
 CString &Replace(char *pOld, char *pNew); 
 CString &Insert(unsigned int uiIndex, char ch); 
 CString &Insert(unsigned int uiIndex, char *str); 
 CString &Remove(char ch); 
 CString &Delete(unsigned int uiIndex, unsigned int uiCount = 1); 
 CString &TrimLeft(void); 
 CString &TrimLeft(char ch); 
 CString &TrimLeft(char *str); 
 CString &TrimRight(void); 
 CString &TrimRight(char ch); 
 CString &TrimRight(char *str); 
 //查找函数 
 int Find(char ch, unsigned int uiBegin = 0); 
 int Find(char *str, unsigned int uiBegin = 0); 
 int ReverseFind(char ch); 
 int FindOneOf(char *str); 
 /*声明成员函数 End*/ 
  
 /*声明重载的操作符 Begin*/ 
 //作为成员函数 
 CString& operator= (const char ch); 
 CString&   operator= (const char *str); 
 CString&   operator= (const   CString &Str); 
 
  CString&   operator= (const string &Str); 
 CString&     operator+=(const char ch); 
 CString&   operator+=(const char *str); 
 CString&   operator+=( const CString &Str); 
 const char& operator[](unsigned int n); 
 //公共函数
 static char *strlwr(char *tmp1); 
 static char *strupr(char *tmp1);
 static char *strrev(char *pString); 
 static  string CString2string(const CString &Str);
 void Format( char *pBuffer, ... );
  void Format(CString str, ... );
  int  Find(CString strData);

 //作为友元 
 friend  CString& operator+ (CString &Str1, CString &Str2); 
 friend CString& operator+ (CString &Str, const char *str); 
 friend CString& operator+ (const char *str, CString &Str); 
 friend CString& operator+ (CString &Str, char ch); 
 friend CString& operator+ (char ch, CString &Str); 
 friend bool operator==(CString &Str1, CString &Str2); 
 friend bool operator==(CString &Str, const char *str); 
 friend bool operator==(const char *str, CString &Str); 
 friend bool operator!=(const CString &Str1, const CString &Str2); 
friend  bool operator!=(const CString &Str, const char *str); 
friend bool operator!=(const char *str, const CString &Str); 
 friend bool operator< (const CString &Str1, const CString &Str2); 
 friend bool operator< (const CString &Str, const char *str); 
friend  bool operator< (const char *str, const CString &Str); 
 friend bool operator> (const CString &Str1, const CString &Str2); 
friend  bool operator> (const CString &Str, const char *str); 
 friend bool operator> (const char *str, const CString &Str); 
friend  bool operator<=(const CString &Str1, const CString &Str2); 
friend  bool operator<=(const CString &Str, const char *str); 
 friend bool operator<=(const char *str, const CString &Str); 
 friend bool operator>=(const CString &Str1, const CString &Str2); 
friend  bool operator>=(const CString &Str, const char *str); 
friend  bool operator>=(const char *str, const CString &Str);

/*声明重载的操作符 End*/ 

 char *GetFirstBuffer() const;

private: 

 char *pString; //指向存储空间的首地址 
 CString &Trim(int mode, char ch); 
}; 
#endif
CString StringToCString(string & str);
