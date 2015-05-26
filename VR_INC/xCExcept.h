/*---------------------------------------------------------------------------\
|  xCExcept.H                                  Last Change : 21.04.01 08:57  |
\---------------------------------------------------------------------------*/
#ifndef  __XCEXCEPT_H
#define  __XCEXCEPT_H

#ifndef _INC_STDLIB
#ifndef __STDLIB_H
#include <STDLIB.h>
#define __STDLIB_H
#endif/*__STDLIB_H*/
#endif/*_INC_STDLIB*/

#define ERR_FAILURE                     40000

/////////////////////////////////////////////////////////////////////////////
// Converting IOStream error codes to CFile exceptions
  int ThrowIosFileException(BOOL isSuccess=FALSE, int ios_eof=0);

  inline int ThrowIosFileException(BOOL isSuccess, int ios_eof) {
    if(isSuccess)
      return 0;
    if(ios_eof)
      ::AfxThrowFileException(CFileException::endOfFile);
    else
      CFileException::ThrowOsError(_doserrno);
    return 0;
  }

#ifdef _FILE_DEFINED
  inline int ThrowStdioFileException(FILE* f) {
    if(feof(f))
      AfxThrowFileException(CFileException::endOfFile);
    if(ferror(f))
      CFileException::ThrowOsError(_doserrno);
    return 0;
  }
#endif//FILE_DEFINED

/////////////////////////////////////////////////////////////////////////////
// Converting memory allocation errors to CMemory exceptions

  inline int ThrowMemoryException(BOOL isSuccess) {
    if(!isSuccess)
      ::AfxThrowMemoryException();
    return 0;
  }

///////////////////////////////////////////////////////////////////////////////
// Integer owerflow exceptions

  class COverflowException : public CMemoryException {
    DECLARE_DYNAMIC(COverflowException)
  public:
    COverflowException()                                   : CMemoryException(){}
    COverflowException(BOOL bAutoDelete)                   : CMemoryException(bAutoDelete){}
    COverflowException(BOOL bAutoDelete, UINT nResourceID) : CMemoryException(bAutoDelete,nResourceID){}
    virtual ~COverflowException()                          {}
  //virtual BOOL GetErrorMessage(LPTSTR lpszError, UINT nMaxError=256, PUINT pnHelpContext=NULL);
    static  int  Throw(BOOL isSuccess);
  };

  inline int ThrowOverflowException(BOOL isSuccess) {
    if(!isSuccess)
      COverflowException::Throw(isSuccess);
    return 0;
  }

/////////////////////////////////////////////////////////////////////////////
// Define common error exception
  int ThrowErrorException(BOOL isSuccess=FALSE, UINT idError=0, LPCTSTR szError=NULL);

  class CErrorException : public CException {
  public:
    CErrorException(const CErrorException& e);
    CErrorException(BOOL bAutoDelete=TRUE, UINT idError=0, LPCTSTR szError=NULL);
    virtual ~CErrorException();
    virtual BOOL GetErrorMessage(LPTSTR lpszError, UINT nMaxError=256, PUINT pnHelpContext=NULL);
  protected: // Implementation
    DECLARE_DYNAMIC(CErrorException)
    int     m_idError;// resource ID
    CString m_szError;
  };

  inline int ThrowErrorException(BOOL isSuccess, UINT idError, LPCTSTR szError) {
    if(!isSuccess)
      throw new CErrorException(TRUE,idError,szError);
    return 0;
  }

  #define THROW_ASSERT_MESSAGE(b,s) \
    ThrowErrorException((b),-1,FormatString(DEBUGPLACE("%s\n"),(s)))
  #define REPORT_ASSERT_MESSAGE(s) \
    { CErrorException e(FALSE,-1,FormatString("%hs(%d):%s\n",__FILE__,__LINE__,((s)==NULL?"":(s)))); e.ReportError(); }
/////////////////////////////////////////////////////////////////////////////
// Define default messages
  int  MessageOnErrorException(CErrorException *e);
  int  MessageOnMemoryException(CMemoryException *e = NULL);
  int  MessageOnFileException(const CFileException *e, LPCTSTR sFile=NULL,BOOL bRetryEnabled=FALSE);
  int  MessageOnFileException(int m_cause, LPCTSTR sFile=NULL,BOOL bRetryEnabled=FALSE);

/////////////////////////////////////////////////////////////////////////////
// Inline implementation
inline
  CErrorException::CErrorException(BOOL bAutoDelete, UINT idError/*0*/, LPCTSTR szError/*NULL*/)
    :CException(bAutoDelete)
  {
    m_idError = idError;
    if(szError!=NULL)
      m_szError = szError;
  }

inline
  CErrorException::CErrorException(const CErrorException& e)
    :CException(FALSE)
  {
    m_idError = e.m_idError;
    m_szError = e.m_szError;
  }

inline
  CErrorException::~CErrorException() { /*virtual*/
    ;
  }

inline CString ErrorPlaceString(LPCTSTR szFile, int nLine=0) {
    CString sz;
    if(nLine==0)
      sz = szFile;
    else
      sz.Format(_T("%s(%d)"),szFile,nLine);
    return sz;
  }
//usage: ErrorPlaceString(__FILE__,__LINE__);


///////////////////////////////////////////////////////////////////////////////
// OS dependent exceptions
#include "OS/OsBase.h"
#include "MM/MMBase.h"
#include "FS/FsBase.h"
///////////////////////////////////////////////////////////////////////////////

inline CString GetExceptionErrorMessage(const CException& ex)
{
  CException* e = const_cast<CException*>(&ex);
  CString sz;
  LPTSTR s = sz.GetBuffer(256);
  BOOL bRet = e->GetErrorMessage(s,255);
  sz.ReleaseBuffer();
  if(!bRet)
    return CString("");
  return sz;
}

inline CString GetExceptionErrorMessage(CException* e)
{
  return GetExceptionErrorMessage(*(const CException*)e);
}

#endif//__XCEXCEPT_H
#pragma once
