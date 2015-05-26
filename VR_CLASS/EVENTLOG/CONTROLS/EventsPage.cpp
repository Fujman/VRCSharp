// EventsPage.cpp: implementation of the CEventsPage class.
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "EventsPage.h"
#include "EventsFilter.h"
#include "EVENTLOG/event.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define STACK_LEN   ((MAX_PATH+1)*sizeof(wchar_t)+sizeof(YEvent64))//542

#ifdef DEBUG_EL
#include "yTime.h"
#endif //DEBUG_EL

//////////////////////////////////////////////////////////////////////
// CEventsPage
//////////////////////////////////////////////////////////////////////

CEventsPage::CEventsPage():
       m_nPage(0),
       m_bLoaded(FALSE),
       m_bIdent(FALSE),
       m_wStartOffset(0),
       m_nEvents(0),
       m_pData(NULL),
       m_pawEvOffsets(NULL)
{
}
//-----------
CEventsPage::~CEventsPage() {
//  if(m_pawEvOffsets) {
//    delete[] m_pawEvOffsets; m_pawEvOffsets = NULL;
//  }
//  if(m_pData) {
//    delete[] m_pData; m_pData = NULL;
//  }
}

CEventsPage&  CEventsPage::operator=(const CEventsPage& ep) {
  m_nPage   = ep.m_nPage;
  m_nEvents = ep.m_nEvents;
  m_bLoaded = ep.m_bLoaded;
  m_bIdent  = ep.m_bIdent;
  m_wStartOffset  = ep.m_wStartOffset;
  SetOffsets(ep.m_pawEvOffsets);
  SetData(ep.m_pData);
  return *this;
}

//=======================================================
//====== CEventsPageArray ===============================
CEventsPageArray::CEventsPageArray(int nSize,BOOL bCache) {
  ASSERT(nSize>0);
  ReInit();
  _Empty();
  m_bCache  = bCache;
  m_nPages        = nSize;
  m_paEP          = new CEventsPage[m_nPages];
  m_pPagesData    = new BYTE[nSize*CEventsPage::PAGEDATASIZE];
  m_pOffsetsData  = new WORD[nSize*CEventsPage::MAX_OFFSETS];
  for(int i=0;i<nSize;++i) {
    m_paEP[i].PrepareData   (m_pPagesData+i*CEventsPage::PAGEDATASIZE);
    m_paEP[i].PrepareOffsets(m_pOffsetsData+i*CEventsPage::MAX_OFFSETS);
    //m_paEP[i].SetOffsets(m_pOffsetsData+i*CEventsPage::MAX_OFFSETS);
  }
}
//-----------
void CEventsPageArray::ReInit() {
  _Empty2();
  SetPageSize(CEventsPage::PAGEDATASIZE);
  SetReplacedFirstPage(FALSE);
}
//-----------
CEventsPageArray::~CEventsPageArray() {
  delete[] m_paEP,        m_paEP = NULL;
  delete[] m_pPagesData,  m_pPagesData = NULL;
  delete[] m_pOffsetsData,m_pOffsetsData = NULL;
}
//-----------
BOOL  CEventsPageArray::__SetAtPage(ULONG nIndex, CEventsPage* ppage) {
  ASSERT(m_paEP);
  ASSERT(nIndex <GetPagesNum());
  if(nIndex <GetPagesNum()) {
    m_paEP[nIndex] = *ppage;
    return TRUE;
  }
  return FALSE;
}

inline YEvent* CEventsPageArray::_GetEvent(const BYTE* pPage, ULONG nOffset, void* pMem/*NULL*/, int nSize/*0*/) {
  ULONG  nEventMaxSize = GetPageSize() - nOffset;
  YEvent *pev = YEvent::Create(pPage+nOffset,nEventMaxSize,pMem,nSize DEBUG_NEW_FILE_LINE);
  if(pev==NULL)
    return NULL;   // Bad Event
  int isGood = pev->Validate();
  ASSERT(isGood);
  if(!isGood) { 
    YEvent::Delete(pev,pMem);
    pev = NULL; 
  }
  return pev; // ATTENTION!: must be deleted in future by operator delete
}

