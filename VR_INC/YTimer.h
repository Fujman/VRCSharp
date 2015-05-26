#ifndef __YTIMER_H
#define __YTIMER_H
#include "YTime.h"

////////////////////////////////////////////////////////////////

#ifndef __YTIME_DEFINED
#define __YTIME_DEFINED
typedef __int64 YTIME;
#endif//__YTIME_DEFINED

class YTimerBase;
class     YTimer;     // ::GetSystemTimeAsFileTime() based, forward only!
class     YCpuTimer;  // ::QueryPerformanceCounter() based, now for debug YTimer used
class     YOsTimer;   // ::GetProcessTimes() based

#ifdef  __cplusplus
////////////////////////////////////////////////////////////////
// YTimerBase
class YTimerBase
{
public: //OS system time operations
  static YTIME GetSystemTime(YTIME* pts = NULL); //forward only!
  static YTIME GetSystemSpan(YTIME ts);
public: //processor time operations
  static YTIME GetProcessorTime(YTIME* pts = NULL);
  static YTIME GetProcessorSpan(YTIME ts);
public: //process time operations
  enum { USER=2, KERNEL=1 };
  static YTIME GetProcessTime(YTIME* pts = NULL, int nFlags=0); //user time default
  static YTIME GetProcessSpan(YTIME  ts, int nFlags=0);
  static YTIME DumpProcessTime(YTIME* pts, LPCSTR  szFormat, int nFlags=0); //see YTimeSpan::Format()
  static YTIME DumpProcessTime(YTIME* pts, LPCWSTR szFormat, int nFlags=0); //see YTimeSpan::Format()
public:
  static unsigned GetRandomSeed();
};

////////////////////////////////////////////////////////////////
// YTimer
class YTimer: public YTime, public YTimerBase  //may be paused
{
public: //system time operations

  static YTimeSpan GetCurrentSpan() // YTime::GetCurrentTime() substitution for the debug purposes only
    { YTIME t = GetSystemTime(); return t; }

  YTimer()//system time
    : YTime( YTIME(GetCurrentSpan()) ) {}

  void Reset()
    { safe_put(YTIME(GetCurrentSpan()), &m_data); }

  YTimeSpan GetSpan(BOOL bReset=TRUE)
  {
    YTimeSpan t  = GetCurrentSpan();
    YTimeSpan t0 = safe_get(&m_data);
    if(bReset)
      safe_put( YTIME( t ), &m_data);
    return t-t0;
  }

  BOOL IsExpired(YTimeSpan ts, ULONG msSleep=INFINITE)
  { 
    BOOL bExpired = (GetCurrentSpan() - YTimeSpan( safe_get(&m_data) )) >= ts; 
    if(!bExpired && msSleep!=INFINITE) 
      ::Sleep(msSleep); 
    return bExpired;
  }

  BOOL IsExpired(ULONG ms, ULONG msSleep=INFINITE)//ms
  { 
    return IsExpired(YTimeSpan(YTIME(ms)*YTIME_1MS), msSleep);
  }

  #ifdef UNICODE
    YTIME DumpTime(BOOL bReset=TRUE, LPCWSTR szFormat = L"%X\r\n");
    YTIME DumpTime(BOOL bReset     , LPCSTR  szFormat            );
  #else
    YTIME DumpTime(BOOL bReset     , LPCWSTR szFormat            );
    YTIME DumpTime(BOOL bReset=TRUE, LPCSTR  szFormat =  "%X\r\n");
  #endif
};

////////////////////////////////////////////////////////////////
// YCpuTimer
class YCpuTimer: public YTimeSpan, public YTimerBase //always run forward
{
public: //processor time operations

  static YTimeSpan GetCurrentSpan() // YTime::GetCurrentTime() substitution for the timer purposes only
    { YTIME t = GetProcessorTime(); return ( t ? t : GetSystemTime() ); }

  YCpuTimer()//system time
    : YTimeSpan( GetCurrentSpan() ) {}

