#ifndef __CSTRINGEX_H
#define __CSTRINGEX_H
#include "xstring.h"

inline CString CString__CString(const void* pMem, size_t size) //hex binary dump
{
  const int len = size*2+1;
  TCHAR* sz = (TCHAR*)_alloca(len*sizeof(TCHAR));
  if(sz==NULL) {
    sz = _T("");
  }else{
    mem2asc(pMem,size,sz,len);
    sz[len-1] = _T('\0');
  }
  return CString(sz);
};

#endif//__CSTRINGEX_H
#pragma once