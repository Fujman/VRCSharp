// EventsFilterDlg.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include <afxpriv.h>
#include "EventsFilterDlg.h"

#include "EVENTLOG/CONTROLS/EventsFilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int _FlagsToNum(DWORD dwSource) {
  int nBits=0;
  if(dwSource>0) {
    nBits=0;
    do {
      ++nBits;
    }while(dwSource>>=1!=0);
    --nBits;
  }
  ASSERT(nBits>=0&&nBits<8);
  return nBits;
}
/////////////////////////////////////////////////////////////////////////////
// CEventsFilterDlg dialog
IMPLEMENT_DYNAMIC(CEventsFilterDlg, CDialogBar)

CEventsFilterDlg::CEventsFilterDlg()
/*	: CDialogBar(CEventsFilterDlg::IDD, pParent)*/
{
	//{{AFX_DATA_INIT(CEventsFilterDlg)
	m_dwErrTmp = 0;
	m_dwWarnTmp = 0;
	m_dwInfoTmp = 0;
	m_bShowChannelsEv = FALSE;
	//}}AFX_DATA_INIT
  m_pEF = NULL;
  m_bUseFilter    = FALSE;
  m_bBeginUse     = FALSE;
  m_tBegin        = YTime::INVALID();
  m_bEndUse       = FALSE;
  m_tEnd          = YTime::INVALID();
  m_dwErrFlags    = 0;
  m_dwWarnFlags   = 0;
  m_dwInfoFlags   = 0; 
//  m_nChannelsList = 0;
}


void CEventsFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventsFilterDlg)
	DDX_Control(pDX, IDC_CHECK_CHANNELS_USE, m_chkUseChannels);
	DDX_Control(pDX, IDC_EDIT_WARNING, m_editWarn);
	DDX_Control(pDX, IDC_EDIT_INFO, m_editInfo);
	DDX_Control(pDX, IDC_EDIT_ERROR, m_editErr);
	DDX_Control(pDX, IDC_DATEPICKER_STOP, m_pickDateStop);
	DDX_Control(pDX, IDC_DATEPICKER_START, m_pickDateStart);
	DDX_Control(pDX, IDC_TIMEPICKER_STOP, m_pickTimeStop);
	DDX_Control(pDX, IDC_TIMEPICKER_START, m_pickTimeStart);
	DDX_Control(pDX, IDC_CHECK_STOP_USE, m_chkStopUse);
	DDX_Control(pDX, IDC_CHECK_START_USE, m_chkStartUse);
	DDX_Control(pDX, IDC_COMBO_VIEW_RANGE, m_cmbViewRange);
	DDX_Control(pDX, IDC_CHECK_ALL_CHANNELS, m_chkAllChannels);
	DDX_Control(pDX, IDC_CHECK_WARNING, m_chkWarn);
	DDX_Control(pDX, IDC_CHECK_ERROR, m_chkErr);
	DDX_Control(pDX, IDC_CHECK_INFO, m_chkInfo);
	DDX_Control(pDX, IDC_CHECK_USE_FILTER, m_chkUseFilter);
	DDX_Control(pDX, IDC_SPIN_WARNING, m_spinWarn);
	DDX_Control(pDX, IDC_SPIN_ERROR, m_spinErr);
	DDX_Control(pDX, IDC_SPIN_INFO, m_spinInfo);
	DDX_Control(pDX, IDC_LIST_CHANNELS, m_listChannels);
	DDX_Text(pDX, IDC_EDIT_ERROR, m_dwErrTmp);
	DDV_MinMaxDWord(pDX, m_dwErrTmp, 0, 7);
	DDX_Text(pDX, IDC_EDIT_WARNING, m_dwWarnTmp);
	DDV_MinMaxDWord(pDX, m_dwWarnTmp, 0, 7);
	DDX_Text(pDX, IDC_EDIT_INFO, m_dwInfoTmp);
	DDV_MinMaxDWord(pDX, m_dwInfoTmp, 0, 7);
	DDX_Check(pDX, IDC_CHECK_START_USE, m_bBeginUse);
	DDX_Check(pDX, IDC_CHECK_STOP_USE, m_bEndUse);
	DDX_Check(pDX, IDC_CHECK_USE_FILTER, m_bUseFilter);
	DDX_Check(pDX, IDC_CHECK_CHANNELS_USE, m_bShowChannelsEv);
	//}}AFX_DATA_MAP
