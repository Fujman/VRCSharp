#ifndef __XCDIALOG_H
#define __XCDIALOG_H
#include "xCResLoad.h"
#include "xCResDlg.h"
#include "xCString.h"
#include "xCMessage.h"

////////////////////////////////////////////////////////////////////////////////////
// CDialog extensions

int    CDialog__YieldModal(CWnd* pWnd, BOOL bPump=TRUE);

////////////////////////////////////////////////////////////////////////////////////
// CTheMultiLanguageDialog
#ifdef MULTILANG

class CTheMultiLanguageDialog : public CResourceDialog
{
protected://members
  HGLOBAL                       m_hDialogTemplate;
  HGLOBAL                       m_hDlgInitTemplate;//AY 05.05.2010
  CWnd*                         m_pParentWnd;
  BOOL                          m_bAnotherLanguage;//AY 21.06.2012
public://construction / destruction
  CTheMultiLanguageDialog( LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL )
    { 
      m_hDialogTemplate  = __GetTemplate(lpszTemplateName); 
      m_hDlgInitTemplate = __GetTemplate(lpszTemplateName, RT_DLGINIT); 
      m_pParentWnd = pParentWnd; 
    }
  CTheMultiLanguageDialog( UINT nIDTemplate, CWnd* pParentWnd = NULL )
    { 
      m_hDialogTemplate  = __GetTemplate(nIDTemplate); 
      m_hDlgInitTemplate = __GetTemplate(nIDTemplate, RT_DLGINIT); 
      m_pParentWnd = pParentWnd;
    }
  CTheMultiLanguageDialog( )
    { 
      m_bAnotherLanguage = FALSE; 
      m_hDialogTemplate = NULL; 
      m_hDlgInitTemplate = NULL;
      m_pParentWnd = NULL;
    }
  BOOL Create( LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL )
    { return CDialog::CreateIndirect(m_hDialogTemplate=GetTemplate(lpszTemplateName), m_pParentWnd=pParentWnd); }
  BOOL Create( UINT nIDTemplate, CWnd* pParentWnd = NULL )
    { return CDialog::CreateIndirect(m_hDialogTemplate=GetTemplate(nIDTemplate), m_pParentWnd=pParentWnd); }
  int  DoModal()
    { CDialog::InitModalIndirect(m_hDialogTemplate,m_pParentWnd); return CDialog::DoModal(); }
  //inherited//BOOL             InitModalIndirect(LPCDLGTEMPLATE lpDialogTemplate, CWnd* pParentWnd=NULL);
  //inherited//BOOL             InitModalIndirect(HGLOBAL hDialogTemplate, CWnd* pParentWnd=NULL);

  virtual BOOL OnInitDialog() //AY 05.05.2010
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
    BOOL bRet = CDialog::OnInitDialog();

    DoInitStatics();

    return bRet;
  }
protected://helpers
  HGLOBAL                       __GetTemplate(LPCTSTR lpszTemplate, LPCTSTR type=NULL/*RT_DIALOG*/) { 
                                    int     iErr = 0; 
                                    HGLOBAL hRet = GetTemplate(lpszTemplate, type, &iErr);
                                    m_bAnotherLanguage = (hRet!=NULL && iErr==ERROR_IS_SUBSTED);
                                    return hRet;
                                  }
  HGLOBAL                       __GetTemplate(UINT     nIDTemplate, LPCTSTR type=NULL/*RT_DIALOG*/) { 
                                    int     iErr = 0; 
                                    HGLOBAL hRet = GetTemplate( nIDTemplate, type, &iErr);
                                    m_bAnotherLanguage = (hRet!=NULL && iErr==ERROR_IS_SUBSTED);
                                    return hRet;
                                  }
public://helpers
  static HGLOBAL                GetTemplate(LPCTSTR lpszTemplate, LPCTSTR type=NULL/*RT_DIALOG*/, int* pError=NULL)
                                  { return LoadMultilanguageDialogTemplate(lpszTemplate, type, pError); }
  static HGLOBAL                GetTemplate(UINT     nIDTemplate, LPCTSTR type=NULL/*RT_DIALOG*/, int* pError=NULL)
                                  { return LoadMultilanguageDialogTemplate( nIDTemplate, type, pError); }

  virtual CString               GetResourceString(UINT nID, LPCTSTR pszDefault=NULL)
                                  { return CString__MessageToString(ResourceMessage(nID,pszDefault)); }
  virtual CString               GetStandardWord  (UINT nID, LPCTSTR pszDefault=NULL)
                                  { return CStdString::GetStdText(nID); }
};
#endif//MULTILANG

////////////////////////////////////////////////////////////////////////////////////
// CNoMultiLanguageDialog

class CNoMultiLanguageDialog : public CResourceDialog
{
public:
  CNoMultiLanguageDialog( LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL )
    :CResourceDialog(lpszTemplateName,pParentWnd) {}
  CNoMultiLanguageDialog( UINT nIDTemplate, CWnd* pParentWnd = NULL )
    :CResourceDialog(nIDTemplate, pParentWnd) {}
  CNoMultiLanguageDialog( )
    :CResourceDialog() {}

