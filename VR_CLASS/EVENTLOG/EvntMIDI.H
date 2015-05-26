#ifndef __EVNTMIDI_H
#define __EVNTMIDI_H
#include "MM/MMEvent.h"
#include "event.h"
#ifdef  __cplusplus

/////////////////////////////////////////////////////////////////////////////
#define  EVN_MIDI_CLASS   (EVN_64BIT_CLASS)
#define  EVN_MIDI_TYPE    (3)
/////////////////////////////////////////////////////////////////////////////
// class YEventMidi
// Common size:128 bit (16 bytes)
// Data size:   80 bit:
//    2-tag (IN=0,OUT=1,QUERY=2,REJECTED QUERY=3)
//    1-error/data flag
//    5-midi number (0..31)
//   24-midi command
//   32-midi answer or mmsystem_error or data size

class YEventMidi: public YEVENT_CLASS(YEventMidi,YEvent64) {
public: enum    {eventCLASS=EVN_MIDI_CLASS, eventTYPE=EVN_MIDI_TYPE};
public:
  static YEvent* Allocate(const void *pEBD, size_t nSize=0, void *pMem=NULL, size_t nMemSize=0, LPCSTR szFileName=0, int nLine=0);
         YEventMidi(const void* pEBD, int n=0);
public:
         YEventMidi(YMidiActionInfo info);
         ~YEventMidi();

  LPTSTR GetInfo(LPTSTR szEvent, int nLength, int* pnLevel=NULL, int* pnClass=NULL, DWORD* pdwCategory=NULL) const;
  LPTSTR GetText(LPTSTR szEvent, int nLength) const;
  int    Validate() const;

private://exclude non-used functions
  WORD   SetType(WORD nType){ ASSERT(0); return 0;};
  WORD   GetType()const{return 0;};//??
};
/////////////////////////////////////////////////////////////////////////////
// classes registration
YEVENT_CLASS_DECLARE(YEventMidi,YEvent64);

/////////////////////////////////////////////////////////////////////////////
// Inline implementation
#include "evntmidi.inl"

#endif//__cplusplus
/////////////////////////////////////////////////////////////////////////////
// C calls
#ifdef __cplusplus
extern "C" {
#define _0 =0
#else
#define _0
#endif

int YLogEventMidi__action(MIDIACTIONINFO* pInfo);

int YLogEventMidi__query(int nMidi, DWORD dwCommand, DWORD dwAnswer, DWORD mmres _0);
int YLogEventMidi__reject(int nMidi, DWORD dwCommand, DWORD timemout _0);//rejected

int YLogEventMidi__out  (int nMidi, DWORD dwCommand, DWORD mmres _0);
  //YLogEventMidi__send (int nMidi, void* pCommand,  DWORD dwSize, DWORD mmres _0); //TO DO

int YLogEventMidi__in   (int nMidi, DWORD dwAnswer,  DWORD mmtime _0);
int YLogEventMidi__data (int nMidi, void* pAnswer,   DWORD dwSize, DWORD mmtime _0);

#undef  _0
#ifdef __cplusplus
}
#endif

#endif//__EVNTMIDI_H
#pragma once
