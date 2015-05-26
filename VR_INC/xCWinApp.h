#ifndef __XCWINAPP_H
#define __XCWINAPP_H

#include "yLocale.h"
#include "yResourc.h"

/////////////////////////////////////////////////////////////////////////////////
// common

inline CString CWinApp__GetModuleName()
{
  CString szAppFile(::AfxGetApp()->m_pszHelpFilePath);
  int nPos = szAppFile.ReverseFind('.');
  szAppFile = szAppFile.Left(nPos) + _T(".EXE");
  return szAppFile;
}

/////////////////////////////////////////////////////////////////////////////////
// localization

inline BOOL InitInstanceLocale(BOOL bForce=FALSE, BOOL bAutomatic=FALSE)
{
  if(bForce || !isApplicationLanguageIDDefined()) {
    WORD wLang = 0;
    int iRet = IDOK;
    if(!bAutomatic) { //manual
      CSelectLanguageDialog dlg;
      iRet  = dlg.DoDialog();
      wLang = dlg.GetLanguageID();
    }else{ //auto
      wLang = ::GetSystemDefaultLangID();
      if(wLang!=MAKELANGID(LANG_RUSSIAN,SUBLANG_DEFAULT) /*&&
         wLang!=MAKELANGID(LANG_UKRAINIAN,SUBLANG_DEFAULT)*/)
        wLang = MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT);
    }
    if(iRet==IDOK) {
      SetApplicationLanguageID(wLang);
      return TRUE;
    }else{
      return FALSE;
    }
  }
  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////
// Console support

DWORD CWinApp__RunConsole(LPCTSTR szExe, LPCTSTR szCmd, 
  int (*pfnCallBack)(char* szANSI, int nLength, void* pobj)=NULL, void* pObj=NULL,
  WORD wShowWindow=SW_HIDE);

/////////////////////////////////////////////////////////////////////////////////
// Version 
#pragma comment(lib, "version.lib")

inline CString CWinApp__GetVersionInfo(LPCTSTR szVariable=_T("FileVersion"), WORD wLanguage=0, WORD wCodePage=0, LPCTSTR szAppFile=NULL)
{
  CString szModuleFile;
  if(szAppFile==NULL)
    { szModuleFile = CWinApp__GetModuleName(); szAppFile = szModuleFile; }

  TCHAR szVersion[256] = _T("");
  DWORD dwHandle = 0;
  DWORD dwSize = ::GetFileVersionInfoSize((LPTSTR)(LPCTSTR)szAppFile,&dwHandle);
  BYTE* pBuffer = NULL;
  if(dwSize>0)
    pBuffer = new BYTE[dwSize];
  if(pBuffer!=NULL) {
    VERIFY( ::GetFileVersionInfo((LPTSTR)(LPCTSTR)szAppFile,dwHandle,dwSize,pBuffer) );
    // Structure used to store enumerated languages and code pages.
    struct LANGANDCODEPAGE{
      WORD wLanguage;
      WORD wCodePage;
    } *lpTranslate = NULL;
    UINT cbTranslate = 0;
    // Read the list of languages and code pages.
    VERIFY( ::VerQueryValue(pBuffer,
                  TEXT("\\VarFileInfo\\Translation"),
                  (LPVOID*)&lpTranslate,
                  &cbTranslate) );
    // Read the file description for each language and code page.
    for(unsigned i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ ) {
      TCHAR szSubBlock[256];
      wsprintf( szSubBlock, 
                TEXT("\\StringFileInfo\\%04x%04x\\%s"),
                lpTranslate[i].wLanguage,
                lpTranslate[i].wCodePage,
                szVariable);
      // Retrieve file description for language and code page "i".
      LPVOID pValue = NULL;
      UINT  cbBytes = 0;
      VERIFY( ::VerQueryValue(pBuffer,
                    szSubBlock,
                    &pValue, 
                    &cbBytes) );

      BOOL bLang = wLanguage==0 || wLanguage==lpTranslate->wLanguage;
      BOOL bPage = wCodePage==0 || wCodePage==lpTranslate->wCodePage;
      if(!bLang || !bPage)
        continue;
      if(!pValue)//AY 19.03.2008
        continue;

      if(cbBytes+sizeof(TCHAR) <= sizeof(szVersion))
        _tcscpy(szVersion,(LPCTSTR)pValue);
      else
        ASSERT(!_T("buffer too small for store version!"));

      if(bLang && bPage)
        break;
    }
    delete pBuffer;
  }
  return szVersion;
}


