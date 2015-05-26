#ifndef __XCSTRING_H
#define __XCSTRING_H
#include "xCResLoad.h"
#include "xdebug.h"
#include "c_string.h"
#include "xstring.h"
#include "xunicod.h"

////////////////////////////////////////////////////////////////////////////////////

#ifdef  MULTILANG
#define MULTILANGSTRINGS   1
#endif

#ifdef  MULTILANGSTRINGS
  #ifndef __MESSAGE_STRINGS_SUPPORT      //use #define ... 0 in stdafx.h to disable
  #define __MESSAGE_STRINGS_SUPPORT    1
  #endif
#endif

//#undef  __MESSAGE_STRINGS_SUPPORT      //AY 01.06.2010 //AY 30.06.2010 commented
//#define __NO_ANSI_TO_UNICODE_SUPPORT 1 //debug

#ifdef _UNICODE
#define IS_CSTRING_UNICODE 1
#define _NULLA
#define _NULLW =NULL
#else
#undef  IS_CSTRING_UNICODE
#define _NULLA =NULL
#define _NULLW
#endif

////////////////////////////////////////////////////////////////////////////////////
// CString resource oriented extensions

//macro   RESOURCE_STRING(lpszVariableName,ID,lpszDefaultValue)
//macro   RESOURCE_ASSERT(condition)

CString __ResourceString(UINT nID, const wchar_t* psz _NULLW);//AY 25.05.2010 // no messages search, strings only
CString __ResourceString(UINT nID, const char*    psz _NULLA);//AY 25.05.2010 // no messages search, strings only
CString   ResourceString(UINT nID, const wchar_t* psz _NULLW);//AY 25.05.2010
CString   ResourceString(UINT nID, const char*    psz _NULLA);//AY 25.05.2010

CString   ResourceFont(LPCTSTR szFont=NULL);
BOOL      ResourceFontW(LPCTSTR szFontName, wchar_t* pwz, int nMaxLen); //AY 06.05.2010

////////////////////////////////////////////////////////////////////////////////////
// CString formatting extensions

CString FormatResourceString(UINT nID, const char* lpszFormat=NULL, ... );
CString FormatString(LPCTSTR lpszFormat, ... );

CString FormatErrorString(DWORD dwErr, LPCTSTR lpszFormat=NULL, ... );
CString FormatErrorString(LPCTSTR lpszFormat=NULL, ... );

////////////////////////////////////////////////////////////////////////////////////
// CString text processing extensions

CString CString__GetTextLine(const CString& sz, int nLine, LPCTSTR szDelimiters=NULL); //NULL is \r\n
CString CString__Distille(LPCTSTR szSource, LPCTSTR szBeg, LPCTSTR szEnd=NULL);
int     CString__CompareNoCase(const CString& sz1, const CString& sz2, WORD wLangID=0);//AY 16.12.2009

CString& CString__MessageToString(CString& sz); //AY 29.03.2010
CString CString__MenuToString(LPCTSTR szSource);//AY 09.11.2010

//AY 06.05.2010
int     CString__W2A(LPCWSTR wz, LPSTR  paz, int nMaxLen);
int     CString__A2W(LPCSTR  az, LPWSTR pwz, int nMaxLen);

int     CString__T2A(LPCTSTR sz, LPSTR  paz, int nMaxLen);
int     CString__T2W(LPCTSTR sz, LPWSTR pwz, int nMaxLen);

int     CString__A2A(LPCSTR  az, LPSTR  paz, int nMaxLen);
int     CString__W2W(LPCWSTR wz, LPWSTR pwz, int nMaxLen);
int     CString__T2T(LPCTSTR sz, LPTSTR pwz, int nMaxLen);
//YA

////////////////////////////////////////////////////////////////////////////////////
// LoadMultilanguageResourceMessageString implementation

#if defined(MULTILANGSTRINGS) && __MESSAGE_STRINGS_SUPPORT

