#include "stdafx.h"
//#include "xtest.h"
/*---------------------------------------------------------------------------\
| Class: YEventMidis                       Language: C++     Model: All      |
|----------------------------------------------------------------------------|
| Description:  Make event messages for MIDI
| Derived from: YEvent
| Constructors: default
| Methods:
| Members:
| Note:
\---Last change 12.03.04 15:36-----Copyright (c) 2004, Anton Yavorsky, SRS--*/

#include "mm/MMEvent.h"
#include "xCString.h"
#include "EvntMidi.h"
#include "EventLog.h"

/*message format:                            Type Midi Data Time Error Total,bits
  MIDI1:  B06000  ......  error=24 ; out        3    5   24         32    64
  MIDI1:  ......  0000FF  size=1   ; in         3    5   24         32

  MIDI1:  B06000  ......           ; out        3    5   24           
  MIDI1:  ......  B06041           ; in         3    5   24  32?
  MIDI1:  B06000  B06041           ; query      3    5   24         24

  MIDI1:  B06000  ??????  rejected ; query      3    5   24  32       
  MIDI1:  B06000  ??????  error=24 ; query      3    5   24         32
*/

//reverse commands for output by %X
#define PACKET(dw) MIDI_PACKET(MIDI_PACKET_DATA2(dw),MIDI_PACKET_DATA1(dw),MIDI_PACKET_CMD(dw))

LPTSTR  YEventMidi::GetInfo(LPTSTR szEvent, int nLength, int* pnLevel/*NULL*/, int* pnClass/*NULL*/, DWORD* pdwCategory) const
{
  YMidiActionInfo info(GetData32(0),GetData32(1));

  BOOL bError = (!info.isSuccess() || (info.isIn() && !info.isPacket()));

  if(pnClass!=NULL) *pnClass = bError?classERROR:classINFO;
  if(pnLevel!=NULL) *pnLevel = info.isQuery()?31:30;
  if(pdwCategory!=NULL) *pdwCategory = 0;//TO DO

  if(nLength<60)
    return NULL;

  TCHAR acTime[28]; GetTime(acTime,28);

  CString szMessage = FormatString(_T("%s     "),acTime);
  szMessage += FormatString(_T("MIDI<%d>:  "),info.GetMidi());
  if(info.isQuery()) {
    if(info.isSuccess())    szMessage += FormatString(_T("%06.6X  %06.6X"),PACKET(info.GetCommand()),PACKET(info.GetAnswer()));
    else if(info.isFailed())szMessage += FormatString(_T("%06.6X  ??????  error=%u"),PACKET(info.GetCommand()),info.GetMMError());
    else                    szMessage += FormatString(_T("%06.6X  ??????  rejected"),PACKET(info.GetCommand()));
  }
  if(info.isOut()) {
    if(info.isSuccess())    szMessage += FormatString(_T("%06.6X  ......"),PACKET(info.GetCommand()));
    else                    szMessage += FormatString(_T("%06.6X  ......  error=%u"),PACKET(info.GetCommand()),info.GetMMError());
  }
  if(info.isIn()) {
    if(info.isPacket())     szMessage += FormatString(_T("......  %06.6X"),PACKET(info.GetAnswer()));
    else                    szMessage += FormatString(_T("......  %06.6X  size=%u"),PACKET(info.GetAnswer()),info.GetSize());
  }

  if(szMessage.GetLength()+1 > nLength)
    return NULL;

  _tcscpy(szEvent,szMessage);
  return szEvent;
}

LPTSTR YEventMidi::GetText(LPTSTR szEvent, int nLength) const 
{
  return GetInfo(szEvent, nLength);
}

int  YEventMidi::Validate()const{
  if(YEvent64::Validate()==FALSE)
    return FALSE;
  return TRUE;
}

int YLogEventMidi__action(MIDIACTIONINFO* pInfo)
{
  YMidiActionInfo info(pInfo->dw[0],pInfo->dw[1]);
  YEventMidi ev(info);
  return YEvent::GetLog()->PutEvent(ev);
}

int YLogEventMidi__query(int nMidi, DWORD dwCommand, DWORD dwAnswer, DWORD mmres)
{
  YMidiActionInfo info; info.query(nMidi,dwCommand,dwAnswer,mmres);
  YEventMidi ev(info); 
  return YEvent::GetLog()->PutEvent(ev);
}

