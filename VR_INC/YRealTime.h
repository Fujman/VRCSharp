#ifndef __yREALTIME_H
#define __yREALTIME_H

#include "YTime.h"

////////////////////////////////////////////////////////////////////////////////////
// YRealTime // UTC, by high-resolution performance counter or by mmsystem timers

#define YREALTIME_1TIC          (YTIME_1MS)       //default resolution

// C section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#pragma pack(push,1)
typedef struct tagYREALTIMEPROVIDERINFO{//rtpi
  DWORD                         m_cbSize;         //size of struct
  DWORD                         m_iProvider;      //provider type: see YRealTime
  DWORD                         m_nFlags;         
  DWORD                         m_reserved0;      //FOR DIRECTX: Specifies the current bias, in minutes, for local time translation on this computer. The bias is the difference, in minutes, between Coordinated Universal Time (UTC) and local time. All translations between UTC and local time are based on the following formula: UTC = local time + bias
  YTIME/*YTimeSpan*/            m_tsResolution;   //duration of one tic (HIGH part: if ==0 use m_nsResolution)
  YTIME/*YTicsSpan*/            m_nsResolution;   //tics per second     (LOW  part: if ==0 use m_tsResolution)
  YTIME/*YTimeSpan*/            m_tsMinPeriod;    //min period between measurements with different results (HIGH part: if ==0 use m_nsMinPeriod)
  YTIME/*YTicsSpan*/            m_nsMinPeriod;    //min period between measurements with different results (LOW  part: if ==0 use m_tsMinPeriod)
  YTIME/*YTimeSpan*/            m_tsMaxPeriod;    //max time perion between roll-up counter
  YTIME/*YTicsSpan*/            m_nsMaxPeriod;    //max time perion between roll-up counter
  YTIME/*YTimeSpan*/            m_tsAdjustment;   //time synchronization span (HIGH part: if ==0 use m_nsAdjustment)
  YTIME/*YTicsSpan*/            m_nsAdjustment;   //time synchronization span (LOW  part: if ==0 use m_tsAdjustment)
  YTIME/*YTimeSpan*/            m_tsIncrement;    //time synchronization increment (HIGH part: if ==0 use m_nsIncrement)
  YTIME/*YTicsSpan*/            m_nsIncrement;    //time synchronization increment (LOW  part: if ==0 use m_tsIncrement)
  YTIME/*YTimeSpan*/            m_tsPrecision;    //max error per 1 year
  YTIME/*YTime*/                m_tInitTime;
  YTIME/*YTics*/                m_nInitTics;
} YREALTIMEPROVIDERINFO;

typedef struct tagYREALTIME{//rt
  YTIME                         m_time;
  YTIME                         m_tics;
  YREALTIMEPROVIDERINFO         m_info;
} YREALTIME;

#pragma pack(pop)

// C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus

////////////////////////////////////////////////////////////////////////////////////
// YRealTime // UTC, by high-resolution performance counter or by mmsystem timers
#pragma pack(push,1)
class YRealTime :               public YTime
{
public: //construction/destruction
  enum /* providers */          { DEFAULT=0, STANDARD=1, HIGHPERFORMANCE=2, MMSYSTEM=3, WINDOWS=4, DIRECTX=7, HASPTIME=8};
  enum /* flags */              { flagTimeAdjustmentDisabled =    128 };
  enum /* flags */              { flagUserTimeIsLocal        =    256 };
  //   /* flags */              { flagConverted              =    512 };//reserved for internal usage
  enum /* flags */              { flagDaylightDisabled       = 1*1024 };//AY 03.04.2007
  enum /* flags */              { flagStandardTime           = 2*1024 };//AY 03.04.2007
  enum /* flags */              { flagDaylightTime           = 4*1024 };//AY 03.04.2007
  enum /* flags */              { flagDaylightZone           = 8*1024 };//AY 03.04.2007
  enum /* flags */              { flagTimehaspUsed           =16*1024 };//AY 10.05.2007
  enum /* flags */              { flagInitialBias            =32*1024 };//AY 22.05.2007
protected:
  static YREALTIMEPROVIDERINFO* s_pDefaultProvider;
  YTIME                         m_tics;
  YREALTIMEPROVIDERINFO         m_info;
public: //construction/destruction
                                YRealTime(YTIME tTime, YTIME nTics, const YREALTIMEPROVIDERINFO* pInfo);
                                YRealTime(const YREALTIME* pTime);
                                YRealTime(const YREALTIME& tTime);
                                YRealTime(const YRealTime& tTime);
                                ~YRealTime();

