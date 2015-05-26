//////////////////////////////////////////////////////////////////////////////
// yResLang.h
#ifndef __YRESLANG_H
#define __YRESLANG_H

//////////////////////////////////////////////////////////////////////////////
//emulated languages definitions
#define SUBLANG_ENGLISH_ARMENIAN 0x3E
//

//////////////////////////////////////////////////////////////////////////////
// C++ helpers

#ifdef  __cplusplus //application dependent! - ::AfxGetResourceHandle() used

WORD    LoadLanguageNameEx(WORD wLangID, CString& szResourceLangName);//return mapped wLangID //AY 15.12.2010
WORD    MapLanguageName(WORD wLangID, CString& szResourceLangName);   //return mapped wLangID //AY 15.12.2010

WORD    LoadLanguageName(WORD wLangID, CString& szResourceLangName);  //return mapped wLangID
BOOL    LoadString(CString& sz, UINT nID, WORD wLangID);
BOOL    InstallResourceFont(LPCTSTR szFont, WORD wLangID);
BOOL    UninstallResourceFont(LPCTSTR szFont, WORD wLangID);
#endif

/////////////////////////////////////////////////////////////////////////////
// Application language dependent resources support

#ifdef  __cplusplus
extern "C" {
#endif

BOOL    SetApplicationLanguageResourceModule(LPCTSTR szDLL, int nModule=0);//0-highest priority,15-lowest
BOOL    RemoveApplicationLanguageResourceModule(int nModule);//0-highest priority,15-lowest
LPCTSTR GetApplicationLanguageResourceModule(int nModule=0);//0-highest priority,15-lowest
BOOL    GetApplicationLanguageResourceModules(CStringArray& aszModules, const int* aPriorities=NULL, int nPriorities=0);//+NULL terminated
HMODULE GetApplicationLanguageResourceHandle(int nModule=0);//0-highest priority,15-lowest, -1-MFC
BOOL    GetApplicationLanguageResourceHandles(HMODULE* pModules, const int* aPriorities=NULL, int nPriorities=0);//+NULL terminated

WORD    GetApplicationUnicodedLanguageID();//application dependent! - ::AfxGetResourceHandle() used
WORD    GetApplicationEmulatedLanguageID();//application dependent! - ::AfxGetResourceHandle() used
WORD    GetApplicationLanguageID();
int     isApplicationLanguageIDDefined();
int     SetApplicationLanguageID(WORD wLangID);
int     PrepareApplicationLanguageID(WORD wLangID);//load resource fonts, tables, etc.

WORD    GetUnicodedLanguageID(WORD wEmulatedLangID);

UINT    GetApplicationLanguageCodePage(WORD wLang, char* acLang=NULL, LPCSTR* ppszCP=NULL); /*char[2] acLang*/ 
BOOL    SetApplicationLanguageLocale(WORD wLang=0); //AY 24.04.2013

#ifdef  __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////

inline WORD UniLanguage(WORD wLangID)
{
  if(wLangID==MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_ARMENIAN))
    return MAKELANGID(LANG_ARMENIAN,SUBLANG_DEFAULT);
  return wLangID;
}

#ifdef  __cplusplus
inline WORD MapLanguage(WORD wLangID)
{
  CString sz; return LoadLanguageName(wLangID, sz);
}
#endif//__cplusplus


#endif//__YRESLANG_H
#pragma once
