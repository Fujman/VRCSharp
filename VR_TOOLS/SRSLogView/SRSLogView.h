// SRSLogView.h : main header file for the SRSLOGVIEW application
//

#if !defined(AFX_SRSLOGVIEW_H__4383DF3C_8105_4078_85CF_9E917C1A8490__INCLUDED_)
#define AFX_SRSLOGVIEW_H__4383DF3C_8105_4078_85CF_9E917C1A8490__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSRSLogViewApp:
// See SRSLogView.cpp for the implementation of this class
//

class CSRSLogViewApp : public CWinApp
{
  typedef CWinApp   CParrent;
protected:
  CMultiDocTemplate*        m_pDocTemplate;
public:
	CSRSLogViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSRSLogViewApp)
	public:
	virtual BOOL InitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

	virtual int               ExitInstance();

// Implementation
	//{{AFX_MSG(CSRSLogViewApp)
	afx_msg void OnAppAbout();
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintSetup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWindowNew(CCmdUI* pCmdUI);
	afx_msg void OnFileOpen();
	afx_msg void OnLogResize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRSLOGVIEW_H__4383DF3C_8105_4078_85CF_9E917C1A8490__INCLUDED_)
