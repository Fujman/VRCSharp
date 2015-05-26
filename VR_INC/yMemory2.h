#ifndef __YMEMORY2_H
#define __YMEMORY2_H
#include "YPointer.h"
#include "YMemBase.h"

// C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus

class YExternBuffer;      // YExternBuffer(size,ptr=NULL),Resize,Expand,Free,Use

///////////////////////////////////////////////////////////////////////////
// YExternBuffer: resizeable disk allocated or statically declared buffer

class YExternBuffer : public YMappableMemory // size is not saved! size in bytes (.CPP implementation)
{
protected:
  void*         ptr;
  int           bAutoDelete;
public:
                YExternBuffer(filesize_t nSize, void* p=NULL)
                  { ptr = NULL; Create(nSize,p); }
                ~YExternBuffer()
                  { Free(); }
                YExternBuffer()
                  { ptr = NULL; bAutoDelete = 1; }

  void*         Create(filesize_t nSize, void* p=NULL);
  int           Free();
  int           Resize(filesize_t nSize);
  int           Expand(filesize_t& nSize, filesize_t nNewSize);
  int           Map(filesize_t nSize, filesize_t nPos=0, BOOL bToPut=FALSE, YMemoryNotify pf=NULL, void* pInstance=NULL) const;
  int           Use(filesize_t nSize, filesize_t nPos=0, BOOL bToPut=FALSE, YMemoryNotify pf=NULL, void* pInstance=NULL) const;

  void*         Clear(filesize_t nSize);
  const void*   Copy(void* pData, size_t nSize, filesize_t nPos=0) const;
  void*         Copy(const void* pData, size_t nSize, filesize_t nPos=0);

  void*         GetPage() const
                  { return (isPaged()?e_page(ptr):ptr); }
  filesize_t    GetOffs() const
                  { return (isPaged()?e_offs(ptr):0);   }
  filesize_t    GetSize() const
                  { return (isPaged()?e_size(ptr):0);   }
  filesize_t    GetBufferSize() const
                  { return (isPaged()?e_size(ptr):0); }

  int           isAutoDelete() const
                  { return(bAutoDelete); }
  int           isEmpty() const
                  { return(ptr==NULL); }
  int           isPaged() const
                  { return(ptr!=NULL && bAutoDelete); }

  byte_t&       operator [](filesize_t i) const
                  { YMEMORY_ASSERT(GetPage() && i>=GetOffs()); return *((byte_t*)GetPage()+i-GetOffs() ); }
protected:
  byte_t*       __GetData(filesize_t nNeeded=0) const;
public:
  DEFINE_ALL_PTR_CONVERSIONS_OPERATORS( __GetData() );
};

///////////////////////////////////////////////////////////////////////////
// YExternMemory: resizeable heap allocated or statically declared array

class YExternMemory: public YExternBuffer
{
  filesize_t    m_nSize;
public:
                YExternMemory(filesize_t nSize, void* p=NULL) : YExternBuffer(nSize, p)
                  { m_nSize = (isEmpty()?0:nSize); }
                ~YExternMemory() 
                  {}
                YExternMemory() : YExternBuffer()
                  { m_nSize = 0; }

  void*         Create(filesize_t nSize, void* p=NULL);
  int           Resize(filesize_t nSize);
  int           Expand(filesize_t nSize);
  int           Map(filesize_t nSize, filesize_t nPos=0, BOOL bToPut=FALSE, YMemoryNotify pf=NULL, void* pInstance=NULL) const;
  int           Use(filesize_t nSize, filesize_t nPos=0, BOOL bToPut=FALSE, YMemoryNotify pf=NULL, void* pInstance=NULL) const;

  byte_t*       Clear();
  const byte_t* Copy(      byte_t* pData, size_t nSize, filesize_t nPos=0) const;
  byte_t*       Copy(const byte_t* pData, size_t nSize, filesize_t nPos=0);


  filesize_t    GetSize() const
                  { return m_nSize; }
  filesize_t    GetBufferSize() const
                  { return m_nSize; }

                operator const byte_t*() const
                  { return __GetData(m_nSize); }
                operator       byte_t*()
                  { return __GetData(m_nSize); }
  const byte_t& operator [](filesize_t i) const
                  { YMEMORY_ASSERT(i>=0 && i<m_nSize); Use(1,i,FALSE); return *((const byte_t*)GetPage()+i-GetOffs()); }
  byte_t&       operator [](filesize_t i)
                  { YMEMORY_ASSERT(i>=0 && i<m_nSize); Use(1,i,TRUE ); return *((      byte_t*)GetPage()+i-GetOffs()); }

public:
  enum{ SIZEOFITEM = sizeof(byte_t) };
  typedef const byte_t* constPOINTER;
  typedef byte_t* POINTER;
  static  size_t   ITEMS(unsigned cbSize) { return cbSize; }
  static  unsigned BYTES(size_t nSize)  { return nSize; }
};

  inline void* YExternMemory::Create(filesize_t nSize, void* p) { 
    YExternBuffer::Create(nSize, p);
    m_nSize = (isEmpty()?0:nSize);
    return ptr;
  }

  inline int YExternMemory::Resize(filesize_t nSize) {
    int iRet = YExternBuffer::Resize(nSize);
    if(iRet==0)
      m_nSize = nSize;
    return(iRet);
  }

  inline int YExternMemory::Expand(filesize_t nSize) {
    if(nSize>m_nSize)
      return Resize(nSize);
    return(0);
  }

  inline int YExternMemory::Map(filesize_t nSize, filesize_t nPos, BOOL bToPut, YMemoryNotify pf, void* pInstance) const
    { return YExternBuffer::Map(nSize, nPos, bToPut, pf, pInstance); }

  inline int YExternMemory::Use(filesize_t nSize, filesize_t nPos, BOOL bToPut, YMemoryNotify pf, void* pInstance) const
    { return YExternBuffer::Use(nSize, nPos, bToPut, pf, pInstance); }

  inline YExternMemory::byte_t* YExternMemory::Clear()
    { return (byte_t*)YExternBuffer::Clear(m_nSize); }

  inline const YExternMemory::byte_t* YExternMemory::Copy(      byte_t* pData, size_t nSize, filesize_t nPos) const
    { YMEMORY_ASSERT(nSize+nPos<=m_nSize); return (const byte_t*)YExternBuffer::Copy((void*)pData,nSize,nPos); }

  inline       YExternMemory::byte_t* YExternMemory::Copy(const byte_t* pData, size_t nSize, filesize_t nPos)
    { YMEMORY_ASSERT(nSize+nPos<=m_nSize); return (byte_t*)YExternBuffer::Copy((const void*)pData,nSize,nPos); }

#endif//__cplusplus
///////////////////////////////////////////////////////////////////////////////
#endif//__YMEMORY2_H
#pragma once
