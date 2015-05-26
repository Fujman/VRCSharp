#ifndef __XERROR_H
#define __XERROR_H

typedef HRESULT HXERROR;

#define XERROR_FAILED(hr) (FAILED(hr) || (((hr)&0xFFFF0000)==0 && (hr)!=S_OK) )
#define XERROR_ERROR(hr)  ((hr)==S_OK?E_FAIL:(hr))

#define XERROR_SUCCESSED_OR_WAIT(hr) (!FAILED(hr) || (hr)==S_FALSE)

#endif//__XERROR_H
#pragma once