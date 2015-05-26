#include "stdafx.h"
#include "eventlog.h"
#include "xCString.h"
#include "FS/FileName.h"
#include "MathAlgo/ZipArchive/ZipArchive.h"

int YEventsProtocol::Resize(LPCTSTR szFileName, DWORD dwNewSize) {
  CString  szLogName;
  if(szFileName==NULL)
    szLogName = MakeLogName();
  else
    szLogName = szFileName;

  CFileName szPath = CFileName(szLogName).GetPath();
  if(szPath.IsEmpty()) {
    CString szCurPath;
    YFileSystem::GetCurrentDirectory(szCurPath);
    szLogName = CFileName(szCurPath).WithSlash()+szLogName;
  }
  //get temp file name
  TCHAR* szPre = _T("log");  
  TCHAR szTmpName[MAX_PATH+1];
  if(0 == ::GetTempFileName(CFileName(szLogName).GetPath(),szPre,0,szTmpName))
    return -1;

  HANDLE hFileTmp = NULL;
  //open source log file
  YEventsProtocol srcLog;
  if(srcLog.Open(szLogName,0)!=0) {
    try { ::DeleteFile(szTmpName);}
    catch(CException*) {}
    return -2; //"Error of log opening!"
  }

  int nPageSize = srcLog.GetPageSize();
  ASSERT(dwNewSize%nPageSize==0);
  if(0 != dwNewSize%nPageSize) {
    try { ::DeleteFile(szTmpName);}
    catch(CException*) {}
    return -3; // size error!
  }
  //calculate...
  int nSrcPages = 0;
  int nDstPages = 0;
  int nCopyPages= 0;

  ULONG nCurOffset = srcLog.m_nFirstPageOffset;
  for(nSrcPages=0;;) {
    ++nSrcPages;
    if(nCurOffset==srcLog.m_nWritePageOffset)
      break;
    nCurOffset  = srcLog.NextPageOffset(nCurOffset);
  }
  nDstPages = dwNewSize/nPageSize;
  nCopyPages  = min(nSrcPages,nDstPages);
  //create temp file
  try {
    hFileTmp = ::CreateFile(szTmpName,
                            GENERIC_WRITE |GENERIC_READ,
                            FILE_SHARE_READ/*0*/,NULL,
                            OPEN_ALWAYS|TRUNCATE_EXISTING,
                            FILE_ATTRIBUTE_NORMAL,
                            NULL);
    
    if(hFileTmp == INVALID_HANDLE_VALUE)
      return FALSE;
  }
  catch (CException*) {
    CloseHandle(hFileTmp); hFileTmp = NULL;
    srcLog.Close();
    ::DeleteFile(szTmpName);
    return -4; //error create/open temporary file
  }
  //prepare temp file
  BYTE*  pPage = NULL;
  try {
    pPage = new BYTE[nPageSize];
    for(int i=0; i<nPageSize; ++i)
      pPage[i] = 0;
    DWORD  nBytes;
    int nOffset;
    for(i=0,nOffset=0;i<nDstPages;++i,nOffset+=nPageSize) {
      DWORD dwPos = ::SetFilePointer(hFileTmp,nOffset,NULL,FILE_BEGIN);
      if(dwPos!=-1)
        ::WriteFile(hFileTmp,pPage,nPageSize,&nBytes,NULL);
      else throw;
    }
  }
  catch (CException*) {
    delete [] pPage;
    CloseHandle(hFileTmp); hFileTmp = NULL;
    srcLog.Close();
    ::DeleteFile(szTmpName);
    return -5; 
  }
  //get start position from source
  DWORD dwSrcCurPageOffset = srcLog.m_nFirstPageOffset;
  if(nSrcPages>nCopyPages) {
    int nPagesToOffset = nSrcPages - nCopyPages;
    for(int i=0;i<nPagesToOffset;++i) {
      dwSrcCurPageOffset  = srcLog.NextPageOffset(dwSrcCurPageOffset);
    }
  }
  //copy contents from source -> temp
  try {
    DWORD dwBytesWriten=0;
    for(int nPage=0,nOffset=0;nPage<nCopyPages;++nPage) {
      srcLog.GetPage(dwSrcCurPageOffset,pPage);
      DWORD dwPos = ::SetFilePointer(hFileTmp,nOffset,NULL,FILE_BEGIN);
      ::WriteFile(hFileTmp,pPage,nPageSize,&dwBytesWriten,NULL);
      dwSrcCurPageOffset  = srcLog.NextPageOffset(dwSrcCurPageOffset);
      nOffset = srcLog.NextPageOffset(nOffset);
    }
  }
  catch (CException*) {
    delete [] pPage;
    CloseHandle(hFileTmp); hFileTmp = NULL;
    srcLog.Close();
    ::DeleteFile(szTmpName);
    return -6;
  }
  //delete source
  srcLog.Close();
  try {
    ::DeleteFile(szLogName);
  }
  catch(CException*) {
    delete [] pPage;
    CloseHandle(hFileTmp); hFileTmp = NULL;
    return -7;
  }
  CloseHandle(hFileTmp); hFileTmp = NULL;
  //rename temp -> source
  try {
    ::MoveFile(szTmpName,szLogName);
  }
  catch(CException*) {
    delete [] pPage;
    ::DeleteFile(szTmpName);
  }
  delete [] pPage;
  return 0;
}