inline YEvent* CEventsPageArray::_GetEventAndNextOffset(const BYTE* pPage, WORD  nOffset, CEventsFilter* pEF, void* pMem/*NULL*/, int nSize/*0*/,WORD& wNextOffset) {
  ASSERT(pPage);
  ASSERT(nOffset!=-1);
  ASSERT(nOffset<GetPageSize());
  YEvent* pThisEvent = NULL;
  if(nOffset<GetPageSize()) {   
    pThisEvent = _GetEvent(pPage,nOffset,pMem,nSize);
    if(pThisEvent==NULL) {
      wNextOffset = 0xFFFF;
      return NULL;
    }
    nOffset += static_cast<WORD>(pThisEvent->GetDataSize());
    if(pEF && !_FilterEvent(pThisEvent,pEF)) {
      YEvent::Delete(pThisEvent,pMem);
      pThisEvent = NULL;
    }
    if(nOffset==GetPageSize()) {
      wNextOffset = 0xFFFF;
      return pThisEvent;
    }

    wNextOffset = nOffset;
    return pThisEvent;//ok!
  }
  wNextOffset = 0xFFFF;
  return NULL;
}

int CEventsPageArray::ScanPage(const BYTE* pData, WORD nStartOffset, ULONG& nEvents, WORD* pCache, CEventsFilter* pEF) {
  ASSERT(pCache);
  BYTE abyBuffer[STACK_LEN];
//  WORD iEvent=0;
  nEvents = 0;
  WORD    nOffset   = nStartOffset;
  WORD    nTmpOffset=0xFFFF;
//  BOOL    bContinue = TRUE;
  YEvent* pEvent    = NULL;
  if(0xFFFF == nOffset) {//check start offset on page (skip header)
    pEvent = _GetEventAndNextOffset(pData,0,NULL,abyBuffer,STACK_LEN,nOffset);//no filter
    #ifdef DEBUG_EL
    ASSERT(nOffset<GetPageSize());
    #endif //DEBUG_EL
    if(pEvent) {
      YEvent::Delete(pEvent,&abyBuffer);
      pEvent = NULL;
    }
    if(0xFFFF == nOffset) {
      ASSERT(!"TODO: empty page ");
      return -1; //error TODO! check event! (maybe 1 event on page (full length))
    }
  }
  do{
    ASSERT(nOffset<GetPageSize());
    pEvent = _GetEventAndNextOffset(pData,nOffset,pEF,abyBuffer,STACK_LEN,nTmpOffset);//filter // get current event and skip to next
    if(pEvent) {
      pCache[nEvents++]= nOffset;
      YEvent::Delete(pEvent,abyBuffer);
    }
    nOffset = nTmpOffset;
  }while(0xFFFF!=nTmpOffset);
  return 0;
}
//------
//--KSN--[2005_07_12 19:27:57] add (experiment)
BOOL CEventsPageArray::GetEventHandle(ULONG nEvID, ULONG& nPage,ULONG& nEventOnPage,void* pMem, int nSize) {
  ULONG nFPI = GetFirstPageIndex();
  ULONG nLPI = GetLastPageIndex();
  int   nItm = GetEventsCount();
  ULONG nEvOnPage = 0;
  ULONG iPage = 0;
  ASSERT(nFPI<=GetPagesNum());
  ASSERT(nLPI<=GetPagesNum());
  BOOL bRun = (nFPI==nLPI);
  for(iPage=nLPI;iPage!=nFPI || bRun;) {
    nItm -= m_paEP[iPage].GetNumEvents();
    ASSERT(nItm>=0);
    if(nItm<=(int)nEvID) {
      nEvOnPage  = nEvID - nItm;
      ASSERT(nEvOnPage<GetEventsCount()); //nEvOnPage<=0
      nPage = m_paEP[iPage].GetNumber();
      return TRUE;
    }
    if(bRun)
      break;
    iPage = GetPrevPageIndex(iPage);
    if(iPage==nFPI)
      bRun=TRUE;
  }
  return NULL;
}


