#ifndef __XCARRAY_H
#define __XCARRAY_H

#include <afxtempl.h>
#include "xqsort.h"

//////////////////////////////////////////////////////////////////////////////
#if 0
template <class TYPE, class ARG_TYPE> CBaseArray;
  template <class TYPE> class CScalarArray;// CBaseArray<TYPE,TYPE>        + operator==();
    template <class TYPE> class CObjPtrArray;// CScalarArray<TYPE*>        + objects array
      template <class TYPE> class CAddressArray;// CObjPtrArray<TYPE>      + operator<<(CDumpContext& dc, TYPE)
        template <class TYPE> class CPointerArray;// CAddressArray<TYPE>   + operator<<(CArchive&  ar, const TYPE*)
        template <class TYPE> class CObjectArray; // CAddressArray<TYPE>   + operator<<(CArchive&  ar, const TYPE*)
#endif

//////////////////////////////////////////////////////////////////////////////
// CBaseArray
template< class TYPE, class ARG_TYPE = TYPE> class CBaseArray : public CArray<TYPE,ARG_TYPE>
{
public:// local typedefs for class templates
  typedef TYPE          BASE_TYPE;
  typedef ARG_TYPE      BASE_ARG_TYPE;
};

//////////////////////////////////////////////////////////////////////////////
// CDumpArray
template< class TYPE, class ARG_TYPE = TYPE> class CDumpArray : public CBaseArray<TYPE,ARG_TYPE>
{
#ifdef _DEBUG
  void Dump(CDumpContext& dc) const 
  {
    CBaseArray<TYPE,ARG_TYPE>::Dump(dc);
    if(dc.GetDepth() > 0){
      for (int i = 0; i < m_nSize; i++)
        dc << "\t[" << i << "] = " << m_pData[i] << "\n";
    }
  }
#endif
};


//////////////////////////////////////////////////////////////////////////////
// CScalarArray
//
// Needed functions:
//         TYPE::TYPE()
//   TYPE& TYPE::operator=(TYPE)
//   BOOL  TYPE::operator==(TYPE)

template <class TYPE>
class CScalarArray :    public CBaseArray<TYPE,TYPE>
{
public://construction/destruction
                        CScalarArray();
                        CScalarArray(const CScalarArray<TYPE>& ar);
                        ~CScalarArray();
  void                  Clear(TYPE fillElement, int nStartIndex=0, int nCount=-1);
public://operations
  BOOL                  Compare(const CScalarArray<TYPE>& ar) const;
  int                   Find(TYPE newElement, BOOL bReverse=FALSE) const;
  int                   Include(TYPE newElement);
  int                   Exclude(TYPE newElement);
  void                  Init(int nCount, const TYPE* pArray);
public://operators
  CScalarArray<TYPE>&   operator = (const CScalarArray<TYPE>& ar);
  BOOL                  operator == (const CScalarArray<TYPE>& ar) const;
  BOOL                  operator != (const CScalarArray<TYPE>& ar) const;

  CScalarArray<TYPE>&   operator |= (const CScalarArray<TYPE>& ar);
  CScalarArray<TYPE>&   operator &= (const CScalarArray<TYPE>& ar);
  CScalarArray<TYPE>&   operator ^= (const CScalarArray<TYPE>& ar);
};

// implementation ////////////////////////////////////////////////////////////////////

template <class TYPE>   inline
CScalarArray<TYPE>::    CScalarArray()
  { }

template <class TYPE>   inline
CScalarArray<TYPE>::    CScalarArray(const CScalarArray<TYPE>& ar)
  { Copy(ar); }

template <class TYPE>   inline
CScalarArray<TYPE>::    ~CScalarArray()
  { }

template <class TYPE>   inline void
CScalarArray<TYPE>::    Clear(TYPE newElement, int nStartIndex/*0*/, int nCount/*-1*/)
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
CScalarArray<TYPE>::    Compare(const CScalarArray<TYPE>& ar) const
{
  if(GetSize() != ar.GetSize())
    return FALSE;
  for(int i=0; i<GetSize(); ++i)
    if(!(GetAt(i)==ar.GetAt(i)))
      return FALSE;
  return TRUE;
}

template <class TYPE>   inline int
CScalarArray<TYPE>::    Find(TYPE newElement, BOOL bReverse/*FALSE*/) const
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
CScalarArray<TYPE>::    Include(TYPE newElement)
{
  int iPos = Find(newElement);
  if(iPos<0)
    iPos = Add(newElement);
  return iPos;
}

