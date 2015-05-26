/*---------------------------------------------------------------------------\
|  XDUMP_ASSERT.H                              Last Change : 06.06.97 18:54  |
\---------------------------------------------------------------------------*/
#include "xpragma.h"
#include "xdump.h"
#undef   ASSERT
#undef   VERIFY
#define  ASSERT     XDUMPASSERT
#define  VERIFY     XDUMPVERIFY
#ifdef   XDUMP_ASSERT_USING
#pragma  message(__FILE__LINE__ " : warning : XDUMPASSERT used instead similar ASSERT")
#endif// XDUMP_ASSERT_USING
