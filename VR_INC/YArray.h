#ifndef __YARRAY_H
#define __YARRAY_H
#include "YMemory.h"
#include "YBit.h"

// C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus

template <class T> class YStaticArray;
template <class T> class YDynamicArray;
template <class T> class YVirtualArray;
template <class A> class YBitArray;

///////////////////////////////////////////////////////////////////////////
// YStaticArray<T>: non-resizeable heap allocated or statically declared array

template <class T>
class YStaticArray: public YStaticBuffer
{
  int  m_nSize;
public:
        YStaticArray(int nSize, void* p=NULL) : YStaticBuffer((size_t)nSize*sizeof(T), p)
          { m_nSize = (isEmpty()?0:nSize); }
        ~YStaticArray() 
          {}
        YStaticArray() : YStaticBuffer()
          { m_nSize = 0; }

  void* Create(int nSize, void* p=NULL)      //throw CMemoryException on error
          {
            YStaticBuffer::Create((size_t)nSize*sizeof(T), p);
            m_nSize = (isEmpty()?0:nSize);
            return ptr;
          }
  int   Resize(int nSize)
          { ASSERT(0); return -1; } // to compatibility with YDynamicBuffer in templates
  int   Expand(int nSize)
          { ASSERT(0); return -1; } // to compatibility with YDynamicBuffer in templates
  int   Map(int nSize, int nPos=0, BOOL bToPut=TRUE, YMemoryNotify pf=NULL, void* pInstance=NULL) const
          { return 0; }
  int   Use(int nSize, int nPos=0, BOOL bToPut=TRUE, YMemoryNotify pf=NULL, void* pInstance=NULL) const
          { return 0; }

  void* Clear()
          { return YStaticBuffer::Clear(m_nSize*sizeof(T)); }
  const T* Copy(T* pData, int nSize, int nPos=0) const
          { YMEMORY_ASSERT(nSize+nPos<=m_nSize); return (const T*)YStaticBuffer::Copy(pData,nSize*sizeof(T),nPos*sizeof(T)); }
  T*    Copy(const T* pData, int nSize, int nPos=0)
          { YMEMORY_ASSERT(nSize+nPos<=m_nSize); return (T*)YStaticBuffer::Copy(pData,nSize*sizeof(T),nPos*sizeof(T)); }

  int   GetSize() const
          { return (isEmpty()?0:m_nSize); }
  int   GetBufferSize() const
          { return (isEmpty()?0:m_nSize*sizeof(T)); }
        operator T*() 
          { return ((T*)ptr); }
        operator const T*() const
          { return ((const T*)ptr); }//AY 1.07.2002

  const T& operator [](int i) const
          { YMEMORY_ASSERT(i>=0 && i<m_nSize); return ((const T*)ptr)[i]; }
  T& operator [](int i)
          { YMEMORY_ASSERT(i>=0 && i<m_nSize); return ((T*)ptr)[i]; }

public:
  enum{ SIZEOFITEM = sizeof(T) };
  typedef const T*  constPOINTER;
  typedef T*        POINTER;
  static  int       ITEMS(unsigned cbSize) { YMEMORY_ASSERT(cbSize%sizeof(T)==0); return cbSize/sizeof(T); }
  static  unsigned  BYTES(int nSize)       { return nSize*sizeof(T); }
};

///////////////////////////////////////////////////////////////////////////
// YDynamicArray<T>: resizeable heap allocated or statically declared array

template <class T>
class YDynamicArray: public YDynamicBuffer
{
  int  m_nSize;
public:
        YDynamicArray(int nSize, void* p=NULL) : YDynamicBuffer((size_t)nSize*sizeof(T), p)
          { m_nSize = (isEmpty()?0:nSize); }
        ~YDynamicArray() 
          {}
        YDynamicArray() : YDynamicBuffer()
          { m_nSize = 0; }

