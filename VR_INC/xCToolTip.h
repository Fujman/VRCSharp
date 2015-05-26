//UNICODE
#ifndef __XCTOOLTIP_H
#define __XCTOOLTIP_H
#include "xCString.h"
#include "YString.h"

/* Notes:
case:CToolTipedDialog / CToolTypeCtrl   RESULT:
        text static      text static    text from control GetToolTipText()
        text static     text callback   text from dialog m_tooltip or GetToolTipText(UINT nID)
       text callback    text callback   text from dialog GetToolTipText(UINT nID)
       text callback     text static    text from dialog GetToolTipText(UINT nID), then from control GetToolTipText()

case:CToolTipedDialog / CCtrl           RESULT:
        text static           -         text from dialog m_tooltip
       text callback          -         text from dialog m_tooltip or GetToolTipText(UINT nID)

case:CDialog          / CToolTypeCtrl   RESULT:
             -           text static    text from control GetToolTipText()
             -          text callback   ERROR or NO TEXT
*/

////////////////////////////////////////////////////////////////////
// CToolTipedDialog

//ATTENTION!: All controls in dialog must have ID>=1000, tools<1000!

template <class CDIALOG> class CToolTipedDialog: public CDIALOG
{ 
protected:
  CToolTipCtrl  m_tooltip;//used as container for controls tooltips text etc.
//HHOOK         m_hhook;
  CFont         m_font;
public:
  CToolTipedDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL):
    CDIALOG(lpszTemplateName, pParentWnd) { /*m_hhook = NULL;*/ }
  CToolTipedDialog( UINT nIDTemplate, CWnd* pParentWnd = NULL ):
    CDIALOG(nIDTemplate, pParentWnd) { /*m_hhook = NULL;*/ }
  CToolTipedDialog():
    CDIALOG() { /*m_hhook = NULL;*/ }
public:
  virtual CString       GetToolTipText(UINT nID);
  BOOL                  AddCtrl(UINT nIDCtrl, LPCTSTR lpszText=LPSTR_TEXTCALLBACK, LPCRECT lpRectTool=NULL);
  BOOL                  AddCtrl(UINT nIDCtrl, UINT nIDText,LPCRECT lpRectTool=NULL);
  BOOL                  AddTool(UINT nIDTool, LPCTSTR lpszText=LPSTR_TEXTCALLBACK, LPCRECT lpRectTool=NULL);
  BOOL                  AddTool(UINT nIDTool, UINT nIDText, LPCRECT lpRectTool=NULL);//0..999
  void                  DelCtrl(UINT nIDCtrl);
  void                  DelTool(UINT nIDTool);
protected:
  BOOL                  OnInitDialog();
  void                  OnToolTipNeedTextA(NMHDR* pNotifyStruct, LRESULT* result);
  void                  OnToolTipNeedTextW(NMHDR* pNotifyStruct, LRESULT* result);
//BOOL                  PreTranslateMessage(MSG* pMsg);
  LRESULT               WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

////////////////////////////////////////////////////////////////////
// CToolTipedControl<CCONTROL>

