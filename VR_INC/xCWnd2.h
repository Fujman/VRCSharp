// xCWnd2.h
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XCWND2_H__INCLUDED_)
#define AFX_XCWND2_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CResizableWnd<CWnd>

template <class CWND>
class CResizableWnd : public CWND
{
public://construction/destruction
                CResizableWnd(LPCTSTR lpszTemplateName, CWnd* pParentWnd=NULL);//dialog-like
                CResizableWnd(UINT nIDTemplate, CWnd* pParentWnd=NULL);//dialog-like
                CResizableWnd();
  void          SetSectionName(LPCTSTR pszSection)
                  { m_szSection = pszSection; }
  LPCTSTR       GetSectionName() const
                  { return m_szSection; }
public:
  BOOL          LoadWindowPlacement(LPCTSTR szConfiguration=NULL, int nVariant=0, BOOL bRectOnly=FALSE);
  BOOL          SaveWindowPlacement(LPCTSTR szConfiguration=NULL, int nVariant=0, BOOL bRectOnly=FALSE);

  BOOL          LoadControlPos(CWnd* pControl, LPCTSTR szControl=NULL, LPCTSTR szConfiguration=NULL, int nVariant=0);
  BOOL          SaveControlPos(CWnd* pControl, LPCTSTR szControl=NULL, LPCTSTR szConfiguration=NULL, int nVariant=0);
  BOOL          LoadControlPos(UINT idControl, LPCTSTR szControl=NULL, LPCTSTR szConfiguration=NULL, int nVariant=0);
  BOOL          SaveControlPos(UINT idControl, LPCTSTR szControl=NULL, LPCTSTR szConfiguration=NULL, int nVariant=0);

  BOOL          LoadSplitterLayout(CSplitterWnd* pSplitter, LPCTSTR szConfiguration=NULL, int nVariant=0);
  BOOL          SaveSplitterLayout(CSplitterWnd* pSplitter, LPCTSTR szConfiguration=NULL, int nVariant=0);

  BOOL          LoadListLayout(CListCtrl* pList, LPCTSTR szControl=NULL, LPCTSTR szConfiguration=NULL, int nVariant=0);
  BOOL          SaveListLayout(CListCtrl* pList, LPCTSTR szControl=NULL, LPCTSTR szConfiguration=NULL, int nVariant=0);

  BOOL          LoadControlsLayout(UINT* pidControls, LPCTSTR szConfiguration=NULL, int nVariant=0);
  BOOL          SaveControlsLayout(UINT* pidControls, LPCTSTR szConfiguration=NULL, int nVariant=0);

public:
  virtual BOOL  DoSetControlPos(CWnd* pControl, LPCRECT prect, LPCRECT prectControl, LPCRECT prectParent);
  virtual BOOL  DoSetWindowPos(LPCRECT prect);
  virtual BOOL  DoSetWindowPlacement(WINDOWPLACEMENT* pwndpl);
public://helpers
  static CString MakeControlVariableName(CWnd* pControl, LPCTSTR szControl, LPCTSTR szConfiguration=NULL, int nVariant=0);
  static CString MakeVariableName(LPCTSTR szBase, LPCTSTR szConfiguration=NULL, int nVariant=0);
protected:
  CString       m_szSection;
};

/////////////////////////////////////////////////////////////////////////////
// CResizableWnd<CWnd> implementation

template <class CWND>
CResizableWnd<CWND>::CResizableWnd()
{
  m_szSection = GetRuntimeClass()->m_lpszClassName;
}

template <class CWND>
CResizableWnd<CWND>::CResizableWnd(LPCTSTR lpszTemplateName, CWnd* pParentWnd)//dialog-like
:
  CWND(lpszTemplateName, pParentWnd)
{
  m_szSection = GetRuntimeClass()->m_lpszClassName;
}

template <class CWND>
CResizableWnd<CWND>::CResizableWnd(UINT nIDTemplate, CWnd* pParentWnd)//dialog-like
:
  CWND(nIDTemplate, pParentWnd)
{
  m_szSection = GetRuntimeClass()->m_lpszClassName;
}

// helpers

template <class CWND> CString CResizableWnd<CWND>::
MakeVariableName(LPCTSTR szBase, LPCTSTR szConfiguration, int nVariant)
{
  CString szVariable = szBase;
  if(szConfiguration!=NULL)
    szVariable += szConfiguration;
  if(nVariant!=0) {
    CString szVariant; szVariant.Format(_T("%d"),nVariant);
    szVariable += szVariant;
  }
  return szVariable;
}

