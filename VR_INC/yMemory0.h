#ifndef __YMEMORY0_H
#define __YMEMORY0_H
#include "YPointer.h"
#include "YMemBase.h"

// C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus

class YStaticBuffer;      // YStaticBuffer(size,ptr=NULL)
class YDynamicBuffer;     // YDynamicBuffer(size,ptr=NULL),Resize,Expand,Free

///////////////////////////////////////////////////////////////////////////
// YStaticBuffer: non-resizable heap allocated or statically declared buffer

class YStaticBuffer : public YMappableMemory // size is not saved! size in bytes
{
protected:
  void* ptr;
  int   bAutoDelete;
public:
        YStaticBuffer(size_t nSize, void* p=NULL)  //throw CMemoryException on error
          { ptr = NULL; Create(nSize,p); }
        ~YStaticBuffer()
          { Free(); }
        YStaticBuffer() 
          { ptr = NULL; bAutoDelete = 0; }

  void* Create(size_t nSize, void* p=NULL);  //throw CMemoryException on error
  int   Free();
  int   Resize(size_t nSize)
          { ASSERT(0); return -1; } // to compatibility with YDynamicBuffer in templates
  int   Expand(size_t& nSize, size_t nNewSize)
          { ASSERT(0); return -1; } // to compatibility with YDynamicBuffer in templates
//int   Map(size_t nSize, size_t nPos=0, BOOL bToPut=TRUE, YMemoryNotify pf=NULL, void* pInstance=NULL) const
//        { return 0; }
//int   Use(size_t nSize, size_t nPos=0, BOOL bToPut=TRUE, YMemoryNotify pf=NULL, void* pInstance=NULL) const
//        { return 0; }

  void* Clear(size_t nSize)
          { return memset(ptr,0,nSize); }
  const void* Copy(void* pData, size_t nSize, size_t nPos=0) const
          { memcpy(pData,((const byte_t*)ptr)+nPos,nSize); return ((const byte_t*)ptr)+nPos; }
  void* Copy(const void* pData, size_t nSize, size_t nPos=0)
          { memcpy(((byte_t*)ptr)+nPos,pData, nSize); return ((byte_t*)ptr)+nPos; }
  int   isAutoDelete() const
          { return(bAutoDelete); }
  int   isEmpty() const
          { return(ptr==NULL); }

  byte_t& operator [](unsigned long i) const
          { return((byte_t *)ptr)[i]; }
  DEFINE_ALL_PTR_CONVERSIONS_OPERATORS(ptr);
};

inline void* YStaticBuffer::Create(size_t nSize, void* p/*NULL*/) {
  YMEMORY_ASSERT(ptr==NULL);
  if(p==NULL) {
    bAutoDelete = 1;
    if(nSize==0)
      { ASSERT("AY modified algorythm at 16.07.2004"); nSize = 1; }
    ptr = new char[nSize];
  }else{
    ptr = p;
    bAutoDelete = 0;
  }
  return ptr;
}
inline int  YStaticBuffer::Free() {
  if(bAutoDelete && ptr!=NULL)
    delete [] ptr;
  ptr = NULL; bAutoDelete = 0;
  return 0;
}

///////////////////////////////////////////////////////////////////////////
// YDynamicBuffer: resizeable heap allocated or statically declared buffer

class YDynamicBuffer: public YMappableMemory // size is not saved! size in bytes (.CPP implementation)
{
protected:
  void* ptr;
  int   bAutoDelete;
public:
        YDynamicBuffer(size_t nSize, void* p=NULL)
          { ptr = NULL; Create(nSize,p); }
        ~YDynamicBuffer()
          { Free(); }
        YDynamicBuffer()
          { ptr = NULL; bAutoDelete = 1; }

