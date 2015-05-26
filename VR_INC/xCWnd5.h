// xCWnd5.h
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCWND5_H__INCLUDED_)
#define AFX_XCWND5_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <Windowsx.h>
#include "message.h"
#include "xassert.h"
#include "xCWnd4.h"
#include "xdebug.h"

/////////////////////////////////////////////////////////////////////////////
// CSizableWnd<CWnd>

template <class CWND>
class CSizableWnd : public CWND
{
public://construction/destruction
                  CSizableWnd(UINT IDD, CWnd* pParent)
                    :CWND(IDD,pParent) {construct();}
                  CSizableWnd(CWnd* pParent)
                    :CWND(pParent) {construct();}
                  CSizableWnd()
                    :CWND() {construct();}

  virtual void    OnRestore (BOOL bFromMinimized=FALSE)
                  { 
                    //TRACE("OnRestore() %s\n",bFromMinimized?"from minimized":"from maximized");
                  }
  virtual void    OnMaximize(BOOL bFromMinimized=FALSE)
                  { 
                    //TRACE("OnMaximize() %s\n",bFromMinimized?"from minimized":"from normal");
                  }
  virtual void    OnMinimize(BOOL bFromMaximized=FALSE)
                  { 
                    //TRACE("OnMinimize() %s\n",bFromMaximized?"from maximized":"from normal");
                  }
  virtual void    OnPlace(CSize sizMove, CSize sizSize)
                  { 
                    //TRACE("OnPlace(): move (%d;%d) size (%d,%d)  current(%d;%d)-(%dx%d)\n",sizMove.cx,sizMove.cy,sizSize.cx,sizSize.cy,m_ptCurrent.x,m_ptCurrent.y,m_sizCurrent.cx,m_sizCurrent.cy);
                  }
protected:
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  virtual LRESULT DebugProc(UINT message, WPARAM wParam, LPARAM lParam);
  
  void            construct()
                    { m_bLastIsMax=0; m_nStyle=0; m_ptCurrent=CPoint(0,0); m_sizCurrent=m_sizSize=m_sizMove=CSize(0,0);  m_rcDebugClient=m_rcDebugScreen=CRect(-100000,-100000,-100000,-100000); }

  BOOL            m_bLastIsMax;
  UINT            m_nStyle;
  CPoint          m_ptCurrent;  //previous screen coordinates of client of area during OnMove(), OnPlace()
  CSize           m_sizCurrent; //previous size of client area during OnSize(), OnPlace()
  CSize           m_sizMove;    //difference between new and old size AFTER OnMove() during OnPlace()
  CSize           m_sizSize;    //difference between new and old size AFTER OnSize() during OnPlace()

  CRect           m_rcDebugClient;
  CRect           m_rcDebugScreen;
};

/////////////////////////////////////////////////////////////////////////////
// CClickableWnd<CWnd> implementation
template <class CWND> LRESULT
CSizableWnd<CWND>::DebugProc(UINT message, WPARAM wParam, LPARAM lParam)
{
#ifdef _DEBUG
  {
    CRect rcClient;            GetClientRect(&rcClient);
    CRect rcScreen = rcClient; ClientToScreen(&rcScreen);
    if(rcClient!=m_rcDebugClient)
      TRACE(DEBUGPLACE("!***! rcCurrent=%dx%d != %dx%d\n"),rcClient.Width(),rcClient.Height(),m_rcDebugClient.Width(),m_rcDebugClient.Height());
    if(rcScreen!=m_rcDebugScreen)
      TRACE(DEBUGPLACE("!***! rcCurrent=%d;%d != %d;%d\n"),rcScreen.left,rcScreen.top,m_rcDebugScreen.left,m_rcDebugScreen.top);
    if(rcClient.Size()!=rcScreen.Size())
      TRACE(DEBUGPLACE("!***! size mithmatch\n"));
  }
#endif

  LRESULT lRet = 0;//DebugProc(message, wParam, lParam);

#ifdef _DEBUG
  {
    CRect rcClient;            GetClientRect(&rcClient);
    CRect rcScreen = rcClient; ClientToScreen(&rcScreen);
    m_rcDebugClient = rcClient;
    m_rcDebugScreen = rcScreen;
  }
#endif
  return lRet;
}