//   DDX_Text(pDX, IDC_EDIT_INFO, m_dwInfo);
//   DDV_MinMaxUInt(pDX, m_dwInfo, 0, 7);
//   DDX_Text(pDX, IDC_EDIT_WARNING, m_dwWarn);
//   DDV_MinMaxUInt(pDX, m_dwWarn, 0, 7);
//   DDX_Text(pDX, IDC_EDIT_ERROR, m_dwErr);
//   DDV_MinMaxUInt(pDX, m_dwErr, 0, 7);
  if(pDX->m_bSaveAndValidate) { //controls -> vars
    CTime tDate,tTime;
    //set BeginTime
    m_pickDateStart.GetTime(tDate);
    m_pickTimeStart.GetTime(tTime);
    if(m_bBeginUse)
      m_tBegin.SetDateTime(NULL,tDate,tTime,0);//AY 13.01.2013 OLD: SetDateTime(tDate,tTime,0)
    else m_tBegin = YTime::INVALID();
    //set EndTime
    m_pickDateStop.GetTime(tDate);
    m_pickTimeStop.GetTime(tTime);
    if(m_bEndUse)
      m_tEnd.SetDateTime(NULL,tDate,tTime,0);//AY 13.01.2013 OLD: SetDateTime(tDate,tTime,0)
    else m_tEnd = YTime::INVALID();
    //set LevelErrFlags
    if(m_chkErr.GetCheck()) {
      CString sz;
      m_editErr.GetWindowText(sz);
      DWORD dw = _ttoi(sz);
      m_dwErrFlags  = (1<<(dw+1)) -1; //set flags [0..m_nErr] bits
    }else m_dwErrFlags  = 0;
    //set LevelWarnFlags
    if(m_chkWarn.GetCheck()) {
      CString sz;
      m_editWarn.GetWindowText(sz);
      DWORD dw = _ttoi(sz);
      m_dwWarnFlags  = (1<<(dw+1)) - 1;
    }else m_dwWarnFlags = 0;
    //set LevelInfoFlags
    if(m_chkInfo.GetCheck()) {
      CString sz;
      m_editInfo.GetWindowText(sz);
      DWORD dw = _ttoi(sz);
      m_dwInfoFlags  = (1<<(dw+1)) - 1;
    }else m_dwInfoFlags = 0;
    //set use channels filters
//    SetShowChannelsEvents
    //set SelectAll channels
    m_aChannels.RemoveAll();
    if(m_chkAllChannels.GetCheck()) {
      for(int i=0;i<CEventsFilter::_MAXCHANNELS;++i)
        m_aChannels.AddChannel(i); //TODO HSRSCHANNEL
    }
  }
  else {//vars -> controls
    CTime tDate,tTime;
    //set BeginTime
    m_pickDateStart.SetTime(&(m_tBegin.GetAsCTime()));
    m_pickTimeStart.SetTime(&(m_tBegin.GetAsCTime()));
    DoCheckUseStartTime(!m_tBegin.IsInvalid());
    //set EndTime
    m_pickDateStop.SetTime(&(m_tEnd.GetAsCTime()));
    m_pickTimeStop.SetTime(&(m_tEnd.GetAsCTime()));
    DoCheckUseStopTime(!m_tEnd.IsInvalid());
    //set ErrorFlags
    TCHAR buf[10];
    int nNum = _FlagsToNum(m_dwErrFlags);
    nNum=nNum!=-1?nNum:0;
    _itot(nNum,buf,10);
    m_editErr.SetWindowText(buf);
    DoCheckErrLevel(m_dwErrFlags!=0);
    //set WarnFlags
    nNum = _FlagsToNum(m_dwWarnFlags);
    nNum=nNum!=-1?nNum:0;
    _itot(nNum,buf,10);
    m_editWarn.SetWindowText(buf);
    DoCheckWarnLevel(m_dwWarnFlags!=0);
    //set InfoFlags
    nNum = _FlagsToNum(m_dwInfoFlags);
    nNum=nNum!=-1?nNum:0;
    _itot(nNum,buf,10);
    m_editInfo.SetWindowText(buf);
    DoCheckInfoLevel(m_dwInfoFlags!=0);
    //set SelectAll channels
    DoCheckAllChannels(m_aChannels.GetSize()>=64); //if selected >=64 - check all channels

    DoUseFilter(m_bUseFilter);
  }
}

