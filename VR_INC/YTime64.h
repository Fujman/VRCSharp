#ifndef __YTIME64_H
#define __YTIME64_H

// C section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#include "int64.h"
#include "YTime.h"

#ifndef __YTIME64_DEFINED
#define __YTIME64_DEFINED
typedef __int64 YTIME64;
#endif//__YTIME64_DEFINED

#define YTIME64_INITIAL   (                   0i64)//0x0000000000000000i64
#define YTIME64_INVALID   (-9223372036854775808i64)//0x8000000000000000i64

#define YTIME64_1CENTURY  (13553514908850585600i64)//0xBC17C20000000000i64 365*100+24 days (may be unsigned only)
#define YTIME64_1YEAR      ( 135446088646656000i64)//0x01E1338000000000i64 365 days
#define YTIME64_1MONTH     (  11132555231232000i64)//0x00100A4000000000i64 30 days
#define YTIME64_1WEEK      (   2597596220620800i64)//0x00093A8000000000i64
#define YTIME64_1DAY       (    371085174374400i64)//0x0001518000000000i64
#define YTIME64_1HOUR      (     15461882265600i64)//0x00000E1000000000i64
#define YTIME64_1MINUTE    (       257698037760i64)//0x0000003C00000000i64
#define YTIME64_1SECOND    (         4294967296i64)//0x0000000100000000i64
#define YTIME64_1MS        (            4294967i64)//0x0000000000418937i64//-6.89e-8s per 1s
#define YTIME64_1MCS       (               4295i64)//0x00000000000010C7i64//+7.61e-6s per 1s
#define YTIME64_100NS      (                429i64)//0x00000000000001ADi64//-1.16e-3s per 1s

#define YTIME64_1mS        (            4194304i64)//0x0000000000400000i64//1/1024s
#define YTIME64_1mcS       (               4096i64)//0x0000000000001000i64//1/1024/1024s


#define YTIME64_MIN       (-9223372036854775808i64)//-2147483648.0000000000s 35791394.133m 596523.235h 24855.135days 68.0963years
#define YTIME64_MAX        (9223372036854775807i64)// 2147483647.9999999998s 

// C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus

////////////////////////////////////////////////////////////////////////////////////
// YSpan64

class YSpan64
{
public:
};

class YTime64: public YSpan64
{
public:

  static inline YTIME Time64ToTime(YTIME64 tTics) //t SECONDS::(1sec/0x10000000) SECONDS = CTime(YTime)
  {
    QWORD nTics = QWORD(tTics);
    QWORD nPrec = nTics & 0xFFFFFFFF;
    QWORD nRest = (nPrec*DWORD(YTIME_1SECOND))>>32;
    QWORD nSecs = nTics >> 32;
    QWORD nTime = nSecs*DWORD(YTIME_1SECOND)+nRest;
    QWORD tTime = nTime + YTIME_CTIME_BASE;
    return YTIME(tTime);
  }

  static inline YTIME64 TimeToTime64(YTIME tTime) //tTime SECONDS::(1sec/0x10000000)
  {
    QWORD nTime = YTIME(tTime) - YTIME_CTIME_BASE;
    QWORD nSecs = nTime/DWORD(YTIME_1SECOND);
    QWORD nRest = nTime%DWORD(YTIME_1SECOND);
    QWORD nPrec = (nRest<<32)/DWORD(YTIME_1SECOND);
    QWORD nTics = (nSecs<<32)|nPrec;
    return YTIME(nTics);
  }
};

#endif//__cplusplus
////////////////////////////////////////////////////////////////////////////////////

#endif//__YTIME64_H
#pragma once
