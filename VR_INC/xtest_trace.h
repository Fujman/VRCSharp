//force TRACE output if XTESTFORCE defined 
#ifdef  XTESTFORCE
#define XDUMPFORCE
#endif
#include "xdump_trace.h"

/* Usage example:
XTESTFUNCTION(xtest_trace)
{ 
  XDUMP_TRACE_ONLY;

  TRACE("message");
}
*/