  static const YRealTime&       FromData(const YREALTIME& tTime);
  static YRealTime&             FromData(YREALTIME& tTime);

  YRealTime&                    operator =(const YRealTime& tTime);
  YRealTime&                    operator =(const YREALTIME& tTime);

  static YREALTIME              INVALID();    //construct invalid object
  static YREALTIME              MKTIME(YTIME);//standard provider used (may be unitialized)
  BOOL                          IsInvalid() const;
  BOOL                          IsInitialized() const;//this object is initialized
public: //time providers support
  static const YREALTIMEPROVIDERINFO* GetCurrentProviderInfo(); //NULL on error
  static YRealTime              GetCurrentRealTime();// get current time
  static YTime                  GetCurrentTime();
  static YTIME                  GetCurrentTics();
  static                        Init(int iProvider=DEFAULT, YTimeSpan tsResolution=YREALTIME_1TIC);
  static                        Term();
        /*constructor*/         YRealTime();  // get current time
  YTime                         Update();
public: //construction/destruction with multi-providers support
  static const YREALTIMEPROVIDERINFO* GetProviderInfo(int iProvider, YTimeSpan tsResolution=YREALTIME_1TIC); //NULL on error
  static YTime                  GetProviderTime(int iProvider, YTimeSpan tsResolution=YREALTIME_1TIC);
  static YTIME                  GetProviderTics(int iProvider, YTimeSpan tsResolution=YREALTIME_1TIC);
  static YRealTime              GetProviderRealTime(int iProvider, YTimeSpan tsResolution=YREALTIME_1TIC);
  static                        InitProvider(int iProvider, YTimeSpan tsResolution=YREALTIME_1TIC);
  static                        TermProvider(int iProvider, YTimeSpan tsResolution=YREALTIME_1TIC);
        /*constructor*/         YRealTime(int iProvider, YTimeSpan tsResolution=YREALTIME_1TIC);//auto initialization
  YTime                         Update(int iProvider, YTimeSpan tsResolution=YREALTIME_1TIC);//specified provider
public: //YREALTIME compatibility
                                operator const YREALTIME&() const;
                                operator YREALTIME&();
public: //attributes
  int                           GetTime(YREALTIME* pTime) const;
  YTime                         GetTime() const;
  YTIME                         GetTics() const;
  const YREALTIMEPROVIDERINFO*  GetInfo() const;
  YTimeSpan                     GetBias() const;//UTC = local + bias //only for DIRECTX, optionally for other
  YTimeSpan                     GetDrift() const;//tUser-tHasp

  int                           GetProvider()   const;
  YTimeSpan                     GetResolution() const;
  YTimeSpan                     GetMinPeriod()  const;
  YTimeSpan                     GetMaxPeriod()  const;
  YTimeSpan                     GetAdjustment() const;
  YTimeSpan                     GetIncrement()  const;
  YTimeSpan                     GetPrecision()  const;
//YTime                         GetInitTime()   const;//time of initialization
//YTIME                         GetInitTics()   const;//tics count at initialization
//YTimeSpan                     GetTimeSpan()   const;//duration since initialization
//YTIME                         GetTicsSpan()   const;//tics count since initialization

  YTimeSpan                     GetMeasurementBase() const;//time span of measurement

//YTime                         GetRealTime()   const;//use GetTime()
  YTime                         GetBaseTime()   const;//base time of measurement (may be approximate)

  YTime                         GetUserTime()   const;//for some providers showed for user time

  YTIME                         GetRealTics()   const;//tics counter directly (for some providers)
  YTIME                         GetBaseTics()   const;//base counter (for some providers)

  YTime                         GetZeroTime()   const;//OS Start time for some providers, base time elsewhere
  YTime                         GetHaspTime()   const;

