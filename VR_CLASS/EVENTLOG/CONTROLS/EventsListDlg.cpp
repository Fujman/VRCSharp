// EventsListDlg.cpp : implementation file
#include "stdafx.h"

#include "EventsPage.h"
#include "EventsListDlg.h"

#include "HeaderCtrl.h"

#include "EVENTLOG/EventLog.h"
#include "xassert.h"
#include "xCString.h"
#include "xCWnd.h"
#include "yEditDlg.h"


#define  _XDUMPLEVEL 255//-1
#include "xdump_trace.h"

#define ID_EVENTSLIST 100

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define STATE_LEVELS_NUM  8

#define PRECACHE_PAGES  5
//#define DATAPAGESIZE  CEventsPage::PAGEDATASIZE
#define VL_ADD_FLAGS  (LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL)

#define ID_TIMER_STATUS_UPDATE   1

#define ID_TIMER_CHECKLOAD_EL      1000 //msec
#define ID_TIMER_STATUS_UPDATE_EL  100  //msec

#define   WM_LOADED_BUFFER_BETWTHREAD   WM_USER+1
#define   WM_LOADED_BUFFER              WM_USER+2
#define   WM_EL_FIND                    WM_USER+3
#define   WM_EL_BEGIN_FIND              WM_USER+4
#define   WM_EL_FINISHED_FIND           WM_USER+5
#define   WM_EL_SET_FILTER              WM_USER+6
#define   WM_LIST_CH_CLIENTRECT         WM_USER+7
#define   ID_FIRST                WM_USER+8

#define   ID_LAST                 ID_FIRST+8  /*WM_USER+16*/

#define ID_MENU_SEARCH_UP         ID_FIRST
#define ID_MENU_SEARCH_DOWN       ID_FIRST+1
#define ID_MENU_QUICKSEARCH_UP    ID_FIRST+2
#define ID_MENU_QUICKSEARCH_DOWN  ID_FIRST+3
#define ID_MENU_GOTO_TIME         ID_FIRST+4
#define ID_MENU_SEARCHTEXT        ID_FIRST+5
#define ID_MENU_SEARCHTEXT_UP     ID_FIRST+6
#define ID_MENU_SEARCHTEXT_DOWN   ID_FIRST+7
#define ID_MENU_SET_FILTER        ID_FIRST+8

#define EL_FIND_TEXT      1
#define EL_FIND_ID        2
#define EL_FIND_TIME      3
#define EL_FIND_PARTTEXT  4
/////////////////////////////////////////////////////////////////////////////
// CEventsListDlg dialog

#define   ICON_STATE_ERROR      0
#define   ICON_STATE_WARNING    1
#define   ICON_STATE_INFO       2

#define   CO_NUMBER_OF_COLUMNS  5

#define   CO_TYPE   0
#define   CO_DATE   1
#define   CO_TIME   2
#define   CO_CHAN   3
#define   CO_MESS   4

#ifdef DEBUG_EL
#include "yTimer.h"
#endif


CMessagesArbiter::CMessage::~CMessage() {
  SetData(NULL,dataNone);
}
////////CEventsListDlg////////////////////////////////////////////////////
CEventsListDlg::CEventsListDlg(/*CWnd* pParent*/ /*=NULL*/)
  /*: CParent(CEventsListDlg::IDD, pParent)*/
{
  //{{AFX_DATA_INIT(CEventsListDlg)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  STATIC_ASSERT(STATE_LEVELS_NUM>=0 && STATE_LEVELS_NUM<10,STATE_LEVELS_NUM_overflow);
  m_pLoaderThread   = NULL;
  m_pFindThread     = NULL;

  m_hNeedLoadEvent  = NULL;
  m_hNeedFindEvent  = NULL;

  m_hLoaderThread   = NULL;
  m_hFindThread     = NULL;

  m_bNeedReset      = FALSE;
  m_bPausePreloader = FALSE;
  m_bNeedKillLoader = FALSE;
  m_bNeedStopFind   = FALSE;

  m_bEnableFilterDialog = FALSE;
  m_bShowLogStatus  = FALSE;

  m_bLoadLeft       = TRUE;

  m_pevp            = NULL;
  m_nLogSize        = 0;
  m_nPageDataSize   = CEventsPage::PAGEDATASIZE;
  m_nOpenMode       = 0;

  m_bIsAttachedLog  = FALSE;

  m_paPreCacheOffs  = NULL;
  m_paPages         = NULL;
  m_paPreCache      = NULL;
  m_pPagePreCache   = NULL;
  m_pbyPageBuf      = NULL;

  m_pTextFindInfo   = NULL;
  m_nSerachStart    = -1;

  m_pList           = NULL;
  m_pLogStatus      = NULL;

  m_pcachedEv       = NULL;
  m_ncachedEv       = ULONG_MAX;

  m_pcachedFEv      = NULL;
  m_ncachedFEv      = ULONG_MAX;

  #ifdef DEBUG_EL
  m_szEvNumText     = "";
  #endif
  m_szLogStatusText = "";
  m_nFirstPageInd   = ULONG_MAX;
  m_nFirstOffset    = ULONG_MAX;
  m_nFirstPageOffset= ULONG_MAX;
  m_nLastPageOffset = ULONG_MAX;
  m_nLastPageIndex  = ULONG_MAX;

  m__nCachedPageNum = ULONG_MAX;
  m__nCachedPageInd = ULONG_MAX;

  m_nHeaderLines    = 1;

//  m_nViewMode       = 1;
  m_bDetailImages   = FALSE;
  SetDetailImages(TRUE);

  m_bHideOnClose    = FALSE;//Ay 19.01.2014
}

void CEventsListDlg::SetHideOnClose(BOOL bHideOnClose)
{
  m_bHideOnClose = bHideOnClose;
}


void CEventsListDlg::DoDataExchange(CDataExchange* pDX) {
  CParent::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CEventsListDlg)
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEventsListDlg, CEmptyAnyDialog<CResizableDialog>/*CParent*/)
  //{{AFX_MSG_MAP(CEventsListDlg)
  ON_WM_SIZE()
  ON_WM_DESTROY()
  ON_WM_CONTEXTMENU()
  ON_WM_TIMER()
  ON_WM_MOVE()
  ON_WM_CLOSE()
  //}}AFX_MSG_MAP
  ON_COMMAND_RANGE(ID_FIRST, ID_LAST, OnMenuCommandRange)
  ON_NOTIFY(LVN_GETDISPINFO, ID_EVENTSLIST, OnGetdispinfoEventslist)
//  ON_NOTIFY(LVN_COLUMNCLICK, ID_EVENTSLIST, OnColumnclick)
//  ON_NOTIFY(LVN_ODFINDITEM, ID_EVENTSLIST, OnOdfinditemEventslist)
  ON_MESSAGE(WM_APP,            OnLogEvent)//called with LOG locking!
  ON_MESSAGE(WM_APP+1,          OnAttach)//called with LOG locking!
  ON_MESSAGE(WM_LOADED_BUFFER_BETWTHREAD,  OnLoadedBufferBetweenThread) //called with loader locking!
  ON_MESSAGE(WM_LOADED_BUFFER,   OnLoadedBuffer) //called with loader locking!
  ON_MESSAGE(WM_EL_FIND,         OnELFindItem)
  ON_MESSAGE(WM_EL_BEGIN_FIND,   OnELBeginFindItem)
  ON_MESSAGE(WM_EL_FINISHED_FIND,OnELFinishFindItem)
  ON_MESSAGE(WM_EL_SET_FILTER,   OnSetFilter)
  ON_MESSAGE(WM_LIST_CH_CLIENTRECT,OnListChangedSize)
//  ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventsListDlg message handlers
int CEventsListDlg::ReCreate(CWnd *pWnd) //AY 13.01.2013 new realization 
{
  CREATE_STRUCT cs = {{sizeof(WINDOWPLACEMENT)}};
  cs.wndpl           ; pWnd->GetWindowPlacement(&cs.wndpl);
  cs.dwHelp          = pWnd->GetWindowContextHelpId();
  cs.dwStyle         = pWnd->GetStyle();
  cs.dwStyleEx       = pWnd->GetExStyle();
  cs.hIcon           = pWnd->GetIcon(FALSE);
  cs.nID             = pWnd->GetDlgCtrlID();
  CString szText     ; pWnd->GetWindowText(szText);
  cs.szText          = szText;
  cs.pParent         = pWnd->GetParent();

  CParent* pParentDlg= (CParent*) pWnd->GetParent();

  pWnd->DestroyWindow();

//BOOL bRet = CParent::Create(WS_VISIBLE|WS_CHILD,0,NULL,pParentDlg);
//if(bRet==FALSE)
//  return -1;//error

  return CEventsListDlg::Create(&cs);
}

int CEventsListDlg::Create(CREATE_STRUCT* pcs) 
{
  WINDOWPLACEMENT wndpl     = pcs->wndpl     ;
  DWORD           dwHelp    = pcs->dwHelp    ;
  DWORD           dwStyle   = pcs->dwStyle   ;
  DWORD           dwStyleEx = pcs->dwStyleEx ;
  HICON           hIcon     = pcs->hIcon     ;
  int             nID       = pcs->nID       ;
  CString         szText    = pcs->szText    ;
  CParent*        pParentDlg= (CParent*) pcs->pParent;

  BOOL bRet = CParent::Create(dwStyle,dwStyleEx,NULL,pParentDlg);
  if(bRet==FALSE)
    return -1;//error

#if 0 //OLD REALIZATION ---------------------------------------------------------------
  return 0;
}