template <class CWND> CString CResizableWnd<CWND>::
MakeControlVariableName(CWnd* pControl, LPCTSTR szControl, LPCTSTR szConfiguration, int nVariant)
{
  if(pControl==NULL)
    return "";
  CString szBase;
  if(szControl!=NULL)
    szBase += CString(_T("control_")) + szControl;
  else
    szBase.Format(_T("control%d"),pControl->GetDlgCtrlID());
  return MakeVariableName(szBase, szConfiguration, nVariant);
}

// dialog

template <class CWND> BOOL CResizableWnd<CWND>::
SaveWindowPlacement(LPCTSTR szConfiguration, int nVariant, BOOL bRectOnly)
{
	WINDOWPLACEMENT wp = {sizeof(WINDOWPLACEMENT)};
	if (!GetWindowPlacement(&wp))
		return FALSE;
	
	RECT& rc = wp.rcNormalPosition;	// alias

	CString data;
	if (bRectOnly)	// save size/pos only (normal state)
	{
		// use screen coordinates
		GetWindowRect(&rc);

		data.Format(_T("%d,%d,%d,%d,%d,%d"), rc.left, rc.top,
			rc.right, rc.bottom, SW_NORMAL, 0);
	}
	else	// save also min/max state
	{
		// use workspace coordinates
		data.Format(_T("%d,%d,%d,%d,%d,%d"), rc.left, rc.top,
			rc.right, rc.bottom, wp.showCmd, wp.flags);
	}

  CString szVariable = MakeVariableName(_T("WindowPlacement"),szConfiguration, nVariant);
	return AfxGetApp()->WriteProfileString(m_szSection, szVariable, data);
}

template <class CWND> BOOL CResizableWnd<CWND>::
LoadWindowPlacement(LPCTSTR szConfiguration, int nVariant, BOOL bRectOnly)
{
  CString szVariable = MakeVariableName(_T("WindowPlacement"),szConfiguration, nVariant);
	CString data = AfxGetApp()->GetProfileString(m_szSection, szVariable);
	
	if(data.IsEmpty()) // never saved before
		return FALSE;

	WINDOWPLACEMENT wp = {sizeof(WINDOWPLACEMENT)};
	
	if(!GetWindowPlacement(&wp))
		return FALSE;

	RECT& rc = wp.rcNormalPosition;	// alias

	if (_stscanf(data, _T("%d,%d,%d,%d,%d,%d"), &rc.left, &rc.top,
		&rc.right, &rc.bottom, &wp.showCmd, &wp.flags) == 6)
	{
		if (bRectOnly)	// restore size/pos only
			return DoSetWindowPos(&rc);
		else	// restore also min/max state
			return DoSetWindowPlacement(&wp);
	}
	return FALSE;
}

// list

template <class CWND> BOOL CResizableWnd<CWND>::
LoadListLayout(CListCtrl* pList, LPCTSTR szControl, LPCTSTR szConfiguration, int nVariant)
{
  CString szID; szID.Format(_T("%d"),pList->GetDlgCtrlID());
  if(!szControl)
    szControl = szID;
  else
    ASSERT(!szID.IsEmpty());

  CString szVariable = MakeVariableName(CString(_T("ListLayout_"))+szControl,szConfiguration, nVariant);
  CString item;
  CString data;

  int aColumn[256]={0};
  int nCount = 0;
	CHeaderCtrl* pCtrl = pList->GetHeaderCtrl();
	ASSERT(pCtrl != NULL);
	if (pCtrl != NULL)
		nCount = pCtrl->GetItemCount();

  //TO DO: chek columns number
  if(nCount==0)
    return TRUE;
  ASSERT(nCount<256);

  for(int i=0; i<nCount; ++i){
    item.Format(_T("_col%d"),i);
	  data = AfxGetApp()->GetProfileString(m_szSection, szVariable+item);
    int iWidth = 0;
	  if(_stscanf(data, _T("%d,%d"), &aColumn[i], &iWidth) != 2)
      return FALSE;
    pList->SetColumnWidth(i,iWidth);//or aColumn[i]?
  }

  if(! pList->SetColumnOrderArray(nCount,aColumn) )
    return FALSE;

  return TRUE;
}

