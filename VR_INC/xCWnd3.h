// xCWnd3.h
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCWND3_H__INCLUDED_)
#define AFX_XCWND3_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <Windowsx.h>
#include "message.h"
#include "xassert.h"

/////////////////////////////////////////////////////////////////////////////
// CClickableWnd<CWnd>

template <class CWND>
class CClickableWnd : public CWND
{
public://constants
  enum { flagSEPARETE_PROCESSING=1, flagSEND_COMMAND=2, flagMOVE_NOTIFY=4 };
public://construction/destruction
                  CClickableWnd(UINT nFlags=flagSEND_COMMAND, UINT nCommandID=0)
                    { m_uFlags=nFlags; m_uCommandID=nCommandID; for(int i=0;i<4;++i) m_ptClient[i]=m_ptScreen[i]=CPoint(0,0),m_anState[i]=0; m_ptDrag=CPoint(0,0); m_wParam=0; m_lParam=0; }
protected:
  virtual LRESULT OnMouse(UINT message, WPARAM wParam, LPARAM lParam)//BEFORE default: if return 0, default procedure and second OnMouse will not be processed
                    { return -1; }
  virtual LRESULT OnMouse(UINT message, WPARAM wParam, LPARAM lParam, LRESULT lResult)//AFTER default
                    { return lResult; }
  virtual LRESULT DoCommand(UINT message, WPARAM wParam, LPARAM lParam)
                    { return DoMessage(message, wParam, lParam); }
  virtual LRESULT DoMove(UINT message, WPARAM wParam, LPARAM lParam)
                    { return DoMessage(message, wParam, lParam); }
  virtual LRESULT DoMessage(UINT message, WPARAM wParam, LPARAM lParam);

  virtual CPoint  GetClickPos(BOOL bScreen=TRUE, UINT nButtton=0/*MK_*/) const;

  //next function will be called if flagSeparateProcessing used
  //default processor MUST BE called
  afx_msg void    OnMouseMove     (UINT nFlags, CPoint point) { CWND::OnMouseMove    (nFlags, point); }
  afx_msg void    OnLButtonDown   (UINT nFlags, CPoint point) { CWND::OnLButtonDown  (nFlags, point); }
  afx_msg void    OnRButtonDown   (UINT nFlags, CPoint point) { CWND::OnRButtonDown  (nFlags, point); }
  afx_msg void    OnMButtonDown   (UINT nFlags, CPoint point) { CWND::OnMButtonDown  (nFlags, point); }
  afx_msg void    OnLButtonUp     (UINT nFlags, CPoint point) { CWND::OnLButtonUp    (nFlags, point); }
  afx_msg void    OnRButtonUp     (UINT nFlags, CPoint point) { CWND::OnRButtonUp    (nFlags, point); }
  afx_msg void    OnMButtonUp     (UINT nFlags, CPoint point) { CWND::OnMButtonUp    (nFlags, point); }
  afx_msg void    OnLButtonDblClk (UINT nFlags, CPoint point) { CWND::OnLButtonDblClk(nFlags, point); }
  afx_msg void    OnRButtonDblClk (UINT nFlags, CPoint point) { CWND::OnRButtonDblClk(nFlags, point); }
  afx_msg void    OnMButtonDblClk (UINT nFlags, CPoint point) { CWND::OnMButtonDblClk(nFlags, point); }

  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

  UINT            m_uCommandID;
  UINT            m_uFlags;
  CPoint          m_ptClient[4];//0-last,1-L,2-R,3-M
  CPoint          m_ptScreen[4];
  UINT            m_anState[4];
  CPoint          m_ptDrag;
  WPARAM          m_wParam;
  LPARAM          m_lParam;

