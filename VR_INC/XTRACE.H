/*---------------------------------------------------------------------------\
|  XTRACE.H                                    Last Change : 06.06.97 18:54  |
\---------------------------------------------------------------------------*/
#ifndef __XTRACE_H
#define __XTRACE_H
#include "xdebug.h"

#ifndef __AFX_H__
#include <afx.h>
#endif

#if (defined(_DEBUG) || defined(XTRACEFORCE)) && !defined(XTRACEBREAK)
  #define _TRACELEVEL_ALL   255
  #ifndef _TRACELEVEL
  #define _TRACELEVEL 2
  #endif

  #ifdef __XTRACE_C
  int __trace_level = 0;
  #else
  extern __trace_level;
  #endif

  inline int __trace_check(int n)
  {                              
     if(__trace_level<0)         
       return(0);                
     int b = __trace_level <= n; 
     __trace_level = 0;          
     return b;                   
  }

  #define STDTR           afxDump

//void AFX_CDECL AfxTrace(LPCTSTR lpszFormat, ...); // AFX.H
  void AFX_CDECL AfxForcedTrace(LPCTSTR lpszFormat, ...);
  #if !defined(_DEBUG) && defined(XTRACEFORCE)//arguments of functions will be calculated
  #define TRACEPRINTF     (__TRACECHECK() ? (*::AfxTrace) : (*::AfxForcedTrace))
  #else
  #define TRACEPRINTF     !__TRACECHECK() ? (void)0 : ::AfxTrace
  #endif

  #define TRACELEVEL(n)   (__trace_level=(n))
  #define TRACEOFF()      (__trace_level=-(__trace_level+1))
  #define TRACEON()       (__trace_level=-(__trace_level-1))
  #define __TRACECHECK()    __trace_check(_TRACELEVEL)
  #define __TRACESTREAM(e)  ((void)(!__TRACECHECK()?STDTR:(e)))

  #define TRACEPROC(s)    TRACEPRINTF(_T("%hs.%d.%hs"),__FILE__,__LINE__,(#s))
  #define TRACEFILE()     TRACEPRINTF(_T("%hs.%d"),__FILE__,__LINE__)
  #define TRACEVAR(s)     __TRACESTREAM(STDTR << #s << "={" << (s) << "} ")
  #define TRACESTR(s)     TRACEPRINTF(_T("%s"),(s)) //ansi or unicode
  #define TRACEEOL()      TRACEPRINTF(_T("\n"))
  #define TRACEMSG(s)     TRACEPRINTF(_T("%s\n"),(s))
  #define TRACEMESSAGE(s) TRACEPRINTF(_T("%hs(%d):%s\n"),__FILE__,__LINE__,(s))
  #define TRACEMODULE(s)  TRACEPRINTF(_T("%hs.%d.%hs\n"),__FILE__,__LINE__,(#s))
  #define TRACEASSERT(e)  (void)((e) || (TRACEPRINTF(_T("%hs(%d): assert on %hs\n"),__FILE__,__LINE__,#e)))
  #define TRACEBLOCK(e)   if(__TRACECHECK()){e};
  #define TRACEVALUE(e)   (!__TRACECHECK()?0:(e))

  #ifdef XTRACEFORCE
    #define TRACEFORCEONLY(e)    e
    #define TRACEFORCEBLOCK(e)   {e};
  #else
    #define TRACEFORCEONLY(e)
    #define TRACEFORCEBLOCK(e)   ;
  #endif

#else /*_DEBUG || _TRACEINCLUDE*/
  //     void AFX_CDECL AfxTrace(LPCTSTR lpszFormat, ...); // AFX.H
  #define TRACEPRINTF     1 ? (void)0 : ::AfxTrace

  #define TRACECHECK()
  #define TRACELEVEL(n)
  #define TRACEOFF()
  #define TRACEON()

  #define TRACEPROC(s)
  #define TRACEFILE()
  #define TRACEVAR(s)
  #define TRACESTR(s)
  #define TRACEEOL()
  #define TRACEMSG(s)
  #define TRACEMESSAGE(s)
  #define TRACEMODULE(s)
  #define TRACEASSERT(e)
  #define TRACEBLOCK(e)
  #define TRACEVALUE(e)

  #define TRACEFORCEONLY(e)
  #define TRACEFORCEBLOCK(e)   ;

#endif

  #undef  TRACE
  #define TRACE           TRACEPRINTF
#endif//__XTRACE_H
