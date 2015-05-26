#ifndef __XCTIME_H
#define __XCTIME_H
#include "time32.h"
  inline CTime2TIME_T(CTime ct)
  {
    __TIME_T t = ct.GetTime();
      TIME_T T = TIME_T( t );
    ASSERT(__TIME_T(T)==t);
    return T;
  }

  inline CTime CTimeFromStringEx(LPCTSTR lpszTime, LPCTSTR lpszDate) {
    if(lpszTime==NULL)
      lpszTime = _T("00:00:00");
    if(lpszDate==NULL)
      lpszDate = _T("01:01:1980");
    CString szTime = lpszTime;
    CString szDate = lpszDate;
    int nHour = _ttoi(szTime.Mid(0,2));
    int nMin  = _ttoi(szTime.Mid(3,2));
    int nSec  = _ttoi(szTime.Mid(6,2));
    int nYear = _ttoi(szDate.Mid(6,4));
    int nMon  = _ttoi(szDate.Mid(3,2));
    int nDay  = _ttoi(szDate.Mid(0,4));
    if(nYear<1900)
      nYear += 2000;
    return CTime(nYear,nMon,nDay,nHour,nMin,nSec);
  }
  inline CTime CTimeFromString(LPCTSTR lpszTime, LPCTSTR lpszDate) {
    if(lpszTime==NULL)
      lpszTime = _T("00:00:00");
    if(lpszDate==NULL)
      lpszDate = _T("01:01:1980");
    CString szTime = lpszTime;
    CString szDate = lpszDate;
    int nHour = _ttoi(szTime.Mid(0,2));
    int nMin  = _ttoi(szTime.Mid(3,2));
    int nSec  = _ttoi(szTime.Mid(6,2));
    int nYear = _ttoi(szDate.Mid(6,4));
    int nMon  = _ttoi(szDate.Mid(3,2));
    int nDay  = _ttoi(szDate.Mid(0,4));
    return CTime(nYear,nMon,nDay,nHour,nMin,nSec);
  }
  inline CTime CTimeAdjustDaylightSavingError(CTime& tDate, LPCTSTR lpszDate) {
    CTime tRealDate = CTimeFromString(NULL, lpszDate);
    if(tDate!=tRealDate)
      if(tDate+CTimeSpan(60*60)==tRealDate)
        { /*ASSERT(0);*/ return tDate = tRealDate; }
    return tRealDate;
  }
  inline int CTimeIsIntervalsOverlaped(CTime tStart1, CTime tStop1, CTime tStart2, CTime tStop2) {
    //1: --------+
    //2:           +--------
    if(tStop1!=-1 && tStart2!=-1 && tStop1<tStart2) return 0;// non overalpped
    //1:           +--------
    //2: --------+
    if(tStop2!=-1 && tStart1!=-1 && tStop2<tStart1) return 0;// non overalpped
    //1:         +--------     -------+
    //2: --------+                    +-------
    if(tStop1==tStart2 || tStop2==tStart1)          return -1;//touch
    return 1;// overalpped
  }
  inline int CTimeIsInInterval(CTime tPoint, CTime tStart, CTime tStop) {
    //I: --------+
    //P:           +
    if(tStop!=-1 && tStop<tPoint)       return 0;// non overalpped
    //I:           +--------
    //P:         +
    if(tStart!=-1 && tPoint<tStart)     return 0;// non overalpped
    //I:         +--------     -------+
    //P:         +                    +
    if(tStart==tPoint || tStop==tPoint) return -1;//touch
    return 1;// overalpped
  }
#endif//__XCTIME_H
#pragma once
