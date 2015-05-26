#ifndef __XCOMOBJ
#define __XCOMOBJ
#include <objidl.h>

////////////////////////////////////////////////////////////////////////////
// C/C++ section
#ifdef __cplusplus
extern "C" {
#define _0 =0
#else
#define _0
#endif

BOOL      IUnknown__CheckInterface(IUnknown* pUnk, const GUID* pGUID);

int       IConnectionPoint__Dump(IUnknown* pServer, const GUID* pguid _0);

#undef  _0
#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////////////////////////////////
// C++ section
#ifdef __cplusplus

IMoniker* IMoniker__GetParent(IMoniker* pMoniker);
CString   IMoniker__GetDislpayName(IMoniker* pMoniker);
CString   IMoniker__GetProperty(IMoniker* pMoniker, LPCWSTR wzProperty);

#endif
////////////////////////////////////////////////////////////////////////////
// C++ ATL based section
#ifdef __cplusplus
#include <atlbase.h>

template <class INTERFACE> inline HRESULT
IUnknown__ReQueryInterface(CComPtr<INTERFACE>& pServer, IUnknown*& pOuter)
{
  if(pOuter){//pServer = pOuter;
    CComQIPtr<INTERFACE> p_Serv = pOuter;
              INTERFACE* p_Temp = NULL;
    ASSERT(p_Serv);//E_FAIL on error: TO DO
    if(!p_Serv)
      { ASSERT(!"programmer error?"); return E_FAIL; }
    pOuter->Release();
    pOuter = NULL;
    p_Temp = pServer.Detach();
    pServer.Attach( p_Serv.Detach() );
    p_Temp->Release();
    return S_OK;
  }
  return S_FALSE;
}

template <class INTERFACE> inline HRESULT
IUnknown__ReQueryInterface(CComQIPtr<INTERFACE>& pServer, IUnknown*& pOuter)
{
  if(pOuter){//pServer = pOuter;
    CComQIPtr<INTERFACE> p_Serv = pOuter;
              INTERFACE* p_Temp = NULL;
    ASSERT(p_Serv);//E_FAIL on error: TO DO
    if(!p_Serv)
      { ASSERT(!"programmer error?"); return E_FAIL; }
    pOuter->Release();
    pOuter = NULL;
    p_Temp = pServer.Detach();
    pServer.Attach( p_Serv.Detach() );
    p_Temp->Release();
    return S_OK;
  }
  return S_FALSE;
}

inline HRESULT hr_error(HRESULT hr, HRESULT hr_def=E_FAIL)
{
  return hr==S_OK?hr_def:hr;
}

inline HRESULT hr_error_ptr(HRESULT hr, void* ptr, HRESULT hr_def=E_FAIL)
{
  return ptr==NULL?(hr==S_OK?hr_def:hr):hr;
}

#endif//__cplusplus

#endif//__XCOMOBJ
#pragma once
