#include "stdafx.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/*---------------------------------------------------------------------------\
| Class: YEventsProtocol                   Language: C++     Model: All      |
|----------------------------------------------------------------------------|
| Description:
|
|
|
|
| Derived from: none
| Constructors: default
| Operators:
| Methods:
| Members:
|
| Used macro,procedures,classes:
| Source:
| Notes:
\---Last change 06.06.01 15:14-----Copyright (c) 1999, Anton Yavorsky, KPI--*/

#include <afxmt.h>
#include "xCSyncOb.h"
#include "eventlog.h"
#include "eventwin.h"

#undef setb
#define  _LOGINCLUDE
#include "xlog.h"

#define time_t TIME_T //AY 01.02.2011

#define DEFAULT_LOG_SIZE  (128*1024L)
#define SIGNATURE         (0xaeaeaeaeUL)

#define STACK_NEW
#define STACK_LEN   ((MAX_PATH+1)*sizeof(wchar_t)+sizeof(YEvent64))//542

int YEventsProtocol::m_nPageSize = 4096;

inline YEvent__CompareTime(time_t tTime1, WORD nMsec1, time_t tTime2, WORD nMsec2)
{
  // tTime1:nMsec1 < tTime2:nMsec2: -1
  // tTime1:nMsec1 > tTime2:nMsec2: +1
  // tTime1:nMsec1 = tTime2:nMsec2:  0
  if     (tTime1<tTime2)
    return -1;
  else if(tTime1>tTime2)
    return +1;
  else if(nMsec1<nMsec2)
    return -1;
  else if(nMsec1>nMsec2)
    return +1;
  else
    return  0;
}


#define AUTOLOCKUNLOCK()   YEventsProtocolAutoUnlock theAutoUnlock(this);\
                           (_lock ? Lock() : 0);

int  YEventsProtocol::PreparePage(BYTE *pPage,ULONG nPageNumber) {
  ASSERT(pPage!=NULL);
  for(int i=0; i<GetPageSize(); ++i)
    pPage[i] = 0;
  YEvent64 evPage(EVN_LOGFILE_TYPE,nPageNumber,SIGNATURE);
  void *pRet = evPage.GetData(pPage,GetPageSize());
  ASSERT(pRet!=NULL);
  return 0;
}

int  YEventsProtocol::WritePage(ULONG nOffset) {
  ASSERT((nOffset%GetPageSize())==0 && nOffset<GetFileSize() && m_pWritePage!=NULL);
  DWORD  nPos, nBytes;

  nPos = ::SetFilePointer(m_hFile,nOffset,NULL,FILE_BEGIN);
  if(nPos==-1)
    return SysError();  ////////////////////// TO DO - ERROR MUST BE RECOVERED
  if(!::WriteFile(m_hFile,m_pWritePage,GetPageSize(),&nBytes,NULL))
    return SysError();  ////////////////////// TO DO - ERROR MUST BE RECOVERED

  return SetSuccess();
}

int  YEventsProtocol::SendEvent(const YEvent& ev, ULONG nOffset, int nSize) {
  if(m_wndLog!=NULL) { //TO DO
    TCHAR sz[255];
    m_wndLog->AddLine(ev.GetText(sz,255));
    //LOGOPEN();
    //LOGSTR(sz);
    //LOGCLOSE();
    return SUCCESS;
  }
  if(m_wndLogEx2) {
    m_wndLogEx2->PostMessage(WM_APP,nSize,(LPARAM)nOffset);// AY+KS 09.03.2003
  //m_wndLogEx2->SendMessage(WM_APP,nSize,(LPARAM)nOffset);// MUST BE SEND! TODO (PostMessage)
    return SUCCESS;    
  }
  
  return FAILURE;
}