  UINT            make_move(UINT code, UINT flags, LPARAM lParam,
                    UINT* button,/*0-move or MK_ for mouse buttons*/
                    UINT* action,/*WMSZ_ on move or 0,1,2 for button down/up/dblclk*/
                    LPARAM* lScreen
                  );
public:
  enum            { buttonDOWN=0, buttonUP=1, buttonDBL=2 };
  static UINT     make_code(UINT message, UINT flags,
                    UINT* button,/*0-move or MK_ for mouse buttons*/
                    UINT* action /*WMSZ_ on move or 0,1,2 for button down/up/dblclk*/
                  );
  static BOOL     parse_code(UINT code, UINT* message, UINT* flags,
                    UINT* button,/*0-move or MK_ for mouse buttons*/
                    UINT* action /*WMSZ_ on move or 0,1,2 for button down/up/dblclk*/
                  );//return: lParam coordinates is absolute

  enum            { moveNONE=0, moveDOWN=1, moveUP=2, moveLEFT=4, moveRIGHT=8 };
  static UINT     make_move(UINT moving); //return WMSZ_???
  static UINT     parse_move(UINT action);//return move????

  static BOOL     parse_msg(const MSG* , UINT* message, UINT* flags,
                    UINT* button,/*0-move or MK_ for mouse buttons*/
                    UINT* action,/*WMSZ_ on move or 0,1,2 for button down/up/dblclk*/
                    LONG* x,
                    LONG* y
                  );//return: coordinates is absolute
};

/////////////////////////////////////////////////////////////////////////////
// CClickableWnd<CWnd> implementation
template <class CWND> LRESULT 
CClickableWnd<CWND>::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  UINT nButton, nAction, nCode=make_code(message,wParam,&nButton,&nAction);
  BOOL bMouse = nCode!=0xFFFF;
  
  if(!bMouse)
    return CWND::WindowProc(message, wParam, lParam);

  LPARAM lScreen; nCode=make_move(nCode,wParam,lParam,&nButton,&nAction,&lScreen);

  LRESULT lRet = OnMouse(message, wParam, lParam);
  if(lRet==0)
    return 0;

  if((m_uFlags&flagSEPARETE_PROCESSING)) {
    CPoint ptClient(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
    UINT nFlags = wParam;
    switch(message){
      case WM_MOUSEMOVE    :OnMouseMove     (nFlags, ptClient); break;
      case WM_LBUTTONDOWN  :OnLButtonDown   (nFlags, ptClient); break;
      case WM_RBUTTONDOWN  :OnRButtonDown   (nFlags, ptClient); break;
      case WM_MBUTTONDOWN  :OnMButtonDown   (nFlags, ptClient); break;
      case WM_LBUTTONUP    :OnLButtonUp     (nFlags, ptClient); break;
      case WM_RBUTTONUP    :OnRButtonUp     (nFlags, ptClient); break;
      case WM_MBUTTONUP    :OnMButtonUp     (nFlags, ptClient); break;
      case WM_LBUTTONDBLCLK:OnLButtonDblClk (nFlags, ptClient); break;
      case WM_RBUTTONDBLCLK:OnRButtonDblClk (nFlags, ptClient); break;
      case WM_MBUTTONDBLCLK:OnMButtonDblClk (nFlags, ptClient); break;
      default: ASSERT(!"not reachable"); break;
    };
    return 0;
  }

  lRet = CWND::WindowProc(message, wParam, lParam);

  BOOL bDoMove = (nButton==0) && (m_uFlags&flagMOVE_NOTIFY );
  BOOL bDoBtn  = (nButton>0)  && (m_uFlags&flagSEND_COMMAND);
  if(bDoMove || bDoBtn) {
    int nID = (int)(m_uCommandID?m_uCommandID:GetDlgCtrlID());
    WPARAM wParam;
    LPARAM lParam;
    MakeCommandMessageParams(nID,nCode,0,wParam,lParam);
    if(bDoBtn) DoCommand(WM_COMMAND, wParam, lScreen);
    else       DoMove   (WM_COMMAND, wParam, lScreen);
  }

  lRet = OnMouse(message, wParam, lParam, lRet);

  return lRet;
}

template <class CWND> CPoint CClickableWnd<CWND>::
GetClickPos(BOOL bScreen, UINT nButton) const
{
  int nBtn = 0;
  if(nButton==MK_LBUTTON) nBtn = 1;
  if(nButton==MK_RBUTTON) nBtn = 2;
  if(nButton==MK_MBUTTON) nBtn = 3;
  return bScreen?m_ptScreen[nBtn]:m_ptClient[nBtn];
}

