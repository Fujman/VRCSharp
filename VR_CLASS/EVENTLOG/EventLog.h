#ifndef __EVENTLOG_H
#define __EVENTLOG_H

#include "event.h"

#ifdef __cplusplus

class CLockEvent;

class CEventsWindow;
class CEventsWindowEx;

/////////////////////////////////////////////////////////////////////////////
#define  EVN_LOGFILE_CLASS     (EVN_64BIT_CLASS)
#define  EVN_LOGFILE_TYPE      (0x0F)
/////////////////////////////////////////////////////////////////////////////
// YEventsProtocol;
class YEventsProtocol
{
  friend class CEventsWindowEx;
  friend class CEventsListDlg;  //KSN 21.01.2004 
public:  // constants
  enum { VIEWCURRENT=0, VIEWALL=1, VIEWSESSION=2 }; // Attach Modes
  enum { BUFFERED=1, NOBUFFERED=0 }; // Flags
  enum { modeTEMPORARY=1 };
protected:
  /////  Log file status
  CString  m_szFileName;
  OFSTRUCT m_ofsReOpen;
  HANDLE m_hFile;
  ULONG  m_nFileSize;        /* 128 kB */
  static int    m_nPageSize;        /* 4096 B */
  ULONG  m_nUsedSize;        /* used pages size */
  ULONG  m_nFilePages;       /* file size in pages */
  /////  Counters
  ULONG  m_nFirstPageNumber; /* lastest page number */
  ULONG  m_nFirstPageOffset; /* lastest page offset (from start of file) */
  ULONG  m_nStartPageNumber; /* current session start number */
  ULONG  m_nStartPageOffset; /* current session start offset (from start of file) */
  ULONG  m_nFirstOffset;     /* lastest event offset (from start of file) */
  ULONG  m_nStartOffset;     /* current session start event offset (from start of file) */
  ULONG  m_nLastOffset;      /* newest  event offset (from start of file) */
  int    m_isNonFirstPage;   /* mark first page for skip redefine Start and First pages */
  int    m_isCycle;          /* if SessionStartEvent will be rewritten */
  int    m_nOpenCount;       /* number of success Open calls */
  int    m_nWrittenEvents;   /* statistics */
  int    m_nWrittenPages;    /* statistics */
  DWORD  m_lError;
  /////  Writing
  ULONG  m_nWriteOffset;     /* current write global offset (if zero - it is new page)*/
  ULONG  m_nWritePageNumber;
  ULONG  m_nWritePageOffset; /* current page global offset */
  BYTE*  m_pWritePage;       /* writting cache */
  /////  Reading
  ULONG  m_nReadPageNumber;
  ULONG  m_nReadPageOffset;  /* current read page global offset */
  BYTE*  m_pReadPage;        /* reading cache */
  /////  Writing Cache
  TIME_T m_tLastWrite;       /* ? last write time */
  TIME_T m_tTimeDelay;       /* ? write delay before saving */
  int    m_isNeedFlush;      /* buffered input has been provided */
  /////  Message window
  CEventsWindow* m_wndLog;   //AY
  CWnd*  m_wndLogEx2;        //KSN
//  ULONG  m_nLastLogEventOffset;
//  WORD   m_nLastLogEventTimeMsec;
  CLockEvent* m_pMutex;//AY 03.07.2003 //CMutex* m_pMutex;
  int    m_nMode;

public: // Attributes
  static int GetPageHeaderSize();
  static int GetPageSize();
  ULONG  GetFileSize() const;
  long   GetError() const;
  BOOL   isAttached() const;
  BOOL   isOpened() const;
  void   ShowLog();

  int    GetMode() const  { return m_nMode; }
  int    SetMode(int nMode) { return m_nMode = nMode; }

  static CString MakeLogName(LPCTSTR szFileName=NULL);
  static CString MakeLogDumpName(LPCTSTR szFileName=NULL);
protected: // Internal Methods
  long   SetError(long lError);
  long   SysError();
  long   SetSuccess();

