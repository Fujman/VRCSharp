#ifndef __YHASPTIME_H
#define __YHASPTIME_H
#include "YTime.h"
#include "YHaspData.h"

//
//#define YTIME_EMULATE_TIMEHASP
//

#ifdef  YTIME_USE_TIMEHASP
#ifndef YHASP_USE_TIMEHASP
#define YHASP_USE_TIMEHASP
#endif
#endif

#ifndef YHASP_DUMMY_LEVEL
#define YHASP_DUMMY_LEVEL 2
#endif

// C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus

////////////////////////////////////////////////////////////////////////////////////
// YHaspTime

class YHaspTime: public YTime
{
public:                 YHaspTime(BOOL bReadHasp=FALSE);
                        YHaspTime(const YHaspTime& yht);
  static YHaspTime      GetInitTime();//hasp init time (CTime precision)
  static YTime          GetBootTime();//OS boot time (CTime precision)
  static YTIME          GetTicsFreq();
  static YTimeSpan      GetHaspDiff();//momentary system_time - hasp_time

  static BOOL           CheckDate();

  static YTimeSpan      CheckDrift(BOOL bQuery=FALSE);//-1 - auto query
  static YTimeSpan      ResetDrift(BOOL bQuery=FALSE);//-1 - auto query
  static YTimeSpan      GetHaspDrift();//summary  system_time - system_time'

  static int            InitHasp();
  static BOOL           IsEmulated();
  static int            TermHasp();

  static BOOL           LockHasp(DWORD dwTimeout=INFINITE);
  static BOOL           UnlockHasp();

  static void           Statistics(BOOL bReset=FALSE);

  static volatile ULONG s_retries;
//helpers
  static YTIME          _CalcDrift();

  static __inline YTime GetEmulatedTime() { return YTime::GetCurrentTime(); }
};

////////////////////////////////////////////////////////////////////////////////////
// YHaspDate

/*
  TIME HASP FAS SYSTEM expire date format  6543210321043210
                                           YYYYYYYMMMMDDDDD
      0021 [21 00]  =        01.01.2000  0b0000000000100001
  7:  151F [1F 15]  = 5407   31.08.2010  0b0001010100011111
  8:  1521 [21 15]  = 5409   01.09.2010  0b0001010100100001
*/

class YHaspDate //01.01.2000 .. 31.12.2127
{
public:
  enum          { BASE=7304+1 };//days //YTIME BASE=6310656000000000i64==(YTime(1999,12,31,00,00,00,000)-YTime(1980,01,01,00,00,00,000))

                YHaspDate();//non-initialized

                YHaspDate(const YHaspDate&);
  YHaspDate&    operator=(const YHaspDate&);

                YHaspDate(YTime t);
                operator YTime() const;

                YHaspDate(WORD  t);

  int           GetYear() const;
  int           GetMonth() const;
  int           GetDay() const;

  WORD          m_wDate;
};

inline YHaspDate::YHaspDate()
  { }
inline YHaspDate& YHaspDate::operator=(const YHaspDate& x)
  { m_wDate = x.m_wDate; return *this; }
inline YHaspDate::YHaspDate(const YHaspDate& x)
  { operator=(x); }
inline YHaspDate::YHaspDate(YTime t)
  { m_wDate = 0; WORD wTime; (t-YTimeSpan(BASE,00,00,00,000)).GetAsDosDateTime(&m_wDate,&wTime); }
inline YHaspDate::operator YTime() const
  { WORD wTime=0; return YTime((void*)0,m_wDate,wTime,0)+YTimeSpan(BASE,00,00,00,000); }
inline YHaspDate::YHaspDate(WORD x)
  { m_wDate = x; }

inline int YHaspDate::GetYear() const 
  { return 2000+int(unsigned(m_wDate>>9)); }
inline int YHaspDate::GetMonth() const 
  { return int(unsigned(m_wDate>>5)&0x0F); }
inline int YHaspDate::GetDay() const 
  { return int(unsigned(m_wDate)&0x1F); }

#endif//__cplusplus

// C section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