template <class TYPE>   inline int
CScalarArray<TYPE>::    Exclude(TYPE newElement)
{
  int iPos = Find(newElement);
  if(iPos>=0)
    RemoveAt(iPos);
  return iPos;
}

template <class TYPE>   inline void
CScalarArray<TYPE>::    Init(int nCount, const TYPE* pArray)
{
  if(nCount){
    SetSize(nCount);
    for(int i=0; i<nCount; ++i)
      operator[](i) = pArray[i];
  }else{
    RemoveAll();
  }
}

template <class TYPE>   inline CScalarArray<TYPE>&
CScalarArray<TYPE>::    operator = (const CScalarArray<TYPE>& ar)
  { Copy(ar); return *this; }

template <class TYPE>   inline BOOL
CScalarArray<TYPE>::    operator == (const CScalarArray<TYPE>& ar) const
  { return Compare(ar); }

template <class TYPE>   inline BOOL
CScalarArray<TYPE>::    operator != (const CScalarArray<TYPE>& ar) const
  { return !Compare(ar); }

template <class TYPE>   inline CScalarArray<TYPE>&
CScalarArray<TYPE>::    operator |= (const CScalarArray<TYPE>& ar)
{
  for(int i=0; i<ar.GetSize(); ++i)
    Include(ar[i]);
  return *this;
}

template <class TYPE>   inline CScalarArray<TYPE>&
CScalarArray<TYPE>::    operator &= (const CScalarArray<TYPE>& ar)
{
  for(int i=GetSize()-1; i>=0; --i)
    if(ar.Find(operator[](i))<0)
      RemoveAt(i);
  return *this;
}

template <class TYPE>   inline CScalarArray<TYPE>&
CScalarArray<TYPE>::    operator ^= (const CScalarArray<TYPE>& ar)
{
  CScalarArray<TYPE> a = ar;
  for(int i=GetSize()-1; i>=0; --i){
    int j = a.Find(operator[](i));
    if(j>=0){
      RemoveAt(i);
      a.RemoveAt(j);
    }
  }
  return operator|=(a);
}

//////////////////////////////////////////////////////////////////////////////
// CObjPtrArray
//
// Needed functions:
//         TYPE::TYPE()
//         TYPE::~TYPE()
//   TYPE& TYPE::operator=(TYPE)
//   BOOL  TYPE::operator==(TYPE)

template <class TYPE>
class CObjPtrArray :   public CScalarArray<TYPE*>
{
public://construction/destruction
                        CObjPtrArray();
                        CObjPtrArray(const CObjPtrArray<TYPE>& ar);
                        ~CObjPtrArray();
  void                  ReNew(int nStartIndex=0, int nCount=-1, const TYPE* templateElement=NULL); // Create new elements, delete old elements if needed
  void                  Clean(int nStartIndex=0, int nCount=-1);// delete non-NULL elements
public://attributes
  void                  Resize(int nNewSize, const TYPE* templateElement=NULL, int nGrowBy=-1);// New filled elements
//*HIDE*  void          SetSize(int nNewSize, int nGrowBy=-1);
//*inh*   int           GetSize() const;
//*inh*   int           GetUpperBound() const;
public://operations
//*inh*   void          FreeExtra( );
  void                  RemoveAll();
public://element access
//*inh*   TYPE*         GetAt(int nIndex) const;
  TYPE*                 NewAt(int nIndex, const TYPE* templateElement=NULL); // Delete old element at this place and create new
  void                  SetAt(int nIndex, TYPE* newElement);    // Delete old element at this place and attach new
  void                  ReplaceAt(int nIndex, TYPE* newElement, TYPE** poldElement=NULL);// Clean old element at this place and attach new
//*inh*   TYPE*&        ElementAt(int nIndex);
//*inh*   const TYPE**  GetData() const;
//*inh*   TYPE**        GetData();
public://growing the array
  TYPE*                 NewAtGrow(int nIndex, const TYPE* templateElement=NULL);  // Delete old element at this place and create new (intermediate added elements filled with NULL!)
  void                  SetAtGrow(int nIndex, TYPE* newElement);// Delete old element at this place and attach new
  TYPE*                 New(const TYPE* templateElement=NULL);  // Create new element
//*inh*   int           Add(TYPE* newElement );                 // Attach element

//*HIDE*  void          InsertAt(int nIndex, TYPE* newElement, int nCount=1);     // replaced with two functions
  void                  InsertAt(int nIndex, int nCount, const TYPE* templateElement=NULL);//make multiple copies of specified element
  void                  InsertAt(int nIndex, TYPE* newElement); // Delete old element and attach new

