/*---------------------------------------------------------------------------\
|  XDUMP.H                                     Last Change : 06.06.97 18:54  |
\---------------------------------------------------------------------------*/
#ifndef __XDUMP_H
#define __XDUMP_H
#include "xpragma.h"
#include "xdebug.h"

////////////////////////////////////////////////////////////////////////
// C and C++ section
#ifdef __cplusplus
extern "C" {
#endif
  #define XDUMP_MAX_LENGTH 4*4096 //maximal size of single outputted string (size of internal static buffer)

  #define XDUMP_TO_STDOUT       1 //send to screen, may be redirected
  #define XDUMP_TO_STDERR       2 //send to screen, can't be redirected
  #define XDUMP_TO_LOG          4 //send to log file (see XLOG.H)         (use macro XDUMPLOG(TCHAR* szFileName) to change file name)
  #define XDUMP_TO_APP          8 //send to events log (see EVENTLOG.H)   (use macro XDUMPAPP(YEventsProtocol* p) to init subsystem)
  #define XDUMP_TO_BOX         16 //send to message box
  #define XDUMP_TO_WIN         32 //send to window (WM_COPYDATA used)     (use macro XDUMPWIN(HWND h) to init subsystem)
  #define XDUMP_TO_WIN32       64 //send to debugger, can't be redirected (use OutputDebugString)
  #define XDUMP_TO_TRACE      128 //send to debugger, may be redirected   (MFC used, debug mode only)
  #define XDUMP_TO_CLIPBOARD  256 //send to Windows clipboard             (MFC used, debug mode only)

  #define XDUMP_AUTOFLUSH   0x400 //auto flush after each packet
  #define XDUMP_MULTITHREAD 0x800 //multithreading locked mode
  #define XDUMP_ASSERTBREAK 0x1000//use ASSERT like message box
  #define XDUMP_ASSERTSTACK 0x2000//dump stack on ASSERT

  #define XDUMP_FULL          255
  #define XDUMP_NONE           -1
  #ifndef _XDUMPLEVEL
  #define _XDUMPLEVEL           8
  #endif

  typedef int (*__xdump_proc)(void* handle, char* sz);
  int __xdump_target(int target, void* handle, __xdump_proc proc);
  int __xdump_mode(int mode);
  int __xdump_stack(int mode);
  int __xdump_printf(LPCTSTR fmt, ...);

  int __xlog_open(int mode);
  int __xlog_close();
  int __xlog_flush();
  int __xlog_is_opened();

#ifdef __cplusplus
}
#ifndef __NO_ANSI_TO_UNICODE_SUPPORT
#if defined(UNICODE) || defined(_UNICODE)
  int __xdump_printf(LPCSTR  fmt,...);
#else
  int __xdump_printf(LPCWSTR fmt,...);
#endif
#endif//__NO_ANSI_TO_UNICODE_SUPPORT
#endif
////////////////////////////////////////////////////////////////////////
// C section
#ifndef __cplusplus

  static int __xdump_current_level = _XDUMPLEVEL;
  extern int __xdump_global_level;

  #define __xdump_check()                 \
  (                                       \
    (__xdump_current_level>=0 && __xdump_current_level<=__xdump_global_level)?( \
      (__xdump_current_level<_XDUMPLEVEL)?(             \
        __xdump_current_level = _XDUMPLEVEL, 1          \
      ):(                                 \
        1                                 \
      )                                   \
    ):(                                   \
      0                                   \
    )                                     \
  )

  #define __xdump_level(nOP, level)       \
  (                                       \
    (nOP!=0 && nOP!=-1 && nOP!=1)?(       \
      __xdump_current_level = level       \
    ):(nOP==-1 && __xdump_current_level>=0)?(           \
      __xdump_current_level=-__xdump_current_level-1    \
    ):(nOP==1  && __xdump_current_level<0)?(            \
      __xdump_current_level=-__xdump_current_level-1    \
    ):(                                   \
      __xdump_current_level               \
    )                                     \
  )

#endif
////////////////////////////////////////////////////////////////////////
// C++ section
#ifdef __cplusplus

  static int __xdump_current_level = _XDUMPLEVEL;
  extern "C" int __xdump_global_level;

#if 0 //fix dumb compiler error
  inline int __xdump_check()
  {
    if(__xdump_current_level>=0 && __xdump_current_level<=__xdump_global_level)
      if(__xdump_current_level<_XDUMPLEVEL) //auto reset after priority up
        { __xdump_current_level = _XDUMPLEVEL; return(1); }
      else
        { return 1; }
    return 0;
  }
#else //fix dumb compiler error
  #define __xdump_check()                 \
  (                                       \
    (__xdump_current_level>=0 && __xdump_current_level<=__xdump_global_level)?( \
      (__xdump_current_level<_XDUMPLEVEL)?(             \
        __xdump_current_level = _XDUMPLEVEL, 1          \
      ):(                                 \
        1                                 \
      )                                   \
    ):(                                   \
      0                                   \
    )                                     \
  )
