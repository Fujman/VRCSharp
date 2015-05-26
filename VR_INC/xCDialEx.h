#ifndef __XCDIALEX_H
#define __XCDIALEX_H
#include "xCDialog.h"

////////////////////////////////////////////////////////////////////////////////////
// CMultiLanguageDialogEx

template <class CDIALOG>
class CTheMultiLanguageDialogEx : public CDIALOG
{
protected://members
  HGLOBAL                       m_hDialogTemplate;
  HGLOBAL                       m_hDlgInitTemplate;//AY 06.05.2010
  CWnd*                         m_pParentWnd;
public://construction / destruction
  CTheMultiLanguageDialogEx( LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL )
    { 
      m_hDialogTemplate = GetTemplate(lpszTemplateName); 
      m_hDlgInitTemplate = GetTemplate(lpszTemplateName, RT_DLGINIT); 
      m_pParentWnd = pParentWnd; 
    }
  CTheMultiLanguageDialogEx( UINT nIDTemplate, CWnd* pParentWnd = NULL )
    { 
      m_hDialogTemplate = GetTemplate(nIDTemplate); 
      m_hDlgInitTemplate = GetTemplate(nIDTemplate, RT_DLGINIT); 
      m_pParentWnd = pParentWnd; 
    }
  CTheMultiLanguageDialogEx( )
    { 
      m_hDialogTemplate = NULL; 
      m_hDlgInitTemplate = NULL;
      m_pParentWnd = NULL; 
    }
  BOOL Create( LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL )
    { return CDIALOG::CreateIndirect(m_hDialogTemplate=GetTemplate(lpszTemplateName), m_pParentWnd=pParentWnd); }
  BOOL Create( UINT nIDTemplate, CWnd* pParentWnd = NULL )
    { return CDIALOG::CreateIndirect(m_hDialogTemplate=GetTemplate(nIDTemplate), m_pParentWnd=pParentWnd); }
  int  DoModal()
    { CDIALOG::InitModalIndirect(m_hDialogTemplate,m_pParentWnd); return CDialog::DoModal(); }
  //inherited//BOOL             InitModalIndirect(LPCDLGTEMPLATE lpDialogTemplate, CWnd* pParentWnd=NULL);
  //inherited//BOOL             InitModalIndirect(HGLOBAL hDialogTemplate, CWnd* pParentWnd=NULL);

  virtual BOOL OnInitDialog() //AY 06.05.2010
  { 
	  HGLOBAL hResource = m_hDlgInitTemplate;
  	LPVOID lpResource = LockResource(hResource);
	  // execute it
	  BOOL bResult = ExecuteDlgInit(lpResource);

	  // cleanup
	  if (lpResource != NULL && hResource != NULL)
	  {
		  UnlockResource(hResource);
		  FreeResource(hResource);
	  }
    BOOL bRet = CDIALOG::OnInitDialog();

    return bRet;
  }
public://helpers

  static HGLOBAL                GetTemplate(LPCTSTR lpszTemplate, LPCTSTR type=NULL/*RT_DIALOG*/)
                                  { return CTheMultiLanguageDialog::GetTemplate(lpszTemplate, type); }
  static HGLOBAL                GetTemplate(UINT nIDTemplate, LPCTSTR type=NULL/*RT_DIALOG*/)
                                  { return CTheMultiLanguageDialog::GetTemplate(MAKEINTRESOURCE(nIDTemplate), type); }
};

////////////////////////////////////////////////////////////////////////////////////
// CNoMultiLanguageDialogEx - CDialog mirror

template <class CDIALOG>
class CNoMultiLanguageDialogEx : public CDIALOG
{
public:
  CNoMultiLanguageDialogEx( LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL )
    :CDIALOG(lpszTemplateName,pParentWnd) {}
  CNoMultiLanguageDialogEx( UINT nIDTemplate, CWnd* pParentWnd = NULL )
    :CDIALOG(nIDTemplate, pParentWnd) {}
  CNoMultiLanguageDialogEx( )
    :CDIALOG() {}
  static HGLOBAL GetTemplate(LPCTSTR lpszTemplate, LPCTSTR type=NULL/*RT_DIALOG*/)
    { return NULL; }
  static HGLOBAL GetTemplate(UINT nIDTemplate, LPCTSTR type=NULL/*RT_DIALOG*/)
    { return NULL; }
};
 
////////////////////////////////////////////////////////////////////////////////////
// CMultiLanguageDialogEx

#ifdef MULTILANG
#  define  CMultiLanguageDialogEx CTheMultiLanguageDialogEx
#else//MULTILANG
#  define  CMultiLanguageDialogEx CNoMultiLanguageDialogEx
#endif

////////////////////////////////////////////////////////////////////////////////////

#endif __XCDIALEX_H
#pragma once
