#ifndef __XCSTRINGARRAY_H
#define __XCSTRINGARRAY_H

inline int CStringArray__Append(CStringArray& as, const CString& s)
{
  for(int i=0; i<as.GetSize(); ++i)
    if(0==as[i].Collate(s))
      return -(i+1);
  return as.Add(s);
}

inline int CStringArray__AppendNoCase(CStringArray& as, const CString& s)
{
  for(int i=0; i<as.GetSize(); ++i)
    if(0==as[i].CollateNoCase(s))
      return -(i+1);
  return as.Add(s);
}

inline void CStringArray__Reverse(CStringArray& as)
{
  CString sz;
  int   n = as.GetSize();
  int   i=0, j=n-1;
  for(;i<n/2; i++, j--){
    sz    = as[i];
    as[i] = as[j];
    as[j] = sz;
  }
}


#endif//__XCSTRINGARRAY_H
#pragma once
