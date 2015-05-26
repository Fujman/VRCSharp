#ifndef __YHASPDATA_H
#define __YHASPDATA_H
#include "YHaspBase.h"


#if 0 ///MOVED TO YHaspBase.h
#include "YHaspPCS.h"
#include "os/OsCS.h"

#ifdef _DEBUG
#define YHASP_USE_HASPHL  1
#endif

//
//#define YHASP_FORCE_DEMO 1
//

#if     YTIME_USE_TIMEHASP
#ifndef YHASP_USE_TIMEHASP
#define YHASP_USE_TIMEHASP
#endif
#endif

#ifdef  YHASP_USE_TIMEHASP
#ifndef YHASP_USE_MEMOHASP
#define YHASP_USE_MEMOHASP
#endif
#endif

#ifdef  YHASP_USE_MEMOHASP
#ifndef YHASP_USE_HASP
#define YHASP_USE_HASP
#endif
#endif

#ifndef YHASP_DUMMY_LEVEL
#define YHASP_DUMMY_LEVEL 2
#endif


// C/C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

#if defined(YHASP_USE_HASP)
#include "Protects/hasp.h"
#include "YHaspPass.h"
#endif // YHASP_USE_HASP

// C section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

__declspec(selectany) DWORD YHasp__LOCK = 0;
__declspec(selectany) int   YHasp__HASP = 0;

extern "C" void YHasp__SetHASP(int UsbNum);//201+usb_id


#if 0//ndef _DEBUG
#define __YHasp__LockHasp(nTimeout)   OS_LOCK(&YHasp__LOCK, (nTimeout))
#define   YHasp__LockHasp()           OS_LOCK(&YHasp__LOCK, INFINITE)
#define   YHasp__UnlockHasp()         OS_UNLOCK(&YHasp__LOCK)
#endif

#if 0//ndef _DEBUG
__declspec(selectany) TCHAR YHasp__CSID[] = _T("SRSDevicesEvent");
__declspec(selectany) DWORD YHasp__CS[10] = {0};
#define __YHasp__LockHasp(nTimeout)   (YHasp__CS[8]=DWORD(YHasp__CSID), OS_CS_LOCK(YHasp__CS, (nTimeout)))
#define   YHasp__LockHasp()           (YHasp__CS[8]=DWORD(YHasp__CSID), OS_CS_LOCK(YHasp__CS, INFINITE))
#define   YHasp__UnlockHasp()         OS_CS_UNLOCK(YHasp__CS)
#endif

__declspec(selectany) HANDLE YHasp__EVENT = NULL;//::CreateEvent(NULL,FALSE,TRUE,_T("SRSDevicesEvent"));

int __YHasp__LockHasp__(DWORD nTimeout);//create event


#if !defined(YHASP_USE_HASP)//emulation

  inline int __YHasp__LockHasp(DWORD nTimeout)
    { return 0; }
  inline int   YHasp__LockHasp()
    { return 0; }
  inline int   YHasp__UnlockHasp()
    { return 0; }

#else

  inline int __YHasp__LockHasp(DWORD nTimeout)
  {
    if(!YHasp__EVENT){
      return __YHasp__LockHasp__(nTimeout);
    }
    return ::WaitForSingleObject(YHasp__EVENT,nTimeout)==WAIT_OBJECT_0?0:-1;
  }

  inline int   YHasp__LockHasp()
  {
    return __YHasp__LockHasp(INFINITE);
  }

  inline int   YHasp__UnlockHasp()
  {
    ASSERT(YHasp__EVENT);
    ::SetEvent(YHasp__EVENT);
    return 0;
  }
#endif

#endif//0 ///MOVED TO YHaspBase.h


//----------------------------------------------------------------------------------

#if defined(YHASP_USE_HASP)

#pragma warning(disable: 4005)