  void* Create(size_t nSize, void* p=NULL);
  int   Free();
  int   Resize(size_t nSize);
  int   Expand(size_t& nSize, size_t nNewSize);
//int   Map(size_t nSize, size_t nPos=0, BOOL bToPut=TRUE, YMemoryNotify pf=NULL, void* pInstance=NULL) const
//        { return 0; }
//int   Use(size_t nSize, size_t nPos=0, BOOL bToPut=TRUE, YMemoryNotify pf=NULL, void* pInstance=NULL) const
//        { return 0; }

  void* Clear(size_t nSize)
          { return memset(ptr,0,nSize); }
  const void* Copy(void* pData, size_t nSize, size_t nPos=0) const
          { memcpy(pData,((const byte_t*)ptr)+nPos,nSize); return ((const byte_t*)ptr)+nPos; }
  void* Copy(const void* pData, size_t nSize, size_t nPos=0)
          { memcpy(((byte_t*)ptr)+nPos,pData, nSize); return ((byte_t*)ptr)+nPos; }

  int   isAutoDelete() const
          { return(bAutoDelete); }
  int   isEmpty() const
          { return(ptr==NULL); }

  byte_t& operator [](unsigned long i) const
          { return((byte_t *)ptr)[i]; }
  DEFINE_ALL_PTR_CONVERSIONS_OPERATORS(ptr);
};

///////////////////////////////////////////////////////////////////////////
// YStaticMamory: non-resizeable heap allocated or statically declared array

class YStaticMemory: public YStaticBuffer
{
  size_t m_nSize;
public:
        YStaticMemory(size_t nSize, void* p=NULL) : YStaticBuffer(nSize, p)
          { m_nSize = (isEmpty()?0:nSize); }
        ~YStaticMemory() 
          {}
        YStaticMemory() : YStaticBuffer()
          { m_nSize = 0; }

  void* Create(size_t nSize, void* p=NULL)      //throw CMemoryException on error
          {
            YStaticBuffer::Create(nSize, p);
            m_nSize = (isEmpty()?0:nSize);
            return ptr;
          }
  int   Resize(size_t nSize)
          { ASSERT(0); return -1; } // to compatibility with YDynamicBuffer in templates
  int   Expand(size_t nSize)
          { ASSERT(0); return -1; } // to compatibility with YDynamicBuffer in templates
  int   Map(size_t nSize, size_t nPos=0, BOOL bToPut=TRUE, YMemoryNotify pf=NULL, void* pInstance=NULL) const
          { return 0; }
  int   Use(size_t nSize, size_t nPos=0, BOOL bToPut=TRUE, YMemoryNotify pf=NULL, void* pInstance=NULL) const
          { return 0; }

  byte_t* Clear()
          { return (byte_t*)YStaticBuffer::Clear(m_nSize); }
  const byte_t* Copy(byte_t* pData, size_t nSize, size_t nPos=0) const
          { YMEMORY_ASSERT(nSize+nPos<=m_nSize); return (const byte_t*)YStaticBuffer::Copy((void*)pData,nSize,nPos); }
  byte_t*       Copy(const byte_t* pData, size_t nSize, size_t nPos=0)
          { YMEMORY_ASSERT(nSize+nPos<=m_nSize); return (byte_t*)YStaticBuffer::Copy((const void*)pData,nSize,nPos); }

  size_t GetSize() const
          { return (isEmpty()?0:m_nSize); }
  size_t GetBufferSize() const
          { return (isEmpty()?0:m_nSize); }
        operator byte_t*() 
          { return ((byte_t*)ptr); }
        operator const byte_t*() const
          { return ((const byte_t*)ptr); }//AY 1.07.2002

  const byte_t& operator [](size_t i) const
          { YMEMORY_ASSERT(i>=0 && i<m_nSize); return ((const byte_t*)ptr)[i]; }
  byte_t& operator [](size_t i)
          { YMEMORY_ASSERT(i>=0 && i<m_nSize); return ((byte_t*)ptr)[i]; }

public:
  enum{ SIZEOFITEM = sizeof(byte_t) };
  typedef const byte_t*  constPOINTER;
  typedef byte_t*        POINTER;
  static  size_t    ITEMS(unsigned cbSize) { return cbSize; }
  static  unsigned  BYTES(size_t nSize)    { return nSize; }
};

