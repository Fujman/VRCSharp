#include "EventsPage.h"
#include "EVENTLOG/EvntChan.h"
#include "EVENTLOG/EvntApp.h"

inline ULONG CEventsListDlg::GetPageSize() const {
  return m_nPageDataSize;
}

inline ULONG CEventsListDlg::GetLogSize() const {
  return m_nLogSize;
}

inline void CEventsListDlg::SetFirstOffset(ULONG nOffset) {
  ASSERT(nOffset!=-1);
  if(nOffset==-1)
    ++nOffset;
  m_nFirstOffset      = nOffset;
  m_nFirstPageOffset  = nOffset & ~(GetPageSize()-1);
}

inline ULONG CEventsListDlg::GetFirstPageOffset() const{
  return m_nFirstPageOffset;
}

inline ULONG CEventsListDlg::GetFirstOffset() const{
  return m_nFirstOffset;
}

//DEL inline ULONG CEventsListDlg::GetNextPageOffset(ULONG nOffset) const{
//DEL   nOffset = nOffset - nOffset%GetPageSize();
//DEL   if((nOffset+GetPageSize()) > GetLogSize())
//DEL     return 0;
//DEL   else return nOffset+GetPageSize();
//DEL }

inline BOOL CEventsListDlg::IsReplacedFirstPage()const {
  return m_paPages->IsReplacedFirstPage();
}

BOOL CEventsListDlg::_FindAndLoadEvent(ULONG nIndex) {
  if(nIndex==m_ncachedEv && m_pcachedEv) {
    //TRACE("+  in cache ID:%d\n",nIndex);
    return TRUE; //event in cache!
  }
  if(m_pcachedEv) {
    //delete m_pcachedEv, m_pcachedEv = NULL, m_ncachedEv = ULONG_MAX;
    YEvent::Delete(m_pcachedEv,m_Buf);
    m_pcachedEv = NULL;
    m_ncachedEv = ULONG_MAX;
  }
  //TRACE("+  not in cache ID:%d\n",nIndex);
#ifdef DEBUG_EL
  ULONG nPageNum=0;
  m_pcachedEv = m_paPages->FindEvent(nIndex,nPageNum,m_Buf,STACK_LEN);
  if(m_pcachedEv) {
    m_ncachedEv = nIndex;
    m_szEvNumText.Format("%6d %10d    ",nPageNum,nIndex);
    return TRUE;
  }
  else m_ncachedEv = ULONG_MAX;
#else
  m_pcachedEv = m_paPages->FindEvent(nIndex,m_Buf,STACK_LEN);
  if(m_pcachedEv) {
    m_ncachedEv = nIndex;
    return TRUE;
  }
  else m_ncachedEv = ULONG_MAX;
#endif
  return FALSE;
}
//---------------------------------------
BOOL CEventsListDlg::_FindAndLoadEventF(ULONG nIndex) {
  if(nIndex==m_ncachedFEv && m_pcachedFEv) {
    //TRACE("++  in cache ID:%d\n",nIndex);
    return TRUE; //event in cache!
  }
  if(m_pcachedFEv) {
    //delete m_pcachedEv, m_pcachedEv = NULL, m_ncachedEv = ULONG_MAX;
    YEvent::Delete(m_pcachedFEv,m_BufFEv);
    m_pcachedFEv = NULL;
    m_ncachedFEv = ULONG_MAX;
  }
  //TRACE("++  not in cache ID:%d\n",nIndex);
#ifdef DEBUG_EL
  ULONG n;
  m_pcachedFEv = m_paPages->FindEvent(nIndex,n,m_BufFEv,STACK_LEN);
#else
  m_pcachedFEv = m_paPages->FindEvent(nIndex,m_BufFEv,STACK_LEN);
#endif
  if(m_pcachedFEv) {
    m_ncachedFEv = nIndex;
    return TRUE;
  }
  else m_ncachedFEv = ULONG_MAX;
  return FALSE;
}
//---------------------------------------
BOOL CEventsListDlg::GetEventTextF(ULONG nIndex, int nBufSize, LPTSTR lpszText, int& nTextSize) {
  if(_FindAndLoadEventF(nIndex)) {
    m_pcachedFEv->GetInfo(lpszText,nBufSize);
    memmove(lpszText,lpszText+30,nBufSize-30+1);//TO DO: make extended flags in GetInfo
    return TRUE;
  }
#ifdef DEBUG_EL
  ASSERT(0);
#endif //DEBUG_EL
  return FALSE;
}
//---------------------------------------
BOOL CEventsListDlg::GetEventText(ULONG nIndex, int nBufSize, LPTSTR lpszText, int& nTextSize) {
  if(_FindAndLoadEvent(nIndex)) {
    m_pcachedEv->GetInfo(lpszText,nBufSize);
//     if(lpszText[31]=='#' && lpszText[34]==':')
//       memmove(lpszText,lpszText+36,nBufSize-36+1);//TO DO: make extended flags in GetInfo
//     else
//       memmove(lpszText,lpszText+32,nBufSize-32+1);//TO DO: make extended flags in GetInfo
    memmove(lpszText,lpszText+30,nBufSize-30+1);//TO DO: make extended flags in GetInfo
    return TRUE;
  }
#ifdef DEBUG_EL
  ASSERT(0);
#endif //DEBUG_EL
  return FALSE;
}
//---------------------------------------
BOOL CEventsListDlg::GetEventID(ULONG nIndex, UINT& nID) {
  if(_FindAndLoadEvent(nIndex)) {
    YEventBaseData* pEBD = m_pcachedFEv;
    if(!pEBD)
      return FALSE;
    if(pEBD->GetClass()==EVN_APPLICATION_CLASS && pEBD->GetType()==EVN_APPLICATION_TYPE) {
      nID  = ((YEventApplication*)pEBD)->GetMessageID();
      return TRUE;
    }
    if(pEBD->GetClass()==EVN_CHANNELS_CLASS && pEBD->GetType()==EVN_CHANNELS_TYPE) {
      nID  = ((YEventChannel*)pEBD)->GetMessageID();
      return TRUE;
    }
    return FALSE;
  }
 #ifdef DEBUG_EL
   ASSERT(0);
 #endif //DEBUG_EL
  return FALSE;
}

