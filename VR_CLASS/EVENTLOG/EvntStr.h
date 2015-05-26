#ifndef __EVNTSTR_H
#define __EVNTSTR_H
#include "EventEx.h"
#ifdef  __cplusplus
#pragma pack(push,1)

/////////////////////////////////////////////////////////////////////////////
#define  EVN_GENERIC_UNICODE (7) // UNICODE string (zero terminated)
#define  EVN_CRYPTED_STRING (15) // UNICODE string (zero terminated, crypted)
/////////////////////////////////////////////////////////////////////////////
// Class YEventString
class YEventString: public YEVENT_CLASS(YEventString,YEventEx)  {// sizeof() = 128 bits = 16 bytes + size

public: enum    {eventCLASS=EVN_xxBIT_CLASS, eventTYPE=EVN_GENERIC_UNICODE};
public:
 static YEvent* Allocate(const void *pEBD, size_t nSize=0, void *pMem=NULL, size_t nMemSize=0, LPCSTR szFileName=0, int nLine=0);
                YEventString(const void *pData, int nDataSize=0);
public:
 static YEvent* CreateEx(WORD nMessageID, LPCTSTR sz, int nLen=-1, DWORD dwSignature=0, void *pMem=NULL, int nMemSize=0, LPCSTR szFileName=0, int nLine=0);
protected:      YEventString(WORD nMessageID, LPCTSTR sz, int nLen=-1, DWORD dwSignature=0);
  void*         SetData(LPCTSTR sz, int nLen =-1);
public:
  LPCWSTR       SetString(LPCTSTR sz, int nLen =-1);
  CString       GetString()const;

public: //virtulized functions
  LPTSTR        GetInfo(LPTSTR szEvent, int nLength, int* pnLevel=NULL, int* pnClass=NULL, DWORD* pdwCategory=NULL) const;
  LPTSTR        GetText(LPTSTR szEvent, int nLength) const;
  LPTSTR        GetDump(LPTSTR szEvent, int nLength) const;
public: //helpers
  static LPWSTR Unicode(void *pMem, int nMax, LPCTSTR sz, int nLen =-1);
  static size_t SizeOf(LPCTSTR sz, int nLen =-1);//in bytes
private://exclude non-used functions
  WORD          SetType(WORD nType){ASSERT(0);return 0;};
};

/////////////////////////////////////////////////////////////////////////////
// Class YEventCryptedString
class YEventCryptedString: public YEVENT_CLASS(YEventCryptedString,YEventEx)  {// sizeof() = 128 bits = 16 bytes + size

public: enum    {eventCLASS=EVN_xxBIT_CLASS, eventTYPE=EVN_CRYPTED_STRING};
public:
 static YEvent* Allocate(const void *pEBD, size_t nSize=0, void *pMem=NULL, size_t nMemSize=0, LPCSTR szFileName=0, int nLine=0);
                YEventCryptedString(const void *pData, int nDataSize=0);
public:
 static YEvent* CreateEx(WORD nMessageID, LPCTSTR sz, int nLen=-1, DWORD dwSignature=0, void *pMem=NULL, int nMemSize=0, LPCSTR szFileName=0, int nLine=0);
protected:      YEventCryptedString(WORD nMessageID, LPCTSTR sz, int nLen=-1, DWORD dwSignature=0);
  void*         SetData(LPCTSTR sz, int nLen =-1);
public:
  LPCWSTR       SetString(LPCTSTR sz, int nLen =-1);
  CString       GetString()const;

public: //virtulized functions
  LPTSTR        GetInfo(LPTSTR szEvent, int nLength, int* pnLevel=NULL, int* pnClass=NULL, DWORD* pdwCategory=NULL) const;
  LPTSTR        GetText(LPTSTR szEvent, int nLength) const;
  LPTSTR        GetDump(LPTSTR szEvent, int nLength) const;
public:
  void          Encode(void *pData, size_t nSize, size_t nOffset=0) const;
  void          Decode(void *pData, size_t nSize, size_t nOffset=0) const;
public: //helpers
  static void*  Crypto(void *pData, size_t nSize, size_t nOffset=0);
private://exclude non-used functions
  WORD          SetType(WORD nType){ASSERT(0);return 0;};
};

/////////////////////////////////////////////////////////////////////////////
// classes registration
YEVENT_CLASS_DECLARE(YEventString,YEventEx);
YEVENT_CLASS_DECLARE(YEventCryptedString,YEventEx);

/////////////////////////////////////////////////////////////////////////////
// Inline implementation
#include "EvntStr.inl"

#pragma pack(pop)
#endif//__cplusplus
/////////////////////////////////////////////////////////////////////////////
// C calls
#ifdef __cplusplus
extern "C" {
#define _0 =0
#define _1 =-1
#else
#define _0
#define _1
#endif

int YLogStringEvent(WORD nMessageID, LPCTSTR sz, int nLen _1, DWORD nSignature _0, BOOL bCript _1);

#undef _0
#undef _1
#ifdef __cplusplus
}
#endif

#endif//__EVNTSTR_H
#pragma once