YEvent* CEventsPageArray::FindEvent(ULONG nEvID,void* pMem/*NULL*/, int nSize/*0*/) {
  ULONG nFPI = GetFirstPageIndex();
  ULONG nLPI = GetLastPageIndex();
  int   nItm = GetEventsCount();
  ULONG nEvOnPage = 0;
  ULONG iPage = 0;
  ASSERT(nFPI<=GetPagesNum());
  ASSERT(nLPI<=GetPagesNum());
  BOOL bRun = (nFPI==nLPI);
  for(iPage=nLPI;iPage!=nFPI || bRun;) {
    //    ASSERT(nEvs == GetEventsCount());
    nItm -= m_paEP[iPage].GetNumEvents();
    ASSERT(nItm>=0);
    if(nItm<=(int)nEvID) {
      nEvOnPage  = nEvID - nItm;
      ASSERT(nEvOnPage<GetEventsCount()); //nEvOnPage<=0
      return _GetEvent(m_paEP[iPage].GetData(),m_paEP[iPage].m_pawEvOffsets[nEvOnPage],pMem,nSize);
    }
    if(bRun)
      break;
    iPage = GetPrevPageIndex(iPage);
    if(iPage==nFPI)
      bRun=TRUE;
  }
  return NULL;
}
//------
BOOL CEventsPageArray::FindPageRange(ULONG nEvFrom, ULONG nEvTo, ULONG& nPageFrom, ULONG& nPageTo, ULONG& nFPE, ULONG& nLPE) {
  //TRACE("Begin find range\n");
  //Sleep(2000);
  ULONG nFound = 0;
  ULONG nFPI = GetFirstPageIndex();
  ULONG nLPI = GetLastPageIndex();
  int nItm = GetEventsCount();
  int nEvs = nItm;
  ULONG iPage = 0;

  ASSERT(nFPI<=GetPagesNum());
  ASSERT(nLPI<=GetPagesNum());

  #ifdef _DEBUG
    ULONG iNeedPages = 0;
  #endif

  BOOL bRun1 = (nFPI==nLPI);
  int nItm1 = GetEventsCount();
  for(ULONG/*int*/ iPage1=nLPI;iPage1!=nFPI || bRun1;) {
    nItm1 -= m_paEP[iPage1].GetNumEvents();
    ASSERT(nItm1>=0);
    if(bRun1)
      break;
    iPage1 = GetPrevPageIndex(iPage1);
    if(iPage1==nFPI)
      bRun1=TRUE;
  }

  BOOL bRun = (nFPI==nLPI);
  for(iPage=nLPI;iPage!=nFPI || bRun;) {
    ASSERT(nEvs == GetEventsCount());
    nItm -= m_paEP[iPage].GetNumEvents();
    ASSERT(nItm>=0);
    if(nItm<=(int)nEvTo && nFound==0) {
      nPageTo = iPage;
      nLPE  = nItm + m_paEP[iPage].GetNumEvents()-1;
      nFound=1;
    }
    #ifdef _DEBUG
      if(nFound>0)
        ++iNeedPages;
    #endif
    if(nFound==1 && nItm<=nEvFrom) {
      nPageFrom = iPage;
      nFPE  = nItm;
      ++nFound;
      break;
    }
    if(bRun)
      break;
    iPage = GetPrevPageIndex(iPage);
    if(iPage==nFPI)
      bRun=TRUE;
  }
  #ifdef _DEBUG
    ASSERT(iNeedPages==1 || iNeedPages==2); //maximum 2 pages in cache!!!
    ASSERT(nPageFrom<=GetPagesNum());
    ASSERT(nPageTo<=GetPagesNum());
  #endif
  //TRACE("End find range\n");
  return nFound==2; //found!
}
//------
BOOL CEventsPageArray::GetPageIndByNum(ULONG nPageNum, ULONG& nPageInd) {
  if(GetFirstPageNum()==nPageNum) {
    nPageInd  = GetFirstPageIndex();
    return TRUE;
  }
  if(GetLastPageNum()==nPageNum) {
    nPageInd  = GetLastPageIndex();
    return TRUE;
  }
  ULONG iPageI=GetFirstPageIndex();
  BOOL bLast = (GetFirstPageIndex()==GetLastPageIndex());
  for(ULONG nPage=GetFirstPageNum();nPage!=GetLastPageNum() || bLast;) {
    if(nPage==nPageNum) {
      nPageInd  = iPageI;
      return TRUE;
    }
    if(bLast)
      break;
    iPageI = GetNextPageIndex(iPageI);
    nPage  = m_paEP[iPageI].GetNumber();
    if(iPageI==GetLastPageIndex())
      bLast=TRUE;
  }
  //ASSERT(!"Not found"); //KSN???????????????
  return FALSE;
}
//------
BOOL CEventsPageArray::GetPageNumByInd(ULONG nPageInd, ULONG& nPageNum) {
  if(nPageInd<0 || nPageInd>=GetPagesNum()) {
    return FALSE;
  }
  nPageNum  = m_paEP[nPageInd].GetNumber();
  return TRUE;
}
//-----
BOOL CEventsPageArray::GetEventsBefore(ULONG nPageTo, ULONG& nEvents) {
  ULONG nPageI = GetFirstPageIndex();
  ULONG nPage  = GetFirstPageNum();
  nEvents = 0;
  for(;nPage != nPageTo;) {
    nEvents += m_paEP[nPageI].GetNumEvents();
    nPageI = GetNextPageIndex(nPageI);
    ++nPage;
  }
  return TRUE;
}

