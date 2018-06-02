#ifndef TIME_H
#define TIME_H
#include "adsStd.h"
#include "CString.h"
#include <stdlib.h>
#include <time.h>
class CTimeSpan
{
public:
	CTimeSpan() throw();
	long long GetMinutes();
	long long GetSeconds();
	void SetTimeSpan(long long timeSpan);
	
private:
	long long  m_timeSpan;
};


class CTime
{
public:
	static CTime  GetCurrentTime() throw();
	
	CTime() throw();
	CTime( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec,
		int nDST = -1 );

	bool operator==( CTime time ) const throw();
	bool operator!=( CTime time ) const throw();
	bool operator<( CTime time ) const throw();
	bool operator>( CTime time ) const throw();
	bool operator<=( CTime time ) const throw();
	bool operator>=( CTime time ) const throw();
	//CTime operator-( CTime time ) const throw();
	CTimeSpan operator-( CTime time ) const throw();

	bool GetAsSystemTime( CTime& st ) const throw();

	long long GetTime() const throw();
        CString Format(string strData);

	int GetYear() const throw();
	int GetMonth() const throw();
	int GetDay() const throw();
	int GetHour() const throw();
	int GetMinute() const throw();
	int GetSecond() const throw();
        int GetDayOfWeek()  const throw();
	void SetTime(long long time);
	//void Format(string strData);

	// formatting using "C" strftime

private:
	CTime(struct tm const time);
	struct tm m_tm;
};
#endif