ULONG  YEventsProtocol::_PutEvent(YEvent& ev, int isBuffered/*NOBUFFERED*/, BOOL _lock) {/* ret=offset */
  AUTOLOCKUNLOCK();
  int   nMaxSize, nSize;
  ULONG nOldPageOffset;
  void  *pRet;

  if(!isOpened())
    { SetError(NOTOPENED); return -1;}

  ev.SetTime(); // Warning: time redefinition! // AY 23.04.2001
  nSize = ev.GetDataSize();

//////////////////////////////////////////////////////////////////////////////
// Put event in the empty logfile
//////////////////////////////////////////////////////////////////////////////
  if(m_nUsedSize==0) {
    // init page
    m_nWritePageOffset = 0;
    m_nWritePageNumber = 0;
    m_nWriteOffset = m_nWritePageOffset + GetPageHeaderSize();
    PreparePage(m_pWritePage,m_nWritePageNumber);
    // put event
    nMaxSize = GetPageSize() - OffsetOnPage(m_nWriteOffset);
    pRet = ev.GetData(m_pWritePage+OffsetOnPage(m_nWriteOffset),nMaxSize);
    ASSERT(pRet!=NULL);
    // write event
    if(isBuffered==NOBUFFERED)
      if(WritePage(m_nWritePageOffset)!=SUCCESS)
        return(-1);
    m_isNeedFlush = (isBuffered==BUFFERED);
    // increment counters
    m_nUsedSize = m_nWriteOffset;
    m_nLastOffset  = m_nWriteOffset;
    m_nWriteOffset += nSize;
    // adjust info
    m_nFirstPageNumber = m_nWritePageNumber;
    m_nStartPageNumber = m_nWritePageNumber;
    m_nFirstPageOffset = m_nWritePageOffset;
    m_nStartPageOffset = m_nWritePageOffset;
    m_nFirstOffset = m_nLastOffset;
    m_nStartOffset = m_nLastOffset;
    m_isCycle = 0;
    if(GetDebugMode())
      SendEventDebug(ev,m_nLastOffset,nSize);// DEBUG
    else
      SendEvent(ev,m_nLastOffset,nSize);
    return(m_nLastOffset);
  }

//////////////////////////////////////////////////////////////////////////////
// Put event in the non-empty logfile
//////////////////////////////////////////////////////////////////////////////

// Make next page if needed //////////////////////////////////////////////////
  nOldPageOffset = m_nWritePageOffset;
  if(m_nWriteOffset + nSize > m_nWritePageOffset+GetPageSize()) {
    // save old page
    if(m_isNeedFlush)
      if(WritePage(m_nWritePageOffset)!=SUCCESS)
        return(-1);
    m_isNeedFlush = FALSE;
    // start new page
    m_nWritePageNumber += 1;
    m_nWritePageOffset = NextPageOffset(m_nWritePageOffset);
    m_nWriteOffset = m_nWritePageOffset + GetPageHeaderSize();
    PreparePage(m_pWritePage,m_nWritePageNumber);
    // mark end of used area
    if(m_nUsedSize<m_nWriteOffset)
      m_nUsedSize = m_nWriteOffset;
    // adjust info - it is already provided on adding first event on page
    m_isNonFirstPage = TRUE;
  }

// Put event on current page /////////////////////////////////////////////////
  // put event
  nMaxSize = GetPageSize() - OffsetOnPage(m_nWriteOffset);
  pRet = ev.GetData(m_pWritePage+OffsetOnPage(m_nWriteOffset),nMaxSize);
  ASSERT(pRet!=NULL);
  // write event
  if(isBuffered==NOBUFFERED)
    if(WritePage(m_nWritePageOffset)!=SUCCESS)
      return(-1);
  m_isNeedFlush = (isBuffered==BUFFERED);
  // increment counters
  m_nLastOffset  = m_nWriteOffset;
  m_nWriteOffset += nSize;
  if(m_nUsedSize<m_nWriteOffset)
    m_nUsedSize = m_nWriteOffset;
  // adjust info
  //if(m_nUsedSize>m_nWriteOffset || m_nUsedSize==GetFileSize()) { // cyclic filling of log
  if(m_isNonFirstPage) {
    if(m_nFirstPageOffset==m_nWritePageOffset) {
      m_isCycle = 1;
      m_nFirstPageNumber ++;
      m_nFirstPageOffset = NextPageOffset(m_nFirstPageOffset);
      m_nFirstOffset = m_nFirstPageOffset + GetPageHeaderSize();
    }
    if(m_nStartPageOffset==m_nWritePageOffset) {
      m_isCycle = 2;
      m_nStartPageNumber ++;
      m_nStartPageOffset = NextPageOffset(m_nStartPageOffset);
      m_nStartOffset = m_nStartPageOffset + GetPageHeaderSize();
    }
  }
  if(GetDebugMode())
    SendEventDebug(ev,m_nLastOffset,nSize);// DEBUG
  else
    SendEvent(ev,m_nLastOffset,nSize);
  return(m_nLastOffset);
}

int  YEventsProtocol::ValidateHeader(const BYTE *pPage, ULONG* pnPageNumber) const {
  YEvent64 ev((const void *)pPage, GetPageSize());
  if(!ev.Validate()) // Bad Page
    return BADPAGE;
  *pnPageNumber = 0;
  if(ev.IsEmpty())   // Empty Page
    return ISNULL;
  if(ev.GetData32(1)!=SIGNATURE)
    return BADPAGE;    // Bad Page
  *pnPageNumber = ev.GetData32();
  return SUCCESS;
}

int  YEventsProtocol::ValidateEvent(
  const BYTE *pEvent,
  ULONG nMaxSize/*0*/,
  ULONG *pnSize/*NULL*/,
  time_t *ptTime/*NULL*/,
  WORD  *pnMsec/*NULL*/
) const
{
  int   isGood, isEmpty;
  ULONG nSize;
  time_t tTime;
  WORD  nMsec;

#ifdef STACK_NEW //AY 03.02.2005
  BYTE abyBuffer[STACK_LEN];
  YEvent *pev = YEvent::Create(pEvent,nMaxSize,(void*)abyBuffer,sizeof(abyBuffer) DEBUG_NEW_FILE_LINE);
#else
  YEvent *pev = YEvent::Create(pEvent,nMaxSize);
#endif
  if(pev==NULL)
    return BADEVENT;    // Bad Event
  nSize   = pev->GetDataSize();
  isGood  = pev->Validate();
  isEmpty = pev->IsEmpty();
  tTime   = pev->GetTime(&nMsec);
#ifdef STACK_NEW //AY 31.01.2005
  YEvent::Delete(pev,(void*)abyBuffer);
#else
  delete pev;
#endif

  if(!isGood)
    return BADEVENT;    // Bad Event

  if(pnSize!=NULL) *pnSize = nSize;
  if(ptTime!=NULL) *ptTime = tTime;
  if(pnMsec!=NULL) *pnMsec = nMsec;

  if(isEmpty)
    return ISEMPTY;     // Empty Event

  return SUCCESS;
}

