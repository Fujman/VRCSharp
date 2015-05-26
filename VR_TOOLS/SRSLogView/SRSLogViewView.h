// SRSLogViewView.h : interface of the CSRSLogViewView class
//
/////////////////////////////////////////////////////////////////////////////
#include "CONTROLS/AUTOSIZE/ResizableFormView.h"

#include "EVENTLOG/CONTROLS/EventsListDlg.h"

#include "eventlog/eventlog.h"
#include "EventLog/events.h"

#if !defined(AFX_SRSLOGVIEWVIEW_H__F35EED65_1C15_4249_AA9B_51884B964025__INCLUDED_)
#define AFX_SRSLOGVIEWVIEW_H__F35EED65_1C15_4249_AA9B_51884B964025__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSRSLogViewView : public CResizableFormView
{
  typedef CResizableFormView CParent;
protected: // create from serialization only
	CSRSLogViewView();
	DECLARE_DYNCREATE(CSRSLogViewView)

protected:
  BOOL             m_bShowLogStatus;
protected:
  CStatic          m_staticWnd;
  CEventsListDlg*  m_pwndLog;
  YEventsProtocol  theEventsProtocol;
public:
	//{{AFX_DATA(CSRSLogViewView)
	enum { IDD = IDD_SRSLOGVIEW_FORM };
	//}}AFX_DATA

// Attributes
public:
	CSRSLogViewDoc* GetDocument();

// Operations
public:
  inline YEventsProtocol* GetLog() { YEvent::SetLog(&theEventsProtocol); return &theEventsProtocol;}


  int           ViewAllLog(CString szLogName);
//helpers
  int           OnViewEventLog(CString szLogFile, int nMode);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSRSLogViewView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSRSLogViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSRSLogViewView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonOpenlog();
	afx_msg void OnDestroy();
	afx_msg void OnButton1();
	afx_msg void OnButtonOpenlogCurses();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButtonShowStatus();
	afx_msg void OnButtonShowDetails();
	//}}AFX_MSG
  afx_msg void OnCheckApply();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SRSLogViewView.cpp
inline CSRSLogViewDoc* CSRSLogViewView::GetDocument()
   { return (CSRSLogViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRSLOGVIEWVIEW_H__F35EED65_1C15_4249_AA9B_51884B964025__INCLUDED_)