  YTime                         GetZoneTime()   const;//user time + initial bias
  YTime                         GetLocalTime()  const;//user time + current bias

public:// operators
  YRealTime                     operator +(YTimeSpan timeSpan) const;
  YRealTime                     operator -(YTimeSpan timeSpan) const;
  YRealTime&                    operator +=(YTimeSpan timeSpan);
  YRealTime&                    operator -=(YTimeSpan timeSpan);

  YTimeSpan                     operator -(const YRealTime& rt)const;
public:// helpers
  static int   PASCAL           DoGetProviderTime(YREALTIMEPROVIDERINFO* pInfo,
                                  YTIME* pnTics=NULL, YTIME* ptTime=NULL, 
                                  YREALTIMEPROVIDERINFO* pLocalInfo=NULL);
  static int   PASCAL           DoInitProvider(YREALTIMEPROVIDERINFO* pInfo,
                                  int   iProvider, //iProvider=1-standard,2-high-resolution performance counter,3-mmsystem timers
                                  YTIME tsResolution=YTimeSpan(0,0,0,0,1)/*1ms*/);
  static int   PASCAL           DoTermProvider(YREALTIMEPROVIDERINFO* pInfo);
  static YTIME PASCAL           TicsToTime(const YREALTIMEPROVIDERINFO* pInfo, YTIME nsTics);
  static YTIME PASCAL           TimeToTics(const YREALTIMEPROVIDERINFO* pInfo, YTIME tsTime);

  static YTIME PASCAL           DoMakeRealTime(YTIME t, YREALTIME& tTime);
  static YTIME PASCAL           DoGetBaseTime(const YREALTIME& tTime);
  static YTIME PASCAL           DoGetBaseTics(const YREALTIME& tTime);
  static YTIME PASCAL           DoGetUserTime(const YREALTIME& tTime);
  static YTIME PASCAL           DoGetZeroTime(const YREALTIME& tTime);
  static YTIME PASCAL           DoGetRealTics(const YREALTIME& tTime);
  static YTIME PASCAL           DoGetZoneTime(const YREALTIME& tTime);
  static YTIME PASCAL           DoGetLocalTime(const YREALTIME& tTime);
  static YTIME PASCAL           DoGetBias(const YREALTIME& tTime);
  static YTIME PASCAL           DoGetDrift(const YREALTIME& tTime);
  static YTIME PASCAL           DoAddTimeSpan(YTIME ts, YREALTIME& tTime);

  static BOOL  PASCAL           IsSameTimeZone(const YREALTIME& tTime);// compare current YTime and tTime time zone. DirectX provider only //AY 02.04.2009
  static BOOL  PASCAL           IsDaylightSaving(const YREALTIME& tTime);// DirectX provider only //AY 02.04.2009

public://multithreading operators
  static volatile YREALTIME&    assign(volatile YREALTIME& t1, const volatile YREALTIME& t2);
  static BOOL                   is_equal(const volatile YREALTIME& t1, const volatile YREALTIME& t2);

public://local time adjustment operations
  static YREALTIME              convert(const YREALTIME& tReal, const YREALTIME& tUser, int iProvider);
  static int                    local_adjust(YREALTIME& tReal, YTIME tsAdjustnment);
  static YTimeSpan              calc_adjust(const YREALTIME& tReal, YTIME tLocal);

public://AFX support
  friend CDumpContext& AFXAPI   operator<<( CDumpContext& dc, YRealTime time );
  friend CArchive& AFXAPI       operator<<( CArchive& ar, YRealTime time );
  friend CArchive& AFXAPI       operator>>( CArchive& ar, YRealTime& time );

  static LPCTSTR                GetProviderName(int iProvider);
  CString                       GetDump(int mode=0) const;
};
#pragma pack(pop)

////////////////////////////////////////////////////////////////////////////////////
// YRealTime implementation 

inline YRealTime::YRealTime(YTIME tTime, YTIME nTics, const YREALTIMEPROVIDERINFO* pInfo)
  : YTime(YTime::mktime(tTime)) { m_tics=nTics, m_info=*pInfo; }

inline YRealTime::YRealTime(const YREALTIME* pTime)
  : YTime(YTime::mktime(pTime->m_time)) { m_tics=pTime->m_tics; m_info=pTime->m_info; }

inline YRealTime::YRealTime(const YREALTIME& tTime)
  : YTime(YTime::mktime(tTime.m_time)) { m_tics=tTime.m_tics; m_info=tTime.m_info; }