BOOL CEventsPageArray::LoadPage(CEventsPage* ppage, ULONG iPageInd, CEventsFilter* pEF, int& nEvAddFirst, int& nEvAddLast) {
  //  pages              first last  addpage addmetod
  // X X X X X X X X      -      -     6      to head
  // 0 1 2 3 4 X X X      0      4     6      to tail
  // 9 103 4 5 6 7 8      3     10     2      to head
  // 0 1 2 3 4 5 6 7      0      7     5     impossible
  // 0 1 2 3 4 5 6 7      0      7    10      to tail 
  ASSERT(ppage);
  if(!ppage)
    return FALSE;
  ULONG nPageNum = ppage->GetNumber();
  ULONG nEvents;
  if(m_bCache) {
    ScanPage(ppage->GetData(), ppage->GetFirstEvOffset(), nEvents, ppage->GetOffsets(),pEF);
    ppage->SetNumEvents(nEvents);
  }
  #ifdef DEBUG_EL
//  TRACE("Page %6d loading (index = %4d)...\n",nPageNum,iPageInd);
//  TRACE("Time loaded     %s\n",YTimer::GetCurrentSpan().FormatEx("%c"));
  #endif
  if(iPageInd!=-1 && m_bCache) {
    ASSERT(iPageInd!=-1);
    return _AddToTail(ppage,iPageInd,nEvAddFirst, nEvAddLast);
  }
  if(iPageInd==-1) {
    if( IsEmpty() || 
        nPageNum >= m_nLastPageNum+1 ||
        nPageNum == m_nLastPageNum   ||
        m_nFirstPageIndex == m_nLastPageIndex)
      return _AddToTail(ppage,iPageInd,nEvAddFirst, nEvAddLast);
    //if(nPageNum <= m_nFirstPageNum-1)
    return _AddToHead(ppage,iPageInd,nEvAddFirst, nEvAddLast);
  }
  if(iPageInd!=-1) {
    if( IsEmpty()    || 
      nPageNum == (m_nLastPageNum+1) ||
      nPageNum == m_nLastPageNum)
      return _AddToTail(ppage,iPageInd,nEvAddFirst, nEvAddLast);
    if(nPageNum == m_nFirstPageNum-1)
      return _AddToHead(ppage,iPageInd,nEvAddFirst, nEvAddLast);
  }
  ASSERT(0);
  return FALSE;
}

