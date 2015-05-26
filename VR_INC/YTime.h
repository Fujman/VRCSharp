#ifndef __yTIME_H
#define __yTIME_H

// C section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#include <time.h>
#include <sys/timeb.h>

#ifndef __YTIME_DEFINED
#define __YTIME_DEFINED
typedef __int64 YTIME;
#endif//__YTIME_DEFINED

#define YTIME_INVALID   (-9223372036854775808i64)//0x8000000000000000i64

#define YTIME_1MILLENIUM ( 315569088000000000i64)//365*100*10+24*10+2 days
#define YTIME_1CENTURY   (  31556736000000000i64)//365*100+24 days
#define YTIME_1YEAR      (    315360000000000i64)//365 days
#define YTIME_1MONTH     (     25920000000000i64)// 30 days
#define YTIME_1WEEK      (      6048000000000i64)
#define YTIME_1DAY       (       864000000000i64)
#define YTIME_1HOUR      (        36000000000i64)
#define YTIME_1MINUTE    (          600000000i64)
#define YTIME_1SECOND    (           10000000i64)
#define YTIME_1MS        (              10000i64)
#define YTIME_1MCS       (                 10i64)
#define YTIME_100NS      (                  1i64)

#define YTIME_MIN       (-9223372036854775808i64)
#define YTIME_MAX        (9223372036854775807i64)//YTime at 30828.9.14 02:48:05.4775807

#define YTIME_YTIME_BASE (                  0i64)//YTime at 1601.01.01 00:00:00 gmt
#define YTIME_1601_01_01 (                  0i64)//YTime at 1601.01.01 00:00:00 gmt
#define YTIME_OLEDT_BASE (  YTime(1899,12,31)   )//==1.0 at 1899.12.31 00:00:00 local, 1.0==day
#define YTIME_1899_12_31 (  94353984000000000i64)//YTime at 1899.12.31 00:00:00 gmt
#define YTIME_CTIME_BASE ( 116444736000000000i64)//CTime=0x00000000 at 1970.01.01 00:00:00 gmt
#define YTIME_1970_01_01 ( 116444736010000000i64)//CTime=0x00000001 at 1970.01.01 00:00:01 gmt
#define YTIME_2000_01_01 ( 125911584000000000i64)//YTime at 2000.01.01 00:00:00 gmt,   ==36526.
#define YTIME_2038_01_19 ( 137919572470000000i64)//CTime=0x7FFFFFFF at 2038.01.19 03:14:07 gmt
#define YTIME_9999_12_30 (2650466448000000000i64)//YTime at 9999.12.30 12:00:00 gmt //max always formatable
#define YTIME_OLEDT_MAXF (  YTime(9999,12,31)   )//max formatable time by COleDateTime:;Format(), min 100.01.01 - cannot be represented by YTime

#define OLEDT_0100_01_01 (             -657434.0)//OleDT at  100.01.01 //min formatable time
#define OLEDT_1899_12_29 (                  -1.0)//OleDT at 1899.12.29
#define OLEDT_1899_12_30 (                   0.0)//OleDT at 1899.12.30
#define OLEDT_1899_12_31 (                   1.0)//OleDT at 1899.12.31
#define OLEDT_1900_01_01 (                   2.0)//OleDT at 1900.01.01
#define OLEDT_2000_01_01 (36525.999999999+1.0e-9)//OleDT at 2000.01.01: 1ns resolution
#define OLEDT_9999_01_01 (             2958465.0)//OleDT at 9999.12.31 //max formatable time

#ifndef AFX_OLE_DATETIME_ERROR
#define AFX_OLE_DATETIME_ERROR (-1)
#endif

// C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus
#include <afxdisp.h>
#include "YTimeZone.h"

class YTimeSpan;
class YTimeZone;
class YTime;
class YRealTime;
class CDumpContext;
class CArchive;

////////////////////////////////////////////////////////////////////////////////////
// YTime

class YTime //1-JAN-1601...inf  64-bit value representing the number of 100-nanosecond (100*1e-9sec) intervals since January 1, 1601
{
  friend class                  YTimeSpan;
  friend class                  YRealTime;
protected://TZ support //AY 01.11.2010
  typedef const YTimeZone*      LPCTZ;  //UTC = local time + bias
protected:
  union { //UTC format of storage - GMT based
    YTIME                       m_data; //UTC
    FILETIME                    m_time; //UTC
  };
public:
  YTime(LPCTZ ptz, short nYear, short nMonth, short nDay, short nHour, short nMin, short nSec, short nMsec);//TZ local time
  YTime(short nYear, short nMonth, short nDay, short nHour, short nMin, short nSec, short nMsec=0);//LOCAL time
  YTime(short nYear, short nMonth, short nDay);           //LOCAL //pure date
  YTime(short nHour, short nMin, short nSec, short nMsec);//LOCAL //pure time
  YTime();
  YTime(YTIME time);                         //UTC  //1-JAN-1601...inf         64-bit value representing the number of 100-nanosecond intervals since January 1, 1601
  YTime(const YTime& time);                  //UTC  //1-JAN-1601...inf         64-bit value representing the number of 100-nanosecond intervals since January 1, 1601
  YTime(const FILETIME& st);          //always UTC  //1-JAN-1601...inf         64-bit value representing the number of 100-nanosecond intervals since January 1, 1601
  YTime(const SYSTEMTIME& st);        //always UTC  //1-JAN-0000...31-DEC-9999 16*8-bit !!! Note:CTime  and COleDateTime use LOCAL time in constructors !!!
  YTime(void*,WORD wDate, WORD wTime, int nMsec=0); //1-JAN-1980...31-DEC-2107 16+16-bit seconds/2 !
  YTime(const CTime& time, int nMsec=0);//alws UTC  //1-JAN-1970...31-DEC-2038 32-bit value representing the number of one second intervals since January 1, 1970
  YTime(const struct _timeb *timeptr);        //?   //1-JAN-1970...31-DEC-2038 32+16-bit Time in seconds since midnight (00:00:00), January 1, 1970, coordinated universal time (UTC).
  YTime(const struct tm* a_tm, int nMsec=0);//local //1-JAN-0000...31-DEC-9999 16*9-bit
  YTime(const COleDateTime& otm, int nMsec=0);      //1-JAN-0100...31-DEC-9999 REAL*8+?
  YTime(const SYSTEMTIME& st, LPCTZ ptz);//TZ dep   //1-JAN-0000...31-DEC-9999 //AY 01.11.2010
#ifdef _TIME32_T_DEFINED
  YTime(__time64_t time, int nMsec  );//always UTC  //1-JAN-1970...inf         64-bit value representing the number of one second intervals since January 1, 1970
  YTime(__time32_t time, int nMsec=0);//always UTC  //1-JAN-1970...31-DEC-2038 32-bit value representing the number of one second intervals since January 1, 1970
#else
  YTime(time_t time, int nMsec=0);    //always UTC  //1-JAN-1970...31-DEC-2038 32-bit value representing the number of one second intervals since January 1, 1970
#endif
public:
  int SetDateTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nMsec=0);//LOCAL
  int SetDate(int nYear, int nMonth, int nDay);            //LOCAL - same tz and daylight only! //AY 01.11.2010 - to do: must be removed
  int SetTime(int nHour, int nMin, int nSec, int nMsec=0); //LOCAL - same tz and daylight only! //AY 01.11.2010 - to do: must be removed
  int SetDateTime(CTime ctDate, CTime ctTime, int nMsec=0);//LOCAL - same tz and daylight only! //AY 01.11.2010 - to do: must be removed
