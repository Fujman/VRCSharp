#ifndef __XCRESDLG_H
#define __XCRESDLG_H
#include "xCResLoad.h"
#include "xCString.h"

////////////////////////////////////////////////////////////////////////////////////
// CResourceDialog

class CResourceDialog: public CDialog
{
public:
  CResourceDialog( LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL )
    :CDialog(lpszTemplateName,pParentWnd) {}
  CResourceDialog( UINT nIDTemplate, CWnd* pParentWnd = NULL )
    :CDialog(nIDTemplate, pParentWnd) {}
  CResourceDialog( )
    :CDialog() {}

  int             SetStdButtonText(UINT nID=IDOK, UINT nStdWordID=0/*wordIDOK*/);//AY 09.11.2010

  virtual CString GetStandardWord  (UINT nID, LPCTSTR pszDefault=NULL) = 0;//nID=IDOK,IDCANCEL,..IDHELP
  virtual CString GetResourceString(UINT nID, LPCTSTR pszDefault=NULL) = 0;
  virtual CFont*  GetResourceFont();

  int             DoInitStdButtons();
  int             DoInitStatics();
  int             DoInitResourceFont(BOOL bSetFont=TRUE, BOOL bRedraw=TRUE);

protected:
  CFont           m_fontResource;
};

inline int CResourceDialog::DoInitResourceFont(BOOL bSetFont, BOOL bRedraw) //MUST be inline for ResourceFont multilang support!
{
  if((HFONT)m_fontResource!=NULL)
    return 0;
  LOGFONT lf = {0};
//_tcscpy(lf.lfFaceName, ResourceFont(_T("Arial")));
  _tcscpy(lf.lfFaceName, ResourceFont(_T("Tahoma"))); //AY 09.11.2010
  _tcscpy(lf.lfFaceName, ResourceFont(_T("Arial Unicode MS"))); //AY 27.12.2010
  lf.lfHeight = -12;
  lf.lfCharSet = RUSSIAN_CHARSET;//TO DO?
  lf.lfCharSet = DEFAULT_CHARSET;//AY 27.12.2010
  BOOL bOK = m_fontResource.CreateFontIndirect(&lf);
  if(bSetFont)
    SetFont(&m_fontResource, bRedraw);
  return bOK?0:-1;
}

inline CFont* CResourceDialog::GetResourceFont()
{
  if((HFONT)m_fontResource==NULL)
    return 0;
  return &m_fontResource;
}

#endif//__XCRESDLG_H