int  YEventsProtocol::ValidatePage(
  const BYTE *pPage,
  ULONG *pnPageNumber/*NULL*/,  // page handle
  ULONG *pnLastOffset/*NULL*/,  // last event on page local offset
  ULONG *pnWriteOffset/*NULL*/  // free area on page local offset
) const
{
  ULONG nEventMaxSize, nEventSize;
  ULONG nLastOffset, nWriteOffset;
  ULONG nPageNumber;
  int   i;
  const BYTE* p;
  int   isEmpty;
  int   iEventState, iHeaderState;
  time_t tTime, tPrevTime;
  WORD   nMsec, nPrevMsec;

  iHeaderState = ValidateHeader(pPage,&nPageNumber);
  if(iHeaderState==BADPAGE)
    return BADPAGE;

  for(isEmpty=1, i=0; i<GetPageSize(); ++i) {
    if(m_pReadPage[i]!=0) {
      isEmpty = 0;
      break;
    }
  }
  if(!isEmpty && iHeaderState==ISNULL)
    return BADPAGE;
  if(isEmpty && iHeaderState==ISNULL)
    return ISNULL;
  if(pnPageNumber!=NULL)
    *pnPageNumber = nPageNumber;
  if(isEmpty && iHeaderState==SUCCESS)
    return ISEMPTY;
  //!isEmpty && iHeaderState==SUCCESS

  nEventMaxSize = GetPageSize() - GetPageHeaderSize();
  p = pPage + GetPageHeaderSize();
  nLastOffset = GetPageHeaderSize();
  nWriteOffset = GetPageHeaderSize();
  i = 0;
  while(nEventMaxSize>0) {
    iEventState = ValidateEvent(p,nEventMaxSize,&nEventSize,&tTime,&nMsec);
    if(iEventState!=SUCCESS)
      break;
    if(i!=0 && YEvent__CompareTime(tPrevTime,nPrevMsec,tTime,nMsec)>0) {// log specific
			if(tPrevTime-tTime>1) // ???
				return BADPAGE; // previous time is greater then current
		}
    nEventMaxSize -= nEventSize;
    p += nEventSize;
    nLastOffset = nWriteOffset;
    nWriteOffset += nEventSize;
    ++i;
    tPrevTime = tTime;
    nPrevMsec = nMsec;
  }

  if(iEventState!=SUCCESS) { // check if tile is zero
    for(isEmpty=1, i=nEventMaxSize; i>0; --i) {
      if(*p++ != 0) {
        isEmpty = 0;
        break;
      }
    }
    if(!isEmpty)
      return BADPAGE; // if tile is not zero and is not event - error
  }
  if(pnWriteOffset!=NULL) *pnWriteOffset = nWriteOffset;
  if(pnLastOffset!=NULL)  *pnLastOffset  = nLastOffset;

  return SUCCESS;
}

int  YEventsProtocol::ReadPage(ULONG nOffset, BOOL bMakeValidation/*TRUE*/) {
  ASSERT((nOffset%GetPageSize())==0 && nOffset<GetFileSize() && m_pReadPage!=NULL && m_pWritePage!=NULL );
  ULONG  nPageNumber;
  DWORD  nPos,nBytes;
  int    i;
  int    iRet;

  if(nOffset==m_nReadPageOffset)    // page already in memory
    return SetError(SUCCESS);

  if(nOffset==m_nWritePageOffset) { // reading page is same as writting page
    for(i=0; i<GetPageSize(); ++i)
      m_pReadPage[i] = m_pWritePage[i];
    m_nReadPageNumber = m_nWritePageNumber;
    m_nReadPageOffset = m_nWritePageOffset;
    iRet = SUCCESS;
  }else{                            // read page from disk
    nPos = ::SetFilePointer(m_hFile,nOffset,NULL,FILE_BEGIN);
    if(nPos==-1)
      return SysError();  ////////////////////// TO DO - ERROR MUST BE RECOVERED
    if(!::ReadFile(m_hFile,m_pReadPage,GetPageSize(),&nBytes,NULL))
      return SysError();  ////////////////////// TO DO - ERROR MUST BE RECOVERED
    if(bMakeValidation)
      iRet = ValidatePage(m_pReadPage,&nPageNumber); // check
    else {// special internal future used in Scan() procedure
      nPageNumber = -1; //KSN 13.11.2006
      iRet = SUCCESS;
    }
    if(iRet==SUCCESS || iRet==ISEMPTY) {
      m_nReadPageNumber = nPageNumber;
      m_nReadPageOffset = nOffset;
    }else if(iRet==ISNULL){
      m_nReadPageNumber = -1;
      m_nReadPageOffset = nOffset;
    }else{
      m_nReadPageNumber = -1;
      m_nReadPageOffset = -1;
    }
  }
  return SetError(iRet);
}

YEvent* YEventsProtocol::_GetEvent(ULONG nOffset, void* pMem/*NULL*/, int nSize/*0*/,BOOL _lock) {
  AUTOLOCKUNLOCK();
  ASSERT(1); //ASSERT(pMem==NULL && nSize==0);
  ULONG  nEventMaxSize;
  int    isGood;
  YEvent *pev;

  if(!isOpened())
    { SetError(NOTOPENED); return NULL; }
  if(nOffset>GetFileSize())
    { SetError(BADPARAMETER); return NULL; }

  const BYTE *pPage = NULL;
  if     (ThisPageOffset(nOffset)==m_nWritePageOffset)
    pPage = m_pWritePage;
  else if(ThisPageOffset(nOffset)==m_nReadPageOffset)
    pPage = m_pReadPage;
  else {
    if(ReadPage(ThisPageOffset(nOffset))!=SUCCESS)
      return NULL;
    pPage = m_pReadPage;
  }

  nEventMaxSize = GetPageSize() - OffsetOnPage(nOffset);
#ifdef STACK_NEW
  pev = YEvent::Create(pPage+OffsetOnPage(nOffset),nEventMaxSize,pMem,nSize DEBUG_NEW_FILE_LINE);
#else
  pev = YEvent::Create(pPage+OffsetOnPage(nOffset),nEventMaxSize);
#endif
  if(pev==NULL)
    { SetError(BADEVENT); return NULL; }   // Bad Event
  isGood = pev->Validate();
  if(!isGood)
    { delete pev; SetError(BADEVENT); return NULL; }

  return pev; // ATTENTION!: must be deleted in future by operator delete
}

LPTSTR  YEventsProtocol::_GetEventText(ULONG nOffset, LPTSTR pszText, int nLength,BOOL _lock) {
  AUTOLOCKUNLOCK(); BYTE abyBuffer[STACK_LEN];
  LPTSTR pszRet;
#ifdef STACK_NEW
  YEvent *pev = _GetEvent(nOffset,abyBuffer,sizeof(abyBuffer));
#else
  YEvent *pev = _GetEvent(nOffset);
#endif
  if(pev==NULL)
    return NULL;     // Bad Event
  pszRet = pev->GetText(pszText,nLength);
  delete pev;
  return pszRet;
}