#endif

  inline int __xdump_level(int nOP, int level) //0-get,-1-off,+1-on, set otherwise
  {
    if(nOP!=0 && nOP!=-1 && nOP!=1)
      return __xdump_current_level = (__xdump_current_level>0)?level:-level-1;
    if(nOP==-1 && __xdump_current_level>=0)
      return __xdump_current_level=-__xdump_current_level-1;//0:-1, 1:-2, 2:-3
    if(nOP==1  && __xdump_current_level<0)
      return __xdump_current_level=-__xdump_current_level-1;//-1:0, -2:1. -3:2
    return __xdump_current_level;
  }

  #define XDUMPAUTOCLOSE() XDUMPAutoClose TheXDUMPAutoClose;
  class   XDUMPAutoClose   { public: ~XDUMPAutoClose(); };

//#define STDDC //TO DO

#endif
////////////////////////////////////////////////////////////////////////
// Common section
#if defined(_DEBUG) || defined(XDUMPFORCE)
#  define _XDUMPDEBUG
#  ifndef __XDUMP_CPP
#    ifdef XDUMPFORCE
#      if defined(XDUMP_FORCE_USING) || defined(XDUMP_SHOW_USING_ANY) || !defined(_DEBUG)
#        pragma message(__FILE__LINE__ " : warning : XDUMP processing forced")
#      endif
#    else
#      if defined(XDUMP_SHOW_USING)  || defined(XDUMP_SHOW_USING_ANY)
#        pragma message(__FILE__LINE__ " : warning : XDUMP processing enabled")
#      endif
#    endif
#  endif
#  define __XDUMPBLOCK(e)       {e};
#  define __XDUMPVALUE(e)       (e)
#  define __XDUMPTERM(e)        e
#  define __XDUMPTARGET(t,h,p)  (__xdump_target((t),(h),(p)))
#  define __XDUMPLEVEL(o,l)     (__xdump_level((o),(l)))
#  define __XDUMPCHECK()        (__xdump_check())
#  define XDUMPSTREAM(e)        ((void)(!__XDUMPCHECK()?STDDC:(e)))
#  define XDUMPPRINTF           !__XDUMPCHECK()? 0 : __xdump_printf
#else
#  define __XDUMPBLOCK(e)       ;
#  define __XDUMPVALUE(e)       (1)
#  define __XDUMPTERM(e)
#  define __XDUMPTARGET(t,p,h)  (0)
#  define __XDUMPLEVEL(o,l)     (0)
#  define __XDUMPCHECK()        (0)
#  define XDUMPSTREAM(e)        ((void)0)
#  define XDUMPPRINTF           1 ? 0 : __xdump_printf
#endif

  //application level macroses
  #define XDUMPADDTARGET(h,p)   (__XDUMPTARGET(0,(h),(p)) //set target handle and proc
  #define XDUMPDELTARGET(h,p)   (__XDUMPTARGET(-1,(h),(p))//delete target handle and proc
  #define XDUMPLOG(s)           (__XDUMPTARGET(XDUMP_TO_LOG,(void*)(LPCTSTR)(s),NULL))//set log file name
  #define XDUMPAPP(h)           (__XDUMPTARGET(XDUMP_TO_APP,(h),NULL))//set event log address, use null to detach
  #define XDUMPWIN(h,hSource)   (__XDUMPTARGET(XDUMP_TO_WIN,(void*)hSource,(void*)(h)))//set wnd handle, use null to detach

  #define XDUMPSETGLOBALLEVEL(n) (__XDUMPVALUE(__xdump_global_level=(n)))
  #define XDUMPGETGLOBALLEVEL(n) (__XDUMPVALUE(__xdump_global_level))
  #define XDUMPSETMODE(n)       (__XDUMPVALUE(__xdump_mode(n)))
  #define XDUMPGETMODE()        (__XDUMPVALUE(__xdump_mode(-1)))
  #define XDUMPENABLE(flag)     (XDUMPSETMODE(XDUMPGETMODE()|(flag)))
  #define XDUMPDISABLE(flag)    (XDUMPSETMODE(XDUMPGETMODE()&~(flag)))

  //module level macroses
  #define XDUMPCREATE()         (__XDUMPVALUE(__xlog_open(1)))
  #define XDUMPOPEN()           (__XDUMPVALUE(__xlog_open(0)))
  #define XDUMPCLOSE()          (__XDUMPVALUE(__xlog_close()))
  #define XDUMPFLUSH()          (__XDUMPVALUE(__xlog_flush()))

  #define XDUMPLEVEL(n)         (__XDUMPLEVEL(10,n))//set (auto restore to default if n<_XDUMPLEVEL)
  #define XDUMPOFF()            (__XDUMPLEVEL(-1,0))//off
  #define XDUMPON()             (__XDUMPLEVEL( 1,0))//on

  //macroses
  #define XDUMPTHREADPROC(s)    XDUMPPRINTF(_T("THREAD(id=0x%8.8X): %hs.%d.%hs"),::GetCurrentThreadId(),__FILE__,__LINE__,(#s))
  #define XDUMPPROC(s)          XDUMPPRINTF(_T("%hs.%d.%hs"),__FILE__,__LINE__,(#s))
  #define XDUMPFILE()           XDUMPPRINTF(_T("%hs.%d"),__FILE__,__LINE__)
  #define XDUMPVAR(s)           XDUMPSTREAM(STDDC << #s << "={" << (s) << "} ")
  #define XDUMPSTR(s)           XDUMPPRINTF(_T("%s"),(s))
  #define XDUMPEOL()            XDUMPPRINTF(_T("\n"))
  #define XDUMPMSG(s)           XDUMPPRINTF(_T("%s\n"),(s))
  #define XDUMPMESSAGE(s)       XDUMPPRINTF(_T("%hs.%d:%s\n"),__FILE__,__LINE__,(s))
  #define XDUMPMODULE(s)        XDUMPPRINTF(_T("%hs.%d.%hs\n"),__FILE__,__LINE__,(#s))

  #define XDUMPPENTERLEAVE(e)   class classXDUMPPROCRUN{ public:\
                                 classXDUMPPROCRUN()  { XDUMP(_T("XDUMPENTER: ")); (e); }\
                                 ~classXDUMPPROCRUN() { XDUMP(_T("XDUMPLEAVE: ")); (e); }\
                                } theXDUMPPROCRUN;

  #define _XDUMPNOTIFY(e)       ( (e) ? 1: !(__xdump_printf(_T("%hs(%d): FAILED : %hs\n"),__FILE__,__LINE__,#e)) ) //no level and xdump mode check!
  #define _XDUMPVERIFY(e)       ( (e) ? 1: !(  XDUMPPRINTF(_T("%hs(%d): VERIFY : %hs\n"),__FILE__,__LINE__,#e)) )
  #define _XDUMPASSERT(e)       (__XDUMPVALUE(e) || !(XDUMPPRINTF(_T("%hs(%d): ASSERT : %hs\n"),__FILE__,__LINE__,#e)))
  #define XDUMPBLOCK(e)         if(__XDUMPCHECK())__XDUMPBLOCK(e);
  #define XDUMPVALUE(e)         (__XDUMPCHECK()?__XDUMPVALUE(e):0)

  //TRACE similar macroses
  #define XDUMP                 XDUMPPRINTF
  #define XDUMP0(s)             XDUMPPRINTF(s)
  #define XDUMP1(s,a1)          XDUMPPRINTF(s,a1)
  #define XDUMP2(s,a1,a2)       XDUMPPRINTF(s,a1,a2)
  #define XDUMP3(s,a1,a2,a3)    XDUMPPRINTF(s,a1,a2,a3)

  //ASSERT similar macroses
