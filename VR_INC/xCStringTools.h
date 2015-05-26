#ifndef __XCSTRINGTOOLS_H
#define __XCSTRINGTOOLS_H
#include "c_array.h"
#include "xstring.h"

inline CString CString__Random()
{
  TCHAR as[33] = {0};
  rndstr(as,-int(countof(as)-1));
  return CString(as);
}

#endif//__XCSTRINGTOOLS_H
#pragma once