int CEventsListDlg::ReCreate(CWnd *pWnd) 
{
  WINDOWPLACEMENT wndpl = {sizeof(wndpl)}; pWnd->GetWindowPlacement(&wndpl);
  DWORD dwHelp          = pWnd->GetWindowContextHelpId();
  DWORD dwStyle         = pWnd->GetStyle();
  DWORD dwStyleEx       = pWnd->GetExStyle();
  HICON hIcon           = pWnd->GetIcon(FALSE);
  int   nID             = pWnd->GetDlgCtrlID();
  CString szText;         pWnd->GetWindowText(szText);
  CParent* pParentDlg   = (CParent*) pWnd->GetParent();

  pWnd->DestroyWindow();

  BOOL bRet = CParent::Create(WS_VISIBLE|WS_CHILD,0,NULL,pParentDlg);
  if(bRet==FALSE)
    return -1;//error
#endif//OLD REALIZATION ----------------------------------------------------------------

  if(nID!=0xFFFF)                   SetDlgCtrlID(nID);
  if(!szText.IsEmpty())             SetWindowText(szText);
  if(hIcon!=NULL)                   SetIcon(hIcon,TRUE);
  if(dwHelp!=0)                     SetWindowContextHelpId(dwHelp);
  UINT nFlags = SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE;
  ModifyStyle(0,WS_CLIPCHILDREN,nFlags);
  if(dwStyle  &WS_CLIPSIBLINGS)     ModifyStyle(0,WS_CLIPSIBLINGS,nFlags);
  if(dwStyle  &WS_GROUP)            ModifyStyle(0,WS_GROUP,nFlags);

  if(dwStyle  &WS_TABSTOP)          ModifyStyle(0,WS_TABSTOP,nFlags);
  if(dwStyle  &WS_BORDER)           ModifyStyle(0,WS_BORDER,nFlags);
  if(dwStyle  &WS_THICKFRAME)       ModifyStyle(0,WS_THICKFRAME,nFlags);
  if(dwStyle  &WS_DLGFRAME)         ModifyStyle(0,WS_DLGFRAME,nFlags);
  if(dwStyleEx&WS_EX_CLIENTEDGE)    ModifyStyleEx(0,WS_EX_CLIENTEDGE,nFlags);
  if(dwStyleEx&WS_EX_WINDOWEDGE)    ModifyStyleEx(0,WS_EX_WINDOWEDGE,nFlags);
  if(dwStyleEx&WS_EX_STATICEDGE)    ModifyStyleEx(0,WS_EX_STATICEDGE,nFlags);

  if(dwStyleEx&WS_EX_TRANSPARENT)   ModifyStyleEx(0,WS_EX_TRANSPARENT,nFlags);
  if(dwStyleEx&WS_EX_ACCEPTFILES)   ModifyStyleEx(0,WS_EX_ACCEPTFILES,nFlags);
  if(dwStyleEx&WS_EX_CONTROLPARENT) ModifyStyleEx(0,WS_EX_CONTROLPARENT,nFlags);
  if(dwStyleEx&WS_EX_TOOLWINDOW)    ModifyStyleEx(0,WS_EX_TOOLWINDOW,nFlags);
  if(dwStyleEx&WS_EX_TOPMOST)       ModifyStyleEx(0,WS_EX_TOPMOST,nFlags);
  if(dwStyle  &WS_DISABLED)         ModifyStyle(0,WS_DISABLED,nFlags);
  else                              ModifyStyle(WS_DISABLED,0,nFlags);

  if(m_pList) {
    RemoveAnchor(m_pList->GetDlgCtrlID());
    delete m_pList;
  }
  m_pList = new CEventsList();

  WINDOWPLACEMENT wndpl1 = {sizeof(wndpl1)}; GetWindowPlacement(&wndpl1);
  RECT& rect = wndpl1.rcNormalPosition;
  GetClientRect(&rect);
  CRect rectList(rect);

  CRect rectText(rectList);
  CDC dc;
  dc.CreateCompatibleDC(NULL);
  SelectObject(dc.m_hDC, GetFont());
  CSize size;
  GetTextExtentPoint32(dc.m_hDC, _T(" "), 1, &size );
  m_nLogStatusHeight  = size.cy;
  rectText.top=rectText.bottom-m_nLogStatusHeight;

  if(m_pLogStatus) {
    delete m_pLogStatus;
    m_pLogStatus = NULL;
  }
  m_pLogStatus = new CStatic;
  m_pLogStatus->Create(NULL,WS_CHILDWINDOW|WS_VISIBLE|SS_LEFTNOWORDWRAP,rectText,this);
  m_pLogStatus->SetFont(GetFont());
  m_pLogStatus->SetWindowText(_T(""));

  m_pList->Create(WS_VISIBLE|WS_TABSTOP,/*WS_EX_CLIENTEDGE*/0, rectList, this, ID_EVENTSLIST);
  AddAnchor(ID_EVENTSLIST,TOP_LEFT,BOTTOM_RIGHT);
  AddAnchor(m_pLogStatus->GetSafeHwnd(),BOTTOM_LEFT,BOTTOM_RIGHT);
  m_ImageList.DeleteImageList();
  if(FALSE == m_ImageList.Create(16,16,ILC_COLOR16|ILC_MASK,0,4)) {
    return -1;//error
  }
  if(GetDetailImages()) {
    LPCTSTR RESOURCE;
    int iTypeNum;
    LPCTSTR Type[] = {IDI_ERROR,IDI_WARNING,IDI_INFORMATION};
    for(iTypeNum=0, RESOURCE=Type[iTypeNum];iTypeNum<sizeof(Type)/sizeof(Type[0]);++iTypeNum) {
      RESOURCE = Type[iTypeNum];
      for(int i=0;i<(STATE_LEVELS_NUM);++i) {
        HICON  hIc = (HICON)::LoadImage(NULL, RESOURCE, IMAGE_ICON , 16, 16, LR_SHARED);
        HICON hImage = CreateImage(hIc,16,16,i,TRUE);
        m_ImageList.Add(hImage);
        DestroyImage(hImage);
      }
    }
  }
  else {
    LPCTSTR RESOURCE;
    int iTypeNum;
    LPCTSTR Type[] = {IDI_ERROR,IDI_WARNING,IDI_INFORMATION};
    for(iTypeNum=0, RESOURCE=Type[iTypeNum];iTypeNum<sizeof(Type)/sizeof(Type[0]);++iTypeNum) {
      RESOURCE = Type[iTypeNum];
      for(int i=0;i<(STATE_LEVELS_NUM);++i) {
        HICON  hIc = (HICON)::LoadImage(NULL, RESOURCE, IMAGE_ICON , 16, 16, LR_SHARED);
        HICON hImage = CreateImage(hIc,16,16,i,FALSE);
        m_ImageList.Add(hImage);
        DestroyImage(hImage);
      }
    }
    m_ImageList.Add(LoadIcon(NULL,IDI_ERROR));
    m_ImageList.Add(LoadIcon(NULL,IDI_WARNING));
    m_ImageList.Add(LoadIcon(NULL,IDI_INFORMATION));
  }
  m_pList->SetImageList(&m_ImageList,LVSIL_SMALL);
//   m_pList->InsertColumn(CO_TYPE,_T(""),LVCFMT_LEFT,32);
//   m_pList->InsertColumn(CO_DATE,_T(""),LVCFMT_LEFT,70);
//   m_pList->InsertColumn(CO_TIME,_T(""),LVCFMT_LEFT,60);
//  m_pList->InsertColumn(CO_CHAN,_T(""),LVCFMT_LEFT,20);
//  m_pList->InsertColumn(CO_MESS,_T(""),LVCFMT_LEFT,400);
  for(int i=0;i<CO_NUMBER_OF_COLUMNS;++i)
    m_pList->InsertColumn(i,_T(""),LVCFMT_LEFT,0);
  LVCOLUMN col;
  col.mask = LVCF_FMT | LVCF_WIDTH;
  //_tcscpy(col.pszText,_T(""));
  col.fmt = LVCFMT_LEFT;
  col.cx = 19; m_pList->SetColumn(CO_TYPE,&col);
  col.cx = 80; m_pList->SetColumn(CO_DATE,&col);
  col.cx = 64; m_pList->SetColumn(CO_TIME,&col);
  col.cx = 30; m_pList->SetColumn(CO_CHAN,&col);
  col.cx = 600; m_pList->SetColumn(CO_MESS,&col);

  SetHeaderLinesCount(1);

//   m_pList->InsertColumn(CO_MESS,_T(""),LVCFMT_LEFT,400);
//   m_pList->InsertColumn(CO_CHAN,_T(""),LVCFMT_LEFT,20);
//   m_pList->InsertColumn(CO_TIME,_T(""),LVCFMT_LEFT,60);
//   m_pList->InsertColumn(CO_DATE,_T(""),LVCFMT_LEFT,70);
//   m_pList->InsertColumn(CO_TYPE,_T(""),LVCFMT_LEFT,32);


  m_pList->SetItemCountEx(0,VL_ADD_FLAGS);
  if(dwStyle  &WS_VISIBLE)
    wndpl.showCmd = SW_SHOW;
  else
    wndpl.showCmd = SW_HIDE;
  SetWindowPlacement(&wndpl);
  m_pList->SetCallbackMask(LVIS_STATEIMAGEMASK); //LVIS_FOCUSED|LVIS_SELECTED | LVIS_OVERLAYMASK
  ShowLogStatus(IsShowLogStatus());

  if(m_pTextFindInfo)
    delete m_pTextFindInfo;
  m_pTextFindInfo = new CFindInfo;

  CRect rectDlgWait;
  m_pList->GetClientRectWithoutScrolBar(rectDlgWait);
  rectDlgWait.left = rectDlgWait.right-100;
  rectDlgWait.top  = rectDlgWait.bottom-20;
#if USE_DLGWAIT
  m_dlgWait.ReCreate(rectDlgWait,_T("wait..."),this);
  m_dlgWait.Show(FALSE);
#endif
  return 0;
}
//-----------
BOOL CEventsListDlg::OnInitDialog() {
  CParent::OnInitDialog();
  ShowSizeGrip(FALSE);
  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}
//-----------
void CEventsListDlg::OnClose()
{
  if(m_bHideOnClose)
    CWnd__Hide(this);
  else  
    CParent::OnClose();
}

//-----------
void CEventsListDlg::OnDestroy() {
  DetachLog();
  if(m_pList) {
    RemoveAnchor(m_pList->GetDlgCtrlID());
    delete m_pList; m_pList = NULL;
  }
  if(m_pLogStatus && m_pLogStatus->GetSafeHwnd())
    RemoveAnchor(m_pLogStatus->GetSafeHwnd());
  if(m_pLogStatus) {
    delete m_pLogStatus;
    m_pLogStatus = NULL;
  }
  if(m_pcachedEv) {
    YEvent::Delete(m_pcachedEv,m_Buf);
    m_pcachedEv = NULL;
    m_ncachedEv = ULONG_MAX;
    #ifdef DEBUG_EL
    m_szEvNumText = "";
    #endif
  }
  if(m_pcachedFEv) {
    YEvent::Delete(m_pcachedFEv,m_BufFEv);
    m_pcachedFEv = NULL;
    m_ncachedFEv = ULONG_MAX;
  }
  if(m_pTextFindInfo) {
    delete m_pTextFindInfo;
    m_pTextFindInfo = NULL;
  }
  CParent::OnDestroy();
}
//-----------
LRESULT CEventsListDlg::OnLogEvent(WPARAM, LPARAM lParam) {
  //int   nSize = wParam; //future usage
  ULONG nPageOffset = lParam & ~(GetPageSize()-1);
  ASSERT(nPageOffset<GetLogSize());
  if(m_pevp==NULL || nPageOffset>=GetLogSize())
    return 0;
  if(nPageOffset==m_nLastPageOffset) {
    ULONG nPageInd = nPageOffset/GetPageSize();
    ASSERT(nPageInd<m_paPages->GetPagesNum());
    if(nPageInd<m_paPages->GetPagesNum())
      m_paPages->m_paEP[nPageInd].SetIdent(FALSE);
  }
  else {
    m_nLastPageOffset = nPageOffset;
    m_nLastPageIndex  = nPageOffset/GetPageSize(); //KSN 2006_01_27 "%" -> "/"
  }
  return 0;
}
//-----------
LRESULT CEventsListDlg::OnLoadedBufferBetweenThread(WPARAM, LPARAM) {
  CMessagesArbiter::CMessage message;
  message.m_hMesWnd = GetSafeHwnd();
  message.m_nMessage= WM_LOADED_BUFFER;
  message.m_bPostMode = FALSE;
  message.m_WParam  = NULL;
  message.m_LParam  = NULL;
  message.SetData(NULL,CMessagesArbiter::CMessage::dataNone);
  m_MesArb.DoPushMessage(&message);
  return 0;
}
//-----------
LRESULT CEventsListDlg::OnLoadedBuffer(WPARAM, LPARAM) {
  ULONG nPages = m_paPreCache->GetPagesNum();
  if(!m_bNeedReset) {
    for(ULONG i=0;i<nPages;++i) {
      CEventsPage& page = m_paPreCache->m_paEP[i];
      if(page.IsLoaded())
        LoadPage(page,m_paPreCacheOffs[i]);
      else break;
    }
  } else m_bNeedReset = FALSE;
  SetEvent(m_hNeedLoadEvent);
  m_MesArb.DoEndProcessing(); //
  return 0;
}
//-----------
LRESULT CEventsListDlg::OnELFindItem(WPARAM wParam, LPARAM lParam) {
  UINT nChar  = wParam;
  UINT nAlg   = lParam;
  BOOL bFndIdent = FALSE;
  if(!  (nChar==CFindInfo::dirUP     || nChar==CFindInfo::dirDOWN
      || nChar==CFindInfo::dirUPDOWN || nChar==CFindInfo::dirDOWNUP
      || nChar==CFindInfo::dirNONE))
  {
    ASSERT(0);
    return 0;
  }
  CFindInfo   fi;
  fi.m_nDirection   = nChar;
  int nSelectedItem = m_pList->GetNextItem(-1,LVNI_SELECTED);
  if(nAlg==EL_FIND_TEXT && nSelectedItem!=-1) {
    TCHAR buf[STACK_LEN];
    int nRetTextSize=0;
    if(GetEventTextF(nSelectedItem,STACK_LEN,buf,nRetTextSize)) {
      fi.m_dwFlags  = CFindInfo::fndText;
      fi.m_szText = buf;
      bFndIdent = TRUE;
    }
  }
  if(!bFndIdent && nAlg==EL_FIND_ID && nSelectedItem!=-1) {
    UINT nMessage;
    if(GetEventIDF(nSelectedItem,nMessage)) {
      fi.m_dwFlags  = CFindInfo::fndID;
      fi.m_nID  = nMessage;
      bFndIdent = TRUE;
    }
  }
  if(!bFndIdent && nAlg==EL_FIND_TIME) {
    if(nSelectedItem==-1)
      nSelectedItem = m_pList->GetLastVisibleItem();
    if(nSelectedItem==-1)
      return  -1;
    YTime tTime = YTime::GetCurrentTime();//TO DO: query true server time
    GetEventTimeF(nSelectedItem,tTime);
    CTimeDialog dlgTime(tTime, this,_T("Ok\nCancel\n"));
    BOOL bRes = dlgTime.InitModal(WS_CAPTION | WS_VISIBLE | WS_DLGFRAME | WS_POPUP |
                                  DS_MODALFRAME | DS_SETFONT);
    if(dlgTime.DoModal()==IDOK) {
      fi.m_dwFlags  = CFindInfo::fndTime;
      fi.m_tTime  = dlgTime.GetDateTime();
      bFndIdent = TRUE;
    }
  }
  if(!bFndIdent && nAlg==EL_FIND_PARTTEXT) {
    if(nSelectedItem==-1)
      nSelectedItem = m_pList->GetLastVisibleItem();
    if(nSelectedItem==-1)
      return  -1;
    int nRetTextSize=0;
    if(fi.m_nDirection==CFindInfo::dirNONE) {
      CSimpleEditDlg<CEdit> dlgFind(NULL,fi.m_szText,WS_VSCROLL|ES_MULTILINE|ES_LEFT);
      CRect rc = CWnd__GetScreenPart(20,10);
      dlgFind.InitModal(WS_POPUPWINDOW|WS_CAPTION,0,&rc,this);
      if(IDOK==dlgFind.DoModal()) {
        m_pTextFindInfo->m_szText = dlgFind.GetText();
        m_pTextFindInfo->m_dwOtherFlags|=CFindInfo::fndPartial;
        bFndIdent = (m_pTextFindInfo->m_szText.IsEmpty())?FALSE:TRUE;
      }
    }
    //if(!m_pTextFindInfo || m_pTextFindInfo->m_szText.IsEmpty()) {
    //  return -1;
    //}
    fi.m_dwFlags  = CFindInfo::fndText;
    fi.m_szText = m_pTextFindInfo->m_szText;
    fi.m_dwOtherFlags|=CFindInfo::fndPartial;
  }
  if(bFndIdent) {
    CMessagesArbiter::CMessage message;
    message.m_hMesWnd = GetSafeHwnd();
    message.m_nMessage= WM_EL_BEGIN_FIND;
    message.m_bPostMode = TRUE;
    message.SetData(&fi,CMessagesArbiter::CMessage::dataFindInfo);
    message.m_LParam  = nSelectedItem;
    m_MesArb.DoPushMessage(&message);
  }
  return 0;
}
//-------------
LRESULT CEventsListDlg::OnELBeginFindItem(WPARAM wParam, LPARAM lParam) {
  if(wParam==0)
    return -1;
  CFindInfo* pFindInfo = (CFindInfo*)wParam;
  *m_pTextFindInfo = *pFindInfo;
  m_nSerachStart  = (UINT)lParam;
#if USE_DLGWAIT
  m_dlgWait.Show(TRUE);
#endif
  SetEvent(m_hNeedFindEvent);
  return 0;
}

