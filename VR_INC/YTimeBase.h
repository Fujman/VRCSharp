#ifndef __yTIMEBASE_H
#define __yTIMEBASE_H

#include "c_inheritance.h"

#define  NO_USE_REALTIME

struct _YSTEP        ;    //YTIME
struct _YSTEPTICS    ;    //YTIME
struct _YTIME        ;    //YTIME
struct _YTIMESPAN    ;    //YTIME
struct _YLATESTEP    ;    //YTIME
struct _YBASETIME    ;    //YTIME
struct _YSPAN        ;    //_YTIME+_YTIMESPAN
struct _YTICS        ;    //_YSPAN+_YSPAN
struct _YBASE        ;    //_YBASETIME+_YTIME
struct _YLATE        ;    //_YLATESTEP+_YSTEP

#ifndef NO_USE_REALTIME
struct _YREALTICS    ;    //YTICS+YTICSINFO
struct _YREALTIME    ;    //YTICS+YTIMEINFO
struct  YREALTICS    ;    //YTICS+YTICSMETERING
struct  YREALTIME    ;    //YTICS+YTIMEPROVIDER
#endif//NO_USE_REALTIME

struct _YTICSINFO    ;
struct _YTIMEINFO    ;
struct _YMETERINGINFO;
struct _YPROVIDERINFO;
struct _YTICSMETERING;//YTICSINFO+YMETERINGINFO
struct _YTIMEPROVIDER;//YTIMEINFO+YPROVIDERINFO

// C and C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

#ifndef __YTIME_DEFINED
#define __YTIME_DEFINED
typedef __int64 YTIME;
#endif//__YTIME_DEFINED

////////////////////////////////////////////////////////////////////////////////////
#pragma pack(push)
#pragma pack(1)

///////////////////////////////////////
struct _YSTEPTICS //YStepTics   //_YTICS?
{
    YTIME           m_tics;         //
};      

struct _YSTEP     //YStep
{
    YTIME           m_step;         //
};

struct _YTIMESPAN //YTimeSpan  //_YSPAN?
{
    YTIME           m_span;         // YTimeSpan
};

struct _YTIME     //YTime
{
    YTIME           m_time;         // YTime
};

struct _YLATESTEP //YLateStep
{
    YTIME           m_latestep;     // YStep
};

struct _YBASETIME //YBaseTime
{
    YTIME           m_basetime;     // YTime
};

///////////////////////////////////////
struct _YSPAN //YSpan  //YTIMESPAN?
{
    USE_AS_OPERATOR(_YBASETIME, const {_YBASETIME s={m_time-m_span};return s;} )
    DECLAREOPERATOR(_YBASE,     const);
    YTIME           m_time;     USE_AS(_YTIME,      m_time);// YTime
    YTIME           m_span;     USE_AS(_YTIMESPAN,  m_span);// YTimeSpan BEFORE m_time
};

struct _YTICS //YTics //YTicsStep //YTICSSTEP?
{
    USE_AS_OPERATOR(_YLATESTEP, const {_YLATESTEP s={m_step+m_tics};return s;} )
    DECLAREOPERATOR(_YLATE,     const);
    YTIME           m_tics;     USE_AS(_YSTEPTICS,  m_tics);// YTicsSpan SINCE  m_base
    YTIME           m_step;     USE_AS(_YSTEP,      m_step);// YStep (=YTicsSpan from 0)
};

struct _YBASE //YTimeBase  //_YTIMEBASE?
{
    USE_AS_OPERATOR(_YTIMESPAN, const {_YTIMESPAN s={m_time-m_basetime};return s;} )
    DECLAREOPERATOR(_YSPAN,     const);
    YTIME           m_basetime; USE_AS(_YTIME,  m_basetime);// YTime
    YTIME           m_time;                                 // YTime
};

struct _YLATE //YStepLate  //_YSTEPLATE?
{
    USE_AS_OPERATOR(_YSTEPTICS, const {_YSTEPTICS s={m_latestep-m_step};return s;} )
    DECLAREOPERATOR(_YTICS,     const);
    YTIME           m_latestep; USE_AS(_YSTEP,  m_latestep);// YStep
    YTIME           m_step;                                 // YStep
};