  int                   Append(const CObjPtrArray<TYPE>& ar);
  void                  Copy(const CObjPtrArray<TYPE>& ar);    // Delete old elements and copy new
  void                  InsertAt(int nStartIndex, CObjPtrArray* pNewArray); // copy elements
  void                  RemoveAt(int nIndex, int nCount=1);                  // delete elements
  BOOL                  Compare(const CObjPtrArray<TYPE>& ar) const;
public://operators
//*inh*   TYPE*&        operator [](int nIndex);
//*inh*   TYPE*         operator [](int nIndex) const;
  CObjPtrArray<TYPE>&  operator = (const CObjPtrArray<TYPE>& ar);
  BOOL                  operator == (const CObjPtrArray<TYPE>& ar) const;
  BOOL                  operator != (const CObjPtrArray<TYPE>& ar) const;
protected://*HIDE* some functions of base class
  void                  InsertAt(int nIndex, TYPE* newElement, int nCount=1) { ASSERT(0); }
  void                  SetSize(int nNewSize, int nGrowBy=-1) { CArray<TYPE*,TYPE*>::SetSize(nNewSize,nGrowBy); }
};

// implementation ////////////////////////////////////////////////////////////////////

template <class TYPE>   inline
CObjPtrArray<TYPE>::   CObjPtrArray()
  { }

template <class TYPE>   inline
CObjPtrArray<TYPE>::   CObjPtrArray(const CObjPtrArray<TYPE>& ar) : CScalarArray()
  { Copy(ar); }

template <class TYPE>   inline
CObjPtrArray<TYPE>::   ~CObjPtrArray()
  { Clean(); }

template <class TYPE>   inline void
CObjPtrArray<TYPE>::   ReNew(int nStartIndex/*0*/, int nCount/*-1*/, const TYPE* templateElement/*NULL*/)
{
  if(nCount==-1) nCount = GetSize() - nStartIndex;

  ASSERT(nStartIndex>=0 && nStartIndex<GetSize());
  ASSERT(nCount>=0 && nCount<=GetSize()-nStartIndex);

  for(int nIndex=nStartIndex; nIndex<nStartIndex+nCount; ++nIndex)
  {
    TYPE*& p = ElementAt(nIndex);
    if(p!=NULL)
      { delete p; p = NULL; }
    p = new TYPE;//may be used new TYPE(*templateElement)?
    if(templateElement!=NULL)
      *p = *templateElement;
  }
}

template <class TYPE>   inline void
CObjPtrArray<TYPE>::   Clean(int nStartIndex/*0*/, int nCount/*-1*/)
{
  if(nCount<0) nCount = GetSize() - nStartIndex;

  ASSERT(nStartIndex>=0 && (nStartIndex<GetSize() || nCount==0));
  ASSERT(nCount>=0 && nCount<=GetSize()-nStartIndex);

  for(int nIndex=nStartIndex; nIndex<nStartIndex+nCount; ++nIndex)
  {
    TYPE*& p = ElementAt(nIndex);
    if(p!=NULL)
      { delete p; p = NULL; }
  }
}

template <class TYPE>   inline void
CObjPtrArray<TYPE>::   Resize(int nNewSize, const TYPE* templateElement/*NULL*/, int nGrowBy/*-1*/)// New filled elements
{
  ASSERT(nNewSize>=0);
  int nOldSize = GetSize();

  if(nNewSize<nOldSize)
    Clean(nNewSize,nOldSize-nNewSize);

  CArray<TYPE*,TYPE*>::SetSize(nNewSize, nGrowBy);

  if(nNewSize>nOldSize)
    ReNew(nOldSize,nNewSize-nOldSize, templateElement);

//return nOldSize;
}

template <class TYPE>   inline TYPE*
CObjPtrArray<TYPE>::   NewAt(int nIndex, const TYPE* templateElement/*NULL*/)
{
  TYPE*& p = ElementAt(nIndex);
  if(p!=NULL)
    delete p;
  p = new TYPE;//may be used new TYPE(*templateElement)?
  if(templateElement!=NULL)
    *p = *templateElement;
  return p;
}