#ifdef _XDUMPDEBUG
  #define _XDUMPBOX(macro,e)  \
        do { if (!macro(e) && \
                ((XDUMPGETMODE()&XDUMP_ASSERTSTACK)==0 || (__xdump_stack(XDUMPGETMODE()),1)) && \
                (XDUMPGETMODE()&XDUMP_ASSERTBREAK)!=0 && \
                (1 == xdebug_report(_CRT_ASSERT, __FILE__, __LINE__, NULL, "%hs", #e))) \
             xdebug_break();  \
        } while (0)

#else
  #define _XDUMPBOX(macro,e)    (void) macro(e)
#endif
  #define XDUMPNOTIFY(e)        _XDUMPBOX(_XDUMPNOTIFY,e)
  #define XDUMPVERIFY(e)        _XDUMPBOX(_XDUMPVERIFY,e)
  #define XDUMPASSERT(e)        _XDUMPBOX(_XDUMPASSERT,e)


//////////////////////////////////////////////////////////////////////////////
// TRACE support

#if defined(_XDUMPDEBUG) && defined(__cplusplus)

struct  __xdump_trace_emulation {
  __xdump_trace_emulation(int newmode)
  {
    mode = __xdump_mode(-1);
    clevel = __xdump_current_level;
    glevel = __xdump_global_level;
    __xdump_mode(newmode);
    __xdump_current_level = 255;
    __xdump_global_level  = 255;
  }
  ~__xdump_trace_emulation()
  {
    __xdump_mode(mode);
    __xdump_current_level = clevel;
    __xdump_global_level  = glevel;
  }
  protected: int mode, clevel, glevel;
};

#define  XDUMP_TRACE_ONLY \
  __xdump_trace_emulation __xdump_trace_emulation_object(XDUMP_TO_WIN32);

#define  XDUMP_ASSERT_ONLY \
  __xdump_trace_emulation __xdump_trace_emulation_object(XDUMP_ASSERTBREAK|XDUMP_TO_WIN32);

#define  XDUMP_TRACE_ASSERT_ONLY \
  __xdump_trace_emulation __xdump_trace_emulation_object(XDUMP_ASSERTBREAK|XDUMP_TO_WIN32);

#else

#define  XDUMP_TRACE_ONLY
#define  XDUMP_ASSERT_ONLY

#endif//_XDUMPDEBUG && __clpusplus


#endif//__XDUMP_H
