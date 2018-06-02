#ifndef CFILE_H
#define CFILE_H

#include <stdio.h>
//#include "ff.h"
#include "string"
#include "adsStd.h"
#include "CString.h"
#include <sys/stat.h>


#define CFileException FRESULT
#ifdef DEBUG_TEST
extern BOOL CFileTest(int i);
#endif
typedef  struct _stat FILINFO;
typedef FILE FIL;
typedef bool BOOL;
typedef unsigned int UINT;
typedef long LONG;
typedef unsigned long DWORD;

#define INVALID_HANDLE_VALUE -1

typedef char TCHAR;

class CFile 
{

public:
  
// Flag values

	enum OpenFlags {
					READ		=		0x01,
					OPEN_EXISTING =		0x00,
					WRITE		=		0x02,
					CREATE_NEW	=		0x04,
					CREATE_ALWAYS =	0x08,
					OPEN_ALWAYS	=	0x10,
					 WRITTEN	=		0x20,
					DIRTY		=		0x40,
					ERROR		=		0x80,
					modeRead =          0x01,
					modeWrite =         0x02,
					modeReadWrite =     0x03,
					modeCreate =        0x08,
                                        typeText = 0x00,
                                        
		};

	enum Attribute {
		normal =    0x00,
		readOnly =  0x01,
		hidden =    0x02,
		system =    0x04,
		volume =    0x08,
		directory = 0x10,
		archive =   0x20
                
		};

	string ChangeOpenFlag(UINT &nOpenFlag);

	enum SeekPosition { begin = 0x0, current = 0x1, end = 0x2 };

	enum { hFileNull = 0 };

// Constructors
	CFile();
	CFile(const char* lpszFileName, UINT nOpenFlags);

// Attributes
	//UINT m_hFile;
	virtual DWORD GetPosition() ;
	virtual string GetFileName() ;
	virtual string GetFilePath() ;
        static BOOL IsExistFile(const char* lpszFileName);

// Operations
	virtual BOOL Open(const char* lpszFileName, UINT nOpenFlags);

	virtual BOOL Open(CString  strFileName, UINT nOpenFlags);

	DWORD SeekToEnd();
	void SeekToBegin();
	void   GetFileAttributes(FILINFO *finfo, /* Ptr to store the File Information */
	const BYTE *dir);

	// backward compatible ReadHuge and WriteHuge
	DWORD ReadHuge(void* lpBuffer, DWORD dwCount);
	void WriteHuge(const void* lpBuffer, DWORD dwCount);

// Overridables

	virtual LONG Seek(LONG lOff, UINT nFrom);
	virtual DWORD GetLength() const;

	virtual UINT Read(void* lpBuf, UINT nCount);
	virtual void Write(const void* lpBuf, UINT nCount);
        virtual void WriteString(CString rString);
	virtual BOOL ReadString(CString& rString);
        
	void static Remove(string const& strFileName);
	void static Remove(CString const& strFileName);

	virtual void Close();
        BOOL IsOpenFile();

// Implementation
protected:
	BOOL m_bCloseOnDelete;
	string m_strFileName;
	long long m_curPosition;
public:
	FIL  *m_hFile;
};


class CMemFile : public CFile
{

public:
// Constructors
	CMemFile(UINT nGrowBytes = 1024);
	CMemFile(BYTE* lpBuffer, UINT nBufferSize, UINT nGrowBytes = 0);

// Operations
	void Attach(BYTE* lpBuffer, UINT nBufferSize, UINT nGrowBytes = 0);
	BYTE* Detach();
	virtual DWORD GetLength() const;

// Advanced Overridables
protected:
	virtual BYTE* Alloc(DWORD nBytes);
	virtual BYTE* Memcpy(BYTE* lpMemTarget, const BYTE* lpMemSource, UINT nBytes);
	virtual void Free(BYTE* lpMem);


// Implementation
protected:
	UINT m_nGrowBytes;
	DWORD m_nPosition;
	DWORD m_nBufferSize;
	DWORD m_nFileSize;
	BYTE* m_lpBuffer;
	BOOL m_bAutoDelete;

public:
	virtual ~CMemFile();
	virtual DWORD GetPosition() const;
	virtual LONG Seek(LONG lOff, UINT nFrom);
	virtual void SetLength(DWORD dwNewLen);
	virtual UINT Read(void* lpBuf, UINT nCount);
	virtual void Close();
};
#endif







































