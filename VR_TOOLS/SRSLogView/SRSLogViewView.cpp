// SRSLogViewView.cpp : implementation of the CSRSLogViewView class
#include "stdafx.h"
#include "SRSLogView.h"

#include "SRSLogViewDoc.h"
#include "SRSLogViewView.h"
#include "MainFrm.h"
//#include "applog.h"
#include "CLIENTS/CmdProtocol.rh"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TEST_RAND   rand()%2 /*in msec*/
#define TEST_EVENT  g_anMessages[rand()%25]

UINT  g_anMessages[25]={32845,32846,32847,32848,32849,32850,32851,32853,32854,32859,32860,32861,32904,32905,32906,32907,32908,32909,32913,32916,32917,32918,32926,32927,32933};

static CWnd*     g_pLastVisView = NULL;
/////////////////////////////////////////////////////////////////////////////
// CSRSLogViewView
IMPLEMENT_DYNCREATE(CSRSLogViewView, CResizableFormView)

BEGIN_MESSAGE_MAP(CSRSLogViewView, CParent)
	//{{AFX_MSG_MAP(CSRSLogViewView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_OPENLOG, OnButtonOpenlog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON_OPENLOG_CURSES, OnButtonOpenlogCurses)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_STATUS, OnButtonShowStatus)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_DETAILS, OnButtonShowDetails)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(IDC_CHECK_APPLY, OnCheckApply)
  
	ON_COMMAND(ID_FILE_PRINT, CParent::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CParent::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CParent::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSRSLogViewView construction/destruction
CSRSLogViewView::CSRSLogViewView()
	                 : CParent(CSRSLogViewView::IDD)
{
  m_pwndLog = NULL;
  m_bShowLogStatus  = FALSE;
	//{{AFX_DATA_INIT(CSRSLogViewView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}
//---------------------------------------
CSRSLogViewView::~CSRSLogViewView() {
  if(m_pwndLog) {
    delete m_pwndLog;
    m_pwndLog = NULL;
  }
}
//---------------------------------------
void CSRSLogViewView::DoDataExchange(CDataExchange* pDX) {
	CParent::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSRSLogViewView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
//---------------------------------------
BOOL CSRSLogViewView::PreCreateWindow(CREATESTRUCT& cs) {
	cs.style &= ~(WS_HSCROLL|WS_VSCROLL);
  return CParent::PreCreateWindow(cs);
}
//---------------------------------------
void CSRSLogViewView::OnInitialUpdate() {
  AddAnchor(IDC_BUTTON_OPENLOG,TOP_LEFT);
  AddAnchor(IDC_STATIC_BOX,TOP_LEFT,BOTTOM_RIGHT);
  AddAnchor(IDC_BUTTON4,BOTTOM_LEFT);
  AddAnchor(IDC_BUTTON_SHOW_DETAILS,BOTTOM_LEFT);
  AddAnchor(IDC_BUTTON_SHOW_STATUS,BOTTOM_LEFT);
	CParent::OnInitialUpdate();
  ViewAllLog(GetDocument()->GetLogFileName());
  m_bShowLogStatus  = m_pwndLog->IsShowLogStatus();
}
/////////////////////////////////////////////////////////////////////////////
// CSRSLogViewView printing
BOOL CSRSLogViewView::OnPreparePrinting(CPrintInfo* pInfo) {
	// default preparation
	return DoPreparePrinting(pInfo);
}
//---------------------------------------
void CSRSLogViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
	// TODO: add extra initialization before printing
}
//---------------------------------------
void CSRSLogViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
	// TODO: add cleanup after printing
}
//---------------------------------------
void CSRSLogViewView::OnPrint(CDC* /* pDC*/, CPrintInfo* /*pInfo*/) {
	// TODO: add customized printing code here
}
/////////////////////////////////////////////////////////////////////////////
// CSRSLogViewView diagnostics
#ifdef _DEBUG
void CSRSLogViewView::AssertValid() const {
	CParent::AssertValid();
}
//---------------------------------------
void CSRSLogViewView::Dump(CDumpContext& dc) const {
	CParent::Dump(dc);
}
//---------------------------------------
CSRSLogViewDoc* CSRSLogViewView::GetDocument() {// non-debug version is inline
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSRSLogViewDoc)));
	return (CSRSLogViewDoc*)m_pDocument;
}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CSRSLogViewView message handlers
void CSRSLogViewView::OnSize(UINT nType, int cx, int cy) { 
	CParent::OnSize(nType, cx, cy);
//  if(m_pwndLog && m_pwndLog->m_hWnd!=NULL) {
//    WINDOWPLACEMENT wndpl = {sizeof(wndpl)}; GetWindowPlacement(&wndpl);
//    RECT& rect = wndpl.rcNormalPosition;
//    GetClientRect(&rect);
//    
//    m_pwndLog->SetWindowPlacement(&wndpl);
//  }
}
//---------------------------------------
void CSRSLogViewView::OnButtonOpenlog() {
	ViewAllLog(GetDocument()->GetLogFileName());
}
//---------------------------------------
int CSRSLogViewView::ViewAllLog(CString szLogName) {
  OnViewEventLog(szLogName, YEventsProtocol::VIEWALL);
  return 0;
}
//---------------------------------------
int CSRSLogViewView::OnViewEventLog(CString szLogFile, int nMode) {
  RemoveAnchor(IDC_STATIC_BOX);
  if(GetLog()->isAttached())
    GetLog()->DetachWindow();
  
  if(GetLog()->isOpened())
    GetLog()->Close();

  if(GetLog()->View(szLogFile)!=0) { //AY 05.12.2007 OLD: Open
    AfxMessageBox(_T("Error of log creating/open!"));
  }

  if(m_pwndLog) {
    UINT nID = m_pwndLog->GetDlgCtrlID();
    WINDOWPLACEMENT wndpl = {sizeof(wndpl)}; 
    m_pwndLog->GetWindowPlacement(&wndpl);
    m_pwndLog->DestroyWindow();
    delete m_pwndLog, m_pwndLog = NULL;
    m_staticWnd.Create(NULL,WS_VISIBLE,wndpl.rcNormalPosition,this,nID);
  }

  if(!m_pwndLog)
    m_pwndLog = new CEventsListDlg();
  RemoveAnchor(IDC_STATIC_BOX);

  CMainFrame* pFrame = static_cast<CMainFrame*>(AfxGetApp()->m_pMainWnd);
  if(!pFrame || !m_pwndLog)
    return nMode;
  CEventsFilter filter;
  pFrame->m_wndDlgBar.ExportFilterConfig(filter);
  m_pwndLog->SetFilter(filter);
  m_pwndLog->SetDetailImages(TRUE);
  m_pwndLog->ShowLogStatus(TRUE);
  
  m_pwndLog->ReCreate(GetDlgItem(IDC_STATIC_BOX));
  AddAnchor(IDC_STATIC_BOX,TOP_LEFT, BOTTOM_RIGHT);
  GetLog()->AttachWindowEx2(m_pwndLog,nMode);
  
  return nMode;
}

