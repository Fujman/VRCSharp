// SRSLogViewDoc.cpp : implementation of the CSRSLogViewDoc class
//
#include "stdafx.h"
#include "SRSLogView.h"

#include "SRSLogViewDoc.h"

#include "FS/FileName.h"
#include "MathAlgo/ZipArchive/ZipArchive.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CSRSLogViewDoc
IMPLEMENT_DYNCREATE(CSRSLogViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CSRSLogViewDoc, CDocument)
	//{{AFX_MSG_MAP(CSRSLogViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSRSLogViewDoc construction/destruction
CSRSLogViewDoc::CSRSLogViewDoc() 
            :m_szLogFileName(""), m_szOrLogFileName("") 
{

}
//---------------------------------------
CSRSLogViewDoc::~CSRSLogViewDoc()
{}
//---------------------------------------
BOOL CSRSLogViewDoc::OnNewDocument() {
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CSRSLogViewDoc serialization
void CSRSLogViewDoc::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		// TODO: add storing code here
	}
	else {
		// TODO: add loading code here
	}
}
/////////////////////////////////////////////////////////////////////////////
// CSRSLogViewDoc diagnostics
#ifdef _DEBUG
void CSRSLogViewDoc::AssertValid() const {
	CDocument::AssertValid();
}
//-----------
void CSRSLogViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CSRSLogViewDoc commands
BOOL CSRSLogViewDoc::OnOpenDocument(LPCTSTR lpszPathName) {
  m_szOrLogFileName = lpszPathName;
  CFileName fnOrig = m_szOrLogFileName;
  if(fnOrig.GetExt().CompareNoCase(_T(".LOZ"))==0) {
    m_szLogFileName   = fnOrig.GetBase() + _T(".LOG");

    CZipArchive zipArch;
    BOOL bAfterException = FALSE;
    try {
      zipArch.Open(m_szOrLogFileName, CZipArchive::zipOpenReadOnly);
      TCHAR sz[MAX_PATH];
      ::GetTempPath(sizeof(sz)/sizeof(TCHAR),sz);
      CFileName szTemp = sz;
      if(szTemp.IsEmpty()) {
        zipArch.Close();
        return FALSE;
      }
      zipArch.ExtractFile(0,szTemp,false);
      CZipFileHeader fh;
      if(zipArch.GetFileInfo(fh,0))   {
        m_szLogFileName = szTemp.WithSlash() + fh.GetFileName();
      }
      else m_szLogFileName  = "";
    }
    catch(CException* e) {
      e->ReportError();
      e->Delete();
      bAfterException = true;
    }
	  zipArch.Close(bAfterException);
  }else{
    m_szLogFileName  = m_szOrLogFileName;
  }
	if (!CDocument::OnOpenDocument(m_szLogFileName))
		return FALSE;
	return TRUE;
}

CFile* CSRSLogViewDoc::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags, CFileException* pError) //AY 05.12.2007
{
  nOpenFlags &= ~CFile::shareDenyWrite;
  nOpenFlags |=  CFile::shareDenyNone;
  return CDocument::GetFile(lpszFileName, nOpenFlags, pError);
}

//---------------------------------------
void CSRSLogViewDoc::OnCloseDocument() {
  if(m_szOrLogFileName!=m_szLogFileName) {
    BOOL bDeleting = FALSE;
    try {
      bDeleting = ::DeleteFile(m_szLogFileName);
    }
    catch (CException* e) {
      e->ReportError();
      e->Delete();
    }
  }
  CDocument::OnCloseDocument();
}
//---------------------------------------
CString CSRSLogViewDoc::GetLogFileName() const {
  return m_szLogFileName;
}

void CSRSLogViewDoc::SetTitle(LPCTSTR lpszTitle) {
	CDocument::SetTitle(m_szLogFileName);
}
