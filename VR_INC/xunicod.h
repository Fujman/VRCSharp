#ifndef __XUNICOD_H
#define __XUNICOD_H
#include "xstring.h"

// C,C++ declarations \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

/*macroses*/

#if defined(UNICODE)||defined(_UNICODE)
  #define __IS_UNICODE        1
  #define TCHAR_COMPLEMENT    char
  #define LPTSTR_COMPLEMENT   LPSTR
  #define LPCTSTR_COMPLEMENT  LPCSTR
#else
  #define __IS_UNICODE        0
  #define TCHAR_COMPLEMENT    wchar_t
  #define LPTSTR_COMPLEMENT   LPWSTR
  #define LPCTSTR_COMPLEMENT  LPCWSTR
#endif

#ifdef  __cplusplus
extern "C" {
#define _0 =0
#define _1 =-1
#else
#define _0
#define _1
#endif//__cplusplus

/*global fuctions*/

/*copy conversions*/
TCHAR*   sz2tzncpy( TCHAR   *tzDst, const char    *szSrc, size_t nDst, size_t nSrc _1); //always zero terminated, use :;GetLastError() to check on errors
TCHAR*   wz2tzncpy( TCHAR   *tzDst, const wchar_t *wzSrc, size_t nDst, size_t nSrc _1); //always zero terminated, use :;GetLastError() to check on errors
//       tz2tzncpy //same as xstrncpy
char*    wz2szncpy( char    *szDst, const wchar_t *wzSrc, size_t nDst, size_t nSrc _1); //always zero terminated, use :;GetLastError() to check on errors
char*    tz2szncpy( char    *szDst, const TCHAR   *tzSrc, size_t nDst, size_t nSrc _1); //always zero terminated, use :;GetLastError() to check on errors
//       sz2szncpy //same as xstrncpyA
wchar_t* sz2wzncpy( wchar_t *wzDst, const char    *szSrc, size_t nDst, size_t nSrc _1); //always zero terminated, use :;GetLastError() to check on errors
wchar_t* tz2wzncpy( wchar_t *wzDst, const TCHAR   *tzSrc, size_t nDst, size_t nSrc _1); //always zero terminated, use :;GetLastError() to check on errors
//       wz2wzncpy //same as xstrncpyW

#undef  _0
#undef  _1
#ifdef  __cplusplus
}
#endif//__cplusplus

// C/C++ dual inline/global declarations /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef  __cplusplus
#ifdef  __XUNICOD_C
extern "C" {
#endif//__XUNICOD_C
#endif//__cplusplus

/*dual inline/global fuctions*/

#ifdef  __cplusplus
#ifdef  __XUNICOD_C
}
#endif//__XUNICOD_C
#endif//__cplusplus

// C++ declarations \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus

/*classes*/

#endif __cplusplus

// C/C++ dual inline/global implementation /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#if      defined(__XUNICOD_C) || defined(__cplusplus)

#if     !defined(__XUNICOD_C) && defined(__cplusplus)
  #define XUNICOD_INLINE   inline
#else
  #define XUNICOD_INLINE //global
#endif//!defined(__XUNICOD_C) && defined(__cplusplus)

/*implementations of dual inline/global functions*/

#undef XUNICOD_INLINE

#endif// defined(__XUNICOD_C) || defined(__cplusplus)
////////////////////////////////////////////////////////////////////////////////////

#endif//__XUNICOD_H
#pragma once
