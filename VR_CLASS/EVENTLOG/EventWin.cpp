// exentwin.cpp : implementation file
//

#include "stdafx.h"
#include "eventwin.h"
#include "xCString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "eventlog.h"

/////////////////////////////////////////////////////////////////////////////
// CEventsWindow construction

CEventsWindow::CEventsWindow() : CEdit()
{
  m_nMaxBufferSize = 30000;
  m_pevp = NULL;
}

int  CEventsWindow::Create(const RECT& rc, UINT nID, CWnd *pParent/*NULL*/)
{
  DWORD dwStyle  = WS_CHILD|WS_VSCROLL|WS_VISIBLE| //|WS_HSCROLL
                   ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_READONLY;
  BOOL  bResult  = CEdit::Create(dwStyle,rc,pParent,nID);
  if(!bResult)
    return bResult;

  SetLimitText(m_nMaxBufferSize);

  SetFont(GetParent()->GetFont());
  return TRUE;
}

BOOL CEventsWindow::PreCreateWindow( CREATESTRUCT& cs )
{
  cs.dwExStyle |= WS_EX_STATICEDGE;
  return TRUE;
}

CEventsWindow::~CEventsWindow()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEventsWindow message handlers

BEGIN_MESSAGE_MAP(CEventsWindow, CWnd)
	//{{AFX_MSG_MAP(CEventsWindow)
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventsWindow methods
int CEventsWindow::AttachLog(YEventsProtocol* pevp) {
  m_pevp = pevp;
	return 0;
}
int CEventsWindow::DetachLog() {
  if(m_pevp!=NULL) {
		m_pevp->DetachWindow();
    m_pevp = NULL;
  }
	return 0;
}
void CEventsWindow::OnClose()
{
	DetachLog();
  CEdit::OnClose();
}
void CEventsWindow::OnDestroy()
{
	DetachLog();
  CEdit::OnDestroy();
}

int CEventsWindow::AddLine(LPCTSTR szText)
{
  ASSERT(szText!=NULL);
  int nStart, nEnd, nLength;
  CString szWindowText;
  UINT nMaxTextSize = GetLimitText();
// form window text
  GetWindowText(szWindowText);
  GetSel(nStart,nEnd);
  nLength = (szWindowText.Mid(nStart)).GetLength();
  nStart += nLength;
  nEnd = nStart;
  szWindowText += szText;
  szWindowText += "\r\n";
// truncate
  int nLen = szWindowText.GetLength();
  int nPos = 0;
  while(nLen-nPos > nMaxTextSize) {
    int nNextPos = szWindowText.Find(_T("\r\n"),nPos);
    if(nNextPos==-1)
      break;
    nPos = nNextPos + 2;
  }
  nStart -= nPos;
  nEnd = nStart;
// add to window
  SetWindowText(((LPCTSTR)szWindowText)+nPos);
  SetSel(nStart,nEnd);
  return TRUE;
}

int CEventsWindow::ResetContents(){
  SetWindowText(_T(""));
  SetSel(0,0);
  return TRUE;
}

int CEventsWindow::SetRedrawOff() {
	SetRedraw(FALSE);
	return 0;
}

int CEventsWindow::SetRedrawOn() {
	SetRedraw(TRUE);
  GetParent()->RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ALLCHILDREN);
	return 0;
}

