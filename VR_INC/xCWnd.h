#ifndef __XCWND_H
#define __XCWND_H
#include <afxtempl.h>

// AY 17.12.2007
inline DWORD CWnd__GetStyle(HWND hWnd)
{
  return (DWORD)::GetWindowLong(hWnd, GWL_STYLE);
}
inline DWORD CWnd__GetStyleEx(HWND hWnd)
{
  return (DWORD)::GetWindowLong(hWnd, GWL_EXSTYLE);
}
inline DWORD CWnd__GetStyle(CWnd* pWnd)
{
  return (DWORD)::GetWindowLong(pWnd->GetSafeHwnd(), GWL_STYLE);
}
inline DWORD CWnd__GetStyleEx(CWnd* pWnd)
{
  return (DWORD)::GetWindowLong(pWnd->GetSafeHwnd(), GWL_EXSTYLE);
}
inline DWORD CWnd__GetStyle(UINT nID, CWnd* pParentWnd)
{
  return (DWORD)::GetWindowLong(pParentWnd->GetDlgItem(nID)->GetSafeHwnd(), GWL_STYLE);
}
inline DWORD CWnd__GetStyleEx(UINT nID, CWnd* pParentWnd)
{
  return (DWORD)::GetWindowLong(pParentWnd->GetDlgItem(nID)->GetSafeHwnd(), GWL_EXSTYLE);
}


inline CRect CWnd__GetClientRect(HWND hWnd)
{
  CRect rc(0,0,0,0); 
  ::GetClientRect(hWnd,&rc); 
  return rc;
}
inline CRect CWnd__GetClientRect(UINT nID, HWND hParentWnd)
{
  return CWnd__GetClientRect(::GetDlgItem(hParentWnd,nID));
}
inline CRect CWnd__GetClientRect(CWnd* pWnd) 
{
  return CWnd__GetClientRect((pWnd!=NULL?pWnd->m_hWnd:(HWND)NULL));
}
inline CRect CWnd__GetClientRect(UINT nID, CWnd* pParentWnd) 
{
  return CWnd__GetClientRect(nID,(pParentWnd!=NULL?pParentWnd->m_hWnd:(HWND)NULL));
}


inline CRect CWnd__GetRect(HWND hWnd)
{
  WINDOWPLACEMENT wndpl={sizeof(WINDOWPLACEMENT)};
  ::GetWindowPlacement(hWnd,&wndpl);
  return wndpl.rcNormalPosition;
}

inline CRect CWnd__GetRect(UINT nID, HWND hParentWnd)
{
  return CWnd__GetRect(::GetDlgItem(hParentWnd,nID)) ;
}

inline CRect CWnd__GetRect(CWnd* pWnd) 
{
  return CWnd__GetRect((pWnd!=NULL?pWnd->m_hWnd:(HWND)NULL));
}

inline CRect CWnd__GetRect(UINT nID, CWnd* pParentWnd) 
{
  return CWnd__GetRect(nID,(pParentWnd!=NULL?pParentWnd->m_hWnd:(HWND)NULL));
}

inline CRect CWnd__SetRect(HWND hWnd, const CRect& rc, UINT showCmd=SW_SHOWNORMAL)
{
  WINDOWPLACEMENT wndpl = {sizeof(WINDOWPLACEMENT)};
  ::GetWindowPlacement(hWnd,&wndpl);
  CRect rcOld = wndpl.rcNormalPosition;
  wndpl.rcNormalPosition = rc;
  wndpl.showCmd = showCmd;
  ::SetWindowPlacement(hWnd,&wndpl);
  return rcOld;
}

inline CRect CWnd__SetRect(CWnd* pWnd, const CRect& rc, UINT showCmd=SW_SHOWNORMAL)
{
  return CWnd__SetRect((pWnd!=NULL?pWnd->m_hWnd:(HWND)NULL),rc,showCmd);
}