ULONG  YEventsProtocol::_GetSessionFirst(BOOL _lock) {
  AUTOLOCKUNLOCK();
  if(!isOpened())
    { SetError(NOTOPENED); return -1; }
  if(m_nUsedSize==0)
    return -1;
  return _GetNext(m_nStartOffset,TRUE); // jump to next page is needed!
}

ULONG  YEventsProtocol::_GetGlobalFirst(BOOL _lock) {
  AUTOLOCKUNLOCK();
  if(!isOpened())
    { SetError(NOTOPENED); return -1; }
  if(m_nUsedSize==0)
    return -1;
  return m_nFirstOffset;
}

ULONG  YEventsProtocol::_GetFirstOnPage(ULONG nPage, BOOL _lock) {
  AUTOLOCKUNLOCK();
  if(!isOpened())
    { SetError(NOTOPENED); return -1; }
  if(m_nUsedSize==0)
    return -1;
  ASSERT(nPage%GetPageSize()==0);
  return nPage+GetPageHeaderSize();
}

ULONG  YEventsProtocol::_GetNext(ULONG nOffset, BOOL isShiftedOffset/*FALSE*/, BOOL _lock) {
  AUTOLOCKUNLOCK(); BYTE abyBuffer[STACK_LEN];
// Page          Next:   First:
//      HEADER1  EVENT2  EVENT1
//      EVENT1   EVENT2
//      EVENT2   EVENT3
//      EVENT3   EVENT4
//      ZEROS
// Write Page (last page)
//      HEADER2  EVENT4
//      EVENT4   EVENT5
//      EVENT5   EVENT6
//      EVENT6   -1
//      ZEROS
  if(!isOpened())
    { SetError(NOTOPENED); return -1; }

  ULONG nPageOffset = ThisPageOffset(nOffset);
  YEvent *pev;
  int   isEmpty, iRet;

  if(nOffset==-1)
    { SetError(BADPARAMETER); return -1; }

  if(!isShiftedOffset) {
    ASSERT(nOffset != ThisPageOffset(nOffset));
#ifdef STACK_NEW
    pev = _GetEvent(nOffset,abyBuffer,sizeof(abyBuffer)); // get current event and skip to next
#else
    pev = _GetEvent(nOffset); // get current event and skip to next
#endif
    if(pev==NULL) // must be impossible situation - physical problems only
      return -1;  // in previous reading it will be correct
    nOffset += pev->GetDataSize();
    delete pev;
  }else{
    if(nPageOffset==nOffset) // adjust offset==page_size
      if(nPageOffset>=m_nPageSize)
        nPageOffset -= m_nPageSize;
  }

  ASSERT(nOffset<=nPageOffset+GetPageSize()); // same page

  // check next event
  if(nOffset==nPageOffset+GetPageSize()){ // last event on page
    pev = NULL;
  }else{
#ifdef STACK_NEW
    pev = _GetEvent(nOffset,abyBuffer,sizeof(abyBuffer)); // in previous reading it will be correct
#else
    pev = _GetEvent(nOffset); // in previous reading it will be correct
#endif
  }
  if(pev!=NULL) { // Next event good or empty
    isEmpty = pev->IsEmpty();
    delete pev;
    if(isEmpty)
      return -1;
    return nOffset;
  }else if(pev==NULL) { // Bad page or page end
    // check if it is page end
    const BYTE* pEvent = m_pReadPage + OffsetOnPage(nOffset);
    int i, nBytes = GetPageSize() - (nOffset-nPageOffset); //Don't use OffsetOnPage(nOffset): nOffset may be == m_nPageSize!
    for (isEmpty=1, i=0; i<nBytes; ++i) { // check if tile is zero
      if(pEvent[i]!=0) {
        isEmpty = 0;
        break;
      }
    }
    if(!isEmpty)
      { SetError(BADPAGE); return -1; } // Tile non-zero -> bad page format

    //Check last page, cases: a)12340000, b)12345678, c)92345678
    // a) file partial filled
    if(GetFileSize()>ThisPageOffset(m_nUsedSize)+GetPageSize()) {
      if(nPageOffset+GetPageSize()>ThisPageOffset(m_nUsedSize)) // this is last page (and tile is zero)
        { SetError(SUCCESS); return -1; }
    // b) file fully linear filled
    }else if(m_nWritePageOffset>m_nFirstPageOffset){
      if(nPageOffset==m_nWritePageOffset)
        { SetError(SUCCESS); return -1; }
    // c) file fully cyclic filled
    }else{
      if(nPageOffset==m_nWritePageOffset)
        { SetError(SUCCESS); return -1; }
    }

    //Next page
    nPageOffset = NextPageOffset(nPageOffset);

    iRet = ReadPage(nPageOffset);
    if(iRet!=SUCCESS && iRet!=ISEMPTY && iRet!=ISNULL)
      return -1;
    if(iRet==ISNULL || iRet==ISEMPTY)
      { SetError(SUCCESS); return -1; }

    nOffset = nPageOffset+GetPageHeaderSize();
#ifdef STACK_NEW
    pev = _GetEvent(nOffset,abyBuffer,sizeof(abyBuffer));
#else
    pev = _GetEvent(nOffset);
#endif
    if(pev==NULL)
      return -1; // phisical error ?
    isEmpty = pev->IsEmpty();
    delete pev;
    if(isEmpty)
      return -1;
    return nOffset;
  }
  return nOffset;
}

