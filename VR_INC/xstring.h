#ifndef __XSTRING_H
#define __XSTRING_H
#include <stdarg.h>
#include <tchar.h>
#include "int64.h"

#define  tchr TCHAR 
#define  wchr wchar_t
#define  mchr unsigned char

// C,C++ declarations \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

/*macroses*/

#ifdef  __cplusplus
extern "C" {
#define _0 =0
#define _1 =-1
#else
#define _0
#define _1
#endif//__cplusplus

/*global fuctions*/



//
// Conversions
//
int      mem2b64(const void* p, int size, tchr* a _0, int len0 _0);
int      mem2str(const void* p, int size, tchr* s _0, int len0 _0, int skip _0);//return is needed string length with zero
int      mem2asc(const void* p, int size, tchr* s _0, int len0 _0);//return is needed ascii length with zero
int      b642mem(const tchr* a, int lens, void* p _0, int size _0, int* err _0);
int      asc2mem(const tchr* s, int lens, void* p _0, int size _0);//return is needed buffer size
int      mem2dos(const void* p, int size, tchr* s _0, int len0 _0);//return is needed ascii length with zero
int      dos2mem(const tchr* s, int lens, void* p _0, int size _0);//return is needed buffer size
tchr*    u2dos(unsigned u, tchr *s);
unsigned dos2u(const tchr *s);
tchr*    i2dos(int i, tchr *s);
int      dos2i(const tchr *s);
tchr*    u2bin(unsigned u, tchr *s);
unsigned bin2u(const tchr *s);
tchr*    i2bin(int i, tchr *s);
int      bin2i(const tchr *s);

int      mem2b64A(const void* p, int size, char* a _0, int len0 _0);
int      mem2strA(const void* p, int size, char* s _0, int len0 _0, int skip _0);//return is needed string length with zero
int      mem2ascA(const void* p, int size, char* s _0, int len0 _0);//return is needed ascii length with zero
int      b642memA(const char* a, int lens, void* p _0, int size _0, int* err _0);
int      asc2memA(const char* s, int lens, void* p _0, int size _0);//return is needed buffer size
int      mem2dosA(const void* p, int size, char* s _0, int len0 _0);//return is needed ascii length with zero
int      dos2memA(const char* s, int lens, void* p _0, int size _0);//return is needed buffer size
char*    u2dosA(unsigned u, char *s);
unsigned dos2uA(const char *s);
char*    i2dosA(int i, char *s);
int      dos2iA(const char *s);
char*    u2binA(unsigned u, char *s);
unsigned bin2uA(const char *s);
char*    i2binA(int i, char *s);
int      bin2iA(const char *s);
                  
int      mem2b64W(const void* p, int size, wchr* a _0, int len0 _0);
int      mem2strW(const void* p, int size, wchr* s _0, int len0 _0, int skip _0);//return is needed string length with zero
int      mem2ascW(const void* p, int size, wchr* s _0, int len0 _0);//return is needed ascii length with zero
int      b642memW(const wchr* a, int lens, void* p _0, int size _0, int* err _0);
int      asc2memW(const wchr* s, int lens, void* p _0, int size _0);//return is needed buffer size
int      mem2dosW(const void* p, int size, wchr* s _0, int len0 _0);//return is needed ascii length with zero
int      dos2memW(const wchr* s, int lens, void* p _0, int size _0);//return is needed buffer size
wchr*    u2dosW(unsigned u, wchr *s);
unsigned dos2uW(const wchr *s);
wchr*    i2dosW(int i, wchr *s);
int      dos2iW(const wchr *s);
wchr*    u2binW(unsigned u, wchr *s);
unsigned bin2uW(const wchr *s);
wchr*    i2binW(int i, wchr *s);
int      bin2iW(const wchr *s);

int      mem2strM(const void* p, int size, mchr* s _0, int len0 _0, int skip _0);//return is needed string length with zero
int      mem2ascM(const void* p, int size, mchr* s _0, int len0 _0);//return is needed ascii length with zero
int      asc2memM(const mchr* s, int lens, void* p _0, int size _0);//return is needed buffer size
int      mem2dosM(const void* p, int size, mchr* s _0, int len0 _0);//return is needed ascii length with zero
int      dos2memM(const mchr* s, int lens, void* p _0, int size _0);//return is needed buffer size
mchr*    u2dosM(unsigned u, mchr *s);
unsigned dos2uM(const mchr *s);
mchr*    i2dosM(int i, mchr *s);
int      dos2iM(const mchr *s);
mchr*    u2binM(unsigned u, mchr *s);
unsigned bin2uM(const mchr *s);
mchr*    i2binM(int i, mchr *s);
int      bin2iM(const mchr *s);

// BCD strings support
//
int      bcd2str(char *sz, const char *bcd, const char* szDigits _0/*=="0123456789ABCDEF"*/);
int      str2bcd(char *bcd, const char *sz, const char* szDigits _0/*=="0123456789ABCDEF"*/);

// randomized strngs support
//
LPCTSTR  rndstr(LPTSTR szBuffer, int size, LPCTSTR szCharSet _0); //file name compatible charset by default

// reverse bytes orderight shift of buffer
//
void*    xmemrev(void* p, int n);//AY 10.11.2011

// right shift of buffer
//
void*    xmemrsh(void *dest, const void *src, size_t count, size_t shift/*bits*/);

// length of leading block of zeros
//
size_t   xmemzero(const void* pMemory, size_t size, size_t offs _0);

// length of leading block of non-zeros
//
size_t   xmemused(const void* pMemory, size_t size, size_t offs _0);

// length of left substring of szSource which contain only chars from szValid
//
int      xstrcspn (const tchr* szSource, const tchr* szValid);
int      xstrcspnA(const char* szSource, const char* szValid);
int      xstrcspnW(const wchr* szSource, const wchr* szValid);

//always zero terminated
//
tchr*    xstrncpy (tchr *szDst, const tchr *szSrc, size_t nDst, size_t nSrc _1);
char*    xstrncpyA(char *szDst, const char *szSrc, size_t nDst, size_t nSrc _1);
wchr*    xstrncpyW(wchr *szDst, const wchr *szSrc, size_t nDst, size_t nSrc _1);
mchr*    xstrncpyM(mchr *szDst, const mchr *szSrc, size_t nDst, size_t nSrc _1);

//may be without trailing zero
//
int      xstrncmp ( const tchr *sz1, const tchr *sz2, size_t n1, size_t n2 _1);
int      xstrncmpA( const char *sz1, const char *sz2, size_t n1, size_t n2 _1);
int      xstrncmpW( const wchr *sz1, const wchr *sz2, size_t n1, size_t n2 _1);
int      xstrncmpM( const mchr *sz1, const mchr *sz2, size_t n1, size_t n2 _1);

// get N-th substring in string (default delimiters are "\r\n")
//
tchr*    xstrsub  (int nSubStr, const tchr* sz, size_t* pnItem _0, const tchr* szDelimiters _0);
char*    xstrsubA (int nSubStr, const char* sz, size_t* pnItem _0, const char* szDelimiters _0);
wchr*    xstrsubW (int nSubStr, const wchr* sz, size_t* pnItem _0, const wchr* szDelimiters _0);

tchr*    xstrnsub (int nSubStr, const tchr* sz, size_t nSize, size_t* pnItem _0, const tchr* szDelimiters _0);
char*    xstrnsubA(int nSubStr, const char* sz, size_t nSize, size_t* pnItem _0, const char* szDelimiters _0);
wchr*    xstrnsubW(int nSubStr, const wchr* sz, size_t nSize, size_t* pnItem _0, const wchr* szDelimiters _0);

tchr*    xstrnext (const tchr* sz, const tchr* szDelimiters, size_t nSize);
char*    xstrnextA(const char* sz, const char* szDelimiters, size_t nSize);
wchr*    xstrnextW(const wchr* sz, const wchr* szDelimiters, size_t nSize);

// file size formatting
//
tchr*    xsize2str (QWORD qSize, tchr *buffer, const tchr* *suffixes _0, int flags _0);
char*    xsize2strA(QWORD qSize, char *buffer, const char* *suffixes _0, int flags _0);
wchr*    xsize2strW(QWORD qSize, wchr *buffer, const wchr* *suffixes _0, int flags _0);
mchr*    xsize2strM(QWORD qSize, mchr *buffer, const mchr* *suffixes _0, int flags _0);

// Format specifacation fields:
//   %[flags] [width] [.precision] [{h | l | I64 | L}]type
//
// Additional types:
//   Z,z - unsigned int present such as %x,%X on base 41, prefix is 0z,0Z 
//         (all flags are supported, prefixes are not suppotred)
//   Y,y - signed int present such as %d on base 41 (y-lower case,Y-upper case digits)
//         (all flags are supported, prefixes are not suppotred)
//   B,b - unsigned int present such as %x,%X on base 2, prefix is 0b,0B
//         (all flags are supported, prefixes are not suppotred)
//   k   - signed int present such as %d on base 2
//         (all flags are supported, prefixes are not suppotred)
//
int      xsprintf (LPTSTR buffer, LPCTSTR format, ... );
int      xvsprintf(LPTSTR buffer, LPCTSTR format, va_list argptr);

// double as hex
int      double2hex(LPTSTR str, LPCVOID pDouble);
int      hex2double(LPVOID pDouble, LPCTSTR str);

#undef  _0
#undef  _1
#ifdef  __cplusplus
}
#endif//__cplusplus

// C/C++ dual inline/global declarations /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef  __cplusplus
#ifdef  __XSTRING_C
extern "C" {
#endif//__XSTRING_C 
#endif//__cplusplus

/*dual inline/global fuctions*/

#ifdef  __cplusplus
#ifdef  __XSTRING_C
}
#endif//__XSTRING_C 
#endif//__cplusplus

// C++ declarations \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus

/*templates*/

/*classes*/

#endif __cplusplus

// C/C++ dual inline/global implementation /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#if      defined(__XSTRING_C) || defined(__cplusplus)

#if     !defined(__XSTRING_C) && defined(__cplusplus)
  #define XSTRING_INLINE   inline
#else
  #define XSTRING_INLINE //global
#endif//!defined(__XSTRING_C) && defined(__cplusplus)

/*implementations of dual inline/global functions*/

#undef XSTRING_INLINE

#endif// defined(__XSTRING_C) || defined(__cplusplus)
////////////////////////////////////////////////////////////////////////////////////

#undef mchr
#undef tchr
#undef wchr
#endif//__XSTRING_H
#pragma once