inline CRect CWnd__SetRect(UINT nID, HWND hParentWnd, const CRect& rc, UINT showCmd=SW_SHOWNORMAL)
{
  return CWnd__SetRect(::GetDlgItem(hParentWnd,nID),rc,showCmd);
}

inline CRect CWnd__SetRect(UINT nID, CWnd* pParentWnd, const CRect& rc, UINT showCmd=SW_SHOWNORMAL)
{
  return CWnd__SetRect(nID,(pParentWnd!=NULL?pParentWnd->m_hWnd:(HWND)NULL),rc,showCmd);
}

inline CRect CWnd__SetRectEx(HWND hWnd, const CRect& rc)
{
  WINDOWPLACEMENT wndpl = {sizeof(WINDOWPLACEMENT)};
  ::GetWindowPlacement(hWnd,&wndpl);
  CRect rcOld = wndpl.rcNormalPosition;
  wndpl.rcNormalPosition = rc;
  wndpl.showCmd = SW_SHOWNORMAL;
  if(!(GetWindowLong(hWnd,GWL_STYLE)&WS_VISIBLE))
    wndpl.showCmd = SW_HIDE;
  ::SetWindowPlacement(hWnd,&wndpl);
  return rcOld;
}

inline CRect CWnd__SetRectEx(CWnd* pWnd, const CRect& rc)
{
  return CWnd__SetRectEx((pWnd!=NULL?pWnd->m_hWnd:(HWND)NULL),rc);
}



inline CRect CWnd__GetScreenPart(int nxSize=50/*%*/, int nySize=0) // 1/4 by square of screen by default
{
  int cx = ::GetSystemMetrics(SM_CXSCREEN);
  int cy = ::GetSystemMetrics(SM_CYSCREEN);
  if(nySize==0) 
    nySize = nxSize;
  int cxDlg = (cx*nxSize)/100;
  int cyDlg = (cy*nySize)/100;
  int x0 = (cx - cxDlg)/2;
  int y0 = (cy - cyDlg)/2;
  int x1 = x0 + cxDlg;
  int y1 = y0 + cyDlg;
  return CRect(x0,y0,x1,y1);
}

inline CRect CWnd__GetScreenPartCenteredBy(HWND hWnd, int nxSize=50/*%*/, int nySize=0)
{
  CRect rc = CWnd__GetScreenPart(nxSize, nySize);
  CRect rcFrame = hWnd?CWnd__GetRect(hWnd):rc;
  int xPos = (rcFrame.Width()-rc.Width())/2;
  rc += CPoint(xPos + rcFrame.left - rc.left, 0);
  int yPos = (rcFrame.Height()-rc.Height())/2;
  rc += CPoint(0, yPos + rcFrame.top - rc.top);
  return rc;
}

inline CRect CWnd__GetScreenPartCenteredBy(CWnd* pWnd, int nxSize=50/*%*/, int nySize=0)
{
  CRect rc = CWnd__GetScreenPartCenteredBy(pWnd->GetSafeHwnd(), nxSize, nySize);
  return rc;
}

inline void CWnd__Hide(UINT nID, CWnd* pParentWnd)
{
  CWnd* pWnd = pParentWnd->GetDlgItem(nID);
  if(pWnd!=NULL) 
    { pWnd->EnableWindow(FALSE); pWnd->ShowWindow(SW_HIDE); }
}

inline void CWnd__Show(UINT nID, CWnd* pParentWnd)
{
  CWnd* pWnd = pParentWnd->GetDlgItem(nID);
  if(pWnd!=NULL) 
    { pWnd->ShowWindow(SW_SHOW); pWnd->EnableWindow(TRUE); }
}

inline void CWnd__Hide(CWnd* pWnd)
{
  if(pWnd!=NULL) 
    { pWnd->EnableWindow(FALSE); pWnd->ShowWindow(SW_HIDE); }
}

inline void CWnd__Show(CWnd* pWnd)
{
  if(pWnd!=NULL) 
    { pWnd->ShowWindow(SW_SHOW); pWnd->EnableWindow(TRUE); }
}