  void* Create(int nSize, void* p=NULL) 
          {
            YDynamicBuffer::Create((size_t)nSize*sizeof(T), p);
            m_nSize = (isEmpty()?0:nSize);
            return ptr;
          }
  int   Resize(int nSize);
  int   Expand(int nSize);
  int   Map(int nSize, int nPos=0, BOOL bToPut=TRUE, YMemoryNotify pf=NULL, void* pInstance=NULL) const
          { return 0; }
  int   Use(int nSize, int nPos=0, BOOL bToPut=TRUE, YMemoryNotify pf=NULL, void* pInstance=NULL) const
          { return 0; }


  void* Clear()
          { return YDynamicBuffer::Clear(m_nSize*sizeof(T)); }
  const T* Copy(T* pData, int nSize, int nPos=0) const
          { YMEMORY_ASSERT(nSize+nPos<=m_nSize); return (const T*)YDynamicBuffer::Copy(pData,nSize*sizeof(T),nPos*sizeof(T)); }
  T*    Copy(const T* pData, int nSize, int nPos=0)
          { YMEMORY_ASSERT(nSize+nPos<=m_nSize); return (T*)YDynamicBuffer::Copy(pData,nSize*sizeof(T),nPos*sizeof(T)); }

  int   GetSize() const
          { return (isEmpty()?0:m_nSize); }
  int   GetBufferSize() const
          { return (isEmpty()?0:m_nSize*sizeof(T)); }

        operator T*()
          { return ((T*)ptr); }
        operator const T*() const 
          { return ((T*)ptr); }

  const T& operator [](int i) const 
          { YMEMORY_ASSERT(i>=0 && i<m_nSize); return ((const T*)ptr)[i]; }
  T&    operator [](int i)
          { YMEMORY_ASSERT(i>=0 && i<m_nSize); return ((T*)ptr)[i]; }
  int   Add(const T& item);

public:
  enum{ SIZEOFITEM = sizeof(T) };
  typedef const T*  constPOINTER;
  typedef T*        POINTER;
  static  int       ITEMS(unsigned cbSize) { YMEMORY_ASSERT(cbSize%sizeof(T)==0); return cbSize/sizeof(T); }
  static  unsigned  BYTES(int nSize)  { return nSize*sizeof(T); }
};

template <class T> inline
  int YDynamicArray<T>::Resize(int nSize) {
    int iRet = YDynamicBuffer::Resize((size_t)nSize*sizeof(T));
    if(iRet==0)
      m_nSize = nSize;
    return(iRet);
  }

template <class T> inline
  int YDynamicArray<T>::Expand(int nSize) {
    if(nSize>m_nSize)
      return Resize(nSize);
    return(0);
  }

template <class T> inline
  int YDynamicArray<T>::Add(const T& item) {
    int iRet = Resize(GetSize()+1);
    if(iRet==0)
      operator[](GetSize()-1) = item;
    return iRet;
  }

template <class T> inline
  int AddNonExist(YDynamicArray<T>& ar, const T& item) {
    for(int i=0; i<ar.GetSize(); ++i)
      if(ar[i]==item)
        return (-4);
    return ar.Add(item);
  }

///////////////////////////////////////////////////////////////////////////
// YVirtualArray<T>: resizeable heap allocated or statically declared array

template <class T>
class YVirtualArray: public YVirtualBuffer
{
  int   m_nSize;
public:
        YVirtualArray(int nSize, void* p=NULL) : YVirtualBuffer((size_t)nSize*sizeof(T), p)
          { m_nSize = (isEmpty()?0:nSize); }
        ~YVirtualArray() 
          {}
        YVirtualArray() : YVirtualBuffer()
          { m_nSize = 0; }

  void* Create(int nSize, void* p=NULL) 
          {
            YVirtualBuffer::Create((size_t)nSize*sizeof(T), p);
            m_nSize = (isEmpty()?0:nSize);
            return ptr;
          }
  int   Resize(int nSize);
  int   Expand(int nSize);
  int   Map(int nSize, int nPos=0, BOOL bToPut=FALSE, YMemoryNotify pf=NULL, void* pInstance=NULL) const;
  int   Use(int nSize, int nPos=0, BOOL bToPut=FALSE, YMemoryNotify pf=NULL, void* pInstance=NULL) const;