  static HGLOBAL GetTemplate(LPCTSTR lpszTemplate, LPCTSTR type=NULL/*RT_DIALOG*/, int* pError=NULL)
    { return NULL; }
  static HGLOBAL GetTemplate(UINT nIDTemplate, LPCTSTR type=NULL/*RT_DIALOG*/, int* pError=NULL)
    { return NULL; }

  virtual CString               GetResourceString(UINT nID, LPCTSTR pszDefault=NULL)
                                  { return __ResourceString__(nID,pszDefault); }
  virtual CString               GetStandardWord  (UINT nID, LPCTSTR pszDefault=NULL)
                                  { return CStdString::GetStdText(nID); }
};  

////////////////////////////////////////////////////////////////////////////////////
// CMultiLanguageDialog
#ifdef MULTILANG //AY 06.05.2010
#define  CMultiLanguageDialog CTheMultiLanguageDialog
#else
#define  CMultiLanguageDialog CNoMultiLanguageDialog
#endif

 
////////////////////////////////////////////////////////////////////////////////////
// CEmptyDialog
#include <afxpriv.h>
class CEmptyDialog : public CMultiLanguageDialog
{
public:
  struct DLGTEMPLATEEX
  {
    WORD dlgVer; 
    WORD signature; 
    DWORD helpID;       /*typedef struct {          */
    DWORD exStyle;      /*    DWORD style;          */
    DWORD style;        /*    DWORD dwExtendedStyle;*/
    WORD cDlgItems;     /*    WORD cdit;            */
    short x;            /*    short x;              */
    short y;            /*    short y;              */
    short cx;           /*    short cx;             */
    short cy;           /*    short cy;             */
    WCHAR menu;         /*} DLGTEMPLATE;            */
    WCHAR windowClass; 
    WCHAR title; 
    short pointsize; 
    short weight; 
    short bItalic; 
    WCHAR font;
  }; 
  enum                  { MAX_FONT_LENGTH=127 };//wchar_t
protected:
  BOOL                  m_isInitModalIndirect;//27.12.02 VEN
  CRect                 m_rcInitModalIndirect;
  struct {
    union {
      DLGTEMPLATE         m_DlgTmp;  //27.12.02 VEN
      DLGTEMPLATEEX       m_DlgTmpEx;//AY 12.02.2010
    };
    wchar_t             m_buffer[(MAX_FONT_LENGTH+1)];//AY 12.02.2010 OLD: BYTE m_buffer[256]
  };

public://Template independent creation
                        CEmptyDialog();
                        ~CEmptyDialog();//28.12.02 VEN
                    
                      //DO NOT USE DS_CONTROL style!!!//19.02.2003 VEN
  BOOL                  Create(DWORD style=WS_VISIBLE|WS_CHILD, DWORD dwExtendedStyle=0, LPCRECT lpRect=NULL, CWnd* pParentWnd=NULL);
//BOOL                  Create(DWORD style=WS_OVERLAPPEDWINDOW, DWORD dwExtendedStyle=0, LPCRECT lpRect=NULL, CWnd* pParentWnd=NULL);
  BOOL                  InitModal(DWORD style=WS_POPUPWINDOW, DWORD dwExtendedStyle=0, LPCRECT lpRect=NULL, CWnd* pParentWnd=NULL);
  BOOL                  ReCreate(CWnd* pStatic);//WS_CHILD //19.02.2003 VEN
  BOOL                  ReCreate(const CRect& rc, CWnd* pParentWnd=NULL, DWORD style=WS_CHILD, DWORD dwExtendedStyle=0); //19.02.2003 VEN - remove style DS_CONTROL
  int                   DoModal();//27.12.02 VEN

public://Template dependent creation
                        CEmptyDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd=NULL);
                        CEmptyDialog(UINT nIDTemplate, CWnd* pParentWnd=NULL);
  //inherited//         Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd=NULL);
  //inherited//         Create(UINT nIDTemplate, CWnd* pParentWnd=NULL);
  //inherited//int      DoModal()
  //inherited//BOOL     InitModalIndirect(LPCDLGTEMPLATE lpDialogTemplate, CWnd* pParentWnd=NULL);
  //inherited//BOOL     InitModalIndirect(HGLOBAL hDialogTemplate, CWnd* pParentWnd=NULL);
  virtual BOOL          OnInitDialog();
protected:
  virtual void          OnOK();
  virtual void          OnCancel();
