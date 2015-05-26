#ifndef __VMALLOC_H
#define __VMALLOC_H
#include <malloc.h>
#include "fs/v_malloc.h"

#ifndef AFXAPI
void __stdcall AfxThrowMemoryException();
#else
void AFXAPI    AfxThrowMemoryException();
#endif

#define vmalloc  v_malloc
#define vrealloc v_realloc
#define vfree    v_free

#ifdef  __cplusplus
extern "C" {
#endif

  void* throwed_vmalloc(size_t size, LPVOID* pBuffer=NULL);
  void* throwed_vrealloc(LPVOID& pBuffer, size_t size, BOOL bDeleteOnError=TRUE);
  void* throwed_vfree(LPVOID& pBuffer);

#ifdef  __cplusplus
}
#endif

#ifdef  __cplusplus

  inline void* throwed_vmalloc(size_t size, LPVOID* ppBuffer) {
    if(ppBuffer!=NULL)
      *ppBuffer = NULL;
    void* p = v_malloc(size);
    if(p==NULL)
      AfxThrowMemoryException();
    if(ppBuffer!=NULL)
      *ppBuffer = p;
    return p;
  }

  inline void* throwed_vfree(LPVOID& pBuffer) {
    if(pBuffer!=NULL)
      v_free(pBuffer);
    return (pBuffer = NULL);
  }

  inline void* throwed_vrealloc(LPVOID& pBuffer, size_t size, BOOL bDeleteOnError/*TRUE*/) {
    if(pBuffer==NULL)
      return throwed_vmalloc(size,&pBuffer);
    void* p = v_realloc(pBuffer, size);
    if(p==NULL && bDeleteOnError)
      throwed_vfree(pBuffer);
    if(p==NULL)
      AfxThrowMemoryException();
    return (pBuffer = p);
  }
#endif//__cplusplus

#endif//__VMALLOC_H
#pragma once