  void* Clear()
          { return YVirtualBuffer::Clear(m_nSize*sizeof(T)); }
  const T* Copy(T* pData, int nSize, int nPos=0) const
          { YMEMORY_ASSERT(nSize+nPos<=m_nSize); return (const T*)YVirtualBuffer::Copy(pData,nSize*sizeof(T),nPos*sizeof(T)); }
  T*    Copy(const T* pData, int nSize, int nPos=0)
          { YMEMORY_ASSERT(nSize+nPos<=m_nSize); return (T*)YVirtualBuffer::Copy(pData,nSize*sizeof(T),nPos*sizeof(T)); }

  int   GetSize() const
          { return (isEmpty()?0:m_nSize); }
  int   GetBufferSize() const
          { return (isEmpty()?0:m_nSize*sizeof(T)); }

        operator T*()
          { return ((T*)ptr); }
        operator const T*() const 
          { return ((T*)ptr); }
  const T& operator [](int i) const
          { YMEMORY_ASSERT(i>=0 && i<m_nSize); Use(1,i,FALSE); return ((const T*)ptr)[i]; }
  T&    operator [](int i)
          { YMEMORY_ASSERT(i>=0 && i<m_nSize); Use(1,i,TRUE ); return ((T*)ptr)[i]; }
  int   Add(const T& item);

public:
  enum{ SIZEOFITEM = sizeof(T) };
  typedef const T* constPOINTER;
  typedef T* POINTER;
  static  int      ITEMS(unsigned cbSize) { YMEMORY_ASSERT(cbSize%sizeof(T)==0); return cbSize/sizeof(T); }
  static  unsigned BYTES(int nSize)  { return nSize*sizeof(T); }
};

template <class T> inline
  int YVirtualArray<T>::Resize(int nSize) {
    int iRet = YVirtualBuffer::Resize((size_t)nSize*sizeof(T));
    if(iRet==0)
      m_nSize = nSize;
    return(iRet);
  }

template <class T> inline
  int YVirtualArray<T>::Expand(int nSize) {
    if(nSize>m_nSize)
      return Resize(nSize);
    return(0);
  }

template <class T> inline
  int YVirtualArray<T>::Map(int nSize, int nPos, BOOL bToPut, YMemoryNotify pf, void* pInstance) const {
    int iRet = YVirtualBuffer::Map((size_t)nSize*sizeof(T), (size_t)nPos*sizeof(T), bToPut, pf, pInstance);
    return(iRet);
  }

template <class T> inline
  int YVirtualArray<T>::Use(int nSize, int nPos, BOOL bToPut, YMemoryNotify pf, void* pInstance) const {
    int iRet = YVirtualBuffer::Use((size_t)nSize*sizeof(T), (size_t)nPos*sizeof(T), bToPut, pf, pInstance);
    return(iRet);
  }

template <class T> inline
  int YVirtualArray<T>::Add(const T& item) {
    int iRet = Resize(GetSize()+1);
    if(iRet==0)
      operator[](GetSize()-1) = item;
    return iRet;
  }

template <class T> inline
  int AddNonExist(YVirtualArray<T>& ar, const T& item) {
    for(int i=0; i<ar.GetSize(); ++i)
      if(ar[i]==item)
        return (-4);
    return ar.Add(item);
  }

///////////////////////////////////////////////////////////////////////////
// YBitArray: resizeable array of bits
template <class YARRAY>
class YBitArray: public YARRAY
{
protected:
  int   m_nSizeInBits;
public:
  static size_t bits2items(size_t nSize)
          { return YBit::bits2items(nSize,YARRAY::SIZEOFITEM); }
  static size_t items2bits(size_t nSize)
          { return YBit::items2bits(nSize,YARRAY::SIZEOFITEM); }
public:
        YBitArray(int nSize, void* p=NULL)
          : YARRAY(bits2items(nSize), p)
          { m_nSizeInBits = (isEmpty()?0:nSize);}
        YBitArray() : YARRAY()
          { m_nSizeInBits = 0; }

