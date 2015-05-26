/*---------------------------------------------------------------------------\
|  XLOG.H                                      Last Change : 07.06.97 13:49  |
\---------------------------------------------------------------------------*/
#ifndef __XLOG_H
#define __XLOG_H
#include "xpragma.h"
#include "xdebug.h"
#include <stdio.h>

#if !VS2010_VERSION
#include <stdiostr.h>
#endif

#ifdef _LOGINCLUDE
#define XLOGFORCE
#endif

#ifdef __cplusplus
extern "C" {
#endif

  FILE*   log_get_file();
  FILE*   nul_get_file();

  void    log_set_name(LPCTSTR s);
  LPCTSTR log_get_name();
  int     log_open(int mode);
  int     log_close();
  int     log_flush();
  int     log_printf(LPCTSTR fmt,...);
  int     log_is_opened();

  int     log_attach_file(int* ifile, FILE* std);
  int     log_detach_file(int* ifile, FILE* std);
  int     log_stdout_attach();
  int     log_stdout_detach();
  int     log_stderr_attach();
  int     log_stderr_detach();
  int     log_stdnul_attach();
  int     log_stdnul_detach();

#ifdef __cplusplus
}//extern "C"
#endif

#ifdef __cplusplus
#ifndef __NO_ANSI_TO_UNICODE_SUPPORT
#if defined(UNICODE) || defined(_UNICODE)
  int     log_printf(LPCSTR  fmt,...);
#else
  int     log_printf(LPCWSTR fmt,...);
#endif
#endif//__NO_ANSI_TO_UNICODE_SUPPORT
#endif

#if defined(_DEBUG) || defined(XLOGFORCE)
#define _LOGDEBUG
#ifndef __XLOG_CPP
#ifdef XLOGFORCE
#ifdef   XLOG_FORCE_USING
  #pragma message(__FILE__LINE__ " : warning : XLOG processing forced")
#endif
#else
#ifdef   XLOG_SHOW_USING
  #pragma message(__FILE__LINE__ " : warning : XLOG processing enabled")
#endif
#endif
#endif

  #define _LOGLEVEL_ALL   255
  #ifndef _LOGLEVEL
  #define _LOGLEVEL 2
  #endif

  #ifdef __XLOG_C
  int __log_level = 0;
  #else
  extern __log_level;
  #endif

  #define ____LOGCHECK(n)      \
  {                            \
     if(__log_level<0)         \
       return(0);              \
     int b = __log_level <= n; \
     __log_level = 0;          \
     return b;                 \
  }

#ifndef __cplusplus
  static int __log_check(int n) ____LOGCHECK(n)
#else/*__cplusplus*/
  inline int __log_check(int n) ____LOGCHECK(n)

  struct LOG_AutoClose
    { static AutoClose(); ~LOG_AutoClose(); };

  #define STDOUT        (stdiostream(stdout))
  #define STDERR        (stdiostream(stderr))
  #define STDLOG        (*log_get_stream())
  #define STDNUL        (*nul_get_stream())
#if !VS2010_VERSION
  extern  stdiostream*    log_get_stream();
  extern  stdiostream*    nul_get_stream();
#endif

  #define stdlog        (log_get_file())
  #define stdnul        (nul_get_file())
#endif/*__cplusplus*/


  #define LOGSETNAME(s) log_set_name(s)
  #define LOGGETNAME()  log_get_name()
  #define LOGCREATE()   log_open(1)
  #define LOGOPEN()     log_open(0)
  #define LOGCLOSE()    log_close()
  #define LOGFLUSH()    log_flush()
  #define LOGAUTOCLOSE() LOG_AutoClose TheLOG_AutoClose;

  #define LOGPRINTF     !__LOGCHECK() ? 0 : log_printf

  #define LOGLEVEL(n)   (__log_level=(n))
  #define LOGOFF()      (__log_level=-(__log_level+1))
  #define LOGON()       (__log_level=-(__log_level-1))
  #define __LOGCHECK()    __log_check(_LOGLEVEL)
  #define __LOGSTREAM(e)  ((void)(!__LOGCHECK()?(STDLOG<<""):(e)))

  #define LOGPROC(s)    LOGPRINTF(_T("%hs.%d.%hs"),__FILE__,__LINE__,(#s))
  #define LOGFILE()     LOGPRINTF(_T("%hs.%d"),__FILE__,__LINE__)
  #define LOGVAR(s)     __LOGSTREAM(STDLOG<< #s << "={" << (s) << "} ")
  #define LOGSTR(s)     LOGPRINTF(_T("%s"),(s))
  #define LOGEOL()      LOGPRINTF(_T("\n"))
  #define LOGMSG(s)     LOGPRINTF(_T("%s\n"),(s))
  #define LOGMESSAGE(s) LOGPRINTF(_T("%hs.%d:%s\n"),__FILE__,__LINE__,(s))
  #define LOGMODULE(s)  LOGPRINTF(_T("%hs.%d.%hs\n"),__FILE__,__LINE__,(#s))
  #define LOGASSERT(e)  (void)((e) || (LOGPRINTF(_T("%hs.%d: assert on %hs\n"),__FILE__,__LINE__,#e)))
  #define LOGBLOCK(e)   if(__LOGCHECK()){e};
  #define LOGVALUE(e)   (!__LOGCHECK()?0:(e))

  #ifdef XLOGFORCE
    #define LOGFORCEONLY(e)    e
    #define LOGFORCEBLOCK(e)   {e};
  #else
    #define LOGFORCEONLY(e)
    #define LOGFORCEBLOCK(e) ;
  #endif

#else /*_DEBUG || _LOGINCLUDE*/
  int     log_printf(const char *fmt, ...);
  #define LOGPRINTF     1 ? 0 : log_printf

  #define LOGSETNAME(s)
  #define LOGGETNAME()  ("")
  #define LOGCREATE()
  #define LOGOPEN()
  #define LOGCLOSE()
  #define LOGFLUSH()
  #define LOGAUTOCLOSE()

  #define LOGCHECK()
  #define LOGLEVEL(n)
  #define LOGOFF()
  #define LOGON()

  #define LOGMODULE(s)
  #define LOGFILE()
  #define LOGVAR(s)
  #define LOGSTR(s)
  #define LOGEOL()
  #define LOGMSG(s)
  #define LOGMESSAGE(s)
  #define LOGASSERT(e)
  #define LOGBLOCK(e)
  #define LOGVALUE(e)

  #define LOGFORCEONLY(e)
  #define LOGFORCEBLOCK(e) ;

#endif/*_DEBUG || _LOGINCLUDE*/

  #define LOG           LOGPRINTF
#endif/*__XLOG_H*/