inline YRealTime::YRealTime(const YRealTime& tTime)
  : YTime(tTime) { m_tics=tTime.m_tics, m_info=tTime.m_info; }

inline YRealTime::~YRealTime()
  {}

inline const YRealTime& YRealTime::FromData(const YREALTIME& tTime)
  { return *(const YRealTime*)&tTime; }

inline YRealTime& YRealTime::FromData(YREALTIME& tTime)
  { return *(YRealTime*)&tTime; }

inline YRealTime& YRealTime::operator =(const YRealTime& tTime)
  { YTime::operator=(tTime); m_tics=tTime.m_tics, m_info=tTime.m_info; return *this; }

inline YRealTime& YRealTime::operator =(const YREALTIME& tTime)
  { YTime::operator=(YTime::mktime(tTime.m_time)); m_tics=tTime.m_tics, m_info=tTime.m_info; return *this; }

inline YREALTIME  YRealTime::INVALID()
  { YREALTIME t={YTIME_INVALID,0,{sizeof(YREALTIMEPROVIDERINFO)}}; return t; }

inline YREALTIME  YRealTime::MKTIME(YTIME tTime)
  { YREALTIME t={YTIME_INVALID,0,{sizeof(YREALTIMEPROVIDERINFO)}}; DoMakeRealTime(tTime,t); return t; }

inline BOOL       YRealTime::IsInvalid() const //AY 28.01.2005
  { return YTime::IsInvalid() || YTime::mktime(m_info.m_tInitTime).IsInvalid(); }

inline BOOL       YRealTime::IsInitialized() const
  { return !IsInvalid() && m_info.m_iProvider!=0; }


inline YRealTime::operator const YREALTIME&() const
  { return *(const YREALTIME*)this; }

inline YRealTime::operator YREALTIME&()
  { return *(YREALTIME*)this; }


inline int   YRealTime::GetTime(YREALTIME* pTime) const
  { pTime->m_time=m_data; pTime->m_tics=m_tics; pTime->m_info=m_info; return 0; }
inline YTime YRealTime::GetTime() const
  { return YTime::mktime(m_data); }
inline YTIME YRealTime::GetTics() const
  { return m_tics; }
inline const YREALTIMEPROVIDERINFO* YRealTime::GetInfo() const
  { return &m_info; }
inline YTimeSpan  YRealTime::GetBias() const //UTC = local + bias
  { return DoGetBias(*this); }
inline YTimeSpan  YRealTime::GetDrift() const //UTC = local + bias
  { return DoGetDrift(*this); }

inline int        YRealTime::GetProvider() const
  { return m_info.m_iProvider; }
inline YTimeSpan  YRealTime::GetResolution() const
  { return m_info.m_tsResolution; }
inline YTimeSpan  YRealTime::GetMinPeriod()  const
  { return m_info.m_tsMinPeriod; }
inline YTimeSpan  YRealTime::GetMaxPeriod()  const
  { return m_info.m_tsMaxPeriod; }
inline YTimeSpan  YRealTime::GetAdjustment() const
  { return m_info.m_tsAdjustment; }
inline YTimeSpan  YRealTime::GetIncrement()  const
  { return m_info.m_tsIncrement; }
inline YTimeSpan  YRealTime::GetPrecision()  const
  { return m_info.m_tsResolution; }

//inline YTime      YRealTime::GetInitTime() const
//  { return m_info.m_tInitTime; }
//inline YTIME      YRealTime::GetInitTics() const
//  { return m_info.m_nInitTics; }

//inline YTimeSpan  YRealTime::GetTimeSpan() const
//  { return m_data - m_info.m_tInitTime; }
//inline YTIME      YRealTime::GetTicsSpan() const
//  { return m_tics - m_info.m_nInitTics; }

inline YTimeSpan  YRealTime::GetMeasurementBase() const
  { return m_data - DoGetBaseTime(*this); }

//line YTime      YRealTime::GetRealTime() const
//{ return m_data; }
inline YTime      YRealTime::GetBaseTime() const
  { return YTime::mktime(DoGetBaseTime(*this)); }

inline YTime      YRealTime::GetUserTime() const
  { return YTime::mktime(DoGetUserTime(*this)); }

