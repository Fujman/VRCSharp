#ifndef __XASSERT_H
#define __XASSERT_H

#ifndef ASSERT
#include <assert.h>
#ifdef _DEBUG
#define ASSERT(expr) assert(expr)
#else
#define ASSERT(expr) (0) //AY 25.10.2006
#endif
#endif

#ifndef VERIFY
#ifdef _DEBUG
#define VERIFY(expr) ASSERT(expr)
#else
#define VERIFY(expr) ((int)(expr))
#endif
#endif

#define VERIFY0(a) VERIFY(0==(a))
#define ASSERT0(a) ASSERT(0==(a))

#ifdef __cplusplus

#ifdef _DEBUG

//#define _XASSERT_BLOCK(name,line) __XASSERT_NAME(name,line)
//#define __XASSERT_NAME(name,line) name##line

template<bool> struct YCompileTimeError;
template<>
  struct YCompileTimeError<true> { enum{ans=1}; };
//still undefined
//struct YCompileTimeError<false>{};

struct YRunTimeError
  { YRunTimeError(bool expr) {ASSERT(expr);} };

#define STATIC_ASSERT(expr, msg)               \
  {                                            \
    YCompileTimeError<(expr) != 0> ERROR_##msg;\
    ERROR_##msg;                               \
  }
#define STATIC_ASSERT0(expr, msg) STATIC_ASSERT(0==(expr), msg)

#define STATIC_ASSERT_SIZEOF(e1,e2) STATIC_ASSERT(sizeof(e1)==sizeof(e2), size_of_types_mithmatch)

#define __XASSERT_FILELINE(ln)   xassert_fileline_##ln
#define  _XASSERT_FILELINE(ln) __XASSERT_FILELINE(ln)

#define DYNAMIC_ASSERT(expr)\
  static  YRunTimeError _XASSERT_FILELINE(__LINE__)(expr);

#define DYNAMIC_ASSERT0(expr) DYNAMIC_ASSERT(0==(expr))

#define RUNTIME_DEFINED(s)  YCompileTimeError<s>::ans //AY 12.02.2010

//#define DYNAMIC_ASSERT(expr,msg)  //don't work! inside functions __LINE__ expaded to $=-4 !??
//  static YRunTimeError _XASSERT_BLOCK(ASSERT_##msg##_at,__LINE__)

#else//_DEBUG

#define STATIC_ASSERT(expr, msg)
#define STATIC_ASSERT0(expr, msg)
#define DYNAMIC_ASSERT(expr)
#define DYNAMIC_ASSERT0(expr)
#define STATIC_ASSERT_SIZEOF(e1,e2)

#endif//_DEBUG
#else //__cplusplus

//still undefined STATIC_ASSERT
//still undefined STATIC_ASSERT0

#endif  //__cplusplus

#endif//__XASSERT_H
#pragma once
