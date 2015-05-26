#ifndef __YSTRING_H
#define __YSTRING_H
#include "YString/YStrBase.h"

/////////////////////////////////////////////////////////////////////////////
// YString* definitions
#include "YString/YStringA.h"
#include "YString/YStringW.h"

/////////////////////////////////////////////////////////////////////////////
// YString* MFC Support
#include "YString/YStringX.h"

////////////////////////////////////////////////////////////////////////////////////
// YString* multilanguage resource support
#include "xCString.h"

////////////////////////////////////////////////////////////////////////////////////
// YString* Global inline resource and formatting helpers

YStringA ResourceStringA(UINT nID, const char* psz=NULL);
YStringA FormatResourceStringA(UINT nID, const char* lpszFormat=NULL, ... );
YStringA FormatStringA(YCSTRA lpszFormat, ... );

YStringW ResourceStringW(UINT nID, const char* psz=NULL);
YStringW FormatResourceStringW(UINT nID, const char* lpszFormat=NULL, ... );
YStringW FormatStringW(YCSTRW lpszFormat, ... );

////////////////////////////////////////////////////////////////////////////////////
// YStringA extensions implementation

inline YStringA ResourceStringA(UINT nID, const char* psz) {
  ASSERT(!"TO DO: implement RESOURCE MESSAGE support! AY 26.05.2010");
  YStringA sz;
  #if defined(MULTILANG) || defined(MULTILANGSTRINGS)
    const int aPriorities[] = {0/*SRS Munites*/,1/*SRS Femida*/,-1/*MFC*/};
    const int nPriorities = sizeof(aPriorities)/sizeof(*aPriorities);
    HMODULE ahModules[nPriorities+1];//NULL terminated
    GetApplicationLanguageResourceHandles(ahModules,aPriorities,nPriorities);
    WORD wLang = GetApplicationLanguageID();
    if( YStringA::LoadMultilanguageResourceString(sz, nID, wLang, ahModules) )
      return sz;
  #else
    if( sz.LoadString(nID) )
      return sz;
  #endif
  XDEBUG_NOTIFY2(XDEBUG_RESOURCE_STRING,nID);
  if(psz != NULL)
    return(psz); //default substitution in english
  XDEBUG_NOTIFY2(XDEBUG_UNKNOWN_STRING,nID);
  return("Undefined resource string");
}

inline YStringA FormatResourceStringA(UINT nID, const char* pszFormat, ... ) {
  YStringA szFormat( ResourceStringA(nID,pszFormat) );
  va_list args; va_start(args, pszFormat);
  YStringA sz; sz.FormatV(szFormat, args);
  return(sz);
}

inline YStringA FormatStringA(YCSTRA szFormat, ... ) {
  va_list args; va_start(args, szFormat);
  YStringA sz; sz.FormatV(szFormat, args);
  return(sz);
}

inline YStringA FormatStringA(LPCWSTR szFormat, ... ) { 
  XDEBUG_NOTIFY2(XDEBUG_UNICODE_TO_ANSI,szFormat);
  YStringA tzFormat = szFormat;
  va_list args; va_start(args, szFormat);
  YStringA sz; sz.FormatV(tzFormat, args);
  return(sz);
}

////////////////////////////////////////////////////////////////////////////////////
// YStringW extensions implementation

inline YStringW ResourceStringW(UINT nID, const char* psz) {
  ASSERT(!"TO DO: implement RESOURCE MESSAGE support! AY 26.05.2010");
  YStringW sz;
  #if defined(MULTILANG) || defined(MULTILANGSTRINGS)
    const int aPriorities[] = {0/*SRS Munites*/,1/*SRS Femida*/,-1/*MFC*/};
    const int nPriorities = sizeof(aPriorities)/sizeof(*aPriorities);
    HMODULE ahModules[nPriorities+1];//NULL terminated
    GetApplicationLanguageResourceHandles(ahModules,aPriorities,nPriorities);
    WORD wLang = GetApplicationLanguageID();
    if( YStringW::LoadMultilanguageResourceString(sz, nID, wLang, ahModules) )
      return sz;
  #else
    if( sz.LoadString(nID) )
      return sz;
  #endif
  XDEBUG_NOTIFY2(XDEBUG_RESOURCE_STRING,nID);
  if(psz != NULL)
    return(psz); //default substitution in english
  XDEBUG_NOTIFY2(XDEBUG_UNKNOWN_STRING,nID);
  return(L"Undefined resource string");
}

inline YStringW FormatResourceStringW(UINT nID, const char* pszFormat, ... ) {
  YStringW szFormat( ResourceStringW(nID,pszFormat) );
  va_list args; va_start(args, pszFormat);
  YStringW sz; sz.FormatV(szFormat, args);
  return(sz);
}

inline YStringW FormatStringW(YCSTRW szFormat, ... ) {
  va_list args; va_start(args, szFormat);
  YStringW sz; sz.FormatV(szFormat, args);
  return(sz);
}

inline YStringW FormatStringW(LPCSTR  szFormat, ... ) { 
  XDEBUG_NOTIFY2(XDEBUG_ANSI_TO_UNICODE,szFormat);
  YStringW tzFormat = szFormat;
  va_list args; va_start(args, szFormat);
  YStringW sz; sz.FormatV(tzFormat, args);
  return(sz);
}

////////////////////////////////////////////////////////////////////////////////////
// ANSI->UNICODE fast migration support (see usage example in YString.cpp)
//
inline YStringW FormatStringWW(YCSTRW szFormat, ... ) {
  va_list args; va_start(args, szFormat);
  YStringW sz; sz.FormatV(szFormat, args, 2/*UNICODE+%T*/);
  return(sz);
}
inline YStringA FormatStringAA(YCSTRA szFormat, ... ) {
  va_list args; va_start(args, szFormat);
  YStringA sz; sz.FormatV(szFormat, args, 1/*ANSI+%T*/);
  return(sz);
}
inline YStringW FormatStringWA(YCSTRA szFormat, ... ) {
  XDEBUG_NOTIFY2(XDEBUG_ANSI_TO_UNICODE,szFormat);
  YStringW tzFormat = szFormat;
  va_list args; va_start(args, szFormat);
  YStringW sz; sz.FormatV(tzFormat, args, 1/*ANSI+%T*/);
  return(sz);
}
#if defined(UNICODE) || defined(_UNICODE)
  #define FormatStringTA FormatStringWA
#else
  #define FormatStringTA FormatStringAA
#endif


////////////////////////////////////////////////////////////////////////////////////
// YString definition
#if defined(UNICODE) || defined(_UNICODE)
  typedef YStringW YString;
#else
  typedef YStringA YString;
#endif

#if defined(UNICODE) || defined(_UNICODE)
  #define FormatStringT         FormatStringW
  #define ResourceStringT       ResourceStringW
  #define FormatResourceStringT FormatResourceStringW
#else
  #define FormatStringT         FormatStringA
  #define ResourceStringT       ResourceStringA
  #define FormatResourceStringT FormatResourceStringA
#endif

#endif//__YSTRING_H
#pragma once