template <class CCONTROL> class CToolTipedControl: public CCONTROL
{ 
protected:
  CString               m_szToolTipText;
  CToolTipCtrl          m_tooltip;
  BOOL                  m_bClickNotify;
public:
  virtual void          SetToolTipText(LPCTSTR szText, UINT unused=0);
  virtual CString       GetToolTipText(UINT unused=0);
  virtual BOOL          EnableClickNotify(BOOL bEnable=TRUE);
  static  CString       ToolTipTextDecore(LPCTSTR szText);

protected:
  void                  OnControlNeedTextA(NMHDR * pNotifyStruct, LRESULT * result);
  void                  OnControlNeedTextW(NMHDR * pNotifyStruct, LRESULT * result);
//BOOL                  PreTranslateMessage(MSG* pMsg);
  LRESULT               WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

////////////////////////////////////////////////////////////////////
// CToolTipedSlider<CSLIDER>

template <class CSLIDER> class CToolTipedSlider: public CToolTipedControl<CSLIDER>
{ 
public:
  virtual void          SetToolTipText(LPCTSTR szFormat=_T("%d"), UINT unused=0);
  virtual CString       GetToolTipText(UINT unused=0);
protected:
  void                  OnControlNeedTextA(NMHDR * pNotifyStruct, LRESULT * result);
  void                  OnControlNeedTextW(NMHDR * pNotifyStruct, LRESULT * result);
  LRESULT               WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};


// CToolTipedDialog implementation /////////////////////////////////////////////

template <class CDIALOG> inline CString 
CToolTipedDialog<CDIALOG>::GetToolTipText(UINT nID)
{
  CToolInfo ti;
  if(nID>=1000 && m_tooltip.m_hWnd!=NULL && m_tooltip.GetToolInfo(ti,this,nID)){
    if(ti.lpszText!=LPSTR_TEXTCALLBACK)
      return ti.lpszText;
    else
      return "";
  }
#ifdef $_DEBUG
  CString sz;
  if(nID<1000)
    sz.Format("Tool #%u",nID);
  else
    sz.Format("Ctrl #%u",nID);
  return sz;
#else
  if(nID<1000)
    return "";//TOOL
  else
    return "";//CTRL
#endif
}
/*
template <class CDIALOG> LRESULT
CALLBACK CToolTipedDialog<CDIALOG>::
MouseHook(int nCode, WPARAM wParam, LPARAM lParam)
{
  MSG msg;
  CWPSTRUCT* pmes_struct;
  pmes_struct = (CWPSTRUCT *)lParam;
  msg.hwnd = pmes_struct->hwnd;
  if(::IsChild(hWnd, msg.hwnd))
    msg.hwnd = hWnd;
  msg.message = pmes_struct->message;
  msg.lParam = pmes_struct->lParam;
  msg.wParam = pmes_struct->wParam;
  m_tooltip.RelayEvent(&msg);
  m_tooltip.Activate(TRUE);
  return ::CallNextHookEx(hhook, nCode, wParam, lParam);
}
*/
template <class CDIALOG> inline BOOL
CToolTipedDialog<CDIALOG>::OnInitDialog()
{
  BOOL bRet = CDIALOG::OnInitDialog();
  //m_hhook = ::SetWindowsHookEx(WH_MOUSE, MouseHook, NULL, GetCurrentThreadId());  
  m_tooltip.Create(this);
  m_tooltip.Activate(TRUE);
#ifdef _DEBUG
  int nDelayAutopop = m_tooltip.GetDelayTime(TTDT_AUTOPOP);
  int nDelayReshow  = m_tooltip.GetDelayTime(TTDT_RESHOW);
  int nDelayInitial = m_tooltip.GetDelayTime(TTDT_INITIAL);
  m_tooltip.SetDelayTime(TTDT_INITIAL,nDelayInitial/2);

  LOGFONT lf = {0}; GetFont()->GetLogFont(&lf);
  _tcscpy(lf.lfFaceName,ResourceFont(lf.lfFaceName));
  //m_font.CreateFontIndirect(&lf);
  //m_tooltip.SetFont(&m_font);
#endif
  return bRet;  // return TRUE  unless you set the focus to a control
}

//reflect to control
template <class CDIALOG> inline void
CToolTipedDialog<CDIALOG>::OnToolTipNeedTextA(NMHDR* pNotifyStruct, LRESULT* result)
{
  LPNMTTDISPINFOA lpnmtdi = (LPNMTTDISPINFOA)pNotifyStruct;
  UINT nNotifyCode = pNotifyStruct->code;//==TTN_NEEDTEXTA
  HWND hwndToolTip = pNotifyStruct->hwndFrom;
  HWND hwndControl = NULL;
  UINT nIDCtrl = 0;//always 0
  UINT nIDTool = 0;//always 0
  UINT nID     = 0;
  if(lpnmtdi->uFlags&TTF_IDISHWND)
    hwndControl = (HWND)pNotifyStruct->idFrom;
  else if(pNotifyStruct->idFrom<1000)
    nID = nIDTool = pNotifyStruct->idFrom;
  else
    hwndControl = GetDlgItem(pNotifyStruct->idFrom)->m_hWnd;
  if(hwndControl!=NULL)
    nID = nIDCtrl = ::GetDlgCtrlID(hwndControl);

  if(nID!=0) {
    YStringA sz = GetToolTipText(nID);
    if(!sz.IsEmpty() && sizeof(lpnmtdi->szText)+1>sz.GetLength()){
      strncpy(lpnmtdi->szText,sz,sizeof(lpnmtdi->szText)/sizeof(char)-1);//AY 24.09.2013 OLD: strcpy(lpnmtdi->szText,sz);
      lpnmtdi->hinst = NULL;
      lpnmtdi->lpszText = (LPSTR)&(lpnmtdi->szText);
      *result = 0;
      return;
    }
  }

  lpnmtdi->hinst = NULL;
  lpnmtdi->lpszText = NULL;
  if(nIDCtrl!=0 && ::IsChild(m_hWnd, hwndControl))
    if(::IsWindowVisible(hwndControl))
      ::SendMessage(hwndControl, WM_NOTIFY,(WPARAM)nIDCtrl,(LPARAM)pNotifyStruct);
  *result = 0;
}

template <class CDIALOG> inline void
CToolTipedDialog<CDIALOG>::OnToolTipNeedTextW(NMHDR* pNotifyStruct, LRESULT* result)
{
  LPNMTTDISPINFOW lpnmtdi = (LPNMTTDISPINFOW)pNotifyStruct;
  UINT nNotifyCode = pNotifyStruct->code;//==TTN_NEEDTEXTA
  HWND hwndToolTip = pNotifyStruct->hwndFrom;
  HWND hwndControl = NULL;
  UINT nIDCtrl = 0;//always 0
  UINT nIDTool = 0;//always 0
  UINT nID     = 0;
  if(lpnmtdi->uFlags&TTF_IDISHWND)
    hwndControl = (HWND)pNotifyStruct->idFrom;
  else if(pNotifyStruct->idFrom<1000)
    nID = nIDTool = pNotifyStruct->idFrom;
  else
    hwndControl = GetDlgItem(pNotifyStruct->idFrom)->m_hWnd;
  if(hwndControl!=NULL)
    nID = nIDCtrl = ::GetDlgCtrlID(hwndControl);

  if(nID!=0) {
    YStringW sz = GetToolTipText(nID);
    if(!sz.IsEmpty()){
      wcsncpy(lpnmtdi->szText,sz,sizeof(lpnmtdi->szText)/sizeof(wchar_t)-1);//AY 26.09.2013 OLD: wcscpy(lpnmtdi->szText,sz);
      lpnmtdi->hinst = NULL;
      lpnmtdi->lpszText = (LPWSTR)&(lpnmtdi->szText);
      *result = 0;
      return;
    }
  }

  lpnmtdi->hinst = NULL;
  lpnmtdi->lpszText = NULL;
  if(nIDCtrl!=0 && ::IsChild(m_hWnd, hwndControl))
    if(::IsWindowVisible(hwndControl))
      ::SendMessage(hwndControl, WM_NOTIFY,(WPARAM)nIDCtrl,(LPARAM)pNotifyStruct);
  *result = 0;
}

/*
template <class CDIALOG> inline BOOL
CToolTipedDialog<CDIALOG>::PreTranslateMessage(MSG* pMsg)
{
  switch (pMsg->message) {
    case WM_LBUTTONDOWN: 
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP: 
    case WM_MOUSEMOVE:
    case WM_LBUTTONUP:
      if(m_tooltip.m_hWnd!=NULL)
        m_tooltip.RelayEvent(pMsg);
      break;
  }
  return CDIALOG::PreTranslateMessage(pMsg);
}
*/

template <class CDIALOG> inline LRESULT
CToolTipedDialog<CDIALOG>::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
//must be or may be in PreTranslateMessage?
#ifdef _DEBUG$$
  if(message==WM_NOTIFY) {
    TRACE(DEBUGPLACE("%8.8X: %d %8.8X %8.8X "),m_hWnd,message,wParam,lParam);
    LPNMHDR lp = (LPNMHDR)lParam;
    TRACE(_T("WM_NOTIFY: hwnd=%8.8X code=0x%x ID=%d"),lp->hwndFrom,lp->code,lp->idFrom);
    if(TTN_GETDISPINFOW==lp->code)
      TRACE(_T("(TTN_GETDISPINFOW)"));
    TRACE(_T("\n"));
  }
#endif

  switch (message) {
    case WM_LBUTTONDOWN: 
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP: 
    case WM_MOUSEMOVE:
    case WM_LBUTTONUP:
      if(m_tooltip.m_hWnd!=NULL) {
        MSG msg = *GetCurrentMessage();
        m_tooltip.RelayEvent(&msg);
      }
      break;
  }
//
  switch (message) {
    case WM_NOTIFY: 
    {
      int     idCtrl = (int) wParam;
      LPNMHDR pnmh   = (LPNMHDR) lParam;
      HWND    hwndFrom = pnmh->hwndFrom;
      UINT    idFrom = pnmh->idFrom;
      UINT    code   = pnmh->code;
      LRESULT result;
      if(TTN_NEEDTEXTA==code) {
        OnToolTipNeedTextA(pnmh,&result);
        //TRACE("wParam = %u (0x%8.8x) (parent=0x%8.8x, this=0x%8.8x, tooltip=0x%8.8X)\n",
        //  wParam,wParam, GetParent()->m_hWnd,m_hWnd,m_tooltipVolume.m_hWnd);
        return result;
      }
      if(TTN_NEEDTEXTW==code) {
        OnToolTipNeedTextW(pnmh,&result);
        //TRACE("wParam = %u (0x%8.8x) (parent=0x%8.8x, this=0x%8.8x, tooltip=0x%8.8X)\n",
        //  wParam,wParam, GetParent()->m_hWnd,m_hWnd,m_tooltipVolume.m_hWnd);
        return result;
      }
    } break;
  }

  LRESULT lRet = CDIALOG::WindowProc(message,wParam,lParam);
  return lRet;
}