#undef   YHaspData__QueryHasp
#undef   YHaspData__EncodeData
#undef   YHaspData__DecodeData
#define  YHaspData__QueryHasp  _YHaspData__QueryHasp
#define  YHaspData__EncodeData _YHaspData__EncodeData
#define  YHaspData__DecodeData _YHaspData__DecodeData
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_VENDOR_CODE
#define  HASP_VENDOR_CODE "aLG7D50+NqcOrGShjsx5yeNfCxXgR9vtoQtq3XfWcF9Xfj0Zotqe4sSBpyT+NzyF5UvErIWF9Uza5AHwp7FcMSDqwX/QW/4Iq4RsbE+q34z9Iv9pTPmFw6iMg8oTscv1UUNxtRKsuXi8V6bvfz8ZMDB7Hxyr0xPktHGcXDMWcvCxzz/OW2Yl4jvi+w5fPKRiVpeoXZ2rLkfMWlxcswhnR+QdPg+F2k04n0UjCTWTVOlGjKxbTAYLOXg+zcWHEYfX3xgEtIUjLNb84+y4s6kZsgkKvVvF6PMwgK8w/85UdAConQbWczFjFGWzJ+5r9ZPYDGSAL8/c6fADL8AgAgPqRee9JMA2yftoVwMrNcQFW910TaIfjyN2JVjedtrkYIBPYNb+x07ABZyjj1F/Q1BjIGltW7c2Hf2RuU9V9dDmOdOjCl6hNUVe8NeacAAADJACppa1JpNn8tA2RNEiPxQ/dv2YE/LpWfTZsgAI3xbrJfaQJCcTXL5AdNEnLEhFmo2LGKdZjsw9tEFTmj5SD+3/WETAK5vemZKRMM+2MFHqnz1IdoGTivcHBUg1DWX9YwEx+lrfPC+h9VzohwQhGd1SQpzOoqTw2mbcCQVzcxgCcQ21ImWzxYMZnPTtanymI93Ral+MNlOUgPVit/4DMJAzSNL9cgQAjy1PIj1NPE6K1zhfeGVC/KpHTrHp99+OfKdSMJLLflUboMWBl0gsfk+sUVs5OJ8SGp4xvVdkcICYXJUF6om6bk9nq3akbVTIDntdnpYYaRqhCFlsxVsSToJwLN8LzYjLjmHpNVV4GoA57Cwu0/3LznRqFdBBmBBtE5Vz6LKHL6rvLwjGd9tKSCdCAkzn4rPWMHio8nMzsEVdIUbV7KNz2o8KFvt8i0WXGB1yVLnRBULO4zV0ZdSD7NP4ZgUaPfthF4h1nNmHd135dDI="
#define  HASP_PASS1  14291
#define  HASP_PASS2  13413
#include "YHaspBase.inl"

#undef   YHaspData__QueryHasp
#undef   YHaspData__EncodeData
#undef   YHaspData__DecodeData
#define  YHaspData__QueryHasp  YHaspData__QueryHasp_
#define  YHaspData__EncodeData YHaspData__EncodeData_
#define  YHaspData__DecodeData YHaspData__DecodeData_
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_VENDOR_CODE
#define  HASP_VENDOR_CODE "bLG7D50+MqcNrGShjsx5yeNdCxOgR9vtoQtq3XfWcF9Xfj0Zotqe4sSBpyT+NzyF5UvErIWF9Uza5AHwp7FcMSDqwX/QW/4Iq4RsbE+q34z9Iv9pTPmFw6iMg8oTscv1UUNxtRKsuXi8V6bvfz8ZMDB7Hxyr0xPktHGcXDMWcvCxzz/OW2Yl4jvi+w5fPKRiVpeoXZ2rLkfMWlxcswhnR+QdPg+F2k04n0UjCTWTVOlGjKxbTAYLOXg+zcWHEYfX3xgEtIUjLNb84+y4s6kZsgkKvVvF6PMwgK8w/85UdAConQbWczFjFGWzJ+5r9ZPYDGSAL8/c6fADL8AgAgPqRee9JMA2yftoVwMrNcQFW910TaIfjyN2JVjedtrkYIBPYNb+x07ABZyjj1F/Q1BjIGltW7c2Hf2RuU9V9dDmOdOjCl6hNUVe8NeacAAADJACppa1JpNn8tA2RNEiPxQ/dv2YE/LpWfTZsgAI3xbrJfaQJCcTXL5AdNEnLEhFmo2LGKdZjsw9tEFTmj5SD+3/WETAK5vemZKRMM+2MFHqnz1IdoGTivcHBUg1DWX9YwEx+lrfPC+h9VzohwQhGd1SQpzOoqTw2mbcCQVzcxgCcQ21ImWzxYMZnPTtanymI93Ral+MNlOUgPVit/4DMJAzSNL9cgQAjy1PIj1NPE6K1zhfeGVC/KpHTrHp99+OfKdSMJLLflUboMWBl0gsfk+sUVs5OJ8SGp4xvVdkcICYXJUF6om6bk9nq3akbVTIDntdnpYYaRqhCFlsxVsSToJwLN8LzYjLjmHpNVV4GoA57Cwu0/3LznRqFdBBmBBtE5Vz6LKHL6rvLwjGd9tKSCdCAkzn4rPWMHio8nMzsEVdIUbV7KNz2o8KFvt8i0WXGB1yVMnRBULO4zV0ZdSD7NP4ZgUaPfthF4x1nNmHd135dDI="
#define  HASP_PASS1  39767
#define  HASP_PASS2  11430
#include "YHaspBase.inl"

