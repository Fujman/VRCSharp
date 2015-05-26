// EventsFilter.cpp: implementation of the CEventsFilter class.
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
//#include "srslogview.h"
#include "EventsFilter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void SetBits(DWORD& dwTarget,DWORD dwVarBits,DWORD dwByteIndWord,DWORD dwVar) {
  DWORD n = (1<<dwVarBits)-1;
  n <<= (dwByteIndWord*dwVarBits);
  dwVar <<= (dwByteIndWord*dwVarBits);
  dwTarget = (dwTarget & ~(n)) | dwVar;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CEventsFilter::CEventsFilter() {
  m_dwEventType = 0;
  m_tStart      = YTime::INVALID();
  m_tStop       = YTime::INVALID();
//  m_nChannels   = ((__int64)1)<<64;
  
  m_bUseFilter  = FALSE;
  m_bShowChsEvs = FALSE;
  m_dwLevWarn   = 0;
  m_dwLevInfo   = 0;
  m_dwLevErr    = 0;
}
//-----------
CEventsFilter::~CEventsFilter() 
{

}
//---------------------------------------
void CEventsFilter::SetUseFilter(BOOL bUse) {
  m_bUseFilter = bUse;
}
//-----------
void CEventsFilter::SetStartTime(YTime tTime) {
  m_tStart = tTime;
}
//-----------
void CEventsFilter::SetStopTime (YTime tTime) {
  m_tStop = tTime;
}
//-----------
void CEventsFilter::SetLevelWarningFlags(DWORD dwLevelsBits) {
  ASSERT(dwLevelsBits<256);
  m_dwLevWarn = dwLevelsBits;
  SetBits(m_dwEventType,8,1,dwLevelsBits);
}
//-----------
void CEventsFilter::SetLevelInfoFlags(DWORD dwLevelsBits) {
  ASSERT(dwLevelsBits<256);
  m_dwLevInfo = dwLevelsBits;
  SetBits(m_dwEventType,8,2,dwLevelsBits);
}
//-----------
void CEventsFilter::SetLevelErrorFlags(DWORD dwLevelsBits) {
  ASSERT(dwLevelsBits<256);
  m_dwLevErr = dwLevelsBits;
  SetBits(m_dwEventType,8,0,dwLevelsBits);
}
//-----------
// void CEventsFilter::_SetEventType(DWORD &dwTarget, DWORD dwErrFlags, 
//                                   DWORD dwWarnFlags, DWORD dwInfoFlags) 
// {
//   SetBits(dwTarget,8,0,dwErrFlags);
//   SetBits(dwTarget,8,1,dwWarnFlags);
//   SetBits(dwTarget,8,2,dwInfoFlags);
// }
//---------------------------------------------------
BOOL CEventsFilter::SetChannelsList(const YSRSChannelsList*  paChannels) {
  ASSERT(paChannels);
  if(paChannels) {
    m_aChannels = *paChannels;
    for(int i=0;i<_MAXCHANNELS;++i) {
      m_anChannels[i]=0;
    }
    int nChannels = m_aChannels.GetChannelsNum();
    for(i=0;i<nChannels;++i) {
      ASSERT(m_aChannels.GetChannel(i)>=0 && m_aChannels.GetChannel(i)<_MAXCHANNELS);
      if(m_aChannels.GetChannel(i)>=0 && m_aChannels.GetChannel(i)<_MAXCHANNELS)
        m_anChannels[m_aChannels.GetChannel(i)]=1;
    }
    return TRUE;
  }
  return FALSE;
}

//-----------
BOOL CEventsFilter::GetChannelsList(YSRSChannelsList* paChannels) const {
  ASSERT(paChannels); 
  if(paChannels) {
    *paChannels=m_aChannels; 
    return TRUE;
  } 
  return FALSE;
}