// Note: this implementation is not check time of pages
int  YEventsProtocol::_Scan(BOOL _lock){   // Initialization
  AUTOLOCKUNLOCK();
  ULONG  nPages, nFileSize;
  ULONG  nPrevPage, nPage, nPageOffset, nPrevPageOffset, nPrevWriteOffset;
  ULONG  nOldestPage, nOldestPageOffset; // first page
  ULONG  nNewestPage, nNewestPageOffset;   // current write page
  ULONG  nUsedSize; // used area size of file
  ULONG  nLastOffset, nWriteOffset;
  int    i, iRet, isNULL, isEmpty, isNewestFound;
  ULONG  n;
  time_t tPrevTime=0, tTime=0;
  WORD   nPrevMsec=0, nMsec=0;

  nFileSize = ::GetFileSize(m_hFile,NULL);
  nPages = nFileSize/GetPageSize();
  if(nPages<2 || (nFileSize%GetPageSize())!=0)
    return SetError(BADSIZE);

  m_nFileSize = nFileSize;

  m_nReadPageNumber  = -1;  // prevent copying readed page from zero buffer
  m_nReadPageOffset  = -1;  // in function ReadPage(...)
  m_nWritePageNumber = -1;  // prevent copying readed page from writting
  m_nWritePageOffset = -1;  // page in function ReadPage(...)
  m_nWriteOffset = -1;

  nUsedSize = 0;
  isNewestFound = 0;
  nPage = -1;
  nPageOffset = -1;
  nWriteOffset = -1; // local offset
  for(nPageOffset=0, n=0; n<nPages; ++n, nPageOffset+=GetPageSize()) {
    nPrevPage = nPage;
    nPrevPageOffset = nPageOffset-GetPageSize();
    nPrevWriteOffset = nWriteOffset; // local offset!

    iRet = ReadPage(nPageOffset,FALSE);
    if(iRet!=SUCCESS)
      return iRet; // TO DO: phisical error ?
    iRet = ValidatePage(m_pReadPage,&nPage,&nLastOffset,&nWriteOffset);
    if(iRet!=SUCCESS && iRet!=ISEMPTY && iRet!=ISNULL)
      return iRet; // TO DO: phisical error ?
    isNULL = (iRet==ISNULL);
    isEmpty = (iRet==ISEMPTY);

//  Cases:    Oldest:  Newest:
//  00000000     0        0
//  12340000     1        4
//  92345678     2        9
//  12345678     1        8
//  92345600  must be impossible
    if(n==0 && isNULL) { // empty log                        // 00000000
      nOldestPage = 0, nOldestPageOffset = nPageOffset;
      nNewestPage = 0, nNewestPageOffset = nPageOffset;
      nUsedSize = 0;
      break; // skip scanning, warning: don't check zero tile
    }else if(n>0  && isNULL) {                               // 12340000
      if(isNewestFound)
        return SetError(BADFMT); //error:92345600
      nNewestPage = nPrevPage;
      nNewestPageOffset = nPrevPageOffset;
      nUsedSize = nPrevPageOffset + nPrevWriteOffset;
      isNewestFound = 1;
      break; // skip scanning, warning: don't check zero tile
    }else if(n>0  && nPage<nPrevPage &&                       //92345678
      (nPrevPage+1)!=0 && nPage!=0) { // Intel PROCESSOR DEPENDENT: 0xFFFFFFFF+1==0!
      if(isNewestFound)
        return SetError(BADFMT); //error:96782345
      nOldestPage = nPage,     nOldestPageOffset = nPageOffset;
      nNewestPage = nPrevPage, nNewestPageOffset = nPrevPageOffset;
      isNewestFound = 1;
    }else if(n>0 && !isNewestFound){ //12345678 - next page
      nNewestPage=nPage, nNewestPageOffset = nPageOffset;
    }else if(n==0){ // initialization
      nNewestPage = nPage, nNewestPageOffset = nPageOffset;
      nOldestPage = nPage, nOldestPageOffset = nPageOffset;
    }else{
      ;//ASSERT(0)?
    }
    nUsedSize = nPageOffset + nWriteOffset;
    if(n>0 && (nPage>nPrevPage && nPage-nPrevPage>1) || (nPage==nPrevPage))
      return SetError(BADFMT); // TO DO
  }

  iRet = ReadPage(nNewestPageOffset,FALSE); ASSERT(iRet==SUCCESS || iRet==ISEMPTY || iRet==ISNULL);
  iRet = ValidatePage(m_pReadPage,&nPage,&nLastOffset,&nWriteOffset); ASSERT(iRet==SUCCESS || iRet==ISEMPTY || iRet==ISNULL);
  ASSERT(nPage==nNewestPage || nPage==-1);

  if(m_nOpenCount==0){ // if it is first opening in session
    m_nStartPageNumber = nNewestPage;
    m_nStartPageOffset = nNewestPageOffset;
    m_nStartOffset = nNewestPageOffset + nWriteOffset;
  }
  m_nFirstPageNumber = nOldestPage;
  m_nFirstPageOffset = nOldestPageOffset;
  m_nFirstOffset = m_nFirstPageOffset + GetPageHeaderSize();
  m_nWritePageNumber = nNewestPage;
  m_nWritePageOffset = nNewestPageOffset;
  m_nWriteOffset = nNewestPageOffset + nWriteOffset;
  m_nUsedSize = nUsedSize;

  for(i=0; i<GetPageSize(); ++i)
    m_pWritePage[i] = m_pReadPage[i];

  return SetError(SUCCESS);
}

