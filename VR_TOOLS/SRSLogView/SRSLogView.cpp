// SRSLogView.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"

#include "xCWinApp.h"
#include "FS/FileName.h"

#include "SRSLogView.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "SRSLogViewDoc.h"
#include "SRSLogViewView.h"

#include "_version.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSRSLogViewApp

BEGIN_MESSAGE_MAP(CSRSLogViewApp, CWinApp/*CParrent*/)
	//{{AFX_MSG_MAP(CSRSLogViewApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnUpdateFilePrintSetup)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_NEW, OnUpdateWindowNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_LOG_RESIZE, OnLogResize)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CParrent::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CParrent::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CParrent::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSRSLogViewApp construction

CSRSLogViewApp::CSRSLogViewApp()
{
  m_pDocTemplate  = NULL;
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSRSLogViewApp object

CSRSLogViewApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSRSLogViewApp initialization

BOOL CSRSLogViewApp::InitInstance() {
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("SpecialRecordingSystems"));

	LoadStdProfileSettings(10);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pDocTemplate = new CMultiDocTemplate(IDR_SRSLOGTYPE,
		                                     RUNTIME_CLASS(CSRSLogViewDoc),
		                                     RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		                                     RUNTIME_CLASS(CSRSLogViewView));
	AddDocTemplate(m_pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

  // Enable drag/drop open
  m_pMainWnd->DragAcceptFiles();

	// Parse command line for standard shell commands, DDE, file open
 	CCommandLineInfo cmdInfo;
 	ParseCommandLine(cmdInfo);
  CString szCmdLine(m_lpCmdLine); 
  CString szCmdLineUp = szCmdLine; 
  szCmdLineUp.MakeUpper();
  CString szLogName = cmdInfo.m_strFileName;
  if(szCmdLine.Replace(_T("/LOGDUMP"),_T("")) >0 && !szLogName.IsEmpty()) {
    //CString szDumpName = CFileName(szLogName).GetBase() + ".dmp";
    YEventsProtocol  theEvProtocol;
    theEvProtocol.Dump(szLogName);
    return FALSE;
  }
  if(szCmdLine.Replace(_T("/LOGZIP"),_T("")) >0 && !szLogName.IsEmpty()) {
    //CString szZipName = CFileName(szLogName).GetBase() + ".loz";
    YEventsProtocol  theEvProtocol;
    theEvProtocol.Zip(szLogName);
    return FALSE;
  }

  {
    int nDigPosStart = szCmdLineUp.Find(_T("/RESIZE="));
    if(-1 != nDigPosStart) {
      nDigPosStart+=_tcslen(_T("/RESIZE="));
      int nDigPosEnd  = nDigPosStart;
      int nNewSize  = 0;
      if(-1 != (nDigPosEnd=szCmdLineUp.Find(_T(' '),nDigPosStart)) || 
         -1 != (nDigPosEnd=szCmdLineUp.Find(_T('\0'),nDigPosStart))  ) {
        ASSERT(nDigPosEnd>nDigPosStart);
        CString szDigit = szCmdLineUp.Mid(nDigPosStart,nDigPosEnd-nDigPosStart);
        nNewSize = _ttoi(szDigit);
        //CString szZipName = CFileName(szLogName).GetBase() + ".loz";
        YEventsProtocol  theEvProtocol;
        theEvProtocol.Resize(szLogName,nNewSize);
      }
      return FALSE;
    }
  }

  if(cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
    cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	// Dispatch commands specified on the command line
  if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	return TRUE;
}
//-----------
int CSRSLogViewApp::ExitInstance() {	
//  delete m_pDocTemplate; m_pDocTemplate = NULL;
	return CParrent::ExitInstance();
}
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
  CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
//	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(_T("IDD_XABOUTDLG"))
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CSRSLogViewApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSRSLogViewApp message handlers


BOOL CAboutDlg::OnInitDialog() {
  CDialog::OnInitDialog();
  CStatic* pstaticAppIcon = static_cast<CStatic*>(GetDlgItem(IDC_APP_ICON));
  CWnd* pMainWnd = ::AfxGetMainWnd();
  HICON hIcon = NULL;
  if(pMainWnd!=NULL) 
    //hIcon = pMainWnd->GetIcon(TRUE);
    hIcon = ::AfxGetApp()->LoadIcon(IDR_MAINFRAME);//IDR_MAINFRAME
  else
    hIcon = ::AfxGetApp()->LoadIcon(128);//IDR_MAINFRAME
  pstaticAppIcon->SetIcon(hIcon);

  CString szAppName = CWinApp__GetVersionInfo(_T("ProductName"));
  CString szVersion = CWinApp__GetModuleVersion();
  CString szCopyright = CWinApp__GetVersionInfo(_T("LegalCopyright"));
  CString szBuild = g_szApplicationRelease;
  GetDlgItem(IDC_APPNAME)->SetWindowText(szAppName);
  GetDlgItem(IDC_VERSION)->SetWindowText(szVersion);
  GetDlgItem(IDC_COPYRIGHT)->SetWindowText(szCopyright);
  GetDlgItem(IDC_BUILD)->SetWindowText(szBuild);

//   if((::GetAsyncKeyState(VK_SHIFT)&0x8000)!=0) {
//     GetDlgItem(IDC_BUILD)->ShowWindow(SW_SHOW);
//   }
//   else GetDlgItem(IDC_BUILD)->ShowWindow(SW_HIDE);
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}
//---------------------------------------
void CSRSLogViewApp::OnFileOpen() {
  CFileDialog fd(TRUE, _T("log"), NULL, OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("All SRS log files (*.log; *.loz; *.cpc)|*.log;*.loz;*.cpc|SRS log files (*.log)|*.log|SRS log files (*.cpc)|*.cpc|SRS archived log files (*.loz)|*.loz||"));
  if(IDOK==fd.DoModal()) {
    CString szFileName = fd.GetPathName();
    OpenDocumentFile(szFileName);
  }
}
//---------------------------------------
CDocument* CSRSLogViewApp::OpenDocumentFile(LPCTSTR lpszFileName) {
  CFileName fn = lpszFileName;
  BOOL bTypeOK = FALSE;
  if(fn.GetExt().CompareNoCase(_T(".LOG"))==0 || fn.GetExt().CompareNoCase(_T(".CPC"))==0 || fn.GetExt().CompareNoCase(_T(".LOZ"))==0) {
    bTypeOK = TRUE;
  }
  _ASSERTE(bTypeOK && "document type mismatch");    
  if(bTypeOK) {
    return CParrent::OpenDocumentFile(lpszFileName);
  }
  if(IDYES==AfxMessageBox(ResourceString(IDS_UNALLOWABLE_LOG_TYPE,"Unallowable type of log file.  Still open?"),MB_YESNO))
    return CParrent::OpenDocumentFile(lpszFileName);
  return NULL;
}
//-----------
//---------------------------------------
void CSRSLogViewApp::OnUpdateFileNew(CCmdUI* pCmdUI) {
  pCmdUI->Enable(FALSE);
}
//-----------
void CSRSLogViewApp::OnUpdateFileSave(CCmdUI* pCmdUI) {
	pCmdUI->Enable(FALSE);	
}
//-----------
void CSRSLogViewApp::OnUpdateFileSaveAs(CCmdUI* pCmdUI) {
	pCmdUI->Enable(FALSE);	
}
//-----------
void CSRSLogViewApp::OnUpdateFilePrint(CCmdUI* pCmdUI) {
	pCmdUI->Enable(FALSE);	
}
//-----------
void CSRSLogViewApp::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) {
	pCmdUI->Enable(FALSE);
}
//-----------
void CSRSLogViewApp::OnUpdateFilePrintSetup(CCmdUI* pCmdUI) {
	pCmdUI->Enable(FALSE);
}
//-----------
void CSRSLogViewApp::OnUpdateWindowNew(CCmdUI* pCmdUI) {
	pCmdUI->Enable(FALSE);
}

void CAboutDlg::OnRButtonDown(UINT nFlags, CPoint point) {
  if(nFlags&(MK_SHIFT)) {
    CRect rectEmblem;
    CPoint point2 = point;
    ClientToScreen(&point2);
    GetDlgItem(IDC_STATIC_SRS_EMBLEM)->GetWindowRect(&rectEmblem);
    if(rectEmblem.PtInRect(point2)) {
      CString szInfo = "";
      #if defined(UNICODE) || defined(_UNICODE)
        szInfo+= "Unicode ";
      #else
        szInfo+= "Ansi ";
      #endif
      #if defined(_DEBUG)
        szInfo+= "debug";
      #else
        szInfo+= "release";
      #endif
      GetDlgItem(IDC_STATIC_INFO)->SetWindowText(szInfo);
    }
  }
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CSRSLogViewApp::OnLogResize() 
{
	// TODO: Add your command handler code here
	
}