inline YTIME      YRealTime::GetRealTics() const
  { return DoGetRealTics(*this); }
inline YTIME      YRealTime::GetBaseTics() const
  { return DoGetBaseTics(*this); }

inline YTime      YRealTime::GetZeroTime() const
  { return YTime::mktime(DoGetZeroTime(*this)); }

inline YTime      YRealTime::GetZoneTime() const
  { return YTime::mktime(DoGetZoneTime(*this)); }
inline YTime      YRealTime::GetLocalTime() const
  { return YTime::mktime(DoGetLocalTime(*this)); }

inline YRealTime  YRealTime::operator +(YTimeSpan timeSpan) const
  { YRealTime t = *this; DoAddTimeSpan( timeSpan,t); return t; }
inline YRealTime  YRealTime::operator -(YTimeSpan timeSpan) const
  { YRealTime t = *this; DoAddTimeSpan(-timeSpan,t); return t; }
inline YRealTime& YRealTime::operator +=(YTimeSpan timeSpan)
  { DoAddTimeSpan( timeSpan,*this); return *this; }
inline YRealTime& YRealTime::operator -=(YTimeSpan timeSpan)
  { DoAddTimeSpan(-timeSpan,*this); return *this; }

inline  YTimeSpan YRealTime::operator -(const YRealTime& rt)const
  { return ((YTime)*this) - ((YTime)rt); } //AY 07.09.2003

inline volatile YREALTIME& YRealTime::assign(volatile YREALTIME& t1, const volatile YREALTIME& t2)
{
  t1.m_time                 = t2.m_time;
  t1.m_tics                 = t2.m_tics;
  t1.m_info.m_cbSize        = t2.m_info.m_cbSize      ;
  t1.m_info.m_iProvider     = t2.m_info.m_iProvider   ; 
  t1.m_info.m_nFlags        = t2.m_info.m_nFlags      ; 
  t1.m_info.m_reserved0     = t2.m_info.m_reserved0   ; 
  t1.m_info.m_tsResolution  = t2.m_info.m_tsResolution; 
  t1.m_info.m_nsResolution  = t2.m_info.m_nsResolution;
  t1.m_info.m_tsMinPeriod   = t2.m_info.m_tsMinPeriod ; 
  t1.m_info.m_nsMinPeriod   = t2.m_info.m_nsMinPeriod ; 
  t1.m_info.m_tsMaxPeriod   = t2.m_info.m_tsMaxPeriod ; 
  t1.m_info.m_nsMaxPeriod   = t2.m_info.m_nsMaxPeriod ; 
  t1.m_info.m_tsAdjustment  = t2.m_info.m_tsAdjustment;
  t1.m_info.m_nsAdjustment  = t2.m_info.m_nsAdjustment;
  t1.m_info.m_tsIncrement   = t2.m_info.m_tsIncrement ;
  t1.m_info.m_nsIncrement   = t2.m_info.m_nsIncrement ;
  t1.m_info.m_tsPrecision   = t2.m_info.m_tsPrecision ;
  t1.m_info.m_tInitTime     = t2.m_info.m_tInitTime   ;
  t1.m_info.m_nInitTics     = t2.m_info.m_nInitTics   ;
  return t1;
}
inline BOOL YRealTime::is_equal(const volatile YREALTIME& t1, const volatile YREALTIME& t2)
{
  return 
  t1.m_info.m_nInitTics     == t2.m_info.m_nInitTics    &&
  t1.m_info.m_tInitTime     == t2.m_info.m_tInitTime    &&
  t1.m_info.m_tsPrecision   == t2.m_info.m_tsPrecision  &&
  t1.m_info.m_nsIncrement   == t2.m_info.m_nsIncrement  &&
  t1.m_info.m_tsIncrement   == t2.m_info.m_tsIncrement  &&
  t1.m_info.m_nsAdjustment  == t2.m_info.m_nsAdjustment &&
  t1.m_info.m_tsAdjustment  == t2.m_info.m_tsAdjustment &&
  t1.m_info.m_nsMaxPeriod   == t2.m_info.m_nsMaxPeriod  &&
  t1.m_info.m_tsMaxPeriod   == t2.m_info.m_tsMaxPeriod  &&
  t1.m_info.m_nsMinPeriod   == t2.m_info.m_nsMinPeriod  &&
  t1.m_info.m_tsMinPeriod   == t2.m_info.m_tsMinPeriod  &&
  t1.m_info.m_nsResolution  == t2.m_info.m_nsResolution &&
  t1.m_info.m_tsResolution  == t2.m_info.m_tsResolution &&
  t1.m_info.m_reserved0     == t2.m_info.m_reserved0    &&
  t1.m_info.m_nFlags        == t2.m_info.m_nFlags       &&
  t1.m_info.m_iProvider     == t2.m_info.m_iProvider    &&
  t1.m_info.m_cbSize        == t2.m_info.m_cbSize       &&
  t1.m_tics                 == t2.m_tics                &&
  t1.m_time                 == t2.m_time                ;
}