int  YEventsProtocol::_Open(LPCTSTR szFileName, int nMaxLogSize/*0*/, BOOL _lock, BOOL bReadOnly){   // auto create if needed
  AUTOLOCKUNLOCK();
  ASSERT(m_hFile==(HANDLE)HFILE_ERROR);  
  HANDLE hFile = NULL;
  int   iRet;
  int   i;

  CString szLogName = MakeLogName(szFileName);

  //Create buffers
  if(m_pWritePage==NULL)
    m_pWritePage = new BYTE[GetPageSize()];
  if(m_pReadPage==NULL)
    m_pReadPage = new BYTE[GetPageSize()];
  for(i=0; i<GetPageSize(); ++i)
    m_pWritePage[i] = m_pReadPage[i] = 0;

#if defined(UNICODE) || defined(_UNICODE) //UNICODE
  //Create file and truncate existing
  if(!bReadOnly) {
    hFile = ::CreateFile(szLogName
      ,GENERIC_READ|GENERIC_WRITE
      ,FILE_SHARE_READ
      ,NULL
      ,OPEN_ALWAYS
      ,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_NO_BUFFERING|FILE_FLAG_SEQUENTIAL_SCAN|FILE_FLAG_WRITE_THROUGH
      ,NULL
    );
  }else{
    hFile = ::CreateFile(szLogName
      ,GENERIC_READ
      ,FILE_SHARE_READ|FILE_SHARE_WRITE
      ,NULL
      ,OPEN_EXISTING
      ,FILE_FLAG_NO_BUFFERING|FILE_FLAG_SEQUENTIAL_SCAN
      ,NULL
    );
  }
  if(hFile==INVALID_HANDLE_VALUE)
    return SysError();
  if(!bReadOnly && ::GetLastError()!=ERROR_ALREADY_EXISTS) //create
    return _Create(szFileName,nMaxLogSize,FALSE,hFile);
  m_hFile = hFile;

  ASSERT(m_hFile!=(HANDLE)HFILE_ERROR);//AY 28.01.2014

#else //ANSI
  //Check if file exists
  m_ofsReOpen.cBytes = sizeof(m_ofsReOpen);
  hFile = (HANDLE)::OpenFile(szLogName,&m_ofsReOpen,OF_EXIST);
  if(!bReadOnly && hFile==(HANDLE)HFILE_ERROR) // file is not exist - Create
    return _Create(szFileName,nMaxLogSize,FALSE);
  if(hFile==(HANDLE)HFILE_ERROR) // file is not exist - Fail
    return SysError();
  
  //Open file
  if(!bReadOnly) {
    m_hFile = (HANDLE)::OpenFile(szLogName,&m_ofsReOpen,
      OF_REOPEN|OF_SHARE_DENY_WRITE|OF_READWRITE
    );
  }else{
    m_hFile = (HANDLE)::OpenFile(szLogName,&m_ofsReOpen,
      OF_REOPEN|OF_SHARE_DENY_NONE|OF_READ
    );
  }
  if(m_hFile==(HANDLE)HFILE_ERROR)
    return SysError();
#endif

  m_isNeedFlush = 0;
  m_szFileName = szFileName;//AY 18.04.2005
  
  iRet = _Scan();
  
  if(iRet==SUCCESS)
    m_nOpenCount++;
  else
    Close(); // TO DO (recreate?)
  return SetError(iRet);
}

int  YEventsProtocol::_Create(LPCTSTR szFileName, int nMaxLogSize/*0*/, BOOL _lock, HANDLE hOpenedFile){ // TO DO: auto import if file exist
  AUTOLOCKUNLOCK();
  ASSERT(m_hFile==(HANDLE)HFILE_ERROR);
  HANDLE hFile = NULL;
  DWORD  nBytes;
  ULONG  nPage, nPages;
  int    i;

  CString szLogName = MakeLogName(szFileName);

//Create buffers
  if(m_pWritePage==NULL)                          
    m_pWritePage = new BYTE[GetPageSize()];
  if(m_pReadPage==NULL)
    m_pReadPage = new BYTE[GetPageSize()];
  for(i=0; i<GetPageSize(); ++i)
    m_pWritePage[i] = m_pReadPage[i] = 0;

#if defined(UNICODE) || defined(_UNICODE)
  //Create file and truncate existing
  if(INVALID_HANDLE_VALUE==hOpenedFile) {
    hFile = ::CreateFile(szLogName,GENERIC_READ|GENERIC_WRITE
      ,FILE_SHARE_READ
      ,NULL
      ,TRUNCATE_EXISTING
      ,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_WRITE_THROUGH|FILE_FLAG_NO_BUFFERING|FILE_FLAG_SEQUENTIAL_SCAN
      ,NULL
    );
    if(hFile==INVALID_HANDLE_VALUE)
      return SysError();
  }else{
    hFile = hOpenedFile;
  }
  nPages = (nMaxLogSize?nMaxLogSize:DEFAULT_LOG_SIZE)/GetPageSize();
  for(nPage=0; nPage<nPages; ++nPage) { // clear log
    if(!::WriteFile(hFile,m_pWritePage,GetPageSize(),&nBytes,NULL))
      return SysError();    // TO DO
    ASSERT(nBytes==GetPageSize());
  }
#else
//Check if file exists
  m_ofsReOpen.cBytes = sizeof(m_ofsReOpen);
  hFile = (HANDLE)::OpenFile(szLogName,&m_ofsReOpen,OF_EXIST);
//if(hFile!=HFILE_ERROR) // file is exist
//  ?;
  //Create file
  m_ofsReOpen.cBytes = sizeof(m_ofsReOpen);
  hFile = (HANDLE)::OpenFile(szLogName,&m_ofsReOpen,OF_CREATE);
  if(hFile==(HANDLE)HFILE_ERROR)
    return SysError();
  nPages = (nMaxLogSize?nMaxLogSize:DEFAULT_LOG_SIZE)/GetPageSize();
  for(nPage=0; nPage<nPages; ++nPage) { // clear log
    if(!::WriteFile(hFile,m_pWritePage,GetPageSize(),&nBytes,NULL))
      return SysError();    // TO DO
    ASSERT(nBytes==GetPageSize());
  }
  ::CloseHandle(hFile);
  m_ofsReOpen.cBytes = sizeof(m_ofsReOpen);
  hFile = (HANDLE)::OpenFile(szLogName,&m_ofsReOpen,OF_REOPEN|OF_READWRITE|OF_SHARE_DENY_WRITE);
  if(hFile==(HANDLE)HFILE_ERROR)
    return SysError();
#endif

//Ok! Initializing:
  m_szFileName = szFileName;
  m_hFile = hFile;
  m_nFileSize = nMaxLogSize;
  m_nUsedSize = 0;
  m_nFilePages = nPages;

  ASSERT(m_hFile!=(HANDLE)HFILE_ERROR);//AY 28.01.2014

  m_nFirstPageNumber = 0; /* Oldest page number */
  m_nFirstPageOffset = 0; /* Oldest page offset (from start of file) */
  m_nStartPageNumber = 0; /* current session start number */
  m_nStartPageOffset = 0; /* current session start offset (from start of file) */
  m_nStartOffset = 0;     /* current session start event offset (from start of file) */
  m_isCycle = 0;          /* if SessionStartEvent will be rewritten */
  m_nWrittenEvents = 0;   /* statistics */
  m_nWrittenPages = 0;    /* statistics */
  m_lError = 0;
  /////  Writing
  m_nWritePageNumber = 0;
  m_nWritePageOffset = 0;
  m_nWriteOffset = 0;     /* current write offset (if zero - it is new page)*/
  /////  Reading
  m_nReadPageNumber  = -1;
  m_nReadPageOffset  = -1;
  /////  Writing Cache
  m_isNeedFlush = 0;      /* buffered input has been provided */

//PrepareHeader(m_pWritePage,m_nWritePageNumber);
//m_nWriteOffset = 0 + GetPageHeaderSize();
//m_isNeedFlush = 0;      /* prevent from writting empty page ! */

  m_nOpenCount = 1;
  return SetSuccess();
}

