/*---------------------------------------------------------------------------\
|  XDUMP_TRACE.H                               Last Change : 06.06.97 18:54  |
\---------------------------------------------------------------------------*/
#ifndef __XDUMP_TRACE
#define __XDUMP_TRACE
#include "xpragma.h"
#include "xdump.h"
#undef   TRACE 
#undef   TRACE0
#undef   TRACE1
#undef   TRACE2
#undef   TRACE3
#define  TRACE      XDUMP
#define  TRACE0     XDUMP0
#define  TRACE1     XDUMP1
#define  TRACE2     XDUMP2
#define  TRACE3     XDUMP3

#if      defined(XDUMP_TRACE_USING) && defined(_XDUMPDEBUG)
#pragma  message(__FILE__LINE__ " : warning : XDUMPTRACE used instead similar TRACE")
#endif// XDUMP_TRACE_USING

#endif//__XDUMP_TRACE
