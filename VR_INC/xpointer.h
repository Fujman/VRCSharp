#ifndef __XPOINTER_H
#define __XPOINTER_H
#include <malloc.h>

// C,C++ declarations \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

#define SAFE_RELEASE(p)                 ( (p) ? (p)->Release(), (p)=NULL : 0 )

#define SAFE_DELETE_MEMORY(p)           ( (p) ? free      (p), (p)=NULL : 0 )
#define SAFE_FREE(p)                    SAFE_DELETE_MEMORY(p)

#define SAFE_RECALLOC(p,t,n)            ( (p) = (t*)__safe_recalloc((p),(n)*sizeof(t)) ) 

__inline void* __safe_recalloc(void* data, size_t size)
{
  void* p = NULL;
  if(data==NULL)
    return calloc(size,1);
  p = realloc(data, size);
  if(p==NULL && size>0)
    free(data);//prevent memory leak!
  if(p!=NULL)
    memset(p,0,size);
  return p;
}


// C++ declarations \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus

#define SAFE_DELETE_POINTER(p)          ( (p) ? delete    (p), (p)=NULL : 0 )
#define SAFE_DELETE_ARRAY(p)            ( (p) ? delete [] (p), (p)=NULL : 0 )
#define SAFE_DELETE_POINTER_AS(p,t)     ( (p) ? delete    (t*)(p), (p)=NULL : 0 )
#define SAFE_DELETE_ARRAY_AS(p,t)       ( (p) ? delete [] (t*)(p), (p)=NULL : 0 )

#define SAFE_DELETE(p)                  SAFE_DELETE_POINTER(p)
#define SAFE_DELETE_AS(p,t)             SAFE_DELETE_POINTER_AS(p,t)

#endif __cplusplus

////////////////////////////////////////////////////////////////////////////////////

#endif//__XPOINTER_H
#pragma once