public://TZ constructors
  int SetDateTime(LPCTZ ptz,int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nMsec=0);//AnyTZ - AY 01.11.2010
  int SetDate(LPCTZ ptz, int nYear, int nMonth, int nDay);            //AnyTZ - AY 01.11.2010
  int SetTime(LPCTZ ptz, int nHour, int nMin, int nSec, int nMsec=0); //AnyTZ - AY 01.11.2010
  int SetDateTime(LPCTZ ptz, CTime ctDate, CTime ctTime, int nMsec=0);//AnyTZ - AY 01.11.2010

  void                          Invalidate();
  BOOL                          IsInvalid() const;
  BOOL                          IsBad()     const;
  static YTime                  INVALID();

  static YTime PASCAL           mk_utc(short nYear, short nMonth, short nDay, short nHour=0, short nMin=0, short nSec=0, short nMsec=0);//UTC
  static __inline YTime PASCAL  mktime(YTIME tics);//UTC
  static __inline YTime PASCAL  mktime64(__int64 time, int nMsec=0);//AY 10.06.2014 time_64_t like

  static short PASCAL           weekday(short nYear, short nMonth, short nDay); //UTC
  static short PASCAL           yearday(short nYear, short nMonth, short nDay); //UTC
  static short PASCAL           monthdays(short nYear, short nMonth);           //UTC

  static YTIME PASCAL           GetCurrentBias();  //UTC=local+bias
  static YTime PASCAL           GetCurrentDate();  //UTC    //AY 18.11.2009 pure date,  don't called GetCurrentTime for the debug purposes
  static YTime PASCAL           GetCurrentTime();  //UTC
  static BOOL  PASCAL           SetCurrentTime(YTime t);

  BOOL                          GetAsSystemTime(SYSTEMTIME& st) const;//UTC
  BOOL                          GetAsFileTime(FILETIME& ft) const;    //UTC
  BOOL                          GetAsDosDateTime(WORD* pwDosDate, WORD* pwDosTime) const;
  struct tm*                    GetGmtTm( struct tm* ptm = NULL ) const;  //see CTime
  struct tm*                    GetLocalTm( struct tm* ptm = NULL ) const;//see CTime
  YTIME                         GetAsYTIME()const;
  CTime                         GetAsCTime(int* pnMsec=NULL)const;
  double                        GetDATE() const; //VARIANT-compatible OLE time
  time_t                        GetTime() const;
                                operator YTIME() const { return m_data; }
                                operator CTime() const;
                                operator COleDateTime() const;

public: //user interface settings
  static YTimeSpan              GetWindowsDaylightSavingDistance();
  static YTimeSpan              GetWindowsTimeZoneDistance();
  static BOOL                   IsWindowsDaylightSavingEnabled();

  static YTimeSpan              GetNowGmtDistance();     //== -bias (current)
  static BOOL                   IsNowDaylightSaving();   //active only if auto daylight saving is enabled, always FALSE elsewhere

  inline YTimeSpan              GetGmtDistance() const;  //== -bias of specified time
  inline BOOL                   IsDaylightSaving() const;//The C run-time library assumes the United States’s rules for implementing the calculation of Daylight Saving Time (DST).
                                                         //active only if auto daylight saving is enabled, always FALSE elsewhere
public: //user interface
//BOOL                          GetAsSystemTime(SYSTEMTIME& st) const;//UTC

  YTime                         GetPureTime() const;     //LOCAL - same tz and daylight only! //AY 01.11.2010 - to do: must be removed
  YTime                         GetPureDate() const;     //LOCAL - same tz and daylight only! //AY 01.11.2010 - to do: must be removed

  int                           GetYear() const;         //UTC
  int                           GetMonth() const;        //UTC
  int                           GetDay() const;          //UTC
  int                           GetHour() const;         //UTC
  int                           GetMinute() const;       //UTC

  int                           GetSecond() const;
  int                           GetMilliseconds() const;
  int                           GetMicroseconds() const;
  int                           GetNanoseconds() const;

  int                           GetDayOfWeek() const;    //UTC
  int                           GetDayOfYear() const;    //current LOCAL


public: //user interface - TZ specified //AY 01.11.2010

  BOOL                          GetAsSystemTime(SYSTEMTIME& stLocal, LPCTZ ptz) const; //AnyTZ

  YTime                         GetPureTime(LPCTZ ptz) const;
  YTime                         GetPureDate(LPCTZ ptz) const;

  int                           GetYear(LPCTZ ptz) const;
  int                           GetMonth(LPCTZ ptz) const;
  int                           GetDay(LPCTZ ptz) const;
  int                           GetHour(LPCTZ ptz) const;
  int                           GetMinute(LPCTZ ptz) const;

  int                           GetDayOfWeek(LPCTZ ptz) const;
  int                           GetDayOfYear(LPCTZ ptz) const;//TO DO

public: // formatting
  CString                       GetAsString() const {return FormatEx(_T("%H:%M:%S %d.%m.%Y"));}

  CString                       Format(LPCTSTR lpszFormat) const; //strftime,wcsftime,++ //see CTime
  CString                       Format(UINT nFormatID) const; //see CTime
  CString                       FormatGmt(LPCTSTR pFormat) const; //strftime,wcsftime //see CTime
  CString                       FormatGmt(UINT nFormatID) const; //see CTime

  CString                       FormatEx(LPCTSTR lpszFormat=_T("%c")) const;//see YTime.cpp
  CString                       FormatEx(UINT nFormatID) const;    //see YTime.cpp
  CString                       FormatGmtEx(LPCTSTR pFormat=_T("%c")) const;//see YTime.cpp
  CString                       FormatGmtEx(UINT nFormatID) const; //see YTime.cpp

  CString                       FormatAsOleDateTime(LPCTSTR lpszFormat) const; //strftime,wcsftime,++ //see CTime
  CString                       FormatAsOleDateTime(UINT nFormatID) const; //see COleDateTime
  CString                       Format(DWORD dwFlags=0, LCID lcid=LANG_USER_DEFAULT) const;//see COleDateTime
  BOOL                          ParseDateTime(LPCTSTR lpszDate, DWORD dwFlags=0, LCID lcid=LANG_USER_DEFAULT) const;//throw( CMemoryException );throw( COleException );//see COleDateTime

public: // comparison
  BOOL                          operator ==(YTime time) const { return m_data==time.m_data; }
  BOOL                          operator !=(YTime time) const { return m_data!=time.m_data; }
  BOOL                          operator <(YTime time) const  { return m_data<time.m_data; }
  BOOL                          operator >(YTime time) const  { return m_data>time.m_data; }
  BOOL                          operator <=(YTime time) const { return m_data<=time.m_data; }
  BOOL                          operator >=(YTime time) const { return m_data>=time.m_data; }

  YTimeSpan                     operator -(YTime time) const;
  YTime                         operator +(YTimeSpan timeSpan) const;
  YTime                         operator -(YTimeSpan timeSpan) const;
  const YTime&                  operator +=(YTimeSpan timeSpan);
  const YTime&                  operator -=(YTimeSpan timeSpan);
  YTime&                        operator =(const YTime& timeSrc);

  BOOL                          operator ==(YTIME tics) const { return m_data==tics; }
//YTime&                        operator =(YTIME tics);
public://implementation
  static YTIME                  GlobalToLocal(YTIME tGlobal);
  static YTIME                  LocalToGlobal(YTIME tLocal);
public://helpers
  BOOL                          InRange(YTime tMin, YTime tMax) const;
  YTime                         Adjust(YTime tMin, YTime tMax) const;
