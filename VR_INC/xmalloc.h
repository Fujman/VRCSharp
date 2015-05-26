#ifndef __XMALLOC_H
#define __XMALLOC_H

#ifndef AFXAPI
void __stdcall AfxThrowMemoryException();
#else
void AFXAPI    AfxThrowMemoryException();
#endif

#include <malloc.h>
#ifdef  __cplusplus
extern "C" {
#endif

  void* throwed_malloc(size_t size, LPVOID* pBuffer=NULL);
  void* throwed_realloc(LPVOID& pBuffer, size_t size, BOOL bDeleteOnError=TRUE);
  void* throwed_free(LPVOID& pBuffer);

#ifdef  __cplusplus
}
#endif

#ifdef  __cplusplus
  inline void* throwed_malloc(size_t size, LPVOID* ppBuffer) {
    if(ppBuffer!=NULL)
      *ppBuffer = NULL;
    void* p = malloc(size);
    if(p==NULL)
      ::AfxThrowMemoryException();
    if(ppBuffer!=NULL)
      *ppBuffer = p;
    return p;
  }

  inline void* throwed_free(LPVOID& pBuffer) {
    if(pBuffer!=NULL)
      free(pBuffer);
    return (pBuffer = NULL);
  }

  inline void* throwed_realloc(LPVOID& pBuffer, size_t size, BOOL bDeleteOnError/*TRUE*/) {
    if(pBuffer==NULL)
      return throwed_malloc(size,&pBuffer);
    void* p = realloc(pBuffer, size);
    if(p==NULL && bDeleteOnError)
      throwed_free(pBuffer);
    if(p==NULL)
      ::AfxThrowMemoryException();
    return (pBuffer = p);
  }
#endif//__cplusplus

#endif//__XMALLOC_H
#pragma once