#if defined(YHASP_USE_TIMEHASP) && !defined(YTIME_EMULATE_TIMEHASP)

#pragma warning(disable: 4005)

#undef   YHaspTime__QueryHaspDateTime
#undef   YHaspTime__QueryHaspTime    
#undef   YHaspTime__QueryHaspDate    
#undef   YHaspTime__WriteHaspDateTime
#define  YHaspTime__QueryHaspDateTime  _YHaspTime__QueryHaspDateTime
#define  YHaspTime__QueryHaspTime      _YHaspTime__QueryHaspTime    
#define  YHaspTime__QueryHaspDate      _YHaspTime__QueryHaspDate    
#define  YHaspTime__WriteHaspDateTime  _YHaspTime__WriteHaspDateTime
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_VENDOR_CODE
#define  HASP_VENDOR_CODE "aLG7D50+NqcOrGShjsx5yeNfCxXgR9vtoQtq3XfWcF9Xfj0Zotqe4sSBpyT+NzyF5UvErIWF9Uza5AHwp7FcMSDqwX/QW/4Iq4RsbE+q34z9Iv9pTPmFw6iMg8oTscv1UUNxtRKsuXi8V6bvfz8ZMDB7Hxyr0xPktHGcXDMWcvCxzz/OW2Yl4jvi+w5fPKRiVpeoXZ2rLkfMWlxcswhnR+QdPg+F2k04n0UjCTWTVOlGjKxbTAYLOXg+zcWHEYfX3xgEtIUjLNb84+y4s6kZsgkKvVvF6PMwgK8w/85UdAConQbWczFjFGWzJ+5r9ZPYDGSAL8/c6fADL8AgAgPqRee9JMA2yftoVwMrNcQFW910TaIfjyN2JVjedtrkYIBPYNb+x07ABZyjj1F/Q1BjIGltW7c2Hf2RuU9V9dDmOdOjCl6hNUVe8NeacAAADJACppa1JpNn8tA2RNEiPxQ/dv2YE/LpWfTZsgAI3xbrJfaQJCcTXL5AdNEnLEhFmo2LGKdZjsw9tEFTmj5SD+3/WETAK5vemZKRMM+2MFHqnz1IdoGTivcHBUg1DWX9YwEx+lrfPC+h9VzohwQhGd1SQpzOoqTw2mbcCQVzcxgCcQ21ImWzxYMZnPTtanymI93Ral+MNlOUgPVit/4DMJAzSNL9cgQAjy1PIj1NPE6K1zhfeGVC/KpHTrHp99+OfKdSMJLLflUboMWBl0gsfk+sUVs5OJ8SGp4xvVdkcICYXJUF6om6bk9nq3akbVTIDntdnpYYaRqhCFlsxVsSToJwLN8LzYjLjmHpNVV4GoA57Cwu0/3LznRqFdBBmBBtE5Vz6LKHL6rvLwjGd9tKSCdCAkzn4rPWMHio8nMzsEVdIUbV7KNz2o8KFvt8i0WXGB1yVLnRBULO4zV0ZdSD7NP4ZgUaPfthF4h1nNmHd135dDI="
#define  HASP_PASS1  14291
#define  HASP_PASS2  13413
#include "YHaspTime.inl"