template <class CWND> LRESULT
CSizableWnd<CWND>::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  LRESULT lRet = 0;
  CRect rcClient;

  if( WM_CREATE==message ) {
    lRet = CWND::WindowProc(message, wParam, lParam);
    m_nStyle = GetStyle();
    return lRet;
  }

  // WM_WINDOWPOSCHANGED, WM_MOVING //TO DO: process?
  BOOL bChanged = WM_WINDOWPOSCHANGED==message;
  BOOL bChange = WM_WINDOWPOSCHANGING==message;
  WINDOWPOS* ppos = (bChange||bChanged)?(WINDOWPOS*)lParam:NULL;
  UINT flags = ppos?ppos->flags:0;
  BOOL bChSize = bChange && (flags&SWP_NOSIZE)==0;
  BOOL bChMove = bChange && (flags&SWP_NOMOVE)==0;
  BOOL bChNote = bChange && !bChSize && !bChMove;

  BOOL bPaint = WM_PAINT==message;

  BOOL bSize  = WM_SIZE==message;
  BOOL bMove  = WM_MOVE==message;
  BOOL bPlace = bSize || bMove;

  BOOL bProcess = bPlace||bChange||bPaint;
  BOOL bNote  = bChNote;

  if(bChanged)
    ASSERT(1);

  if(!bProcess)
    return CWND::WindowProc(message, wParam, lParam);

  if(bPaint) {
    rcClient = CWnd__GetClientRect(this,TRUE);
    CPoint ptCurrent  = rcClient.TopLeft();
    CSize  sizCurrent = rcClient.Size();
    if(ptCurrent==m_ptCurrent)
      return CWND::WindowProc(message, wParam, lParam);
    else
      ASSERT(1);
  }

  if(bNote) {
    lRet = CWND::WindowProc(message, wParam, lParam);

    rcClient = CWnd__GetClientRect(this,TRUE);
    CPoint ptCurrent  = rcClient.TopLeft();
    CSize  sizCurrent = rcClient.Size();
    if(ptCurrent==m_ptCurrent)
      return lRet;
#ifndef _DEBUG
    return lRet;//not needed now?
#endif
  }

  int x  = (int)(short)LOWORD(lParam);
  int y  = (int)(short)HIWORD(lParam);
  int cx = x;
  int cy = y;
  if(bChMove) x  = ppos->x , y  = ppos->y ;
  if(bChSize) cx = ppos->cx, cy = ppos->cy;

  if(bNote || bPaint) { //new positions
    x  = rcClient.left;
    y  = rcClient.top;
    cx = rcClient.Width();
    cy = rcClient.Height();
  }

  BOOL bMax  = bSize && wParam==SIZE_MAXIMIZED;
  BOOL bMin  = bSize && wParam==SIZE_MINIMIZED;
  BOOL bNorm = bSize && wParam==SIZE_RESTORED;
  UINT dwStyle = bPlace?GetStyle():0;
  BOOL bChild  = (dwStyle&WS_CHILD)!=0;

  BOOL bMinimized = (dwStyle&WS_MINIMIZE)!=0;
  BOOL bMaximized = (dwStyle&WS_MAXIMIZE)!=0;
  BOOL bMoveFromMinimize     = bMin && (m_nStyle&WS_MINIMIZE)!=0;
  BOOL bMaximizeFromMinimize = bMax && (m_nStyle&WS_MINIMIZE)!=0;
  BOOL bMinimizeFromMaximize = bMin && (m_nStyle&WS_MAXIMIZE)!=0;
  BOOL bRestoreFromMinimize = bNorm && (m_nStyle&WS_MINIMIZE)!=0;
  BOOL bRestoreFromMaximize = bNorm && (m_nStyle&WS_MAXIMIZE)!=0;
  BOOL bRestore = bRestoreFromMinimize || bRestoreFromMaximize;
  BOOL bDoSize = (bMax || bNorm);
  BOOL bDoMove = bMove && !bMinimized;

  BOOL bDoPlace = bDoMove || bDoSize;

  if(!bNote && !bPaint) //WM_MOVE || WM_SIZE || WM_WINDOWPOSCHANGING
    lRet = CWND::WindowProc(message, wParam, lParam);

  CRect rc = bDoPlace?CWnd__GetClientRect(this,TRUE):CRect(0,0,0,0);
  CPoint ptCurrent  = bDoSize?rc.TopLeft():m_ptCurrent;
  CSize  sizCurrent = bDoMove?rc.Size():m_sizCurrent;
  if(bDoMove && bChild)
    x = ptCurrent.x, y = ptCurrent.y;

  static const CSize siz0(0,0);
  m_sizSize = m_sizMove = siz0;
  if(bDoSize || bNote || bPaint)
    m_sizSize = CSize(cx,cy)-m_sizCurrent, m_sizMove = ptCurrent-m_ptCurrent;
  if(bDoMove || bNote || bPaint)
    m_sizMove = CPoint(x,y)-m_ptCurrent, m_sizSize = sizCurrent-m_sizCurrent;

  if(bMin)
    OnMinimize(bMinimizeFromMaximize);
  if(bMax)
    OnMaximize(bMaximizeFromMinimize);
  if(bRestore)
    OnRestore(bRestoreFromMinimize);
  if(bDoPlace && !bMoveFromMinimize) //? if(m_sizSize!=siz0 && m_sizMove!=siz0)
    OnPlace(m_sizMove,m_sizSize);
  if(bNote)
    OnPlace(m_sizMove,m_sizSize);
  if(bPaint)
    OnPlace(m_sizMove,m_sizSize);

  if(bDoSize || bNote || bPaint)
    m_sizCurrent = CSize(cx,cy), m_ptCurrent = ptCurrent;
  if(bDoMove || bNote || bPaint)
    m_ptCurrent = CPoint(x,y), m_sizCurrent = sizCurrent;

  if(bMin)
    m_bLastIsMax = (m_nStyle&WS_MAXIMIZE)!=0;
  if(bSize)
    m_nStyle = GetStyle();

  if(bPaint)
    lRet = CWND::WindowProc(message, wParam, lParam);

  return lRet;
}



#endif // !defined(AFX_XCWND5_H__INCLUDED_)