int  YEventsProtocol::_Close(BOOL _lock){
  AUTOLOCKUNLOCK();
  ASSERT(m_hFile!=(HANDLE)HFILE_ERROR);
  int iRet = _Flush();
  if(iRet!=SUCCESS)
    return iRet;
  BOOL bRet = ::CloseHandle(m_hFile);
  ASSERT(bRet!=0);
  m_hFile = (HANDLE)HFILE_ERROR;
  return iRet;
}
int  YEventsProtocol::_Flush(BOOL _lock){
  AUTOLOCKUNLOCK();
  if(!isOpened())
    return SetError(NOTOPENED);
  int iRet = SUCCESS;
  if(m_isNeedFlush)
    iRet = WritePage(m_nWritePageOffset);
  if(iRet==SUCCESS)
    m_isNeedFlush = 0;
  return iRet;
}
BOOL  YEventsProtocol::isOpened() const{
  return(m_hFile!=(HANDLE)HFILE_ERROR);
}

YEventsProtocol::YEventsProtocol() {
  //LOGMESSAGE("YEventsProtocol constructor..."); LOGFLUSH();
  /////  Log file status
  m_ofsReOpen.cBytes = 0;
  m_hFile = (HANDLE)HFILE_ERROR;
  m_nFileSize = 0;
  m_nPageSize = 4096;
  m_nUsedSize = 0;
  m_nFilePages = 0;
  /////  Info
  m_nFirstPageNumber = 0; /* Oldest page number */
  m_nFirstPageOffset = 0; /* Oldest page offset (from start of file) */
  m_nStartPageNumber = 0; /* current session start number */
  m_nStartPageOffset = 0; /* current session start offset (from start of file) */
  m_nStartOffset = 0;     /* current session start event offset (from start of file) */
  m_isNonFirstPage = 0;   /* if SessionStartEvent will be rewritten */
  m_isCycle = 0;          /* if SessionStartEvent will be rewritten */
  m_nOpenCount = 0;
  m_nWrittenEvents = 0;   /* statistics */
  m_nWrittenPages = 0;    /* statistics */
  m_lError = 0;
  /////  Writing
  m_nWritePageNumber = -1;
  m_nWritePageOffset = -1;
  m_nWriteOffset = -1;    /* current write offset (if zero - it is new page)*/
  m_pWritePage = NULL;    /* writting cache */
  /////  Reading Cache
  m_nReadPageNumber = -1;
  m_nReadPageOffset = -1;
  m_pReadPage = NULL;     /* reading cache */
  /////  Writing Cache
  m_tLastWrite = 0;       /* ? last write time */
  m_tTimeDelay = 0;       /* ? write delay before saving */
  m_isNeedFlush = 0;      /* buffered input has been provided */
  /////  Message window
  m_wndLog = NULL;
  m_wndLogEx2  = NULL;
  m_nDebugMode = FALSE;
  m_pMutex = new CLockEvent;//AY 03.07.2003 //m_pMutex = new CMutex;
  m_nMode = 0;
}

YEventsProtocol::_YEventsProtocolDestructor(BOOL _lock) {
  { // don't delete { - special future before delete mutex
    AUTOLOCKUNLOCK();
    if(m_isNeedFlush)
      _Flush();
    if(isAttached())
      _DetachWindow();
    if(isOpened())
      ::CloseHandle(m_hFile);
    if(m_pWritePage!=NULL)
      delete m_pWritePage;
    if(m_pReadPage!=NULL)
      delete m_pReadPage;
  }
  delete m_pMutex;
	return 0;
}
// Utilities 
CString YEventsProtocol::MakeLogName(LPCTSTR szFileName){
  CString szLogName;
  int nPointPos;

  if(szFileName==NULL) {// default name
    szLogName = AfxGetApp()->m_pszHelpFilePath;
    nPointPos = szLogName.ReverseFind('.');  ASSERT(nPointPos>0);
    szLogName = szLogName.Left(nPointPos);
    szLogName += ".LOG";
    return szLogName;
  }

  szLogName = szFileName;

  if(szLogName.ReverseFind('\\')==0) {  // add program path to user name
    szLogName = AfxGetApp()->m_pszHelpFilePath;
    nPointPos = szLogName.ReverseFind('\\'); ASSERT(nPointPos>0);
    szLogName = szLogName.Left(nPointPos);
    szLogName += szFileName;
    return szLogName;
  }
  return szLogName;    // full name
}

