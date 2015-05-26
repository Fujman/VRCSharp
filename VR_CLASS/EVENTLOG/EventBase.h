#ifndef __EVENTBASE_H
#define __EVENTBASE_H
#include  "int64.h"
#include  "time32.h"
#include  "YTime.h"
#ifdef  __cplusplus
#pragma pack(push,1)

/////////////////////////////////////////////////////////////////////////////
#define  EVN_64BIT_CLASS   (0)  // (16 bytes/event, data-32+32+16 bits, type-4 bits)
#define  EVN_16BIT_CLASS   (1)  // (8 bytes/event, data-16 bits, type-4 bits)
#define  EVN_20BIT_CLASS   (2)  // (8 bytes/event, data-20 bits, type-0 bits)
#define  EVN_xxBIT_CLASS   (3)  // variable data size event (16+raw data size)
/////////////////////////////////////////////////////////////////////////////
// structures YEventBaseData(1,2), YEventBaseData64(0), YEventBaseDataEx(3)

struct tagYEventBaseData {      // 64 bits (8 bytes)   // data: 16 bits (2 bytes)
  WORD          m_nClass:2;     // = EVN_16BIT_CLASS (1)
  WORD          m_nType:4;  
  WORD          m_nMsec:10;     // milliseconds
  WORD          m_nData;        // data (16 bits)
  TIME_T        m_tTime;        // seconds since 1.01.1970
};

struct tagYEventBaseData64:     // 128 bits (16 bytes) // data: 80 bits (10 bytes)
public tagYEventBaseData
{    
//WORD          m_nClass:2;     // = EVN_64BIT_CLASS (0)
//WORD          m_nType:4;  
//WORD          m_nMsec:10;     // milliseconds
//WORD          m_nData;        // data (16 bits)
//time_t        m_tTime;        // seconds since 1.01.1970
  DWORD         m_dwData[2];    // data (64 bits)
};

struct tagYEventBaseDataEx:     // 128 bits (16 bytes) // data: 80 bits (10 bytes)
public tagYEventBaseData {
//WORD          m_nClass:2;     // = EVN_xxBIT_CLASS (3)
//WORD          m_nType:4;      //
//WORD          m_nMsec:10;     // milliseconds
//WORD          m_nData;        // message ID
//time_t        m_tTime;        // seconds since 1.01.1970
  WORD          m_nYsec:14;     // time_t extension to YTime - in 100ns units
  WORD          m_nYera:2;      // time_t extension to YTime - must be zero 
  WORD          m_nSize:16;     // data size, bytes
  DWORD         m_nSignature;   // data type
};

/////////////////////////////////////////////////////////////////////////////
// YEventBaseData: non-virtual
class YEventBaseData : protected tagYEventBaseData/*Ex*/ { //! if m_nClass==3 treated as inherited from tagYEventBaseDataEx
public://construction/destruction
  typedef TIME_T time_t;//local time_t //AY 01.02.2011
  void          Invalidate();
  YTime         SetTimeEx();                      // current time
  time_t        SetTime();                        // current time

public://attributes
  WORD          GetClass()const;                  // 0..3
  WORD          SetClass(WORD nClass);
  WORD          GetType()const;                   // 0..15
  WORD          SetType(WORD nType);

  time_t        GetTime(WORD *pnMsec=NULL)const;
  time_t        SetTime(time_t tTime, WORD nMsec=0);

  YTime         GetTimeEx()const;
  YTime         SetTimeEx(YTime);

  WORD          SetMessageID(WORD  nMessageID);
  WORD          GetMessageID() const;

  DWORD         SetSignature(DWORD nSignature);  //EVN_xxBIT_CLASS only
  DWORD         GetSignature()const;             //EVN_xxBIT_CLASS only

public://raw data operations
  size_t        GetSize()const; //size of raw data
  const void*   GetData()const;
  void*         GetData();
  void*         GetData(void *pData, int nMaxSize=0, size_t nOffset=0) const;
  void*         SetData(const void *pData, int nRawSize=0, size_t nOffset=0);

public://struct+data helpers
  size_t        SizeOf() const; //size of struct+data
  static size_t SizeOf(const YEventBaseData* pData, size_t nDataSize=0);

public://operations
  LPTSTR        GetTime(LPTSTR szEvent, int nLength) const;
};

/////////////////////////////////////////////////////////////////////////////
// YEventBaseDataEx; non-virtualized, HSRSRECORD compatible, used conceptually only

class  YEventBaseDataEx : public tagYEventBaseDataEx {
public: //move to YEventBaseData - non-virtual!
  typedef TIME_T time_t;//local time_t //AY 01.02.2011
  YTime         SetTimeEx();               // current time
  time_t        SetTime();                 // current time

  WORD          GetClass()const;           // 0..3
  WORD          SetClass(WORD nClass);
  WORD          GetType()const;            // 0..15
  WORD          SetType(WORD nType);

  time_t        GetTime(WORD *pnMsec=NULL)const;
  time_t        SetTime(time_t tTime, WORD nMsec=0);

  YTime         GetTimeEx() const;
  YTime         SetTimeEx(YTime t);

  WORD          SetMessageID(WORD  nMessageID);
  WORD          GetMessageID() const;

  DWORD         SetSignature(DWORD nSignature);  //EVN_xxBIT_CLASS only
  DWORD         GetSignature()const;             //EVN_xxBIT_CLASS only

  DWORD         GetSize()const;
  const void*   GetData()const;
  void*         GetData();
};

/////////////////////////////////////////////////////////////////////////////

#include "EventBase.inl"

#pragma pack(pop)
#endif//__cplusplus
#endif//__EVENTBASE_H
#pragma once
