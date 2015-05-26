#ifndef __EVENTOBJ_H
#define __EVENTOBJ_H
#ifdef  __cplusplus
#pragma pack(push,1)
#include "xnew.h"
/////////////////////////////////////////////////////////////////////////////

class   YEventObject;   //+
class   YEventBaseData; //+
struct  YEventClassInfo;//=
class       YEvent;

/////////////////////////////////////////////////////////////////////////////
// YEventObject; base vtable;
class YEventObject {
  public: BOOL   m_bInHeap;
  virtual ~YEventObject(){}

public://allocation operators
  #if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  void*          operator new(size_t nSize, LPCSTR szFileName, int nLine, void *pMem=0, size_t nMemSize=0, const void *pEBD=NULL, int nDataSize=0);
  void           operator delete(void *pOb, LPCSTR szFileName, int nLine, void *pMem,   size_t nMemSize,   const void *pEBD,      int nDataSize  );
  #endif
  void*          operator new(size_t nSize, void *pMem=0, size_t nMemSize=0, const void *pEBD=NULL, int nDataSize=0);
  void           operator delete(void *pOb, void *pMem,   size_t nMemSize,   const void *pEBD,      int nDataSize  );

  void           operator delete(void *pOb, void* pMem);
  void           operator delete(void *pOb);

  static  size_t SizeOf(size_t nNewNeedSize, const YEventBaseData* pData, size_t nDataSize=0);
};

/////////////////////////////////////////////////////////////////////////////
#include "xnew.h" //leave

/////////////////////////////////////////////////////////////////////////////
// Inline implementation
#include "EventObj.inl"

#pragma pack(pop)
#endif//__cplusplus
#endif//__EVENTOBJ_H
#pragma once