public://AFX support
  friend CDumpContext& AFXAPI   operator<<( CDumpContext& dc, YTime time );
  friend CArchive& AFXAPI       operator<<( CArchive& ar, YTime time );
  friend CArchive& AFXAPI       operator>>( CArchive& ar, YTime& time );
#ifdef _DEBUG
  int Dump() { TRACE(_T("%s"),GetAsString()); return 0; }
#endif
public://UNICODE/ANSI support extensions
  #ifndef __NO_ANSI_TO_UNICODE_SUPPORT
  #if defined(UNICODE) || defined(_UNICODE)
    CString                     Format(LPCSTR lpszFormat) const; //strftime,wcsftime,++ //see CTime
    CString                     FormatGmt(LPCSTR pFormat) const; //strftime,wcsftime //see CTime
    CString                     FormatEx(LPCSTR lpszFormat) const;//see YTime.cpp
    CString                     FormatGmtEx(LPCSTR pFormat) const;//see YTime.cpp
    CString                     FormatAsOleDateTime(LPCSTR lpszFormat) const; //strftime,wcsftime,++ //see CTime
  #else 
    CString                     Format(LPCWSTR lpszFormat) const; //strftime,wcsftime,++ //see CTime
    CString                     FormatGmt(LPCWSTR pFormat) const; //strftime,wcsftime //see CTime
    CString                     FormatEx(LPCWSTR lpszFormat) const;//see YTime.cpp
    CString                     FormatGmtEx(LPCWSTR pFormat) const;//see YTime.cpp
    CString                     FormatAsOleDateTime(LPCWSTR lpszFormat) const; //strftime,wcsftime,++ //see CTime
  #endif
  #endif//__NO_ANSI_TO_UNICODE_SUPPORT
public://helpers
    static YTIME                _GetPureDate(YTIME t);
    static YTIME                _GetPureTime(YTIME t);
    static YTIME                _mkpure(YTIME tDate, YTIME tTime);

    static YTIME                _GetPureDate(CTime ct);
    static YTIME                _GetPureTime(CTime ct,              int nMsec=0);
    static YTIME                _mkpure(CTime ctDate, CTime ctTime, int nMsec=0);
public:
    static YTIME                safe_get(const YTime* pTime);
    static YTIME                safe_get(const YTIME* pTime);
    static void                 safe_put(YTIME v, YTime* pTime);
    static void                 safe_put(YTIME v, YTIME* pTime);

    YTIME                       safe_get() volatile const;//from this
    void                        safe_put(YTIME v) volatile;//to this

    static YTime                printable(YTime t);//AY 16.04.2010

    static const YTimeZone*     safe_get_tz();
};

////////////////////////////////////////////////////////////////////////////////////
// YTimeSpan
/*
  tics*       .01 = nanosecond      
                1 = 100 nanoseconds -2^63...2^63  -9223372036854775808...9223372036854775807  -9e18...9e18
               10 = microsecond                    -922337203685477580...922337203685477580   -9e17...9e17
           10 000 = millisecond                       -922337203685477...922337203685477      -9e14...9e14
       10 000 000 = sec                                   922337203685...922337203685         -9e11...9e11
      600 000 000 = min                                    15372286728...15372286728          -1e10...1e10
   36 000 000 000 = hour                  LONG               256204778...256204778             -2e8...2e8
  864 000 000 000 = day                   LONG                10675199...10675199              -1e7...1e7
13140 000 000 000 = year                  LONG                  701930...701930                -7e5...7e5
*/                                                                                         
                               
class YTimeSpan //64-bit value representing the number of 100-nanosecond (100*1e-9sec) intervals
{
  friend class                  YRealTime;
  friend class                  YTime;
protected:
  union {
    YTIME                       m_timeSpan;
    FILETIME                    m_time;
  };
public:
  YTimeSpan();
  YTimeSpan(YTIME time);
  YTimeSpan(long nDays, __int64 nHours, __int64 nMins, __int64 nSecs, __int64 nMsec=0);
  YTimeSpan(__int64 nHours, __int64 nMins, __int64 nSecs);
  YTimeSpan(const CTimeSpan& ts, __int64 nMsec=0);
  YTimeSpan(const YTimeSpan& timeSpanSrc);
  const YTimeSpan&              operator=(const YTimeSpan& timeSpanSrc);
  const YTimeSpan&              operator=(YTIME nTics);
                                operator YTIME() const;
                                operator CTimeSpan() const;
  long                          GetDays() const;
  int                           GetHours() const;
  int                           GetMinutes() const;
  int                           GetSeconds() const;
  int                           GetMilliseconds() const;
  int                           GetMicroseconds() const;
  int                           GetNanoseconds() const;
  long                          GetTotalHours() const;
  __int64                       GetTotalMinutes() const;
  __int64                       GetTotalSeconds() const;
  __int64                       GetTotalMilliseconds() const;
  __int64                       GetTotalMicroseconds() const;
  __int64                       GetTotalNanoseconds() const;
  BOOL                          IsZero() const;
  BOOL                          IsNegative() const;
  BOOL                          IsPositive() const;

  CString                       Format(LPCTSTR lpszFormat=_T("%c")) const;//see YTime.cpp
  CString                       Format(UINT nFormatID) const;    //see YTime.cpp
  YTimeSpan                     Parse(LPCTSTR szTimeSpan);    //"0000:00:00.000" //AY 02.09.2010
  static YTimeSpan              ParseTime(LPCTSTR szTimeSpan);//"0000:00:00.000" //AY 02.09.2010

  YTimeSpan                     operator-(YTimeSpan timeSpan) const;
  YTimeSpan                     operator+(YTimeSpan timeSpan) const;
  const YTimeSpan&              operator+=(YTimeSpan timeSpan);
  const YTimeSpan&              operator-=(YTimeSpan timeSpan);
  BOOL                          operator==(YTimeSpan timeSpan) const;
  BOOL                          operator!=(YTimeSpan timeSpan) const;
  BOOL                          operator<(YTimeSpan timeSpan) const;
  BOOL                          operator>(YTimeSpan timeSpan) const;
  BOOL                          operator<=(YTimeSpan timeSpan) const;
  BOOL                          operator>=(YTimeSpan timeSpan) const;
  YTimeSpan                     operator*(__int64 nTimes) const;
  YTimeSpan                     operator/(__int64 nTimes) const;
  YTimeSpan                     operator%(__int64 nTimes) const;
  const YTimeSpan&              operator*=(__int64 nTimes);
  const YTimeSpan&              operator/=(__int64 nTimes);
  const YTimeSpan&              operator%=(__int64 nTimes);
  YTimeSpan                     operator*(int nTimes) const;
  YTimeSpan                     operator/(int nTimes) const;
  YTimeSpan                     operator%(int nTimes) const;
  const YTimeSpan&              operator*=(int nTimes);
  const YTimeSpan&              operator/=(int nTimes);
  const YTimeSpan&              operator%=(int nTimes);
  __int64                       operator/(const YTimeSpan& ts) const;
  __int64                       operator%(const YTimeSpan& ts) const;
public://AFX support
  friend CDumpContext& AFXAPI   operator<<( CDumpContext& dc, YTimeSpan ts );
  friend CArchive& AFXAPI       operator<<( CArchive& ar, YTimeSpan ts );
  friend CArchive& AFXAPI       operator>>( CArchive& ar, YTimeSpan& ts );
public://UNICODE/ANSI support extensions
  #ifndef __NO_ANSI_TO_UNICODE_SUPPORT
  #if defined(UNICODE) || defined(_UNICODE)
    CString                     Format(LPCSTR  lpszFormat) const;
  #else 
    CString                     Format(LPCWSTR lpszFormat) const;
  #endif
  #endif//__NO_ANSI_TO_UNICODE_SUPPORT
public:
  static YTIME                safe_get(const YTimeSpan* pTime);
  static YTIME                safe_get(const YTIME* pTime);
  static void                 safe_put(YTIME v, YTimeSpan* pTime);
  static void                 safe_put(YTIME v, YTIME* pTime);