#undef   YHaspTime__QueryHaspDateTime
#undef   YHaspTime__QueryHaspTime    
#undef   YHaspTime__QueryHaspDate    
#undef   YHaspTime__WriteHaspDateTime
#define  YHaspTime__QueryHaspDateTime  YHaspTime__QueryHaspDateTime_
#define  YHaspTime__QueryHaspTime      YHaspTime__QueryHaspTime_
#define  YHaspTime__QueryHaspDate      YHaspTime__QueryHaspDate_
#define  YHaspTime__WriteHaspDateTime  YHaspTime__WriteHaspDateTime_
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_VENDOR_CODE
#define  HASP_VENDOR_CODE "bLG7D50+MqcNrGShjsx5yeNdCxOgR9vtoQtq3XfWcF9Xfj0Zotqe4sSBpyT+NzyF5UvErIWF9Uza5AHwp7FcMSDqwX/QW/4Iq4RsbE+q34z9Iv9pTPmFw6iMg8oTscv1UUNxtRKsuXi8V6bvfz8ZMDB7Hxyr0xPktHGcXDMWcvCxzz/OW2Yl4jvi+w5fPKRiVpeoXZ2rLkfMWlxcswhnR+QdPg+F2k04n0UjCTWTVOlGjKxbTAYLOXg+zcWHEYfX3xgEtIUjLNb84+y4s6kZsgkKvVvF6PMwgK8w/85UdAConQbWczFjFGWzJ+5r9ZPYDGSAL8/c6fADL8AgAgPqRee9JMA2yftoVwMrNcQFW910TaIfjyN2JVjedtrkYIBPYNb+x07ABZyjj1F/Q1BjIGltW7c2Hf2RuU9V9dDmOdOjCl6hNUVe8NeacAAADJACppa1JpNn8tA2RNEiPxQ/dv2YE/LpWfTZsgAI3xbrJfaQJCcTXL5AdNEnLEhFmo2LGKdZjsw9tEFTmj5SD+3/WETAK5vemZKRMM+2MFHqnz1IdoGTivcHBUg1DWX9YwEx+lrfPC+h9VzohwQhGd1SQpzOoqTw2mbcCQVzcxgCcQ21ImWzxYMZnPTtanymI93Ral+MNlOUgPVit/4DMJAzSNL9cgQAjy1PIj1NPE6K1zhfeGVC/KpHTrHp99+OfKdSMJLLflUboMWBl0gsfk+sUVs5OJ8SGp4xvVdkcICYXJUF6om6bk9nq3akbVTIDntdnpYYaRqhCFlsxVsSToJwLN8LzYjLjmHpNVV4GoA57Cwu0/3LznRqFdBBmBBtE5Vz6LKHL6rvLwjGd9tKSCdCAkzn4rPWMHio8nMzsEVdIUbV7KNz2o8KFvt8i0WXGB1yVMnRBULO4zV0ZdSD7NP4ZgUaPfthF4x1nNmHd135dDI="
#define  HASP_PASS1  39767
#define  HASP_PASS2  11430
#include "YHaspTime.inl"

#undef   YHaspTime__QueryHaspDateTime
#undef   YHaspTime__QueryHaspTime    
#undef   YHaspTime__QueryHaspDate    
#undef   YHaspTime__WriteHaspDateTime
#define  YHaspTime__QueryHaspDateTime  __YHaspTime__QueryHaspDateTime
#define  YHaspTime__QueryHaspTime      __YHaspTime__QueryHaspTime    
#define  YHaspTime__QueryHaspDate      __YHaspTime__QueryHaspDate    
#define  YHaspTime__WriteHaspDateTime  __YHaspTime__WriteHaspDateTime
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_VENDOR_CODE
#define  HASP_VENDOR_CODE "eLD7D50+MqcOrGShjsx5ygNfCxOgR9vtoQtq4XfWcF9Xfj0Zotqe7sSBpyT+NzyF5UvErIWF9Uza5AHwp7FcMSDqwX/QW/4Iq4RsbE+q34z9Iv9pTPmFw6iMg8oTscv1UUNxtRKsuXi8V6bvfz8ZMDB7Hxyr0xPktHGcXDMWcvCxzz/OW2Yl4jvi+w5fPKRiVpeoXZ2rLkfMWlxcswhnR+QdPg+F2k04n0UjCTWTVOlGjKxbTAYLOXg+zcWHEYfX3xgEtIUjLNb84+y4s6kZsgkKvVvF6PMwgK8w/85UdAConQbWczFjFGWzJ+5r9ZPYDGSAL8/c6fADL8AgAgPqRee9JMA2yftoVwMrNcQFW910TaIfjyN2JVjedtrkYIBPYNb+x07ABZyjj1F/Q1BjIGltW7c2Hf2RuU9V9dDmOdOjCl6hNUVe8NeacAAADJACppa1JpNn8tA2RNEiPxQ/dv2YE/LpWfTZsgAI3xbrJfaQJCcTXL5AdNEnLEhFmo2LGKdZjsw9tEFTmj5SD+3/WETAK5vemZKRMM+2MFHqnz1IdoGTivcHBUg1DWX9YwEx+lrfPC+h9VzohwQhGd1SQpzOoqTw2mbcCQVzcxgCcQ21ImWzxYMZnPTtanymI93Ral+MNlOUgPVit/4DMJAzSNL9cgQAjy1PIj1NPE6K1zhfeGVC/KpHTrHp99+OfKdSMJLLflUboMWBl0gsfk+sUVs5OJ8SGp4xvVdkcICYXJUF6om6bk9nq3akbVTIDntdnpYYaRqhCFlsxVsSToJwLN8LzYjLjmHpNVV4GoA57Cwu0/3LznRqFdBBmBBtE5Vz6LKHL6rvLwjGd9tKSCdCAkzn4rPWMHio8nMzsEVdIUbV7KNz2o8KFvt8i0WXGB1yVLnRBULO4zV0ZdSD7NP4ZgUaPfthF4h1nNmHd135dDI="
#define  HASP_PASS1   7634
#define  HASP_PASS2  18498
#include "YHaspTime.inl"

