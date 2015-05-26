#ifndef __EVNTPORT_H
#define __EVNTPORT_H
#include "event.h"
#ifdef  __cplusplus

/////////////////////////////////////////////////////////////////////////////
#define  EVN_PORTS_CLASS   (EVN_20BIT_CLASS)
/////////////////////////////////////////////////////////////////////////////
// class YEventPort
// Common size: 64 bit (8 bytes)
// Data size:   20 bit:
//    1-tag,
//   11-port number (0x000...0x7FF)
//    8-data
class YEventPort: public YEVENT_CLASS(YEventPort,YEvent20) {
//WORD   m_nClass:2; = EVN_20BIT_CLASS (1)
//WORD   m_nType:4;    data bits 16..19 = ioport:3, tag:1
//WORD   m_nMsec:10;
//WORD   m_nData;      data bits  0..15 = byte:8, ioport:8
//time_t m_tTime;
public: enum    {eventCLASS=EVN_PORTS_CLASS, eventTYPE=0};
public:
  static YEvent* Allocate(const void *pEBD, size_t nSize=0, void *pMem=NULL, size_t nMemSize=0, LPCSTR szFileName=0, int nLine=0);
         YEventPort(const void* pEBD, int n=0);
public:
         YEventPort();
         ~YEventPort();
  void   in(WORD nPort,BYTE bData);
  void   out(WORD nPort,BYTE bData);
  void   in(WORD nPort,BYTE bData,time_t tTime,WORD nMsec=0);
  void   out(WORD nPort,BYTE bData,time_t tTime,WORD nMsec=0);
  BYTE   GetByte()const;
  BYTE   SetByte(BYTE bData);
  WORD   GetPort()const;
  WORD   SetPort(WORD nPort);
  int    isIn()const;
  int    isOut()const;
  LPTSTR  GetText(LPTSTR szEvent, int nLength) const;
  int    Validate() const;

private://exclude non-used functions
  WORD   SetType(WORD nType){return 0;};
  WORD   GetType()const{return 0;};//??
};
/////////////////////////////////////////////////////////////////////////////
// classes registration
YEVENT_CLASS_DECLARE(YEventPort,YEvent20);

/////////////////////////////////////////////////////////////////////////////
// Inline implementation
#include "evntport.inl"

#endif//__cplusplus
/////////////////////////////////////////////////////////////////////////////
// C calls
#ifdef __cplusplus
extern "C" {
#endif

int YLogInPortEvent(WORD nPort, BYTE bData);
int YLogOutPortEvent(WORD nPort, BYTE bData);

#ifdef __cplusplus
}
#endif

#endif//__EVNTPORT_H
#pragma once
