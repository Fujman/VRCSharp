// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SRSLogView.h"

#include "MainFrm.h"
#include "EVENTLOG/controls/EventsFilter.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
#ifdef DEBUG_EL_TIME
  ID_INDIATOR_LOADTIME,
#endif
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
  EnableDocking(CBRS_ALIGN_ANY);

	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
  if (!m_wndDlgBar.Create(this, CBRS_ALIGN_ANY, AFX_IDW_DIALOGBAR)) {
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if(!m_wndReBar.Create(this) ||
     !m_wndReBar.AddBar(&m_wndToolBar, 0, 0, RBBS_FIXEDBMP | RBBS_BREAK)|| 
     !m_wndReBar.AddBar(&m_wndDlgBar,0,0,RBBS_FIXEDBMP|RBBS_BREAK)
      )
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

  CEventsFilter filter;
  filter.SetUseFilter(FALSE);
  filter.SetLevelErrorFlags(255);
  filter.SetLevelWarningFlags(255);
  filter.SetLevelInfoFlags(255);
  filter.SetStartTime(YTime::INVALID());
  filter.SetStopTime(YTime::INVALID());
  
  YSRSChannelsList aChannels;
  for(int i=0;i<CEventsFilter::_MAXCHANNELS;++i)
    aChannels.AddChannel((HSRSCHANNEL)i);

  m_wndDlgBar.ImportFilterConfig(filter);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) {
  cs.style &= ~FWS_ADDTOTITLE;
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