template <class TYPE>   inline void
CObjPtrArray<TYPE>::   SetAt(int nIndex, TYPE* newElement)    // Delete old element
{
  TYPE*& p = ElementAt(nIndex);
  if(p!=NULL)
    delete p;
  p = newElement;
}

template <class TYPE>   inline void
CObjPtrArray<TYPE>::   ReplaceAt(int nIndex, TYPE* newElement, TYPE** poldElement/*NULL*/)
{
  TYPE*& p = ElementAt(nIndex);
  if(poldElement!=NULL)
    *poldElement = p;
  p = newElement;
}

template <class TYPE>   inline TYPE*
CObjPtrArray<TYPE>::   NewAtGrow(int nIndex, const TYPE* templateElement/*NULL*/)  // New empty or filled element
{
  if(nIndex>=m_nSize)
    Resize(nIndex+1);
  return NewAt(nIndex,newElement);
}

template <class TYPE>   inline void
CObjPtrArray<TYPE>::   SetAtGrow(int nIndex, TYPE* newElement)// Delete old element
{
  if(nIndex>=m_nSize)
    Resize(nIndex+1);
  SetAt(nIndex,newElement);
}

template <class TYPE>   inline TYPE*
CObjPtrArray<TYPE>::   New(const TYPE* templateElement/*NULL*/)      // New emppty element
{
  int nIndex = CArray<TYPE*,TYPE*>::Add(NULL);
  return NewAt(nIndex,templateElement);
}

template <class TYPE>   inline void
CObjPtrArray<TYPE>::   InsertAt(int nIndex, int nCount, const TYPE* templateElement/*NULL*/)
{
  CArray<TYPE*,TYPE*>::InsertAt(nIndex,NULL,nCount);
  for(int nTarget=nIndex; nTarget<nIndex+nCount; ++nTarget)
    NewAt(nTarget,templateElement);
}


template <class TYPE>   inline void
CObjPtrArray<TYPE>::   InsertAt(int nIndex, TYPE* newElement)
{
  CArray<TYPE*,TYPE*>::InsertAt(nIndex,newElement,nCount);
}


template <class TYPE>   inline int
CObjPtrArray<TYPE>::   Append(const CObjPtrArray& ar)
{
  ASSERT(this != &ar);   // cannot append to itself
  int nOldSize = GetSize();
  SetSize(GetSize() + ar.GetSize());
  for(int nTarget=nOldSize, nSource=0; nSource<ar.GetSize(); ++nSource, ++nTarget)
    NewAt(nTarget,ar.GetAt(nSource));
  return nOldSize;
}

template <class TYPE>   inline void
CObjPtrArray<TYPE>::   Copy(const CObjPtrArray<TYPE>& ar)
{
  ASSERT(this != &ar);   // cannot append to itself
  Clean();
  SetSize(ar.GetSize());
  for(int nTarget=0, nSource=0; nSource<ar.GetSize(); ++nSource, ++nTarget)
    NewAt(nTarget,ar.GetAt(nSource));
}

template <class TYPE>   inline void
CObjPtrArray<TYPE>::   InsertAt(int nStartIndex, CObjPtrArray<TYPE>* pNewArray)
{
  CArray<TYPE*,TYPE*>::InsertAt(nStartIndex, NULL, pNewArray->GetSize());
  for(int i=0; i<pNewArray->GetSize(); i++)
    NewAt(nStartIndex+i,pNewArray->GetAt(i));
}

template <class TYPE>   inline void
CObjPtrArray<TYPE>::   RemoveAt(int nIndex, int nCount)
{
  Clean(nIndex,nCount);
  CArray<TYPE*,TYPE*>::RemoveAt(nIndex, nCount);
}

template <class TYPE>   inline void
CObjPtrArray<TYPE>::   RemoveAll()
{
  Clean();
  CArray<TYPE*,TYPE*>::RemoveAll();
}


template <class TYPE>   inline BOOL
CObjPtrArray<TYPE>::   Compare(const CObjPtrArray<TYPE>& ar) const
{
  if(GetSize() != ar.GetSize())
    return FALSE;
  for(int i=0; i<GetSize(); ++i) {
    const TYPE* p1 = GetAt(i);     BOOL bEmpty1 = p1==NULL;
    const TYPE* p2 = ar.GetAt(i);  BOOL bEmpty2 = p2==NULL;
    if(bEmpty1 && bEmpty2)
      continue;
    if((!bEmpty1 && bEmpty2) || (bEmpty1 && !bEmpty2))
      return FALSE;
    if(!(*p1==*p2))
      return FALSE;
  }
  return TRUE;
}