inline int __LoadMultilanguageResourceMessageString(CString& sz, UINT nID, WORD wLangID)
{
  BOOL bMessage =  (nID&0xFFFF0000)!=0;
  UINT bStrings = __IsMultilanguageResourceMessageStringID(nID);
  BOOL bEvents  = __IsMultilanguageResourceMessageEventID(nID);
  BOOL bControls= __IsMultilanguageResourceMessageControlID(nID);
  ASSERT(bStrings || bEvents || bControls);//programmer error - debug now

  if(bStrings) {
    UINT nMsgID = UINT(bStrings);
    if( LoadMultilanguageResourceMessage(sz, nMsgID, NULL, wLangID) )
      { CString__MessageToString(sz); return 0; }
    XDEBUG_NOTIFY2(XDEBUG_RESOURCE_MESSAGE,nMsgID);
  }else if(bMessage){
    if( LoadMultilanguageResourceMessage(sz, nID, NULL, wLangID) )
      { return 0; }
    return -1;//message: RESOURCE_MESSAGE_DEFAULT(psz);
  }
  if( LoadMultilanguageResourceString(sz, nID, NULL, wLangID) )
    return 0; //string or string message retry
  return 1;   //string:  RESOURCE_STRING_DEFAULT(psz);
}

#endif

#if __MESSAGE_STRINGS_SUPPORT

inline int __LoadResourceMessageString(CString& sz, UINT nID)
{
  BOOL bMessage =  (nID&0xFFFF0000)!=0;
  UINT bStrings = __IsMultilanguageResourceMessageStringID(nID);
  BOOL bEvents  = __IsMultilanguageResourceMessageEventID(nID);
  ASSERT(bStrings || bEvents);//programmer error - debug now
  UINT nMsgID   = 0;

  if(bStrings) {
    nMsgID = UINT(bStrings);
    sz = FormatErrorString(nMsgID);
    if( !sz.IsEmpty() ) //TO DO: error handling?
      { CString__MessageToString(sz); return 0; }
  }else if(bMessage){
    sz = FormatErrorString(nID);
    if( !sz.IsEmpty() ) //TO DO: error handling?
      { return 0; }
    return -1;//message: RESOURCE_MESSAGE_DEFAULT(psz);
  }
  if(bStrings) {
    if( sz.LoadString(nID) ) {
      XDEBUG_NOTIFY2(XDEBUG_STRING_ONLY,nMsgID);
      return 0; //string or string message retry
    }else{
      XDEBUG_NOTIFY2(XDEBUG_RESOURCE_MESSAGE,nMsgID);
    }
  }
  return 1;   //string:  RESOURCE_STRING_DEFAULT(psz);
}

#endif


#if defined(MULTILANGSTRINGS) && __MESSAGE_STRINGS_SUPPORT

__inline int LoadMultilanguageResourceMessageString(CString& sz, UINT nID, WORD wLangID)
{
  return __LoadMultilanguageResourceMessageString(sz, nID, wLangID);
}

#elif __MESSAGE_STRINGS_SUPPORT

__inline int LoadMultilanguageResourceMessageString(CString& sz, UINT nID, WORD wLangID)
{
  return __LoadResourceMessageString(sz, nID);
}

#elif defined(MULTILANGSTRINGS)

__inline int LoadMultilanguageResourceMessageString(CString& sz, UINT nID, WORD wLangID) //AY 23.11.2010
{
  return LoadMultilanguageResourceString(sz, nID, NULL, wLangID);
}

#else

__inline int LoadMultilanguageResourceMessageString(CString& sz, UINT nID, WORD wLangID) //AY 23.11.2010
{
  ASSERT(__IsMultilanguageResourceMessageStringID(nID));  return !sz.LoadString(nID & 0xFFFF);
}

#endif


////////////////////////////////////////////////////////////////////////////////////
// ResourceString implementation

