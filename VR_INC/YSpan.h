#ifndef __ySPAN_H
#define __ySPAN_H

#include "YTimeBase.h"

// C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus

////  manual template based virtualization  ////

inline YTIME YSpan__GetTime(const _YTIME& t)
  { return t.m_time; }
inline YTIME YSpan__GetTime(const _YTIMESPAN& t)
  { return t.m_tics+YTIME_1601_01_01; }
inline YTIME YSpan__GetTime(const _YSPAN& t)
  { return t.m_time; }
inline YTIME YSpan__GetTime(const _YREALSPAN& t)
  { return t.m_time; }
inline YTIME YSpan__GetTime(const _YREALTIME& t)
  { return t.m_time; }

inline YTIME YSpan__GetTics(const _YTIME& t)
  { return t.m_time-YTIME_1601_01_01; }
inline YTIME YSpan__GetTics(const _YTIMESPAN& t)
  { return t.m_tics; }
inline YTIME YSpan__GetTics(const _YSPAN& t)
  { return t.m_tics; }
inline YTIME YSpan__GetTics(const _YREALSPAN& t)
  { return t.m_tics; }
inline YTIME YSpan__GetTics(const _YREALTIME& t)//TO DO? return t.m_tics;
  { return t.m_tics-t.m_tBaseTics; }

inline YTIME YSpan__GetSpan(const _YTIME& t)
  { return t.m_time-YTIME_1601_01_01; }
inline YTIME YSpan__GetSpan(const _YTIMESPAN& t)
  { return t.m_tics; }
inline YTIME YSpan__GetSpan(const _YSPAN& t)
  { return t.m_tics; }
inline YTIME YSpan__GetSpan(const _YREALSPAN& t)//=== m_tics*RATE, RATE=(t.m_time-t.m_tBaseTime)/m_tics
  { return t.m_time-t.m_tBaseTime; }  
inline YTIME YSpan__GetSpan(const _YREALTIME& t)//=== m_tics*RATE, RATE=const
  { return YRealTime::TicsToTime(&t.m_info,t.m_tics); }

inline YTIME YSpan__GetBase(const _YTIME& t)
  { return YTIME_1601_01_01; }
inline YTIME YSpan__GetBase(const _YTIMESPAN& t)
  { return YTIME_1601_01_01; }
inline YTIME YSpan__GetBase(const _YSPAN& t)
  { return t.m_time-t.m_tics; }
inline YTIME YSpan__GetBase(const _YREALSPAN& t)
  { return t.m_tBaseTime; }
inline YTIME YSpan__GetBase(const _YREALTIME& t)
  { return YRealTime::DoGetBaseTime(t); }

#if 0
inline YTIME YSpan__GetRate(const _YTIME& t)
  { return YTIME_100NS; }
inline YTIME YSpan__GetRate(const _YTIMESPAN& t)
  { return YTIME_100NS; }
inline YTIME YSpan__GetRate(const _YSPAN& t)
  { return YTIME_100NS; }
inline YTIME YSpan__GetRate(const _YREALSPAN& t)
  { return t.m_tics==0?0:(t.m_time-t.m_tBaseTime)/t.m_tics; }
inline YTIME YSpan__GetRate(const _YREALTIME& t)
  { return YTIME_100NS; }
#endif

template <class YSPANBASE>
class YSpan_: public YSPANBASE
{
#if 0 //////////////////////////////////////////////////////////////////////////////
public://YTime
  BOOL                          operator ==(YTIME tics) const { return m_data==tics; }

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
public://YTimeSpan
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
#endif /////////////////////////////////////////////////////////////////////////////
//construction/destruction
                                YSpan_()
                                  {}
                                YSpan_(const YSpan_<YSPANBASE>& t)
                                  { operator=(t); }
                                YSpan_(YTIME tTime, YTIME nTics, const YSpan_<YSPANBASE>* p=NULL);
  YSpan_<YSPANBASE>&            operator=(const YSpan_<YSPANBASE>&);

                                operator const YSPANBASE&();
                                operator YSPANBASE&() const;
//attributes
  YTIME                         GetTime() const                    //YTime
                                  { return YSpan__GetTime(*this); }
  YTIME                         GetSpan() const                    //YTimeSpan
                                  { return YSpan__GetSpan(*this); }
  YTIME                         GetTics() const                    //int64
                                  { return YSpan__GetTics(*this); }
  YTIME                         GetBase() const                    //YTime
                                  { return YSpan__GetBase(*this); }
  YTIME                         GetRate() const                    //Hz*1000
                                  { return YSpan__GetSpan(*this)?0:(YSpan__GetTics(*this)*1000*1000*1000)/YSpan__GetSpan(*this).GetTotalMicroseconds(); }
};

