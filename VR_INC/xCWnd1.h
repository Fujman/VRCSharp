// xCWnd1.h - not worked!
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCWND1_H__INCLUDED_)
#define AFX_XCWND1_H__INCLUDED_
#include <winuser.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

inline BOOL CWnd__ReCreate(CWnd* pNewWnd, HWND hWnd, 
  DWORD dwAddStyle=0, DWORD dwDelStyle=0, DWORD dwAddStyleEx=0, DWORD dwDelStyleEx=0)
{
#if 0
  CWnd* pWnd = CWnd::FromHandle(hWnd);
  CWnd& ctrl = *pNewWnd;
{
  WINDOWPLACEMENT wndpl = {sizeof(WINDOWPLACEMENT)};
                            //pWnd->GetWindowPlacement(&wndpl);
  DWORD dwHelpID        = 0;//pWnd->GetWindowContextHelpId();
  DWORD dwStyle         = 0;//pWnd->GetStyle();
  DWORD dwStyleEx       = 0;//pWnd->GetExStyle();
  HICON hIcon           = pWnd->GetIcon(FALSE);
  int   nID             = pWnd->GetDlgCtrlID();
  TCHAR szClass[512];      ;//::GetClassName(pWnd->m_hWnd,szClass,512);
  CString szText;          pWnd->GetWindowText(szText);
  CMenu* pMenu = pWnd->GetMenu( );
}
  CWnd* pwndParent      = pWnd->GetParent();
#endif

  CString szText;
  int nLen = ::GetWindowTextLength(hWnd);
  LPTSTR s = szText.GetBufferSetLength(nLen);
	int nOk  = ::GetWindowText(hWnd, s, nLen+1);
	szText.ReleaseBuffer(nLen);
  if(!nOk && nLen)
    return FALSE;

  WINDOWPLACEMENT wndpl = {sizeof(WINDOWPLACEMENT)};
  if(! ::GetWindowPlacement(hWnd,&wndpl)  ) return FALSE;
  TCHAR szClass[512];
  if(! ::GetClassName(hWnd,szClass,511) ) return FALSE;

  DWORD dwStyle   = ::GetWindowLong(hWnd,GWL_STYLE  );
  DWORD dwStyleEx = ::GetWindowLong(hWnd,GWL_EXSTYLE);
  DWORD dwHelpID  = ::GetWindowContextHelpId(hWnd);
  int   nCtrlID   = ::GetDlgCtrlID(hWnd);
  HWND  hwndParent= ::GetParent(hWnd);
  HMENU hMenu     = ::GetMenu(hWnd);            //TO DO: copy all items?
  HMENU hSysMenu  = ::GetSystemMenu(hWnd,FALSE);//TO DO: copy all items?
  HICON hIcon     = (HICON)::SendMessage(hWnd, WM_GETICON, ICON_SMALL, 0);
  HICON hIconBig  = (HICON)::SendMessage(hWnd, WM_GETICON, ICON_BIG  , 0);

  if(! ::DestroyWindow(hWnd) )
    return FALSE;

  dwStyle   |= dwAddStyle;
  dwStyleEx |= dwAddStyleEx;
  dwStyle   &= ~dwDelStyle;
  dwStyleEx &= ~dwDelStyleEx;

  BOOL bRet = pNewWnd->CreateEx(
    dwStyleEx,
    szClass,//lpszClassName,
    szText, //lpszWindowName,
    dwStyle,
    wndpl.rcNormalPosition,
    CWnd::FromHandlePermanent(hWnd),
    nCtrlID,
    NULL
  );
  if(!bRet)
    return FALSE;
  
  if(hIcon!=NULL)
    pNewWnd->CWnd::SetIcon(hIcon,FALSE);
  if(hIconBig!=NULL)
    pNewWnd->CWnd::SetIcon(hIcon,TRUE);
  pNewWnd->SetWindowPlacement(&wndpl);
  pNewWnd->SetWindowContextHelpId(dwHelpID);
  return TRUE;
}

inline BOOL CWnd__ReCreate(CWnd* pNewWnd, UINT nID, HWND hParentWnd, DWORD dwAddStyle=0, DWORD dwDelStyle=0, DWORD dwAddStyleEx=0, DWORD dwDelStyleEx=0)
  { return  CWnd__ReCreate(pNewWnd, ::GetDlgItem(hParentWnd,nID), dwAddStyle, dwDelStyle, dwAddStyleEx, dwDelStyleEx); }

inline BOOL CWnd__ReCreate(CWnd* pNewWnd, CWnd* pWnd, DWORD dwAddStyle=0, DWORD dwDelStyle=0, DWORD dwAddStyleEx=0, DWORD dwDelStyleEx=0) 
  { return  CWnd__ReCreate(pNewWnd, (pWnd!=NULL?pWnd->m_hWnd:(HWND)NULL), dwAddStyle, dwDelStyle, dwAddStyleEx, dwDelStyleEx);}

inline BOOL CWnd__ReCreate(CWnd* pNewWnd, UINT nID, CWnd* pParentWnd, DWORD dwAddStyle=0, DWORD dwDelStyle=0, DWORD dwAddStyleEx=0, DWORD dwDelStyleEx=0) 
  { return  CWnd__ReCreate(pNewWnd, nID,(pParentWnd!=NULL?pParentWnd->m_hWnd:(HWND)NULL), dwAddStyle, dwDelStyle, dwAddStyleEx, dwDelStyleEx); }

#endif // !defined(AFX_XCWND1_H__INCLUDED_)