#define RESOURCE_STRING_DEFAULT(psz)\
  XDEBUG_NOTIFY2(XDEBUG_RESOURCE_STRING,nID);\
  if(psz != NULL)\
    return CString(psz);\
  XDEBUG_NOTIFY2(XDEBUG_UNKNOWN_STRING,nID);\
  return CString(_T("Undefined resource string")); //default substitution in english

#define RESOURCE_MESSAGE_DEFAULT(psz)\
  XDEBUG_NOTIFY2(XDEBUG_RESOURCE_MESSAGE,nID);\
  if(psz != NULL)\
    return CString(psz);\
  XDEBUG_NOTIFY2(XDEBUG_UNKNOWN_MESSAGE,nID);\
  return CString(_T("Undefined resource message")); //default substitution in english


inline CString __ResourceString__(UINT nID, const char* psz) {  //AY 25.05.2010
//ASSERT(__IsMultilanguageResourceMessageStringID(nID)); //in MREC is absent
  CString sz;
  if( sz.LoadString(nID & 0xFFFF) )
    return sz;
  RESOURCE_STRING_DEFAULT(psz);
}

inline CString __ResourceString__(UINT nID, const wchar_t* psz) {
  ASSERT(__IsMultilanguageResourceMessageStringID(nID));
  CString sz;
  if( sz.LoadString(nID & 0xFFFF) )
    return sz;
  RESOURCE_STRING_DEFAULT(psz);
}

#if defined(MULTILANGSTRINGS)
inline CString __ResourceStringML(UINT nID, const char* psz) {
  CString sz;
  if( LoadMultilanguageResourceString(sz, nID) )
    return sz;
  RESOURCE_STRING_DEFAULT(psz);
}
inline CString __ResourceStringML(UINT nID, const wchar_t* psz) {
  CString sz;
  if( LoadMultilanguageResourceString(sz, nID) )
    return sz;
  RESOURCE_STRING_DEFAULT(psz);
}
#endif


#if __MESSAGE_STRINGS_SUPPORT

inline CString __ResourceMessageString(UINT nID, const char* psz) {
  CString sz;
  int iAns = LoadMultilanguageResourceMessageString(sz, nID, 0);
  if(iAns==0)
    return sz;
  if(iAns<0){
    RESOURCE_MESSAGE_DEFAULT(psz);
  }
  RESOURCE_STRING_DEFAULT(psz);
}
inline CString __ResourceMessageString(UINT nID, const wchar_t* psz) {
  CString sz;
  int iAns = LoadMultilanguageResourceMessageString(sz, nID, 0);
  if(iAns==0)
    return sz;
  if(iAns<0){
    RESOURCE_MESSAGE_DEFAULT(psz);
  }
  RESOURCE_STRING_DEFAULT(psz);
}
#endif


////////////////////////////////////////////////////////////////////////////////////
// ResourceString top level implementation

