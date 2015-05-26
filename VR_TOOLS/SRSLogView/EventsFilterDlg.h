#if !defined(AFX_EVENTSFILTERDLG_H__8E9211EC_14BF_46C8_B6FC_0FED4EAF5661__INCLUDED_)
#define AFX_EVENTSFILTERDLG_H__8E9211EC_14BF_46C8_B6FC_0FED4EAF5661__INCLUDED_

#include "yTime.h"
#include "channels/chan_id.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEventsFilter;
// EventsFilterDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CEventsFilterDlg dialog
class CEventsFilterDlg : public CDialogBar
{
  DECLARE_DYNAMIC(CEventsFilterDlg)
// Construction
public:
	                CEventsFilterDlg();   // standard constructor
  BOOL            Create(CWnd* pParentWnd,UINT nStyle, UINT nID);

//Implementation
public:
  void            ImportFilterConfig(const CEventsFilter& filter);
  void            ExportFilterConfig(CEventsFilter &filter)const;
protected:

private:

//Implementation helpers
public:
protected:
  void            DoUseFilter(BOOL bUse);

  void            DoUseChannelsEvents(BOOL bUse);
  void            DoCheckAllChannels(BOOL bCheck);
  void            DoCheckInfoLevel(BOOL bCheck);
  void            DoCheckWarnLevel(BOOL bCheck);
  void            DoCheckErrLevel(BOOL bCheck);
  void            DoCheckUseStartTime(BOOL bCheck);
  void            DoCheckUseStopTime(BOOL bCheck);
  
  void            DoEnableChannelsEvents(BOOL bEnable);
  void            DoEnableSelectAllChannels(BOOL bEnable);
  void            DoEnableChannelsList(BOOL bEnable);
  void            DoEnableCheckInfoLevel(BOOL bEnable);
  void            DoEnableCheckWarnLevel(BOOL bEnable);
  void            DoEnableCheckErrLevel(BOOL bEnable);
  void            DoEnableCheckUseStartTime(BOOL bEnable);
  void            DoEnableCheckUseStopTime(BOOL bEnable);
  void            DoEnableComboViewRange(BOOL bEnable);
//Attributes
public:
  
protected:
  CEventsFilter*  m_pEF;
  YSRSChannelsList  m_aChannels;
private:
  BOOL	          m_bUseFilter;
  
  BOOL	          m_bBeginUse;
  YTime           m_tBegin;
  
  BOOL	          m_bEndUse;
  YTime           m_tEnd;
  
  DWORD           m_dwErrFlags;
  DWORD           m_dwWarnFlags;
  DWORD           m_dwInfoFlags;

//  __int64         m_nChannelsList;
public:
// Dialog Data
	//{{AFX_DATA(CEventsFilterDlg)
	enum { IDD = IDR_EVENTS_FILTER };
	CButton	m_chkUseChannels;
	CEdit	m_editWarn;
	CEdit	m_editInfo;
	CEdit	m_editErr;
	CDateTimeCtrl	m_pickDateStop;
	CDateTimeCtrl	m_pickDateStart;
	CDateTimeCtrl	m_pickTimeStop;
	CDateTimeCtrl	m_pickTimeStart;
	CButton	m_chkStopUse;
	CButton	m_chkStartUse;
	CComboBox	m_cmbViewRange;
	CButton	m_chkAllChannels;
	CButton	m_chkWarn;
	CButton	m_chkErr;
	CButton	m_chkInfo;
	CButton	m_chkUseFilter;
	CSpinButtonCtrl	m_spinWarn;
	CSpinButtonCtrl	m_spinErr;
	CSpinButtonCtrl	m_spinInfo;
	CListCtrl	m_listChannels;
	DWORD	m_dwErrTmp;
	DWORD	m_dwWarnTmp;
	DWORD	m_dwInfoTmp;
	BOOL	m_bShowChannelsEv;
	//}}AFX_DATA
//   DWORD	m_dwInfo; //internal usage
//   DWORD	m_dwWarn; //internal usage
//   DWORD	m_dwErr;  //internal usage


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventsFilterDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
  LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
  LRESULT WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);

	// Generated message map functions
	//{{AFX_MSG(CEventsFilterDlg)
	afx_msg void OnCheckUseFilter();
	afx_msg void OnCheckAllChannels();
	afx_msg void OnCheckStartUse();
	afx_msg void OnCheckStopUse();
	afx_msg void OnCheckInfo();
	afx_msg void OnCheckWarning();
	afx_msg void OnCheckError();
	afx_msg void OnDestroy();
	afx_msg void OnCheckApply();
	afx_msg void OnCheckChannelsUse();
	//}}AFX_MSG
  afx_msg LONG    OnInitDialog(UINT, LONG);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVENTSFILTERDLG_H__8E9211EC_14BF_46C8_B6FC_0FED4EAF5661__INCLUDED_)