LRESULT CEventsListDlg::OnELFinishFindItem(WPARAM wParam, LPARAM lParam) {
  //ensure visible founded element
#if USE_DLGWAIT
  m_dlgWait.Show(FALSE);
#endif
  if(m_nSerachStart!=-1) {
    m_pList->EnsureVisible(m_nSerachStart,TRUE);
    m_pList->SetItemState(m_nSerachStart, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
  }
  m_MesArb.DoEndProcessing();
  return 0;
}

/*
LRESULT CEventsListDlg::OnELFindItem(WPARAM wParam, LPARAM lParam) {
  UINT nChar  = wParam;
  UINT nAlg   = lParam;
//  BOOL bRet = m_cs.Lock();
  if(!  (nChar==CFindInfo::dirUP     || nChar==CFindInfo::dirDOWN
      || nChar==CFindInfo::dirUPDOWN || nChar==CFindInfo::dirDOWNUP
      || nChar==CFindInfo::dirNONE))
  {
    ASSERT(0);
    return 0;
  }
  CFindInfo   fi;
  fi.m_nDirection   = nChar;
  int nSelectedItem = m_pList->GetNextItem(-1,LVNI_SELECTED);
  if(nAlg==EL_FIND_TEXT && nSelectedItem!=-1) {
    TCHAR buf[STACK_LEN];
    int nRetTextSize=0;
    if(GetEventTextF(nSelectedItem,STACK_LEN,buf,nRetTextSize)) {
      fi.m_dwFlags  = CFindInfo::fndText;
      fi.m_szText = buf;
      CMessage message;
      message.m_hMesWnd = GetSafeHwnd();
      message.m_nMessage= WM_EL_BEGIN_FIND;
      message.m_bPostMode = TRUE;
      message.m_WParam  = wParam;
      message.m_LParam  = lParam;
      message.m_nDataType = CMessage::dataFindInfo;
      message.m_pData = new CFindInfo(&fi);
      m_MesArb.DoPushMessage(message);

//      message.
//      m_MesArb.DoPushMessage(
      _FindEvent(&fi,nSelectedItem);
      if(nSelectedItem!=-1) {
        m_pList->EnsureVisible(nSelectedItem,TRUE);
        m_pList->SetItemState(nSelectedItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
      }
      return 0;
    }
  }
  if(nAlg==EL_FIND_ID && nSelectedItem!=-1) {
    UINT nMessage;
    if(GetEventIDF(nSelectedItem,nMessage)) {
      fi.m_dwFlags  = CFindInfo::fndID;
      fi.m_nID  = nMessage;
      CRect rect;
      m_pList->GetClientRect(&rect);
      rect.left = rect.right-60;
      rect.top  = rect.bottom-20;
      CMessageDlg dlg;
      dlg.ReCreate(rect,_T("wait..."),this);
      nSelectedItem = _FindEvent(&fi,nSelectedItem);
      dlg.ShowWindow(SW_HIDE);
      dlg.DestroyWindow();
      if(nSelectedItem!=-1) {
        m_pList->EnsureVisible(nSelectedItem,TRUE);
        m_pList->SetItemState(nSelectedItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
      }
    }
  }
  if(nAlg==EL_FIND_TIME) {
    if(nSelectedItem==-1)
      nSelectedItem = m_pList->GetLastVisibleItem();
    if(nSelectedItem==-1)
      return  -1;
    YTime tTime = YTime::GetCurrentTime();
    GetEventTimeF(nSelectedItem,tTime);
    CTimeDialog dlgTime(tTime, this,_T("Ok\nCancel\n"));
    BOOL bRes = dlgTime.InitModal(WS_CAPTION | WS_VISIBLE | WS_DLGFRAME | WS_POPUP |
                                  DS_MODALFRAME | DS_SETFONT);
    if(dlgTime.DoModal()==IDOK) {
      fi.m_dwFlags  = CFindInfo::fndTime;
      fi.m_tTime  = dlgTime.GetDateTime();
      CRect rect;
      m_pList->GetClientRect(&rect);
      rect.left = rect.right-60;
      rect.top  = rect.bottom-20;
      CMessageDlg dlg;
      dlg.ReCreate(rect,_T("wait..."),this);
      nSelectedItem = _FindEvent(&fi,nSelectedItem);
      dlg.ShowWindow(SW_HIDE);
      dlg.DestroyWindow();
      if(nSelectedItem!=-1) {
        m_pList->EnsureVisible(nSelectedItem,TRUE);
        m_pList->SetItemState(nSelectedItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
      }
    }
  }
  if(nAlg==EL_FIND_PARTTEXT) {
    if(nSelectedItem==-1)
      nSelectedItem = m_pList->GetLastVisibleItem();
    if(nSelectedItem==-1)
      return  -1;
    int nRetTextSize=0;
    if(fi.m_nDirection==0) {
      CSimpleEditDlg<CEdit> dlgFind(NULL,fi.m_szText,WS_VSCROLL|ES_MULTILINE|ES_LEFT);
      CRect rc = CWnd__GetScreenPart(20,10);
      dlgFind.InitModal(WS_POPUPWINDOW|WS_CAPTION,0,&rc,this);
      if(IDOK==dlgFind.DoModal()) {
        m_pTextFindInfo->m_szText = dlgFind.GetText();
        m_pTextFindInfo->m_dwOtherFlags|=CFindInfo::fndPartial;
      }
      return 0;
    }
    if(!m_pTextFindInfo || m_pTextFindInfo->m_szText.IsEmpty()) {
      return -1;
    }
    fi.m_dwFlags  = CFindInfo::fndText;
    fi.m_szText = m_pTextFindInfo->m_szText;
    fi.m_dwOtherFlags|=CFindInfo::fndPartial;
    CRect rect;
    m_pList->GetClientRect(&rect);
    rect.left = rect.right-60;
    rect.top  = rect.bottom-20;
    CMessageDlg dlg;
    dlg.ReCreate(rect,_T("wait..."),this);
    nSelectedItem = _FindEvent(&fi,nSelectedItem);
    dlg.ShowWindow(SW_HIDE);
    dlg.DestroyWindow();
    if(nSelectedItem!=-1) {
      m_pList->EnsureVisible(nSelectedItem,TRUE);
      m_pList->SetItemState(nSelectedItem, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
    }
    TRACE(_T(""));
  }
  return 0;
}
*/
//-----------------------------------
LRESULT CEventsListDlg::OnSetFilter(WPARAM wParam, LPARAM lParam) {
  _ASSERTE(!"filter dialog under construction");
  //TODO filter dialog
  return 0;
}

LRESULT CEventsListDlg::OnListChangedSize(WPARAM wParam, LPARAM lParam) {
#if USE_DLGWAIT
  if(m_dlgWait.m_hWnd) {
    CRect rectList;
    CRect rect;
    m_pList->GetClientRectWithoutScrolBar(rectList);
//     rectList.right-=16;
//     rectList.bottom-=16;
    m_dlgWait.GetWindowRect(&rect);
    m_dlgWait.MoveWindow(rectList.right-rect.Width(),
                         rectList.bottom-rect.Height(),
                         rect.Width(),
                         rect.Height());
  }
  else ASSERT(0);
#endif
  return 0;
}

//-----------------------------------
#ifdef DEBUG_EL_TIME
YTimeSpan g_tStartTime= YTime::INVALID();
#endif

LRESULT CEventsListDlg::OnAttach(WPARAM wParam, LPARAM lParam) {// called from locked state of log!
  if(AttachLog((YEventsProtocol*)wParam, (int)lParam) >= 0) {
    InitForPreloader();
    #ifdef DEBUG_EL_TIME
    g_tStartTime  = YTimer::GetCurrentSpan(); //AY 18.11.2009 OLD: YTime::GetCurrentTime
    #endif
    m_hNeedLoadEvent  = ::CreateEvent(NULL,TRUE,FALSE,NULL);
    m_hNeedFindEvent  = ::CreateEvent(NULL,TRUE,FALSE,NULL);
    m_pLoaderThread   = AfxBeginThread(_BackgroundPreLoading, (LPVOID)this, (int)THREAD_PRIORITY_BELOW_NORMAL);
    m_pFindThread     = AfxBeginThread(_BackgroundFinding,    (LPVOID)this, (int)THREAD_PRIORITY_BELOW_NORMAL);
    VERIFY( DuplicateHandle (GetCurrentProcess(), m_pLoaderThread->m_hThread,
      GetCurrentProcess(), &m_hLoaderThread, 0L, FALSE, DUPLICATE_SAME_ACCESS) );
    VERIFY( DuplicateHandle (GetCurrentProcess(), m_pFindThread->m_hThread,
      GetCurrentProcess(), &m_hFindThread, 0L, FALSE, DUPLICATE_SAME_ACCESS) );
    SetEvent(m_hNeedLoadEvent);
    SetTimer(ID_TIMER_STATUS_UPDATE,ID_TIMER_STATUS_UPDATE_EL,NULL);
  }
  return 0;
}
//-----------
int CEventsListDlg::AttachLog(YEventsProtocol *pevp, int nMode) {
  if(!pevp || IsAttachedLog())
    return -1;
  ULONG nPages;
  m_pevp      = pevp;
  m_nOpenMode = nMode;
  m_nLogSize  = m_pevp->GetFileSize();
  m_nPageDataSize   = m_pevp->GetPageSize();
  nPages = (GetLogSize() / m_nPageDataSize);
  ASSERT((m_nLogSize%CEventsPage::PAGEDATASIZE)==0);
  ASSERT(m_nPageDataSize==CEventsPage::PAGEDATASIZE);
  ASSERT(nPages>0);

  delete m_paPreCacheOffs; m_paPreCacheOffs = NULL;
  if(m_paPages) {
    delete m_paPages; m_paPages = NULL;
  }
  if(m_paPreCache) {
    delete m_paPreCache; m_paPreCache= NULL;
  }
  if(m_pPagePreCache) {
    delete m_pPagePreCache; m_pPagePreCache= NULL;
  }
  delete  m_pbyPageBuf; m_pbyPageBuf  = NULL;

  //--log pages prepare

  //--pages prepare (optimized for Pentium CPU cache usage!!!)
  m_paPages       = new CEventsPageArray(nPages,FALSE);
  m_paPreCache    = new CEventsPageArray(PRECACHE_PAGES,TRUE);
  m_pPagePreCache = new CEventsPageArray(1,FALSE);
  m_paPreCacheOffs= new UINT[PRECACHE_PAGES];
  m_pbyPageBuf    = new BYTE[CEventsPage::PAGEDATASIZE];
  //--
  ULONG nLP,nLPInd,nLPOffs;

  switch(m_nOpenMode) {
    default:
      ASSERT(0);
    case (YEventsProtocol::VIEWALL):    //global start
      SetFirstOffset(m_pevp->GetGlobalFirst());
      break;
    case (YEventsProtocol::VIEWSESSION)://start session
      SetFirstOffset(m_pevp->GetSessionFirst());
    break;
  }
  m_nFirstPageInd = GetFirstPageOffset() / m_nPageDataSize;

  nLPOffs = m_pevp->m_nWritePageOffset & ~(GetPageSize()-1);
  nLP     = m_pevp->m_nWritePageNumber;
  nLPInd  = nLPOffs / GetPageSize();

  ASSERT(GetFirstOffset()<GetLogSize());

  m_pList->SetItemCountEx(0,VL_ADD_FLAGS);

//   m_paPages->SetFirstPageNum(nFP);
//   m_paPages->SetFirstPageIndex(nFPInd);

  m_paPages->SetLastPageNum(nLP);
  m_paPages->SetLastPageIndex(nLPInd);

  m_paPages->SetFirstPageNum(nLP);
  m_paPages->SetFirstPageIndex(nLPInd);

  m_bIsAttachedLog  = TRUE;
  return 0; //0-ok
}
//-----------
int CEventsListDlg::DetachLog() {
  if(IsAttachedLog()) {
    m_bIsAttachedLog  = FALSE;
    m_bNeedKillLoader = TRUE;
    SetEvent(m_hNeedLoadEvent);
    SetEvent(m_hNeedFindEvent);
    DWORD dwExitCode=0;
    do {

      switch(WaitForSingleObject(m_hLoaderThread,5000))
      {
        case WAIT_FAILED:
          m_pLoaderThread = NULL;
          break;
        case WAIT_OBJECT_0:
          m_pLoaderThread = NULL;
          break;
        case WAIT_TIMEOUT:
            continue;
        default:
          TRACE(_T(""));
            break;
      }
    } while(m_pLoaderThread!=NULL);
    CloseHandle(m_hLoaderThread);  m_hLoaderThread  = NULL;
    CloseHandle(m_hNeedLoadEvent); m_hNeedLoadEvent = NULL;
    do {
      switch(WaitForSingleObject(m_hFindThread,5000))
      {
      case WAIT_FAILED:
        ASSERT(0);
      case WAIT_OBJECT_0:
        m_pFindThread = NULL;
        break;
      case WAIT_TIMEOUT:
        continue;
      default:
        TRACE(_T(""));
        break;
      }
    } while(m_pFindThread!=NULL);
    CloseHandle(m_hFindThread); m_hFindThread = NULL;
    CloseHandle(m_hNeedFindEvent);  m_hNeedFindEvent  = NULL;
    if(m_pevp) {
      m_pevp->DetachWindow();
      m_pevp = NULL;
    }

    m_pList->SetItemCountEx(0,VL_ADD_FLAGS);
    delete m_paPreCacheOffs; m_paPreCacheOffs = NULL;
    if(m_paPages) {
      delete m_paPages; m_paPages = NULL;
    }
    if(m_paPreCache) {
      delete m_paPreCache; m_paPreCache= NULL;
    }
    if(m_pPagePreCache) {
      delete m_pPagePreCache; m_pPagePreCache= NULL;
    }
    delete  m_pbyPageBuf; m_pbyPageBuf  = NULL;
  }
  return 0;//0-ok
}
//---------------------------------------
UINT CEventsListDlg::CheckAndPreloadPages(CEventsPageArray& aPages, UINT* panDestIndex) {
  ASSERT(panDestIndex);
  if(!panDestIndex || m_bPausePreloader/* || m_bPausedPreloader*/)
    return 0;

  ULONG nPages = aPages.GetPagesNum();
  int nEvAddFirst=0,nEvAddLast=0;
  ASSERT(nPages>0);

  BOOL bRet = FALSE;

  ULONG nLPInd = m_paPages->GetLastPageIndex();
  ULONG nLPOffs= nLPInd*m_nPageDataSize;

  ULONG nLastPageOffset = m_nLastPageOffset;
//  ULONG nLastPageIndex  = nLastPageOffset/GetPageSize();

  ULONG nFirstOffset      = GetFirstOffset();
  ULONG nFirstPageOffset  = GetFirstPageOffset();
//  ULONG nFirstPageInd     = m_nFirstPageInd;
  WORD  wLogFirstOnPageOffs= static_cast<WORD>(nFirstOffset - nFirstPageOffset);

  WORD  wFirstOnPageOffs=0xFFFF;
  UINT  nCacheInd   = 0;

  ULONG nGuessPageNum  = ULONG_MAX;

  ULONG nOffs  = nLPOffs;
  ULONG nInd   = nLPInd;
  ULONG nPageNumber = 0;
  BOOL  bContinue = TRUE;

  for(UINT i=0;i<nPages;++i) {
    CEventsPage& page = aPages.m_paEP[i];
    page.SetLoaded(FALSE);
    page.SetIdent(FALSE);
  }
  if(m_bLoadLeft) {
    do {
      if(FALSE == m_paPages->m_paEP[nInd].IsIdent()) {//load modified page (last page)
        if(nOffs==nFirstPageOffset) {//set only on first page in log
          wFirstOnPageOffs = wLogFirstOnPageOffs;
        }
        else wFirstOnPageOffs = 0xFFFF;
        if(YEventsProtocol::SUCCESS == m_pevp->GetPage(nOffs,m_pbyPageBuf,TRUE)) {
          if(YEventsProtocol::SUCCESS == m_pevp->ValidateHeader(m_pbyPageBuf,&nPageNumber)) {
            if(m__nCachedPageInd==ULONG_MAX) {
              m__nCachedPageInd = nInd;
              m__nCachedPageNum = nPageNumber;
            }
            if(m_paPages->m_paEP[nInd].IsLoaded()) {
              nGuessPageNum = m_paPages->m_paEP[nInd].GetNumber();
            }
            else {
              if(nInd==m_paPages->GetLastPageIndex()) {
                nGuessPageNum = nPageNumber;
              }
              else {
                nGuessPageNum = --m__nCachedPageNum;
              }
            }
            if(nPageNumber==nGuessPageNum) {
              CEventsPage& page = m_pPagePreCache->m_paEP[0];
              page.SetData(m_pbyPageBuf);
              page.SetFirstEvOffset(wFirstOnPageOffs);
              page.SetNumber(nPageNumber);
              page.SetLoaded(TRUE);
              page.SetIdent(TRUE);
              aPages.LoadPage(&page,nCacheInd,&m_EventsFilter,nEvAddFirst,nEvAddLast);
              panDestIndex[nCacheInd] = nInd;
              ++nCacheInd;
              bRet = TRUE;
              if(nFirstPageOffset==nOffs) {
                m__nCachedPageInd = ULONG_MAX;
                m__nCachedPageNum = ULONG_MAX;
                bContinue = FALSE;
                m_bLoadLeft = FALSE;
                break;
              }
            }
            else {
//              ASSERT(!"Overflow of a log. It is necessary reload all anew");//TODO:OnAttach(...)
              m__nCachedPageInd = ULONG_MAX;
              m__nCachedPageNum = ULONG_MAX;
              m_bLoadLeft = FALSE;
              bContinue = FALSE;
            }
          }
        }
        else {
          ASSERT(!"error loading?");
          break;
        }
      }
      nInd   = m_paPages->GetPrevPageIndex(nInd);
      nOffs  = nInd * GetPageSize();
    } while(nCacheInd<PRECACHE_PAGES && bContinue);
  }
  else {
    ULONG nFPOffs = m_paPages->GetFirstPageIndex() * GetPageSize();
    if(m__nCachedPageInd==ULONG_MAX) {
      m__nCachedPageInd = nInd;
      if(m_paPages->m_paEP[nInd].IsLoaded())
        m__nCachedPageNum = m_paPages->m_paEP[nInd].GetNumber();
      else {
        ASSERT(!"page not loaded???");
        if(YEventsProtocol::SUCCESS == m_pevp->GetPage(nOffs,m_pbyPageBuf,TRUE))
          if(YEventsProtocol::SUCCESS == m_pevp->ValidateHeader(m_pbyPageBuf,&nPageNumber))
            m__nCachedPageNum = nPageNumber;
      }
    }
    do {
      if(FALSE == m_paPages->m_paEP[nInd].IsIdent()) {//load modified page (last page)
        if(nLPOffs==nFPOffs && nOffs==nFPOffs) {
          wFirstOnPageOffs = wLogFirstOnPageOffs;
        }
        else wFirstOnPageOffs = 0xFFFF;
        if(YEventsProtocol::SUCCESS == m_pevp->GetPage(nOffs,m_pbyPageBuf,TRUE)) {
          if(YEventsProtocol::SUCCESS == m_pevp->ValidateHeader(m_pbyPageBuf,&nPageNumber)) {
            if(nLPOffs==nOffs)
              nGuessPageNum = m_paPages->m_paEP[nInd].GetNumber();
            else
              nGuessPageNum = ++m__nCachedPageNum;
            if(nPageNumber==nGuessPageNum) {
              CEventsPage& page = m_pPagePreCache->m_paEP[0];
              page.SetData(m_pbyPageBuf);
              page.SetFirstEvOffset(wFirstOnPageOffs);
              page.SetNumber(nPageNumber);
              page.SetLoaded(TRUE);
              page.SetIdent(TRUE);
              aPages.LoadPage(&page,nCacheInd,&m_EventsFilter,nEvAddFirst,nEvAddLast);
              panDestIndex[nCacheInd] = nInd;
              ++nCacheInd;
              bRet = TRUE;
              if(nLastPageOffset==nOffs) {
                bContinue = FALSE;
                break;
              }
            }
            else {
              ASSERT(!"Overflow of a log. It is necessary reload all anew");//TODO:OnAttach(...)
              bContinue = FALSE;
            }
          }
        }
        else {
          ASSERT(!"error loading?");
          break;
        }
      }
      nInd   = m_paPages->GetNextPageIndex(nInd);
      nOffs  = nInd * GetPageSize();
    } while(nCacheInd<PRECACHE_PAGES && bContinue);
  }
  return bRet?nCacheInd:0;
}
//---------------------------------------
BOOL CEventsListDlg::IsNeedPreLoadPages() const {
  return (m_nLastPageIndex != m_paPages->GetLastPageIndex() ||
    !(m_paPages->m_paEP[m_paPages->GetLastPageIndex()].IsIdent()) ||
    m_bLoadLeft);
}
//---------------------------------------
int CEventsListDlg::AdjustColumnSize() {//AY
  CRect rc; GetClientRect(&rc);
  m_pList->SetColumnWidth(0,rc.Width()-4-::GetSystemMetrics(SM_CXVSCROLL));
  return 0;
}
//---------------------------------------
// int CEventsListDlg::SetViewMode(int nMode) {// 0-full,1-short //AY
//   int nOldMode = m_nViewMode;
//   m_nViewMode = nMode;
//   return nOldMode;
// }
//---------------------------------------
// int CEventsListDlg::GetViewMode() const {// 0-full,1-short //AY
//   return m_nViewMode;
// }
//---------------------------------------
void CEventsListDlg::SetFilter(const CEventsFilter& filter) {
  m_EventsFilter  = filter;
  if(IsAttachedLog()) {
    m_bNeedReset  = TRUE;
    m_bPausePreloader  = TRUE;
    BOOL bContinueWait = TRUE;
    do {
      switch(WaitForSingleObject(m_hNeedLoadEvent,0))
      {
      case WAIT_OBJECT_0:
        Sleep(50);
        bContinueWait = TRUE;
        break;
      case WAIT_FAILED:
        ASSERT(0);
      case WAIT_TIMEOUT:
        bContinueWait = FALSE;
        break;
      default:
        ASSERT(0);
        bContinueWait = FALSE;
        break;
      }
    } while(bContinueWait&(!m_bNeedKillLoader));
    m_bPausePreloader = FALSE;
    ULONG nPages = m_paPreCache->GetPagesNum();
    for(ULONG i=0;i<nPages;++i) {
      CEventsPage& page = m_paPreCache->m_paEP[i];
      page.SetLoaded(FALSE);
      page.SetIdent(FALSE);
    }
    nPages = m_paPages->GetPagesNum();
    for(i=0;i<nPages;++i) {
      CEventsPage& page = m_paPages->m_paEP[i];
      page.SetLoaded(FALSE);
      page.SetIdent(FALSE);
    }
    m_paPages->ReInit();
    ReInit();
    //PostMessage(WM_LOADED_BUFFER); //post message for clear last waitable buffer
    CMessagesArbiter::CMessage message;
    message.m_hMesWnd = GetSafeHwnd();
    message.m_nMessage= WM_LOADED_BUFFER;
    message.m_bPostMode = FALSE;
    message.m_WParam  = NULL;
    message.m_LParam  = NULL;
    message.SetData(NULL,CMessagesArbiter::CMessage::dataNone);
    m_MesArb.DoPushMessage(&message);
  }
}
//-----------
BOOL CEventsListDlg::GetFilter(CEventsFilter* pfilter) {
  if(pfilter) {
    *pfilter = m_EventsFilter;
  }
  return pfilter?TRUE:FALSE;
}

BOOL CEventsListDlg::SetHeaderLinesCount(int nTextLines)
{
  ASSERT(nTextLines>0 && nTextLines < 3);
  if(nTextLines>0 || nTextLines < 3)
    m_nHeaderLines = nTextLines;
  else
    m_nHeaderLines = 1;
  if(m_pList)
    m_pList->SetHeaderLinesCount(m_nHeaderLines);
  return TRUE;
}

void CEventsListDlg::ShowLogStatus(BOOL bShow) {
  m_bShowLogStatus = bShow;
  if(m_pList) {
    RemoveAnchor(m_pList->GetDlgCtrlID());
    WINDOWPLACEMENT wndplList = {sizeof(wndplList)}; m_pList->GetWindowPlacement(&wndplList);
    RECT& rcList = wndplList.rcNormalPosition;
    WINDOWPLACEMENT wndplLogStatus = {sizeof(wndplLogStatus)}; m_pLogStatus->GetWindowPlacement(&wndplLogStatus);
    RECT& rcLogStatus = wndplLogStatus.rcNormalPosition;// ------------------
    if(bShow)                                           // | CEventsListCtrl|
      rcList.bottom = rcLogStatus.top-1;                // |                |
    else                                                // |----------------|
      rcList.bottom = rcLogStatus.bottom;               // | event statistic|
    m_pLogStatus->ShowWindow(bShow?SW_SHOW:SW_HIDE);    // ------------------
    m_pList->SetWindowPlacement(&wndplList);
    AddAnchor(m_pList->GetDlgCtrlID(),TOP_LEFT,BOTTOM_RIGHT);
  }
}
//---------------------------------------
void CEventsListDlg::SetDetailImages(BOOL bShow) {
  m_bDetailImages = bShow;
  //TODO!
}
//-----------
BOOL CEventsListDlg::GetDetailImages() const {
  return m_bDetailImages;
}
//---------------------------------------
void CEventsListDlg::OnSize(UINT nType, int cx, int cy) {
//   if(m_pList && m_pList->m_hWnd!=NULL) {
//     WINDOWPLACEMENT wndpl = {sizeof(wndpl)}; GetWindowPlacement(&wndpl);
//     RECT& rc = wndpl.rcNormalPosition;
//     GetClientRect(&rc);
//     int cxvs = 0;//GetSystemMetrics (SM_CXVSCROLL); //Get the system metrics - VERT
//     int cyvs = 0;//GetSystemMetrics (SM_CYVSCROLL); //Get the system metrics - HORZ
//
//     m_pList->SetWindowPlacement(&wndpl);
//     if(IsShowLogStatus()) {
//
//     }
////    m_pList->GetClientRect(&rc);
//  }
  CParent::OnSize(nType, cx, cy);
}
//---------------------------------------
void CEventsListDlg::OnTimer(UINT nIDEvent)
{
  if(nIDEvent) {
    int nItems = m_pList->GetItemCount();
    CString  sz;
    #ifdef DEBUG_DETAIL_STATUS
    sz.Format(_T("Events: %7d "),nItems);
    #else
    sz.Format(_T("Events: %7d "),nItems);
    #endif
    SetStatusText(sz);
  }
  CEmptyAnyDialog<CResizableDialog>/*CParent*/::OnTimer(nIDEvent);
}
//---------------------------------------
int CEventsListDlg::LoadPage(CEventsPage& page, UINT nDestIndex) {
  ASSERT(m_paPages!=NULL);
  int nRet = -1;
  if(m_paPages) {
    ASSERT(nDestIndex<m_paPages->GetPagesNum());
    if(nDestIndex<m_paPages->GetPagesNum()) {
      page.SetLoaded(TRUE);
      page.SetIdent(TRUE);

      int nBottomVisible = m_pList->GetTopIndex() + m_pList->GetCountPerPage();
      int nSelectedItem= m_pList->GetNextItem(-1, LVNI_SELECTED);
      if(nSelectedItem!=-1) {
        m_pList->SetItemState(nSelectedItem, 0, LVIS_SELECTED|LVIS_FOCUSED);
      }
      BOOL bLastVisible = (static_cast<ULONG>(nBottomVisible) >= m_paPages->GetEventsCount());

      int nEvAddFirst, nEvAddLast;
      nRet = (m_paPages->LoadPage(&page, nDestIndex, NULL, nEvAddFirst, nEvAddLast) == TRUE)?0:-1;
      m_pList->SetItemCountEx(m_paPages->GetEventsCount(),VL_ADD_FLAGS);
      if(nSelectedItem!=-1) //select items if needed
        m_pList->SetItemState(nSelectedItem+nEvAddFirst, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
      if(bLastVisible) {// list to last item if needed
        m_pList->EnsureVisible(m_paPages->GetEventsCount()-1,FALSE);
      }
      else {
        int nItemToScrol = nBottomVisible+nEvAddFirst-1;
        m_pList->EnsureVisible(nItemToScrol>0?nItemToScrol:0,FALSE);
      }
     #ifdef DEBUG_EL
      ULONG nEvents = 0;
      for(ULONG nPage=0;nPage<m_paPages->GetPagesNum();++nPage) {
        if(m_paPages->m_paEP[nPage].IsLoaded())
          nEvents += m_paPages->m_paEP[nPage].GetNumEvents();
      }
      if(nEvents != m_paPages->GetEventsCount()) {
        ASSERT(0);
      }
      int nLPI = m_paPages->GetLastPageIndex();
      int nFPI = m_paPages->GetFirstPageIndex();
      //ASSERT(!(nLPI==(nFPI-1)));
      BOOL bRun1 = (nFPI==nLPI);
      int nItm1 = m_paPages->GetEventsCount();
      for(int iPage1=nLPI;iPage1!=nFPI || bRun1;) {
        nItm1 -= m_paPages->m_paEP[iPage1].GetNumEvents();
        ASSERT(nItm1>=0);
        if(bRun1)
          break;
        iPage1 = m_paPages->GetPrevPageIndex(iPage1);
        if(iPage1==nFPI)
          bRun1=TRUE;
      }
     #endif //DEBUG_EL

    } else
      ASSERT(!"Page index out of range!");
  }
  return nRet;
}
//---------------------------------------
#include "J:\VR\VR_TOOLS\SRSLogView\resource.h"
HICON CEventsListDlg::CreateImage(HICON hIconSource, int sx, int sy, int nTextMask, BOOL bDetailsShow) {
  HICON   hIcon = NULL;
  CFont   fontWhite;
  CFont   fontBlack;
  try {
    HDC hMainDC = ::GetDC(NULL);
    HDC hTempDC = ::CreateCompatibleDC(hMainDC);
    HBITMAP hTempBitmap = ::CreateCompatibleBitmap(hMainDC,sx,sy);
    HBITMAP hOldBitmap  = (HBITMAP)::SelectObject(hTempDC,hTempBitmap);
    HBRUSH hBrush       = ::CreateSolidBrush(RGB(255,255,255));
    ::FillRect(hTempDC,CRect(0,0,sx,sy), hBrush);

    CImageList tmpIL;
    tmpIL.Create(32,32,ILC_COLOR16|ILC_MASK,0,1);
    tmpIL.SetImageCount(1);
    COLORREF crBack = ::GetSysColor(COLOR_WINDOW);
    tmpIL.Replace(0,hIconSource);

    ::DrawIconEx(hTempDC,0,0,tmpIL.ExtractIcon(0),sx,sy,0,NULL,DI_NORMAL);
     fontWhite.CreateFont(10,0,0,0,FW_NORMAL,FALSE, FALSE,
                          FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
                          CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH, ResourceFont("Arial"));
     fontBlack.CreateFont(10,0,0,0,FW_NORMAL,FALSE, FALSE,
                          FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
                          CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH, ResourceFont("Arial"));
     ::SelectObject(hTempDC,fontWhite);
     char buf[2];
     ASSERT(nTextMask>=0 && nTextMask<10);
     if(bDetailsShow) {
       itoa(nTextMask,buf,10);
       ::SetBkMode(hTempDC,TRANSPARENT);
       ::SetTextColor(hTempDC,RGB(255,255,255));
       ::TextOutA(hTempDC, 0-1, sy/2,buf, 1);
       ::TextOutA(hTempDC, 0+1, sy/2,buf, 1);
       ::TextOutA(hTempDC, 0, sy/2-1,buf, 1);
       ::TextOutA(hTempDC, 0, sy/2+1,buf, 1);
       ::SelectObject(hTempDC,fontBlack);
       ::SetTextColor(hTempDC,COLORREF(COLOR_WINDOWTEXT));
       ::TextOutA(hTempDC, 0, sy/2,buf, 1);
     }
     ICONINFO info={TRUE, 0, 0, hTempBitmap, hTempBitmap};
     hIcon = ::CreateIconIndirect(&info);
     fontBlack.DeleteObject();
     fontWhite.DeleteObject();
    return  hIcon;
  }
  catch(CException*) {
  }
  return  NULL;
}
//-----------
void  CEventsListDlg::DestroyImage(HICON  hIcon) {
  if(hIcon) {
    DestroyIcon(hIcon);
    hIcon = NULL;
  }
}
//---------------------------------------
UINT CEventsListDlg::_BackgroundFinding(LPVOID lpVoid)
{
  CEventsListDlg* pDlg = ((CEventsListDlg*)lpVoid);
  ASSERT(pDlg);
  do {
    WaitForSingleObject(pDlg->m_hNeedFindEvent,INFINITE);
    pDlg->BackgroundFind();
  }while(!pDlg->m_bNeedKillLoader);
  return 0;
}
//---------------------------------------
UINT CEventsListDlg::BackgroundFind() {
  if(m_bNeedKillLoader)
    return 0;
  ResetEvent(m_hNeedFindEvent);
  m_bNeedStopFind = FALSE;
  m_nSerachStart = _FindEvent(m_pTextFindInfo,m_nSerachStart);
  PostMessage(WM_EL_FINISHED_FIND);
  return 0;
}
//---------------------------------------
UINT CEventsListDlg::_BackgroundPreLoading(LPVOID lpVoid)
{
  CEventsListDlg* pDlg = ((CEventsListDlg*)lpVoid);
  ASSERT(pDlg);
  do {
    WaitForSingleObject(pDlg->m_hNeedLoadEvent,INFINITE);
    pDlg->BackgroundPreload();
  }while(!pDlg->m_bNeedKillLoader);
  return 0;
}
//---------------------------------------
UINT CEventsListDlg::BackgroundPreload() {
  if(m_bNeedKillLoader)
    return 0;
  UINT nCacheFill=0; // 0..PRECACHE_PAGES
  if(IsNeedPreLoadPages() && (nCacheFill=CheckAndPreloadPages(*m_paPreCache,m_paPreCacheOffs))) {
    ResetEvent(m_hNeedLoadEvent);
    PostMessage(WM_LOADED_BUFFER_BETWTHREAD);
    if(m_bNeedKillLoader)
      return 0;
    if(nCacheFill!=PRECACHE_PAGES) {
      #ifdef DEBUG_EL
      Beep(1000,100);
      #endif
      #ifdef DEBUG_EL_TIME
      YTime tStopTime= YTimer::GetCurrentSpan();
      YTimeSpan ts  = tStopTime - g_tStartTime;
      TRACE("Log load time = %02d min :%02d sec:%03d ms",ts.GetMinutes(),ts.GetSeconds(),ts.GetMilliseconds());
      #endif
      Sleep(ID_TIMER_CHECKLOAD_EL);
    }
  }
  else {
    if(m_bPausePreloader) {
      ResetEvent(m_hNeedLoadEvent);
      m_bPausePreloader  = FALSE;
      return  0;
    }
    Sleep(ID_TIMER_CHECKLOAD_EL);
  }
  return 0;
}
//---------------------------------------
void CEventsListDlg::ReInit() {
  m_bLoadLeft       = TRUE;

  m__nCachedPageNum = ULONG_MAX;
  m__nCachedPageInd = ULONG_MAX;

  m_pList->SetItemCountEx(0,VL_ADD_FLAGS);
}
//---------------------------------------
void CEventsListDlg::InitForPreloader() {
  ULONG nLPOffs  = m_pevp->m_nWritePageOffset & ~(GetPageSize()-1);
  ULONG nLPInd   = nLPOffs / GetPageSize();

  m_nLastPageOffset = nLPOffs;
  m_nLastPageIndex  = nLPInd;
}
//---------------------------------------
BOOL CEventsListDlg::GetEventImage(ULONG nIndex, int nBufSize, LPTSTR lpszText, int* pnIcon) {
  ASSERT(pnIcon);
  if(_FindAndLoadEvent(nIndex)) {
    int nClassIcon=YEvent::classERROR;
    int nLevel=0;

    UINT n = 8;
    //a * b * n
    n = n<<1;

    #ifdef DISABLE_STATE_RATE
    if(NULL != m_pcachedEv->GetInfo(lpszText,nBufSize,&nLevel,&nClassIcon)) {
      switch(nClassIcon) {
        case YEvent::classWARNING:
          *pnIcon  = ICON_STATE_WARNING;
        break;
        case YEvent::classERROR:
          *pnIcon  = ICON_STATE_ERROR;
        break;
        case YEvent::classINFO:
          *pnIcon  = ICON_STATE_INFO;
        break;
        default:
          #ifdef DEBUG_EL
          ASSERT(0);
          #endif //DEBUG_EL
          *pnIcon  = ICON_STATE_ERROR;
      }
      return TRUE;
    }
    #else
    if(NULL != m_pcachedEv->GetInfo(lpszText,nBufSize,&nLevel,&nClassIcon)) {
      switch(nClassIcon) {
      case YEvent::classWARNING:
        *pnIcon  = ICON_STATE_WARNING*(STATE_LEVELS_NUM)+nLevel;
        break;
      case YEvent::classERROR:
        *pnIcon  = ICON_STATE_ERROR*(STATE_LEVELS_NUM)+nLevel;
        break;
      case YEvent::classINFO:
        *pnIcon  = ICON_STATE_INFO*(STATE_LEVELS_NUM)+nLevel;
        break;
      default:
      #ifdef DEBUG_EL
              ASSERT(0);
      #endif //DEBUG_EL
        *pnIcon  = ICON_STATE_ERROR;
      }
      return TRUE;
    }
    #endif
  }
#ifdef DEBUG_EL
  ASSERT(0);
#endif //DEBUG_EL
  return FALSE;
}
//---------------------------------------
void CEventsListDlg::OnGetdispinfoEventslist(NMHDR* pNMHDR, LRESULT* pResult) {
  LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
  LV_ITEM* pItem= &(pDispInfo)->item;
  int nIndex= pItem->iItem;
  int nColumn= pItem->iSubItem;
  int nRetTextSize=0;
  TCHAR buf[STACK_LEN];
  if(pItem->mask & LVIF_DI_SETITEM )
    ASSERT(0);

  switch(nColumn) {
    case CO_TYPE:
      {
        int nImage  = ICON_STATE_ERROR;
        if(GetEventImage(nIndex,STACK_LEN,buf,&nImage))
          pItem->iImage = nImage;
        else pItem->iImage = ICON_STATE_ERROR;
      }
    break;
    case CO_DATE:
      {
        YTime tTime=YTime::INVALID();
        if(GetEventTime(nIndex,tTime))
          _tcscpy(pItem->pszText, tTime.FormatEx(_T("%d.%m.%Y")));
        else
          _tcscpy(pItem->pszText, _T("?"));
      }
      break;
    case CO_TIME:
      {
        YTime tTime=YTime::INVALID();
        if(GetEventTime(nIndex,tTime))
          _tcscpy(pItem->pszText, tTime.FormatEx(_T("%H:%M:%S")));
        else
          _tcscpy(pItem->pszText, _T("?"));
      }
      break;
    case CO_CHAN:
      if(GetEventChannel(nIndex,STACK_LEN,buf,nRetTextSize))
        _tcscpy(pItem->pszText, buf);
      else
        _tcscpy(pItem->pszText, _T(""));
      break;
    case CO_MESS:
      if(GetEventText(nIndex,STACK_LEN,buf,nRetTextSize)) {
        _tcscpy(pItem->pszText, buf);
      }
      else
        _tcscpy(pItem->pszText, _T("?"));
      break;

  }
  #if 0
    if (pItem->mask & LVIF_TEXT) {
      int nRetTextSize=0;
     #ifdef DEBUG_EL
      if(GetEventText(nIndex,STACK_LEN,buf,nRetTextSize)) {
        char buf2[STACK_LEN+100];
        strcpy(buf2,m_szEvNumText + buf);
        strcpy(pItem->pszText, buf2);
      }
      else {
        #ifdef DEBUG_EL
        ASSERT(0);
        #endif
        strcpy(pItem->pszText, "?");
      }
     #else
      if(GetEventText(nIndex,STACK_LEN,buf,nRetTextSize))
        _tcscpy(pItem->pszText, buf);
      else {
        //ASSERT(0);
        _tcscpy(pItem->pszText, _T("?"));
      }
     #endif //DEBUG_EL
    }
    if(pItem->mask&LVIF_IMAGE) {
      int nImage  = ICON_STATE_ERROR;
      if(GetEventImage(nIndex,STACK_LEN,buf,&nImage))
        pItem->iImage = nImage;
      else pItem->iImage = ICON_STATE_ERROR;
    }
  #endif //0
  *pResult = 0;
}
//---------------------------------------
// void CEventsListDlg::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult)
// {
//   NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
//   int iColumn = pNMListView->iSubItem;
//
// //   if(column_sort == clicked)
// //     bSortAscending = !bSortAscending;
// //   else
// //   {
// //     column_sort = clicked;
// //     bSortAscending = TRUE;
// //   }
// //
// //   qsort(array, count, sizeof(DATA*), SortFunc);
// //   SetItemCount(count);  //force redraw
// //
//   *pResult = 0;
// }
//---------------------------------------
/*void CEventsListDlg::OnOdfinditemEventslist(NMHDR* pNMHDR, LRESULT* pResult) {
   NMLVFINDITEM* pFindInfo = (NMLVFINDITEM*)pNMHDR;
   LVFINDINFO FindItem = pFindInfo->lvfi;
   int i = pFindInfo->iStart;
   if(FindItem.flags & LVFI_STRING) {
     CRect rect;
     m_pList->GetClientRect(&rect);
     rect.left = rect.right-60;
     rect.top  = rect.bottom-20;
     CMessageDlg dlg;
     dlg.ReCreate(rect,_T("wait..."),this);
     i = _FindEvent(&FindItem,i);
     dlg.ShowWindow(SW_HIDE);
     dlg.DestroyWindow();
   }
   m_pList->EnsureVisible(i,TRUE);
   m_pList->SetItemState(i, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
   *pResult = i;
} */
//-----------
int CEventsListDlg::_FindEvent(CFindInfo* pFindInfo, int nStart) {
  ASSERT(0 != pFindInfo->m_nDirection);
  ASSERT(0 != pFindInfo->m_dwFlags);
  ULONG iEvent = nStart;
  if(pFindInfo->m_dwFlags&CFindInfo::fndText) {//find text
    if(pFindInfo->m_dwOtherFlags & CFindInfo::fndPartial) { //find partial string from event
      TCHAR buf[STACK_LEN];
      int nRetTextSize;
      CString szTmp;
      if(pFindInfo->m_nDirection==CFindInfo::dirDOWN) {//DOWN search
        CString szFindText = pFindInfo->m_szText;
        int nFindTextSize = szFindText.GetLength();
        szFindText.MakeLower();
        while((++iEvent)<m_paPages->GetEventsCount()) {
          if(GetEventTextF(iEvent,STACK_LEN,buf,nRetTextSize)) {
            szTmp = buf;
            szTmp.MakeLower();
            if(-1!=szTmp.Find(szFindText))
              return iEvent;
            if(m_bNeedStopFind)
              break;
          }
        };
      }
      if(pFindInfo->m_nDirection==CFindInfo::dirUP) {//UP search
        CString szFindText = pFindInfo->m_szText;
        int nFindTextSize = szFindText.GetLength();
        szFindText.MakeLower();
        while((--iEvent)<m_paPages->GetEventsCount()) {
          if(GetEventTextF(iEvent,STACK_LEN,buf,nRetTextSize)) {
            szTmp = buf;
            szTmp.MakeLower();
            if(-1!=szTmp.Find(szFindText))
              return iEvent;
            if(m_bNeedStopFind)
              break;
          }
        };
      }
      return -1; //not Found
    }
    else { ////find full string from event

      TCHAR buf[STACK_LEN];
      int nRetTextSize;
      if(pFindInfo->m_nDirection==CFindInfo::dirDOWN) {//DOWN search
        CString szFindText = pFindInfo->m_szText;
        int nFindTextSize = szFindText.GetLength();
        while((++iEvent)<m_paPages->GetEventsCount()) {
          if(GetEventTextF(iEvent,STACK_LEN,buf,nRetTextSize)) {
            if(0==szFindText.Compare(buf))
              return iEvent;
            if(m_bNeedStopFind)
              break;
          }
        };
      }
      if(pFindInfo->m_nDirection==CFindInfo::dirUP) {//UP search
        CString szFindText = pFindInfo->m_szText;
        int nFindTextSize = szFindText.GetLength();
        while((--iEvent)<m_paPages->GetEventsCount()) {
          if(GetEventTextF(iEvent,STACK_LEN,buf,nRetTextSize)) {
            if(0==szFindText.Compare(buf))
              return iEvent;
            if(m_bNeedStopFind)
              break;
          }
        };
      }
    }
    return -1; //not Found
  }
  if(pFindInfo->m_dwFlags&CFindInfo::fndID) { ////find from event by ID
    if(pFindInfo->m_nDirection==CFindInfo::dirDOWN) {//DOWN search
      UINT nEvents = m_paPages->GetEventsCount();
      UINT nMessage = pFindInfo->m_nID;
      while((++iEvent)<nEvents) {
        UINT nMessageCur=0;
        if(GetEventIDF(iEvent,nMessageCur)) {
          if(nMessage==nMessageCur)
            return iEvent;
        }
        if(m_bNeedStopFind)
          break;
      };
    }
                                               ////find from event by ID
    if(pFindInfo->m_nDirection==CFindInfo::dirUP) {//UP search
      UINT nEvents = m_paPages->GetEventsCount();
      UINT nMessage = pFindInfo->m_nID;
      while((--iEvent)<nEvents) {
        UINT nMessageCur=0;
        if(GetEventIDF(iEvent,nMessageCur)) {
          if(nMessage==nMessageCur)
            return iEvent;
        }
        if(m_bNeedStopFind)
          break;
      };
    }
    return -1; //not Found
  }
  if(pFindInfo->m_dwFlags&CFindInfo::fndTime) { ////find from event by TIME
    if(pFindInfo->m_nDirection==CFindInfo::dirUPDOWN) {  //UPDOWN search
      ULONG n = __FindEventByTime(pFindInfo->m_tTime,TRUE,nStart);
      return __FindEventByTime(pFindInfo->m_tTime,FALSE,n);
    }
    if(pFindInfo->m_nDirection==CFindInfo::dirDOWNUP) {  //DOWNUP search
      ULONG n = __FindEventByTime(pFindInfo->m_tTime,FALSE,nStart);
      return __FindEventByTime(pFindInfo->m_tTime,TRUE,n);
    }
    if(pFindInfo->m_nDirection==CFindInfo::dirDOWN) //DOWN search
      return  __FindEventByTime(pFindInfo->m_tTime,FALSE,nStart);
    if(pFindInfo->m_nDirection==CFindInfo::dirUP)   //UP search
      return  __FindEventByTime(pFindInfo->m_tTime,FALSE,nStart);
  }
  return -1; //not Found
}
//---------------------------------------
int CEventsListDlg::__FindEventByTime(YTime tFindTime, BOOL bFindUp, ULONG nStart) {
  ASSERT(nStart!=-1);
  if(bFindUp) { //UP
    ULONG  iEvent=nStart;
    ULONG  nEvents = m_paPages->GetEventsCount();
    YTime tTimeCur  = YTime::INVALID();
    int nStartItm  = nStart;
    while((--iEvent)<nEvents) {
      if(GetEventTimeF(iEvent,tTimeCur)) {
        if(tTimeCur<tFindTime)
          return nStartItm;
        nStartItm = iEvent;
      }
      if(m_bNeedStopFind)
        break;
    };
    return  nStartItm;
  }
  else { //DOWN
    ULONG  iEvent=nStart;
    ULONG  nEvents = m_paPages->GetEventsCount();
    YTime tTimeCur  = YTime::INVALID();
    int nStartItm  = nStart;
    while((++iEvent)<nEvents) {
      if(GetEventTimeF(iEvent,tTimeCur)) {
        if(tTimeCur>tFindTime)
          return nStartItm;
        if(m_bNeedStopFind)
          break;
        nStartItm = iEvent;
      }
    };
    return  nStartItm;
  }
}
//---------------------------------------
void CEventsListDlg::OnContextMenu(CWnd* pWnd, CPoint point) {
  if(pWnd==NULL)
    return;
  int nID = pWnd->GetDlgCtrlID();
  if(nID==ID_EVENTSLIST && m_pList->GetSelectedCount()>0) {
    UINT nMenuFlags=0;
    UINT nTmpID;
    CMenu menu;
    menu.CreatePopupMenu();
    nMenuFlags|=MF_STRING;
    int nSelectedItem= m_pList->GetNextItem(-1,LVNI_SELECTED);
    if(nSelectedItem!=-1) {
      //--search
      menu.AppendMenu(nMenuFlags,ID_MENU_SEARCH_UP,  _T("Search up\t(Ctrl+Up)"));
      menu.EnableMenuItem(ID_MENU_SEARCH_UP,MF_ENABLED);
      menu.AppendMenu(nMenuFlags,ID_MENU_SEARCH_DOWN,_T("Search down\t(Ctrl+Down)"));
      menu.EnableMenuItem(ID_MENU_SEARCH_DOWN,MF_ENABLED);
    }
    //--quick search
    if(nSelectedItem!=-1  && GetEventID(nSelectedItem,nTmpID)) {
      menu.AppendMenu(MF_SEPARATOR,NULL);
      menu.AppendMenu(nMenuFlags,ID_MENU_QUICKSEARCH_UP,  _T("Quick search up\t(Ctrl+Shift+Up)"));
      menu.EnableMenuItem(ID_MENU_QUICKSEARCH_UP,MF_ENABLED);
      menu.AppendMenu(nMenuFlags,ID_MENU_QUICKSEARCH_DOWN,_T("Quick search down\t(Ctrl+Shift+Down)"));
      menu.EnableMenuItem(ID_MENU_QUICKSEARCH_DOWN,MF_ENABLED);
    }
    //--go to time...
    menu.AppendMenu(MF_SEPARATOR,NULL);
    menu.AppendMenu(nMenuFlags,ID_MENU_GOTO_TIME,  _T("Go to time...\t(Ctrl+T)"));
    //--search text...
    menu.AppendMenu(MF_SEPARATOR,NULL);
    menu.AppendMenu(nMenuFlags,ID_MENU_SEARCHTEXT,        _T("Search text..."));
    BOOL bFindStrEmpty = m_pTextFindInfo->m_szText.IsEmpty();
    if(m_pTextFindInfo && !bFindStrEmpty) {
      menu.AppendMenu(nMenuFlags,ID_MENU_SEARCHTEXT_UP,     _T("Search text up"));
      menu.AppendMenu(nMenuFlags,ID_MENU_SEARCHTEXT_DOWN,   _T("Search text down"));
//      menu.EnableMenuItem(ID_MENU_SEARCHTEXT_UP,  bFindStrEmpty?MF_DISABLED:MF_ENABLED);
//      menu.EnableMenuItem(ID_MENU_SEARCHTEXT_DOWN,bFindStrEmpty?MF_DISABLED:MF_ENABLED);
    }
//    menu.EnableMenuItem(ID_MENU_QUICKSEARCH_UP,MF_ENABLED);
    //--filter dialog
    if(m_bEnableFilterDialog) {
      //separator
      menu.AppendMenu(MF_SEPARATOR,NULL);
      //filter...
      menu.AppendMenu(nMenuFlags,ID_MENU_SET_FILTER,_T("Filter..."));
      menu.EnableMenuItem(ID_MENU_SET_FILTER,MF_ENABLED);
    }
    //menu.AppendMenu(MF_SEPARATOR,NULL);
    menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, point.x, point.y, this);
  }
  else
    CParent::OnContextMenu(pWnd, point);
}
//-----------
void CEventsListDlg::OnMenuCommandRange(UINT nID) {
  ASSERT_VALID(this);
  switch(nID)
  {
  case ID_MENU_SEARCH_UP:
    SendMessage(WM_EL_FIND,CFindInfo::dirUP,    EL_FIND_TEXT);
    break;

  case ID_MENU_SEARCH_DOWN:
    SendMessage(WM_EL_FIND,CFindInfo::dirDOWN,  EL_FIND_TEXT);
    break;

  case ID_MENU_QUICKSEARCH_UP:
    SendMessage(WM_EL_FIND,CFindInfo::dirUP,    EL_FIND_ID);
    break;

  case ID_MENU_QUICKSEARCH_DOWN:
    SendMessage(WM_EL_FIND,CFindInfo::dirDOWN,  EL_FIND_ID);
    break;

  case ID_MENU_GOTO_TIME:
    SendMessage(WM_EL_FIND,CFindInfo::dirUPDOWN,EL_FIND_TIME);
    break;
  case ID_MENU_SEARCHTEXT:
    SendMessage(WM_EL_FIND,CFindInfo::dirNONE,EL_FIND_PARTTEXT);
    break;
  case ID_MENU_SEARCHTEXT_UP:
    SendMessage(WM_EL_FIND,CFindInfo::dirUP,EL_FIND_PARTTEXT);
    break;
  case ID_MENU_SEARCHTEXT_DOWN:
    SendMessage(WM_EL_FIND,CFindInfo::dirDOWN,EL_FIND_PARTTEXT);
    break;

  case ID_MENU_SET_FILTER:
    SendMessage(WM_EL_SET_FILTER,NULL,NULL);
    break;

  default:
    _ASSERTE(!"unhandled context menu!");
    break;
  }
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//=======================================
void CEventsListDlg::CMessageDlg::DoDataExchange(CDataExchange* pDX) {
  CParentDlg::DoDataExchange(pDX);
}
//----------------------------
/////////////////////////////////////////////////////////////////////////////
// CMessageDlg message handlers
BOOL CEventsListDlg::CMessageDlg::OnInitDialog() {
  CParentDlg::OnInitDialog();
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}
//----------------------------
int CEventsListDlg::CMessageDlg::ReCreate(CRect rectDlg, LPCTSTR lpszText, CWnd* pParent) {
  CRect rectTmp;
  delete m_pText;
  m_pText = NULL;
  if(m_bCreated)
    DestroyWindow();
  if(!Create(WS_OVERLAPPED/*WS_CHILD|DS_3DLOOK*/,/*WS_EX_WINDOWEDGE|*/WS_EX_TOPMOST,&rectDlg,pParent))
    return -1;
  GetClientRect(&rectTmp);
  CRect rectText;
  rectText.left = rectTmp.left+0;
  rectText.top  = rectTmp.top+0;
  rectText.bottom = rectTmp.bottom-0;
  rectText.right  = rectTmp.right/*-15*/;
  m_TextFont.DeleteObject();
  m_TextFont.CreatePointFont(90,ResourceFont(_T("Tahoma")));
  SetFont(&m_TextFont);
  m_pText = new CStatic;
  m_pText->Create(NULL,WS_CHILDWINDOW|WS_VISIBLE|SS_CENTER/*|SS_CENTERIMAGE*/,rectText,this);
  m_pText->SetWindowText(lpszText);
  m_pText->SetFont(&m_TextFont);
  //SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE );
  ShowWindow(SW_HIDE);
  SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0,SWP_NOMOVE|SWP_NOSIZE);
  m_bCreated  = TRUE;
  return 0;
}

void CEventsListDlg::CMessageDlg::Show(BOOL bShow) {
  ShowWindow(bShow?SW_SHOW:SW_SHOW);
}
//------------------------------------
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#include "YText.h"//04.01.2003 VEN
#define IDC_OK              1
#define IDC_CANCEL          2
#define IDC_TIMEDIALOG_DATE 1006
#define IDC_TIMEDIALOG_TIME 1007
/////////////////////////////////////////////////////////////////////////////
// CTimeDialog dialog
BEGIN_MESSAGE_MAP(CTimeDialog, CEmptyDialog)
  //{{AFX_MSG_MAP(CTimeDialog)
  //}}AFX_MSG_MAP
  ON_WM_CREATE()
  ON_BN_CLICKED(IDC_OK, OnOk)
END_MESSAGE_MAP()

CTimeDialog::CTimeDialog(YTime tDateTime, CWnd* pParent, LPCTSTR szOkCancel)
  :CParent()
{
//   CSimpleText stMessages(szMessages);
//   CText aszMessages(stMessages);
//   m_aszMessages.Copy(aszMessages);

  CSimpleText stButtonNames(szOkCancel);
  CText aszButtonNames(stButtonNames);
  m_aszButtonNames.Copy(aszButtonNames);

  m_pOK = NULL;
  m_pCancel = NULL;
  m_pFont = NULL;
  m_pParentWnd  = pParent;

  m_pDate = NULL;
  m_pTime = NULL;
  m_tDateTime = tDateTime;
}

CTimeDialog::~CTimeDialog()
{
  if(m_pOK != NULL)
    delete m_pOK;
  if(m_pCancel != NULL)
    delete m_pCancel;
  if(m_pFont != NULL)
    delete m_pFont;

}

int CTimeDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  //if (CEmptyDialog::OnCreate(lpCreateStruct) == -1)//AY 19.09.2003  if (CDialog::OnCreate(lpCreateStruct) == -1) //KSN 31.10.2003 rem
   if (CDialog::OnCreate(lpCreateStruct) == -1)
    return -1;

  CFont* pFont = m_pParentWnd->GetFont();
  LOGFONT lf;
  pFont->GetLogFont(&lf);
  LOGFONT LogFont;

  memset(&LogFont, 0x00, sizeof(LogFont));
  _tcscpy(LogFont.lfFaceName, lf.lfFaceName);
  LogFont.lfHeight = lf.lfHeight;
  _tcscpy(LogFont.lfFaceName,ResourceFont(LogFont.lfFaceName));//AY 23.12.2004

  m_pFont = new CFont;
  m_pFont->CreateFontIndirect(&LogFont);
  SetFont(m_pFont);

  //calculation of size of dialog in pixels
  HDC hDC;
  hDC = ::GetDC(NULL);
  int nx = ::GetDeviceCaps(hDC, HORZRES);

  int nMax = 0;
  int ny = 0;

  /*
  for (int i=0; i<m_nNum; i++) {
    CSize size;
    ::GetTextExtentPoint32(hDC, m_aszMessages[i],
                           m_aszMessages[i].GetLength(), &size);
    anx.Add(size.cx);
    if(size.cy > ny)
      ny = size.cy;

    if(size.cx > nMax)
      nMax = size.cx;
    if(size.cx > nx/2)
      m_bIsMultyLine = TRUE;
  }    */
  /*
  CRect rect(0, 0, 50, 70);
  rect.right = rect.right + nx/2;
    int nTemp = nMax*2/nx;
    nTemp = nTemp + 1;
    rect.bottom = rect.bottom + nTemp*ny*(m_nNum+1);// + 10*(nTemp*(nNum-1));
  */
  CRect rect(0, 0, 245, 170);
  CRect rectClient;
  GetClientRect(&rectClient);
  nx = rectClient.Width();
  ny = rectClient.Height();
  MoveWindow(rect.left, rect.top,
             rect.Width(), rect.Height());
  return 0;
}