template <class CWND> BOOL CResizableWnd<CWND>::
SaveListLayout(CListCtrl* pList, LPCTSTR szControl, LPCTSTR szConfiguration, int nVariant)
{
  CString szID; szID.Format(_T("%d"),pList->GetDlgCtrlID());
  if(!szControl)
    szControl = szID;
  else
    ASSERT(!szID.IsEmpty());

  CString szVariable = MakeVariableName(CString(_T("ListLayout_"))+szControl,szConfiguration, nVariant);
  CString data;
  CString item;

  int aColumn[256]={0};
  int nCount = 0;
	CHeaderCtrl* pCtrl = pList->GetHeaderCtrl();
	ASSERT(pCtrl != NULL);
	if (pCtrl != NULL)
		nCount = pCtrl->GetItemCount();

  if(nCount==0)
    return TRUE;

  ASSERT(nCount<256);
  if(! pList->GetColumnOrderArray(aColumn,-1) )
    return FALSE;

  for(int i=0; i<nCount; ++i){
    item.Format(_T("_col%d"),i);
    int iWidth = pList->GetColumnWidth(i);
		data.Format(_T("%d,%d"), aColumn[i], iWidth);
	  if( !AfxGetApp()->WriteProfileString(m_szSection, szVariable+item, data) )
      return FALSE;
  }
  return TRUE;
}

// splitter

template <class CWND> BOOL CResizableWnd<CWND>::
LoadSplitterLayout(CSplitterWnd* pSplitter, LPCTSTR szConfiguration, int nVariant)
{
  CString szVariable = MakeVariableName(_T("SplitterLayout"),szConfiguration, nVariant);
  CString data;
  CString item;
  int nRows = pSplitter->GetRowCount();
  int nCols = pSplitter->GetColumnCount();
  int cCur, cMin;
  int i;
  //TO DO: check rows/cols number

  for(i=0; i<nRows; ++i){
    item.Format(_T("_row%d"),i);
	  data = AfxGetApp()->GetProfileString(m_szSection, szVariable+item);
	  if(_stscanf(data, _T("%d,%d"), &cCur, &cMin) != 2)
      return FALSE;
    pSplitter->SetRowInfo(i, cCur, cMin);
  }
  for(i=0; i<nCols; ++i){
    item.Format(_T("_col%d"),i);
	  data = AfxGetApp()->GetProfileString(m_szSection, szVariable+item);
	  if(_stscanf(data, _T("%d,%d"), &cCur, &cMin) != 2)
      return FALSE;
    pSplitter->SetColumnInfo(i, cCur, cMin);
  }
/*
  WINDOWPLACEMENT wndpl = {sizeof(wndpl)};
  GetWindowPlacement(&wndpl);
  wndpl.showCmd = SW_SHOWNORMAL;
  SetWindowPlacement(&wndpl);
*/
  return TRUE;
}

template <class CWND> BOOL CResizableWnd<CWND>::
SaveSplitterLayout(CSplitterWnd* pSplitter, LPCTSTR szConfiguration, int nVariant)
{
  CString szVariable = MakeVariableName(_T("SplitterLayout"),szConfiguration, nVariant);
  CString data;
  CString item;
  int nRows = pSplitter->GetRowCount();
  int nCols = pSplitter->GetColumnCount();
  int cCur, cMin;
  int i;

  data.Format(_T("%d"), nRows);
	if( !AfxGetApp()->WriteProfileString(m_szSection, szVariable+_T("_rows"), data) )
    return FALSE;
  data.Format(_T("%d"), nCols);
	if( !AfxGetApp()->WriteProfileString(m_szSection, szVariable+_T("_cols"), data) )
    return FALSE;

  for(i=0; i<nRows; ++i){
    item.Format(_T("_row%d"),i);
    pSplitter->GetRowInfo(i, cCur, cMin);
		data.Format(_T("%d,%d"), cCur, cMin);
	  if( !AfxGetApp()->WriteProfileString(m_szSection, szVariable+item, data) )
      return FALSE;
  }
  for(i=0; i<nCols; ++i){
    item.Format(_T("_col%d"),i);
    pSplitter->GetColumnInfo(i, cCur, cMin);
		data.Format(_T("%d,%d"), cCur, cMin);
	  if( !AfxGetApp()->WriteProfileString(m_szSection, szVariable+item, data) )
      return FALSE;
  }
  return TRUE;
}

// controls