#undef   YHaspData__QueryHasp
#undef   YHaspData__EncodeData
#undef   YHaspData__DecodeData
#define  YHaspData__QueryHasp  __YHaspData__QueryHasp
#define  YHaspData__EncodeData __YHaspData__EncodeData
#define  YHaspData__DecodeData __YHaspData__DecodeData
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_VENDOR_CODE
#define  HASP_VENDOR_CODE "eLD7D50+MqcOrGShjsx5ygNfCxOgR9vtoQtq4XfWcF9Xfj0Zotqe7sSBpyT+NzyF5UvErIWF9Uza5AHwp7FcMSDqwX/QW/4Iq4RsbE+q34z9Iv9pTPmFw6iMg8oTscv1UUNxtRKsuXi8V6bvfz8ZMDB7Hxyr0xPktHGcXDMWcvCxzz/OW2Yl4jvi+w5fPKRiVpeoXZ2rLkfMWlxcswhnR+QdPg+F2k04n0UjCTWTVOlGjKxbTAYLOXg+zcWHEYfX3xgEtIUjLNb84+y4s6kZsgkKvVvF6PMwgK8w/85UdAConQbWczFjFGWzJ+5r9ZPYDGSAL8/c6fADL8AgAgPqRee9JMA2yftoVwMrNcQFW910TaIfjyN2JVjedtrkYIBPYNb+x07ABZyjj1F/Q1BjIGltW7c2Hf2RuU9V9dDmOdOjCl6hNUVe8NeacAAADJACppa1JpNn8tA2RNEiPxQ/dv2YE/LpWfTZsgAI3xbrJfaQJCcTXL5AdNEnLEhFmo2LGKdZjsw9tEFTmj5SD+3/WETAK5vemZKRMM+2MFHqnz1IdoGTivcHBUg1DWX9YwEx+lrfPC+h9VzohwQhGd1SQpzOoqTw2mbcCQVzcxgCcQ21ImWzxYMZnPTtanymI93Ral+MNlOUgPVit/4DMJAzSNL9cgQAjy1PIj1NPE6K1zhfeGVC/KpHTrHp99+OfKdSMJLLflUboMWBl0gsfk+sUVs5OJ8SGp4xvVdkcICYXJUF6om6bk9nq3akbVTIDntdnpYYaRqhCFlsxVsSToJwLN8LzYjLjmHpNVV4GoA57Cwu0/3LznRqFdBBmBBtE5Vz6LKHL6rvLwjGd9tKSCdCAkzn4rPWMHio8nMzsEVdIUbV7KNz2o8KFvt8i0WXGB1yVLnRBULO4zV0ZdSD7NP4ZgUaPfthF4h1nNmHd135dDI="
#define  HASP_PASS1   7634
#define  HASP_PASS2  18498
#include "YHaspBase.inl"

