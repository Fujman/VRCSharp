#ifndef __YBIT_H
#define __YBIT_H
#ifndef __YMEMORY_H
#include "YMemory.h"
#endif
// C section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

#ifndef bitsof
#define bitsof(i)             (sizeof(i)*8)
#endif

// C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus

class YBit; template <class A> class YBitArray;

///////////////////////////////////////////////////////////////////////////////
// YBit - single bit in memory buffer representation
class YBit {// attention! parent memory buffer can't be moved or deleted while YBit is live!
public:
  typedef YMappableMemory::byte_t byte_t;
  enum
    { SIZEOF=sizeof(byte_t)*8/*bits*/ };
  static size_t bits2items(size_t nSize, size_t nSizeOfItem)
    { return (nSize+(nSizeOfItem*SIZEOF)-1)/(nSizeOfItem*SIZEOF); }
  static size_t items2bits(size_t nSize, size_t nSizeOfItem)
    { return nSize*nSizeOfItem*SIZEOF; }
  static size_t bits2bytes(size_t nSize) 
    { return (nSize+SIZEOF-1)/SIZEOF; }
  static size_t bytes2bits(size_t nSize) 
    { return nSize*SIZEOF; }
protected:
  byte_t* ptr;
  size_t  bit;
public://ATTENTION! The logic of YBit(YBit& ) and operator=(YBit&) mithmatch!
  YBit(const YBit& b)
    { ptr=b.ptr; bit=b.bit; YMEMORY_TRACE(TRACE("YBit(const YBit& b)%8.8X:%8.8X %u  :  %d\n",this,ptr,bit,(int)operator byte_t())); }
  YBit(void *p, int n)
    { YMEMORY_ASSERT(p!=NULL); ptr=(byte_t*)p; bit=n; YMEMORY_TRACE(TRACE("\nYBit(void *p, int n)%8.8X:%8.8X %u  :  %d\n",this,ptr,bit,(int)operator byte_t())); }
  YBit(byte_t b)
    { ptr=NULL; bit=(b?1:0); YMEMORY_TRACE(TRACE("YBit(byte_t b):%8.8X %u\n",ptr,bit)); }

  operator byte_t() const
    { return NULL==ptr?bit:(((ptr[bit/SIZEOF]) >> (bit%SIZEOF)) & 0x01); }

  byte_t  operator = (byte_t b) {
    YMEMORY_TRACE(TRACE("YBit::operator = (byte_t b)%8.8X:%8.8X %u  =  %d\n",this,ptr,bit,(int)b));
    if(NULL==ptr)
      return (bit = (b?1:0));
    if(b) {
      ptr[bit/SIZEOF] |= (0x01<<(bit%SIZEOF)); 
      return 1;
    }else{
      ptr[bit/SIZEOF] &= ~(0x01<<(bit%SIZEOF)); 
      return 0;
    }
  }
  YBit&   operator = (const YBit& b)
    { operator =((byte_t)b); YMEMORY_TRACE(TRACE("*** YBit::operator =(const YBit& b)%8.8X:%8.8X %u  :  %d\n",this,ptr,bit,(int)operator byte_t())); return *this; }

public://debug
#ifdef YMEMORY_DEBUG
  ~YBit()
    { YMEMORY_TRACE(TRACE("\n~YBit()%8.8X\n",this)); }
  int Dump() const
    { YMEMORY_TRACE(TRACE("\nYBit::Dump()%8.8X:%8.8X %u  :  %d\n",this,ptr,bit,(int)operator byte_t())); return 0; }
#else
  int Dump() const { return 0; }
#endif
};

#endif//__cplusplus
#endif//__YBIT_H
#pragma once