template <class CWND> UINT CClickableWnd<CWND>::
make_move(UINT moving)/*move????*/
{
  UINT action = 0;
  if     (moving & (moveUP   |moveLEFT)) action = WMSZ_TOPLEFT    ;
  else if(moving & (moveRIGHT|moveUP  )) action = WMSZ_TOPRIGHT   ;
  else if(moving & (moveDOWN |moveLEFT)) action = WMSZ_BOTTOMLEFT ;
  else if(moving & (moveRIGHT|moveDOWN)) action = WMSZ_BOTTOMRIGHT;
  else if(moving & (moveLEFT |moveNONE)) action = WMSZ_LEFT       ;
  else if(moving & (moveRIGHT|moveNONE)) action = WMSZ_RIGHT      ;
  else if(moving & (moveUP   |moveNONE)) action = WMSZ_TOP        ;
  else if(moving & (moveDOWN |moveNONE)) action = WMSZ_BOTTOM     ;
  return action;
}//WMSZ_

template <class CWND> UINT CClickableWnd<CWND>::
parse_move(UINT action)/*WMSZ_ on move*/
{
  UINT moving = 0;
  if     (action==WMSZ_TOPLEFT    ) moving |= moveUP   |moveLEFT;
  else if(action==WMSZ_TOPRIGHT   ) moving |= moveRIGHT|moveUP  ;
  else if(action==WMSZ_BOTTOMLEFT ) moving |= moveDOWN |moveLEFT;
  else if(action==WMSZ_BOTTOMRIGHT) moving |= moveRIGHT|moveDOWN;
  else if(action==WMSZ_LEFT       ) moving |= moveLEFT |moveNONE;
  else if(action==WMSZ_RIGHT      ) moving |= moveRIGHT|moveNONE;
  else if(action==WMSZ_TOP        ) moving |= moveUP   |moveNONE;
  else if(action==WMSZ_BOTTOM     ) moving |= moveDOWN |moveNONE;
  return moving;
}//move????