class YTime2 : protected _YTIME
{
//YTIME m_time;
  typedef _YTIME YParent;
  friend YTIME YSpan__GetTime(const YParent&);
  friend YTIME YSpan__GetSpan(const YParent&);
  friend YTIME YSpan__GetTics(const YParent&);
  friend YTIME YSpan__GetBase(const YParent&);
}

class YTimeSpan2: public _YTIMESPAN
{
//YTIME m_tics;
  typedef _YTIMESPAN YParent;
  friend YTIME YSpan__GetTime(const YParent&);
  friend YTIME YSpan__GetSpan(const YParent&);
  friend YTIME YSpan__GetTics(const YParent&);
  friend YTIME YSpan__GetBase(const YParent&);
};

class YRealSpan2 : public YREALSPAN
{
//YTIME                         m_time;
//YTIME                         m_tics;
//YTIME                         m_tBaseTime;
//YTIME                         m_nBaseTics;
//YTIMEPROVIDER                 m_info;
  typedef _YTIMESPAN YParent;
  friend YTIME YSpan__GetTime(const YParent&);
  friend YTIME YSpan__GetSpan(const YParent&);
  friend YTIME YSpan__GetTics(const YParent&);
  friend YTIME YSpan__GetBase(const YParent&);
};

class YRealTime2 : public YREALTIME
{
//YTIME                         m_time;
//YTIME                         m_tics;
//YTIME                         m_tBaseTime;
//YTIME                         m_nBaseTics;
//YREALTIMEPROVIDERINFO         m_info;
  typedef _YREALTIME YParent;
  friend YTIME YSpan__GetTime(const YParent&);
  friend YTIME YSpan__GetSpan(const YParent&);
  friend YTIME YSpan__GetTics(const YParent&);
  friend YTIME YSpan__GetBase(const YParent&);
};

typedef YSpan_<_YTIME>          YSpanTime;
typedef YSpan_<_YTIMESPAN>      YSpanSpan;
typedef YSpan_<_YSPAN>          YSpan;
typedef YSpan_<_YTICS>          YSpanTics;
//pedef YSpan_<YTime>           YSpanTime;
//pedef YSpan_<YTimeSpan>       YSpanSpan;
//pedef YSpan_<YRealTimer>      YSpanRealTimer;
//pedef YSpan_<YRealTime>       YSpanRealTime;

#define TEMPLATE_CREF  template <class YSPANBASE> inline const YSpan_<YSPANBASE>& YSpan_<YSPANBASE>
#define TEMPLATE__REF  template <class YSPANBASE> inline YSpan_<YSPANBASE>& YSpan_<YSPANBASE>
#define TEMPLATE_SPAN  template <class YSPANBASE> inline YSpan_<YSPANBASE>
#define SPAN           YSpan_<YSPANBASE>

#define TEMPLATE_TYPE  template <class YSPANBASE, class YTIMESPAN> inline  YSpan_<YSPANBASE>
#define TEMPLATE       template <class YSPANBASE, class YTIMESPAN> inline

TEMPLATE_SPAN::SPAN(YTIME tTime, YTIME nTics, const SPAN* p=NULL)
  { }

TEMPLATE_SPAN::operator const YSPANBASE&()
  { return *(const YSPANBASE*)this; }

TEMPLATE_SPAN::operator YSPANBASE&() const
  { return *(YSPANBASE*)this; }

TEMPLATE__REF::operator=(const YSpan_<YSPANBASE>& t)
  { memcpy(this,&t,sizeof(t); return *this; }

//MPLATE_SPAN operator+=(const YTIMESPAN& ts)//??

TEMPLATE_TYPE operator+(const YSpanBase<YSPANBASE>& span, const YTIMESPAN& ts)
  { return YSpanBase<YSPANBASE>(GetTime(span)+GetSpan(ts),GetTics(span),&span); }

TEMPLATE_TYPE operator-(const YSpanBase<YSPANBASE>& span, const YTIMESPAN& ts)
  { return YSpanBase<YSPANBASE>(YSpan__GetTime(span)-YSpan__GetSpan(ts),YSpan__GetTics(span)-YSpan__GetTics(YSpan__GetSpan(ts)),&span); }

TEMPLATE BOOL operator==(const YSpanBase<YSPANBASE>& span, const YTIMESPAN& ts)
  { return YSpan__GetTime(span)==YSpan__GetTime(ts) && YSpan__GetSpan(span)==YSpan__GetSpan(ts); }

#undef  TEMPLATE_SPAN
#undef  TEMPLATE__REF
#undef  TEMPLATE_CREF
#undef  TEMPLATE_TYPE
#undef  TEMPLATE

#endif//__cplusplus

#endif//__ySPAN_H
#pragma once