CString YEventsProtocol::MakeLogDumpName(LPCTSTR szFileName){
  CString szLogName;
  int nPointPos;

  if(szFileName==NULL) {// default name
    szLogName = AfxGetApp()->m_pszHelpFilePath;
    nPointPos = szLogName.ReverseFind('.');  ASSERT(nPointPos>0);
    szLogName = szLogName.Left(nPointPos);
    szLogName += ".DMP";
    return szLogName;
  }
//   else {
//     szFileName = CFileName(szFileName).GetBase() +
//   }
  szLogName = szFileName;

  if(szLogName.ReverseFind('\\')==0) {  // add program path to user name
    szLogName = AfxGetApp()->m_pszHelpFilePath;
    nPointPos = szLogName.ReverseFind('\\'); ASSERT(nPointPos>0);
    szLogName = szLogName.Left(nPointPos);
    szLogName += szFileName;
    return szLogName;
  }
  return szLogName;    // full name
}

int    YEventsProtocol::_AttachWindow(CEventsWindow* wndLog, int nMode/*VIEWSESSION*/, BOOL _lock){
  AUTOLOCKUNLOCK(); BYTE abyBuffer[STACK_LEN];
  if(!isOpened())
    return SetError(NOTOPENED);

  ASSERT(m_wndLog==NULL);
  m_wndLog = wndLog;
  m_wndLog->AttachLog(this);

  UINT nOffset = 0;
  TCHAR sz[255];

	wndLog->SetRedrawOff();

  //FILE* file = fopen("log.tmp","w");

  switch(nMode) {
    case VIEWALL:
      wndLog->ResetContents();
      nOffset = _GetGlobalFirst();
      break;
    case VIEWSESSION:
      wndLog->ResetContents();
      nOffset = _GetSessionFirst();
      break;
    case VIEWCURRENT:
      nOffset = -1;
      break;
    default:
      ASSERT(0);
  }
  while(nOffset!=-1){
    if(!GetDebugMode()) {
      LPTSTR szRet = _GetEventText(nOffset,sz,255);
      if(szRet!=NULL)  // only if log is empty - session mode
        wndLog->AddLine(sz);
      //fputs(szRet,file); fputs("\n",file);
    }else{
#ifdef STACK_NEW
      YEvent* pEvent = _GetEvent(nOffset,abyBuffer,sizeof(abyBuffer));
#else
      YEvent* pEvent = _GetEvent(nOffset); //DEBUG
#endif
      if(pEvent!=NULL) {
        SendEventDebug(*pEvent,nOffset,pEvent->GetDataSize());// DEBUG
        delete pEvent; // DEBUG
      }
    }
    nOffset = _GetNext(nOffset);
  }
  //fclose(file);

	wndLog->SetRedrawOn();

  return TRUE;
}

int    YEventsProtocol::_AttachWindowEx2(CWnd* wndLog, int nMode/*VIEWSESSION*/, BOOL _lock){
  AUTOLOCKUNLOCK();
  if(!isOpened())
    return SetError(NOTOPENED);

  ASSERT(m_wndLogEx2==NULL);
  m_wndLogEx2 = wndLog;

  UINT nOffset = 0;
  switch(nMode) {
    case VIEWALL:
      //wndLog->ResetContents();
      nOffset = _GetGlobalFirst();
      break;
    case VIEWSESSION:
      //wndLog->ResetContents();
      nOffset = _GetSessionFirst();
      break;
    case VIEWCURRENT:
      nOffset = -1;
      break;
    default:
      ASSERT(0);
  }
  wndLog->SendMessage(WM_APP+1,(WPARAM)this,(LPARAM)nMode);//MUST BE SEND - locking is provided
  return TRUE;
}

int    YEventsProtocol::_DetachWindow(BOOL _lock){
  AUTOLOCKUNLOCK();
  //ASSERT(m_wndLog!=NULL);
  m_wndLog = NULL;
  m_wndLogEx2 = NULL;
  return TRUE;
}

int    YEventsProtocol::Lock(DWORD dwTimeout/*INFINITE*/){
  ASSERT(m_pMutex!=NULL);
  BOOL bRet = m_pMutex->Lock(dwTimeout);
  ASSERT(bRet);
  return bRet;
}
int    YEventsProtocol::Unlock(){
  ASSERT(m_pMutex!=NULL);
  BOOL bRet = m_pMutex->Unlock();
  ASSERT(bRet);
  return bRet;
}

int YEventsProtocol::GetPage(ULONG nOffset, BYTE* pPage, BOOL bUseCurrent/*TRUE*/) {
  ASSERT((nOffset%GetPageSize())==0 && nOffset<GetFileSize());
  DWORD  nPos, nBytes;

  if(bUseCurrent && nOffset==m_nWritePageOffset) {
    memcpy(pPage,m_pWritePage,GetPageSize());
    return SetSuccess();
  }
  nPos = ::SetFilePointer(m_hFile,nOffset,NULL,FILE_BEGIN);
  if(nPos==-1)
    return SysError();  ////////////////////// TO DO - ERROR MUST BE RECOVERED
  if(!::ReadFile(m_hFile,pPage,GetPageSize(),&nBytes,NULL))
    return SysError();  ////////////////////// TO DO - ERROR MUST BE RECOVERED 
  return SetSuccess();
}

#include "fs/FileName.h"

int YEventsProtocol::ClientOpen(int nMaxLogSize, int nAltLogSize)
{
  YEventsProtocol* pThis = this;
  CString szTemp; YFileSystem::GetTempDir(szTemp);
  CFileName szLog  = pThis->MakeLogName();
  CFileName szFile = szTemp;
    szFile++ += szLog.GetName();
  YTime t = YTime::GetCurrentTime();
  CFileName szAlt  = szFile.GetBase() + t.FormatGmt(_T(".%Y-%m-%d.%H_%M_%S")) + szFile.GetExt();

  int iAns = pThis->Open(szFile,nMaxLogSize);// 32 kB = 2000 events
  if(iAns!=0) { 
	//GetLog()->Zip(NULL);
    iAns = pThis->Open(szAlt,nAltLogSize);
  }
  return iAns;
}

#include "xCWnd.h"

void YEventsProtocol::ShowLog()
{
  if(m_wndLogEx2!=NULL)
    CWnd__Show(m_wndLogEx2);
  else if(m_wndLog!=NULL)
    CWnd__Show(m_wndLog);
}