  void Reset()
    { safe_put( GetCurrentSpan(), &m_timeSpan ); }

  YTimeSpan GetSpan(BOOL bReset=TRUE)
  {
    YTimeSpan t = GetCurrentSpan();
    YTimeSpan t0 = safe_get(&m_timeSpan);
    if(bReset)
      safe_put( t, &m_timeSpan);
    return t-t0;
  }

  void Invalidate() //AY 25.08.2010
    { safe_put(YTIME_INVALID, &m_timeSpan); }

  #ifdef UNICODE
    YTIME DumpTime(BOOL bReset=TRUE, LPCWSTR szFormat = L"%X\r\n");
    YTIME DumpTime(BOOL bReset     , LPCSTR  szFormat            );
  #else
    YTIME DumpTime(BOOL bReset     , LPCWSTR szFormat            );
    YTIME DumpTime(BOOL bReset=TRUE, LPCSTR  szFormat =  "%X\r\n");
  #endif
};

////////////////////////////////////////////////////////////////
// YOsTimer
class YOsTimer: public YTimeSpan, public YTimerBase //always run forward
{
  int m_nFlags;
public: //process time operations

//enum { USER=2, KERNEL=1 }; //inherited
  static YTimeSpan GetCurrentSpan(int nFlags=2) // YTime::GetCurrentTime() substitution for the timer purposes only (math calculations oriented)
    { YTIME t = GetProcessTime(NULL, nFlags); return ( t ? t : GetSystemTime() ); }

  YOsTimer(int nFlags=0)//process time
    : YTimeSpan( GetCurrentSpan(nFlags) ) { m_nFlags = nFlags; }

  void Reset()
    { safe_put( GetCurrentSpan(m_nFlags), &m_timeSpan); }

  YTimeSpan GetSpan(BOOL bReset=TRUE)
  {
    YTimeSpan t = GetCurrentSpan(m_nFlags);
    YTimeSpan t0 = safe_get(&m_timeSpan);
    if(bReset)
      safe_put( t, &m_timeSpan);
    return t-t0;
  }

  void Invalidate() //AY 31.08.2010
    { safe_put(YTIME_INVALID, &m_timeSpan); }

  #ifdef UNICODE
    YTIME DumpTime(BOOL bReset=TRUE, LPCWSTR szFormat = L"%X\r\n");
    YTIME DumpTime(BOOL bReset     , LPCSTR  szFormat            );
  #else
    YTIME DumpTime(BOOL bReset     , LPCWSTR szFormat            );
    YTIME DumpTime(BOOL bReset=TRUE, LPCSTR  szFormat =  "%X\r\n");
  #endif
};

/* Example1 (process timing):

  YTIME ts = YTimer::GetProcessTime();//process user time by default
    //...
  YTimer::DumpProcessTime(&ts,"Total %X\r\n");


   Example2 (system timing):

  YTimer tm;
    //...
  tm.DumpTime("Total %X\r\n");



  Example3: 
    With YTime:
      YTime t = YTime::GetCurrentTime();
      ...
      YTimeSpan ts = YTime::GetCurrentTime() - t;

    With YTimer 1:
      YTimeSpan t = YTimer::GetCurrentSpan();
      ...
      YTimeSpan ts = YTimer::GetCurrentTime() - t;

    With YTimer 2:
      YTime t = YTimer();
      ...
      YTimeSpan ts = YTimer() - t;

*/

#endif//__cplusplus
//////////////////////////////////////////////////////
// C support
#ifdef  __cplusplus
extern "C" {
#endif//__cplusplus

YTIME  YOsTimer__get_span();
void   YOsTimer__dump_time(YTIME ts, LPCSTR szFormat/*="%X\r\n"*/);

#ifdef  __cplusplus
}
#endif//__cplusplus

#endif//__YTIMER_H
#pragma once


//history:

// AY 31.08.2010 add multithread support