///////////////////////////////////////////////////////////////////////////
// YDynamicMemory: resizeable heap allocated or statically declared array

class YDynamicMemory: public YDynamicBuffer
{
  size_t m_nSize;
public:
        YDynamicMemory(size_t nSize, void* p=NULL) : YDynamicBuffer(nSize, p)
          { m_nSize = (isEmpty()?0:nSize); }
        ~YDynamicMemory() 
          {}
        YDynamicMemory() : YDynamicBuffer()
          { m_nSize = 0; }

  void* Create(size_t nSize, void* p=NULL)
          {
            YDynamicBuffer::Create(nSize, p);
            m_nSize = (isEmpty()?0:nSize);
            return ptr;
          }
  int   Resize(size_t nSize);
  int   Expand(size_t nSize);
  int   Map(size_t nSize, size_t nPos=0, BOOL bToPut=TRUE, YMemoryNotify pf=NULL, void* pInstance=NULL) const
          { return 0; }
  int   Use(size_t nSize, size_t nPos=0, BOOL bToPut=TRUE, YMemoryNotify pf=NULL, void* pInstance=NULL) const
          { return 0; }


  byte_t* Clear()
          { return (byte_t*)YDynamicBuffer::Clear(m_nSize); }
  const byte_t* Copy(byte_t* pData, size_t nSize, size_t nPos=0) const
          { YMEMORY_ASSERT(nSize+nPos<=m_nSize); return (const byte_t*)YDynamicBuffer::Copy((void*)pData,nSize,nPos); }
  byte_t*    Copy(const byte_t* pData, size_t nSize, size_t nPos=0)
          { YMEMORY_ASSERT(nSize+nPos<=m_nSize); return (byte_t*)YDynamicBuffer::Copy((const void*)pData,nSize,nPos); }

  size_t GetSize() const
          { return (isEmpty()?0:m_nSize); }
  size_t GetBufferSize() const
          { return (isEmpty()?0:m_nSize); }

        operator byte_t*()
          { return ((byte_t*)ptr); }
        operator const byte_t*() const 
          { return ((byte_t*)ptr); }

  const byte_t& operator [](size_t i) const 
          { YMEMORY_ASSERT(i>=0 && i<m_nSize); return ((const byte_t*)ptr)[i]; }
  byte_t& operator [](size_t i)
          { YMEMORY_ASSERT(i>=0 && i<m_nSize); return ((byte_t*)ptr)[i]; }
  int   Add(const byte_t& item);

public:
  enum{ SIZEOFITEM = sizeof(byte_t) };
  typedef const byte_t*  constPOINTER;
  typedef byte_t*        POINTER;
  static  size_t         ITEMS(unsigned cbSize) { return cbSize; }
  static  unsigned       BYTES(size_t nSize)  { return nSize; }
};
  
  inline int YDynamicMemory::Resize(size_t nSize) {
    int iRet = YDynamicBuffer::Resize(nSize);
    if(iRet==0)
      m_nSize = nSize;
    return(iRet);
  }

  inline int YDynamicMemory::Expand(size_t nSize) {
    if(nSize>m_nSize)
      return Resize(nSize);
    return(0);
  }

  inline int YDynamicMemory::Add(const byte_t& item) {
    int iRet = Resize(GetSize()+1);
    if(iRet==0)
      operator[](GetSize()-1) = item;
    return iRet;
  }

  inline int AddNonExist(YDynamicMemory& ar, const YDynamicMemory::byte_t& item) {
    for(size_t i=0; i<ar.GetSize(); ++i)
      if(ar[i]==item)
        return (-4);
    return ar.Add(item);
  }


#endif//__cplusplus
///////////////////////////////////////////////////////////////////////////////
#endif//__YMEMORY_H
#pragma once
