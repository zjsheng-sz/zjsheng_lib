#ifndef __NeedChange__
#define  __NeedChange__

typedef bool BOOL;

typedef short SHORT;
typedef unsigned short USHORT;

typedef int INT;
typedef unsigned int UINT;

typedef void VOID;

typedef unsigned char byte;
typedef long long LONG64;
typedef unsigned long long ULONG64;
typedef ULONG64 ULONGLONG;
typedef double DOUBLE;
//typedef unsigned double UDOUBLE;

#define TRUE true
#define FALSE false

#define _atoi64(x) atoi(x)

#define PAUSE SCAN_PAUSE
#define CONTINUE SCAN_CONTINUE
#define QUICK_ERASE SCAN_QUICK_ERASE
#define DISPLAY_FAULT SCAN_DISPLAY_FAULT
#define SAVE SCAN_SAVE

#include "DataSheet.h"
#include "Public.h"
#include "CFile.h"
#include "CTime.h"
#include "CString.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <ctype.h>
#include <algorithm>
using namespace std;


#define CString2string(x) (x.GetBuffer())
#define DF_NEXT_DTC NEXT_DTC
#define DF_PRE_DTC LAST_DTC

#define TRACE(...)

#define GetSelectionItem GetCurSelected

#define BASE_HELP_KEY_VALUE 0
#define TRACE(...)

#define GetSelectionItem GetCurSelected

#define BASE_HELP_KEY_VALUE 0

#define LastButOne TROUBLE_CODE_HELP_BASE


#define ClearDataStreamVector Clear

#define CRect W_RECT
#endif