#undef   YHaspData__QueryHasp
#undef   YHaspData__EncodeData
#undef   YHaspData__DecodeData
#define  YHaspData__QueryHasp  YHaspData__QueryHasp__
#define  YHaspData__EncodeData YHaspData__EncodeData__
#define  YHaspData__DecodeData YHaspData__DecodeData__
#undef   HASP_PASS1
#undef   HASP_PASS2
#include "YHaspPass.h"  //TRUE
#include "YHaspBase.inl"

#undef   YHaspData__QueryHasp
#undef   YHaspData__EncodeData
#undef   YHaspData__DecodeData
#define  YHaspData__QueryHasp  _YHaspData__QueryHasp_
#define  YHaspData__EncodeData _YHaspData__EncodeData_
#define  YHaspData__DecodeData _YHaspData__DecodeData_
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_VENDOR_CODE
#define  HASP_VENDOR_CODE "bLG7D50+MqcOrGShjsx5y7NfCxOgR9vtoQrq3XfWcF9Xfj0Zotqe4sSBbxT+NzyF5UvErIWF9Uza5AHwp7FcMSDqwX/QW/4Iq4RsbE+q34z9Iv9pTPmFw6iMg8oTscv1UUNxtRKsuXi8V6bvfz8ZMDB7Hxyr0xPktHGcXDMWcvCxzz/OW2Yl4jvi+w5fPKRiVpeoXZ2rLkfMWlxcswhnR+QdPg+F2k04n0UjCTWTVOlGjKxbTAYLOXg+zcWHEYfX3xgEtIUjLNb84+y4s6kZsgkKvVvF6PMwgK8w/85UdAConQbWczFjFGWzJ+5r9ZPYDGSAL8/c6fADL8AgAgPqRee9JMA2yftoVwMrNcQFW910TaIfjyN2JVjedtrkYIBPYNb+x07ABZyjj1F/Q1BjIGltW7c2Hf2RuU9V9dDmOdOjCl6hNUVe8NeacAAADJACppa1JpNn8tA2RNEiPxQ/dv2YE/LpWfTZsgAI3xbrJfaQJCcTXL5AdNEnLEhFmo2LGKdZjsw9tEFTmj5SD+3/WETAK5vemZKRMM+2MFHqnz1IdoGTivcHBUg1DWX9YwEx+lrfPC+h9VzohwQhGd1SQpzOoqTw2mbcCQVzcxgCcQ21ImWzxYMZnPTtanymI93Ral+MNlOUgPVit/4DMJAzSNL9cgQAjy1PIj1NPE6K1zhfeGVC/KpHTrHp99+OfKdSMJLLflUboMWBl0gsfk+sUVs5OJ8SGp4xvVdkcICYXJUF6om6bk9nq3akbVTIDntdnpYYaRqhCFlsxVsSToJwLN8LzYjLjmHpNVV4GoA57Cwu0/3LznRqFdBBmBBtE5Vz6LKHL6rvLwjGd9tKSCdCAkzn4rPWMHio8nMzsEVdIUbV7KNz2o8KFvt8i0WXGB1yVLnRBULO4zV0ZdSD7NP4ZgUaPfthF4h1nNmHd135dDI="
#define  HASP_PASS1  12956
#define  HASP_PASS2  17458
#include "YHaspBase.inl"

#undef   YHaspData__QueryHasp
#undef   YHaspData__EncodeData
#undef   YHaspData__DecodeData
#define  YHaspData__QueryHasp  YHaspData__QueryHasp__
#define  YHaspData__EncodeData YHaspData__EncodeData__
#define  YHaspData__DecodeData YHaspData__DecodeData__
#include "YHaspPass.h" //restore

#pragma warning(default: 4005)

#if YHASP_DUMMY_LEVEL<1
#define  _YHaspData__QueryHasp()         unsigned(0)
#define  _YHaspData__EncodeData(p,n)     int(0)
#define  _YHaspData__DecodeData(p,n)     int(0)
#endif
#if YHASP_DUMMY_LEVEL<2
#define  YHaspData__QueryHasp_()         unsigned(0)
#define  YHaspData__EncodeData_(p,n)     int(0)
#define  YHaspData__DecodeData_(p,n)     int(0)
#endif
#if YHASP_DUMMY_LEVEL<3
#define  __YHaspData__QueryHasp()         unsigned(0)
#define  __YHaspData__EncodeData(p,n)     int(0)
#define  __YHaspData__DecodeData(p,n)     int(0)
#endif
#if YHASP_DUMMY_LEVEL<4
#define  _YHaspData__QueryHasp_()         unsigned(0)
#define  _YHaspData__EncodeData_(p,n)     int(0)
#define  _YHaspData__DecodeData_(p,n)     int(0)
#endif