  void* Create(int nSize, void* p=NULL)
          { m_nSizeInBits = nSize; return YARRAY::Create(bits2items(nSize), p); }
  int   Resize(int nSize)
          { m_nSizeInBits=nSize; return YARRAY::Resize(bits2items(nSize)); }
  int   Expand(int nSize)
          { m_nSizeInBits=nSize; return YARRAY::Expand(bits2items(nSize)); }
  int   Map(int nSize, int nPos=0, BOOL bToPut=FALSE, YMemoryNotify pf=NULL, void* pInstance=NULL) const
          { return YARRAY::Map(bits2items(nSize),bits2items(nSize),bToPut,pf,pInstance); }
  int   Use(int nSize, int nPos=0, BOOL bToPut=FALSE, YMemoryNotify pf=NULL, void* pInstance=NULL) const
          { return YARRAY::Use(bits2items(nSize),bits2items(nSize),bToPut,pf,pInstance); }

  int   GetSize() const
          { return (isEmpty()?0:m_nSizeInBits);}
  int   GetBufferSize() const
          { return YARRAY::GetSize();}
  const YBit operator [](int i) const
          { YMEMORY_ASSERT(i>=0 && i<m_nSizeInBits); Use(1,i,FALSE); return YBit(ptr,i); }
  YBit  operator [](int i)
          { YMEMORY_ASSERT(i>=0 && i<m_nSizeInBits); Use(1,i,TRUE);  return YBit(ptr,i); }

  enum{ SIZEOFITEM=0 }; typedef const unsigned char* constPOINTER; typedef unsigned char* POINTER;
};

// types //////////////////////////////////////////////////////////////////
typedef YStaticArray<char>            YStaticCharArray;
typedef YStaticArray<unsigned char>   YStaticUCharArray;
typedef YStaticArray<int>             YStaticIntArray;
typedef YStaticArray<unsigned int>    YStaticUIntArray;
typedef YStaticArray<long>            YStaticLongArray;
typedef YStaticArray<unsigned long>   YStaticULongArray;
typedef YStaticArray<float>           YStaticFloatArray;
typedef YStaticArray<double>          YStaticDoubleArray;
typedef YStaticArray<long double>     YStaticLDoubleArray;

typedef YDynamicArray<char>           YDynamicCharArray;
typedef YDynamicArray<unsigned char>  YDynamicUCharArray;
typedef YDynamicArray<int>            YDynamicIntArray;
typedef YDynamicArray<unsigned int>   YDynamicUIntArray;
typedef YDynamicArray<long>           YDynamicLongArray;
typedef YDynamicArray<unsigned long>  YDynamicULongArray;
typedef YDynamicArray<float>          YDynamicFloatArray;
typedef YDynamicArray<double>         YDynamicDoubleArray;
typedef YDynamicArray<long double>    YDynamicLDoubleArray;

typedef YVirtualArray<char>           YVirtualCharArray;
typedef YVirtualArray<unsigned char>  YVirtualUCharArray;
typedef YVirtualArray<int>            YVirtualIntArray;
typedef YVirtualArray<unsigned int>   YVirtualUIntArray;
typedef YVirtualArray<long>           YVirtualLongArray;
typedef YVirtualArray<unsigned long>  YVirtualULongArray;
typedef YVirtualArray<float>          YVirtualFloatArray;
typedef YVirtualArray<double>         YVirtualDoubleArray;
typedef YVirtualArray<long double>    YVirtualLDoubleArray;

typedef YStaticArray<YMemory::byte_t>  YStaticByteArray; //byte non-resizable array
typedef YDynamicArray<YMemory::byte_t> YDynamicByteArray;//byte resizable array
typedef YVirtualArray<YMemory::byte_t> YVirtualByteArray;//byte resizable array

typedef YBitArray<YStaticByteArray>   YStaticBitArray;  //bits non-resizable array
typedef YBitArray<YDynamicByteArray>  YDynamicBitArray; //bits resizable array
typedef YBitArray<YVirtualByteArray>  YVirtualBitArray; //bits resizable array

#endif//__cplusplus
///////////////////////////////////////////////////////////////////////////////
#endif//__YARRAY_H
#pragma once