template <class TYPE>   inline CObjPtrArray<TYPE>&
CObjPtrArray<TYPE>::   operator = (const CObjPtrArray<TYPE>& ar)
  { Copy(ar); }

template <class TYPE>   inline BOOL
CObjPtrArray<TYPE>::   operator == (const CObjPtrArray<TYPE>& ar) const
  { return Compare(ar); }

template <class TYPE>   inline BOOL
CObjPtrArray<TYPE>::   operator != (const CObjPtrArray<TYPE>& ar) const
  { return !Compare(ar); }


//////////////////////////////////////////////////////////////////////////////
// CAddressArray
//
// Needed functions:
//         TYPE::TYPE()
//         TYPE::~TYPE()
//   TYPE& TYPE::operator=(TYPE)
//   BOOL  TYPE::operator==(TYPE)
// For dump:
//   operator<<(CDumpContext& dc, TYPE)

template <class TYPE>
class CAddressArray :   public CObjPtrArray<TYPE>
{
public://construction/destruction
                        CAddressArray();
                        CAddressArray(const CAddressArray<TYPE>& ar);
                        ~CAddressArray();
public://operators
  CAddressArray<TYPE>&  operator = (const CAddressArray<TYPE>& ar);
  BOOL                  operator == (const CAddressArray<TYPE>& ar) const;
  BOOL                  operator != (const CAddressArray<TYPE>& ar) const;
public://dump
#ifdef _DEBUG
  void                  Dump(CDumpContext&) const;
#endif
};

template <class TYPE>   inline
CAddressArray<TYPE>::   CAddressArray()
  : CObjPtrArray<TYPE>() { }

template <class TYPE>   inline
CAddressArray<TYPE>::   CAddressArray(const CAddressArray<TYPE>& ar) : CScalarArray()
  : CObjPtrArray<TYPE>(ar) { }

template <class TYPE>   inline
CAddressArray<TYPE>::   ~CAddressArray()
  { }

template <class TYPE>   inline CAddressArray<TYPE>&
CAddressArray<TYPE>::   operator = (const CAddressArray<TYPE>& ar)
  { Copy(ar); }

template <class TYPE>   inline BOOL
CAddressArray<TYPE>::   operator == (const CAddressArray<TYPE>& ar) const
  { return Compare(ar); }

template <class TYPE>   inline BOOL
CAddressArray<TYPE>::   operator != (const CAddressArray<TYPE>& ar) const
  { return !Compare(ar); }

#ifdef _DEBUG
template<class TYPE>    inline void
CAddressArray<TYPE>::   Dump(CDumpContext& dc) const
{
  CObject::Dump(dc);

  dc << "with " << m_nSize << " elements";
  if (dc.GetDepth() > 0)
  {
    dc << "\n";
    for(int i=0; i<GetSize(); ++i)
      if(GetAt(i)==NULL)
        dc << "null";
      else
        dc << *GetAt(i);
  }
  dc << "\n";
}
#endif


//////////////////////////////////////////////////////////////////////////////
// CPointerArray
//
// Needed functions:
//         TYPE::TYPE()
//         TYPE::~TYPE()
//   TYPE& TYPE::operator=(TYPE)
//   BOOL  TYPE::operator==(TYPE)
// For serialization:
//   operator<<(CArchive&  ar, TYPE)
//   operator>>(CArchive&  ar, TYPE)
// For dump:
//   operator<<(CDumpContext& dc, TYPE)

template <class TYPE>
class CPointerArray :   public CAddressArray<TYPE>
{
public://construction/destruction
                        CPointerArray();
                        CPointerArray(const CPointerArray<TYPE>& ar);
public://operators
  CPointerArray<TYPE>&  operator = (const CPointerArray<TYPE>& ar);
  BOOL                  operator == (const CPointerArray<TYPE>& ar) const;
  BOOL                  operator != (const CPointerArray<TYPE>& ar) const;
protected://helpers
  void                  Serialize(CArchive& ar);
};

// implementation ////////////////////////////////////////////////////////////////////

template <class TYPE>   inline
CPointerArray<TYPE>::   CPointerArray()
  { }

template <class TYPE>   inline
CPointerArray<TYPE>::   CPointerArray(const CPointerArray<TYPE>& ar) : CAddressArray()
  { Copy(ar); }

