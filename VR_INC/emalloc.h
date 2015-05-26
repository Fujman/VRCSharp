#ifndef __EMALLOC_H
#define __EMALLOC_H
#include <malloc.h>
#include "fs/e_malloc.h"

#ifndef AFXAPI
void __stdcall AfxThrowMemoryException();
#else
void AFXAPI    AfxThrowMemoryException();
#endif

#define emalloc  e_malloc
#define erealloc e_realloc
#define efree    e_free
#define euse     e_use

#ifdef  __cplusplus
extern "C" {
#endif

  const void* throwed_emalloc(filesize_t size, const void* *pBuffer=NULL);
  const void* throwed_erealloc(const void*& pBuffer, filesize_t size, BOOL bDeleteOnError=TRUE);
  const void* throwed_efree(const void*& pBuffer);
  void* throwed_euse(const void* pBuffer, filesize_t size, filesize_t offs);

#ifdef  __cplusplus
}
#endif

#ifdef  __cplusplus
  inline const void* throwed_emalloc(filesize_t size, const void* *ppBuffer) {
    if(ppBuffer!=NULL)
      *ppBuffer = NULL;
    const void* p = e_malloc(size);
    if(p==NULL)
      AfxThrowMemoryException();
    if(ppBuffer!=NULL)
      *ppBuffer = p;
    return p;
  }

  inline const void* throwed_efree(const void*& pBuffer) {
    if(pBuffer!=NULL)
      e_free((void*&)pBuffer);
    return (pBuffer = NULL);
  }

  inline const void* throwed_erealloc(const void*& pBuffer, filesize_t size, BOOL bDeleteOnError/*TRUE*/) {
    if(pBuffer==NULL)
      return throwed_emalloc(size,&pBuffer);
    const void* p = e_realloc((void*&)pBuffer, size);
    if(p==NULL && bDeleteOnError)
      throwed_efree(pBuffer);
    if(p==NULL)
      AfxThrowMemoryException();
    return (pBuffer = p);
  }

  inline void* throwed_euse(const void*& pBuffer, filesize_t size, filesize_t offs=0){
    if(pBuffer==NULL)
      return NULL;
    void* p = e_use((void*&)pBuffer, size, offs);
    if(p==NULL)
      AfxThrowMemoryException();
    return p;
  }

#endif//__cplusplus

#endif//__VMALLOC_H
#pragma once