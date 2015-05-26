//UNICODE
#ifndef __YINIFILE_H
#define __YINIFILE_H
#include "fs/YFileIni.h"
#include "os/OsBase.h"
#include "fs/FsBase.h"

///////////////////////////////////////////////////////////////////////////////
// YIniFile

#ifndef YINIFILE_DEFINED
#define YINIFILE_DEFINED
typedef YFileIni<YFile> YIniFile;
#endif//YINIFILE_DEFINED

inline DWORD __GetPrivateProfileString
(
  LPCTSTR lpAppName,        // section name
  LPCTSTR lpKeyName,        // key name
  LPCTSTR lpDefault,        // default string
  LPTSTR  lpReturnedString, // destination buffer
  DWORD   nSize,            // size of destination buffer
  LPCTSTR lpFileName        // initialization file name
){
  ASSERT(lpKeyName!=NULL && lpAppName!=NULL);//TO DO
  DWORD nLength = 0;
  DWORD nRetSize = 0;
  CString sz;
  int iRet = 0;
  try 
  { 
    YIniFile file(lpFileName);
    sz = file.GetProfileString(lpAppName,lpKeyName,lpDefault);
  }
  catch(CFsException* e) { iRet = e->GetErrorOsCode(); iRet=iRet?iRet:-1; e->Delete(); }
  catch(COsException* e) { iRet = e->GetErrorOsCode(); iRet=iRet?iRet:-1; e->Delete(); }
  catch(CException* e)   { e->Delete(); iRet = -1; }

  if(iRet==0) {
    nLength = sz.GetLength();
    if(nLength<=nSize){ //success, \0 don't copied!

      memcpy(lpReturnedString,LPCTSTR(sz),nLength*sizeof(TCHAR));
      nRetSize = nLength;

      if(nLength<nSize) //robust extension
        lpReturnedString[nLength] = '\0';

    }else if(lpAppName!=NULL && lpKeyName!=NULL){ //error, force \0 at end

      if(nSize>=2) {
        memcpy(lpReturnedString,LPCTSTR(sz),(nSize-1)*sizeof(TCHAR));
        lpReturnedString[nSize-1] = _T('\0');
      }else if(nSize==1){
        lpReturnedString[0] = _T('\0');
      }
      nRetSize = nSize-1;

    }else if(lpAppName==NULL || lpKeyName==NULL) { //error, force \0\0 at end

      if(nSize>=3) {
        memcpy(lpReturnedString,LPCTSTR(sz),(nSize-2)*sizeof(TCHAR));
        lpReturnedString[nSize-2] = _T('\0');
        lpReturnedString[nSize-1] = _T('\0');
      }else if(nSize==2){
        lpReturnedString[0] = _T('\0');
        lpReturnedString[1] = _T('\0');
      }else if(nSize==1){
        lpReturnedString[0] = _T('\0');//? TO DO: check?
      }
      nRetSize = nSize-2;

    }
    ::SetLastError(0);
  }

  if(iRet)
    ::SetLastError(iRet);

  return iRet?0:nRetSize;
}

//CString  GetProfileString(LPCTSTR szSection, LPCTSTR szKeyName, LPCTSTR szDefault=NULL) const;
//int      SetProfileString(LPCTSTR szSection, LPCTSTR szKeyName, LPCTSTR szValue);

inline BOOL __WritePrivateProfileString
(
  LPCTSTR lpAppName,  // section name
  LPCTSTR lpKeyName,  // key name
  LPCTSTR lpString,   // string to add
  LPCTSTR lpFileName  // initialization file
){
  ASSERT(lpKeyName!=NULL && lpAppName!=NULL);//TO DO
  int iRet = 0;
  try 
  { 
    YIniFile file(lpFileName);
    iRet = file.SetProfileString(lpAppName,lpKeyName,lpString);
  }
  catch(CFsException* e) { iRet = e->GetErrorOsCode(); iRet=iRet?iRet:-1; e->Delete(); }
  catch(COsException* e) { iRet = e->GetErrorOsCode(); iRet=iRet?iRet:-1; e->Delete(); }
  catch(CException* e)   { e->Delete(); iRet = -1; }
  if(iRet)
    ::SetLastError(iRet);
  return iRet==0;
}



#endif//__YINIFILE_H
#pragma once