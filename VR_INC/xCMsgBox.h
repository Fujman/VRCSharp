// SRSMessageBox.h: interface for the CMessageBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SRSMESSAGEBOX_H__8FBDC447_94B2_459A_9ED3_1320FE165D12__INCLUDED_)
#define AFX_SRSMESSAGEBOX_H__8FBDC447_94B2_459A_9ED3_1320FE165D12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "xCDialog.h"
#include "xCString.h"

#ifdef MULTILANG
#define  AfxMessageBox  ResourceMessageBox
#endif

//
class CMessageBox  : public CEmptyDialog
{
public:
	CMessageBox(int m_nMode=MB_OK, LPCTSTR strMessage=NULL, LPCTSTR strCaption=NULL,  
		LPCTSTR strControls=_T("OK\nCancel\nAbort\nRetry\nIgnore\nYes\nNo\nClose\nHelp\nApply\nRevert\nDefaults\nOpen\nSave\nSave As"));
	virtual ~CMessageBox();

	void SetStrings(LPCTSTR strMessage=NULL, LPCTSTR strCaption=NULL, LPCTSTR strControls=NULL);
	void SetMode(int nMode=-1);
	void SetFont(LPCTSTR strName, int lfSize=14, int lfWeight=FW_NORMAL);

	int    DoModal();

protected:
	void DesignBox();

protected:
	virtual BOOL          OnInitDialog();
	afx_msg int           OnCreate(LPCREATESTRUCT lpCreateStruct);

protected:
	CString m_szMessage, m_szCaption, m_szControls;
	int m_nMode;

// Controls
	CStatic* m_pStatic, *m_pIcon;
	CButton* m_pBtn1, *m_pBtn2, *m_pBtn3;

	CFont		font;
	LOGFONT		m_lf;

	CWnd *			m_pMWnd;
	CWnd *			m_pAWnd;

	

protected:
	enum
	{
		BUTTONWIDTH  = 75,
		BUTTONTEXTMARGX  = 10,
		BUTTONHEIGHT = 27,
		BUTTONMARGX   = 6,
		BUTTONMARGY   = 18,
		SIDEMARG      = 7,
		TOPMARG       = 12,
		BOTTOMMARG    = 10,
		MSGSHIFT      = 7,
		CENTER_MSG    = 0,
		MIN_WIDTH     =100,
	};
// message map handlers
	 afx_msg void  OnRetry();
	 afx_msg void  OnAbort();
	 afx_msg void  OnIgnore();
	 afx_msg void  OnYes();
	 afx_msg void  OnNo();

// overrides
virtual void OnCancel( ); 
virtual void OnOK(); 
	 
//  Loaders:
	 HICON IconFromType(int nIcon);
	 void SetDefaultFont();


	 DECLARE_MESSAGE_MAP()
};

int __AfxMessageBox(LPCTSTR lpszText, UINT nType = MB_OK, UINT nIDHelp = 0 );
int __AfxMessageBox(UINT nID, UINT nType = MB_OK, UINT nIDHelp = 0 );

int inline ResourceMessageBox(LPCTSTR lpszText, UINT nType = MB_OK, UINT nIDHelp = 0 )
{
  TCHAR szAppName[_MAX_PATH];
  LPCTSTR pszAppName;
  if (AfxGetApp())
    pszAppName = AfxGetApp()->m_pszAppName;
  else
  {
    pszAppName = szAppName;
    GetModuleFileName(NULL, szAppName, _MAX_PATH);
  }
	
  CString szButtonsText = ResourceString(3,"OK\nCancel\nAbort\nRetry\nIgnore\nYes\nNo\nClose\nHelp\nApply\nRevert\nDefaults\nOpen\nSave\nSave As");
  CMessageBox box(nType, lpszText,pszAppName,szButtonsText);
  return  box.DoModal();
}

int inline ResourceMessageBox(UINT nID, UINT nType = MB_OK, UINT nIDHelp = 0 )
{
  CString sz = ResourceString(nID);
  LPCTSTR lpszText = sz;
  TCHAR szAppName[_MAX_PATH];
  LPCTSTR pszAppName;
  if (AfxGetApp())
    pszAppName = AfxGetApp()->m_pszAppName;
  else
  {
    pszAppName = szAppName;
    GetModuleFileName(NULL, szAppName, _MAX_PATH);
  }
	
  CString szButtonsText = ResourceString(3,"OK\nCancel\nAbort\nRetry\nIgnore\nYes\nNo\nClose\nHelp\nApply\nRevert\nDefaults\nOpen\nSave\nSave As");
  CMessageBox box(nType, lpszText,pszAppName,szButtonsText);
  return  box.DoModal();
}

//  test usage see in .cpp file:
//  void TestSRSMessageBox();

#endif // !defined(AFX_SRSMESSAGEBOX_H__8FBDC447_94B2_459A_9ED3_1320FE165D12__INCLUDED_)