#ifdef __cplusplus
inline _YSPAN::operator _YBASE() const {_YBASE s={m_time-m_span,m_time};return s;}
inline _YTICS::operator _YLATE() const {_YLATE s={m_step+m_tics,m_step};return s;}
inline _YBASE::operator _YSPAN() const {_YSPAN s={m_time,m_time-m_basetime};return s;}
inline _YLATE::operator _YTICS() const {_YTICS s={m_latestep-m_step,m_step};return s;}
#endif

///////////////////////////////////////
struct _YTICSTIME//_YTICSBASE?
{
    YTIME           m_tics;     USE_AS(_YSTEPTICS,  m_tics);// YTicsSpan SINCE m_time
    YTIME           m_basetime; USE_AS(_YBASETIME,  m_basetime);// YTime
};
struct _YSTEPSPAN//_YLATESPAN?
{
    YTIME           m_latestep; USE_AS(_YLATESTEP,  m_latestep);// YStep
    YTIME           m_span;     USE_AS(_YTIMESPAN,  m_span);// YTimeSpan BEFORE m_base
};

struct _YTIMESTEP
{
    YTIME           m_time;     USE_AS(_YTIME,      m_time);// YTime
    YTIME           m_step;     USE_AS(_YSTEP,      m_step);// YStep at m_time
};
struct _YSPANTICS
{
    YTIME           m_span;     USE_AS(_YTIMESPAN,  m_span);// YTimeSpan
    YTIME           m_tics;     USE_AS(_YSTEPTICS,  m_tics);// YTicsSpan during m_span
};
///////////////////////////////////////

struct _YTIMETICS
{                                                            
    YTIME           m_time;     USE_AS(_YTIME,     m_time);
    YTIME           m_span;     USE_AS(_YTIMESPAN, m_span);
    YTIME           m_tics;     USE_AS(_YSTEPTICS, m_tics);
    YTIME           m_step;     USE_AS(_YSTEP,     m_step);
//C++//conversions
    USE_AS_OPERATOR(_YBASE,     const {_YBASE s={m_time-m_span};s.m_time=m_time;return s;} )
    USE_AS_OPERATOR(_YLATE,     const {_YLATE s={m_step+m_tics};s.m_step=m_step;return s;} )
    USE_AS         (_YSPAN,     m_time);
    USE_AS         (_YTICS,     m_tics);
    Cx2( operator   _YTICSTIME()const {_YTICSTIME s={m_tics,m_time};return s;} )
    Cx2( operator   _YSTEPSPAN()const {_YSTEPSPAN s={m_step,m_span};return s;} )
    Cx2( operator   _YTIMESTEP()const {_YTIMESTEP s={m_time,m_step};return s;} )
    Cx2( operator   _YSPANTICS()const {_YSPANTICS s={m_span,m_tics};return s;} )
//? USE_AS         (_YSPANTICS, m_span);
};

//_YTIMETICS
//NEW:             ALL(m_span=~m_tics)  WINDOWS(m_span!~m_tics)
//m_time;          =m_time              =m_time             (time)
//m_span;          =m_time-m_tInitTime  =m_time-m_tInitTime (time - user_time)
//m_tics;          =m_tics-m_nInitTics  =m_tics-m_nInitTics (tics)      =provider.m_tics-provider.m_nInitTics
//m_step;          =m_nInitTics         =@                  (base tics)
//                                       m_nInitTics == ((base time - user time)/rate) < 0
//                                       @=m_tInitTime-TicsToTime(-m_nInitTics)
//GetSpan:         m_span               TicsToTime(m_tics)
//GetUser:        (m_time)              m_time-m_span
//GetTime:         m_time               m_time
//GetBase:         m_time-m_span *)     m_time-TicsToTime(m_tics)
//                 *)m_time-m_span==m_time-TicsToTime(m_tics)
//Update:
//                 m_time+=             m_time+=
//                 m_span+=             m_span=
//                 m_tics+=             m_tics+=