#endif

#if defined(YHASP_USE_MEMOHASP)

#pragma warning(disable: 4005)

#undef   YHaspData__QueryHaspID
#undef   YHaspData__QueryHaspData
#undef   YHaspData__WriteHaspData
#undef   YHaspData__WriteData
#define  YHaspData__QueryHaspID    _YHaspData__QueryHaspID
#define  YHaspData__QueryHaspData  _YHaspData__QueryHaspData
#define  YHaspData__WriteHaspData  _YHaspData__WriteHaspData
#define  YHaspData__WriteData      _YHaspData__WriteData
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_VENDOR_CODE
#define  HASP_VENDOR_CODE "bLG7D50+MqcOrGShjsx5yeNfCxOgR9vtoQtq3XfWcF9Xfj0Zotqe4sSBpyT+NzyF5UvErIWF9Uza5AHwp7FcMSDqwX/QW/4Iq4RsbE+q34z9Iv9pTPmFw6iMg8oTscv1UUNxtRKsuXi8V6bvfz8ZMDB7Hxyr0xPktHGcXDMWcvCxzz/OW2Yl4jvi+w5fPKRiVpeoXZ2rLkfMWlxcswhnR+QdPg+F2k04n0UjCTWTVOlGjKxbTAYLOXg+zcWHEYfX3xgEtIUjLNb84+y4s6kZsgkKvVvF6PMwgK8w/85UdAConQbWczFjFGWzJ+5r9ZPYDGSAL8/c6fADL8AgAgPqRee9JMA2yftoVwMrNcQFW910TaIfjyN2JVjedtrkYIBPYNb+x07ABZyjj1F/Q1BjIGltW7c2Hf2RuU9V9dDmOdOjCl6hNUVe8NeacAAADJACppa1JpNn8tA2RNEiPxQ/dv2YE/LpWfTZsgAI3xbrJfaQJCcTXL5AdNEnLEhFmo2LGKdZjsw9tEFTmj5SD+3/WETAK5vemZKRMM+2MFHqnz1IdoGTivcHBUg1DWX9YwEx+lrfPC+h9VzohwQhGd1SQpzOoqTw2mbcCQVzcxgCcQ21ImWzxYMZnPTtanymI93Ral+MNlOUgPVit/4DMJAzSNL9cgQAjy1PIj1NPE6K1zhfeGVC/KpHTrHp99+OfKdSMJLLflUboMWBl0gsfk+sUVs5OJ8SGp4xvVdkcICYXJUF6om6bk9nq3akbVTIDntdnpYYaRqhCFlsxVsSToJwLN8LzYJLjmHpNVV4GoA57Cwu0+3LznRqFdBBmBBtE5Vz6LKHL6rvLwjGd9tKSCdCAkzn4rPWMHio8nMzsEVdIUbV6KNz2o8KFvt8i0RXGB1yVLnRBULO4zV0ZdSD7NP4ZgUaPfthF4h1nNmHd135dDI="
#define  HASP_PASS1  14291
#define  HASP_PASS2  13413
#include "YHaspData.inl"