//////////////////////////////////////////////////////////////////////////////
// CClickableWnd command notification code format
// on move:
// 5432109876543210 kkkkk-button status flags (MK_???)
// 1mmmm------kkkkk mmmm -movement direction (WMSZ_???) 0..8
// on button:
// 5432109876543210 kkkkk-button status flags (MK_???)          u=0 down, 1 up
// 0udbb------kkkkk bbbb -button command flags  1-L,2-R,3-M,... d double click
//
template <class CWND> UINT CClickableWnd<CWND>::
make_code(UINT message, UINT flags,
  UINT* button/*0-move or MK_ for mouse buttons*/,
  UINT* action/*WMSZ_ on move or 0,1,2 for button down/up/dblclk*/
)
{
  STATIC_ASSERT(0x1F==(MK_LBUTTON|MK_RBUTTON|MK_SHIFT|MK_CONTROL|MK_MBUTTON),unexpected_value_of_constant);
  STATIC_ASSERT(0<WMSZ_LEFT       &&WMSZ_LEFT       <=8,unexpected_value_of_constant);
  STATIC_ASSERT(0<WMSZ_RIGHT      &&WMSZ_RIGHT      <=8,unexpected_value_of_constant);
  STATIC_ASSERT(0<WMSZ_TOP        &&WMSZ_TOP        <=8,unexpected_value_of_constant);
  STATIC_ASSERT(0<WMSZ_TOPLEFT    &&WMSZ_TOPLEFT    <=8,unexpected_value_of_constant);
  STATIC_ASSERT(0<WMSZ_TOPRIGHT   &&WMSZ_TOPRIGHT   <=8,unexpected_value_of_constant);
  STATIC_ASSERT(0<WMSZ_BOTTOM     &&WMSZ_BOTTOM     <=8,unexpected_value_of_constant);
  STATIC_ASSERT(0<WMSZ_BOTTOMLEFT &&WMSZ_BOTTOMLEFT <=8,unexpected_value_of_constant);
  STATIC_ASSERT(0<WMSZ_BOTTOMRIGHT&&WMSZ_BOTTOMRIGHT<=8,unexpected_value_of_constant);

  UINT m = message;
  BOOL bMove = m==WM_MOUSEMOVE;
  BOOL bLBtn = !bMove&& (m==WM_LBUTTONDOWN  ||m==WM_LBUTTONUP    ||m==WM_LBUTTONDBLCLK);
  BOOL bRBtn = !bMove&& (m==WM_RBUTTONDOWN  ||m==WM_RBUTTONUP    ||m==WM_RBUTTONDBLCLK);
  BOOL bMBtn = !bMove&& (m==WM_MBUTTONDOWN  ||m==WM_MBUTTONUP    ||m==WM_MBUTTONDBLCLK);
  BOOL bBtn  = (bLBtn||bRBtn||bMBtn);
  BOOL bDown =  bBtn && (m==WM_RBUTTONDOWN  ||m==WM_LBUTTONDOWN  ||m==WM_MBUTTONDOWN  );
  BOOL bUp   =  bBtn && (m==WM_RBUTTONUP    ||m==WM_LBUTTONUP    ||m==WM_MBUTTONUP    );
  BOOL bDbl  =  bBtn && (m==WM_LBUTTONDBLCLK||m==WM_RBUTTONDBLCLK||m==WM_MBUTTONDBLCLK);
  BOOL bMouse= bBtn || bMove;
  if(!bMouse)
    return 0xFFFF;

  UINT nCode = flags & 0x1F;
  if(bMove){
    int nMove = 0;//will be recalculated in make_move()
    nCode |= 0x8000;
    nCode |= (nMove<<11);
    if(button) *button = 0;
    if(action) *action = 0;
  }else{
    UINT nBtn=0, nBtnMask=0;
    if     (bLBtn) nBtn=1, nBtnMask=MK_LBUTTON;
    else if(bRBtn) nBtn=2, nBtnMask=MK_RBUTTON;
    else if(bMBtn) nBtn=3, nBtnMask=MK_MBUTTON;
    else ASSERT(0);

    if(bUp)  nCode |= 0x4000;
    if(bDbl) nCode |= 0x2000;
    nCode &= ~nBtnMask;//clear own
    if(nCode==0 && nBtn==1)
      nCode = 0;//special case
    else
      nCode |= (nBtn<<11);
    if(button) *button = nBtn;
    if(action) *action = (bDbl?buttonDBL:(bUp?buttonUP:buttonDOWN));
  }
  return nCode;
}