BOOL CTimeDialog::OnInitDialog()
{
  //CEmptyDialog::OnInitDialog();//AY 19.09.2003//CDialog::OnInitDialog(); //KSN 31.10.2003 rem
  CDialog::OnInitDialog();

  CRect rectDlg;
  GetClientRect(&rectDlg);

  CRect rectControl;
  rectControl.left  = rectDlg.left  +20;
  rectControl.top   = rectDlg.top   +20;
  rectControl.right = rectControl.left+100;
  rectControl.bottom= rectControl.top +20;

  m_pDate = new CDateTimeCtrl;
  m_pDate->Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | DTS_SHORTDATEFORMAT,rectControl,this,IDC_TIMEDIALOG_DATE);
  m_pDate->SetTime(m_tDateTime);

  rectControl.left =  rectControl.right + 20;
  rectControl.right=  rectControl.left  + 80;

  m_pTime = new CDateTimeCtrl;
  m_pTime->Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | DTS_TIMEFORMAT,rectControl,this,IDC_TIMEDIALOG_TIME);
  m_pTime->SetTime(m_tDateTime);

  CRect rectOK(0, 0, 75, 23);
  CRect rectOKpos(rectDlg.right-20-rectOK.right*2-30, rectDlg.bottom-12-rectOK.bottom,0,0);
  rectOKpos.right = rectOKpos.left + rectOK.right;
  rectOKpos.bottom = rectOKpos.top + rectOK.bottom;

  if (m_pFont == NULL) {
    LOGFONT LogFont;
    memset(&LogFont, 0x00, sizeof(LogFont));
    _tcscpy(LogFont.lfFaceName,ResourceFont(_T("Arial")));//AY 23.12.2004
    LogFont.lfHeight = 12;
    m_pFont = new CFont;
    m_pFont->CreateFontIndirect(&LogFont);
  }
