// eventwin.h : header file
//
#if !defined(AFX_EVENTWIN_H__C65C8D01_B3D0_11D3_88A8_008048D9AFEA__INCLUDED_)
#define AFX_EVENTWIN_H__C65C8D01_B3D0_11D3_88A8_008048D9AFEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEventsWindow window
class YEventsProtocol;

class CEventsWindow : public CEdit
{
  ULONG  m_nMaxBufferSize;
	YEventsProtocol* m_pevp;

//Construction
public:
  CEventsWindow();
  int Create(const RECT& rc, UINT nID, CWnd *pParent=NULL);
	int SetRedrawOff();
	int SetRedrawOn();
	int AttachLog(YEventsProtocol* pevp);
	int DetachLog();

//Operations
public:
  int AddLine(LPCTSTR szText);
  int ResetContents();

// Implementation
public:
	virtual ~CEventsWindow();
  virtual BOOL PreCreateWindow( CREATESTRUCT& cs );

	// Generated message map functions
protected:
	//{{AFX_MSG(CEventsWindow)
	//}}AFX_MSG
  afx_msg void OnClose();
  afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVENTWIN_H__C65C8D01_B3D0_11D3_88A8_008048D9AFEA__INCLUDED_)