template <class TYPE>   inline void
CPointerArray<TYPE>::   Serialize(CArchive& ar)
{
  CObject::Serialize(ar);
  if (ar.IsStoring())
  {
    ar.WriteCount(m_nSize);
    for(int i=0; i<GetSize(); ++i) {
      const TYPE* p = GetAt(i);
      int b = (p==NULL);
      ar << b;
      if(b)
        ar << *p;
    }
  }
  else
  {
    DWORD nOldSize = ar.ReadCount();
    Clean();
    SetSize(nOldSize, -1);
    for(int i=0; i<GetSize(); ++i){
      int b;
      ar >> b;
      if(b) {
        TYPE* p = new TYPE;
        ar >> *p;
        ElementAt(i)= p;
      }
    }
  }
}

template <class TYPE>   inline CPointerArray<TYPE>&
CPointerArray<TYPE>::   operator = (const CPointerArray<TYPE>& ar)
  { CAddressArray::Copy(ar); }

template <class TYPE>   inline BOOL
CPointerArray<TYPE>::   operator == (const CPointerArray<TYPE>& ar) const
  { return CAddressArray::Compare(ar); }

template <class TYPE>   inline BOOL
CPointerArray<TYPE>::   operator != (const CPointerArray<TYPE>& ar) const
  { return !CAddressArray::Compare(ar); }

//////////////////////////////////////////////////////////////////////////////
// CObjectArray
//
// Needed functions:
//         TYPE::TYPE()
//         TYPE::~TYPE()
//   TYPE& TYPE::operator=(TYPE)
//   BOOL  TYPE::operator==(TYPE)
// For serialization:
//   operator<<(CArchive&  ar, const TYPE*)
//   operator>>(CArchive&  ar, TYPE*)
// For dump:
//   operator<<(CDumpContext& dc, TYPE)

template <class TYPE>
class CObjectArray:     public CAddressArray<TYPE>
{
public://construction/destruction
                        CObjectArray();
                        CObjectArray(const CObjectArray<TYPE>& ar);
public://operators
  CObjectArray<TYPE>&   operator = (const CObjectArray<TYPE>& ar);
  BOOL                  operator == (const CObjectArray<TYPE>& ar) const;
  BOOL                  operator != (const CObjectArray<TYPE>& ar) const;
protected://helpers
  void                  Serialize(CArchive& ar);
};

// implementation ////////////////////////////////////////////////////////////////////

template <class TYPE>   inline
CObjectArray<TYPE>::    CObjectArray()
  { /*TYPE a; ASSERT(a.IsKindOf(RUNTIME_CLASS(CObject)));*/ }

template <class TYPE>   inline
CObjectArray<TYPE>::    CObjectArray(const CObjectArray<TYPE>& ar) : CAddressArray()
  { /*TYPE a; ASSERT(a.IsKindOf(RUNTIME_CLASS(CObject)));*/ Copy(ar); }

template <class TYPE>   inline void
CObjectArray<TYPE>::    Serialize(CArchive& ar)
{
  CObject::Serialize(ar);
  if (ar.IsStoring())
  {
    ar.WriteCount(m_nSize);
    for(int i=0; i<GetSize(); ++i) {
      const TYPE* p = GetAt(i);
      int b = (p==NULL);
      ar << b;
      if(b)
        ar << (const CObject*)p;
    }
  }
  else
  {
    DWORD nOldSize = ar.ReadCount();
    Clean();
    SetSize(nOldSize, -1);
    for(int i=0; i<GetSize(); ++i){
      int b;
      ar >> b;
      if(b) {
        TYPE* p = NULL;
        ar >> *((CObject**)&p);
        ElementAt(i)= p;
      }
    }
  }
}

template <class TYPE>   inline CObjectArray<TYPE>&
CObjectArray<TYPE>::    operator = (const CObjectArray<TYPE>& ar)
  { CAddressArray<TYPE>::Copy(ar); }

template <class TYPE>   inline BOOL
CObjectArray<TYPE>::    operator == (const CObjectArray<TYPE>& ar) const
  { return CAddressArray<TYPE>::Compare(ar); }

template <class TYPE>   inline BOOL
CObjectArray<TYPE>::    operator != (const CObjectArray<TYPE>& ar) const
  { return !CAddressArray<TYPE>::Compare(ar); }

#endif// __XCARRAY_H
#pragma once