  YTIME                       safe_get() volatile const;
  void                        safe_put(YTIME v) volatile;
};

////////////////////////////////////////////////////////////////////////////////////
// YTime implementation

inline void YTime::Invalidate()
{
  m_time.dwHighDateTime = 0x80000000, m_time.dwLowDateTime = 0;
}
inline BOOL YTime::IsInvalid() const
{
  return(m_time.dwHighDateTime==0x80000000 && m_time.dwLowDateTime==0);
}
inline YTime YTime::INVALID()
{
  YTime time; time.Invalidate(); return time; 
}
inline BOOL YTime::IsBad() const
{
  return((m_time.dwHighDateTime==0x80000000||m_time.dwHighDateTime==0) && m_time.dwLowDateTime==0);
}

inline YTime::YTime(short nYear, short nMonth, short nDay, short nHour, short nMin, short nSec, short nMsec/*0*/)
{
  union{ FILETIME ft; YTIME t; }; SYSTEMTIME st;
  st.wYear   = nYear;
  st.wMonth  = nMonth;
  st.wDay    = nDay;
  st.wHour   = nHour;
  st.wMinute = nMin;
  st.wSecond = nSec;
  st.wMilliseconds = nMsec;
  st.wDayOfWeek = 0;//ignored
  if(!::SystemTimeToFileTime(&st,&ft)/* || !::LocalFileTimeToFileTime(&ft,&m_time) AY 7.04.2003*/)
    Invalidate();
  else  //AY 7.04.2003
    m_data = LocalToGlobal(t);
}
inline YTime::YTime(short nYear, short nMonth, short nDay)// pure date
{
  union{ FILETIME ft; YTIME t; }; SYSTEMTIME st={0};
  st.wYear   = nYear;
  st.wMonth  = nMonth;
  st.wDay    = nDay;
  if(!::SystemTimeToFileTime(&st,&ft)/* || !::LocalFileTimeToFileTime(&ft,&m_time) AY 7.04.2003*/)
    Invalidate();
  else  //AY 7.04.2003
    m_data = LocalToGlobal(t);
}
inline YTime::YTime(short nHour, short nMin, short nSec, short nMsec)//pure time
{
  union{ FILETIME ft; YTIME t; }; SYSTEMTIME st;
  st.wYear   = 1601;
  st.wMonth  = 1;
  st.wDay    = 1;
  st.wHour   = nHour;
  st.wMinute = nMin;
  st.wSecond = nSec;
  st.wMilliseconds = nMsec;
  st.wDayOfWeek = 0;//ignored
  if(!::SystemTimeToFileTime(&st,&ft)/* || !::LocalFileTimeToFileTime(&ft,&m_time) AY 7.04.2003*/)
    Invalidate();
  else  //AY 7.04.2003
    m_data = LocalToGlobal(t);
}

inline YTime PASCAL YTime::mk_utc(short nYear, short nMonth, short nDay, short nHour, short nMin, short nSec, short nMsec/*0*/)
{
  SYSTEMTIME st;
  FILETIME ft;
  st.wYear   = nYear;
  st.wMonth  = nMonth;
  st.wDay    = nDay;
  st.wHour   = nHour;
  st.wMinute = nMin;
  st.wSecond = nSec;
  st.wMilliseconds = nMsec;
  st.wDayOfWeek = 0;//ignored
  if(!::SystemTimeToFileTime(&st,&ft))
    return YTime::mktime(YTIME_INVALID);
  else
    return YTime(ft);
}

inline YTIME YTime::LocalToGlobal(YTIME a_tLocal) 
{ YTime tLocal(YTime::mktime(a_tLocal));

  BOOL bOk = (tLocal>=YTime::mktime(YTIME_1970_01_01+YTIME_1SECOND*60*60*12) && tLocal<=YTime::mktime(YTIME_2038_01_19-YTIME_1SECOND*60*60*12));
  ASSERT(bOk);
  if(!bOk)
    return YTime::mktime(YTIME_INVALID); //TO DO: more wide bounds, depend of timezone?

  struct tm  stm = {0};
  SYSTEMTIME st;
  if(!tLocal.GetAsSystemTime(st))
    return YTIME_INVALID; //TO DO: more wide bounds, depend of timezone?

  stm.tm_year = st.wYear-1900,
  stm.tm_mon  = st.wMonth-1,
  stm.tm_mday = st.wDay,
  stm.tm_hour = st.wHour,
  stm.tm_min  = st.wMinute,
  stm.tm_sec  = st.wSecond,
  stm.tm_isdst= -1;/*auto*/

  YTime  tGlobal;
  tGlobal = YTime( ::mktime(&stm), 0/*ms*/ );
  tGlobal += YTimeSpan(((YTIME)tLocal)%YTIME_1SECOND);
  return tGlobal;
}

inline YTIME YTime::GlobalToLocal(YTIME a_tGlobal)
{ YTime tGlobal(YTime::mktime(a_tGlobal));

  BOOL bOk = (tGlobal>=YTime::mktime(YTIME_1970_01_01+YTIME_1SECOND*60*60*12) && tGlobal<=YTime::mktime(YTIME_2038_01_19-YTIME_1SECOND*60*60*12));
  ASSERT(bOk);
  if(!bOk)
    return YTIME_INVALID;
  struct tm  stm;
  if( !tGlobal.GetLocalTm(&stm) )
    return YTIME_INVALID;

  YTime  tLocal;
  tLocal = YTime::mk_utc(
    stm.tm_year+1900,
    stm.tm_mon+1,
    stm.tm_mday,
    stm.tm_hour,
    stm.tm_min,
    stm.tm_sec
  );
  tLocal += YTimeSpan(((YTIME)tGlobal)%YTIME_1SECOND);
  return tLocal;
}

inline YTimeSpan YTime::GetWindowsDaylightSavingDistance()
{
  YTime tWinter(YTime::mktime(YTIME_2000_01_01));
  YTime tSummer(tWinter+YTimeSpan(365/2,00,00,00,000));
  YTIME tsWinter = GlobalToLocal(tWinter)-tWinter;//+2
  YTIME tsSummer = GlobalToLocal(tSummer)-tSummer;//+3
  return tsSummer-tsWinter;
}

inline YTimeSpan YTime::GetWindowsTimeZoneDistance()
{
  return YTimeSpan(CTimeSpan(_timezone));
}

inline BOOL      YTime::IsWindowsDaylightSavingEnabled()
{
  return !GetWindowsDaylightSavingDistance().IsZero();
}

inline YTimeSpan YTime::GetNowGmtDistance()
{
  union { YTIME tGlobal; FILETIME ftGlobal; };
  union { YTIME tLocal ; FILETIME ftLocal ; };
  tGlobal = YTime::GetCurrentTime();
  VERIFY( ::FileTimeToLocalFileTime(&ftGlobal,&ftLocal) );
  return YTime::mktime(tLocal) - YTime::mktime(tGlobal);
}

inline BOOL YTime::IsNowDaylightSaving()
  { return YTime::GetCurrentTime().IsDaylightSaving(); }

inline YTimeSpan YTime::GetGmtDistance() const
{
  YTime tGlobal = *this;
  YTime tLocal  = YTime::mktime(YTime::GlobalToLocal(*this));
  return YTime(tLocal) - YTime(tGlobal);
}