  ULONG  ThisPageOffset(ULONG nOffset) const;
  ULONG  NextPageOffset(ULONG nOffset) const;
  ULONG  OffsetOnPage(ULONG nOffset) const;

//ULONG  PrepareHeader(ULONG nOffset,ULONG nPageNumber);
//int    ValidatePage(ULONG nOffset) const;  // default is current read page
//int    ValidateEvent(ULONG nOffset) const;
//int    ValidateHeader(ULONG nOffset,ULONG *pnPageNumber) const;
  //KSN add
  int    GetPage(ULONG nOffset, BYTE* pPage, BOOL bUseCurrent=TRUE);
  //SKN add
  int    WritePage(ULONG nOffset);
  int    ReadPage(ULONG nOffset, BOOL bMakeValidation=TRUE); // bMakeValidation=FALSE is special internal future, used in Scan()
  int    PreparePage(BYTE *pPage,ULONG nPageNumber);
  int    ValidateHeader(const BYTE *pPage, ULONG *pnPageNumber) const;
  int    ValidateEvent(const BYTE *pPage, ULONG nMaxSize=0,
           ULONG *pnSize=NULL, TIME_T *ptTime=NULL, WORD *pnMsec=NULL) const;
  int    ValidatePage(const BYTE *pPage, ULONG *pnPageNumber=NULL,
           ULONG *pnLastOffset=NULL, ULONG *pnWriteOffset=NULL) const;
  int    SendEvent(const YEvent& ev, ULONG nOffset, int nSize);

protected: // Internal metods with conditioonal locking
  int    _YEventsProtocolDestructor(BOOL _lock=FALSE);
  int    _Create(LPCTSTR szFileName, int nMaxLogSize=0,BOOL _lock=FALSE, HANDLE hOpenedFile=INVALID_HANDLE_VALUE); // TO DO: auto import if exist
  int    _Open(LPCTSTR szFileName, int nMaxLogSize=0,BOOL _lock=FALSE, BOOL bReadOnly=FALSE);   // auto create if needed
  int    _Scan(BOOL _lock=FALSE);
  int    _Flush(BOOL _lock=FALSE);
  int    _Close(BOOL _lock=FALSE);
  int    _AttachWindowEx2(CWnd* wndLog, int nMode=VIEWSESSION,BOOL _lock=FALSE);
  int    _AttachWindow(CEventsWindow* wndLog, int nMode=VIEWSESSION,BOOL _lock=FALSE);
  int    _DetachWindow(BOOL _lock=FALSE);

  ULONG  _PutEvent(YEvent& ev, int isBuffered=NOBUFFERED,BOOL _lock=FALSE);// ret=offset

  ULONG  _GetSessionFirst(BOOL _lock=FALSE);
  ULONG  _GetGlobalFirst(BOOL _lock=FALSE);
  ULONG  _GetFirstOnPage(ULONG nPage=0, BOOL _lock=FALSE);
  ULONG  _GetNext(ULONG nOffset, BOOL isShiftedOffset=FALSE,BOOL _lock=FALSE);
  // GetEvent return temporary object if pMem==NULL - use operator delete!
  YEvent* _GetEvent(ULONG nOffset, void* pMem=NULL, int nSize=0,BOOL _lock=FALSE); // TO DO: pMem!=NULL
  LPTSTR  _GetEventText(ULONG nOffset, LPTSTR pszText, int nLength,BOOL _lock=FALSE);

public: // Methods with auto locking
  YEventsProtocol(); // no need locking
  ~YEventsProtocol();
  int    ClientOpen(int nMaxLogSize=0, int nAltLogSize=0);//AY 18.01.2014
  int    Create(LPCTSTR szFileName, int nMaxLogSize=0); // TO DO: auto import if exist?
  int    Open(LPCTSTR szFileName, int nMaxLogSize=0);   // auto create if needed
  int    View(LPCTSTR szFileName);
  int    Scan();
  int    Flush();
  int    Close();
  static int Dump(LPCTSTR szFileName, LPCTSTR szDumpName=NULL);
  static int Zip(LPCTSTR szFileName,LPCTSTR szZipName=NULL);
  int    Resize(LPCTSTR szFileName, DWORD dwNewSize/*bytes*/);
  int    AttachWindowEx2(CWnd* wndLog, int nMode=VIEWSESSION);
  int    AttachWindow(CEventsWindow* wndLog, int nMode=VIEWSESSION);
  int    DetachWindow();
  LPCTSTR GetFileName() const { return m_szFileName; }

  ULONG  PutEvent(YEvent& ev, int isBuffered=NOBUFFERED, BOOL bLock=TRUE);/* ret=offset */

  ULONG  GetSessionFirst();
  ULONG  GetGlobalFirst();
  ULONG  GetFirstOnPage(ULONG nPage);//AY 18.04.2005
  ULONG  GetNext(ULONG nOffset, BOOL isShiftedOffset=FALSE);
  // GetEvent return temporary object if pMem==NULL - use operator delete!
  YEvent* GetEvent(ULONG nOffset, void* pMem=NULL, int nSize=0); // TO DO: pMem!=NULL
  LPTSTR  GetEventText(ULONG nOffset, LPTSTR pszText, int nLength);

  int    Lock(DWORD dwTimeout=INFINITE);
  int    Unlock();

public:    // constants
  enum { // Error Codes: (warning: its must be different from GetLastError codes!)
    SUCCESS = 0, _START_ERROR_CODE_NUMBER = -1024,
    BADSIZE,     // Bad log file size
    BADPAGE,     // Bad page format (destroyed?)
    BADFMT,      // Bad pages order (destroyed?)
    BADEVENT,    // Bad event format
    BADPARAMETER,// Bad event format
    ISEMPTY,     // Page is empty
    ISNULL,      // Page is null (fully zero)
    NOTOPENED,   // Log is not opened
    FAILURE      // Unknown error
  };

public://DEBUG options
  BOOL   m_nDebugMode;
  BOOL   GetDebugMode() const { return m_nDebugMode; }
  void   SetDebugMode(BOOL bMode=TRUE) { m_nDebugMode=bMode; }
  void   SetPageSize(ULONG nPageSize) {m_nPageSize=nPageSize;};
protected:
  int    SendEventDebug(const YEvent& ev, ULONG nOffset, ULONG nSize);
};
/////////////////////////////////////////////////////////////////////////////
// Inline implementation
inline int YEventsProtocol::GetPageHeaderSize()
  { return YEvent64::SIZE_OF_BASE_DATA; }