template <class CDIALOG> inline BOOL
CToolTipedDialog<CDIALOG>::AddCtrl(UINT nIDCtrl, LPCTSTR lpszText/*LPSTR_TEXTCALLBACK*/, LPCRECT lpRectTool/*NULL*/)  //  +1024
{
  if(nIDCtrl<1000)
    return FALSE;
  CWnd* pWnd = GetDlgItem(nIDCtrl);
  if(pWnd==NULL)
    return FALSE;
  CRect rc;
  if(lpRectTool==NULL) {
    pWnd->GetWindowRect(&rc);
    this->ScreenToClient(&rc);
    lpRectTool = &rc;
  }
  CString szText;
  if(lpszText==NULL){
    pWnd->GetWindowText(szText);
    lpszText = szText;
  }
  return m_tooltip.AddTool(this,lpszText,lpRectTool,nIDCtrl);
}

template <class CDIALOG> inline BOOL
CToolTipedDialog<CDIALOG>::AddCtrl(UINT nIDCtrl, UINT nIDText,LPCRECT lpRectTool/*NULL*/)
{
  if(nIDCtrl<1000)
    return FALSE;
  if(nIDText==(UINT)NULL) //special case
    return AddCtrl(nIDCtrl,(LPCTSTR)NULL,lpRectTool);
  CWnd* pWnd = GetDlgItem(nIDCtrl);
  if(pWnd==NULL)
    return FALSE;
  CRect rc;
  if(lpRectTool==NULL) {
    pWnd->GetWindowRect(&rc);
    this->ScreenToClient(&rc);
    lpRectTool = &rc;
  }
  return m_tooltip.AddTool(this,nIDText,lpRectTool,nIDCtrl);
}