inline BOOL YTime::IsDaylightSaving() const
  { struct tm t={0}; if(!GetLocalTm(&t)) { ASSERT(0); return -1; } return (t.tm_isdst>0); }


__inline YTime PASCAL YTime::mktime(YTIME tics)
  { YTime yt; yt.m_data = tics; return yt; }

inline YTime::YTime()
  { Invalidate(); }// m_data=0?
inline YTime::YTime(YTIME time)
  { m_data = time; }
inline YTime::YTime(const YTime& time)
  { m_data = time.m_data; }


inline YTime::YTime(const FILETIME& st)
{ 
  m_time = st; 
}
inline YTime::YTime(const SYSTEMTIME& st) 
{
  if(!::SystemTimeToFileTime(&st,&m_time))
    Invalidate();
}
inline YTime::YTime(void*, WORD wDosDate, WORD wDosTime, int nMsec/*0*/)
{
  ASSERT(nMsec>=0 && nMsec<2000);
  if(!::DosDateTimeToFileTime(wDosDate,wDosTime,&m_time))
    Invalidate();
  else
    m_data += (nMsec*10000);
}

__inline YTime PASCAL YTime::mktime64(__int64 time, int nMsec)//AY 10.06.2014
{
  ASSERT(nMsec>=0 && nMsec<1000);
  YTIME data = 0;
  if(time==-1 || time==0)
    return YTime();
  else
    data = YTIME_1SECOND*time+YTIME_1MS*nMsec+YTIME_CTIME_BASE;
  return YTime(data);
}


#ifdef _TIME32_T_DEFINED  
inline YTime::YTime(__time64_t time, int nMsec)//AY 08.04.2008
{
  ASSERT(nMsec>=0 && nMsec<1000);
  if(time==-1)
    Invalidate();
  else
    m_data = YTIME_1SECOND*time+YTIME_1MS*nMsec+YTIME_CTIME_BASE;
}

inline YTime::YTime(__time32_t time, int nMsec)//AY 08.04.2008
#else
inline YTime::YTime(time_t time, int nMsec)  //AY 31.03.2004
#endif
{ 
  ASSERT(nMsec>=0 && nMsec<1000);
  if(time==-1)
    Invalidate();
  else
    m_data = YTIME_1SECOND*time+YTIME_1MS*nMsec+YTIME_CTIME_BASE;
}
inline YTime::YTime(const CTime& time, int nMsec/*0*/)//afx.h
{
  *this = ( time==-1 ? YTime() : YTime(time.GetTime(), nMsec) );
}
inline YTime::YTime(const struct _timeb *timeptr) //sys/timeb.h
{ 
  *this = YTime((time_t)(timeptr->time),timeptr->millitm);
}
inline YTime::YTime(const struct tm* a_tm, int nMsec/*0*/)//time.h
{
  ASSERT(nMsec>=0 && nMsec<1000);
  struct tm the_tm = *a_tm;
  time_t time = ::mktime(&the_tm);
  if(time==-1)
    Invalidate();
  else
    *this = YTime(time,nMsec);
}
inline YTime::YTime(const COleDateTime& otm, int nMsec/*0*/) //afxdisp.h
{
  ASSERT(nMsec>=0 && nMsec<1000);
  if(otm.GetStatus()!=COleDateTime::DateTimeStatus::valid)
    { Invalidate(); return; }
  SYSTEMTIME st; FILETIME ft,ft_local;
  BOOL bRet = otm.GetAsSystemTime(st);
  st.wMilliseconds += nMsec;
  if(bRet)
    bRet = ::SystemTimeToFileTime(&st,&ft_local);
  if(bRet)
    bRet = ::LocalFileTimeToFileTime(&ft_local,&ft);
  if(!bRet)
    Invalidate();
  else
    m_time = ft;
}

inline YTIME PASCAL YTime::GetCurrentBias()
{
  FILETIME ftGlobal; ::GetSystemTimeAsFileTime(&ftGlobal);
  FILETIME ftLocal;  
  if(!::FileTimeToLocalFileTime(&ftGlobal,&ftLocal))
    return (YTIME)0;
  return YTime(ftGlobal)-YTime(ftLocal);//UTC = local + bias
}

inline YTime PASCAL YTime::GetCurrentDate() //AY 18.11.2009 don't called GetCurrentTime for the debug purposes
{
  FILETIME ft; ::GetSystemTimeAsFileTime(&ft);//UTC
  return YTime(ft).GetPureDate();
}

inline YTime PASCAL YTime::GetCurrentTime()
{
  FILETIME ft; ::GetSystemTimeAsFileTime(&ft);//UTC
  return YTime(ft);
}

inline BOOL  PASCAL YTime::SetCurrentTime(YTime t)
{
  SYSTEMTIME st; t.GetAsSystemTime(st); //UTC
  return ::SetSystemTime(&st);
}


inline int YTime::SetDateTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nMsec/*0*/)
{
  *this = YTime(nYear,nMonth,nDay,nHour,nMin,nSec,nMsec);
  return(IsInvalid()?-1:0);
}

inline BOOL YTime::GetAsFileTime(FILETIME& ft) const
{
  if(IsInvalid())
    return FALSE;
  ft = m_time;
  return TRUE;
}
inline BOOL YTime::GetAsSystemTime(SYSTEMTIME& st) const
{
  if(IsInvalid())
    return FALSE;
  if(!::FileTimeToSystemTime(&m_time,&st))
    return FALSE;
  return TRUE;
}
inline BOOL YTime::GetAsDosDateTime(WORD* pwDosDate, WORD* pwDosTime) const
{
  if(!::FileTimeToDosDateTime(&m_time,pwDosDate,pwDosTime))
    return FALSE;
  return TRUE;
}

inline struct tm* YTime::GetGmtTm(struct tm* ptm/*NULL*/) const  //see CTime
  { return GetAsCTime().GetGmtTm(ptm); }   //AY 31.03.2004 { return CTime(m_time).GetGmtTm(ptm); }

inline struct tm* YTime::GetLocalTm(struct tm* ptm/*NULL*/) const//see CTime
  { return GetAsCTime().GetLocalTm(ptm); } //AY 31.03.2004 { return CTime(m_time).GetLocalTm(ptm); }

inline YTIME YTime::GetAsYTIME()const
  { return m_data; }

inline CTime YTime::GetAsCTime(int* pnMsec/*NULL*/)const //AY 31.03.2004
{ 
  if(IsInvalid())
    return -1;
  if(pnMsec!=NULL)
    *pnMsec = GetMilliseconds();
  return CTime((time_t)((m_data-YTIME_CTIME_BASE)/YTIME_1SECOND)); // return operator CTime();//OLD: AY 31.03.2004
}

inline double YTime::GetDATE() const //VARIANT-compatible OLE time
  { return (IsInvalid()? -1.7976931348623158e+308/*-DBL_MAX*/: ((COleDateTime)(*this)).m_dt); }

inline time_t YTime::GetTime() const
  { return (IsInvalid()? -1: GetAsCTime().GetTime()); }  //AY 31.03.2004 { return CTime(m_time).GetTime(); }

inline YTime::operator CTime() const
  { return (IsInvalid()? CTime(-1) : GetAsCTime()); }    //AY 31.03.2004...CTime(m_time,0) //AY 27.10.2003//... CTime(m_time));

inline YTime::operator COleDateTime() const
  { return COleDateTime(m_time); }

//
// Calendar //////////////////////////////////////////////////////////////////
//

