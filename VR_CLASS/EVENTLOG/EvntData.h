#ifndef __EVNTDATA_H
#define __EVNTDATA_H
#include "EventEx.h"
#ifdef  __cplusplus
#pragma pack(push,1)

/////////////////////////////////////////////////////////////////////////////
#define  EVN_GENERIC_DATA    (0)// raw data
/////////////////////////////////////////////////////////////////////////////
// YEventData
class YEventData: public YEVENT_CLASS(YEventData,YEventEx) {// sizeof() = 128 bits = 16 bytes + size

public: enum    {eventCLASS=EVN_xxBIT_CLASS, eventTYPE=EVN_GENERIC_DATA};
public:
 static YEvent* Allocate(const void *pEBD, size_t nSize=0, void *pMem=NULL, size_t nMemSize=0, LPCSTR szFileName=0, int nLine=0);
                YEventData(const void* pEBD, int nSize=0);
public:
 static YEvent* CreateEx(WORD nMessageID, int nRawSize, const void* pRawData=NULL, DWORD dwSignature=0, void *pMem=NULL, int nMemSize=0, LPCSTR szFileName=0, int nLine=0);
protected:      YEventData(WORD nMessageID, int nRawSize, const void *pRawData=NULL, DWORD dwSignature=0);

public: //virtulized functions
  LPTSTR        GetInfo(LPTSTR szEvent, int nLength, int* pnLevel=NULL, int* pnClass=NULL, DWORD* pdwCategory=NULL) const;
  LPTSTR        GetText(LPTSTR szEvent, int nLength) const;
  LPTSTR        GetDump(LPTSTR szEvent, int nLength) const;

private://exclude non-used functions
  WORD          SetType(WORD nType){ASSERT(0);return 0;};
};

/////////////////////////////////////////////////////////////////////////////
// classes registration
YEVENT_CLASS_DECLARE(YEventData,YEventEx);

/////////////////////////////////////////////////////////////////////////////
// Inline implementation
#include "EvntData.inl"

#pragma pack(pop)
#endif//__cplusplus
/////////////////////////////////////////////////////////////////////////////
// C calls
#ifdef __cplusplus
extern "C" {
#define _0 =0
#else
#define _0
#endif

int YLogDataEvent(WORD nMessageID, const void* pData, int nSize, DWORD nSignature _0);

#undef _0
#ifdef __cplusplus
}
#endif

#endif//__EVNTDATA_H
#pragma once
