#ifndef __YSTRARRX_H
#define __YSTRARRX_H

template <class CTYPE>
class YStringArrayPairBase
{
public:
  static CTYPE& ZeroElement(CTYPE& zero)  
    { zero = 0; return zero; }
}; 

template <class TARRAY, class TSTRINGARRAY=CStringArray, class TSTRING=CString, class TSTRSTR=LPCTSTR,  int NORDER=1/*TO DO?*/>
class YStringArrayPair : public TSTRINGARRAY, public YStringArrayPairBase<typename TARRAY::BASE_TYPE>
{
public:
  TARRAY                        m_array;

public:
  enum                        { ORDER = NORDER };
  typedef TARRAY                CARRAY;
  typedef TSTRINGARRAY          CSTRINGARRAY;
  typedef TSTRING               CSTRING;
  typedef TSTRSTR               CSTRSTR;

  typedef typename TARRAY::BASE_ARG_TYPE CARGTYPE;
  typedef typename TARRAY::BASE_TYPE     CTYPE;

public:

// Construction
  YStringArrayPair()
    {}

  void                                          Merge(const YStringArrayPair& src); //AY 02.09.2010

//manual construct
  CSTRINGARRAY& GetAsStringArray() const
                                                { return *(CSTRINGARRAY*)this; }
  void InitPairArray()
                                                { 
                                                  CTYPE zero;
                                                  ASSERT(m_array.GetSize()==0); 
                                                  m_array.RemoveAll();
                                                  if(CSTRINGARRAY::GetSize()>0)
                                                    m_array.InsertAt(0,ZeroElement(zero),CSTRINGARRAY::GetSize()); 
                                                }
// Attributes
  int GetSize() const
                                                {
                                                  int nRet1 = CSTRINGARRAY::GetSize(); 
                                                  int nRet2 = m_array.GetSize(); 
                                                  ASSERT(nRet1==nRet2);
                                                  return nRet1;
                                                }
  int GetUpperBound() const
                                                {
                                                  int nRet1 = CSTRINGARRAY::GetUpperBound(); 
                                                  int nRet2 = m_array.GetUpperBound();
                                                  ASSERT(nRet1==nRet2);
                                                  return nRet1;
                                                }
  void SetSize(int nNewSize, int nGrowBy = -1)
                                                {
                                                  CSTRINGARRAY::SetSize(nNewSize, nGrowBy);//TO DO: memery errors processing
                                                  m_array.SetSize(nNewSize, nGrowBy);
                                                }

// Operations
  // Clean up
  void FreeExtra()
                                                {
                                                  CSTRINGARRAY::FreeExtra(); 
                                                  m_array.FreeExtra();
                                                }
  void RemoveAll()
                                                {
                                                  CSTRINGARRAY::RemoveAll(); 
                                                  m_array.RemoveAll();
                                                }
  // Accessing elements
  CSTRSTR GetAt(int nIndex) const
                                                {
                                                  return CSTRINGARRAY::GetAt(nIndex);
                                                }
  void SetAt(int nIndex, CSTRSTR newElement)
                                                {
                                                  CTYPE zero;
                                                  CSTRINGARRAY::SetAt(nIndex,newElement);
                                                  m_array.SetAt(nIndex,ZeroElement(zero));
                                                }

  void SetAt(int nIndex, const CSTRING& newElement)
                                                {
                                                  CTYPE zero;
                                                  CSTRINGARRAY::SetAt(nIndex,newElement);
                                                  m_array.SetAt(nIndex,ZeroElement(zero));
                                                }

  void SetAt(int nIndex, CSTRSTR newElement, CARGTYPE zeroElement)//extension
                                                {
                                                  CSTRINGARRAY::SetAt(nIndex,newElement);
                                                  m_array.SetAt(nIndex,zeroElement);
                                                }

  void SetAt(int nIndex, const CSTRING& newElement, CARGTYPE zeroElement)//extension
                                                {
                                                  CSTRINGARRAY::SetAt(nIndex,newElement);
                                                  m_array.SetAt(nIndex,zeroElement);
                                                }
  CSTRING& ElementAt(int nIndex)
                                                {
                                                  return CSTRINGARRAY::ElementAt(nIndex);
                                                }

  CTYPE&   SecondAt(int nIndex)
                                                {
                                                  return m_array.ElementAt(nIndex);
                                                }