inline void CWnd__Enable(CWnd* pWnd)
{
  if(pWnd!=NULL) 
    { pWnd->EnableWindow(TRUE); }
}
inline void CWnd__Enable(UINT nID, CWnd* pParentWnd)
{
  CWnd__Enable( pParentWnd->GetDlgItem(nID) );
}

inline void CWnd__Disable(CWnd* pWnd)
{
  if(pWnd!=NULL) 
    { pWnd->EnableWindow(FALSE); }
}
inline void CWnd__Disable(UINT nID, CWnd* pParentWnd)
{
  CWnd__Disable( pParentWnd->GetDlgItem(nID) );
}

inline CString CWnd__GetText(CWnd* pWnd)
{
  if(pWnd!=NULL) 
    { CString sz; pWnd->GetWindowText(sz); return sz; }
  return "";
}
inline CString CWnd__GetText(UINT nID, CWnd* pParentWnd)
{
  return CWnd__GetText( pParentWnd->GetDlgItem(nID) );
}

inline void CWnd__Union(UINT nID, UINT nHideID, CWnd* pParentWnd)
{
  CWnd* pWnd = pParentWnd->GetDlgItem(nID);
  CWnd* pHideWnd = pParentWnd->GetDlgItem(nHideID);
  if(pWnd==NULL || pHideWnd==NULL)
    return;
  CRect rc = CWnd__GetRect(pWnd->m_hWnd) | CWnd__GetRect(pHideWnd->m_hWnd);
  CWnd__Hide(pHideWnd);
  CWnd__SetRect(pWnd->m_hWnd,rc);
}

inline void CWnd__Hide(HWND hWnd)
{
  if(hWnd!=NULL) 
    { ::EnableWindow(hWnd,FALSE); ::ShowWindow(hWnd,SW_HIDE); }
}

inline void CWnd__Show(HWND hWnd)
{
  if(hWnd!=NULL) 
    { ::ShowWindow(hWnd,SW_SHOW); ::EnableWindow(hWnd,TRUE); }
}

inline void CWnd__ClientOnly(CWnd* pWnd, BOOL bClientOnly=TRUE, DWORD dwStyle=0)
{
  if(dwStyle==0)
    dwStyle = WS_CAPTION|WS_THICKFRAME|WS_SYSMENU|WS_MAXIMIZEBOX|WS_MINIMIZEBOX;
  if(pWnd!=NULL && pWnd->m_hWnd!=NULL){
    CRect rcS = CWnd__GetClientRect(pWnd); pWnd->ClientToScreen(&rcS);

    BOOL bVisible = (pWnd->GetStyle()&WS_VISIBLE);
    UINT nFlags = SWP_FRAMECHANGED;
    if(!bVisible)  
      nFlags|= SWP_HIDEWINDOW;//AY 26.12.2013 OLD: always hide

    if(bClientOnly) pWnd->ModifyStyle(dwStyle,0,nFlags);
    else            pWnd->ModifyStyle(0,dwStyle,nFlags);

    if(bClientOnly){
      CWnd__SetRectEx(pWnd,rcS);//AY 13.12.2013 OLD:CWnd__SetRect()
    }else{
      CRect rcC = CWnd__GetClientRect(pWnd); pWnd->ClientToScreen(&rcC);
      CRect rcG = CWnd__GetRect(pWnd);
      rcS.top -= (rcC.top-rcG.top);
      rcS.left -= (rcC.left-rcG.left);
      rcS.right += (rcG.right-rcC.right);
      rcS.bottom += (rcG.bottom-rcC.bottom);
      CWnd__SetRectEx(pWnd,rcS);//AY 13.12.2013 OLD:CWnd__SetRect()
    }
  }
}

//// enumeration /////////////////////////////////////////////

template <class TYPE> class CWnd__Enum
  { public: static BOOL CALLBACK EnumProc(HWND hwnd, LPARAM lParam); };

