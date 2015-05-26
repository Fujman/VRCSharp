#ifndef __XTEST2_H
#define __XTEST2_H

__declspec(selectany) int __xtest_disabled = 0;

#include "xtest.h"
#undef _XTESTBLOCK1
#undef _XTESTBLOCK2
#undef _XTESTBLOCK3
#undef  XTESTBLOCK
#undef  XTESTFUNCTION
#undef  XTESTROUTINE

#undef  XTEST

#ifndef XTEST_NONE

#if defined(_DEBUG) || defined(XTESTFORCE)
  #define XTEST_ON
#endif
#ifdef XTEST_ON
  #undef  XTEST
  #define XTEST 1
#endif
#ifdef XTEST_OFF
  #undef  XTEST
  #define XTEST 0
#endif

#define __XTEST_EXTERNALS_INITIALIZATION { void YStringInitializeApplication(); YStringInitializeApplication(); }
#define __XTEST_NAME(YName,ln) YName##ln

#define   XTEST_NAME(name,__line__)  __XTEST_NAME(name,__line__)
#define   XTEST_NAME_LINE(name)        XTEST_NAME(name,__LINE__)

#if XTEST
  #define _XTESTBLOCK1(YName,ln) \
    static struct __XTEST_NAME(YName,ln){  __XTEST_NAME(YName,ln)(); void xtest(); }\
    __XTEST_NAME(xtest_object,ln); \
    __XTEST_NAME(YName,ln)::__XTEST_NAME(YName,ln)()\
      { if(!__xtest_disabled) xtest(); } \
    void __XTEST_NAME(YName,ln)::xtest()
#else //compile check only
  #define _XTESTBLOCK1(YName,ln) \
           struct __XTEST_NAME(YName,ln){ __XTEST_NAME(YName,ln)(); void xtest(); }\
    ;\
    __XTEST_NAME(YName,ln)::__XTEST_NAME(YName,ln)() \
      { if(!__xtest_disabled) xtest(); } \
    void __XTEST_NAME(YName,ln)::xtest()
#endif

#if XTEST
  #define _XTESTBLOCK2(YName,ln) \
    static struct __XTEST_NAME(YName,ln){ __XTEST_NAME(YName,ln)(); void xtest(); }\
    __XTEST_NAME(xtest_object,ln); \
    __XTEST_NAME(YName,ln)::__XTEST_NAME(YName,ln)() { \
      if(!__xtest_disabled) { \
        __XTEST_EXTERNALS_INITIALIZATION \
        TRACE(_T("\n%hs(%d): *XTESTBLOCK* : start %hs%d\n"),__FILE__,__LINE__,(#YName),ln); \
        xtest(); \
        TRACE(_T("\n%hs(%d): *XTESTBLOCK* : finis %hs%d\n"),__FILE__,__LINE__,(#YName),ln); \
      } \
    } \
    void __XTEST_NAME(YName,ln)::xtest()
#else
  #define _XTESTBLOCK2(YName,ln) _XTESTBLOCK1(YName,ln)
#endif


#if XTEST
  #define _XTESTBLOCK3(YName,ln) \
    static struct __XTEST_NAME(YName,ln){ __XTEST_NAME(YName,ln)(); void xtest(); }\
    __XTEST_NAME(xtest_object,ln); \
    __XTEST_NAME(YName,ln)::__XTEST_NAME(YName,ln)() { \
      if(!__xtest_disabled) { \
        __XTEST_EXTERNALS_INITIALIZATION \
        xtest(); \
        TRACE(_T("\n%hs(%d): *XTESTBLOCK* : exit %hs%d\n"),__FILE__,__LINE__,(#YName),ln); \
        exit(0); \
      } \
    } \
    void __XTEST_NAME(YName,ln)::xtest()
#else
  #define _XTESTBLOCK3(YName,ln) _XTESTBLOCK1(YName,ln)
#endif

#define   XTESTBLOCK(name)    _XTESTBLOCK1(name##_xtest_block,__LINE__)
#define   XTESTFUNCTION(name) _XTESTBLOCK2(name##_xtest_function,__LINE__)
#define   XTESTROUTINE(name)  _XTESTBLOCK3(name##_xtest_routine,__LINE__)


/////////////////////////////////////////////////////////////////////////
// file name storing in global variable
//
// Usage 1: 
//    #define XTESTFILE filename    (filename must b everiable name compatible)
//    #include "xtest2.h"
// Build output (filename=EVENTOBJ):
//    j:\vr\vr_inc\xtest2.h(111): warning : char*__XTEST_FILE__EVENTOBJ = "EVENTOBJ.CPP"; generated
//
// Usage 2:
//    #pragma XTEST_FILE_PRAGMA(filename)
//            XTEST_FILE_VAR(filename)
// Build output (filename=YDEVREAL):
//   j:\vr\vr_class\devices\ydevreal.cpp(6): warning : char*__XTEST_FILE__YDEVREAL = "j:\vr\vr_class\devices\ydevreal.cpp"; generated
//

#define __XTEST_PRAGMA_STRING__(FILE) #FILE
#define __XTEST_PRAGMA_STRING(FILE)   __XTEST_PRAGMA_STRING__(FILE)

#define __XTEST_FILE_VAR__(FILE)      __XTEST_FILE__##FILE
#define __XTEST_FILE_VAR(FILE)        __XTEST_FILE_VAR__(FILE)

#define __XTEST_FILE_VAR_PRAGMA_STRING(FILE) __FILE__ "(" __XTEST_PRAGMA_STRING(__LINE__) ")"\
  ": debug warning : " "char*" "__XTEST_FILE__" __XTEST_PRAGMA_STRING(FILE) " = \"" __FILE__ "\"; generated"
#define __XTEST_FILE_VAR_PRAGMA_string(FILE) __FILE__ "(" __XTEST_PRAGMA_STRING(__LINE__) ")"\
  ": debug warning : " "char*" "__XTEST_FILE__" __XTEST_PRAGMA_STRING(FILE) " = \"" __XTEST_PRAGMA_STRING(FILE) ".CPP\"; generated"

#define XTEST_FILE_PRAGMA(FILE)       message ( __XTEST_FILE_VAR_PRAGMA_STRING(FILE) ) 
#define XTEST_FILE_VAR(FILE)          char* __XTEST_FILE_VAR(XTESTFILE) = __FILE__;

#ifdef  XTESTFILE
char*   __XTEST_FILE_VAR(XTESTFILE) = __XTEST_PRAGMA_STRING(XTESTFILE);
#ifdef _DEBUG
#pragma message(__XTEST_FILE_VAR_PRAGMA_string(XTESTFILE))
#endif
#define XTEST_FILE_VAR_NAME   __XTEST_FILE_VAR(XTESTFILE)
#define XTEST_FILE_NAME       XTESTFILE
#endif

#endif// XTEST_KILL

#endif//__XTEST2_H
#pragma once