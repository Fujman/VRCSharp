#ifndef __YRECREAT_H
#define __YRECREAT_H

template <class CWND> ReCreate(CWND& ctrl, CWnd* pWnd, 
  DWORD dwAddStyle=0, DWORD dwDelStyle=0, 
  DWORD dwAddStyleEx=0, DWORD dwDelStyleEx=0)
{
  WINDOWPLACEMENT wndpl = {sizeof(WINDOWPLACEMENT)};
                          pWnd->GetWindowPlacement(&wndpl);
  DWORD dwHelp          = pWnd->GetWindowContextHelpId();
  DWORD dwStyle         = pWnd->GetStyle();
  DWORD dwStyleEx       = pWnd->GetExStyle();
  HICON hIcon           = pWnd->GetIcon(FALSE);
  int   nID             = pWnd->GetDlgCtrlID();
  CString szText;         pWnd->GetWindowText(szText);
  CWnd* pwndParent      = pWnd->GetParent();
  TCHAR szClass[512];   ::GetClassName(pWnd->m_hWnd,szClass,512);

  dwStyle   |= dwAddStyle;
  dwStyleEx |= dwAddStyleEx;
  dwStyle   &= ~dwDelStyle;
  dwStyleEx &= ~dwDelStyleEx;

  pWnd->DestroyWindow();

  BOOL bRet = ctrl.CWnd::CreateEx(
    dwStyleEx,
    szClass,//lpszClassName,
    szText, //lpszWindowName,
    dwStyle,
    wndpl.rcNormalPosition,
    pwndParent,
    nID,
    NULL
  );
  

  if(hIcon!=NULL)
    ctrl.CWnd::SetIcon(hIcon,FALSE);
  ctrl.SetWindowPlacement(&wndpl);
  ctrl.SetWindowContextHelpId(dwHelp);
  return bRet;
}

template <class CWND> ReCreate(CWND& ctrl, UINT nID, CWnd* pParentWnd, 
  DWORD dwAddStyle=0, DWORD dwDelStyle=0, 
  DWORD dwAddStyleEx=0, DWORD dwDelStyleEx=0)
{
  CWnd* pWnd = pParentWnd->GetDlgItem(nID);
  if(pWnd!=NULL)
    return ReCreate(ctrl,pWnd,dwAddStyle, dwDelStyle, dwAddStyleEx, dwDelStyleEx);
  return FALSE;
}


template <class CWND> ReCreate4(CWND& ctrl, CWnd* pWnd, //CComboBox like
  DWORD dwDelStyle  =0, DWORD dwAddStyle  =0, 
  DWORD dwDelStyleEx=0, DWORD dwAddStyleEx=0) //AY 07.07.2008
{
  WINDOWPLACEMENT wndpl = {sizeof(WINDOWPLACEMENT)};
                          pWnd->GetWindowPlacement(&wndpl);
  DWORD dwHelp          = pWnd->GetWindowContextHelpId();
  DWORD dwStyle         = pWnd->GetStyle();
  DWORD dwStyleEx       = pWnd->GetExStyle();
  HICON hIcon           = pWnd->GetIcon(FALSE);
  int   nID             = pWnd->GetDlgCtrlID();
  CString szText;         pWnd->GetWindowText(szText);
  CWnd* pwndParent      = pWnd->GetParent();
  CFont* pFont          = pWnd->GetFont();
  TCHAR szClass[512];   ::GetClassName(pWnd->m_hWnd,szClass,512);

  dwStyle   &= ~dwDelStyle;
  dwStyleEx &= ~dwDelStyleEx;
  dwStyle   |= dwAddStyle;
  dwStyleEx |= dwAddStyleEx;

  pWnd->DestroyWindow();

  BOOL bRet = ctrl.Create(
    dwStyle,
    wndpl.rcNormalPosition,
    pwndParent,
    nID
  );
  ctrl.ModifyStyleEx(0,dwStyleEx);
  ctrl.SetFont(pFont);
  
  if(hIcon!=NULL)
    ctrl.CWnd::SetIcon(hIcon,FALSE);
//ctrl.SetWindowPlacement(&wndpl);
//ctrl.SetWindowContextHelpId(dwHelp);
  return bRet;

  const UINT EDIT_STYLES = 0
    | ES_LEFT      
    | ES_CENTER    
    | ES_RIGHT     
    | ES_MULTILINE 
    | ES_UPPERCASE 
    | ES_LOWERCASE 
    | ES_PASSWORD  
    | ES_AUTOVSCROLL
    | ES_AUTOHSCROLL
    | ES_NOHIDESEL  
    | ES_OEMCONVERT 
    | ES_READONLY   
    | ES_WANTRETURN 
  ;
  const UINT EXTENDED_STYLES = 0
    | WS_EX_DLGMODALFRAME     
    | WS_EX_NOPARENTNOTIFY    
    | WS_EX_TOPMOST           
    | WS_EX_ACCEPTFILES       
    | WS_EX_TRANSPARENT       
    | WS_EX_MDICHILD          
    | WS_EX_TOOLWINDOW        
    | WS_EX_WINDOWEDGE        
    | WS_EX_CLIENTEDGE        
    | WS_EX_CONTEXTHELP       
    | WS_EX_RIGHT             
    | WS_EX_LEFT              
    | WS_EX_RTLREADING        
    | WS_EX_LTRREADING        
    | WS_EX_LEFTSCROLLBAR     
    | WS_EX_RIGHTSCROLLBAR    
    | WS_EX_CONTROLPARENT     
    | WS_EX_STATICEDGE        
    | WS_EX_APPWINDOW         
  ; 

}


#endif//__YRECREAT_H
#pragma once

