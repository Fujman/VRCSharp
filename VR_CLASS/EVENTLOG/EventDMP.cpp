#include "stdafx.h"
#include "eventlog.h"
#include "xCFile.h"
#include "xCString.h"
#include "FS/FileName.h"

#ifndef  __XCFILE_CARCHIVE_OPERATOR_STRING_DEFINED
inline
CArchive& operator<<(CArchive& ar, LPCTSTR sz)
{
  ar.WriteString(sz);
  return ar;
}
#endif


int YEventsProtocol::Dump(LPCTSTR szFileName, LPCTSTR szDumpName/*NULL*/) {
  CTime time = CTime::GetCurrentTime();
  CString szTime = time.Format("%Y-%m-%d.%H_%M_%S");

  CString  szLogName;
  if(szFileName==NULL)
    szLogName = MakeLogName();
  else
    szLogName = szFileName;

  CString  szDmpName;
  if(szDumpName==NULL) 
    szDmpName = MakeLogDumpName(/*szLogName*/);
  else
    szDmpName = szDumpName;

  CString  szCopyName;
  if(szFileName==NULL)
    szCopyName = MakeLogName();

  if(szFileName==NULL && szDumpName==NULL) {
    CString szExt = szDmpName.Mid(szDmpName.GetLength()-4);
    szExt.MakeUpper();
    if(szExt==".DMP") {
      szDmpName = szDmpName.Left(szDmpName.GetLength()-4)
        + "."
        + szTime
        + szExt;
    }else{
      szDmpName += ".";
      szDmpName += szTime;
    }

    szExt = szCopyName.Mid(szCopyName.GetLength()-4);
    szExt.MakeUpper();
    if(szExt==".LOG") {
      szCopyName = szCopyName.Left(szCopyName.GetLength()-4)
        + "."
        + szTime
        + szExt;
    }else{
      szCopyName += "."; 
      szCopyName += szTime;
    }
    ::CopyFile(szLogName,szCopyName,FALSE);
  }
  if(szFileName!=NULL && szDumpName==NULL) {
    szDmpName = CFileName(szFileName).GetBase()+"."+szTime+".DMP";
  }
  if(szFileName!=NULL && szDumpName!=NULL) {
    szDmpName = szDumpName;
  }

  szDumpName = szDmpName; 

  #if defined(UNICODE) || defined(_UNICODE)
    HANDLE hFile = ::CreateFile(szLogName,0,FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,NULL,OPEN_EXISTING,FILE_FLAG_NO_BUFFERING | FILE_FLAG_SEQUENTIAL_SCAN,NULL);
    if(INVALID_HANDLE_VALUE == hFile) {
      ::CloseHandle(hFile);
      return -1;
    }
    ::CloseHandle(hFile);
    hFile = ::CreateFile(szLogName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,0);
    if(hFile==(HANDLE)HFILE_ERROR)
      return -2;
  #else
    OFSTRUCT ofsReOpen; ofsReOpen.cBytes = sizeof(ofsReOpen);
    HFILE hFile = ::OpenFile(szLogName,&ofsReOpen,OF_EXIST);
    if(hFile==HFILE_ERROR)
      return -1;
  
    hFile = ::OpenFile(szLogName,&ofsReOpen,OF_REOPEN|OF_READ);
    if(hFile==HFILE_ERROR)
      return -2;
  #endif

  CFile fileout(szDumpName,CFile::modeCreate|CFile::modeWrite);
  CArchive out(&fileout,CArchive::store);

  ULONG nFileSize = ::GetFileSize((HANDLE)hFile,NULL);
  ULONG nPages = nFileSize/GetPageSize();                  
  if((nFileSize%GetPageSize())!=0)
    return -3;

  BYTE*  pReadPage = new BYTE[GetPageSize()];


  for(ULONG nPage=0; nPage<nPages; ++nPage){
    DWORD nPos = ::SetFilePointer((HANDLE)hFile,nPage*GetPageSize(),NULL,FILE_BEGIN);
    if(nPos==-1)
      return -4;

    DWORD dwBytes;
    if(!::ReadFile((HANDLE)hFile,pReadPage,GetPageSize(),&dwBytes,NULL))
      return -5;

    out << (LPCTSTR)FormatString("*** PAGE #%u  offset=%u",nPage,nPage*GetPageSize());

    int isEmpty = 1;
    for(UINT n=0; n<(UINT)GetPageSize(); ++n){
      if(pReadPage[n]!=0)
        isEmpty = 0;
    }
    if(isEmpty) {
      out << "(empty)\n";
      continue;
    }

    YEvent64 ev((const void*)pReadPage,GetPageSize());
    if(ev.IsEmpty()) {
      out << "(empty)";
    }else{
      out << (LPCTSTR)FormatString("  number=%u  signature=%X",ev.GetData32(0),ev.GetData32(1));
    }
    out << "\n";

    DWORD nEventPos = GetPageHeaderSize();
    do{
      YEvent *pev = YEvent::Create(pReadPage+nEventPos,GetPageSize()-nEventPos);
      if(pev==NULL) {
        out << "*** BAD EVENT ***\n";
        break;
      }
      int isGood = pev->Validate();
      if(!isGood) {
        out << "invalid event\n";
        delete pev;
        break;
      }
      TCHAR sz[256];
      pev->GetText(sz,sizeof(sz));
      out << sz << "\n";
      nEventPos += pev->GetDataSize();
      delete pev;
    }while(nEventPos<(UINT)GetPageSize());
  }
  out.Close();
  fileout.Close();

  delete [] pReadPage;
  CloseHandle((HANDLE)hFile);

  return 0;
}