inline int YEventsProtocol::GetPageSize()
  { return m_nPageSize; }
inline ULONG YEventsProtocol::GetFileSize() const
  { return m_nFileSize; }
inline BOOL  YEventsProtocol::isAttached() const
  { return (m_wndLogEx2!=NULL || m_wndLog!=NULL); }

inline long  YEventsProtocol::GetError() const
  { return m_lError; }
inline long  YEventsProtocol::SysError()
  { return(m_lError = GetLastError()); }
inline long  YEventsProtocol::SetSuccess()
  { return(m_lError = SUCCESS); }
inline long  YEventsProtocol::SetError(long lError)
  { return(m_lError = lError); }


inline ULONG  YEventsProtocol::NextPageOffset(ULONG nOffset) const {
  nOffset += m_nPageSize; ASSERT((nOffset%m_nPageSize)==0);
  if(nOffset>=m_nFileSize)
    nOffset = 0;
  return nOffset;
}
inline ULONG  YEventsProtocol::OffsetOnPage(ULONG nOffset) const {
  return (nOffset%m_nPageSize);
}
inline ULONG  YEventsProtocol::ThisPageOffset(ULONG nOffset) const {
  return nOffset-OffsetOnPage(nOffset);
}

// auto locking functions
inline YEventsProtocol::~YEventsProtocol()
  { _YEventsProtocolDestructor(TRUE);  }
inline  int    YEventsProtocol::Create(LPCTSTR szFileName, int nMaxLogSize)
  { return _Create(szFileName, nMaxLogSize, TRUE);  }
inline  int    YEventsProtocol::Open(LPCTSTR szFileName, int nMaxLogSize)
  { return _Open(szFileName, nMaxLogSize,TRUE); }
inline  int    YEventsProtocol::View(LPCTSTR szFileName)
  { return _Open(szFileName, 0,TRUE,TRUE); }
inline  int    YEventsProtocol::Scan()
  { return _Scan(TRUE); }
inline  int    YEventsProtocol::Flush()
  { return _Flush(TRUE); }
inline  int    YEventsProtocol::Close()
  { return _Close(TRUE); }
inline  int    YEventsProtocol::AttachWindowEx2(CWnd* wndLog, int nMode)
{ return _AttachWindowEx2(wndLog, nMode,TRUE); }
inline  int    YEventsProtocol::AttachWindow(CEventsWindow* wndLog, int nMode)
  { return _AttachWindow(wndLog, nMode,TRUE); }
inline  int    YEventsProtocol::DetachWindow()
  { return _DetachWindow(TRUE); }

inline  ULONG  YEventsProtocol::PutEvent(YEvent& ev, int isBuffered, BOOL bLock)
  { return _PutEvent(ev, isBuffered,bLock); }

inline  ULONG  YEventsProtocol::GetSessionFirst()
  { return _GetSessionFirst(TRUE); }
inline  ULONG  YEventsProtocol::GetGlobalFirst()
  { return _GetGlobalFirst(TRUE); }
inline  ULONG  YEventsProtocol::GetFirstOnPage(ULONG nPage)
  { return _GetFirstOnPage(nPage,TRUE); }

inline  ULONG  YEventsProtocol::GetNext(ULONG nOffset, BOOL isShiftedOffset)
  { return _GetNext(nOffset, isShiftedOffset,TRUE); }

inline  YEvent* YEventsProtocol::GetEvent(ULONG nOffset, void* pMem, int nSize)
  { return _GetEvent(nOffset, pMem, nSize, TRUE); }
inline  LPTSTR  YEventsProtocol::GetEventText(ULONG nOffset, LPTSTR pszText, int nLength)
  { return _GetEventText(nOffset, pszText, nLength, TRUE); }


/////////////////////////////////////////////////////////////////////////////
// Class YEventsProtocolAutoUnlock; (fully inline)
class YEventsProtocolAutoUnlock {
  YEventsProtocol* m_pEventsProtocol;
public:
  YEventsProtocolAutoUnlock(YEventsProtocol* pEventsProtocol)
    { m_pEventsProtocol = pEventsProtocol; }
  ~YEventsProtocolAutoUnlock()
    { m_pEventsProtocol->Unlock(); }
};
#endif//__cplusplus

#endif//__EVENTLOG_H
#pragma once
