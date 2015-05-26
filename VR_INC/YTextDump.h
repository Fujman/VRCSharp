#ifndef __YTEXTDUMP_H
#define __YTEXTDUMP_H
#include "YText.h"

template<class TYPE> inline void Dump(const CSimpleTextT<TYPE>& stext)
{
  CText text; text.Create(stext);
  for(int i=0; i<text.GetSize(); ++i) {
    CString sz(text[i]);
    for(int j=0; j<sz.GetLength(); j+=256)
      TRACE(_T("%s"), sz.Mid(j,256));
    TRACE(_T("\n"));
  }
}

#endif//__YTEXTDUMP_H
#pragma once