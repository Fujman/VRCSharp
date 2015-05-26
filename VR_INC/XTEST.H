/*---------------------------------------------------------------------------\
|  XTEST.H                                     Last Change : 02.09.02 18:54  |
\---------------------------------------------------------------------------*/
#ifndef __XTEST_H
#define __XTEST_H

//Usage: XTESTBLOCK(name) | XTESTFUNCTION(name) | XTESTROUTINE(name)
//       {                | {                   | {
//         ...            |   ...               |   ...
//       }                | }                   | }
//
//Note:  XTESTBLOCK()   - run block {...} and continue executing
//       XTESTFUCTION() - run block {...}, notify it's start and stop by TRACE
//                        and continue executing
//       XTESTROUTINE() - run block {...}, notify it's stop by TRACE
//                        and stop executing
//       name - generally name of testing class

/* For help:
  #define TRACEPROC(s)    TRACEPRINTF("%s.%d.%s",__FILE__,__LINE__,(#s))
  #define TRACEFILE()     TRACEPRINTF("%s.%d",__FILE__,__LINE__)
  #define TRACEVAR(s)     __TRACESTREAM(STDTR << #s << "={" << (s) << "} ")
  #define TRACESTR(s)     TRACEPRINTF("%s",(s))
  #define TRACEEOL()      TRACEPRINTF("\n")
  #define TRACEMSG(s)     TRACEPRINTF("%s\n",(s))
  #define TRACEMESSAGE(s) TRACEPRINTF("%s.%d:%s\n",__FILE__,__LINE__,(s))
  #define TRACEMODULE(s)  TRACEPRINTF("%s.%d.%s\n",__FILE__,__LINE__,(#s))
*/

#if defined(_DEBUG) || defined(XTESTFORCE)
  #define _XTESTBLOCK1(YName) static struct YName{ YName(); } YName##object1; \
    YName::YName()
#else
  #define _XTESTBLOCK1(YName) struct YName{ YName(); }; YName::YName()
#endif

#if defined(_DEBUG) || defined(XTESTFORCE)
  #define _XTESTBLOCK2(YName) static struct YName{ YName(); void YName##Test2(); } YName##object2; \
    YName::YName() { \
      TRACE(_T("\n%hs *XTESTBLOCK* start from %hs(%d)\n"),(#YName),__FILE__,__LINE__); \
      YName##Test2(); \
      TRACE(_T("\n%hs *XTESTBLOCK* finis from %hs(%d)\n"),(#YName),__FILE__,__LINE__); \
    } \
    void YName::YName##Test2()
#else
  #define _XTESTBLOCK2(YName) _XTESTBLOCK1(YName)
#endif


#if defined(_DEBUG) || defined(XTESTFORCE)
  #define _XTESTBLOCK3(YName) static struct YName{ YName(); void YName##Test3(); } YName##object3; \
    YName::YName() { \
      YName##Test3();\
      TRACE(_T("\n%hs *XTESTBLOCK* exit from %hs(%d)\n"),(#YName),__FILE__,__LINE__); \
      exit(0); \
    } \
    void YName::YName##Test3()
#else
  #define _XTESTBLOCK3(YName) _XTESTBLOCK1(YName)
#endif

#define   XTESTBLOCK(name)    _XTESTBLOCK1(name##TestBlock)
#define   XTESTFUNCTION(name) _XTESTBLOCK2(name##TestFunction)
#define   XTESTROUTINE(name)  _XTESTBLOCK3(name##TestRoutine)


#endif//__XTEST_H