BOOL  CEventsPageArray::_AddToHead(CEventsPage* ppage, ULONG iPageInd/*-1*/, int& nEvAddFirst, int& nEvAddLast) {
  ASSERT(NULL!=ppage);
  if(!ppage)
    return FALSE;

  BOOL bFirst = FALSE;
  BOOL bPrev  = FALSE;

  ULONG nPageNum = ppage->GetNumber();

  if(nPageNum==m_nFirstPageNum)
    bFirst = TRUE;
  if(nPageNum==m_nFirstPageNum-1) //this is previous page
    bPrev = TRUE;
  ASSERT(!(bFirst==TRUE && bPrev==TRUE));

  if(!bFirst && !bPrev)
    _Empty();

  if(IsEmpty()) {
    if(iPageInd==-1) {
      __SetAtPage(0,ppage);
      m_nFirstPageNum   = ppage->GetNumber();
      m_nLastPageNum    = ppage->GetNumber();
      m_nFirstPageIndex = 0;
      m_nLastPageIndex  = 0;
      m_bEmpty          = FALSE;
    }
    else {
      __SetAtPage(iPageInd,ppage);
      m_nFirstPageNum   = ppage->GetNumber();
      m_nLastPageNum    = ppage->GetNumber();
      m_nFirstPageIndex = iPageInd;
      m_nLastPageIndex  = iPageInd;
      m_bEmpty          = FALSE;
    }
    nEvAddFirst     = 0;
    nEvAddLast      = (int)ppage->GetNumEvents();
    m_dwEventsCount = ppage->GetNumEvents();
    return TRUE;
  }
 
  if(bFirst) {
    ULONG nPrevEvCount  = m_paEP[m_nFirstPageIndex].GetNumEvents();
    __SetAtPage(m_nFirstPageIndex,ppage);
    nEvAddFirst     = ((int)ppage->GetNumEvents()-(int)nPrevEvCount);
    nEvAddLast      = 0;
    m_dwEventsCount = m_dwEventsCount-nPrevEvCount+ppage->GetNumEvents();
    return TRUE;
  }

  if(bPrev) {
    ULONG nPrevEvCount = m_paEP[m_nLastPageIndex].GetNumEvents();
    ULONG nPrevPageIndex = GetPrevPageIndex(m_nFirstPageIndex);
    #ifdef _DEBUG
      if(iPageInd!=-1)
        ASSERT(iPageInd==nPrevPageIndex);
    #endif //_DEBUG
    __SetAtPage(nPrevPageIndex,ppage);
    m_nFirstPageNum   = ppage->GetNumber();
    m_nFirstPageIndex = nPrevPageIndex;
    if(nPrevPageIndex == m_nLastPageIndex) {//replace last and set 
      m_nLastPageIndex = GetPrevPageIndex(m_nLastPageIndex);
      --m_nLastPageNum; //TODO maybe read PageNum from page!
      nEvAddFirst     = (int)ppage->GetNumEvents();
      nEvAddLast      = -((int)nPrevEvCount);
      m_dwEventsCount = m_dwEventsCount-nPrevEvCount+ppage->GetNumEvents();
      if(!IsReplacedFirstPage())
        SetReplacedFirstPage(TRUE);
    }
    else {
      nEvAddFirst     = (int)ppage->GetNumEvents();
      nEvAddLast      = 0;
      m_dwEventsCount+=ppage->GetNumEvents();
    }
    ASSERT((m_nLastPageNum-m_nFirstPageNum+1)<=GetPagesNum());
    return TRUE;
  }
  ASSERT(0);
  return FALSE;
}

