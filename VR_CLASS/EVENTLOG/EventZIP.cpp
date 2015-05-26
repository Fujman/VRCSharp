#include "stdafx.h"
#include "eventlog.h"
#include "xCString.h"
#include "FS/FileName.h"
#include "MathAlgo/ZipArchive/ZipArchive.h"

int YEventsProtocol::Zip(LPCTSTR szFileName,LPCTSTR szZipName/*NULL*/) {
  CTime time = CTime::GetCurrentTime();
  CString szTime = time.Format("%Y-%m-%d.%H_%M_%S");
	
  CString  szLogName, szLogNameInZip;
  CString  szArchName;

  if(szFileName==NULL)
    szLogName = MakeLogName();
  else
    szLogName = szFileName;

  if(szZipName==NULL) 
    szArchName = CFileName(szLogName).GetBase()+"."+szTime+".LOZ";
  else 
    szArchName = szZipName;
  szLogNameInZip = CFileName(szLogName).GetName();
	
  if(!szLogNameInZip.IsEmpty()) {
	  CZipArchive zipArch;
	  BOOL bAfterException = FALSE;
    try {
		  zipArch.Open(szArchName, CZipArchive::zipCreate,0);
		  zipArch.AddNewFile(szLogName,szLogNameInZip,9);
	  }
	  catch(CException* e) {
		  e->Delete();
		  bAfterException = true;
	  }
	  zipArch.Close(bAfterException);
    return (bAfterException==FALSE)?0:-1; //0-ok,-1-error
  }	
  return -1;
}