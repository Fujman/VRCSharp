#ifndef __XCARRAY2_H
#define __XCARRAY2_H
#include "xCArray.h"

//////////////////////////////////////////////////////////////////////////////
// CStructArray
//
// Needed functions:
//         TYPE::TYPE()
//   TYPE& TYPE::operator=(TYPE)
//   BOOL  TYPE::operator==(TYPE)

template <class TYPE>
class CStructArray :    public CArray<TYPE,TYPE&>
{
public://construction/destruction
   		                  CStructArray();
   		                  CStructArray(const CStructArray<TYPE>& ar);
   		                  ~CStructArray();
  void                  Clear(const TYPE& fillElement, int nStartIndex=0, int nCount=-1);
public://operations
  BOOL                  Compare(const CStructArray<TYPE>& ar) const;
  int                   Find(const TYPE& newElement, BOOL bReverse=FALSE);
  int                   Include(const TYPE& newElement);
  int                   Exclude(const TYPE& newElement);
public://operators
  CStructArray<TYPE>&   operator = (const CStructArray<TYPE>& ar);
  BOOL                  operator == (const CStructArray<TYPE>& ar) const;
  BOOL                  operator != (const CStructArray<TYPE>& ar) const;
};

// implementation ////////////////////////////////////////////////////////////////////

template <class TYPE>   inline
CStructArray<TYPE>::    CStructArray()
  { }

template <class TYPE>   inline
CStructArray<TYPE>::    CStructArray(const CStructArray<TYPE>& ar)
  { Copy(ar); }

template <class TYPE>   inline
CStructArray<TYPE>::    ~CStructArray()
  { }

template <class TYPE>   inline void
CStructArray<TYPE>::    Clear(const TYPE& newElement, int nStartIndex/*0*/, int nCount/*-1*/)
{
  if(nCount<0) nCount = GetSize() - nStartIndex;

  ASSERT(nStartIndex>=0 && (nStartIndex<GetSize() || nCount==0));
  ASSERT(nCount>=0 && nCount<=GetSize()-nStartIndex);

  for(int nIndex=nStartIndex; nIndex<nStartIndex+nCount; ++nIndex) 
  {
    TYPE*& p = ElementAt(nIndex);
    p = fillElement;
  }
}

template <class TYPE>   inline BOOL                  
CStructArray<TYPE>::    Compare(const CStructArray<TYPE>& ar) const
{
  if(GetSize() != ar.GetSize())
    return FALSE;
  for(int i=0; i<GetSize(); ++i)
    if(!(GetAt(i)==ar.GetAt(i)))
      return FALSE;
  return TRUE;
}

template <class TYPE>   inline int
CStructArray<TYPE>::    Find(const TYPE& newElement, BOOL bReverse/*FALSE*/)
{
  if(bReverse){
    for(int i=GetSize()-1; i>=0; --i)
      if(newElement==operator[](i))
        return i;
  }else{
    for(int i=0; i<GetSize(); ++i)
      if(newElement==operator[](i))
        return i;
  }
  return -1;
}

template <class TYPE>   inline int
CStructArray<TYPE>::    Include(const TYPE& newElement)
{
  int iPos = Find(newElement);
  if(iPos<0)
    iPos = Add(newElement);
  return iPos;
}

template <class TYPE>   inline int
CStructArray<TYPE>::    Exclude(const TYPE& newElement)
{
  int iPos = Find(newElement);
  if(iPos>=0)
    RemoveAt(iPos);
  return iPos;
}

template <class TYPE>   inline CStructArray<TYPE>&
CStructArray<TYPE>::    operator = (const CStructArray<TYPE>& ar)
  { Copy(ar); }

template <class TYPE>   inline BOOL                  
CStructArray<TYPE>::    operator == (const CStructArray<TYPE>& ar) const
  { return Compare(ar); }

template <class TYPE>   inline BOOL
CStructArray<TYPE>::    operator != (const CStructArray<TYPE>& ar) const
  { return !Compare(ar); }


#endif//__XCARRAY2_H
