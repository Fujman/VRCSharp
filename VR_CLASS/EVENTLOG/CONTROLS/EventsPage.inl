#include "FS/v_malloc.h"
#include "EVENTLOG/evntchan.h"

//=======CEventsPage class=========================
inline void CEventsPage::SetNumber(ULONG nPage) {
  m_nPage = nPage;
}
//-----------
inline ULONG  CEventsPage::GetNumber()const {
  return m_nPage;
}
//---------------------------------------
inline void CEventsPage::SetNumEvents(ULONG nEvents){
  ASSERT(nEvents<MAX_OFFSETS+1);
  m_nEvents = nEvents;
}
//-----------
inline ULONG CEventsPage::GetNumEvents()const {
  ASSERT(m_nEvents<MAX_OFFSETS+1);
  return m_nEvents;
}
//---------------------------------------
inline void   CEventsPage::SetLoaded(BOOL bLoaded) {
  m_bLoaded = bLoaded;
}
//-----------
inline void CEventsPage::SetIdent(BOOL bIdent) {
  m_bIdent  = bIdent;
}
//---------------------------------------
inline BOOL   CEventsPage::IsLoaded()const {
  return m_bLoaded;
}
//-----------
inline BOOL   CEventsPage::IsIdent()const {
  return m_bIdent;
}
//---------------------------------------
inline ULONG  CEventsPage::GetDataSize()const {
  return PAGEDATASIZE;
}
//-----------
inline void CEventsPage::PrepareData(const BYTE* pData) {
  m_pData  = (BYTE*)pData;
}
//-----------
inline void CEventsPage::PrepareOffsets(const WORD* pData) {
  m_pawEvOffsets  = (WORD*)pData;
}
//-----------
inline void CEventsPage::SetData(const BYTE *pData) {
  ASSERT(m_pData);
  ASSERT(pData);
  if(!m_pData)
    return;
  if(pData)
    memcpy(m_pData,pData,GetDataSize());
//  else m_pData = NULL;
}
//-----------
inline BYTE* CEventsPage::GetData() const{
  return m_pData;
}
//---------------------------------------
inline void CEventsPage::SetOffsets(const WORD* pData) {
  ASSERT(m_pawEvOffsets);//must be prepared
  ASSERT(pData);
  if(!m_pawEvOffsets)
    return;
  if(pData)
    memcpy(m_pawEvOffsets,pData,MAX_OFFSETS*sizeof(WORD));
//  else m_pawEvOffsets = NULL;
}
//-----------
inline WORD* CEventsPage::GetOffsets() const{
  return m_pawEvOffsets;
}
//---------------------------------------
inline BOOL CEventsPage::SetFirstEvOffset(WORD wOffset) {
  m_wStartOffset  = wOffset;
  return TRUE;
}
//-----------
inline WORD CEventsPage::GetFirstEvOffset() {  
  return m_wStartOffset;
}
//---------------------------------------
inline void CEventsPageArray::_Empty() {
  m_bEmpty =  TRUE;
  m_nFirstPageNum   = 0;
  m_nFirstPageIndex = 0;
  m_nLastPageNum    = 0;
  m_nLastPageIndex  = 0;
  
  m_dwEventsCount     = 0;
}

inline void CEventsPageArray::_Empty2() {
  m_bEmpty =  TRUE;
  
  m_dwEventsCount     = 0;
}
//=======CEventsPage Array class===================
inline BOOL CEventsPageArray::IsEmpty()const { 
  return m_bEmpty;
} 

inline ULONG	CEventsPageArray::GetPagesNum()const {
  return m_nPages;
}

inline ULONG CEventsPageArray::GetEventsCount()const {
  return m_dwEventsCount;
}

