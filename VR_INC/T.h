#include "YString/YStringC.h"

#define T (const void*)(LPCTSTR)(YStringC)
#define T_             (LPCTSTR)(YStringC)

/*
Example:
  TRACE(_T("%s"), T "TEST1" " TEST2");
  TRACE(T_ "TEST1" " TEST2");
*/