template <class CDIALOG> inline BOOL
CToolTipedDialog<CDIALOG>::AddTool(UINT nIDTool, LPCTSTR lpszText/*LPSTR_TEXTCALLBACK*/, LPCRECT lpRectTool/*NULL*/)
{
  if(nIDTool>=1000)
    return FALSE;
  return m_tooltip.AddTool(this,lpszText,lpRectTool,nIDTool);
}

template <class CDIALOG> inline BOOL
CToolTipedDialog<CDIALOG>::AddTool(UINT nIDTool, UINT nIDText, LPCRECT lpRectTool/*NULL*/)//0..999
{
  if(nIDTool>=1000)
    return FALSE;
  return m_tooltip.AddTool(this,nIDText,lpRectTool,nIDTool);
}

template <class CDIALOG> inline void
CToolTipedDialog<CDIALOG>::DelCtrl(UINT nIDCtrl)
{
  m_tooltip.DelTool(this,nIDCtrl);
}
template <class CDIALOG> inline void
CToolTipedDialog<CDIALOG>::DelTool(UINT nIDTool)
{
  m_tooltip.DelTool(this,nIDTool);
}


// CToolTipedControl implementation /////////////////////////////////////////////////

template <class CCONTROL> inline CString
CToolTipedControl<CCONTROL>::ToolTipTextDecore(LPCTSTR szText) //AY 04.09.2009
{
  CString szToolTipText(szText);
  szToolTipText.Replace(_T("..."),_T(""));
  szToolTipText.TrimRight(_T('.'));
  return szToolTipText;
}