template <class CWND> BOOL CResizableWnd<CWND>::
SaveControlPos(CWnd* pControl, LPCTSTR szControl, LPCTSTR szConfiguration, int nVariant)
{
  if(pControl==NULL)
    return FALSE;

	WINDOWPLACEMENT wpControl = {sizeof(WINDOWPLACEMENT)};
	if(!pControl->GetWindowPlacement(&wpControl))
		return FALSE;
	RECT& rcControl = wpControl.rcNormalPosition;	//alias

	RECT rcParent; GetClientRect(&rcParent);
  if(GetStyle()&WS_CHILD){
	  WINDOWPLACEMENT wpParent = {sizeof(WINDOWPLACEMENT)};
	  if(!this->GetWindowPlacement(&wpParent))
		  return FALSE;
	  rcParent = wpParent.rcNormalPosition;//AY 05.08.2005
  }

  if(rcParent.top==0 && 
     rcParent.left==0 &&
     rcParent.bottom==0 &&
     rcParent.right==0)
   return FALSE;//AY 05.08.2005

	CString data;
	data.Format(_T("%d,%d,%d,%d,%d,%d,%d,%d"),
    rcControl.left, rcControl.top,
		rcControl.right, rcControl.bottom,
    rcParent.left, rcParent.top,
		rcParent.right, rcParent.bottom);

  CString szVariable = MakeControlVariableName(pControl,szControl,szConfiguration,nVariant);
	return AfxGetApp()->WriteProfileString(m_szSection, szVariable, data);
}

template <class CWND> BOOL CResizableWnd<CWND>::
LoadControlPos(CWnd* pControl, LPCTSTR szControl, LPCTSTR szConfiguration, int nVariant)
{
  if(pControl==NULL)
    return FALSE;
  CString szVariable = MakeControlVariableName(pControl,szControl,szConfiguration,nVariant);
	CString data = AfxGetApp()->GetProfileString(m_szSection, szVariable);
	if(data.IsEmpty()) // never saved before
		return FALSE;

	CRect rcParent0; GetClientRect(&rcParent0);

	CRect rcControl;
	CRect rcParent;

	if(8 == _stscanf(data, _T("%d,%d,%d,%d,%d,%d,%d,%d"),
    &rcControl.left, &rcControl.top,
		&rcControl.right, &rcControl.bottom,
    &rcParent.left, &rcParent.top,
		&rcParent.right, &rcParent.bottom
    ))
	{
    CRect rc;
    rc.left   = (rcParent0.Width()*rcControl.left)/rcParent.Width();
    rc.top    = (rcParent0.Height()*rcControl.top)/rcParent.Height();
    rc.right  = (rcParent0.Width()*rcControl.right)/rcParent.Width();
    rc.bottom = (rcParent0.Height()*rcControl.bottom)/rcParent.Height();

		return DoSetControlPos(pControl, &rc, &rcControl, &rcParent);
	}
	return FALSE;
}


template <class CWND> BOOL CResizableWnd<CWND>::
LoadControlPos(UINT idControl, LPCTSTR szControl, LPCTSTR szConfiguration, int nVariant)
{
  return LoadControlPos(GetDlgItem(idControl), szControl, szConfiguration, nVariant);
}

template <class CWND> BOOL CResizableWnd<CWND>::
SaveControlPos(UINT idControl, LPCTSTR szControl, LPCTSTR szConfiguration, int nVariant)
{
  return SaveControlPos(GetDlgItem(idControl), szControl, szConfiguration, nVariant);
}

template <class CWND> BOOL CResizableWnd<CWND>::
LoadControlsLayout(UINT* pidControls, LPCTSTR szConfiguration, int nVariant)
{
  for(;*pidControls!=0; ++pidControls){
    if(!LoadControlPos(*pidControls, NULL, szConfiguration, nVariant))
      return FALSE;
  }
  return TRUE;
}

template <class CWND> BOOL CResizableWnd<CWND>::
SaveControlsLayout(UINT* pidControls, LPCTSTR szConfiguration, int nVariant)
{
  for(;*pidControls!=0; ++pidControls){
    if(!SaveControlPos(*pidControls, NULL, szConfiguration, nVariant))
      return FALSE;
  }
  return TRUE;
}

template <class CWND> BOOL CResizableWnd<CWND>::
DoSetControlPos(CWnd* pControl, LPCRECT prect, LPCRECT prectControl, LPCRECT prectParent)
{
  if(pControl==NULL)
    return FALSE;
  CRect rect = *prect;
	return pControl->SetWindowPos(NULL, rect.left, rect.top,
		rect.Width(), rect.Height(), SWP_NOACTIVATE | SWP_NOZORDER |
		SWP_NOREPOSITION);
}

template <class CWND> BOOL CResizableWnd<CWND>::
DoSetWindowPos(LPCRECT prect)
{
  CRect rect = *prect;
	return SetWindowPos(NULL, rect.left, rect.top,
		rect.Width(), rect.Height(), SWP_NOACTIVATE | SWP_NOZORDER |
		SWP_NOREPOSITION);
}

template <class CWND> BOOL CResizableWnd<CWND>::
DoSetWindowPlacement(WINDOWPLACEMENT* pwndpl)
{
	return SetWindowPlacement(pwndpl);
}


#endif // !defined(AFX_XCWND2_H__INCLUDED_)
