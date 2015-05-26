#ifndef __YMEMORY1_H
#define __YMEMORY1_H
#include "YPointer.h"
#include "YMemBase.h"

// C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus

class YVirtualBuffer;     // YVirtualBuffer(size,ptr=NULL),Resize,Expand,Free,Use

///////////////////////////////////////////////////////////////////////////
// YVirtualBuffer: resizeable disk allocated or statically declared buffer

class YVirtualBuffer : public YMappableMemory // size is not saved! size in bytes (.CPP implementation)
{
protected:
  void* ptr;
  int   bAutoDelete;
public:
        YVirtualBuffer(size_t nSize, void* p=NULL)
          { ptr = NULL; Create(nSize,p); }
        ~YVirtualBuffer()
          { Free(); }
        YVirtualBuffer()
          { ptr = NULL; bAutoDelete = 1; }

  void* Create(size_t nSize, void* p=NULL);
  int   Free();
  int   Resize(size_t nSize);
  int   Expand(size_t& nSize, size_t nNewSize);
  int   Map(size_t nSize, size_t nPos=0, BOOL bToPut=FALSE, YMemoryNotify pf=NULL, void* pInstance=NULL) const;
  int   Use(size_t nSize, size_t nPos=0, BOOL bToPut=FALSE, YMemoryNotify pf=NULL, void* pInstance=NULL) const;

  void* Clear(size_t nSize)
          { Use(nSize,0,TRUE); return memset(ptr,0,nSize); }
  const void* Copy(void* pData, size_t nSize, size_t nPos=0) const
          { memcpy(pData,((const char*)ptr)+nPos,nSize); return ((const char*)ptr)+nPos; }
  void* Copy(const void* pData, size_t nSize, size_t nPos=0)
          { memcpy(((char*)ptr)+nPos,pData, nSize); return ((char*)ptr)+nPos; }

  int   isAutoDelete() const
          { return(bAutoDelete); }
  int   isEmpty() const
          { return(ptr==NULL); }

  byte_t& operator [](unsigned long i) const
          { return((unsigned char *)ptr)[i]; }
  DEFINE_ALL_PTR_CONVERSIONS_OPERATORS(ptr);
};

///////////////////////////////////////////////////////////////////////////
// YVirtualMemory: resizeable heap allocated or statically declared array

class YVirtualMemory: public YVirtualBuffer
{
  size_t m_nSize;
public:
        YVirtualMemory(size_t nSize, void* p=NULL) : YVirtualBuffer(nSize, p)
          { m_nSize = (isEmpty()?0:nSize); }
        ~YVirtualMemory() 
          {}
        YVirtualMemory() : YVirtualBuffer()
          { m_nSize = 0; }

  void* Create(size_t nSize, void* p=NULL)
          {
            YVirtualBuffer::Create(nSize, p);
            m_nSize = (isEmpty()?0:nSize);
            return ptr;
          }
  int   Resize(size_t nSize);
  int   Expand(size_t nSize);
  int   Map(size_t nSize, size_t nPos=0, BOOL bToPut=FALSE, YMemoryNotify pf=NULL, void* pInstance=NULL) const;
  int   Use(size_t nSize, size_t nPos=0, BOOL bToPut=FALSE, YMemoryNotify pf=NULL, void* pInstance=NULL) const;

  byte_t* Clear()
          { return (byte_t*)YVirtualBuffer::Clear(m_nSize); }
  const byte_t* Copy(byte_t* pData, size_t nSize, size_t nPos=0) const
          { YMEMORY_ASSERT(nSize+nPos<=m_nSize); return (const byte_t*)YVirtualBuffer::Copy((void*)pData,nSize,nPos); }
  byte_t*    Copy(const byte_t* pData, size_t nSize, size_t nPos=0)
          { YMEMORY_ASSERT(nSize+nPos<=m_nSize); return (byte_t*)YVirtualBuffer::Copy((const void*)pData,nSize,nPos); }

  size_t GetSize() const
          { return (isEmpty()?0:m_nSize); }
  size_t GetBufferSize() const
          { return (isEmpty()?0:m_nSize); }

        operator byte_t*()
          { return ((byte_t*)ptr); }
        operator const byte_t*() const 
          { return ((byte_t*)ptr); }
  const byte_t& operator [](size_t i) const
          { YMEMORY_ASSERT(i>=0 && i<m_nSize); Use(1,i,FALSE); return ((const byte_t*)ptr)[i]; }
  byte_t& operator [](size_t i)
          { YMEMORY_ASSERT(i>=0 && i<m_nSize); Use(1,i,TRUE ); return ((byte_t*)ptr)[i]; }
  int   Add(const byte_t& item);

public:
  enum{ SIZEOFITEM = sizeof(byte_t) };
  typedef const byte_t* constPOINTER;
  typedef byte_t* POINTER;
  static  size_t   ITEMS(unsigned cbSize) { return cbSize; }
  static  unsigned BYTES(size_t nSize)  { return nSize; }
};

  inline int YVirtualMemory::Resize(size_t nSize) {
    int iRet = YVirtualBuffer::Resize(nSize);
    if(iRet==0)
      m_nSize = nSize;
    return(iRet);
  }

  inline int YVirtualMemory::Expand(size_t nSize) {
    if(nSize>m_nSize)
      return Resize(nSize);
    return(0);
  }

  inline int YVirtualMemory::Map(size_t nSize, size_t nPos, BOOL bToPut, YMemoryNotify pf, void* pInstance) const {
    int iRet = YVirtualBuffer::Map(nSize, nPos, bToPut, pf, pInstance);
    return(iRet);
  }

  inline int YVirtualMemory::Use(size_t nSize, size_t nPos, BOOL bToPut, YMemoryNotify pf, void* pInstance) const {
    int iRet = YVirtualBuffer::Use(nSize, nPos, bToPut, pf, pInstance);
    return(iRet);
  }

  inline int YVirtualMemory::Add(const byte_t& item) {
    int iRet = Resize(GetSize()+1);
    if(iRet==0)
      operator[](GetSize()-1) = item;
    return iRet;
  }

  inline int AddNonExist(YVirtualMemory& ar, const YVirtualMemory::byte_t& item) {
    for(size_t i=0; i<ar.GetSize(); ++i)
      if(ar[i]==item)
        return (-4);
    return ar.Add(item);
  }

#endif//__cplusplus
///////////////////////////////////////////////////////////////////////////////
#endif//__YMEMORY1_H
#pragma once
