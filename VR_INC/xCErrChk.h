#ifndef __XCERRCHK_H
#define __XCERRCHK_H

#ifdef _DEBUG
  #define REPORT_ERROR(e)   ((e)->ReportError())
#else
  #define REPORT_ERROR(e)
#endif

#define  OSCHECK(bSuccess)       ::ThrowOsException(bSuccess)          //throw COsException
#define  DXCHECK(hresult)        ::ThrowDXException(SUCCEEDED(hresult))//throw CDXException
#define  MMCHECK(mmresult)       ::ThrowMMSystemException(mmresult)    //throw CMMSystemException
#define  STDIOCHECK(pFILE)       ::ThrowStdioFileException(pFILE)      //throw CFileException
#define  IOSCHECK(bSuccess,bEOF) ::ThrowIosFileException(bSuccess,bEOF)//throw CFileException
#define  MEMCHECK(bSuccess)      ::ThrowMemoryException(b)             //throw CMemoryException
#define  ERRCHECK(bSuccess)      ::ThrowErrorException(b)              //throw CErrorException

#define  OSCATCH(r)   catch(COsException* e) { REPORT_ERROR(e); e->Delete(); return (r);}
#define  MMCATCH(r)   catch(CMMSystemException* e) { REPORT_ERROR(e); e->Delete(); return (r);}
#define  DXCATCH(r)   catch(CDXException* e) { REPORT_ERROR(e); e->Delete(); return (r);}
#define  IOCATCH(r)   catch(CFileException* e) { REPORT_ERROR(e); e->Delete(); return (r);} 
#define  MEMCATCH(r)  catch(CMemoryException* e) { REPORT_ERROR(e); e->Delete(); return (r);}
#define  ERRCATCH(r)  catch(CException* e) { REPORT_ERROR(e); e->Delete(); return (r);}

#define  OSNOTIFY()   catch(COsException* e) { REPORT_ERROR(e); e->Delete(); }
#define  MMNOTIFY()   catch(CMMSystemException* e) { REPORT_ERROR(e); e->Delete(); }
#define  DXNOTIFY()   catch(CDXException* e) { REPORT_ERROR(e); e->Delete(); }
#define  IONOTIFY()   catch(CFileException* e) { REPORT_ERROR(e); e->Delete(); } 
#define  MEMNOTIFY()  catch(CMemoryException* e) { REPORT_ERROR(e); e->Delete(); }
#define  ERRNOTIFY()  catch(CException* e) { REPORT_ERROR(e); e->Delete(); }

#define  OSREPORT()   catch(COsException* e) { REPORT_ERROR(e); throw; }
#define  MMREPORT()   catch(CMMSystemException* e) { REPORT_ERROR(e); throw; }
#define  DXREPORT()   catch(CDXException* e) { REPORT_ERROR(e); throw; }
#define  IOREPORT()   catch(CFileException* e) { REPORT_ERROR(e); throw; } 
#define  MEMREPORT()  catch(CMemoryException* e) { REPORT_ERROR(e); throw; }
#define  ERRREPORT()  catch(CException* e) { REPORT_ERROR(e); throw; }

inline CString FormatErrorString(CException* e, LPCTSTR lpszFormat/*NULL*/, ... ) {
  // Get error message
  CString szMessage; e->GetErrorMessage(szMessage.GetBuffer(512),512);
  if(lpszFormat==NULL)
    return szMessage;
  // Format error string
  CString sz;
  va_list args;
  va_start(args, lpszFormat);
  sz.FormatV(lpszFormat, args);
  for(int iPos=0; (iPos=sz.Find(_T("%m"),iPos))>=0; ) {
    if(iPos>0 && sz[iPos-1]=='%') // check %%
      { iPos += 2; continue; }
    sz = sz.Left(iPos) + szMessage + sz.Mid(iPos+2);
    iPos += szMessage.GetLength();
  }
  return(sz);
}

#ifdef _DEBUG
  #define  TRACE_EXCEPTION(e) TRACE(DEBUGPLACE("exception : %s\r\n"),FormatErrorString(e,NULL))
#else
  #define  TRACE_EXCEPTION(e) (0)
#endif

#endif// __XCERRCHK_H
#pragma once