#ifndef __XDEBUG2_H
#define __XDEBUG2_H
#include "xdebug.h"

bool __xdebug_IsDebug(); //from command line

inline bool xdebug_IsDebug()
  { return __IS_DEBUG || __xdebug_IsDebug(); }

void xdebug_dump(LPCTSTR szOp, LPCSTR azFunc, const CString& xml);

#endif//__XDEBUG2_H
