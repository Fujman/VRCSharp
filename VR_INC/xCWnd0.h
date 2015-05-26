#ifndef __XCWND0_H
#define __XCWND0_H

#include "xCWnd.h"
#include <afxtempl.h>
#include "c_array.h"

inline CString CWnd__DumpWindowStyles(CWnd* pWnd)
{
  #define STYLE(n) { n, #n }
  static struct { DWORD dwStyle; LPCSTR szName; } s_styles[] = 
  {
      STYLE( WS_BORDER            )
    , STYLE( WS_CAPTION           )
    , STYLE( WS_CHILD             )
    , STYLE( WS_CLIPCHILDREN      )
    , STYLE( WS_CLIPSIBLINGS      )
    , STYLE( WS_DISABLED          )
    , STYLE( WS_DLGFRAME          )
    , STYLE( WS_GROUP             )
                                    
    , STYLE( WS_HSCROLL           )
    , STYLE( WS_ICONIC            )
    , STYLE( WS_MAXIMIZE          )
    , STYLE( WS_MAXIMIZEBOX       )
    , STYLE( WS_MINIMIZE          )
    , STYLE( WS_MINIMIZEBOX       )
    , STYLE( WS_OVERLAPPED        )
    , STYLE( WS_POPUP             )
    , STYLE( WS_SIZEBOX           )
    , STYLE( WS_SYSMENU           )
    , STYLE( WS_TABSTOP           )
                                    
    , STYLE( WS_THICKFRAME        )
    , STYLE( WS_TILED             )
    , STYLE( WS_TILEDWINDOW       )
    , STYLE( WS_VISIBLE           )
                                    
    , STYLE( WS_VSCROLL           )
  //, STYLE( WS_CHILDWINDOW       )
  //, STYLE( WS_OVERLAPPEDWINDOW  )
  //, STYLE( WS_POPUPWINDOW       )
  };
  static struct { DWORD dwStyleEx; LPCSTR szName; } s_stylesex[] = 
  {
      STYLE( WS_EX_DLGMODALFRAME  )
    , STYLE( WS_EX_NOPARENTNOTIFY )
    , STYLE( WS_EX_TOPMOST        )
    , STYLE( WS_EX_ACCEPTFILES    )
    , STYLE( WS_EX_TRANSPARENT    )

    , STYLE( WS_EX_MDICHILD       )
    , STYLE( WS_EX_TOOLWINDOW     )
    , STYLE( WS_EX_WINDOWEDGE     )
    , STYLE( WS_EX_CLIENTEDGE     )
    , STYLE( WS_EX_CONTEXTHELP    )

    , STYLE( WS_EX_RIGHT          )
    , STYLE( WS_EX_LEFT           )
    , STYLE( WS_EX_RTLREADING     )
    , STYLE( WS_EX_LTRREADING     )
    , STYLE( WS_EX_LEFTSCROLLBAR  )
    , STYLE( WS_EX_RIGHTSCROLLBAR )
                                  
    , STYLE( WS_EX_CONTROLPARENT  )
    , STYLE( WS_EX_STATICEDGE     )
    , STYLE( WS_EX_APPWINDOW      )

  //, STYLE( WS_EX_OVERLAPPEDWINDOW)
  //, STYLE( WS_EX_PALETTEWINDOW   )
  };
  #undef STYLE

  DWORD dwStyle   = pWnd->GetStyle();
  DWORD dwStyleEx = GetWindowLong( pWnd->GetSafeHwnd(), GWL_EXSTYLE );

  CString sz;
  sz.Format(_T("0x08.8X 0x08.8X "),dwStyle,dwStyleEx);

  if((dwStyle&WS_OVERLAPPEDWINDOW)==WS_OVERLAPPEDWINDOW) 
    dwStyle &= ~WS_OVERLAPPEDWINDOW, sz += _T("WS_OVERLAPPEDWINDOW ");
  if((dwStyle&WS_POPUPWINDOW)==WS_POPUPWINDOW) 
    dwStyle &= ~WS_POPUPWINDOW, sz += _T("WS_POPUPWINDOW ");

  if((dwStyleEx&WS_EX_OVERLAPPEDWINDOW)==WS_EX_OVERLAPPEDWINDOW) 
    dwStyleEx &= ~WS_EX_OVERLAPPEDWINDOW, sz += _T("WS_EX_OVERLAPPEDWINDOW ");
  if((dwStyleEx&WS_EX_PALETTEWINDOW)==WS_EX_PALETTEWINDOW) 
    dwStyleEx &= ~WS_EX_PALETTEWINDOW, sz += _T("WS_EX_PALETTEWINDOW ");

  DWORD dw = 1;
  for(dw=1; dw!=0; dw<<=1) {
    if(dwStyle&dw) {
      CString szItem;
      LPCSTR szName = NULL;
      for(int i=0; i<countof(s_styles); ++i)
        if(s_styles[i].dwStyle & dw)
          { szName = s_styles[i].szName; break; }
      if(szName!=NULL)
        szItem = CString(szName) + _T(" ");
      else
        szItem.Format(_T("0x%X "),dw);
      sz += szItem;
    }
  }
  for(dw=1; dw!=0; dw<<=1) {
    if(dwStyleEx&dw) {
      CString szItem;
      LPCSTR szName = NULL;
      for(int i=0; i<countof(s_stylesex); ++i)
        if(s_stylesex[i].dwStyleEx & dw)
          { szName = s_stylesex[i].szName; break; }
      if(szName!=NULL)
        szItem = CString(szName) + _T(" ");
      else
        szItem.Format(_T("0x%X "),dw);
      sz += szItem;
    }
  }
  return sz;
}


inline void CWnd__DumpWindowChilds(CWnd* pParent, BOOL bTraceStyles=FALSE)
{
  HWND hParent = pParent->GetSafeHwnd();
  CArray<HWND,HWND> aWnd;
  CWnd__EnumChilds(pParent->m_hWnd, aWnd);
  do {
    aWnd.InsertAt(0,pParent->m_hWnd);
  }while(pParent=pParent->GetParent());
  TRACE(_T("\n"));
  for(int i=0; i<aWnd.GetSize(); ++i){
    CWnd* pWnd = CWnd::FromHandle(aWnd[i]);
    CString sz; pWnd->GetWindowText(sz);
    if(sz.GetLength()>80)
      sz.Empty();
    CRect rc = CWnd__GetClientRect(pWnd);
    CPoint pt = rc.TopLeft();
    CPoint pt2 = rc.BottomRight();
    pWnd->ClientToScreen(&pt);
    pWnd->ClientToScreen(&pt2);
    TRACE(_T("%s %08.8X (%4d) [%08.8X] <%08.8X> (0x%8.8X,0x%8.8X)\"%s\" %dx%d %d;%d-%d;%d: %s%s"),
      (pWnd->m_hWnd==hParent?_T("* "):_T("  ")),
      pWnd->m_hWnd,
      pWnd->GetDlgCtrlID(),
      pWnd->GetParent()->GetSafeHwnd(),
      pWnd->GetOwner()->GetSafeHwnd(),
      pWnd->GetStyle(),
      CWnd__GetStyleEx(pWnd),
      sz,
      rc.Width(),
      rc.Height(),
      pt.x,
      pt.y,
      pt2.x,
      pt2.y,
      pWnd->m_hWnd?(pWnd->IsWindowEnabled()?_T("enabled"):_T("disabled")):_T("destroyed"),
      pWnd->m_hWnd?(pWnd->IsWindowVisible()?_T(",visible"):_T("")):_T("")
    );
    TRACE(_T("\n"));
  }
}

#endif//__XCWND0_H
#pragma once