struct _YINTERVAL
{                                                            
    YTIME           m_time;  USE_AS(_YTIME,      m_time);
    YTIME           m_span;  USE_AS(_YTIMESPAN,  m_span);
    YTIME           m_tics;  USE_AS(_YSTEPTICS,  m_tics);
    YTIME           m_step;  USE_AS(_YSTEP,      m_step);
//C++//conversions
    USE_AS(_YSPAN,  m_time);
    USE_AS(_YTICS,  m_tics);
    Cx2(operator _YTICSTIME() const { _YTICSTIME s={m_tics,m_time}; return s; })
    Cx2(operator _YSTEPSPAN() const { _YSTEPSPAN s={m_step,m_span}; return s; })
    Cx2(operator _YTIMESTEP() const { _YTIMESTEP s={m_time,m_step}; return s; })
    USE_AS(_YSPANTICS,  m_span);
};


////////////////////////////////////////////////////////////////////////////////

struct _YTICSINFO
{
  WORD                          m_cbSize;         //size of struct
  WORD                          m_nFlags;         
  DWORD                         m_meteringinfo;   //metering type or pointer: see YRealTimer?
};
struct _YMETERINGINFO
{
  YTIME/*YTimeSpan*/            m_tsMaxPeriod;    //// YTimeSpan m_tsBase;max time period between roll-up counter
  YTIME/*YTicsSpan*/            m_nsMaxPeriod;    //max time period between roll-up counter
};
struct _YTICSMETERING: public   _YTICSINFO, _YMETERINGINFO //rtpi
{                                                     
//WORD                          m_cbSize;   
//WORD                          m_nFlags;         
//DWORD                         m_providerinfo;   //provider type or pointer: see YRealTime
//YTIME/*YTimeSpan*/            m_tsMaxPeriod;    //// YTimeSpan m_tsBase;max time period between roll-up counter
//YTIME/*YTicsSpan*/            m_nsMaxPeriod;    //max time period between roll-up counter
};

struct _YTIMEINFO
{
  WORD                          m_cbSize;   
  WORD                          m_nFlags;         
  DWORD                         m_providerinfo;   //provider type or pointer: see YRealTime
};
struct _YPROVIDERINFO
{
  YTIME/*YTimeSpan*/            m_tsResolution;   //duration of one tic (HIGH part: if ==0 use m_nsResolution)
  YTIME/*YTicsSpan*/            m_nsResolution;   //tics per second     (LOW  part: if ==0 use m_tsResolution)
  YTIME/*YTimeSpan*/            m_tsMinPeriod;    //min period between measurements with different results (HIGH part: if ==0 use m_nsMinPeriod)
  //IME/*YTicsSpan*/            m_nsMinPeriod;    //min period between measurements with different results (LOW  part: if ==0 use m_tsMinPeriod)
  YTIME/*YTimeSpan*/            m_tsMaxPeriod;    //max time period between roll-up counter
  YTIME/*YTicsSpan*/            m_nsMaxPeriod;    //max time period between roll-up counter
  YTIME/*YTimeSpan*/            m_tsAdjustment;   //time synchronization span (HIGH part: if ==0 use m_nsAdjustment)
  YTIME/*YTicsSpan*/            m_nsAdjustment;   //time synchronization span (LOW  part: if ==0 use m_tsAdjustment)
  YTIME/*YTimeSpan*/            m_tsIncrement;    //time synchronization increment (HIGH part: if ==0 use m_nsIncrement)
  YTIME/*YTicsSpan*/            m_nsIncrement;    //time synchronization increment (LOW  part: if ==0 use m_tsIncrement)
  YTIME/*YTimeSpan*/            m_tsPrecision;    //max error per 1 year
};
struct _YTIMEPROVIDER: public   _YTIMEINFO, _YPROVIDERINFO //rtpi
{                                                     
//WORD                          m_cbSize;   
//WORD                          m_nFlags;         
//DWORD                         m_providerinfo;   //provider type or pointer: see YRealTime
//YTIME/*YTimeSpan*/            m_tsResolution;   //duration of one tic (HIGH part: if ==0 use m_nsResolution)
//YTIME/*YTicsSpan*/            m_nsResolution;   //tics per second     (LOW  part: if ==0 use m_tsResolution)
//YTIME/*YTimeSpan*/            m_tsMinPeriod;    //min period between measurements with different results (HIGH part: if ==0 use m_nsMinPeriod)
////IME/*YTicsSpan*/            m_nsMinPeriod;    //min period between measurements with different results (LOW  part: if ==0 use m_tsMinPeriod)
//YTIME/*YTimeSpan*/            m_tsMaxPeriod;    //max time period between roll-up counter
//YTIME/*YTicsSpan*/            m_nsMaxPeriod;    //max time period between roll-up counter
//YTIME/*YTimeSpan*/            m_tsAdjustment;   //time synchronization span (HIGH part: if ==0 use m_nsAdjustment)
//YTIME/*YTicsSpan*/            m_nsAdjustment;   //time synchronization span (LOW  part: if ==0 use m_tsAdjustment)
//YTIME/*YTimeSpan*/            m_tsIncrement;    //time synchronization increment (HIGH part: if ==0 use m_nsIncrement)
//YTIME/*YTicsSpan*/            m_nsIncrement;    //time synchronization increment (LOW  part: if ==0 use m_tsIncrement)
//YTIME/*YTimeSpan*/            m_tsPrecision;    //max error per 1 year
};