#undef   YHaspTime__QueryHaspDateTime
#undef   YHaspTime__QueryHaspTime    
#undef   YHaspTime__QueryHaspDate    
#undef   YHaspTime__WriteHaspDateTime
#define  YHaspTime__QueryHaspDateTime  YHaspTime__QueryHaspDateTime__
#define  YHaspTime__QueryHaspTime      YHaspTime__QueryHaspTime__
#define  YHaspTime__QueryHaspDate      YHaspTime__QueryHaspDate__
#define  YHaspTime__WriteHaspDateTime  YHaspTime__WriteHaspDateTime__
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_VENDOR_CODE
#include "YHaspPass.h" //TRUE
#include "YHaspTime.inl"

#undef   YHaspTime__QueryHaspDateTime
#undef   YHaspTime__QueryHaspTime    
#undef   YHaspTime__QueryHaspDate    
#undef   YHaspTime__WriteHaspDateTime
#define  YHaspTime__QueryHaspDateTime  _YHaspTime__QueryHaspDateTime_
#define  YHaspTime__QueryHaspTime      _YHaspTime__QueryHaspTime_
#define  YHaspTime__QueryHaspDate      _YHaspTime__QueryHaspDate_
#define  YHaspTime__WriteHaspDateTime  _YHaspTime__WriteHaspDateTime_
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_VENDOR_CODE
#define  HASP_VENDOR_CODE "bLG7D50+MqcOrGShjsx5y7NfCxOgR9vtoQrq3XfWcF9Xfj0Zotqe4sSBbxT+NzyF5UvErIWF9Uza5AHwp7FcMSDqwX/QW/4Iq4RsbE+q34z9Iv9pTPmFw6iMg8oTscv1UUNxtRKsuXi8V6bvfz8ZMDB7Hxyr0xPktHGcXDMWcvCxzz/OW2Yl4jvi+w5fPKRiVpeoXZ2rLkfMWlxcswhnR+QdPg+F2k04n0UjCTWTVOlGjKxbTAYLOXg+zcWHEYfX3xgEtIUjLNb84+y4s6kZsgkKvVvF6PMwgK8w/85UdAConQbWczFjFGWzJ+5r9ZPYDGSAL8/c6fADL8AgAgPqRee9JMA2yftoVwMrNcQFW910TaIfjyN2JVjedtrkYIBPYNb+x07ABZyjj1F/Q1BjIGltW7c2Hf2RuU9V9dDmOdOjCl6hNUVe8NeacAAADJACppa1JpNn8tA2RNEiPxQ/dv2YE/LpWfTZsgAI3xbrJfaQJCcTXL5AdNEnLEhFmo2LGKdZjsw9tEFTmj5SD+3/WETAK5vemZKRMM+2MFHqnz1IdoGTivcHBUg1DWX9YwEx+lrfPC+h9VzohwQhGd1SQpzOoqTw2mbcCQVzcxgCcQ21ImWzxYMZnPTtanymI93Ral+MNlOUgPVit/4DMJAzSNL9cgQAjy1PIj1NPE6K1zhfeGVC/KpHTrHp99+OfKdSMJLLflUboMWBl0gsfk+sUVs5OJ8SGp4xvVdkcICYXJUF6om6bk9nq3akbVTIDntdnpYYaRqhCFlsxVsSToJwLN8LzYjLjmHpNVV4GoA57Cwu0/3LznRqFdBBmBBtE5Vz6LKHL6rvLwjGd9tKSCdCAkzn4rPWMHio8nMzsEVdIUbV7KNz2o8KFvt8i0WXGB1yVLnRBULO4zV0ZdSD7NP4ZgUaPfthF4h1nNmHd135dDI="
#define  HASP_PASS1  12956
#define  HASP_PASS2  17458
#include "YHaspTime.inl"