inline CString CWinApp__GetModuleVersion(LPCTSTR szAppFile=NULL)
{
  CString szVersion = CWinApp__GetVersionInfo(_T("FileVersion"), 0, 0, szAppFile);
  szVersion.Replace(_T(", "),_T("."));
  return szVersion;
}

inline CString CWinApp__GetModuleLicense(LPCTSTR szAppFile=NULL)
{
  CString sz = CWinApp__GetVersionInfo(_T("SpecialBuild"), 0, 0, szAppFile);
  CString szLicense;
  for(LPCTSTR s=sz; *s; ++s) {
    if     (s[0]=='\\' && s[1]=='r')
      { szLicense += _T('\r'); ++s; }
    else if(s[0]=='\\' && s[1]=='n')
      { szLicense += _T('\n'); ++s; }
    else if(s[0]=='\\' && s[1]=='t')
      { szLicense += _T('\t'); ++s; }
    else if(s[0]=='\\' && s[1]=='\\')
      { szLicense += _T('\\'); ++s; }
    else
      szLicense += s[0];
  }
  return szLicense;
}


/////////////////////////////////////////////////////////////////////////////////
// CmdLine (obsolete, see xCCmdLine.h)

inline CString CWinApp__GetCmdLineUpperCase()
{
  CString szCmdLine = ::AfxGetApp()->m_lpCmdLine; szCmdLine.MakeUpper(); return szCmdLine;
}

inline BOOL CWinApp__GetCmdLineFlag(LPCTSTR szKey, BOOL bDef=FALSE, const CString* pszUpperCmdLine=NULL)
{
  CString szCmdLine = pszUpperCmdLine? *pszUpperCmdLine : CWinApp__GetCmdLineUpperCase();
  int iPos = szCmdLine.Find(szKey);
  if(iPos>=0)
    return TRUE;
  return bDef;
}

inline int CWinApp__GetCmdLineInt(LPCTSTR szKey, int iDef=0, const CString* pszUpperCmdLine=NULL)
{
  CString szCmdLine = pszUpperCmdLine? *pszUpperCmdLine : CWinApp__GetCmdLineUpperCase();
  int iPos = szCmdLine.Find(szKey);
  if(iPos>=0)
    return _ttoi( LPCTSTR(szCmdLine) + iPos + _tcslen(szKey) );
  return iDef;
}

inline CString CWinApp__GetCmdLineString(LPCTSTR szKey, int iDef=0, const CString* pszUpperCmdLine=NULL)
{
  CString szCmdLine = pszUpperCmdLine? *pszUpperCmdLine : CWinApp__GetCmdLineUpperCase();
  CString szRet;

  int iPos = szCmdLine.Find(szKey);
  if(iPos<0)
    return szRet;

  LPCTSTR szBeg = LPCTSTR(szCmdLine) + iPos + _tcslen(szKey);
  LPCTSTR szEnd = szBeg;
  if(!*szBeg || _istspace(*szBeg))
    return szRet;

  TCHAR cQuote = _T('\"');
  TCHAR cSlash = _T('\\');
  if(*szBeg==cQuote ){
    ++szBeg;
    ++szEnd;
    for(; *szEnd && *szEnd!=cQuote; ++szEnd){
      if(szEnd[0]==cSlash && szEnd[1]==cQuote)
        ++szEnd;
    }
  }else{
    for(; *szEnd && !_istspace(*szEnd); ++szEnd)
      ;
  }
  szRet = CString(szBeg,szEnd-szBeg);
  return szRet;
}



#endif//__XCWINAPP_H
#pragma once