//  */
  m_pOK = new CButton;
  m_pOK->Create(m_aszButtonNames[0], WS_CHILD|WS_VISIBLE, rectOKpos, this, IDC_OK);
  m_pOK->SetFont(m_pFont);

  CRect rectCancelpos(rectDlg.right-20-rectOK.right, rectDlg.bottom-12-rectOK.bottom,0,0);
  rectCancelpos.right = rectCancelpos.left + rectOK.right;
  rectCancelpos.bottom = rectCancelpos.top + rectOK.bottom;
  m_pCancel = new CButton;
  m_pCancel->Create(m_aszButtonNames[1], WS_CHILD|WS_VISIBLE, rectCancelpos, this, IDC_CANCEL);
  m_pCancel->SetFont(m_pFont);

  return TRUE;
}

BOOL CTimeDialog::InitModal(DWORD style, DWORD dwExtendedStyle, LPCRECT lpRect, CWnd* pParentWnd)
{
  RECT rc = {0, 0, 0, 0};
  if(pParentWnd!=NULL)
    pParentWnd->GetWindowRect(&rc);
  if(lpRect==NULL)
    lpRect = &rc;
  m_DlgTmp.style = style;
  m_DlgTmp.dwExtendedStyle = dwExtendedStyle;
  m_DlgTmp.cdit = 0;
  m_DlgTmp.x = (WORD)lpRect->left;
  m_DlgTmp.y = (WORD)lpRect->top;
  m_DlgTmp.cx = lpRect->right-lpRect->left+1;
  m_DlgTmp.cy = lpRect->bottom-lpRect->top+1;

  WCHAR szBoxCaption[] = L"";

  LOGFONT LogFont;
  memset(&LogFont, 0x00, sizeof(LogFont));
  _tcscpy(LogFont.lfFaceName,ResourceFont(_T("Courier New")));
  LogFont.lfHeight = 8;

  //Prework for setting font in dialog...
#if defined(UNICODE) || defined (_UNICODE)
  int nFontNameLen = _tcslen(LogFont.lfFaceName)+1;
  WCHAR *szFontName = new WCHAR[nFontNameLen+1];
  _tcscpy(szFontName,LogFont.lfFaceName);
  nFontNameLen = (nFontNameLen) * sizeof(WCHAR);
#else //ANSI
  int cWC = MultiByteToWideChar(CP_ACP, 0, LogFont.lfFaceName, -1, NULL, 0);
  int nFontNameLen = cWC + 1;
  WCHAR *szFontName = new WCHAR[nFontNameLen];
  // Copy the string
  MultiByteToWideChar(CP_ACP, 0, LogFont.lfFaceName, -1, (LPWSTR) szFontName, cWC);
  szFontName[cWC] = 0;
  nFontNameLen = (cWC) * sizeof(WCHAR);
#endif
  int nBufferSize =  sizeof(DLGTEMPLATE) + (2 * sizeof(WORD)) /*menu and class*/+sizeof(szBoxCaption)
  + sizeof(WORD) /*fontsize*/ + nFontNameLen /*size of fontname*/;

  m_hLocal = LocalAlloc(LHND, nBufferSize);
  if (m_hLocal != NULL) {
    m_pBuffer = (BYTE*)LocalLock(m_hLocal);
    if (m_pBuffer == NULL) {
      LocalFree(m_hLocal);
      AfxMessageBox(_T("CDynDialogEx::DoModal() : LocalLock Failed"));
    }

    BYTE *pdest = m_pBuffer;
    // transfer DLGTEMPLATE structure to the buffer
    memcpy(pdest, &m_DlgTmp, sizeof(DLGTEMPLATE));  // DLGTemplate
    pdest += sizeof(DLGTEMPLATE);
    *(WORD*)pdest = 0;                  // no menu             -- WORD to say it is 0 bytes
    pdest += sizeof(WORD);                // Increment
    *(WORD*)(pdest + 1) = 0;              // use default window class -- WORD to say it is 0 bytes
    pdest += sizeof(WORD);                // Increment
    memcpy(pdest, szBoxCaption, sizeof(szBoxCaption));  // Caption
    pdest += sizeof(szBoxCaption);

    *(WORD*)pdest = 8;            // font size
    pdest += sizeof(WORD);
    memcpy(pdest, szFontName, nFontNameLen);    // font name
    pdest += nFontNameLen;

    ASSERT(pdest - m_pBuffer == nBufferSize); // just make sure we did not overrun the heap

    BOOL bRes = CDialog::InitModalIndirect((LPDLGTEMPLATE)m_pBuffer, pParentWnd);

    delete [] szFontName;
    if(bRes){
      m_isInitModalIndirect = TRUE;
      return TRUE;
    }else
      return FALSE;
  }else
    return FALSE;
}

