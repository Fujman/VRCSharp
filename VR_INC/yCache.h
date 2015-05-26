#ifndef __YCACHE_H
#define __YCACHE_H

#include "yCyclic.h"

///////////////////////////////////////////////////////////////////////////////////////
// YCacheBuffer (multithread prepared)
template <class T, class BUFFER=YStaticBuffer>
class YCacheBuffer: public YCyclicBuffer<T>
{
protected:
  BUFFER  m_buffer;
  int     m_nTile;
public:                                                                //types::
  typedef YCacheData<T> YData;
public:                                             //construction/destruction::
  YCacheBuffer(int nSize, int nTile=-1, T* p=NULL) : //throw CMemoryException on error
          m_nTile(nTile<0?nSize:nTile),
          m_buffer((size_t)(nSize+m_nTile)*sizeof(T), p),
          YCyclicBuffer<T>((size_t)nSize, (T*)(void*)m_buffer) 
          {}
  YCacheBuffer()
          {}
  ~YCacheBuffer() 
          {}

  void*   Create(int nSize, int nTile=-1, T* p=NULL)
          { 
            m_nTile = (nTile<0?nSize:nTile);
            return (NULL==m_buffer.Create((size_t)(nSize+m_nTile)*sizeof(T),p) ? NULL: //AY 08.11.2007 OLD: Create((size_t)(nSize+m_nTile)*sizeof(T)): p not used!
            YCyclicBuffer<T>::Create((size_t)nSize, (T*)(void*)m_buffer));
          }
  int     Free()
            { return YCyclicBuffer<T>::Free(), m_buffer.Free(), m_nTile=0; }

  int     GetCacheSize() const
            { return GetArraySize(); }
  int     GetCacheTile() const
            { return m_nTile; }
public:
  const T* GetPtr() const
            { return (const T*)ptr; }
  T*      GetPtr()
            { return (T*)ptr; }
};

#endif//__YCACHE_H
#pragma once
