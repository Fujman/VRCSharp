// SRSLogViewDoc.h : interface of the CSRSLogViewDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SRSLOGVIEWDOC_H__A5FF763C_C67E_4BC8_BF9A_719CB5E141F5__INCLUDED_)
#define AFX_SRSLOGVIEWDOC_H__A5FF763C_C67E_4BC8_BF9A_719CB5E141F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSRSLogViewDoc : public CDocument
{
protected: // create from serialization only
	CSRSLogViewDoc();
	virtual ~CSRSLogViewDoc();
	DECLARE_DYNCREATE(CSRSLogViewDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSRSLogViewDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual void SetTitle(LPCTSTR lpszTitle);
	//}}AFX_VIRTUAL

// Implementation
public:

protected:
	CString m_szOrLogFileName;//original log name (.LOZ)
  CString m_szLogFileName;  //unpacked name     (.LOG)
private:

public:
	CString GetLogFileName() const;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	virtual CFile* GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
		CFileException* pError);
protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSRSLogViewDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRSLOGVIEWDOC_H__A5FF763C_C67E_4BC8_BF9A_719CB5E141F5__INCLUDED_)