template <class CCONTROL> inline void
CToolTipedControl<CCONTROL>::SetToolTipText(LPCTSTR szText, UINT unused)
{
  ASSERT(m_hWnd!=NULL);//because initialization of m_bClickNotify provided in WM_CREATE handler

  m_szToolTipText = ToolTipTextDecore(szText);
}

template <class CCONTROL> inline CString
CToolTipedControl<CCONTROL>::GetToolTipText(UINT unused)
{
  return m_szToolTipText;
}

template <class CCONTROL> inline BOOL
CToolTipedControl<CCONTROL>::EnableClickNotify(BOOL bEnable)
{
  m_bClickNotify = bEnable;
  return 0;
}

template <class CCONTROL> inline void
CToolTipedControl<CCONTROL>::OnControlNeedTextA(NMHDR * pNotifyStruct, LRESULT * result)
{
  LPNMTTDISPINFOA lpnmtdi = (LPNMTTDISPINFOA)pNotifyStruct;
  CString sz = GetToolTipText(0);
#if defined(UNICODE) || defined(_UNICODE)
  int iRet = ::WideCharToMultiByte(CP_ACP,0,sz,sz.GetLength(),lpnmtdi->szText,sizeof(lpnmtdi->szText),NULL,NULL);
#else
  strncpy(lpnmtdi->szText,(LPCTSTR)sz,sizeof(lpnmtdi->szText)/sizeof(char)-1);//AY 24.09.2013 OLD: strcpy(lpnmtdi->szText,(LPCTSTR)sz);
#endif
  lpnmtdi->hinst = NULL;
  lpnmtdi->lpszText = (LPSTR)&(lpnmtdi->szText);
  *result = 0;
}

template <class CCONTROL> inline void
CToolTipedControl<CCONTROL>::OnControlNeedTextW(NMHDR * pNotifyStruct, LRESULT * result)
{
  LPNMTTDISPINFOW lpnmtdi = (LPNMTTDISPINFOW)pNotifyStruct;
  CString sz = GetToolTipText(0);
#if defined(UNICODE) || defined(_UNICODE)
  wcsncpy(lpnmtdi->szText,(LPCTSTR)sz,sizeof(lpnmtdi->szText)/sizeof(wchar_t)-1);//AY 24.09.2013 OLD: wcscpy(lpnmtdi->szText,(LPCTSTR)sz);
#else
  int iRet = ::MultiByteToWideChar(CP_ACP,0,(LPCTSTR)sz,sz.GetLength()+1,(WCHAR*)&(lpnmtdi->szText),sizeof(lpnmtdi->szText));
#endif
  lpnmtdi->hinst = NULL;
  lpnmtdi->lpszText = (LPWSTR)&(lpnmtdi->szText);
  *result = 0;
}

#if 0
template <class CCONTROL> inline BOOL
CToolTipedControl<CCONTROL>::PreTranslateMessage(MSG* pMsg)
{
  switch (pMsg->message) {
    case WM_LBUTTONDOWN: 
    {
      CWnd* pWnd = GetParent();
      if(m_bClickNotify && pWnd!=NULL)
        ::SendMessage(GetParent()->m_hWnd,WM_COMMAND,MAKELONG(GetDlgCtrlID(),BN_CLICKED),(LPARAM)m_hWnd);
    }
  }
  return CCONTROL::PreTranslateMessage(pMsg);
}
#endif