#undef   YHaspData__QueryHaspID
#undef   YHaspData__QueryHaspData
#undef   YHaspData__WriteHaspData
#undef   YHaspData__WriteData
#define  YHaspData__QueryHaspID    YHaspData__QueryHaspID_
#define  YHaspData__QueryHaspData  YHaspData__QueryHaspData_
#define  YHaspData__WriteHaspData  YHaspData__WriteHaspData_
#define  YHaspData__WriteData      YHaspData__WriteData_
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_VENDOR_CODE
#define  HASP_VENDOR_CODE "bLG8D50+MqcOrGShjsx5yeNfCxOgR0vtoQtq3XfWcF9Xfj0Zotqe4sSBpyT+NzyF5UvErIWF9Uza5AHwp7FcMSDqwX/QW/4Iq4RsbE+q34z9Iv9pTPmFw6iMg8oTscv1UUNxtRKsuXi8V6bvfz8ZMDB7Hxyr0xPktHGcXDMWcvCxzz/OW2Yl4jvi+w5fPKRiVpeoXZ2rLkfMWlxcswhnR+QdPg+F2k04n0UjCTWTVOlGjKxbTAYLOXg+zcWHEYfX3xgEtIUjLNb84+y4s6kZsgkKvVvF6PMwgK8w/85UdAConQbWczFjFGWzJ+5r9ZPYDGSAL8/c6fADL8AgAgPqRee9JMA2yftoVwMrNcQFW910TaIfjyN2JVjedtrkYIBPYNb+x07ABZyjj1F/Q1BjIGltW7c2Hf2RuU9V9dDmOdOjCl6hNUVe8NeacAAADJACppa1JpNn8tA2RNEiPxQ/dv2YE/LpWfTZsgAI3xbrJfaQJCcTXL5AdNEnLEhFmo2LGKdZjsw9tEFTmj5SD+3/WETAK5vemZKRMM+2MFHqnz1IdoGTivcHBUg1DWX9YwEx+lrfPC+h9VzohwQhGd1SQpzOoqTw2mbcCQVzcxgCcQ21ImWzxYMZnPTtanymI93Ral+MNlOUgPVit/4DMJAzSNL9cgQAjy1PIj1NPE6K1zhfeGVC/KpHTrHp99+OfKdSMJLLflUboMWBl0gsfk+sUVs5OJ8SGp4xvVdkcICYXJUF6om6bk9nq3akbVTIDntdnpYYaRqhCFlsxVsSToJwLN8LzYjLjmHpNVV4GoA57Cwu0/3LznRqFdBBmBBtE5Vz8LKHL6rvLwjGd9tKSCdCAkzn4rPWMHio8nMzsEVdIUbV7KNz2o8KFvt8i0WXGR1yVLnRBULO4zV0ZdSD7NP4ZgUaPfthF4h1nHHd135dDI="
#define  HASP_PASS1  39767
#define  HASP_PASS2  11430
#include "YHaspData.inl"

#undef   YHaspData__QueryHaspID
#undef   YHaspData__QueryHaspData
#undef   YHaspData__WriteHaspData
#undef   YHaspData__WriteData
#define  YHaspData__QueryHaspID    __YHaspData__QueryHaspID
#define  YHaspData__QueryHaspData  __YHaspData__QueryHaspData
#define  YHaspData__WriteHaspData  __YHaspData__WriteHaspData
#define  YHaspData__WriteData      __YHaspData__WriteData
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_VENDOR_CODE
#define  HASP_VENDOR_CODE "bLG7D50+MqcOrGShjsx5yeNfCxOgR9vtoQtq3XfWcR9Xfj0Zotqe4sSBpy+TNzyF5UvEr1WF9Uza5AHwp7FcMSOqwX/QW/4Iq4RsbE+q34z9Iv9pTPmFw6iMg8oTscv1UUNxtRKsuXi8V6bvfz8ZMDB7Hxyr0xPktHGcXDMWcvCxzz/OW2Yl4jvi+w5fPKRiVpeoXZ2rLkfMWlxcswhnR+QdPg+F2k04n0UjCTWTVOlGjKxbTAYLOXg+zcWHEYfX3xgEtIUjLNb84+y4s6kZsgkKvVvF6PMwgK8w/85UdAConQbWczFjFGWzJ+5r9ZPYDGSAL8/c6fADL8AgAgPqRee9JMA2yftoVwMrNcQFW910TaIfjyN2JVjedtrkYIBPYNb+x07ABZyjj1F/Q1BjIGltW7c2Hf2RuU9V9dDmOdOjCl6hNUVe8NeacAAADJACppa1JpNn8tA2RNEiPxQ/dv2YE/LpWfTZsgAI3xbrJfaQJCcTXL5AdNEnLEhFmo2LGKdZjsw9tEFTmj5SD+3/WETAK5vemZKRMM+2MFHqnz1IdoGTivcHBUg1DWX9YwEx+lrfPC+h9VzohwQhGd1SQpzOoqTw2mbcCQVzcxgCcQ21ImWzxYMZnPTtanymI93Ral+MNlOUgPVit/4DMJAzSNL9cgQAjy1PIj1NPE6K1zhfeGVC/KpHTrHp99+OfKdSMJLLflUboMWBl0gsfk+sUVs5OJ8SGp4xvVdkcICYXJUF6om6bk9nq3akbVTIDntdnpYYaRqhCFlsxVsSToJwLN8LzYjLjmHpNVV4GoA57Cwu0/3LznRqFdBBmBBtE5Vz6LKHL6rvLwjGd9tKSCdCAkzn4rPWMHio8nMzsEVdIUbV7KNz2o8KFvt8i0WXGB1yVLnRBULO4zV0ZdSD7NP4ZgUaBfthF4h1nNmHd135dDI="
#define  HASP_PASS1   7634
#define  HASP_PASS2  18498
#include "YHaspData.inl"

