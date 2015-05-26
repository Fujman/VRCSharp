// EventsPage.h: interface for the CEventsPage class.
#if !defined(AFX_EVENTSPAGE_H__C9EA98F8_9E48_45EA_B40D_4E21A64E41D3__INCLUDED_)
#define AFX_EVENTSPAGE_H__C9EA98F8_9E48_45EA_B40D_4E21A64E41D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "EVENTLOG/Event.h"
#include "EventsFilter.h"
//=============================
class   YEvent;
//class   CEventsFilter;
//=============================
class CEventsPage {
  friend  class CEventsPageArray;
public:
  enum { PAGEDATASIZE = 4096 };
  enum { MAX_OFFSETS  = 512 };
protected:
  ULONG		m_nPage;        //page number
  ULONG		m_nEvents;      //number of events
  BOOL		m_bLoaded;      //page loaded
  BOOL		m_bIdent;       //page loaded and valid
	WORD    m_wStartOffset; //start offset on page (0-4095)
  WORD*   m_pawEvOffsets; //events offsets list
  BYTE*		m_pData;
public:
								CEventsPage();
//								CEventsPage(const CEventsPage& ep);
	virtual				~CEventsPage();

protected:
  CEventsPage&	operator=(const CEventsPage& ep);
public:
  inline void   SetNumber(ULONG nPage);
  inline ULONG  GetNumber()const;
  inline void   SetNumEvents(ULONG nEvents);
  inline ULONG  GetNumEvents()const;
//use only in LoadPage
  inline void   SetLoaded(BOOL bLoaded);
//use only in LoadPage and OnLogEvent
  inline void   SetIdent(BOOL bIdent);
//-------
  inline BOOL   IsLoaded()const;
  inline BOOL   IsIdent()const;
  inline ULONG  GetDataSize()const;

	inline void		SetData(const BYTE* pData);
  inline BYTE*  GetData() const;

  inline WORD*  GetOffsets() const;

  inline BOOL   SetFirstEvOffset(WORD wOffset);
  inline WORD   GetFirstEvOffset();
protected:  
  inline void   PrepareData(const BYTE* pData);
  inline void   PrepareOffsets(const WORD* pData);
  inline void		SetOffsets(const WORD* pData);
};
//---------------------------------------
class CEventsPageArray 
{
//attributes
public:
  CEventsPage*	m_paEP;
private:
  BYTE*         m_pPagesData;
  WORD*         m_pOffsetsData;
private:
  ULONG					m_nFirstPageNum;
  ULONG					m_nFirstPageIndex;
  ULONG					m_nLastPageNum;
  ULONG					m_nLastPageIndex; 

  ULONG         m_dwEventsCount;
  
  ULONG					m_nPages;
  ULONG         m_nPageSize;
  
  BOOL          m_bEmpty;
  BOOL          m_bCache;
  BOOL          m_bReplacedFirstPage;
//constructors/destructors
public:
					      CEventsPageArray(int nSize, BOOL bCache);
	virtual       ~CEventsPageArray();
//operations
public:
  void          ReInit();
  inline BOOL   IsReplacedFirstPage() const;

  inline void   SetReplacedFirstPage(BOOL bReplace);

//--KSN--[2005_07_12 19:28:27] (experiment)
//#ifndef DEBUG_EL
  YEvent*       FindEvent(ULONG nEvID,void* pMem, int nSize);
//#else
  BOOL          GetEventHandle(ULONG nEvID, ULONG& nPage,ULONG& nEventOnPage, void* pMem, int nSize);
//#endif

  BOOL          FindPageRange(ULONG nEvFrom, ULONG nEvTo, ULONG& nPageFrom, ULONG& nPageTo, ULONG& nFPE, ULONG& nLPE);
  BOOL          GetPageIndByNum(ULONG nPageNum, ULONG& nPageInd);
  BOOL          GetPageNumByInd(ULONG nPageInd, ULONG& nPageNum);
  BOOL          GetEventsBefore(ULONG nPageTo, ULONG& nEvents);

  inline ULONG  GetNextPageIndex(ULONG nCur) const;
  inline ULONG  GetPrevPageIndex(ULONG nCur) const;
protected:
  BOOL            __SetAtPage(ULONG nIndex, CEventsPage* ppage);

private:
  inline BOOL     _FilterEvent(const YEvent* pEvent, CEventsFilter* pEF);
  inline YEvent*  _GetEvent(const BYTE* pPage, ULONG nOffset, void* pMem=NULL, int nSize=0);
  inline YEvent*  _GetEventAndNextOffset(const BYTE* pPage, WORD  nOffset, CEventsFilter* pEF, void* pMem/*NULL*/, int nSize/*0*/,WORD& wNextOffset);

public:
  inline void    _Empty();
  inline void    _Empty2();
  int           ScanPage(const BYTE* pData, WORD nStartOffset, ULONG& nEvents, WORD* pCache, CEventsFilter* pEF);
  BOOL          LoadPage  (CEventsPage* page, ULONG iPageInd, CEventsFilter* pEF, int& nEvAddFirst, int& nEvAddLast);
  BOOL  	      _AddToHead(CEventsPage* page, ULONG iPageInd, int& nEvAddFirst, int& nEvAddLast);
  BOOL  	      _AddToTail(CEventsPage* page, ULONG iPageInd, int& nEvAddFirst, int& nEvAddLast);
  inline BOOL   IsEmpty()const; 

  inline ULONG	GetPagesNum() const;
  inline ULONG  GetEventsCount() const;
  inline ULONG  GetPageSize() const;
  void          SetPageSize(ULONG nSize) {m_nPageSize = nSize;}

//  inline void   SetCachedBeginEventNum(ULONG nEvents);
//  inline void   SetCachedEndEventNum(ULONG nEvents);
//  inline ULONG  GetCachedBeginEventNum() const;
//  inline ULONG  GetCachedEndEventNum() const;

	inline void		SetFirstPageIndex(ULONG nFirst);
	inline ULONG	GetFirstPageIndex() const;
	inline void		SetFirstPageNum(ULONG nFirst);
	inline ULONG	GetFirstPageNum() const;

  inline void		SetLastPageIndex(ULONG nFirst);
  inline ULONG	GetLastPageIndex() const;
  inline void		SetLastPageNum(ULONG nFirst);
  inline ULONG	GetLastPageNum() const;

//   inline void		SetOwnFirstPageNum(ULONG nFirst);
//   inline ULONG	GetOwnFirstPageNum() const;
//   inline void		SetOwnLastPageNum(ULONG nFirst);
//   inline ULONG	GetOwnLastPageNum() const;
};
#include "EventsPage.inl"
#endif // !defined(AFX_EVENTSPAGE_H__C9EA98F8_9E48_45EA_B40D_4E21A64E41D3__INCLUDED_)