//// AFX support ///////////////////////////////////////////////////////////////////

inline CDumpContext& AFXAPI   operator<<( CDumpContext& dc, YRealTime time )
{ 
  if(time.IsInvalid())
    return dc<<"YRealTime(invalid)";
  CString szResolution; szResolution.Format(_T("0.%09.9I64d"),time.GetResolution().GetNanoseconds());
  CString szMilliseconds; szMilliseconds.Format(_T(".%3.3d"),time.GetMilliseconds());
  dc<<"YRealTime("<<time.Format(YTIME_DUMP_FORMAT)<<szMilliseconds;//<<")";
  dc<<"  GMT: "<<time.FormatGmt(YTIME_DUMP_FORMAT)<<szMilliseconds;
  dc<<"  RES: "<<szResolution;
  dc<<")";
  return dc;
}

inline CArchive& AFXAPI       operator<<( CArchive& ar, YREALTIMEPROVIDERINFO rtpi )
{ 
  ar<<rtpi.m_cbSize;         
  ar<<rtpi.m_iProvider;      
  ar<<rtpi.m_nFlags;         
  ar<<rtpi.m_reserved0;      
  ar<<rtpi.m_tsResolution;
  ar<<rtpi.m_nsResolution;   
  ar<<rtpi.m_tsMinPeriod;    
  ar<<rtpi.m_nsMinPeriod;    
  ar<<rtpi.m_tsMaxPeriod;    
  ar<<rtpi.m_nsMaxPeriod;    
  ar<<rtpi.m_tsAdjustment;   
  ar<<rtpi.m_nsAdjustment;   
  ar<<rtpi.m_tsIncrement;    
  ar<<rtpi.m_nsIncrement;    
  ar<<rtpi.m_tsPrecision;    
  ar<<rtpi.m_tInitTime;
  ar<<rtpi.m_nInitTics;
  return ar; 
}
inline CArchive& AFXAPI       operator>>( CArchive& ar, YREALTIMEPROVIDERINFO& rtpi )
{ 
  ar>>rtpi.m_cbSize;         
  ar>>rtpi.m_iProvider;      
  ar>>rtpi.m_nFlags;         
  ar>>rtpi.m_reserved0;      
  ar>>rtpi.m_tsResolution;   
  ar>>rtpi.m_nsResolution;   
  ar>>rtpi.m_tsMinPeriod;    
  ar>>rtpi.m_nsMinPeriod;    
  ar>>rtpi.m_tsMaxPeriod;    
  ar>>rtpi.m_nsMaxPeriod;    
  ar>>rtpi.m_tsAdjustment;   
  ar>>rtpi.m_nsAdjustment;   
  ar>>rtpi.m_tsIncrement;    
  ar>>rtpi.m_nsIncrement;    
  ar>>rtpi.m_tsPrecision;    
  ar>>rtpi.m_tInitTime;
  ar>>rtpi.m_nInitTics;
  return ar; 
}

inline CArchive& AFXAPI       operator<<( CArchive& ar, YRealTime t )
  { return ar<<t.m_data<<t.m_tics<<t.m_info; }
inline CArchive& AFXAPI       operator>>( CArchive& ar, YRealTime& t )
  { return ar>>t.m_data>>t.m_tics>>t.m_info; }

//// Extensions ////////////////////////////////////////////////////////////////////

#endif//__cplusplus
////////////////////////////////////////////////////////////////////////////////////

#endif//__yREALTIME_H
#pragma once