int YLogEventMidi__reject(int nMidi, DWORD dwCommand, DWORD timemout)
{
  YMidiActionInfo info; info.query(nMidi,dwCommand,timemout);
  YEventMidi ev(info);
  return YEvent::GetLog()->PutEvent(ev);
}

int YLogEventMidi__out  (int nMidi, DWORD dwCommand, DWORD mmres)
{
  YMidiActionInfo info; info.out(nMidi,dwCommand,mmres);
  YEventMidi ev(info);
  return YEvent::GetLog()->PutEvent(ev);
}

int YLogEventMidi__in   (int nMidi, DWORD dwAnswer,  DWORD mmtime)
{
  YMidiActionInfo info; info.in(nMidi,dwAnswer,mmtime);
  YEventMidi ev(info);
  return YEvent::GetLog()->PutEvent(ev);
}

int YLogEventMidi__data (int nMidi, void* pAnswer,   DWORD dwSize, DWORD mmtime)
{
  YMidiActionInfo info; info.in(nMidi,pAnswer,dwSize,mmtime);
  YEventMidi ev(info);
  return YEvent::GetLog()->PutEvent(ev);
}

// dynamic construction //////////////////////////////////////////////////////
#include "xnew.h"//*{

YEvent* YEventMidi::Allocate(const void *pEBD, size_t nDataSize, void *pMem, size_t nSize, LPCSTR szFileName, int nLine)
{
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  if(szFileName!=NULL)
    return new(szFileName, nLine, pMem, nSize, pEBD, nDataSize) YEventMidi(pEBD,nDataSize);
#endif
  return new(pMem, nSize, pEBD, nDataSize) YEventMidi(pEBD,nDataSize);
}

#include "xnew.h"//}*

YEVENT_CLASS_IMPLEMENT(YEventMidi,YEvent64);

////////////////////////////////////////////////////////////////////////////////
#ifdef XTESTROUTINE
#include "EventLog.h"
#include "os/ythread.h"
#include <mmsystem.h>
static TEST(YMidiActionInfo info)
{
  YEventMidi ev(info);  ev.SetTime();
  char sz[128];
  ev.GetText(sz,sizeof(sz));
  TRACE("%s\n",sz);
}

static YEventsProtocol theProtocol;
static LONG dwCounter = 0;

static int proc(void* p)
{
  while(1) {
    DWORD dw = InterlockedIncrement(&dwCounter);
    dw = MIDI_PACKET(
      ((BYTE*)&dw)[2],
      ((BYTE*)&dw)[1],
      ((BYTE*)&dw)[0]
    );

    YMidiActionInfo info; info.out((int)p,dw,0);
    YEventMidi ev(info);
    theProtocol.PutEvent(ev);
  }
  return 0;
}

XTESTROUTINE(YEventMidi)
{
  theProtocol.Open("XTESTROUTINE(YEventMidi)",8*1024*1024);
  {
    YSimpleThread 
      t1(proc,(void*)1,TRUE),
      t2(proc,(void*)2,TRUE),
      t3(proc,(void*)3,TRUE),
      t4(proc,(void*)4,TRUE);
    ::Sleep(15*1000);
  }
  return;

  YMidiActionInfo info;
  DWORD dwCommand = MIDI_PACKET(0xB0,0x60,0x88);
  DWORD dwAnswer  = MIDI_PACKET(0xB0,0x60,0x41);
  DWORD dwData    = MIDI_PACKET(0xD0,0xFF,0x00);
  MMRESULT mmres;
  int nMidi = 7;

  TEST( info.query(nMidi,dwCommand,0,mmres=24) );
  TEST( info.query(nMidi,dwCommand,2000/*to*/) );
  TEST( info.query(nMidi,dwCommand,dwAnswer,0) );

  TEST( info.out(nMidi,dwCommand,mmres=24) );
  TEST( info.out(nMidi,dwCommand,mmres=0) );

  TEST( info.in(nMidi,&dwData,2,12345) );//data
  TEST( info.in(nMidi,dwAnswer,12345) );
}

#endif