struct _YREALTICS       PUBLIC(_YTIMETICS)
{
I(  YTIME                       m_time; )      //  YTimeSpan m_tsDeltaTime;=m_time-m_base.m_time
I(  YTIME                       m_span; )      //  YPos      m_qDeltaPos;
I(  YTIME                       m_tics; )      //  YTime     m_tStart;
I(  YTIME                       m_step; )      //  YPos      m_qPrevPos;
  struct _YTICSINFO             m_info;
  //WORD                        m_cbSize;   
  //WORD                        m_nFlags;         
  //DWORD                       m_providerinfo;  //provider type or pointer: see YRealTime
};

struct _YREALTIME: public       _YTIMETICS
{
//YTIME                         m_time;
//YTIME                         m_tics;
//YSPAN                         m_base;
  //YTIME                       m_base.m_time;
  //YTIME                       m_base.m_tics;
  struct _YTIMEINFO             m_info;
  //WORD                        m_cbSize;   
  //WORD                        m_nFlags;         
  //DWORD                       m_providerinfo;   //provider type or pointer: see YRealTime
};

struct YREALTICS: public        _YTICS
{
//YTIME                         m_time;     
//YTIME                         m_tics;     
//YTIME                         m_tBaseTime;
//YTIME                         m_nBaseTics;
  struct _YTICSMETERING         m_info;
  //WORD                        m_cbSize;   
  //WORD                        m_nFlags;         
  //DWORD                       m_providerinfo;  //provider type or pointer: see YRealTime
  //YTIME/*YTimeSpan*/          m_tsResolution;   //duration of one tic (HIGH part: if ==0 use m_nsResolution)
  //YTIME/*YTicsSpan*/          m_nsResolution;   //tics per second     (LOW  part: if ==0 use m_tsResolution)
  //YTIME/*YTimeSpan*/          m_tsMinPeriod;    //min period between measurements with different results (HIGH part: if ==0 use m_nsMinPeriod)
  //YTIME/*YTimeSpan*/          m_tsMaxPeriod;    //max time period between roll-up counter
  //YTIME/*YTicsSpan*/          m_nsMaxPeriod;    //max time period between roll-up counter
  //YTIME/*YTimeSpan*/          m_tsAdjustment;   //time synchronization span (HIGH part: if ==0 use m_nsAdjustment)
  //YTIME/*YTicsSpan*/          m_nsAdjustment;   //time synchronization span (LOW  part: if ==0 use m_tsAdjustment)
  //YTIME/*YTimeSpan*/          m_tsIncrement;    //time synchronization increment (HIGH part: if ==0 use m_nsIncrement)
  //YTIME/*YTicsSpan*/          m_nsIncrement;    //time synchronization increment (LOW  part: if ==0 use m_tsIncrement)
  //YTIME/*YTimeSpan*/          m_tsPrecision;    //max error per 1 year
};