template <class CCONTROL> inline LRESULT
CToolTipedControl<CCONTROL>::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message) {
    case WM_CREATE:
      m_bClickNotify = FALSE;
      ::PostMessage(m_hWnd,WM_USER+1000,0,0);
      break;
    case WM_USER+1000:
      m_tooltip.Create(this,TTS_ALWAYSTIP);
      if(!GetToolTipText(0).IsEmpty())
        m_tooltip.AddTool(this,GetToolTipText(0));
      else
        m_tooltip.AddTool(this,LPSTR_TEXTCALLBACK);
      m_tooltip.Activate(TRUE);
#if 0//def _DEBUG
      {
        int nDelayAutopop = m_tooltip.GetDelayTime(TTDT_AUTOPOP);
        int nDelayReshow  = m_tooltip.GetDelayTime(TTDT_RESHOW);
        int nDelayInitial = m_tooltip.GetDelayTime(TTDT_INITIAL);
        m_tooltip.SetDelayTime(TTDT_INITIAL,nDelayInitial/2);
      }
#endif
      return 0;
    case WM_LBUTTONDOWN:
    {
      CWnd* pWnd = GetParent();
      if(m_bClickNotify && pWnd!=NULL)
        ::SendMessage(GetParent()->m_hWnd,WM_COMMAND,MAKELONG(GetDlgCtrlID(),BN_CLICKED),(LPARAM)m_hWnd);
    }
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP: 
    case WM_MOUSEMOVE:
    case WM_LBUTTONUP:
    { //static int nMouse=0; TRACE("MOUSE%d\n",nMouse++);
      if(m_tooltip.m_hWnd!=NULL) {
        if(m_hWnd!=NULL && IsWindowVisible()) {
          MSG msg = *GetCurrentMessage();
          MSG* pMsg = &msg;
          m_tooltip.RelayEvent(pMsg);
        }
      }
      break;
    }
    case WM_NOTIFY:
    {
      int     idCtrl = (int) wParam;
      LPNMHDR pnmh   = (LPNMHDR) lParam;
      HWND    hwndFrom = pnmh->hwndFrom;
      UINT    idFrom = pnmh->idFrom;
      UINT    code   = pnmh->code;
      LRESULT result;
      if(TTN_NEEDTEXTA==code) {
        OnControlNeedTextA(pnmh,&result);
        //TRACE("wParam = %u (0x%8.8x) (parent=0x%8.8x, this=0x%8.8x, tooltip=0x%8.8X)\n",
        //  wParam,wParam, GetParent()->m_hWnd,m_hWnd,m_tooltipVolume.m_hWnd);
        return result;
      }
      if(TTN_NEEDTEXTW==code) {
        OnControlNeedTextW(pnmh,&result);
        //TRACE("wParam = %u (0x%8.8x) (parent=0x%8.8x, this=0x%8.8x, tooltip=0x%8.8X)\n",
        //  wParam,wParam, GetParent()->m_hWnd,m_hWnd,m_tooltipVolume.m_hWnd);
        return result;
      }
    } break;
  }
  return CCONTROL::WindowProc(message,wParam,lParam);
}

// special case ///////////////////////////////////////////////////////////////////

template <class CSLIDER> inline void
CToolTipedSlider<CSLIDER>::SetToolTipText(LPCTSTR szFormat, UINT unused)
{ 
  CToolTipedControl<CSLIDER>::SetToolTipText(szFormat,0); 
}

template <class CSLIDER> inline CString
CToolTipedSlider<CSLIDER>::GetToolTipText(UINT unused)
{
  if(m_szToolTipText.IsEmpty())
    return "";
  CString sz; sz.Format(m_szToolTipText,GetPos());
  return sz;
}

template <class CSLIDER> inline void
CToolTipedSlider<CSLIDER>::OnControlNeedTextA(NMHDR * pNotifyStruct, LRESULT * result)
{
  LPNMTTDISPINFOA lpnmtdi = (LPNMTTDISPINFOA)pNotifyStruct;
  CString sz = GetToolTipText(0);
  if(!sz.IsEmpty()) {
    #if defined(UNICODE) || defined(_UNICODE)
      int iRet = ::WideCharToMultiByte(CP_ACP,0,sz,sz.GetLength(),lpnmtdi->szText,sizeof(lpnmtdi->szText),NULL,NULL);
    #else
      strncpy(lpnmtdi->szText,sz,sizeof(lpnmtdi->szText)/sizeof(char)-1);//AY 24.09.2013 OLD: strcpy(lpnmtdi->szText,sz);
    #endif
    lpnmtdi->hinst = NULL;
    lpnmtdi->lpszText = (LPSTR)&(lpnmtdi->szText);
    *result = 0;
  }else{
    CToolTipCtrl* pToolTipCtrl = GetToolTips();
    HWND hownToolTip = NULL;
    if(pToolTipCtrl!=NULL)
      hownToolTip = pToolTipCtrl->m_hWnd;
    UINT nNotifyCode = pNotifyStruct->code;//==TTN_NEEDTEXTA
    HWND hwndToolTip = pNotifyStruct->hwndFrom;
    if(hwndToolTip==hownToolTip) { //ascuire parent
      pNotifyStruct->hwndFrom = m_hWnd;
      *result = ::SendMessage(GetParent()->m_hWnd, WM_NOTIFY,(WPARAM)GetDlgCtrlID(),(LPARAM)pNotifyStruct);
      pNotifyStruct->hwndFrom = hwndToolTip;
    }
  }
}