inline short PASCAL YTime::weekday(short nYear, short nMonth, short nDay) //UTC
{ 
  FILETIME ft; SYSTEMTIME st = {0};
  st.wYear  = nYear;
  st.wMonth = nMonth;
  st.wDay   = nDay;
  if(!::SystemTimeToFileTime(&st,&ft))
    return -1;
  if(!::FileTimeToSystemTime(&ft,&st))
    return -1;
  return short(st.wDayOfWeek);
}

inline short PASCAL YTime::monthdays(short nYear, short nMonth)           //UTC
{
  static const short days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  if(nMonth<1 || nMonth>12)
    return -1;
  short iDays = days[nMonth-1];
  if(nMonth==2) //february correction for leap year
    iDays += weekday(nYear,2,29)>=0? 1 : 0;
  return iDays;
}

inline short PASCAL YTime::yearday(short nYear, short nMonth, short nDay) //UTC
{
  static const short days[] = {31,59,90,120,151,181,212,243,273,304,334,365};
  if(mk_utc(nYear, nMonth, nDay).IsInvalid())
    return -1;
  short iDay = days[nMonth-1] + nDay;
  if(nMonth>2) //february correction for leap year
    iDay += monthdays(nYear, 2)-28;
  return iDay;
}

//
// TZ loacal based (obsolete error implementation ) ////////////////////////////////////////////////////////
//

inline int YTime::GetYear() const   //UTC
  { SYSTEMTIME st; return(!GetAsSystemTime(st) ? -1024*1024 : st.wYear); }
inline int YTime::GetMonth() const  //UTC
  { SYSTEMTIME st; return(!GetAsSystemTime(st) ? -1 : st.wMonth); }
inline int YTime::GetDay() const    //UTC
  { SYSTEMTIME st; return(!GetAsSystemTime(st) ? -1 : st.wDay); }
inline int YTime::GetHour() const   //UTC
  { SYSTEMTIME st; return(!GetAsSystemTime(st) ? -1 : st.wHour); }
inline int YTime::GetMinute() const //UTC
  { SYSTEMTIME st; return(!GetAsSystemTime(st) ? -1 : st.wMinute); }
inline int YTime::GetSecond() const
  { SYSTEMTIME st; return(!GetAsSystemTime(st) ? -1 : st.wSecond); }
inline int YTime::GetMilliseconds() const
  { SYSTEMTIME st; return(!GetAsSystemTime(st) ? -1 : st.wMilliseconds); }
inline int YTime::GetMicroseconds() const 
  { SYSTEMTIME st; return(!GetAsSystemTime(st) ? -1 : (int)((m_data%YTIME_1SECOND)/10L) ); } //100-nanosec to microseconds multiplier
inline int YTime::GetNanoseconds() const
  { SYSTEMTIME st; return(!GetAsSystemTime(st) ? -1 : (int)((m_data%YTIME_1SECOND)*100) ); } //100-nanosec to nanoseconds

inline int YTime::GetDayOfWeek() const//UTC
  { SYSTEMTIME st; return(!GetAsSystemTime(st) ? -1 : st.wDayOfWeek); }

inline int YTime::GetDayOfYear() const//current LOCAL
{
  if(IsInvalid())
    return -1;
  int iDayOfYear = COleDateTime(m_time).GetDayOfYear();
  if(iDayOfYear==AFX_OLE_DATETIME_ERROR)
    return -1;
  return(iDayOfYear); 
}
//
// TZ based //////////////////////////////////////////////////////////////////
//
inline BOOL YTime::GetAsSystemTime(SYSTEMTIME& stLocal, LPCTZ ptz) const
{
  const TIME_ZONE_INFORMATION* pTZ = ptz;
  if(IsInvalid())
    return FALSE;
  SYSTEMTIME st;
  if(!::FileTimeToSystemTime(&m_time,&st))
    return FALSE;
  if(ptz==NULL)
    ptz = safe_get_tz();
  if(ptz==NULL)
    return FALSE;
  if(!::SystemTimeToTzSpecificLocalTime(const_cast<LPTIME_ZONE_INFORMATION>(pTZ),&st,&stLocal))
    return FALSE;
  return TRUE;
}

inline YTime YTime::GetPureDate(LPCTZ ptz) const
  { YTime yt = *this; yt.SetTime(ptz,0,0,0); return yt; }
inline YTime YTime::GetPureTime(LPCTZ ptz) const
  { YTime yt = *this; yt.SetDate(ptz,0,0,0); return yt; }

inline int YTime::GetYear(LPCTZ ptz) const
  { SYSTEMTIME st; return(!GetAsSystemTime(st, ptz) ? -1024*1024 : st.wYear); }
inline int YTime::GetMonth(LPCTZ ptz) const
  { SYSTEMTIME st; return(!GetAsSystemTime(st, ptz) ? -1 : st.wMonth); }
inline int YTime::GetDay(LPCTZ ptz) const
  { SYSTEMTIME st; return(!GetAsSystemTime(st, ptz) ? -1 : st.wDay); }
inline int YTime::GetHour(LPCTZ ptz) const
  { SYSTEMTIME st; return(!GetAsSystemTime(st, ptz) ? -1 : st.wHour); }
inline int YTime::GetMinute(LPCTZ ptz) const
  { SYSTEMTIME st; return(!GetAsSystemTime(st, ptz) ? -1 : st.wMinute); }

inline int YTime::GetDayOfWeek(LPCTZ ptz) const
  { SYSTEMTIME st; return(!GetAsSystemTime(st, ptz) ? -1 : st.wDayOfWeek); }

// Formatting //////////////////////////////////////////////////////////////////

inline YTime   YTime::printable(YTime t)//AY 16.04.2010
  { return t.IsBad()? YTime(YTIME_1970_01_01) : t; }

inline CString YTime::Format(LPCTSTR lpszFormat) const //strftime,wcsftime,++   //see CTime
  { YTime yt = printable(*this); return CTime(yt).Format(lpszFormat); }
inline CString YTime::Format(UINT nFormatID) const                              //see CTime
  { YTime yt = printable(*this); return CTime(yt).Format(nFormatID); }
inline CString YTime::FormatGmt( LPCTSTR pFormat ) const //strftime,wcsftime    //see CTime
  { YTime yt = printable(*this); return CTime(yt).FormatGmt(pFormat); }
inline CString YTime::FormatGmt( UINT nFormatID ) const                         //see CTime
  { YTime yt = printable(*this); return CTime(yt).FormatGmt(nFormatID); }

inline CString YTime::FormatAsOleDateTime(LPCTSTR lpszFormat) const //strftime,wcsftime,++ //see CTime
  { return ((COleDateTime)*this).Format(lpszFormat); }
inline CString YTime::FormatAsOleDateTime(UINT nFormatID) const //see COleDateTime
  { return ((COleDateTime)*this).Format(nFormatID); }
inline CString YTime::Format(DWORD dwFlags/*0*/, LCID lcid/*LANG_USER_DEFAULT*/) const//see COleDateTime
  { return ((COleDateTime)*this).Format(dwFlags, lcid); }
inline BOOL    YTime::ParseDateTime(LPCTSTR lpszDate, DWORD dwFlags/*0*/, LCID lcid/*LANG_USER_DEFAULT*/) const //see COleDateTime
  //throw( CMemoryException );throw( COleException );
  { return ((COleDateTime)*this).ParseDateTime(lpszDate, dwFlags, lcid); }

inline YTimeSpan YTime::operator-(YTime time) const
  { return YTimeSpan(m_data - time.m_data); }
inline YTime YTime::operator-(YTimeSpan timeSpan) const
  { return YTime::mktime(m_data - timeSpan.m_timeSpan); }