BEGIN_MESSAGE_MAP(CEventsFilterDlg, CDialogBar)
	//{{AFX_MSG_MAP(CEventsFilterDlg)
	ON_BN_CLICKED(IDC_CHECK_USE_FILTER, OnCheckUseFilter)
	ON_BN_CLICKED(IDC_CHECK_ALL_CHANNELS, OnCheckAllChannels)
	ON_BN_CLICKED(IDC_CHECK_START_USE, OnCheckStartUse)
	ON_BN_CLICKED(IDC_CHECK_STOP_USE, OnCheckStopUse)
	ON_BN_CLICKED(IDC_CHECK_INFO, OnCheckInfo)
	ON_BN_CLICKED(IDC_CHECK_WARNING, OnCheckWarning)
	ON_BN_CLICKED(IDC_CHECK_ERROR, OnCheckError)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_APPLY, OnCheckApply)
	ON_BN_CLICKED(IDC_CHECK_CHANNELS_USE, OnCheckChannelsUse)
	//}}AFX_MSG_MAP
//  ON_MESSAGE(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
  ON_MESSAGE(WM_INITDIALOG, OnInitDialog )
END_MESSAGE_MAP()
//---------------------------------------
LRESULT CEventsFilterDlg::WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
  ASSERT_VALID(this);
  
  // Parent notification messages are just passed to parent of control bar.
  switch (nMsg)
  {
   case WM_COMMAND:
     if(LOWORD(wParam)==IDC_CHECK_APPLY)
     {
       OnCheckApply();
       ::SendMessage(::GetParent(m_hWnd), nMsg, wParam, lParam);
       break;
     }
//      
//      break;
//   case WM_DRAWITEM:
//   case WM_MEASUREITEM:
//   case WM_DELETEITEM:
//   case WM_COMPAREITEM:
//   case WM_VKEYTOITEM:
//   case WM_CHARTOITEM:
//     return ::SendMessage(::GetParent(m_hWnd), nMsg, wParam, lParam);
  }
  return CWnd::WindowProc(nMsg, wParam, lParam);
}
//---------------------------------------
LONG CEventsFilterDlg::OnInitDialog(UINT wParam, LONG lParam) {
  if(!HandleInitDialog(wParam, lParam) || !UpdateData(FALSE))
  {
    TRACE0("Warning: UpdateData failed during dialog init.\n");
    return FALSE;
  }

  delete m_pEF; 
  m_pEF = NULL;

  m_pEF = new CEventsFilter;

  m_spinErr.SetRange32(0,7);
  m_spinInfo.SetRange32(0,7);
  m_spinWarn.SetRange32(0,7);
	
//  m_pEF

  UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//-----------
BOOL CEventsFilterDlg::Create(CWnd* pParentWnd,UINT nStyle, UINT nID) {
  return CDialogBar::Create(pParentWnd,IDD,nStyle,nID);
}
//---------------------------------------
void CEventsFilterDlg::OnDestroy() {
  delete m_pEF;
  m_pEF = NULL;
  CDialogBar::OnDestroy();
  
}
//---------------------------------------
void CEventsFilterDlg::DoUseFilter(BOOL bUse) {
  m_chkUseFilter.SetCheck(bUse);
//    DoEnableSelectAllChannels(bUse);  
//    DoEnableChannelsList(bUse);
  DoEnableChannelsEvents(bUse);
  DoEnableCheckInfoLevel(bUse);
  DoEnableCheckWarnLevel(bUse);
  DoEnableCheckErrLevel(bUse);
  DoEnableCheckUseStartTime(bUse);
  DoEnableCheckUseStopTime(bUse);
  DoEnableComboViewRange(bUse);
}
//---------------------------------------
void CEventsFilterDlg::DoUseChannelsEvents(BOOL bUse) {
  m_chkUseChannels.SetCheck(bUse?1:0);
//  if(bUse) {
  DoEnableSelectAllChannels(bUse);  
  DoEnableChannelsList(bUse);
//  }
}
//---------------------------------------
void CEventsFilterDlg::DoCheckAllChannels(BOOL bCheck) {
  m_chkAllChannels.SetCheck(bCheck);
}
//---------------------------------------
void CEventsFilterDlg::DoCheckInfoLevel(BOOL bCheck) {
  m_chkInfo.SetCheck(bCheck);
  m_editInfo.EnableWindow(bCheck);
  m_spinInfo.EnableWindow(bCheck);
}
//-----------
void CEventsFilterDlg::DoCheckWarnLevel(BOOL bCheck) {
  m_chkWarn.SetCheck(bCheck);
  m_editWarn.EnableWindow(bCheck);
  m_spinWarn.EnableWindow(bCheck);
}
//-----------
void CEventsFilterDlg::DoCheckErrLevel(BOOL bCheck) {
  m_chkErr.SetCheck(bCheck);
  m_editErr.EnableWindow(bCheck);
  m_spinErr.EnableWindow(bCheck);
}
//-----------
void CEventsFilterDlg::DoCheckUseStartTime(BOOL bCheck) {
  m_chkStartUse.SetCheck(bCheck);
  m_pickTimeStart.EnableWindow(bCheck);
  m_pickDateStart.EnableWindow(bCheck);
}
//-----------
void CEventsFilterDlg::DoCheckUseStopTime(BOOL bCheck) {
  m_chkStopUse.SetCheck(bCheck);
  m_pickTimeStop.EnableWindow(bCheck);
  m_pickDateStop.EnableWindow(bCheck);
}
//---------------------------------------
void CEventsFilterDlg::DoEnableChannelsEvents(BOOL bEnable) {
  m_chkUseChannels.EnableWindow(bEnable);
  DoUseChannelsEvents(m_chkUseChannels.GetCheck());
}
//-----------
void CEventsFilterDlg::DoEnableSelectAllChannels(BOOL bEnable) {
  m_chkAllChannels.EnableWindow(bEnable);
}
//-----------
void CEventsFilterDlg::DoEnableChannelsList(BOOL bEnable) {
  GetDlgItem(IDC_STATIC_CHANNELS)->EnableWindow(bEnable);
  m_listChannels.EnableWindow(bEnable);
}
//-----------
void CEventsFilterDlg::DoEnableCheckInfoLevel(BOOL bEnable) {
  m_chkInfo.EnableWindow(bEnable);
  m_editInfo.EnableWindow(bEnable);
  m_spinInfo.EnableWindow(bEnable);
  if(bEnable)
    DoCheckInfoLevel(m_chkInfo.GetCheck());
}
//-----------
void CEventsFilterDlg::DoEnableCheckWarnLevel(BOOL bEnable) {
  m_chkWarn.EnableWindow(bEnable);
  m_editWarn.EnableWindow(bEnable);
  m_spinWarn.EnableWindow(bEnable);
  if(bEnable)
    DoCheckWarnLevel(m_chkWarn.GetCheck());
}
//-----------
void CEventsFilterDlg::DoEnableCheckErrLevel(BOOL bEnable) {
  m_chkErr.EnableWindow(bEnable);
  m_editErr.EnableWindow(bEnable);
  m_spinErr.EnableWindow(bEnable);
  if(bEnable)
    DoCheckErrLevel(m_chkErr.GetCheck());  
}
//-----------
void CEventsFilterDlg::DoEnableCheckUseStartTime(BOOL bEnable) {
  m_pickDateStart.EnableWindow(bEnable);
  m_pickTimeStart.EnableWindow(bEnable);
  m_chkStartUse.EnableWindow(bEnable);
  GetDlgItem(IDC_STATIC_START)->EnableWindow(bEnable);
  if(bEnable)
    DoCheckUseStartTime(m_chkStartUse.GetCheck());
}
//-----------
void CEventsFilterDlg::DoEnableCheckUseStopTime(BOOL bEnable) {
  m_pickDateStop.EnableWindow(bEnable);
  m_pickTimeStop.EnableWindow(bEnable);
  m_chkStopUse.EnableWindow(bEnable);
  GetDlgItem(IDC_STATIC_STOP)->EnableWindow(bEnable);
  if(bEnable)
    DoCheckUseStopTime(m_chkStopUse.GetCheck());
}
//-----------
void CEventsFilterDlg::DoEnableComboViewRange(BOOL bEnable) {
  m_cmbViewRange.EnableWindow(bEnable);
}
//-----------

void CEventsFilterDlg::OnCheckUseFilter() {
	DoUseFilter(m_chkUseFilter.GetCheck());
}

void CEventsFilterDlg::OnCheckChannelsUse() {
	DoUseChannelsEvents(m_chkUseChannels.GetCheck());
}

void CEventsFilterDlg::OnCheckAllChannels() {
  DoCheckAllChannels(m_chkAllChannels.GetCheck());
}

void CEventsFilterDlg::OnCheckStartUse() {
	DoCheckUseStartTime(m_chkStartUse.GetCheck());
}

void CEventsFilterDlg::OnCheckStopUse() {
  DoCheckUseStopTime(m_chkStopUse.GetCheck());
}

void CEventsFilterDlg::OnCheckInfo() {
  DoCheckInfoLevel(m_chkInfo.GetCheck());
}

void CEventsFilterDlg::OnCheckWarning() {
  DoCheckWarnLevel(m_chkWarn.GetCheck());  
}

void CEventsFilterDlg::OnCheckError() {
  DoCheckErrLevel(m_chkErr.GetCheck());  
}

void CEventsFilterDlg::OnCheckApply() {
  UpdateData(TRUE);
//CWnd* pParent = GetParent();
//   CEventsFilter filter;
//   ExportFilterConfig(filter);

}
//---------------------------------------
LRESULT CEventsFilterDlg::OnIdleUpdateCmdUI(WPARAM wParam, LPARAM lParam) {
  return  CDialogBar::OnIdleUpdateCmdUI(wParam, lParam);
//   if(IsWindowVisible()) {
//     //    CWnd* pOwner = GetOwnerNotify();
//     CFrameWnd* pParent = (CFrameWnd*)GetParent();
//     if(pParent)
//       OnUpdateCmdUI(pParent, (BOOL)wParam);
//   }
//   return 0L;
}
//---------------------------------------
//DEL void CEventsFilterDlg::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler) {
//DEL //  ASSERT(bDisableIfNoHndler==FALSE);
//DEL   CDialogBar::OnUpdateCmdUI(pTarget, bDisableIfNoHndler);
//DEL }
//---------------------------------------
void CEventsFilterDlg::ImportFilterConfig(const CEventsFilter &filter) {
  //set UseFilter
  m_bUseFilter = filter.IsUseFilter();
  //set StartTime
  m_tBegin     = filter.GetStartTime();
  //set StopTime
  m_tEnd       = filter.GetStopTime();
  //set LevelErrFlags
  m_dwErrFlags = filter.GetLevelErrorFlags();
  //set LevelWarnFlags
  m_dwWarnFlags= filter.GetLevelWarningFlags();
  //set LevelInfoFlags
  m_dwInfoFlags= filter.GetLevelInfoFlags();
  //set  ShowChannelsEvents
  m_bShowChannelsEv = filter.IsShowChannelsEvents();
  //set ChannelsList (TODO)
  filter.GetChannelsList(&m_aChannels);
  UpdateData(FALSE);
}
//-----------
void CEventsFilterDlg::ExportFilterConfig(CEventsFilter &filter) const {
  //set UseFilter                                                
  filter.SetUseFilter(m_bUseFilter);
  //set StartTime
  filter.SetStartTime(m_tBegin);
  //set StopTime
  filter.SetStopTime(m_tEnd);
  //set LevelErrFlags
  filter.SetLevelErrorFlags(m_dwErrFlags);
  //set LevelWarnFlags
  filter.SetLevelWarningFlags(m_dwWarnFlags);
  //set LevelInfoFlags
  filter.SetLevelInfoFlags(m_dwInfoFlags);
  //set  ShowChannelsEvents
  filter.SetShowChannelsEvents(m_bShowChannelsEv);
  //set ChannelsList (TODO)
  filter.SetChannelsList(&m_aChannels);
}