void CTimeDialog::OnOk()
{
  UpdateData(FALSE);
  CTime tDate, tTime;
  DWORD dwRet = m_pDate->GetTime(tDate);
  dwRet = m_pTime->GetTime(tTime);
  m_tDateTime = YTime(tDate.GetYear(),tDate.GetMonth(),tDate.GetDay(),
                      tTime.GetHour(),tTime.GetMinute(),tTime.GetSecond());
  CParent::OnOK();
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// CEventsList
CEventsList::CEventsList() : m_pbmpView(NULL){
  m_rgbWindow = RGB(255,255,255);//*/GetSysColor(COLOR_WINDOW);
//  m_nRedraws  = 0;
  m_rectList  = CRect(0,0,0,0);
//  m_rectListWithoutScroolAndHeader = CRect(0,0,0,0);

  m_rectListHead  = CRect(0,0,0,0);
  m_rectClientArea= CRect(0,0,0,0);
  m_nSortColumn = -1;
}

CEventsList::~CEventsList() {
  delete m_pbmpView;
  m_pbmpView=NULL;
}

BEGIN_MESSAGE_MAP(CEventsList, CListCtrl)
  //{{AFX_MSG_MAP(CEventsList)
  ON_WM_PAINT()
  ON_WM_SIZE()
  ON_WM_ERASEBKGND()
  ON_WM_NCCALCSIZE()
  ON_WM_VSCROLL()
  ON_WM_KEYDOWN()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventsList message handlers
BOOL CEventsList::Create(DWORD dwStyle, DWORD dwStyleEx, RECT& rect, CWnd* pParent, UINT nID)
{
  CDialog* pParentDlg   = (CDialog*)pParent;
  BOOL bRet = CListCtrl::Create(WS_VISIBLE|LVS_REPORT|LVS_OWNERDATA, rect, pParentDlg, nID);
  if(bRet==FALSE)
    return FALSE;
  if(nID!=0xFFFF)   SetDlgCtrlID(nID);

  UINT nFlags = SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE;
  if(dwStyle  &WS_CLIPCHILDREN)     ModifyStyle(0,WS_CLIPCHILDREN,nFlags);
  if(dwStyle  &WS_CLIPSIBLINGS)     ModifyStyle(0,WS_CLIPSIBLINGS,nFlags);
  if(dwStyle  &WS_GROUP)            ModifyStyle(0,WS_GROUP,nFlags);

  if(dwStyle  &WS_TABSTOP)          ModifyStyle(0,WS_TABSTOP,nFlags);
  if(dwStyle  &WS_BORDER)           ModifyStyle(0,WS_BORDER,nFlags);
  if(dwStyle  &WS_THICKFRAME)       ModifyStyle(0,WS_THICKFRAME,nFlags);
  if(dwStyle  &WS_DLGFRAME)         ModifyStyle(0,WS_DLGFRAME,nFlags);
  if(dwStyle  &WS_VISIBLE)          ModifyStyle(0,WS_VISIBLE,nFlags);
  if(dwStyleEx&WS_EX_CLIENTEDGE)    ModifyStyleEx(0,WS_EX_CLIENTEDGE,nFlags);
  if(dwStyleEx&WS_EX_WINDOWEDGE)    ModifyStyleEx(0,WS_EX_WINDOWEDGE,nFlags);
  if(dwStyleEx&WS_EX_STATICEDGE)    ModifyStyleEx(0,WS_EX_STATICEDGE,nFlags);

  if(dwStyleEx&WS_EX_TRANSPARENT)   ModifyStyleEx(0,WS_EX_TRANSPARENT,nFlags);
  if(dwStyleEx&WS_EX_ACCEPTFILES)   ModifyStyleEx(0,WS_EX_ACCEPTFILES,nFlags);
  if(dwStyleEx&WS_EX_CONTROLPARENT) ModifyStyleEx(0,WS_EX_CONTROLPARENT,nFlags);
  if(dwStyleEx&WS_EX_TOOLWINDOW)    ModifyStyleEx(0,WS_EX_TOOLWINDOW,nFlags);
  if(dwStyleEx&WS_EX_TOPMOST)       ModifyStyleEx(0,WS_EX_TOPMOST,nFlags);
  if(dwStyle  &WS_DISABLED)         ModifyStyle(0,WS_DISABLED,nFlags);
  else                              ModifyStyle(WS_DISABLED,0,nFlags);

  ModifyStyle(0,LVS_SINGLESEL|LVS_SHOWSELALWAYS|LVS_NOSORTHEADER/*|LVS_SHAREIMAGELISTS*/);
  SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES/*|LVS_EX_INFOTIP*/);

//  ShowWindow(SW_SHOW);
  SendMessage(WM_SIZE,0,0);
  return TRUE;
}
//---------------------------------------
BOOL CEventsList::ReCreate(CWnd *pWnd)
{ ASSERT(0);
  WINDOWPLACEMENT wndpl = {sizeof(wndpl)}; pWnd->GetWindowPlacement(&wndpl);
  DWORD dwHelp          = pWnd->GetWindowContextHelpId();
  DWORD dwStyle         = pWnd->GetStyle();
  DWORD dwStyleEx       = pWnd->GetExStyle();
  HICON hIcon           = pWnd->GetIcon(FALSE);
  int   nID             = pWnd->GetDlgCtrlID();
  CString szText;         pWnd->GetWindowText(szText);
  CDialog* pParentDlg   = (CDialog*)pWnd->GetParent();
  pWnd->DestroyWindow();

  BOOL bRet = CListCtrl::Create(WS_VISIBLE|LVS_REPORT|LVS_OWNERDATA, wndpl.rcNormalPosition,pParentDlg,nID);
  if(bRet==FALSE)
    return FALSE;
  if(nID!=0xFFFF)                   SetDlgCtrlID(nID);
  if(!szText.IsEmpty())             SetWindowText(szText);
  if(hIcon!=NULL)                   SetIcon(hIcon,TRUE);
  if(dwHelp!=0)                     SetWindowContextHelpId(dwHelp);

  UINT nFlags = SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE;
  if(dwStyle  &WS_CLIPCHILDREN)     ModifyStyle(0,WS_CLIPCHILDREN,nFlags);
  if(dwStyle  &WS_CLIPSIBLINGS)     ModifyStyle(0,WS_CLIPSIBLINGS,nFlags);
  if(dwStyle  &WS_GROUP)            ModifyStyle(0,WS_GROUP,nFlags);

  if(dwStyle  &WS_TABSTOP)          ModifyStyle(0,WS_TABSTOP,nFlags);
  if(dwStyle  &WS_BORDER)           ModifyStyle(0,WS_BORDER,nFlags);
  if(dwStyle  &WS_THICKFRAME)       ModifyStyle(0,WS_THICKFRAME,nFlags);
  if(dwStyle  &WS_DLGFRAME)         ModifyStyle(0,WS_DLGFRAME,nFlags);
  if(dwStyleEx&WS_EX_CLIENTEDGE)    ModifyStyleEx(0,WS_EX_CLIENTEDGE,nFlags);
  if(dwStyleEx&WS_EX_WINDOWEDGE)    ModifyStyleEx(0,WS_EX_WINDOWEDGE,nFlags);
  if(dwStyleEx&WS_EX_STATICEDGE)    ModifyStyleEx(0,WS_EX_STATICEDGE,nFlags);

  if(dwStyleEx&WS_EX_TRANSPARENT)   ModifyStyleEx(0,WS_EX_TRANSPARENT,nFlags);
  if(dwStyleEx&WS_EX_ACCEPTFILES)   ModifyStyleEx(0,WS_EX_ACCEPTFILES,nFlags);
  if(dwStyleEx&WS_EX_CONTROLPARENT) ModifyStyleEx(0,WS_EX_CONTROLPARENT,nFlags);
  if(dwStyleEx&WS_EX_TOOLWINDOW)    ModifyStyleEx(0,WS_EX_TOOLWINDOW,nFlags);
  if(dwStyleEx&WS_EX_TOPMOST)       ModifyStyleEx(0,WS_EX_TOPMOST,nFlags);
  if(dwStyle  &WS_DISABLED)         ModifyStyle(0,WS_DISABLED,nFlags);
  else                              ModifyStyle(WS_DISABLED,0,nFlags);

  SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_SUBITEMIMAGES|LVS_EX_ONECLICKACTIVATE);
  ModifyStyle(0,LVS_NOSORTHEADER|LVS_SHOWSELALWAYS|LVS_REPORT);

  if(dwStyle  &WS_VISIBLE)
    wndpl.showCmd = SW_SHOW;
  else
    wndpl.showCmd = SW_HIDE;
  SetWindowPlacement(&wndpl);
  return TRUE;
}
//---------------------------------------
void CEventsList::OnPaint() {
  CPaintDC  PaintDC(this);
  PaintDC.ExcludeClipRect(&m_rectListHead);
  CMemDC dc(&PaintDC, &m_pbmpView, m_rgbWindow);
  DefWindowProc(WM_PAINT, (WPARAM)dc.m_hDC, (LPARAM)0);
}
//---------------------------------------
BOOL CEventsList::OnEraseBkgnd(CDC* /* pDC*/) {
  return TRUE;
}
//---------------------------------------
void CEventsList::OnSize(UINT nType, int cx, int cy) {
  CListCtrl::OnSize(nType, cx, cy);
  if(m_hWnd && (GetStyle() & WS_VISIBLE)) {
    GetDlgItem(0)->GetWindowRect(&m_rectListHead);
    ScreenToClient(&m_rectListHead);
    //GetClientRect(&m_rectList);
    //GetDlgItem(1)->GetClientRect(&m_rectList);
  }
}
//---------------------------------------
int CEventsList::GetLastVisibleItem() const {
  int nItems = GetItemCount();
  if(nItems==0)
    return -1;
  int nTop   = GetTopIndex();
  int nCountPerPage = GetCountPerPage();
  if(nTop+nCountPerPage > nItems)
    return nItems-1;
  return nTop+nCountPerPage-1;
}
//---------------------------------------
int CEventsList::GetClientRectWithoutScrolBar(CRect& Rect) {
  Rect = m_rectClientArea;
  return 0;
}
//---------------------------------------
BOOL CEventsList::SetHeaderLinesCount(int nTextLines)
{
  ASSERT(nTextLines>0 && nTextLines<4);
  if(nTextLines<1 || nTextLines>3)
    nTextLines=1;

  m_NewHeaderFont.DeleteObject();

  m_NewHeaderFont.CreatePointFont(nTextLines*80,ResourceFont(_T("Arial")));//AY 26.11.2010 OLD "Arial Cyr"
  CHeaderCtrl* pHeader = NULL;
  pHeader=GetHeaderCtrl();
  if(pHeader==NULL)
    return FALSE;
  if(m_HeaderCtrl.GetSafeHwnd() == NULL)
    //m_HeaderCtrl.UnsubclassWindow();
    VERIFY(m_HeaderCtrl.SubclassWindow(pHeader->m_hWnd));
  //A BIGGER FONT MAKES THE CONTROL BIGGER
  m_HeaderCtrl.SetFont(&m_NewHeaderFont);
  HDITEM hdItem;
  hdItem.mask = HDI_FORMAT;
  for(int i=0; i < m_HeaderCtrl.GetItemCount(); ++i)
  {
    m_HeaderCtrl.GetItem(i,&hdItem);
    hdItem.fmt|= HDF_OWNERDRAW;
    m_HeaderCtrl.SetItem(i,&hdItem);
  }
  CRect rc;
  GetWindowRect( &rc );
  WINDOWPOS wp;
  wp.hwnd = m_hWnd;
  wp.cx = rc.Width();
  wp.cy = rc.Height();
  wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
  SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp );
  return TRUE;
}
//---------------------------------------
void CEventsList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
  switch (nSBCode)
  {
  case SB_PAGEDOWN:
  case SB_PAGEUP:
  case SB_LINEDOWN:
  case SB_LINEUP:
    // Don't update window if paging up or down. It looks
    // terrible!
//    LockWindowUpdate();
    CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
//    UnlockWindowUpdate();
    break;
  default:
    CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
    break;
  }
}
//---------------------------------------
void CEventsList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
  const UINT ENHANCEDKEY = 0x0100;
  const UINT PAGEUPKEY   = 0x21;
  const UINT PAGEDNKEY   = 0x22;
  // Handle enhanced keys since OnChar doesn't seem to get
  // them...
  if (nFlags & ENHANCEDKEY)
  {
    // Don't update window if paging up or down. It looks
    // terrible!
    switch (nChar)
    {
    case PAGEUPKEY:
      OnVScroll(SB_PAGEUP, 0, 0);
      return;

    case PAGEDNKEY:
      OnVScroll(SB_PAGEDOWN, 0, 0);
      return;
    }
  }
  if(GetKeyState(VK_CONTROL)<0 && (nChar=='F')) {
    GetParent()->SendMessage(WM_EL_FIND,
      0,
      EL_FIND_PARTTEXT);
    return;
  }

  if(GetKeyState(VK_CONTROL)<0 && GetKeyState(VK_MENU)<0 && (nChar==VK_UP || nChar==VK_DOWN)) {
    GetParent()->SendMessage(WM_EL_FIND,
      nChar==VK_UP?CFindInfo::dirUP:CFindInfo::dirDOWN,
      EL_FIND_PARTTEXT);
    return;
  }

  if(GetKeyState(VK_CONTROL)<0 && GetKeyState(VK_SHIFT)<0 && (nChar==VK_UP || nChar==VK_DOWN)) {
    GetParent()->SendMessage(WM_EL_FIND,
                             nChar==VK_UP?CFindInfo::dirUP:CFindInfo::dirDOWN,
                             EL_FIND_ID);
    return;
  }
  if(GetKeyState(VK_CONTROL)<0 && (nChar==VK_UP || nChar==VK_DOWN)) {
    GetParent()->SendMessage(WM_EL_FIND,
                             nChar==VK_UP?CFindInfo::dirUP:CFindInfo::dirDOWN,
                             EL_FIND_TEXT);
    return;
  }
  if(GetKeyState(VK_CONTROL)<0 && (nChar=='T')) {
    GetParent()->SendMessage(WM_EL_FIND,
                             CFindInfo::dirUPDOWN,
                             EL_FIND_TIME);
    return;
  }
  CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CEventsList::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) {
//  Beep(1000,3);
  CListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);
  m_rectClientArea = lpncsp->rgrc[0];
  GetParent()->PostMessage(WM_LIST_CH_CLIENTRECT,0,0);
}