#undef   YHaspData__QueryHaspID
#undef   YHaspData__QueryHaspData
#undef   YHaspData__WriteHaspData
#undef   YHaspData__WriteData
#define  YHaspData__QueryHaspID    YHaspData__QueryHaspID__
#define  YHaspData__QueryHaspData  YHaspData__QueryHaspData__
#define  YHaspData__WriteHaspData  YHaspData__WriteHaspData__
#define  YHaspData__WriteData      YHaspData__WriteData__
#undef   HASP_PASS1
#undef   HASP_PASS2
#include "YHaspPass.h" //TRUE
#include "YHaspData.inl"

#undef   YHaspData__QueryHaspID
#undef   YHaspData__QueryHaspData
#undef   YHaspData__WriteHaspData
#undef   YHaspData__WriteData
#define  YHaspData__QueryHaspID    _YHaspData__QueryHaspID_
#define  YHaspData__QueryHaspData  _YHaspData__QueryHaspData_
#define  YHaspData__WriteHaspData  _YHaspData__WriteHaspData_
#define  YHaspData__WriteData      _YHaspData__WriteData_
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_VENDOR_CODE
#define  HASP_VENDOR_CODE "bLG7D50+MqcOrGShjsx5yeNfCxOgR9vtoQtq3XfWcF9Xfj0Zotqe4sSBpyT+NzyF5UvErIWF9Uza5AHwp7FcMSDqwX/QW/4Iq4RsbE+q34z9Iv9pTPmFw6iMg8oTscv1UUNxtRKsuXi8V6bvfz8ZMDB7Hxyr0xPktHGcXDMWcvCxzz/OW2Yl4jvi+w5fPKRiVpeoXZ2rLkfMWlxcswhnR+QdPg+F2k04n0UjCTWTVOlGjKxbTAYLOXg+zcWHEYfX3xgEtIUjLNb84+y4s6kZsgkKvVvF6PMwgK8w/85UdAConQbWczFjFGWzJ+5r9ZPYDGSAL8/c6fADL8AgAgPqRee9JMA2yftoVwMrNcQFW910TaIfjyN2JVjedtrkYIBPYNb+x07ABZyjj1F/Q1BjIGltW7c2Hf2RuU9V9dDmOdOjCl6hNUVe8NeacAAADJACppa1JpNn8tA2RNEiPxQ/dv2YE/LpWfTZsgAI3xbrJfaQJCcTXL5AdNEnLEhFmo2LGKdZjsw9tEFTmj5SD+3/WETAK5vemZKRMM+2MFHqnz1IdoGTivcHBUg1DWX9YwEx+lrfPC+h9VzohwQhGd1SQpzOoqTw2mbcCQVzcxgCcQ21ImWzxYMZnPTtanymI93Ral+MNlOUgPVit/4DMJAzSNL9cgQAjy1PIj1NPE6K1zhfeGVC/KpHTrHp99+OfKdSMJLLflUboWMBl0gsfk+sUVs5OJ8SGp4xwVdkcICYXJUF6om6bk9nq3akbvTIDntdnpYYaRqhCFlsxVsSToIwLN8LzYjLjmHpNVV4GoA57Cwu0/8LznRqFdBBmBBtE5Vz6LKHL6rvLwjGd9tKSCdCAkzn4rPWMHio8nMzsEVdIUbV7KNz2o8KFvt8i0WXGB1yVLnRBULO4zV0ZdSD7NP4ZgUaPfthF4h1nNmHd135dDI="
#define  HASP_PASS1  12956
#define  HASP_PASS2  17458
#include "YHaspData.inl"

