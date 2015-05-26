#ifndef __EVENTEX_H
#define __EVENTEX_H
#include "Event.h"
#ifdef  __cplusplus
#pragma pack(push,1)

/////////////////////////////////////////////////////////////////////////////
// Class YEventEx
class YEventEx: public YEVENT_CLASS(YEventEx,YEvent64) {// sizeof() = 128 bits = 16 bytes + size
protected:
//WORD          m_nClass:2; = EVN_xxBIT_CLASS (3)
//WORD          m_nType:4;  = type:3(raw data, UNICODE),flag:1
//WORD          m_nMsec:10; = Msec:10
//WORD          m_nData:16; = message
//time_t        m_tTime:32; = time
//WORD          m_nYsec:14; = time_t extension to YTime - in 100ns units
//WORD          m_nYera:2;  = time_t extension to YTime - must be zero 
//WORD          m_nSize:16; = data size, bytes
//DWORD         m_nSignature;=data type

public: enum    {eventCLASS=EVN_xxBIT_CLASS, eventTYPE=-1};

public:
 static YEvent* Allocate(const void *pEBD, size_t nSize=0, void *pMem=NULL, size_t nMemSize=0, LPCSTR szFileName=0, int nLine=0);
                YEventEx(const void* pEBD, int nSize=0);
public:
 static YEvent* CreateEx(WORD nType, WORD nMessageID, int nRawSize, const void *pRawData=NULL, DWORD nSignature=0, void *pMem=NULL, int nMemSize=0, LPCSTR szFileName=0, int nLine=0);
protected:      YEventEx(WORD nType, WORD nMessageID, int nRawSize, const void *pRawData=NULL, DWORD nSignature=0);
 //atic YEvent* DeleteEx(YEvent* pEvent, void *pMem=0);
public:
  BYTE          GetData8 (int n=0)const;
  BYTE          SetData8 (BYTE byData, int n=0);
  WORD          GetData16(int n=0)const;
  WORD          SetData16(WORD wData, int n=0);
  DWORD         GetData32(int n=0)const;
  DWORD         SetData32(DWORD dwData, int n=0);
  QWORD         GetData64(int n=0)const;
  QWORD         SetData64(QWORD qwData, int n=0);
  LPWSTR        SetString(LPCWSTR, int nLen =-1);
  LPCWSTR       GetString()const;
  LPWSTR        GetString(LPWSTR, int nMaxLen=0) const;

public: //virtulized functions
  LPTSTR        GetInfo(LPTSTR szEvent, int nLength, int* pnLevel=NULL, int* pnClass=NULL, DWORD* pdwCategory=NULL) const;
  LPTSTR        GetText(LPTSTR szEvent, int nLength) const;
  LPTSTR        GetDump(LPTSTR szEvent, int nLength) const;
  int           IsEmpty() const;

private://exclude non-used functions
  WORD          SetClass(WORD nClass){ASSERT(0);return 0;};
public:
  enum          {SIZE_OF_BASE_DATA=sizeof(tagYEventBaseDataEx)};
};

/////////////////////////////////////////////////////////////////////////////
// classes registration
YEVENT_CLASS_DECLARE(YEventEx,YEvent64);

/////////////////////////////////////////////////////////////////////////////
// Inline implementation
#include "EventEx.inl"

/////////////////////////////////////////////////////////////////////////////
#pragma pack(pop)
#endif//__cplusplus
#endif//__EVENTEX_H
#pragma once
