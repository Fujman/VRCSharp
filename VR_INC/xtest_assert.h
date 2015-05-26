//force ASSERT messages if XTESTFORCE defined 
#ifdef  XTESTFORCE
#define XDUMPFORCE
#endif
#include "xdump_assert.h"

/* Usage example:
XTESTFUNCTION(xtest_assert)
{ 
  XDUMP_ASSERT_ONLY;

  ASSERT(0);
}
*/
