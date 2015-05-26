#ifndef __XCSTRINGEX_H
#define __XCSTRINGEX_H
#include "xunicod.h"
#include "xCString.h"

inline CString CString__Upper(LPCTSTR_COMPLEMENT az)
{
  CString szAns(az); szAns.MakeUpper(); return szAns;
}
inline CString CString__Upper(LPCTSTR sz)
{
  CString szAns(sz); szAns.MakeUpper(); return szAns;
}
inline CString CString__Upper(const CString& sz)
{
  CString szAns = sz; szAns.MakeUpper(); return szAns;
}

#endif//__XCSTRING_H
#pragma once