template <class CSLIDER> inline void
CToolTipedSlider<CSLIDER>::OnControlNeedTextW(NMHDR * pNotifyStruct, LRESULT * result)
{
  LPNMTTDISPINFOW lpnmtdi = (LPNMTTDISPINFOW)pNotifyStruct;
  CString sz = GetToolTipText(0);
  if(!sz.IsEmpty()) {
    #if defined(UNICODE) || defined(_UNICODE)
      wcsncpy(lpnmtdi->szText,(LPCTSTR)sz,sizeof(lpnmtdi->szText)/sizeof(wchar_t)-1);//AY 24.09.2013 OLD: wcscpy(lpnmtdi->szText,(LPCTSTR)sz);
    #else
      int iRet = ::MultiByteToWideChar(CP_ACP,0,(LPCTSTR)sz,sz.GetLength()+1,(WCHAR*)&(lpnmtdi->szText),sizeof(lpnmtdi->szText));
    #endif
    lpnmtdi->hinst = NULL;
    lpnmtdi->lpszText = (LPWSTR)&(lpnmtdi->szText);
    *result = 0;
  }else{
    CToolTipCtrl* pToolTipCtrl = GetToolTips();
    HWND hownToolTip = NULL;
    if(pToolTipCtrl!=NULL)
      hownToolTip = pToolTipCtrl->m_hWnd;
    UINT nNotifyCode = pNotifyStruct->code;//==TTN_NEEDTEXTW
    HWND hwndToolTip = pNotifyStruct->hwndFrom;
    if(hwndToolTip==hownToolTip) { //ascuire parent
      pNotifyStruct->hwndFrom = m_hWnd;
      *result = ::SendMessage(GetParent()->m_hWnd, WM_NOTIFY,(WPARAM)GetDlgCtrlID(),(LPARAM)pNotifyStruct);
      pNotifyStruct->hwndFrom = hwndToolTip;
    }
  }
}

template <class CSLIDER> inline LRESULT
CToolTipedSlider<CSLIDER>::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message) {
    case WM_USER+1000: 
    {
      CToolTipCtrl* pToolTipCtrl = GetToolTips();
      m_tooltip.Create(this,TTS_ALWAYSTIP);
      if(pToolTipCtrl==NULL && !GetToolTipText(0).IsEmpty())
        m_tooltip.AddTool(this,GetToolTipText(0));
      else
        m_tooltip.AddTool(this,LPSTR_TEXTCALLBACK);
      m_tooltip.Activate(TRUE);
#if 0//def _DEBUG
      {
        int nDelayAutopop = m_tooltip.GetDelayTime(TTDT_AUTOPOP);
        int nDelayReshow  = m_tooltip.GetDelayTime(TTDT_RESHOW);
        int nDelayInitial = m_tooltip.GetDelayTime(TTDT_INITIAL);
        m_tooltip.SetDelayTime(TTDT_INITIAL,nDelayInitial/2);
      }
#endif
      return 0;
    }
    case WM_NOTIFY:
    {
      int     idCtrl = (int) wParam;
      LPNMHDR pnmh   = (LPNMHDR) lParam;
      HWND    hwndFrom = pnmh->hwndFrom;
      UINT    idFrom = pnmh->idFrom;
      UINT    code   = pnmh->code;
      LRESULT result;
      if(TTN_NEEDTEXTA==code) {
        OnControlNeedTextA(pnmh,&result);
        //TRACE("wParam = %u (0x%8.8x) (parent=0x%8.8x, this=0x%8.8x, tooltip=0x%8.8X)\n",
        //  wParam,wParam, GetParent()->m_hWnd,m_hWnd,m_tooltipVolume.m_hWnd);
        return result;
      }
      if(TTN_NEEDTEXTW==code) {
        OnControlNeedTextW(pnmh,&result);
        //TRACE("wParam = %u (0x%8.8x) (parent=0x%8.8x, this=0x%8.8x, tooltip=0x%8.8X)\n",
        //  wParam,wParam, GetParent()->m_hWnd,m_hWnd,m_tooltipVolume.m_hWnd);
        return result;
      }
    } break;
  }
  return CToolTipedControl<CSLIDER>::WindowProc(message,wParam,lParam);
}


