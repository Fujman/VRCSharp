#ifndef __EVNTCHAN_H
#define __EVNTCHAN_H
#include "event.h"
#ifdef  __cplusplus

/////////////////////////////////////////////////////////////////////////////
#define  EVN_CHANNELS_CLASS    (EVN_64BIT_CLASS)
#define  EVN_CHANNELS_TYPE     (1)
/////////////////////////////////////////////////////////////////////////////
// Class YEventChannel
class YEventChannel: public YEVENT_CLASS(YEventChannel,YEvent64) {
//WORD   m_nClass:2; = EVN_64BIT_CLASS (2)
//WORD   m_nType:4;  = EVN_CHANNELS_TYPE (1)
//WORD   m_nMsec:10;
//WORD   m_nData;    // nMessage
//time_t m_tTime;
//DWORD  m_dwData[2];// nChannel:16, { char[6] | bcd[12] | short,int }
public: enum    {eventCLASS=EVN_CHANNELS_CLASS, eventTYPE=EVN_CHANNELS_TYPE};
public:
  static YEvent* Allocate(const void *pEBD, size_t nSize=0, void *pMem=NULL, size_t nMemSize=0, LPCSTR szFileName=0, int nLine=0);
  YEventChannel(const void* pEBD, int n=0);
public:
  YEventChannel();
  YEventChannel(int nChannel, UINT nMessage, int nData, short nData16, time_t tTime, WORD nMsec);
  YEventChannel(int nChannel, UINT nMessage, int nData=0, short nData16=0);
  YEventChannel(int nChannel, UINT nMessage, const char* sz, time_t tTime, WORD nMsec);
  YEventChannel(int nChannel, UINT nMessage, const char* sz);
  ~YEventChannel();

  UINT   SetMessage(UINT nMessage);
  int    SetChannel(int nChannel);
  int    SetData(int nData, short nData16=0);
  UINT   GetMessage() const;
  int    GetChannel() const;
  int    GetData(short* pData16=NULL) const;
  const char* SetString(const char* sz);
  char*  GetString(char* sz) const;
  const char* SetBCDString(const char* sz); // 11 chars max (12 with zero)
  char* GetBCDString(char* sz) const;

  LPTSTR GetText(LPTSTR szEvent, int nLength) const;
  LPTSTR GetInfo(LPTSTR szEvent, int nLength, int* pnLevel=NULL, int* pnClass=NULL, DWORD* pdwCategory=NULL) const;
  int    Validate() const;

private://exclude non-used functions
  WORD   SetType(WORD nType){return 0;};
};
/////////////////////////////////////////////////////////////////////////////
// classes registration
YEVENT_CLASS_DECLARE(YEventChannel,YEvent64);

/////////////////////////////////////////////////////////////////////////////
// Inline implementation
#include "evntchan.inl"

#endif//__cplusplus
/////////////////////////////////////////////////////////////////////////////
// C calls
#ifdef __cplusplus
extern "C" {
#endif

int YLogChannelEventIC(int nChannel, int nMessage, int nData, short nCase);
int YLogChannelEventIW(int nChannel, int nMessage, int nData, short nData2);
int YLogChannelEventI(int nChannel, int nMessage, int nData);
int YLogChannelEventS(int nChannel, int nMessage, LPCTSTR sz);
int YLogChannelEventBCD(int nChannel, int nMessage, const char* szMessage);

#ifdef __cplusplus
}
#endif


#endif//__EVNTCHAN_H
#pragma once
