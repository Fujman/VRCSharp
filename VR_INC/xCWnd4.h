#ifndef __XCWND4_H
#define __XCWND4_H

inline CRect CWnd__ScreenToClient(HWND hWnd, CRect rc)
{
  CPoint pt0 = rc.TopLeft();
  CPoint pt1 = rc.BottomRight();
  ::ScreenToClient(hWnd,&pt0);
  ::ScreenToClient(hWnd,&pt1);
  return CRect(pt0,pt1);
}
inline CRect CWnd__ClientToScreen(HWND hWnd, CRect rc)
{
  CPoint pt0 = rc.TopLeft();
  CPoint pt1 = rc.BottomRight();
  ::ClientToScreen(hWnd,&pt0);
  ::ClientToScreen(hWnd,&pt1);
  return CRect(pt0,pt1);
}

inline CRect CWnd__GetClientRect(HWND hWnd, BOOL bScreen)
{
  CRect rc(0,0,0,0);
  ::GetClientRect(hWnd,&rc); 
  if(bScreen)
    return CWnd__ClientToScreen(hWnd,&rc);
  return rc;
}
inline CRect CWnd__GetClientRect(UINT nID, HWND hParentWnd, BOOL bScreen)
{
  return CWnd__GetClientRect(::GetDlgItem(hParentWnd,nID),bScreen);
}
inline CRect CWnd__GetClientRect(CWnd* pWnd, BOOL bScreen) 
{
  return CWnd__GetClientRect((pWnd!=NULL?pWnd->m_hWnd:(HWND)NULL),bScreen);
}
inline CRect CWnd__GetClientRect(UINT nID, CWnd* pParentWnd, BOOL bScreen) 
{
  return CWnd__GetClientRect(nID,(pParentWnd!=NULL?pParentWnd->m_hWnd:(HWND)NULL),bScreen);
}


inline CRect CWnd__GetRect(HWND hWnd, BOOL bScreen)
{
  WINDOWPLACEMENT wndpl={sizeof(WINDOWPLACEMENT)};
  ::GetWindowPlacement(hWnd,&wndpl);
  if(bScreen && (::GetWindowLong(hWnd,GWL_STYLE)&WS_CHILD)!=0)
    return CWnd__ClientToScreen(hWnd,&wndpl.rcNormalPosition);
  return wndpl.rcNormalPosition;
}

inline CRect CWnd__GetRect(UINT nID, HWND hParentWnd, BOOL bScreen)
{
  return CWnd__GetRect(::GetDlgItem(hParentWnd,nID),bScreen) ;
}

inline CRect CWnd__GetRect(CWnd* pWnd, BOOL bScreen) 
{
  return CWnd__GetRect((pWnd!=NULL?pWnd->m_hWnd:(HWND)NULL),bScreen);
}

inline CRect CWnd__GetRect(UINT nID, CWnd* pParentWnd, BOOL bScreen) 
{
  return CWnd__GetRect(nID,(pParentWnd!=NULL?pParentWnd->m_hWnd:(HWND)NULL),bScreen);
}

#endif//__XCWND4_H
#pragma once
