#include "EventBase.h"
///////////////////////////////////////////////////////////////////////////////////
// YEventObject allocation
#include "xnew.h" //dumb MFC feature fixing - replace operator new

#undef   _XDUMPLEVEL
#define  _XDUMPLEVEL 255//-1
#include "xdump_trace.h"

#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
inline void* YEventObject::operator new(size_t nSize, LPCSTR szFileName, int nLine, void *pMem, size_t nMemSize, const void *pData, int nDataSize)
{
  nSize = YEventObject::SizeOf(nSize,(const YEventBaseData*)pData,nDataSize);
  void* pObj = pMem;
  if(nSize==0)//data size check
    ::AfxThrowMemoryException();
  if(pMem!=NULL && (nMemSize!=0 && nMemSize<nSize))
    TRACE(DEBUGPLACE("warning : out of local memory : %u needed\n"),nSize);
  if(pMem==NULL || (nMemSize!=0 && nMemSize<nSize))
    pObj = ::operator new(nSize, szFileName, nLine);
  ((YEventObject*)pObj)->m_bInHeap = (pObj!=pMem);
  return pObj;
}
inline void  YEventObject::operator delete(void *pObject, LPCSTR szFileName, int nLine, void *pMem, size_t nMemSize, const void *pData, int nDataSize)
{
  YEventObject::operator delete(pObject, pMem);
}

#endif

inline void* YEventObject::operator new(size_t nSize, void *pMem, size_t nMemSize, const void *pData, int nDataSize)
{
  nSize = YEventObject::SizeOf(nSize,(const YEventBaseData*)pData,nDataSize);
  void* pObj = pMem;
  if(nSize==0)//data size check
    ::AfxThrowMemoryException();
  if(pMem!=NULL && (nMemSize!=0 && nMemSize<nSize))
    TRACE(DEBUGPLACE("warning : out of local memory : %u needed"),nSize);
  if(pMem==NULL || (nMemSize!=0 && nMemSize<nSize))
    pObj = ::operator new(nSize);
  ((YEventObject*)pObj)->m_bInHeap = (pObj!=pMem);
  return pObj;
}
inline void  YEventObject::operator delete(void *pObject, void *pMem, size_t nMemSize, const void *pData, int nDataSize)
{
  YEventObject::operator delete(pObject, pMem);
}

inline void  YEventObject::operator delete(void *pObject, void* pMem)
{
  if(pMem==NULL || pObject!=pMem)
    ASSERT( ((YEventObject*)pObject)->m_bInHeap );
  if(pMem==NULL || pObject!=pMem)
    { ::operator delete(pObject); return; }
  if(((YEventObject*)pObject)->m_bInHeap) //AY 08.02.2005
    { ::operator delete(pObject); return; }
  //no actions elsewere
  ASSERT( ! ((YEventObject*)pObject)->m_bInHeap );
}

inline void  YEventObject::operator delete(void *pObject)
{
  if(((YEventObject*)pObject)->m_bInHeap) //AY 08.02.2005
    ::operator delete(pObject);
  //no actions elsewere
}

#include "xnew.h" //dumb MFC feature fixing - replace operator new

inline size_t YEventObject::SizeOf(size_t nSize, const YEventBaseData* pData, size_t nDataSize)
{
  if(pData==NULL && nDataSize==0)
    return nSize;
  if(pData==NULL && nDataSize!=0) //AY 01.02.2005
    return nSize+nDataSize;//additional memory
  const YEventBaseData* pEBD = (const YEventBaseData*)pData;
  BOOL bExSize = (pEBD->GetClass()==EVN_xxBIT_CLASS);
  nDataSize = YEventBaseData::SizeOf(pEBD,nDataSize);
  if(nDataSize==0)
    return 0;//error
  if(bExSize)
    nSize += nSize + pEBD->GetSize();
  if(nSize<nDataSize + sizeof(YEventObject)/*vtable ptr + m_bInHeap*/)//AY 08.02.2005
    return 0;//error
  return nSize;//ok
}