#if 0
inline LRESULT
CToolTipedControl<CSliderCtrl>::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message) {
    case WM_CREATE:
      ::PostMessage(m_hWnd,WM_USER+1000,0,0);
      break;
    case WM_USER+1000:
      if(GetToolTips()==NULL) {
        m_tooltip.Create(this,TTS_ALWAYSTIP);
        if(!GetToolTipText(0).IsEmpty())
          m_tooltip.AddTool(this,GetToolTipText(0));
        else
          m_tooltip.AddTool(this,LPSTR_TEXTCALLBACK);
        m_tooltip.Activate(TRUE);
#ifdef _DEBUG
        {
          int nDelayAutopop = m_tooltip.GetDelayTime(TTDT_AUTOPOP);
          int nDelayReshow  = m_tooltip.GetDelayTime(TTDT_RESHOW);
          int nDelayInitial = m_tooltip.GetDelayTime(TTDT_INITIAL);
          m_tooltip.SetDelayTime(TTDT_INITIAL,nDelayInitial/2);
        }
#endif
      }
      break;
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP: 
    case WM_MOUSEMOVE:
    case WM_LBUTTONUP:
    {
      CToolTipCtrl* pToolTipCtrl = GetToolTips();
      if(pToolTipCtrl==NULL) {
        MSG msg = *GetCurrentMessage();
        MSG* pMsg = &msg;
        m_tooltip.RelayEvent(pMsg);
      }else{
        MSG msg = *GetCurrentMessage();
        MSG* pMsg = &msg;
        pToolTipCtrl->RelayEvent(pMsg);
      }
      break;
    }
    case WM_NOTIFY:
    {
      int     idCtrl = (int) wParam;
      LPNMHDR pnmh   = (LPNMHDR) lParam;
      HWND    hwndFrom = pnmh->hwndFrom;
      UINT    idFrom = pnmh->idFrom;
      UINT    code   = pnmh->code;
      LRESULT result;
      if(TTN_NEEDTEXTA==code) {
        OnControlNeedTextA(pnmh,&result);
        //TRACE("wParam = %u (0x%8.8x) (parent=0x%8.8x, this=0x%8.8x, tooltip=0x%8.8X)\n",
        //  wParam,wParam, GetParent()->m_hWnd,m_hWnd,m_tooltipVolume.m_hWnd);
        return result;
      }
      if(TTN_NEEDTEXTW==code) {
        OnControlNeedTextW(pnmh,&result);
        //TRACE("wParam = %u (0x%8.8x) (parent=0x%8.8x, this=0x%8.8x, tooltip=0x%8.8X)\n",
        //  wParam,wParam, GetParent()->m_hWnd,m_hWnd,m_tooltipVolume.m_hWnd);
        return result;
      }
    } break;
  }
  return CSliderCtrl::WindowProc(message,wParam,lParam);
}
#endif

// helpers ///////////////////////////////////////////////////////////////////

template <class CCONTROL, class CDIALOG> BOOL
AddTooltipedCtrl(
  CToolTipedDialog<CDIALOG>& dlg,
  CToolTipedControl<CCONTROL>& ctrl,
  LPCTSTR lpszText=NULL,//from GetWindowText
  LPCRECT lpRectTool=NULL)
{
  if(lpszText!=NULL && lpszText!=LPSTR_TEXTCALLBACK)
    ctrl.SetToolTipText(lpszText);
  if(lpszText==NULL)
    ctrl.SetToolTipText(CWnd__GetText(&ctrl));
  return dlg.AddCtrl(ctrl.GetDlgCtrlID(),LPSTR_TEXTCALLBACK,lpRectTool);
}

template <class CCONTROL, class CDIALOG> BOOL
AddTooltipedCtrl(
  CToolTipedDialog<CDIALOG>& dlg,
  CToolTipedControl<CCONTROL>& ctrl,
  UINT nIDText,//0:from GetWindowText
  LPCRECT lpRectTool)
{
  if(nIDText!=0)
    ctrl.SetToolTipText(ResourceString(nIDText));
  if(nIDText==0)
    ctrl.SetToolTipText(CWnd__GetText(&ctrl));
  return dlg.AddCtrl(ctrl.GetDlgCtrlID(),LPSTR_TEXTCALLBACK,lpRectTool);
}

#endif//__XCTOOLTIP_H
#pragma once
