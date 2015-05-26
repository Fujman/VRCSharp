#ifndef __YMEMBASE_H
#define __YMEMBASE_H

// C section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

#ifdef ASSERT
  #define YMEMORY_ASSERT(b) ASSERT(b)
#else
  #define YMEMORY_ASSERT(b) 
  #pragma message("Warning: ASSERT is not defined!")
#endif

#ifdef YMEMORY_DEBUG
  #define YMEMORY_TRACE(s) s
#else
  #define YMEMORY_TRACE(s)
#endif

// C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus

class YMemory;
class YMappableMemory;

///////////////////////////////////////////////////////////////////////////
// YMemory

class YMemory
{
  public:
    typedef unsigned char byte_t;
    typedef unsigned      size_t;
    typedef int           index_t;
    typedef void*         ptr_t;
};

///////////////////////////////////////////////////////////////////////////
// YMappableMemory

typedef int (*YMemoryNotify)(void* p, size_t size, size_t pos, int bToStore, void* pInstance);

class YMappableMemory: public YMemory
{
public: enum {toREAD=0, toFULL=1, toFREE=-1, toKILL=-2}; //see V_MALLOC.H
public: enum {toSTORE=1, toLOAD=0};                      //see V_MALLOC.H
public: int   Map( //reserve memory
                size_t nSize, 
                size_t nPos=0, 
                BOOL bToWrite=TRUE,
                YMemoryNotify pf=NULL, 
                void* pInstance=NULL
              ) const
                { ASSERT(!"debug"); return 0; }
public: int   Use( //prepare memory
                size_t nSize, 
                size_t nPos=0, 
                BOOL bToWrite=TRUE,
                YMemoryNotify pf=NULL, 
                void* pInstance=NULL
              ) const
                { return 0; }
public: void*  GetPage() const
                { return 0; }
public: size_t GetOffs() const
                { return 0; }
};


#endif//__cplusplus
///////////////////////////////////////////////////////////////////////////////
#endif//__YMEMBASE_H
#pragma once