  // Direct Access to the element data (may return NULL)
  const CSTRING* GetData() const
                                                {
                                                  return CSTRINGARRAY::GetData();
                                                }
  CSTRING* GetData()
                                                {
                                                  return CSTRINGARRAY::GetData();
                                                }
  const CTYPE* GetSecondData() const
                                                {
                                                  return m_array.GetData();
                                                }
  CTYPE* GetSecondData()
                                                {
                                                  return m_array.GetData();
                                                }

  // Potentially growing the array
  void SetAtGrow(int nIndex, CSTRSTR newElement)
                                                {
                                                  CTYPE zero;
                                                  CSTRINGARRAY::SetAtGrow(nIndex, newElement);  //TO DO: memery errors processing
                                                  m_array.SetAtGrow(nIndex, ZeroElement(zero));
                                                }

  void SetAtGrow(int nIndex, const CSTRING& newElement)
                                                {
                                                  CTYPE zero;
                                                  CSTRINGARRAY::SetAtGrow(nIndex, newElement);  //TO DO: memery errors processing
                                                  m_array.SetAtGrow(nIndex, ZeroElement(zero));
                                                }
  int Add(CSTRSTR newElement)
                                                {
                                                  CTYPE zero;
                                                  int idx1 = CSTRINGARRAY::Add(newElement);     //TO DO: memery errors processing
                                                  int idx2 = m_array.Add(ZeroElement(zero)); 
                                                  ASSERT(idx1==idx2);
                                                  return idx1;
                                                }

  int Add(const CSTRING& newElement)
                                                {
                                                  CTYPE zero;
                                                  int idx1 = CSTRINGARRAY::Add(newElement);    //TO DO: memery errors processing
                                                  int idx2 = m_array.Add(ZeroElement(zero)); 
                                                  ASSERT(idx1==idx2);
                                                  return idx1;
                                                }

  int Add(CSTRSTR newElement, CARGTYPE zeroElement)
                                                {
                                                  int idx1 = CSTRINGARRAY::Add(newElement);    //TO DO: memery errors processing
                                                  int idx2 = m_array.Add(zeroElement); 
                                                  ASSERT(idx1==idx2);
                                                  return idx1;
                                                }

  int Add(const CSTRING& newElement, CARGTYPE zeroElement)
                                                {
                                                  int idx1 = CSTRINGARRAY::Add(newElement);    //TO DO: memery errors processing
                                                  int idx2 = m_array.Add(zeroElement); 
                                                  ASSERT(idx1==idx2);
                                                  return idx1;
                                                }

  int Append(const YStringArrayPair& src)
                                                {
                                                  int idx1 = CSTRINGARRAY::Append(src);        //TO DO: memery errors processing
                                                  int idx2 = m_array.Append(src.m_array);
                                                  ASSERT(idx1==idx2);
                                                  return idx1;
                                                }
  void Copy(const YStringArrayPair& src)
                                                {                                              //TO DO: memery errors processing
                                                  CSTRINGARRAY::Copy(src); 
                                                  m_array.Copy(src.m_array);
                                                }

  int Append(const CSTRINGARRAY& src) //special
                                                {
                                                  CTYPE zero;
                                                  int idx1 = CSTRINGARRAY::Append(src);        //TO DO: memery errors processing
                                                  m_array.InsertAt(m_array.GetSize(), ZeroElement(zero), src.GetSize());
                                                  return idx1;
                                                }
  void Copy(const CSTRINGARRAY& src)  //special
                                                {                                              //TO DO: memery errors processing
                                                  CTYPE zero;
                                                  CSTRINGARRAY::Copy(src); 
                                                  m_array.RemoveAll();
                                                  if(src.GetSize()>0)
                                                    m_array.InsertAt(0, ZeroElement(zero), src.GetSize());
                                                }

  // overloaded operator helpers
  CSTRING operator[](int nIndex) const
                                                {
                                                  return CSTRINGARRAY::operator[](nIndex);
                                                }
  CSTRING& operator[](int nIndex)
                                                {
                                                  return CSTRINGARRAY::operator[](nIndex);
                                                }

  CTYPE   operator()(int nIndex) const //extension
                                                {
                                                  return m_array.operator[](nIndex);
                                                }
  CTYPE&  operator()(int nIndex)       //extension
                                                {
                                                  return m_array.operator[](nIndex);
                                                }

  // Operations that move elements around
  void InsertAt(int nIndex, CSTRSTR newElement, int nCount = 1)
                                                {
                                                  CTYPE zero;
                                                  CSTRINGARRAY::InsertAt(nIndex, newElement, nCount);
                                                  m_array.InsertAt(nIndex, ZeroElement(zero), nCount);
                                                }