BOOL CEventsListDlg::GetEventIDF(ULONG nIndex, UINT& nID) {
  if(_FindAndLoadEventF(nIndex)) {
    YEventBaseData* pEBD = m_pcachedFEv;
    if(!pEBD)
      return FALSE;
    if(pEBD->GetClass()==EVN_APPLICATION_CLASS && pEBD->GetType()==EVN_APPLICATION_TYPE) {
      nID  = ((YEventApplication*)pEBD)->GetMessageID();
      return TRUE;
    }
    if(pEBD->GetClass()==EVN_CHANNELS_CLASS && pEBD->GetType()==EVN_CHANNELS_TYPE) {
      nID  = ((YEventChannel*)pEBD)->GetMessageID();
      return TRUE;
    }
    return FALSE;
  }
#ifdef DEBUG_EL
  ASSERT(0);
#endif //DEBUG_EL
  return FALSE;
}

BOOL CEventsListDlg::GetEventTime(ULONG nIndex, YTime& tTime) {
  if(_FindAndLoadEvent(nIndex)) {
    YEventBaseData* pEBD = m_pcachedEv;
    if(!pEBD)
      return FALSE;
    tTime = pEBD->GetTimeEx();
    return  TRUE;
  }
#ifdef DEBUG_EL
  ASSERT(0);
#endif //DEBUG_EL
  return FALSE;
}

BOOL CEventsListDlg::GetEventTimeF(ULONG nIndex, YTime& tTime) {
  if(_FindAndLoadEventF(nIndex)) {
    YEventBaseData* pEBD = m_pcachedFEv;
    if(!pEBD)
      return FALSE;
    
    tTime = pEBD->GetTimeEx();
    return  TRUE;
  }
#ifdef DEBUG_EL
  ASSERT(0);
#endif //DEBUG_EL
  return FALSE;
}

BOOL CEventsListDlg::GetEventChannel(ULONG nIndex, int nBufSize, LPTSTR lpszText, int& nTextSize) {
  if(_FindAndLoadEvent(nIndex)) {
    m_pcachedEv->GetInfo(lpszText,nBufSize);
    if(lpszText[31] == '#') {
      if(lpszText[31+3]==':') {
        _tcsncpy(lpszText,lpszText+32,2);
        lpszText[2] = '\0';
        return TRUE;
      }
    }
  }

  return FALSE;
}

//CMessagesArbiter::CMessage::CMessage()