#ifndef __XCARRAY3_H
#define __XCARRAY3_H
#include <afxtempl.h>

template< class TYPE, class ARG_TYPE > class CBasicArray : public CArray<TYPE, ARG_TYPE>
{
  typedef CArray<TYPE, ARG_TYPE> CParent;
public:
// Construction
  CBasicArray()
    { m_base = 0; }

// Attributes
//int GetSize() const;
  int GetUpperBound() const
    { return CParent::GetUpperBound() - m_base; }
//void SetSize(int nNewSize, int nGrowBy = -1);
  void SetLowerBound(int nBase, ARG_TYPE newElement)
    { 
      if(nBase==m_base)
        return;
      if(GetSize()) {
        if(nBase>m_base) { //remove
          if(nBase-m_base>GetSize())
            RemoveAt(0,nBase-m_base);
          else
            RemoveAll();
        }else{ //add
          InsertAt(0,m_base-nBase,newElement);
        }
      }
      m_base = nBase;
    }
  int GetLowerBound() const
    { return m_base; }

// Operations
// Clean up
//void FreeExtra();
//void RemoveAll();

// Accessing elements
  TYPE GetAt(int nIndex) const
    { return CParent::GetAt(nIndex-m_base); }
  void SetAt(int nIndex, ARG_TYPE newElement)
    { return CParent::SetAt(nIndex-m_base, newElement); }
  TYPE& ElementAt(int nIndex)
    { return CParent::ElementAt(nIndex-m_base); }

// Direct Access to the element data (may return NULL)
//const TYPE* GetData() const;
//TYPE* GetData();

// Potentially growing the array
  void SetAtGrow(int nIndex, ARG_TYPE newElement)
    { return CParent::SetAtGrow(nIndex-m_base, newElement); } 
  int Add(ARG_TYPE newElement)
    { return CParent::Add(newElement)+m_base; }

//int Append(const CArray& src);
//void Copy(const CArray& src);
  void Copy(const CBasicArray& src)//
  {
    CParent::Copy((const CArray&)src);
    m_base = src.m_base;
  }

// overloaded operator helpers
  TYPE operator[](int nIndex) const
    { return CParent::operator[](nIndex-m_base); }
  TYPE& operator[](int nIndex)
    { return CParent::operator[](nIndex-m_base); }

// Operations that move elements around
  void InsertAt(int nIndex, ARG_TYPE newElement, int nCount = 1)
    { return CParent::InsertAt(nIndex-m_base, newElement, nCount); }
  void RemoveAt(int nIndex, int nCount = 1)
    { return CParent::RemoveAt(nIndex-m_base, nCount); }
  void InsertAt(int nStartIndex, CArray* pNewArray)
  { 
    int nAddSize = pNewArray->GetSize();
    if(nStartIndex==m_base-nAddSize){ //insert before/AY
      m_base = nStartIndex;
    }else{
      ASSERT(nStartIndex>=m_base && nStartIndex<GetUpperBound());//TO DO?
    }
    CParent::InsertAt(nStartIndex-m_base, pNewArray); 
  }

// Implementation
public:
//~CArray();
void Serialize(CArchive& ar)
  {
    CParent::Serialize(ar);
    if(ar.IsLoading())
      ar >> m_base;
    else
      ar << m_base;
  }
#ifdef _DEBUG
//void Dump(CDumpContext&) const;//TO DO?
//void AssertValid() const;
#endif
protected:
  int m_base;  
};

#endif