BOOL  CEventsPageArray::_AddToTail(CEventsPage* ppage, ULONG iPageInd/*-1*/, int& nEvAddFirst, int& nEvAddLast) {
  //this page == last page  -> SetPage(lastpage)
  //this page == last page+1-> SetPage(lastpage+1)
  //else                    -> Empty()
  ASSERT(NULL!=ppage);
  if(!ppage)
    return FALSE;
  ULONG nPageNum = ppage->GetNumber();
  
  BOOL bLast=FALSE;
  BOOL bNext=FALSE;
  
  if(m_bCache) {
    return __SetAtPage(iPageInd,ppage);
  }

  if(nPageNum==m_nLastPageNum)
    bLast = TRUE;
  if(nPageNum==m_nLastPageNum+1) //this next page
    bNext = TRUE;
  ASSERT(!(bLast==TRUE && bNext==TRUE));
  if(!bLast && !bNext)
    _Empty();
     
  if(IsEmpty()) {
    if(iPageInd==-1) {
      __SetAtPage(0,ppage);
      m_nFirstPageNum   = ppage->GetNumber();
      m_nLastPageNum    = ppage->GetNumber();
      m_nFirstPageIndex = 0;
      m_nLastPageIndex  = 0;
      m_bEmpty          = FALSE;
    }
    else {
      __SetAtPage(iPageInd,ppage);
      m_nFirstPageNum   = ppage->GetNumber();
      m_nLastPageNum    = ppage->GetNumber();
      m_nFirstPageIndex = iPageInd;
      m_nLastPageIndex  = iPageInd;
      m_bEmpty          = FALSE;
    }
    nEvAddFirst     = (int)0;
    nEvAddLast      = (int)ppage->GetNumEvents();
    m_dwEventsCount = ppage->GetNumEvents();
    return TRUE;
  }
 
  if(bLast) {
    ULONG nPrevEvCount  = m_paEP[m_nLastPageIndex].GetNumEvents();
    __SetAtPage(m_nLastPageIndex,ppage);
    nEvAddFirst     = (int)0;
    nEvAddLast      = (int)ppage->GetNumEvents() - (int)nPrevEvCount;
    m_dwEventsCount = m_dwEventsCount-nPrevEvCount+ppage->GetNumEvents();
    return TRUE;
  }

  if(bNext) {
    //ULONG nPrevEvCount = m_paEP[m_nLastPageIndex].GetNumEvents();; //modify TEST
    ULONG nPrevEvCount = m_paEP[m_nFirstPageIndex].GetNumEvents();; 
    ULONG nNextPageIndex = GetNextPageIndex(m_nLastPageIndex);
    __SetAtPage(nNextPageIndex,ppage);
    m_nLastPageNum   = ppage->GetNumber();
    m_nLastPageIndex = nNextPageIndex;
    if(nNextPageIndex == m_nFirstPageIndex) {//replace first and set
      m_nFirstPageIndex = GetNextPageIndex(m_nFirstPageIndex);
      ++m_nFirstPageNum; //TODO maybe read PageNum from page!
      nEvAddFirst     = -(int)nPrevEvCount;
      nEvAddLast      = (int)ppage->GetNumEvents();
      m_dwEventsCount = m_dwEventsCount-nPrevEvCount+ppage->GetNumEvents();
      if(!IsReplacedFirstPage())
        SetReplacedFirstPage(TRUE);
    }
    else {
      nEvAddFirst     = 0;
      nEvAddLast      = (int)ppage->GetNumEvents()-(int)nPrevEvCount;
      m_dwEventsCount+=ppage->GetNumEvents();
    }
    ASSERT((m_nLastPageNum-m_nFirstPageNum+1)<=GetPagesNum());
    return TRUE;
  }
  ASSERT(0);
  return FALSE;
}
