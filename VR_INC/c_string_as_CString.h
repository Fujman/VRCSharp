#ifndef C_STRING_AS_CSTRING_H
#define C_STRING_AS_CSTRING_H
#include "xCExcept.h"
#include "t_string.h"

#define C_STRING(s)  C_String(s,sizeof(s))

struct  C_String
{
protected:
union {
  LPCTSTR  c_as;
  LPTSTR   m_as;
};
  unsigned m_size; //with zero, in bytes
  bool     m_isRO;

public:
  C_String(LPCTSTR as, int size) : m_isRO(true)
    { c_as = as; m_size = size; }
  C_String(LPTSTR  as, int size) : m_isRO(false)
    { m_as = as; m_size = size; }

  bool IsEmpty() const
    { return m_as==NULL || *m_as=='\0'; }

  C_String& operator=(CString sz);
  C_String& operator=(LPCTSTR sz);
};

inline C_String& C_String::operator=(CString sz)
{
  int nOwnLen0 = m_size/sizeof(*m_as);
  int nObjLen0 = sz.GetLength() + 1;
  if(nOwnLen0<nObjLen0 || m_isRO)
    ThrowMemoryException(0);
  strcpyT<TCHAR>(m_as,LPCTSTR(sz));
  return *this;    
}
inline C_String& C_String::operator=(LPCTSTR sz)
{
  int nOwnLen0 = m_size/sizeof(*m_as);
  int nObjLen0 = strlenT<TCHAR>(sz) + 1;
  if(nOwnLen0<nObjLen0 || m_isRO)
    ThrowMemoryException(0);
  strcpyT<TCHAR>(m_as,sz);
  return *this;    
}



#endif//C_STRING_AS_CSTRING_H
#pragma once
