#include "stdafx.h"
#include "events.h"

//////////////////////////////////////////////////////////////////////////////
// Application specific code /////////////////////////////////////////////////

#if 0
static YEventClassInfo s_event_descriptions[] = {
  {EVN_xxBIT_CLASS,       EVN_GENERIC_UNICODE,  0, 0, YEventString      ::Allocate},
  {EVN_APPLICATION_CLASS, EVN_APPLICATION_TYPE, 0, 0, YEventChannel     ::Allocate},
  {EVN_CHANNELS_CLASS,    EVN_CHANNELS_TYPE,    0, 0, YEventApplication ::Allocate},
  {EVN_MIDI_CLASS,        EVN_MIDI_TYPE,        0, 0, YEventMidi        ::Allocate},
  {EVN_PORTS_CLASS,       -1,                   0, 0, YEventPort        ::Allocate},
  {EVN_16BIT_CLASS,       -1,                   0, 0, YEvent16          ::Allocate},
  {EVN_20BIT_CLASS,       -1,                   0, 0, YEvent20          ::Allocate},
  {EVN_64BIT_CLASS,       -1,                   0, 0, YEvent64          ::Allocate},
  {EVN_xxBIT_CLASS,       -1,                   0, 0, YEventEx          ::Allocate},
{0}};
#endif

#ifndef _DEBUG

YEvent* YEvent::Create(const void *pData, int nDataSize, void *pMem, int nSize, LPCSTR szFileName, int nLine) {
  ASSERT(nDataSize>=0 && nSize>=0);

  const YEventBaseData* pEBD = (const YEventBaseData*)pData;
  YEvent *pEvent = NULL;

  if      (pEBD->GetClass()==EVN_64BIT_CLASS &&
           pEBD->GetType() ==EVN_MIDI_TYPE){
    size_t nObjSize = YEventMidi::SIZE_OF_BASE_DATA;
    if(pMem!=0) pEvent = new(pMem) YEventMidi(pEBD,nDataSize);
    else        pEvent = new YEventMidi(pEBD,nDataSize);

  }else if(pEBD->GetClass()==EVN_20BIT_CLASS)  {
    size_t nObjSize = YEventPort::SIZE_OF_BASE_DATA;
    if((nDataSize!=0 && (UINT)nDataSize<nObjSize) || (pMem!=0 && (UINT)nSize<nObjSize))
      return NULL;
    if(pMem!=0) pEvent = new(pMem) YEventPort(pEBD,nDataSize);
    else        pEvent = new YEventPort(pEBD,nDataSize);

  }else if(pEBD->GetClass()==EVN_64BIT_CLASS &&
           pEBD->GetType() ==EVN_CHANNELS_TYPE){
    size_t nObjSize = YEventChannel::SIZE_OF_BASE_DATA;
    if((nDataSize!=0 && (UINT)nDataSize<nObjSize) || (pMem!=0 && (UINT)nSize<nObjSize))
      return NULL;
    if(pMem!=0) pEvent = new(pMem) YEventChannel(pEBD,nDataSize);
    else        pEvent = new YEventChannel(pEBD,nDataSize);

  }else if(pEBD->GetClass()==EVN_64BIT_CLASS &&
           pEBD->GetType() ==EVN_APPLICATION_TYPE){
    size_t nObjSize = YEventApplication::SIZE_OF_BASE_DATA;
    if(pMem!=0) pEvent = new(pMem) YEventApplication(pEBD,nDataSize);
    else        pEvent = new YEventApplication(pEBD,nDataSize);

  }else if(pEBD->GetClass()==EVN_64BIT_CLASS &&
           pEBD->GetType() ==EVN_LOGFILE_TYPE){
    size_t nObjSize = YEvent64::SIZE_OF_BASE_DATA;
    if(pMem!=0) pEvent = new(pMem) YEvent64(pEBD,nDataSize);
    else        pEvent = new YEvent64(pEBD,nDataSize);
  }
  return pEvent;
}

#endif