inline ULONG CEventsPageArray::GetPageSize() const {
  return m_nPageSize;
}
//---------------------------------------
inline void	CEventsPageArray::SetFirstPageIndex(ULONG nFirst) {
  m_nFirstPageIndex = nFirst;
}
//-----------
inline ULONG	CEventsPageArray::GetFirstPageIndex() const{
  return m_nFirstPageIndex;
}
//---------------------------------------
inline void	CEventsPageArray::SetFirstPageNum(ULONG nFirst) {
  m_nFirstPageNum = nFirst;
}
//-----------
inline ULONG	CEventsPageArray::GetFirstPageNum() const{
  return m_nFirstPageNum;
}
//---------------------------------------
inline void	CEventsPageArray::SetLastPageIndex(ULONG nLast) {
  m_nLastPageIndex = nLast;
}
//-----------
inline ULONG	CEventsPageArray::GetLastPageIndex() const{
  return m_nLastPageIndex;
}
//---------------------------------------
inline void	CEventsPageArray::SetLastPageNum(ULONG nLast) {
  m_nLastPageNum = nLast;
}
//-----------
inline ULONG	CEventsPageArray::GetLastPageNum() const{
  return m_nLastPageNum;
}
//---------------------------------------
inline ULONG CEventsPageArray::GetNextPageIndex(ULONG nCur) const{
  ASSERT(GetPagesNum()>0);
  ASSERT(nCur<GetPagesNum());
  if(nCur == GetPagesNum()-1)
    return 0;
  return ++nCur;
}
//-----------
inline ULONG CEventsPageArray::GetPrevPageIndex(ULONG nCur) const{
  ASSERT(GetPagesNum()>0);
  ASSERT(nCur<GetPagesNum());
  if(nCur==0)
    return GetPagesNum()-1;
  return --nCur;
}
//---------------------------------------
inline BOOL CEventsPageArray::IsReplacedFirstPage() const {
  return m_bReplacedFirstPage;
}
//-----------
inline void CEventsPageArray::SetReplacedFirstPage(BOOL bReplace) {
  m_bReplacedFirstPage  = bReplace;
}
//---------------------------------------
inline BOOL CEventsPageArray::_FilterEvent(const YEvent* pEvent, CEventsFilter* pEF) {
  if(pEF && pEvent && pEF->IsUseFilter()) {
    int nLev=0,nClass=0;
    DWORD dwCat=0;
    pEvent->GetInfo(NULL,0,&nLev,&nClass,&dwCat);
    DWORD dwShift = 0;
    //type filter
    switch(nClass) {
      case YEvent::classERROR:
        dwShift = (1<<(0+nLev));
        break;
      case YEvent::classWARNING:
        dwShift = (1<<(8+nLev));
    	  break;
      case YEvent::classINFO:
        dwShift = (1<<(16+nLev));
    	  break;
    }
    if((pEF->m_dwEventType&dwShift)==0)
      return FALSE;
    //time filter
    YTime tEvTime = pEvent->GetTimeEx();
    BOOL bTimeInSpan = TRUE;
    if(!pEF->m_tStart.IsInvalid())
      bTimeInSpan = tEvTime>=pEF->m_tStart;
    if(bTimeInSpan && !pEF->m_tStop.IsInvalid())
      bTimeInSpan = tEvTime<=pEF->m_tStop;
    if(!bTimeInSpan)
      return FALSE;
    //channels filter
    WORD wClass = pEvent->GetClass();
    WORD wType = pEvent->GetType();
    if(pEF->IsShowChannelsEvents() && wClass==EVN_CHANNELS_CLASS && wType==EVN_CHANNELS_TYPE) {
      int nChannel =((YEventChannel*)pEvent)->GetChannel();
      ASSERT(nChannel>=0 && nChannel<=CEventsFilter::_MAXCHANNELS);
      if(nChannel>=0 && nChannel<CEventsFilter::_MAXCHANNELS && pEF->m_anChannels[nChannel] == 0)
        return FALSE;
    }

    ASSERT(dwCat==0);
    //     if(nClass!=YEvent::classINFO) { 
    //       return FALSE; 
    //     }
    return TRUE;
  }  
  return TRUE;
}