//restore defaults
#undef   YHaspData__QueryHaspID
#undef   YHaspData__QueryHaspData
#undef   YHaspData__WriteHaspData
#undef   YHaspData__WriteData
#define  YHaspData__QueryHaspID    YHaspData__QueryHaspID__
#define  YHaspData__QueryHaspData  YHaspData__QueryHaspData__
#define  YHaspData__WriteHaspData  YHaspData__WriteHaspData__
#define  YHaspData__WriteData      YHaspData__WriteData__
#include "YHaspPass.h"

#pragma warning(default: 4005)

#if YHASP_DUMMY_LEVEL<1
#define  _YHaspData__QueryHaspID()          unsigned(0)
#define  _YHaspData__QueryHaspData(o)       int(0xFFFF)
#define  _YHaspData__WriteHaspData(o,d)     int(d)
#define  _YHaspData__WriteData(p,n)         int(0)
#endif
#if YHASP_DUMMY_LEVEL<2
#define  YHaspData__QueryHaspID_()          unsigned(0)
#define  YHaspData__QueryHaspData_(o)       int(0xFFFF)
#define  YHaspData__WriteHaspData_(o,d)     int(d)
#define  YHaspData__WriteData_(p,n)         int(0)
#endif
#if YHASP_DUMMY_LEVEL<3
#define  __YHaspData__QueryHaspID()          unsigned(0)
#define  __YHaspData__QueryHaspData(o)       int(0xFFFF)
#define  __YHaspData__WriteHaspData(o,d)     int(d)
#define  __YHaspData__WriteData(p,n)         int(0)
#endif
#if YHASP_DUMMY_LEVEL<4
#define  _YHaspData__QueryHaspID_()          unsigned(0)
#define  _YHaspData__QueryHaspData_(o)       int(0xFFFF)
#define  _YHaspData__WriteHaspData_(o,d)     int(d)
#define  _YHaspData__WriteData_(p,n)         int(0)
#endif

#endif

extern "C" int    YHaspData__QuerySpecifiedHaspID(int UsbNum);
extern "C" int    YHaspData__ReadHaspBlock(void* pData, int nOffs, int nSize);
extern "C" int    YHasp__ReadHaspBlock(void* pData, int nOffs, int nSize);//nOffs-words, nSize-words//AY 13.06.2014
extern "C" int    YHaspHL__ReadHaspBlock(void* pData, int nOffs, int nSize);

extern "C" int    YHaspData__WriteHaspBlock(const void* pData, int nOffs, int nSize);
extern "C" int    YHaspHL__WriteHaspBlock(const void* pData, int nOffs, int nSize);


//----------------------------------------------------------------------------------

#if !defined(YHASP_USE_HASP)//emulation
extern "C" __inline int YHaspData__QueryHasp()
{
  YHasp__LockHasp();
  YHasp__UnlockHasp();
  return 1;
}
#endif

#if !defined(YHASP_USE_MEMOHASP) //emulation

extern "C" __inline unsigned YHaspData__QueryHaspID()
{
  YHasp__LockHasp();
  YHasp__UnlockHasp();
  return 0x33333333U+0x7B7B7B7BU;
}

extern "C" __inline int YHaspData__QueryHaspData(int nOffs)
{
  YHasp__LockHasp();
  YHasp__UnlockHasp();
  return -1;
}

extern "C" __inline int YHaspData__WriteHaspData(int nOffs, int nData)
{
  YHasp__LockHasp();
  YHasp__UnlockHasp();
  return 0;//ok
}

#endif


// C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus

#endif//__cplusplus
////////////////////////////////////////////////////////////////////////////////////

#endif//__YHASPDATA_H
#pragma once