//////////////////////////////////////////////////////////////////////
// CMessagesArbiter Class
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMessagesArbiter::CMessagesArbiter() : m_SingleLock(&m_csQueue) {

}

void CMessagesArbiter::DoPushMessage(CMessage* pMessage) {
  m_cs.Lock();
  m_messages.Add(*pMessage);
  TryPopMessage();
  m_cs.Unlock();
}

void CMessagesArbiter::_PopMessage() {
  TRACE("");
  if(m_messages.GetSize()>0) {
    _DoStartProcessing();
    CMessage& message = m_messages.ElementAt(0);
    if(message.m_bPostMode)
      PostMessage(message.m_hMesWnd,message.m_nMessage,message.m_WParam,message.m_LParam);
    else
      SendMessage(message.m_hMesWnd,message.m_nMessage,message.m_WParam,message.m_LParam);
  }
}

void CMessagesArbiter::_DoStartProcessing() {
  m_SingleLock.Lock();
}

void CMessagesArbiter::_DoEndProcessing() {
  if(m_messages.GetSize()>0)
    m_messages.RemoveAt(0);
  m_SingleLock.Unlock();
  TryPopMessage();
}

void CMessagesArbiter::TryPopMessage() {
  if(!m_SingleLock.IsLocked())
    _PopMessage();
}

void CMessagesArbiter::DoEndProcessing() {
  _DoEndProcessing();
}



void CEventsListDlg::OnMove(int x, int y)
{
  CEmptyAnyDialog<CResizableDialog>/*CParent*/::OnMove(x, y);
//   Beep(500,3);
  // TODO: Add your message handler code here

}