template <class TYPE> BOOL CALLBACK CWnd__Enum<TYPE>::
  EnumProc(HWND hwnd, LPARAM lParam)
{ 
  struct PARAMS {CArray<HWND,HWND>* paWnd; LPCRECT lprc; DWORD dwStyle,dwStyleEx,dwStyleNo,dwStyleExNo;}
    *params = (PARAMS*)lParam;
  CRect rc  = (params->lprc!=NULL)?
    CWnd__GetRect(hwnd) : CRect(0,0,0,0);
  DWORD dw0 = (~params->dwStyle|params->dwStyleNo)?
    ::GetWindowLong(hwnd,GWL_STYLE)  :0xFFFFFFFF;
  DWORD dw1 = (~params->dwStyleEx|params->dwStyleExNo)?
    ::GetWindowLong(hwnd,GWL_EXSTYLE):0xFFFFFFFF;
  if(!rc.IsRectNull() && (CRect(params->lprc)|rc)!=CRect(params->lprc))
    return TRUE;//skip by position
  if((params->dwStyle&dw0)==0 || (params->dwStyleNo&dw0)!=0)
    return TRUE;//skip by style
  if((params->dwStyleEx&dw1)==0 || (params->dwStyleExNo&dw1)!=0)
    return TRUE;//skip by extended style
  params->paWnd->Add(hwnd);
  return TRUE;
}

inline BOOL CWnd__EnumChilds(HWND hWnd, CArray<HWND,HWND>& aWnd, LPCRECT lprc=NULL, DWORD dwStyle=0xFFFFFFFF, DWORD dwStyleEx=0xFFFFFFFF, DWORD dwStyleNo=0, DWORD dwStyleExNo=0)
{
  struct PARAMS {CArray<HWND,HWND>* paWnd; LPCRECT lprc; DWORD dwStyle,dwStyleEx,dwStyleNo,dwStyleExNo;}
    params = { &aWnd, lprc, dwStyle, dwStyleEx, dwStyleNo, dwStyleExNo };
  return ::EnumChildWindows(hWnd,CWnd__Enum<void>::EnumProc,(LPARAM)&params);
}

inline BOOL CWnd__EnumChilds(UINT nID, HWND hParentWnd, CArray<HWND,HWND>& aWnd, LPCRECT lprc=NULL, DWORD dwStyle=0xFFFFFFFF, DWORD dwStyleEx=0xFFFFFFFF, DWORD dwStyleNo=0, DWORD dwStyleExNo=0)
{
  return CWnd__EnumChilds(::GetDlgItem(hParentWnd,nID),aWnd,lprc,dwStyle,dwStyleEx,dwStyleNo,dwStyleExNo);
}
inline BOOL CWnd__EnumChilds(CWnd* pWnd, CArray<HWND,HWND>& aWnd, LPCRECT lprc=NULL, DWORD dwStyle=0xFFFFFFFF, DWORD dwStyleEx=0xFFFFFFFF, DWORD dwStyleNo=0, DWORD dwStyleExNo=0) 
{
  return CWnd__EnumChilds((pWnd!=NULL?pWnd->m_hWnd:(HWND)NULL),aWnd,lprc,dwStyle,dwStyleEx,dwStyleNo,dwStyleExNo);
}
inline BOOL CWnd__EnumChilds(UINT nID, CWnd* pParentWnd, CArray<HWND,HWND>& aWnd, LPCRECT lprc=NULL, DWORD dwStyle=0xFFFFFFFF, DWORD dwStyleEx=0xFFFFFFFF, DWORD dwStyleNo=0, DWORD dwStyleExNo=0) 
{
  return CWnd__EnumChilds(nID,(pParentWnd!=NULL?pParentWnd->m_hWnd:(HWND)NULL),aWnd,lprc,dwStyle,dwStyleEx,dwStyleNo,dwStyleExNo);
}

#endif//__XCWND_H
#pragma once