void CSRSLogViewView::OnDestroy() {
  if(GetLog()->isAttached())
    GetLog()->DetachWindow();
  
  if(m_pwndLog) {
    m_pwndLog->DestroyWindow();
    delete m_pwndLog;
    m_pwndLog = NULL;
  }

  if(GetLog()->isOpened())
    GetLog()->Close();

	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CSRSLogViewView::OnButton1() {
	//add 
	YEventApplication ev(TEST_EVENT); GetLog()->PutEvent(ev);
}

void CSRSLogViewView::OnButtonOpenlogCurses() {
	OnViewEventLog(GetDocument()->GetLogFileName(),YEventsProtocol::VIEWSESSION);
}

void CSRSLogViewView::OnButton2() 
{
	YEventApplication ev1(TEST_EVENT); GetLog()->PutEvent(ev1);
	YEventApplication ev2(TEST_EVENT); GetLog()->PutEvent(ev2);
  YEventApplication ev3(TEST_EVENT); GetLog()->PutEvent(ev3);
  YEventApplication ev4(TEST_EVENT); GetLog()->PutEvent(ev4);
  YEventApplication ev5(TEST_EVENT); GetLog()->PutEvent(ev5);
  YEventApplication ev6(TEST_EVENT); GetLog()->PutEvent(ev6);
  YEventApplication ev7(TEST_EVENT); GetLog()->PutEvent(ev7);
  YEventApplication ev8(TEST_EVENT); GetLog()->PutEvent(ev8);
  YEventApplication ev9(TEST_EVENT); GetLog()->PutEvent(ev9);
  YEventApplication ev10(TEST_EVENT); GetLog()->PutEvent(ev10);
}


//DEL void CSRSLogViewView::OnSetFocus(CWnd* pOldWnd) {
//DEL   CMainFrame* pFrame = static_cast<CMainFrame*>(AfxGetApp()->m_pMainWnd);
//DEL   if(!pFrame || !m_pwndLog)
//DEL     return;
//DEL   CEventsFilter filter;
//DEL   if(m_pwndLog->GetFilter(&filter)) {
//DEL     pFrame->m_wndDlgBar.ImportFilterConfig(filter);
//DEL   }
//DEL   CParent::OnSetFocus(pOldWnd);
//DEL }

void CSRSLogViewView::OnCheckApply() {
  CMainFrame* pFrame = static_cast<CMainFrame*>(AfxGetApp()->m_pMainWnd);
  if(!pFrame || !m_pwndLog)
    return;
  CEventsFilter filter;
  pFrame->m_wndDlgBar.ExportFilterConfig(filter);
  m_pwndLog->SetFilter(filter);
}

void CSRSLogViewView::OnButton3() {
	//theEventsProtocol.DetachWindow();
}

void CSRSLogViewView::OnButton4() 
{
  LPCSTR szName = "Тестирование";
  YEventApplication ev2(IDSE_APP_LOGON2,szName); GetLog()->PutEvent(ev2);
//  YEventApplication ev3(
}

void CSRSLogViewView::OnButtonShowDetails() 
{
  m_pwndLog->SetDetailImages(!m_pwndLog->GetDetailImages());
  //m_pwndLog->Re
}

void CSRSLogViewView::OnButtonShowStatus() 
{
  m_bShowLogStatus=!m_bShowLogStatus;
  m_pwndLog->ShowLogStatus(m_bShowLogStatus);
  // TODO: Add your control notification handler code here
  
}

void CSRSLogViewView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
  do 
  {
    if(bActivate) {
      if(g_pLastVisView == pActivateView) {
        break;
      }
      CMainFrame* pFrame = static_cast<CMainFrame*>(AfxGetApp()->m_pMainWnd);
      CEventsFilter filter;
      if(m_pwndLog && m_pwndLog->GetFilter(&filter)) {
        pFrame->m_wndDlgBar.ImportFilterConfig(filter);
      }
      g_pLastVisView  = pActivateView;
    }
  } while(0);
  CParent::OnActivateView(bActivate, pActivateView, pDeactiveView);
}
