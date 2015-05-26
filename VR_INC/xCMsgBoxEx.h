#ifndef __XCMSGBOXEX_H
#define __XCMSGBOXEX_H
#include "xCMsgBox.h"

class CCheckedMessageBox: public CMessageBox
{
public:
  static CString GetAppName()
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
    return pszAppName;
  }

  static CString GetDefWords()
  {
    return ResourceString(3,"OK\nCancel\nAbort\nRetry\nIgnore\nYes\nNo\nClose\nHelp\nApply\nRevert\nDefaults\nOpen\nSave\nSave As");
  }

	CCheckedMessageBox(int nMode=MB_OK, LPCTSTR szMessage=NULL, LPCTSTR szCaption=NULL)
    : CMessageBox(nMode,szMessage,(szCaption?szCaption:GetAppName()),GetDefWords()) 
    { m_bCheck = FALSE; }

  void SetCheckLabel(LPCTSTR szLabel) 
    { m_szCheck = szLabel;}

  void SetCheck(BOOL bCheck=TRUE) 
    { m_bCheck = bCheck; }
  BOOL GetCheck() const
    { return m_bCheck; }

	virtual BOOL OnInitDialog()
  {
    BOOL bRet = CMessageBox::OnInitDialog();
    CRect rc = CWnd__GetRect(this);

    CArray<HWND,HWND> aWnd;
    CWnd__EnumChilds(this, aWnd);
    CRect rcOK(0,0,0,0);

    int i=0;
    for(i=0; i<aWnd.GetSize(); ++i){ 
      CRect rc = CWnd__GetRect(aWnd[i]); //TRACE(_T("l=%d  t=%d  r=%d  b=%d \n"), rc); 
      if(rcOK.top<rc.top)
        rcOK = rc;
    }
    int yShift = rcOK.Height();
    
    rc.bottom += yShift;
    CWnd__SetRect(this,rc);

    CRect rcCheck = rcOK;
    UINT  idCheck = 100;
    CFont* pFont = NULL;
    for(i=0; i<aWnd.GetSize(); ++i){ 
      CRect rc = CWnd__GetRect(aWnd[i]); //TRACE(_T("l=%d  t=%d  r=%d  b=%d \n"), rc); 
      CWnd* pWnd = CWnd::FromHandle(aWnd[i]);
      UINT  id = pWnd?pWnd->GetDlgCtrlID():0;
      idCheck = max(idCheck,id);
      pFont = pWnd?pWnd->GetFont():NULL;
      if(rcOK.top==rc.top){
        rcCheck.left  = min(rcCheck.left,rc.left);
        rcCheck.right = max(rcCheck.right,rc.right);
        rc.top    += yShift;
        rc.bottom += yShift;
        CWnd__SetRect(aWnd[i],rc);
      }
    }
  
    rcCheck.top   -= 8;
    rcCheck.bottom-= 8;
    DWORD dwStyle = WS_CHILDWINDOW|WS_VISIBLE|WS_TABSTOP|BS_TEXT|BS_AUTOCHECKBOX;
    VERIFY( m_check.Create(m_szCheck,dwStyle,rcCheck,this,idCheck+1) );
    m_check.SetFont(pFont);
    m_check.SetCheck(m_bCheck);
    return bRet;
  }

  virtual LRESULT WindowProc( UINT message, WPARAM wParam, LPARAM lParam )
  {
    if(message==WM_DESTROY)
      m_bCheck = m_check.GetCheck();
    return CMessageBox::WindowProc(message, wParam, lParam);
  }

protected:
  CButton   m_check;
  CString   m_szCheck;
  BOOL      m_bCheck;
};


#endif//__XCMSGBOXEX_H
#pragma once