public:
  static CString        GetStdText(int nCtrlID=IDOK, int nType=0) 
                          { return CStdString::GetStdText(nCtrlID, nType); }//AY 06.05.2010

  static BOOL           CalcLayout(CRect rcClient, CRect* rcButtons, int mbType=MB_OK, int nDisp=WMSZ_BOTTOM);//TRUE-all visible
  static  CRect         CalcWindow(int nX=33/*%*/, int nY=33/*%*/, LPCRECT lpRect=NULL, CWnd* pParentWnd=NULL, BOOL bCenter=FALSE, DWORD dwStyle=0, DWORD dwExStyle=0);
  virtual CRect         CalcWindow(DWORD dwStyle, DWORD dwExStyle, LPCRECT lpRect, CWnd* pParentWnd);
};


class CEmptyDialogEx: public CEmptyDialog
{
public:
                        CEmptyDialogEx();

	BOOL                  Create(DWORD style=WS_VISIBLE|WS_CHILD, DWORD dwExtendedStyle=0, LPCRECT lpRect=NULL, CWnd* pParentWnd=NULL);
};


////////////////////////////////////////////////////////////////////////////////////
// CMultyChooseDialog
class CMultyChooseDialog : public CEmptyDialog
{
public:
  enum                  { MAX_ALTERNATIVES = 16, FIRST_RADIO = 1000};
public:
                        CMultyChooseDialog(LPCTSTR szMessages, LPCTSTR szOkCancel, UINT nIDHelp = 0);
                         ~CMultyChooseDialog();   
  BOOL                  InitModal(DWORD style=WS_POPUPWINDOW, DWORD dwExtendedStyle=0, LPCRECT lpRect=NULL, CWnd* pParentWnd=NULL);

  int                   m_nChosen;
protected:// Implementation
  BOOL                  m_bIsMultyLine;
  HLOCAL                m_hLocal;
  int                   m_nNum;//number of messages
  CFont*                m_pFont;

  CStatic*              m_pstat;
  CButton*              m_pbutton[MAX_ALTERNATIVES];
  CButton*              m_pOK;
  CButton*              m_pCancel;

  BYTE*                 m_pBuffer;//03.01.03VEN 
  CStringArray          m_aszMessages;
  CStringArray          m_aszButtonNames;
  // Generated message map functions
  //{{AFX_MSG(CThreeChooseDialog)
  //}}AFX_MSG
  afx_msg int           OnCreate(LPCREATESTRUCT lpCreateStruct);
  virtual BOOL          OnInitDialog();
  afx_msg void          OnOk();
  afx_msg void          OnRadioAny(UINT nRadio);
  DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////////////
// CEmptyAnyDialog<CDialog>
template <class CDIALOG>
class CEmptyAnyDialog : public CDIALOG
{
public:
  typedef CEmptyDialog::DLGTEMPLATEEX DLGTEMPLATEEX;
  enum                  { MAX_FONT_LENGTH=127 };//wchar_t

protected:
  BOOL                  m_isInitModalIndirect;
  CRect                 m_rcInitModalIndirect;
  struct {
    union {
      DLGTEMPLATE       m_DlgTmp;  //27.12.02 VEN
      DLGTEMPLATEEX     m_DlgTmpEx;//AY 12.02.2010
    };
    wchar_t             m_buffer[(MAX_FONT_LENGTH+1)];//AY 12.02.2010 OLD: BYTE m_buffer[256]
  };

public://Template independent creation
                        CEmptyAnyDialog();
                        ~CEmptyAnyDialog();
                    
                        //DO NOT USE DS_CONTROL style!!!
  BOOL                  Create(DWORD style=WS_VISIBLE|WS_CHILD, DWORD dwExtendedStyle=0, LPCRECT lpRect=NULL, CWnd* pParentWnd=NULL);
//BOOL                  Create(DWORD style=WS_OVERLAPPEDWINDOW, DWORD dwExtendedStyle=0, LPCRECT lpRect=NULL, CWnd* pParentWnd=NULL);
  BOOL                  InitModal(DWORD style=WS_POPUPWINDOW, DWORD dwExtendedStyle=0, LPCRECT lpRect=NULL, CWnd* pParentWnd=NULL);
  BOOL                  ReCreate(CWnd* pStatic);//WS_CHILD
  BOOL                  ReCreate(const CRect& rc, CWnd* pParentWnd=NULL, DWORD style=WS_CHILD, DWORD dwExtendedStyle=0); //19.02.2003 VEN - remove style DS_CONTROL
  int                   DoModal();

public://Template dependent creation
                        CEmptyAnyDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd=NULL);
                        CEmptyAnyDialog(UINT nIDTemplate, CWnd* pParentWnd=NULL);
  //inherited//         Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd=NULL);
  //inherited//         Create(UINT nIDTemplate, CWnd* pParentWnd=NULL);
  //inherited//int      DoModal()
  //inherited//BOOL     InitModalIndirect(LPCDLGTEMPLATE lpDialogTemplate, CWnd* pParentWnd=NULL);
  //inherited//BOOL     InitModalIndirect(HGLOBAL hDialogTemplate, CWnd* pParentWnd=NULL);
  virtual BOOL          OnInitDialog();
};

////////////////////////////////////////////////////////////////////////////////////

#include "xCDialog.inl"

#endif __XCDIALOG_H
#pragma once