template <class CWND> UINT CClickableWnd<CWND>::
make_move(UINT nCode, UINT nFlags, LPARAM lParam,
  UINT* button,/*0-move or MK_ for mouse buttons*/
  UINT* action,/*WMSZ_ on move or 0,1,2 for button down/up/dblclk*/
  LPARAM* lScreen
)
{
  CPoint ptClient(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
  CPoint ptScreen(ptClient); ClientToScreen(&ptScreen);
  *lScreen = MAKELPARAM(ptScreen.x, ptScreen.y);//absolute

  UINT nButton = *button;
  UINT nAction = *action;

  BOOL bMouse = TRUE;
  BOOL bMove  = bMouse && nButton==0;
  BOOL bBtn   = bMouse && nButton>0;
  BOOL bDown  = bBtn && nAction==buttonDOWN;
  BOOL bDble  = bBtn && nAction==buttonDBL;
  BOOL bDrag  = bMove && (nFlags&(MK_LBUTTON|MK_RBUTTON|MK_MBUTTON))!=0;

  if(bDown || bDble){
    m_ptClient[0] = m_ptClient[nButton] = ptClient;
    m_ptScreen[0] = m_ptScreen[nButton] = ptScreen;
    m_anState [0] = m_anState [nButton] = nFlags;
  }
  if(bDown)
    m_ptDrag = ptScreen;

  if(bDrag){
    CPoint pt = m_ptDrag;
    pt.x = ptScreen.x - pt.x;
    pt.y = ptScreen.y - pt.y;
    m_ptDrag = ptScreen;

    UINT moving = 0;
    if(pt.x<0) moving |= moveLEFT;
    if(pt.x>0) moving |= moveRIGHT;
    if(pt.y<0) moving |= moveUP;
    if(pt.y>0) moving |= moveDOWN;

    UINT nMove = make_move(moving);
    nCode = nFlags & 0x1F;
    nCode |= 0x8000;
    nCode |= (nMove<<11);

    *button = 0;
    *action = nMove;
    *lScreen = MAKELPARAM(pt.x, pt.y);//relative
  }
  return nCode;
}

template <class CWND> BOOL CClickableWnd<CWND>::
parse_code(UINT nCode, UINT* message, UINT* flags,
  UINT* button,/*0-move or MK_ for mouse buttons*/
  UINT* action /*WMSZ_ on move or 0,1,2 for button down/up/dblclk*/
)
{
  BOOL bMove = (nCode&0x8000)!=0;
  BOOL bAbs  = TRUE;

  if(bMove) {//move
    UINT nMove = (nCode&~0x8000)>>11;
    if(button) *button = 0;
    if(action) *action = nMove;
    if(message)*message= WM_MOUSEMOVE;
    if(nMove)
      bAbs = FALSE;
  }else{
    UINT nBtn  = (nCode&~0x6000)>>11;
    if(nCode==0)
      nBtn = 1;//special case
    UINT nAct  = buttonDOWN;
    if(nCode&0x4000) nAct  = buttonUP;
    if(nCode&0x2000) nAct  = buttonDBL;
    if(button) *button = nBtn;
    if(action) *action = nAct;
    if(message) {
      static const UINT aD[]={0,WM_LBUTTONDOWN  ,WM_RBUTTONDOWN  ,WM_MBUTTONDOWN  };
      static const UINT aU[]={0,WM_LBUTTONUP    ,WM_RBUTTONUP    ,WM_MBUTTONUP    };
      static const UINT a2[]={0,WM_LBUTTONDBLCLK,WM_RBUTTONDBLCLK,WM_MBUTTONDBLCLK};
      if(nAct==buttonDOWN) *message = aD[nBtn];
      if(nAct==buttonUP)   *message = aU[nBtn];
      if(nAct==buttonDBL)  *message = a2[nBtn];
    }
  }
  if(flags) *flags = nCode&0x1F;

  return bAbs;
}

template <class CWND> BOOL CClickableWnd<CWND>::
parse_msg(const MSG* pmsg, UINT* message, UINT* flags,
  UINT* button,/*0-move or MK_ for mouse buttons*/
  UINT* action,/*WMSZ_ on move or 0,1,2 for button down/up/dblclk*/
  LONG* x,
  LONG* y
)
{
  HWND  hCtrl = NULL;
  UINT  nID = 0;
  MSG   msg = *pmsg;

  if(msg.message==WM_COMMAND){
    hCtrl = GetCommandCtrlHWND(&msg);
    nID   = LOWORD(msg.wParam);
    CClickableWnd<CWND>* pWnd = (CClickableWnd<CWND>*)CWnd::FromHandle(hCtrl);
    ASSERT(pWnd!=NULL);
    if(pWnd)
      { msg.wParam = pWnd->m_wParam; msg.lParam = pWnd->m_lParam; }
    else
      { msg.wParam = 0; msg.lParam = 0; }
    ASSERT(nID==LOWORD(msg.wParam));
  }

  int nCode = GetCommandNotificationCode(&msg);
  if(x) *x = GET_X_LPARAM(msg.lParam);
  if(y) *y = GET_Y_LPARAM(msg.lParam);
  return parse_code(nCode, message, flags, button, action);
}

template <class CWND> LRESULT CClickableWnd<CWND>::
DoMessage(UINT message, WPARAM wParam, LPARAM lParam)
{ 
  if(WM_COMMAND==message){
    m_wParam = wParam;
    m_lParam = lParam;
    return SendCommandMessage(GetParent(), LOWORD(wParam), 0, m_hWnd);
  }
  return GetParent()->SendMessage(message, wParam, lParam); 
}


#endif // !defined(AFX_XCWND3_H__INCLUDED_)