inline YTime YTime::operator+(YTimeSpan timeSpan) const
  { return YTime::mktime(m_data + timeSpan.m_timeSpan); }
inline const YTime& YTime::operator+=(YTimeSpan timeSpan)
  { m_data += timeSpan.m_timeSpan; return *this; }
inline const YTime& YTime::operator-=(YTimeSpan timeSpan)
  { m_data -= timeSpan.m_timeSpan; return *this; }
inline YTime& YTime::operator =(const YTime& timeSrc)
  { m_data = timeSrc.m_data; return *this; }
//inline YTime& YTime::operator =(YTIME tics)
//  { *this = mktime(tics); return *this; }
inline BOOL YTime::InRange(YTime tMin, YTime tMax) const
  { return *this>=tMin && *this<=tMax; }
inline YTime YTime::Adjust(YTime tMin, YTime tMax) const
  { return *this<tMin?tMin: *this>tMax?tMax: *this; }

inline YTIME YTime::_GetPureDate(YTIME t)                         //GMT only!
  { ASSERT(!YTime(t).IsInvalid()); return t - (t % YTIME_1DAY); }
inline YTIME YTime::_GetPureTime(YTIME t)                         //GMT only!
  { ASSERT(!YTime(t).IsInvalid()); return t % YTIME_1DAY; }
inline YTIME YTime::_mkpure(YTIME tDate, YTIME tTime)             //GMT only!
  { return _GetPureDate(tDate)+_GetPureTime(tTime); }

inline YTIME YTime::_GetPureDate(CTime ct)                        //GMT only!
  { YTIME t = YTime(ct,0);     return _GetPureDate(t); }
inline YTIME YTime::_GetPureTime(CTime ct, int nMsec)             //GMT only!
  { YTIME t = YTime(ct,nMsec); return _GetPureTime(t); }
inline YTIME YTime::_mkpure(CTime ctDate, CTime ctTime, int nMsec)//GMT only!
  { return _GetPureDate(ctDate)+_GetPureTime(ctTime, nMsec); }

////////////////////////////////////////////////////////////////////////////////////
// YTimeSpan implementation
inline YTimeSpan::YTimeSpan()
  { m_timeSpan = 0; }
inline YTimeSpan::YTimeSpan(YTIME time)
  { m_timeSpan = time; }
inline YTimeSpan::YTimeSpan(long nDays, __int64 nHours, __int64 nMins, __int64 nSecs, __int64 nMsec)
  { m_timeSpan = 10000*(nMsec + 1000*(nSecs + 60* (nMins + 60* (nHours + 24* nDays)))); }
inline YTimeSpan::YTimeSpan(__int64 nHours, __int64 nMins, __int64 nSecs)
  { m_timeSpan = 10000*(0 + 1000*(nSecs + 60* (nMins + 60* (nHours + 24* 0)))); }
inline YTimeSpan::YTimeSpan(const CTimeSpan& ts, __int64 nMsec)
  { m_timeSpan = 10000*(nMsec + 1000*((__int64)ts.GetTotalSeconds())); }
inline YTimeSpan::YTimeSpan(const YTimeSpan& timeSpanSrc)
  { m_timeSpan = timeSpanSrc.m_timeSpan; }
inline const YTimeSpan& YTimeSpan::operator=(const YTimeSpan& timeSpanSrc)
  { m_timeSpan = timeSpanSrc.m_timeSpan; return *this; }
inline const YTimeSpan& YTimeSpan::operator=(YTIME nTics)
  { m_timeSpan = nTics; return *this; }
inline YTimeSpan::operator YTIME() const
  { return m_timeSpan; }
inline YTimeSpan::operator CTimeSpan() const
  { return CTimeSpan((long)(m_timeSpan / 10000000L)); } //100-nanesec to seconds multiplier
inline long YTimeSpan::GetDays() const
  { return (long)(m_timeSpan / 10000000L / (24*3600L)); }
inline long YTimeSpan::GetTotalHours() const
  { return (long)(m_timeSpan / 10000000L / 3600); }
inline int YTimeSpan::GetHours() const
  { return (int)(GetTotalHours() - GetDays()*24); }
inline __int64 YTimeSpan::GetTotalMinutes() const
  { return m_timeSpan / 10000000L / 60; }

inline int YTimeSpan::GetMinutes() const
  { return (int)(GetTotalMinutes() - GetTotalHours()*60); }

inline __int64 YTimeSpan::GetTotalSeconds() const
  { return m_timeSpan / 10000000L; }
inline int YTimeSpan::GetSeconds() const
  { return (int)(GetTotalSeconds() - GetTotalMinutes()*60); }

inline __int64 YTimeSpan::GetTotalMilliseconds() const
  { return m_timeSpan / 10000L; }             //100-nanosec to milliseconds multiplier
inline int YTimeSpan::GetMilliseconds() const
  { return (int)(GetTotalMilliseconds() - GetTotalSeconds()*1000L); }

inline __int64 YTimeSpan::GetTotalMicroseconds() const
  { return m_timeSpan / 10L; }                //100-nanosec to microseconds multiplier
inline int YTimeSpan::GetMicroseconds() const
  { return (int)(GetTotalMicroseconds() - GetTotalSeconds()*1000000L); }

inline __int64 YTimeSpan::GetTotalNanoseconds() const
  { if(((m_timeSpan*100)/100)!=m_timeSpan) return 0; return m_timeSpan*100; }
inline int YTimeSpan::GetNanoseconds() const
  { return (int)((m_timeSpan%YTIME_1SECOND)*100); }

inline BOOL YTimeSpan::IsZero() const
  { return m_timeSpan==0; }
inline BOOL YTimeSpan::IsNegative() const
  { return m_timeSpan<0; }
inline BOOL YTimeSpan::IsPositive() const
  { return m_timeSpan>0; }
inline YTimeSpan YTimeSpan::operator-(YTimeSpan timeSpan) const
  { return YTimeSpan(m_timeSpan - timeSpan.m_timeSpan); }
inline YTimeSpan YTimeSpan::operator+(YTimeSpan timeSpan) const
  { return YTimeSpan(m_timeSpan + timeSpan.m_timeSpan); }
inline const YTimeSpan& YTimeSpan::operator+=(YTimeSpan timeSpan)
  { m_timeSpan += timeSpan.m_timeSpan; return *this; }
inline const YTimeSpan& YTimeSpan::operator-=(YTimeSpan timeSpan)
  { m_timeSpan -= timeSpan.m_timeSpan; return *this; }
inline BOOL YTimeSpan::operator==(YTimeSpan timeSpan) const
  { return m_timeSpan == timeSpan.m_timeSpan; }
inline BOOL YTimeSpan::operator!=(YTimeSpan timeSpan) const
  { return m_timeSpan != timeSpan.m_timeSpan; }
inline BOOL YTimeSpan::operator<(YTimeSpan timeSpan) const
  { return m_timeSpan < timeSpan.m_timeSpan; }
inline BOOL YTimeSpan::operator>(YTimeSpan timeSpan) const
  { return m_timeSpan > timeSpan.m_timeSpan; }
inline BOOL YTimeSpan::operator<=(YTimeSpan timeSpan) const
  { return m_timeSpan <= timeSpan.m_timeSpan; }
inline BOOL YTimeSpan::operator>=(YTimeSpan timeSpan) const
  { return m_timeSpan >= timeSpan.m_timeSpan; }
inline YTimeSpan YTimeSpan::operator*(__int64 nTimes) const
  { return YTimeSpan(m_timeSpan*nTimes); }
inline YTimeSpan YTimeSpan::operator/(__int64 nTimes) const
  { return YTimeSpan(m_timeSpan/nTimes); }
