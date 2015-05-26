#ifndef __EVNTAPP_H
#define __EVNTAPP_H
#include "event.h"
#ifdef  __cplusplus

/////////////////////////////////////////////////////////////////////////////
#define  EVN_APPLICATION_CLASS    (EVN_64BIT_CLASS)
#define  EVN_APPLICATION_TYPE     (2)
/////////////////////////////////////////////////////////////////////////////
// Class YEventChannel
class YEventApplication : public YEVENT_CLASS(YEventApplication,YEvent64) {
//WORD   m_nClass:2; = EVN_64BIT_CLASS (2)
//WORD   m_nType:4;  = EVN_APPLICATION_TYPE (2)  
//WORD   m_nMsec:10;
//WORD   m_nData;    // nMessage
//time_t m_tTime;
//DWORD  m_dwData[2];// { char[8] | int[2] }
public: enum    {eventCLASS=EVN_APPLICATION_CLASS, eventTYPE=EVN_APPLICATION_TYPE};
public:
  static YEvent* Allocate(const void *pEBD, size_t nSize=0, void *pMem=NULL, size_t nMemSize=0, LPCSTR szFileName=0, int nLine=0);
  YEventApplication(const void* pEBD, int n=0);
public:
  YEventApplication();
  YEventApplication(UINT nMessage, const char* psz, time_t tTime, WORD nMsec=0);
  YEventApplication(UINT nMessage, int n1, int n2, time_t tTime, WORD nMsec=0);
  YEventApplication(UINT nMessage, const char* psz);
  YEventApplication(UINT nMessage, int n1=0, int n2=0);
  ~YEventApplication();

  UINT   SetMessage(UINT nMessage);
  UINT   GetMessage() const;

  const char* SetString(const char* psz);
  char*  GetString(char* psz) const;

  LPTSTR GetText(LPTSTR szEvent, int nLength) const;
  LPTSTR GetInfo(LPTSTR szEvent, int nLength, int* pnLevel=NULL, int* pnClass=NULL, DWORD* pdwCategory=NULL) const;
  int    Validate() const;

private://exclude non-used functions
  WORD   SetType(WORD nType){ASSERT(0);return 0;};
};
/////////////////////////////////////////////////////////////////////////////
// classes registration
YEVENT_CLASS_DECLARE(YEventApplication,YEvent64);

/////////////////////////////////////////////////////////////////////////////
// Inline implementation
#include "evntapp.inl"

#endif//__cplusplus
/////////////////////////////////////////////////////////////////////////////
// C calls
#ifdef __cplusplus
extern "C" {
#endif

int YLogApplicationEventIC(int nMessage, int nData, int nCase);//string case and data
int YLogApplicationEventII(int nMessage, int n1, int n2);
int YLogApplicationEventS(int nMessage, const char* szMessage);

#ifdef __cplusplus
}
#endif


#endif//__EVNTCHAN_H
#pragma once