//restore defaults
#undef   YHaspTime__QueryHaspDateTime
#undef   YHaspTime__QueryHaspTime    
#undef   YHaspTime__QueryHaspDate    
#undef   YHaspTime__WriteHaspDateTime
#define  YHaspTime__QueryHaspDateTime  YHaspTime__QueryHaspDateTime__
#define  YHaspTime__QueryHaspTime      YHaspTime__QueryHaspTime__
#define  YHaspTime__QueryHaspDate      YHaspTime__QueryHaspDate__
#define  YHaspTime__WriteHaspDateTime  YHaspTime__WriteHaspDateTime__
#include "YHaspPass.h"

#pragma warning(default: 4005)

#if YHASP_DUMMY_LEVEL<1
#define  _YHaspTime__QueryHaspDateTime()    YTIME(0)
#define  _YHaspTime__QueryHaspTime()        YTIME(0)
#define  _YHaspTime__QueryHaspDate()        YTIME(0)
#define  _YHaspTime__WriteHaspDateTime(t,b) (0)
#endif
#if YHASP_DUMMY_LEVEL<2
#define  YHaspTime__QueryHaspDateTime_()    YTIME(0)
#define  YHaspTime__QueryHaspTime_()        YTIME(0)
#define  YHaspTime__QueryHaspDate_()        YTIME(0)
#define  YHaspTime__WriteHaspDateTime_(t,b) (0)
#endif
#if YHASP_DUMMY_LEVEL<3
#define  __YHaspTime__QueryHaspDateTime()    YTIME(0)
#define  __YHaspTime__QueryHaspTime()        YTIME(0)
#define  __YHaspTime__QueryHaspDate()        YTIME(0)
#define  __YHaspTime__WriteHaspDateTime(t,b) (0)
#endif
#if YHASP_DUMMY_LEVEL<4
#define  _YHaspTime__QueryHaspDateTime_()    YTIME(0)
#define  _YHaspTime__QueryHaspTime_()        YTIME(0)
#define  _YHaspTime__QueryHaspDate_()        YTIME(0)
#define  _YHaspTime__WriteHaspDateTime_(t,b) (0)
#endif

#endif

#if (defined(YHASP_USE_TIMEHASP) && defined(YTIME_EMULATE_TIMEHASP)) || !defined(YHASP_USE_TIMEHASP)
extern "C" __inline YTIME YHaspTime__QueryHaspDateTime()//date+time
{
  YHasp__LockHasp();
  YHasp__UnlockHasp();
  return YHaspTime::GetEmulatedTime();
}
extern "C" __inline YTIME YHaspTime__QueryHaspTime()//time
{
  YHasp__LockHasp();
  YHasp__UnlockHasp();
  return YHaspTime::GetEmulatedTime().GetPureTime();
}
extern "C" __inline YTIME YHaspTime__QueryHaspDate()//date
{
  YHasp__LockHasp();
  YHasp__UnlockHasp();
  return YHaspTime::GetEmulatedTime().GetPureDate(); //emulation
}
#endif


#endif//__YHASPTIME_H
#pragma once