inline YTimeSpan YTimeSpan::operator%(__int64 nTimes) const
  { return YTimeSpan(m_timeSpan%nTimes); }
inline const YTimeSpan& YTimeSpan::operator*=(__int64 nTimes)
  { m_timeSpan *= nTimes; return *this; }
inline const YTimeSpan& YTimeSpan::operator/=(__int64 nTimes)
  { m_timeSpan /= nTimes; return *this; }
inline const YTimeSpan& YTimeSpan::operator%=(__int64 nTimes)
  { m_timeSpan %= nTimes; return *this; }
inline YTimeSpan YTimeSpan::operator*(int nTimes) const
  { return YTimeSpan(m_timeSpan*nTimes); }
inline YTimeSpan YTimeSpan::operator/(int nTimes) const
  { return YTimeSpan(m_timeSpan/nTimes); }
inline YTimeSpan YTimeSpan::operator%(int nTimes) const
  { return YTimeSpan(m_timeSpan%nTimes); }
inline const YTimeSpan& YTimeSpan::operator*=(int nTimes)
  { m_timeSpan *= nTimes; return *this; }
inline const YTimeSpan& YTimeSpan::operator/=(int nTimes)
  { m_timeSpan /= nTimes; return *this; }
inline const YTimeSpan& YTimeSpan::operator%=(int nTimes)
  { m_timeSpan %= nTimes; return *this; }
inline __int64 YTimeSpan::operator/(const YTimeSpan& ts) const
  { return m_timeSpan / ts.m_timeSpan; }
inline __int64 YTimeSpan::operator%(const YTimeSpan& ts) const
  { return m_timeSpan % ts.m_timeSpan; }

///////////////////////////////////////////////////////////////////
// YTime/YTimeSpan multithread support implementation
#include "xscalar.h"
//
// GET
//
inline YTIME YTime::safe_get() volatile const
  { return __safe_get_i64(&m_data); }

inline YTIME YTime::safe_get(const YTime* pTime)
  { return safe_get_i64(&pTime->m_data); }

inline YTIME YTime::safe_get(const YTIME* pTime)
  { return safe_get_i64(pTime); }

inline YTIME YTimeSpan::safe_get() volatile const
  { return __safe_get_i64(&m_timeSpan); }

inline YTIME YTimeSpan::safe_get(const YTimeSpan* pTime)
  { return safe_get_i64(&pTime->m_timeSpan); }

inline YTIME YTimeSpan::safe_get(const YTIME* pTime)
  { return safe_get_i64(pTime); }

//
// PUT
//
inline void YTime::safe_put(YTIME v) volatile
  { __safe_put_i64(v, &m_data); }

inline void YTime::safe_put(YTIME v, YTime* pTime)
  { safe_put_i64(v, &pTime->m_data); }

inline void YTime::safe_put(YTIME v, YTIME* pTime)
  { safe_put_i64(v, pTime); }

inline void  YTimeSpan::safe_put(YTIME v) volatile
  { __safe_put_i64(v, &m_timeSpan); }

inline void YTimeSpan::safe_put(YTIME v, YTimeSpan* pTime)
  { safe_put_i64(v, &pTime->m_timeSpan); }

inline void YTimeSpan::safe_put(YTIME v, YTIME* pTime)
  { safe_put_i64(v, pTime); }

inline const YTimeZone* YTime::safe_get_tz()
  { return YTimeZone::safe_get_tz(); }

//// AFX support ///////////////////////////////////////////////////////////////////
#define YTIME_DUMP_FORMAT _T("%c,%a  %Y.%m.%d %H:%M:%S")

class CTimeDump:public CTime{public:CTimeDump(const CTime& t){*((CTime*)this)=t;}};

inline CDumpContext& AFXAPI   operator<<( CDumpContext& dc, CTimeDump time )
{
  if(time==-1)
    return dc<<"CTime(invalid)";
  dc<<_T("CTime(")<<time.Format(YTIME_DUMP_FORMAT _T(".000"));//<<")";
  dc<<_T("  GMT: ")<<time.FormatGmt(YTIME_DUMP_FORMAT _T(".000"))<<_T(")");
  return dc;
}
inline CDumpContext& AFXAPI   operator<<( CDumpContext& dc, YTime time )
{
  if(time.IsInvalid())
    return dc<<"YTime(invalid)";
  CString szMilliseconds; szMilliseconds.Format(_T(".%3.3d"),time.GetMilliseconds());
  dc<<_T("YTime(")<<time.Format(YTIME_DUMP_FORMAT)<<szMilliseconds;//<<")";
  dc<<"  GMT: "<<time.FormatGmt(YTIME_DUMP_FORMAT)<<szMilliseconds<<")";
  return dc;
}
inline CDumpContext& AFXAPI   operator<<( CDumpContext& dc, YTimeSpan ts )
{
  CString sz; sz.Format(_T("YTimeSpan(%ld days, %d hours, %d minutes, %d seconds, %d milliseconds)"),
    ts.GetDays(),
    ts.GetHours(), 
    ts.GetMinutes(), 
    ts.GetSeconds(), 
    ts.GetMilliseconds());
  return dc<<sz;
}

#if _MSC_VER < 1400
inline CArchive& AFXAPI       operator<<( CArchive& ar, YTIME t)
  { return ar<<((DWORD*)&t)[0]<<((DWORD*)&t)[1]; }
inline CArchive& AFXAPI       operator>>( CArchive& ar, YTIME& t)
  { return ar>>((DWORD*)&t)[0]>>((DWORD*)&t)[1]; }
#endif

inline CArchive& AFXAPI       operator<<( CArchive& ar, YTime t )
  { return ar<<((DWORD*)&t)[0]<<((DWORD*)&t)[1]; }
inline CArchive& AFXAPI       operator>>( CArchive& ar, YTime& t )
  { return ar>>((DWORD*)&t)[0]>>((DWORD*)&t)[1]; }
inline CArchive& AFXAPI       operator<<( CArchive& ar, YTimeSpan t )
  { return ar<<((DWORD*)&t)[0]<<((DWORD*)&t)[1]; }
inline CArchive& AFXAPI       operator>>( CArchive& ar, YTimeSpan& t )
  { return ar>>((DWORD*)&t)[0]>>((DWORD*)&t)[1]; }


//// Extensions ////////////////////////////////////////////////////////////////////

inline int YTimeIsIntervalsOverlaped(YTime tStart1, YTime tStop1, YTime tStart2, YTime tStop2) {
  //1: --------+
  //2:           +--------
  if(!tStop1.IsInvalid() && !tStart2.IsInvalid() && tStop1<tStart2) return 0;// non overalpped
  //1:           +--------
  //2: --------+
  if(!tStop2.IsInvalid() && !tStart1.IsInvalid() && tStop2<tStart1) return 0;// non overalpped
  //1:         +--------     -------+
  //2: --------+                    +-------
  if(tStop1==tStart2 || tStop2==tStart1)          return -1;//touch
  return 1;// overalpped
}
inline int YTimeIsInInterval(YTime tPoint, YTime tStart, YTime tStop) {
  //I: --------+
  //P:           +
  if(!tStop.IsInvalid() && tStop<tPoint)       return 0;// non overalpped
  //I:           +--------
  //P:         +
  if(!tStart.IsInvalid() && tPoint<tStart)     return 0;// non overalpped
  //I:         +--------     -------+
  //P:         +                    +       
  if(tStart==tPoint || tStop==tPoint) return -1;//touch
  return 1;// overalpped
}


#endif//__cplusplus
////////////////////////////////////////////////////////////////////////////////////

#endif//__yTIME_H
#pragma once