#ifndef NO_USE_REALTIME
struct YREALTIME: public        _YTICS
{
//YTIME                         m_time;     
//YTIME                         m_tics;     
//YTIME                         m_tBaseTime;
//YTIME                         m_nBaseTics;
  struct _YTIMEPROVIDER         m_info;
  //WORD                        m_cbSize;   
  //WORD                        m_nFlags;         
  //DWORD                       m_providerinfo;   //provider type or pointer: see YRealTime
  //YTIME/*YTimeSpan*/          m_tsResolution;   //duration of one tic (HIGH part: if ==0 use m_nsResolution)
  //YTIME/*YTicsSpan*/          m_nsResolution;   //tics per second     (LOW  part: if ==0 use m_tsResolution)
  //YTIME/*YTimeSpan*/          m_tsMinPeriod;    //min period between measurements with different results (HIGH part: if ==0 use m_nsMinPeriod)
  //YTIME/*YTimeSpan*/          m_tsMaxPeriod;    //max time period between roll-up counter
  //YTIME/*YTicsSpan*/          m_nsMaxPeriod;    //max time period between roll-up counter
  //YTIME/*YTimeSpan*/          m_tsAdjustment;   //time synchronization span (HIGH part: if ==0 use m_nsAdjustment)
  //YTIME/*YTicsSpan*/          m_nsAdjustment;   //time synchronization span (LOW  part: if ==0 use m_tsAdjustment)
  //YTIME/*YTimeSpan*/          m_tsIncrement;    //time synchronization increment (HIGH part: if ==0 use m_nsIncrement)
  //YTIME/*YTicsSpan*/          m_nsIncrement;    //time synchronization increment (LOW  part: if ==0 use m_tsIncrement)
  //YTIME/*YTimeSpan*/          m_tsPrecision;    //max error per 1 year
} YREALTIME;
#endif//NO_USE_REALTIME

#pragma pack(pop)

// C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

typedef struct _YSTEP          _YSTEP;        //YTIME
typedef struct _YSTEPTICS      _YSTEPTICS;    //YTIME
typedef struct _YTIME          _YTIME;        //YTIME
typedef struct _YTIMESPAN      _YTIMESPAN;    //YTIME
typedef struct _YLATESTEP      _YLATESTEP;    //YTIME
typedef struct _YBASETIME      _YBASETIME;    //YTIME
typedef struct _YSPAN           YSPAN;        //_YTIME+_YTIMESPAN
typedef struct _YTICS           YTICS;        //_YSPAN+_YSPAN
typedef struct _YBASE           YBASE;        //_YBASETIME+_YTIME
typedef struct _YLATE           YLATE;        //_YLATESTEP+_YSTEP

#ifndef NO_USE_REALTIME
typedef struct _YREALTICS      _YREALTICS;    //YTICS+YTICSINFO
typedef struct _YREALTIME      _YREALTIME;    //YTICS+YTIMEINFO
typedef struct  YREALTICS       YREALTICS;    //YTICS+YTICSMETERING
typedef struct  YREALTIME       YREALTIME;    //YTICS+YTIMEPROVIDER
#endif//NO_USE_REALTIME

typedef struct _YTICSINFO       YTICSINFO;
typedef struct _YTIMEINFO       YTIMEINFO;
typedef struct _YMETERINGINFO   YMETERINGINFO;
typedef struct _YPROVIDERINFO   YPROVIDERINFO;
typedef struct _YTICSMETERING   YTICSMETERING;//YTICSINFO+YMETERINGINFO
typedef struct _YTIMEPROVIDER   YTIMEPROVIDER;//YTIMEINFO+YPROVIDERINFO


// C section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifndef __cplusplus

typedef YTIME                   YTime;
typedef YTIME                   YTimeSpan;
typedef YTIME                   YStep;
typedef YTIME                   YStepTics;
typedef struct _YSPAN           YSpan;
typedef struct _YTICS           YTics;
typedef struct _YBASE           YBase;
typedef struct _YLATE           YLate;

typedef struct  YREALTICS       YRealTics;
typedef struct  YREALTIME       YRealTime;

typedef struct _YTIME           YSpanTime;
typedef struct _YTIMESPAN       YSpanSpan;
typedef struct _YSPAN           YSpan;
typedef struct _YTICS           YSpanTics;
typedef struct  YREALTICS       YSpanRealTics;
#ifndef NO_USE_REALTIME
typedef struct  YREALTIME       YSpanRealTime;
#endif//NO_USE_REALTIME

#endif//__cplusplus

// C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus

#endif//__cplusplus


#endif//__yTIMEBASE_H
#pragma once