  void InsertAt(int nIndex, const CSTRING& newElement, int nCount = 1)
                                                {
                                                  CTYPE zero;
                                                  CSTRINGARRAY::InsertAt(nIndex, newElement, nCount);
                                                  m_array.InsertAt(nIndex, ZeroElement(zero), nCount);
                                                }

  void InsertAt(int nIndex, CSTRSTR newElement, CARGTYPE zeroElement, int nCount)
                                                {                                            //TO DO: memery errors processing
                                                  CSTRINGARRAY::InsertAt(nIndex, newElement, nCount);
                                                  m_array.InsertAt(nIndex, zeroElement, nCount);
                                                }

  void InsertAt(int nIndex, const CSTRING& newElement, CARGTYPE zeroElement, int nCount)
                                                {                                             //TO DO: memery errors processing
                                                  CSTRINGARRAY::InsertAt(nIndex, newElement, nCount);
                                                  m_array.InsertAt(nIndex, zeroElement, nCount);
                                                }

  void RemoveAt(int nIndex, int nCount = 1)
                                                {
                                                  CSTRINGARRAY::RemoveAt(nIndex, nCount);
                                                  m_array.RemoveAt(nIndex, nCount);
                                                }

  void InsertAt(int nStartIndex, YStringArrayPair* pNewArray)
                                                {
                                                  CSTRINGARRAY::InsertAt(nIndex, pNewArray);  //TO DO: memery errors processing
                                                  m_array.InsertAt(nIndex, pNewArray->m_array);
                                                }
// Implementation
protected: //inherited
//YStringW* m_pData;   // the actual array of data
//int m_nSize;     // # of elements (upperBound - 1)
//int m_nMaxSize;  // max allocated
//int m_nGrowBy;   // grow amount

//void InsertEmpty(int nIndex, int nCount);

public:
  ~YStringArrayPair()
    {}

//void Serialize(CArchive& ar)//TO DO - make backward compatible
//                                              {
//                                                CSTRINGARRAY::Serialize(ar);
//                                              }
#ifdef _DEBUG
  void Dump(CDumpContext& dc) const
                                                {
                                                  CSTRINGARRAY::Dump(dc);
                                                  dc << m_array;
                                                }
  void AssertValid() const
                                                {
                                                  CSTRINGARRAY::AssertValid();
                                                  m_array.AssertValid();
                                                }
#endif
//
// extensions
//
  int  Find(CSTRSTR findElement, const CTYPE* pSecond=NULL, BOOL bReverse=FALSE) const
                                                {
                                                  for(int k=0; k<GetSize(); ++k){
                                                    int i = bReverse? GetSize()-k-1 : k;
                                                    if(findElement!=NULL){
                                                      if(operator[](i)==findElement) {
                                                        if(pSecond==NULL)
                                                          return i;
                                                        else if(*pSecond==m_array[i])
                                                          return i;
                                                      }
                                                    }else{
                                                      if(pSecond!=NULL && *pSecond==m_array[i])
                                                        return i;
                                                    }
                                                  }
                                                  return -1;
                                                }

  int  Find(const CSTRING& findElement, const CTYPE* pSecond=NULL, BOOL bReverse=FALSE) const
                                                {
                                                  return Find(CSTRSTR(findElement),pSecond,bReverse);
                                                }

  int  Include(CSTRSTR newElement, CARGTYPE zeroElement, const CTYPE* pFindSecond=NULL)
                                                {
                                                  int idx = Find(newElement,pSecond);
                                                  if(idx>=0) 
                                                    SetAt(idx,newElement,zeroElement);
                                                  else
                                                    idx = Add(newElement,zeroElement);        //TO DO: memery errors processing
                                                  return idx;
                                                }

  int  Include(const CSTRING& newElement, CARGTYPE zeroElement, const CTYPE* pSecond=NULL)
                                                {
                                                  return Include(CSTRSTR(newElement), zeroElement, pSecond);
                                                }

  int  Exclude(CSTRSTR newElement, const CTYPE* pFindSecond=NULL)
                                                {
                                                  int idx = Find(newElement,pFindSecond);
                                                  if(idx<0) 
                                                    return idx;
                                                  RemoveAt(idx);
                                                  return idx;
                                                }

  int  Exclude(const CSTRING& newElement, const CTYPE* pFindSecond=NULL)
                                                {
                                                  return Exclude(CSTRSTR(newElement),pFindSecond);
                                                }
};

#include "YStrArrX.inl"

#endif//__YSTRARRX_H
#pragma once