#define RESOURCE_STRING(lpsz,ID,lpszDef) \
  CString lpsz##__res; \
  LPCTSTR lpsz = (lpsz##__res.LoadString(ID)? lpsz##__res : (lpszDef));

__inline CString __ResourceString(UINT nID, const char* psz)
{
#if defined(MULTILANGSTRINGS)
  return __ResourceStringML(nID,psz);
#else
  return __ResourceString__(nID,psz);
#endif
}

__inline CString __ResourceString(UINT nID, const wchar_t* psz)
{
#if defined(MULTILANGSTRINGS)
  return __ResourceStringML(nID,psz);
#else
  return __ResourceString__(nID,psz);
#endif
}

__inline CString ResourceString(UINT nID, const char* psz)
{
#if   defined(MULTILANGSTRINGS) && __MESSAGE_STRINGS_SUPPORT
  return __ResourceMessageString(nID,psz);
#elif __MESSAGE_STRINGS_SUPPORT
  return __ResourceMessageString(nID,psz);//AY 29.11.2010 ?
#elif defined(MULTILANGSTRINGS)
  return __ResourceStringML(nID,psz);
#else
  return __ResourceString__(nID,psz);
#endif
}

__inline CString ResourceString(UINT nID, const wchar_t* psz)
{
#if   defined(MULTILANGSTRINGS) && __MESSAGE_STRINGS_SUPPORT
  return __ResourceMessageString(nID,psz);
#elif __MESSAGE_STRINGS_SUPPORT
  return __ResourceMessageString(nID,psz);//AY 29.11.2010 ?
#elif defined(MULTILANGSTRINGS)
  return __ResourceStringML(nID,psz);
#else
  return __ResourceString__(nID,psz);
#endif
}

////////////////////////////////////////////////////////////////////////////////////
// ResourceFont  implementation

enum { __IDS_FONTMAPPING=2 }; //predefined resource id

inline CString ResourceFont(LPCTSTR szFont) {
  #if defined(MULTILANG)
    CString szMap;
    LoadMultilanguageResourceString(szMap, __IDS_FONTMAPPING);
    CString sz;
    if( CString__MapMultilanguageResourceFont(sz, szFont, szMap) )
      return sz;
    XDEBUG_NOTIFY2(XDEBUG_RESOURCE_FONT,szFont);
    return CString();//resources format error
  #else
    if( szFont!=NULL )
      return szFont;
    CString sz;
    CString__MapMultilanguageResourceFont(sz, NULL, sz);
    return sz;//"MS Sans Serif"; //AY 25.05.2010 "Tahoma"
  #endif
}

inline BOOL ResourceFontW(LPCTSTR szFontName, wchar_t* pwz, int nMaxLen)  //AY 06.05.2010
{
  CString szFont = ResourceFont(szFontName);
  BOOL bRet = TRUE;
  if(szFont.GetLength()+1>=nMaxLen)
    { ASSERT(0); ASSERT(nMaxLen>6); szFont = _T("Tahoma"); bRet = FALSE; }
  int iRet = CString__T2W(szFont, pwz, nMaxLen);
  if(iRet<0)
    bRet = FALSE;
  return bRet;
}

////////////////////////////////////////////////////////////////////////////////////
// CString extensions implementation

inline CString FormatResourceString(UINT nID, const char* pszFormat, ... ) {
  CString szFormat( ResourceString(nID,pszFormat) );
  va_list args; va_start(args, pszFormat);
  CString sz; sz.FormatV(szFormat, args);
  return(sz);
}

inline CString FormatString(LPCTSTR szFormat, ... ) {
  va_list args; va_start(args, szFormat);
  CString sz; sz.FormatV(szFormat, args);
  return(sz);
}

inline CString FormatErrorString(DWORD dwError, LPCTSTR szFormat, ... ) {
  va_list args; va_start(args, szFormat);
  CString sz; CString__FormatErrorStringV(sz, dwError, szFormat, args);
  return sz;
}

inline CString FormatErrorString(LPCTSTR szFormat, ... ) {
  DWORD dwError = ::GetLastError();
  va_list args; va_start(args, szFormat);
  CString sz; CString__FormatErrorStringV(sz, dwError, szFormat, args);
  return sz;
}

/////////////////////////////////////////////////////////////////////////////
// CString extensions

inline int CString__CompareNoCase(const CString& sz1, const CString& sz2, WORD wLangID)
{
  if(wLangID==0)
  #if defined(MULTILANG) || defined(MULTILANGSTRINGS)
    wLangID = GetApplicationLanguageID();
  #else
    wLangID = LOCALE_USER_DEFAULT;
  #endif

  int iRet = ::CompareString(MAKELCID(wLangID,SORT_DEFAULT),NORM_IGNORECASE,sz1,-1,sz2,-1);

  if(iRet==CSTR_LESS_THAN)
    return -1;
  if(iRet==CSTR_GREATER_THAN)
    return  1;
  return 0;//on error also
}

// UNICODE/ANSI support extensions ////////////////////////////////////////////////

#ifndef __NO_ANSI_TO_UNICODE_SUPPORT

#if defined(UNICODE) || defined(_UNICODE)
inline CString ResourceFont(LPCSTR  szFont)
{
  XDEBUG_NOTIFY2(XDEBUG_ANSI_TO_UNICODE,szFont);
  return ResourceFont((LPCTSTR)CString(szFont));
}
#else
inline CString ResourceFont(LPCWSTR szFont)
{
  XDEBUG_NOTIFY2(XDEBUG_UNICODE_TO_ANSI,szFont);
  return ResourceFont((LPCTSTR)CString(szFont));
}
#endif

#if defined(UNICODE) || defined(_UNICODE)
inline CString FormatString(LPCSTR  szFormat, ... )
{
  XDEBUG_NOTIFY2(XDEBUG_ANSI_TO_UNICODE, szFormat);
  CString tzFormat(szFormat);
  va_list args; va_start(args, szFormat);
  CString sz; sz.FormatV(tzFormat, args);
  return(sz);
}
#else
inline CString FormatString(LPCWSTR szFormat, ... )
{
  XDEBUG_NOTIFY2(XDEBUG_UNICODE_TO_ANSI, szFormat);
  CString tzFormat = szFormat;
  va_list args; va_start(args, szFormat);
  CString sz; sz.FormatV(tzFormat, args);
  return(sz);
}
#endif
#endif//__NO_ANSI_TO_UNICODE_SUPPORT

// UNICODE/ANSI conversion extensions /////////////////////////////////////////////

inline int CString__A2A(LPCSTR sz, LPSTR psz, int nMaxLen)
{
  size_t nLen = strlen(sz);
  if(nMaxLen>=0 && nLen>=(size_t)nMaxLen)
    return -1;//no space
  strcpy(psz, sz);
  return nLen;
}

inline int CString__W2W(LPCWSTR sz, LPWSTR psz, int nMaxLen)
{
  size_t nLen = wcslen(sz);
  if(nMaxLen>=0 && nLen>=(size_t)nMaxLen)
    return -1;//no space
  wcscpy(psz, sz);
  return nLen;
}

inline int CString__W2A(LPCWSTR sz, LPSTR  paz, int nMaxLen)
{
  size_t nLen = wcslen(sz);
  if(nMaxLen>=0 && nLen>=(size_t)nMaxLen)
    return -1;//no space
  wz2szncpy(paz, sz, nLen+1);
  return nLen;
}

inline int CString__A2W(LPCSTR sz, LPWSTR pwz, int nMaxLen)
{
  size_t nLen = strlen(sz);
  if(nMaxLen>=0 && nLen>=(size_t)nMaxLen)
    return -1;//no space
  sz2wzncpy(pwz, sz, nLen+1);
  return nLen;
}


inline int CString__T2T(LPCTSTR sz, LPTSTR psz, int nMaxLen)
{
  #if IS_CSTRING_UNICODE
    return CString__W2W(sz, psz, nMaxLen);
  #else
    return CString__A2A(sz, psz, nMaxLen);
  #endif
}

inline int CString__T2A(LPCTSTR sz, LPSTR  paz, int nMaxLen)
{
  #if IS_CSTRING_UNICODE
    return CString__W2A(sz, paz, nMaxLen);
  #else
    return CString__A2A(sz, paz, nMaxLen);
  #endif
}

inline int CString__T2W(LPCTSTR sz, LPWSTR pwz, int nMaxLen)
{
  #if IS_CSTRING_UNICODE
    return CString__W2W(sz, pwz, nMaxLen);
  #else
    return CString__A2W(sz, pwz, nMaxLen);
  #endif
}

/////////////////////////////////////////////////////////////////////////////
// CString extensions

inline CString CString__GetTextLine(const CString& sz, int nLine, LPCTSTR szDelimiters) //NULL is \r\n
{
  size_t nAns = 0;
  LPTSTR szAns = xstrnsub(nLine,(LPCTSTR)sz,sz.GetLength(),&nAns,szDelimiters);
  CString szRet(szAns,nAns);
  szRet.TrimRight(_T("\r\n\f\x1A"));//CR,LF,FF,EOF
  return szRet;
}

inline CString CString__Distille(LPCTSTR szSource, LPCTSTR szBeg, LPCTSTR szEnd)
{
  CString sz(szSource);
  int i = sz.Find(szBeg);
  if(i>=0) {
    i += CString(szBeg).GetLength();
    sz.Delete(0,i);
    if(szEnd!=NULL) {
      i = sz.Find(szEnd); //AA 19.20.2011 OLD: Find(_T("\n"))
      if(i>=0)
        sz.Delete(i,sz.GetLength()-i);
    }
  }else{
    sz.Empty();
  }
  return sz;
}

inline CString& CString__MessageToString(CString& sz) //AY 29.03.2010
{
  int      nLen = sz.GetLength();
  unsigned nNew = 0;
  unsigned nCRLF = 0;
  if(nLen>=1 && sz[nLen-1]==_T('\n')) nCRLF+=1;
  if(nLen>=2 && sz[nLen-2]==_T('\r')) nCRLF+=1;

  LPTSTR s = sz.GetBuffer(nLen);
  nNew = c_string_c2text(s);
  sz.ReleaseBuffer(nNew-nCRLF);
  return sz;
}

inline CString CString__MenuToString(LPCTSTR szMenu) //AY 09.11.2010
{
  CString sz = szMenu;
#if __IS_UNICODE
  TCHAR s[2] = {0x2026,'\0'};//... UNICODE
  sz.Replace(s, _T(""));
#endif
  sz.Replace(_T("..."),_T(""));
  sz.Replace(_T("&"),_T(""));
  return sz;
}

/////////////////////////////////////////////////////////////////////////////
// CStdString

enum { __IDS_STANDARD_WORDS=3 }; //predefined resource id

enum CStdWords //standard words
{                    // same as Windows identifiers:
  wordIDOK      =  1,// IDOK
  wordIDCANCEL  =  2,// IDCANCEL
  wordIDABORT   =  3,// IDABORT
  wordIDRETRY   =  4,// IDRETRY
  wordIDIGNORE  =  5,// IDIGNORE
  wordIDYES     =  6,// IDYES
  wordIDNO      =  7,// IDNO
  wordIDCLOSE   =  8,// IDCLOSE
  wordIDHELP    =  9,// IDHELP

  wordIDAPPLY   = 10,
  wordIDREVERT  = 11,
  wordIDDEFAULT = 12,
  wordIDOPEN    = 13,
  wordIDSAVE    = 14,
  wordIDSAVEAS  = 15,
  wordIDPROPERTIES = 16,
  wordIDFILE       = 17
};

class CStdString
{
  void static_construct();
public:
  static CString GetStdText(int nStdWordID, int nType=0) //AY 06.05.2010
  {
    CString szText = ResourceString(__IDS_STANDARD_WORDS,
    /*English words:*/ "OK\nCancel\nAbort\nRetry\nIgnore\nYes\nNo\nClose\nHelp\nApply\nRevert\nDefaults\nOpen\nSave\nSave As");  //AA 27.08.2009 OLD: ResourceString(3,"OK\nCancel\nAbort\nRetry\nIgnore\nYes\nNo\nClose\nHelp\nApply\nRevert\nDefaults");
    //Russian words:   "Готово\nОтмена\nПрервать\nПовторить\nПропустить\nДа\nНет\nЗакрыть\nПомощь\nПрименить\nВозвратить\nПо умолчанию\nОткрыть\nСохранить\nСохранить как"
    CString szWord = CString__GetTextLine(szText,nStdWordID-1,_T("\n"));
    return szWord;
  }
};

#undef  _NULLA
#undef  _NULLW
#endif//__XCSTRING_H
#pragma once
