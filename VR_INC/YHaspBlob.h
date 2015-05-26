#ifndef __YHASPBLOB_H
#define __YHASPBLOB_H
#include "YHaspData.h"
#include "YHaspTime.h"
#include "YTime.h"

#ifndef YHASP_DUMMY_LEVEL
#define YHASP_DUMMY_LEVEL 2
#endif

extern "C" unsigned long /*ZEXPORT*/ 
crc32(
    unsigned long crc,
    const unsigned char FAR *buf,
    unsigned len
);//see J:\VR\VR_CLASS\MathAlgo\ZLIB\crc32.c

// C section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

#if defined(YHASP_USE_MEMOHASP)

#pragma warning(disable: 4005)

#undef   YHaspData__WriteLicense
#undef   YHaspData__ParseBlob
#undef   YHaspData__CheckBlob
#undef   YHaspData__DecodeBlob
#undef   YHaspData__WriteData
#define  YHaspData__WriteLicense   _YHaspData__WriteLicense
#define  YHaspData__ParseBlob      _YHaspData__ParseBlob 
#define  YHaspData__CheckBlob      _YHaspData__CheckBlob 
#define  YHaspData__DecodeBlob     _YHaspData__DecodeBlob
#define  YHaspData__WriteData      _YHaspData__WriteData 
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_MASK
#undef   HASP_VENDOR_CODE
#define  HASP_VENDOR_CODE "aLG7D50+NqcOrGShjsx5yeNfCxXgR9vtoQtq3XfWcF9Xfj0Zotqe4sSBpyT+NzyF5UvErIWF9Uza5AHwp7FcMSDqwX/QW/4Iq4RsbE+q34z9Iv9pTPmFw6iMg8oTscv1UUNxtRKsuXi8V6bvfz8ZMDB7Hxyr0xPktHGcXDMWcvCxzz/OW2Yl4jvi+w5fPKRiVpeoXZ2rLkfMWlxcswhnR+QdPg+F2k04n0UjCTWTVOlGjKxbTAYLOXg+zcWHEYfX3xgEtIUjLNb84+y4s6kZsgkKvVvF6PMwgK8w/85UdAConQbWczFjFGWzJ+5r9ZPYDGSAL8/c6fADL8AgAgPqRee9JMA2yftoVwMrNcQFW910TaIfjyN2JVjedtrkYIBPYNb+x07ABZyjj1F/Q1BjIGltW7c2Hf2RuU9V9dDmOdOjCl6hNUVe8NeacAAADJACppa1JpNn8tA2RNEiPxQ/dv2YE/LpWfTZsgAI3xbrJfaQJCcTXL5AdNEnLEhFmo2LGKdZjsw9tEFTmj5SD+3/WETAK5vemZKRMM+2MFHqnz1IdoGTivcHBUg1DWX9YwEx+lrfPC+h9VzohwQhGd1SQpzOoqTw2mbcCQVzcxgCcQ21ImWzxYMZnPTtanymI93Ral+MNlOUgPVit/4DMJAzSNL9cgQAjy1PIj1NPE6K1zhfeGVC/KpHTrHp99+OfKdSMJLLflUboMWBl0gsfk+sUVs5OJ8SGp4xvVdkcICYXJUF6om6bk9nq3akbVTIDntdnpYYaRqhCFlsxVsSToJwLN8LzYjLjmHpNVV4GoA57Cwu0/3LznRqFdBBmBBtE5Vz6LKHL6rvLwjGd9tKSCdCAkzn4rPWMHio8nMzsEVdIUbV7KNz2o8KFvt8i0WXGB1yVLnRBULO4zV0ZdSD7NP4ZgUaPfthF4h1nNmHd135dDI="
#define  HASP_PASS1  14291
#define  HASP_PASS2  13413
#define  HASP_MASK   (0x37373737&0x77777777)
#include "YHaspBlob.inl"

#undef   YHaspData__WriteLicense
#undef   YHaspData__ParseBlob
#undef   YHaspData__CheckBlob
#undef   YHaspData__DecodeBlob
#undef   YHaspData__WriteData
#define  YHaspData__WriteLicense   YHaspData__WriteLicense_
#define  YHaspData__ParseBlob      YHaspData__ParseBlob_
#define  YHaspData__CheckBlob      YHaspData__CheckBlob_
#define  YHaspData__DecodeBlob     YHaspData__DecodeBlob_
#define  YHaspData__WriteData      YHaspData__WriteData_ 
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_MASK
#undef   HASP_VENDOR_CODE
#define  HASP_VENDOR_CODE "bLG7D50+MqcNrGShjsx5yeNdCxOgR9vtoQtq3XfWcF9Xfj0Zotqe4sSBpyT+NzyF5UvErIWF9Uza5AHwp7FcMSDqwX/QW/4Iq4RsbE+q34z9Iv9pTPmFw6iMg8oTscv1UUNxtRKsuXi8V6bvfz8ZMDB7Hxyr0xPktHGcXDMWcvCxzz/OW2Yl4jvi+w5fPKRiVpeoXZ2rLkfMWlxcswhnR+QdPg+F2k04n0UjCTWTVOlGjKxbTAYLOXg+zcWHEYfX3xgEtIUjLNb84+y4s6kZsgkKvVvF6PMwgK8w/85UdAConQbWczFjFGWzJ+5r9ZPYDGSAL8/c6fADL8AgAgPqRee9JMA2yftoVwMrNcQFW910TaIfjyN2JVjedtrkYIBPYNb+x07ABZyjj1F/Q1BjIGltW7c2Hf2RuU9V9dDmOdOjCl6hNUVe8NeacAAADJACppa1JpNn8tA2RNEiPxQ/dv2YE/LpWfTZsgAI3xbrJfaQJCcTXL5AdNEnLEhFmo2LGKdZjsw9tEFTmj5SD+3/WETAK5vemZKRMM+2MFHqnz1IdoGTivcHBUg1DWX9YwEx+lrfPC+h9VzohwQhGd1SQpzOoqTw2mbcCQVzcxgCcQ21ImWzxYMZnPTtanymI93Ral+MNlOUgPVit/4DMJAzSNL9cgQAjy1PIj1NPE6K1zhfeGVC/KpHTrHp99+OfKdSMJLLflUboMWBl0gsfk+sUVs5OJ8SGp4xvVdkcICYXJUF6om6bk9nq3akbVTIDntdnpYYaRqhCFlsxVsSToJwLN8LzYjLjmHpNVV4GoA57Cwu0/3LznRqFdBBmBBtE5Vz6LKHL6rvLwjGd9tKSCdCAkzn4rPWMHio8nMzsEVdIUbV7KNz2o8KFvt8i0WXGB1yVMnRBULO4zV0ZdSD7NP4ZgUaPfthF4x1nNmHd135dDI="
#define  HASP_PASS1  39767
#define  HASP_PASS2  11430
#define  HASP_MASK   (0x37373737|0x77777777)
#include "YHaspBlob.inl"

#undef   YHaspData__WriteLicense
#undef   YHaspData__ParseBlob
#undef   YHaspData__CheckBlob
#undef   YHaspData__DecodeBlob
#undef   YHaspData__WriteData
#define  YHaspData__WriteLicense   __YHaspData__WriteLicense
#define  YHaspData__ParseBlob      __YHaspData__ParseBlob 
#define  YHaspData__CheckBlob      __YHaspData__CheckBlob 
#define  YHaspData__DecodeBlob     __YHaspData__DecodeBlob
#define  YHaspData__WriteData      __YHaspData__WriteData 
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_MASK
#undef   HASP_VENDOR_CODE
#define  HASP_VENDOR_CODE "eLD7D50+MqcOrGShjsx5ygNfCxOgR9vtoQtq4XfWcF9Xfj0Zotqe7sSBpyT+NzyF5UvErIWF9Uza5AHwp7FcMSDqwX/QW/4Iq4RsbE+q34z9Iv9pTPmFw6iMg8oTscv1UUNxtRKsuXi8V6bvfz8ZMDB7Hxyr0xPktHGcXDMWcvCxzz/OW2Yl4jvi+w5fPKRiVpeoXZ2rLkfMWlxcswhnR+QdPg+F2k04n0UjCTWTVOlGjKxbTAYLOXg+zcWHEYfX3xgEtIUjLNb84+y4s6kZsgkKvVvF6PMwgK8w/85UdAConQbWczFjFGWzJ+5r9ZPYDGSAL8/c6fADL8AgAgPqRee9JMA2yftoVwMrNcQFW910TaIfjyN2JVjedtrkYIBPYNb+x07ABZyjj1F/Q1BjIGltW7c2Hf2RuU9V9dDmOdOjCl6hNUVe8NeacAAADJACppa1JpNn8tA2RNEiPxQ/dv2YE/LpWfTZsgAI3xbrJfaQJCcTXL5AdNEnLEhFmo2LGKdZjsw9tEFTmj5SD+3/WETAK5vemZKRMM+2MFHqnz1IdoGTivcHBUg1DWX9YwEx+lrfPC+h9VzohwQhGd1SQpzOoqTw2mbcCQVzcxgCcQ21ImWzxYMZnPTtanymI93Ral+MNlOUgPVit/4DMJAzSNL9cgQAjy1PIj1NPE6K1zhfeGVC/KpHTrHp99+OfKdSMJLLflUboMWBl0gsfk+sUVs5OJ8SGp4xvVdkcICYXJUF6om6bk9nq3akbVTIDntdnpYYaRqhCFlsxVsSToJwLN8LzYjLjmHpNVV4GoA57Cwu0/3LznRqFdBBmBBtE5Vz6LKHL6rvLwjGd9tKSCdCAkzn4rPWMHio8nMzsEVdIUbV7KNz2o8KFvt8i0WXGB1yVLnRBULO4zV0ZdSD7NP4ZgUaPfthF4h1nNmHd135dDI="
#define  HASP_PASS1   7634
#define  HASP_PASS2  18498
#define  HASP_MASK   (0x37373737^0x77777777)
#include "YHaspBlob.inl"

#undef   YHaspData__WriteLicense
#undef   YHaspData__ParseBlob
#undef   YHaspData__CheckBlob
#undef   YHaspData__DecodeBlob
#undef   YHaspData__WriteData
#define  YHaspData__WriteLicense   YHaspData__WriteLicense__
#define  YHaspData__ParseBlob      YHaspData__ParseBlob__
#define  YHaspData__CheckBlob      YHaspData__CheckBlob__
#define  YHaspData__DecodeBlob     YHaspData__DecodeBlob__
#define  YHaspData__WriteData      YHaspData__WriteData__
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_MASK
#include "YHaspPass.h" //TRUE
#define  HASP_MASK   (0x37373737+0x77777777)
#include "YHaspBlob.inl"

#undef   YHaspData__WriteLicense
#undef   YHaspData__ParseBlob
#undef   YHaspData__CheckBlob
#undef   YHaspData__DecodeBlob
#undef   YHaspData__WriteData
#define  YHaspData__WriteLicense   _YHaspData__WriteLicense_
#define  YHaspData__ParseBlob      _YHaspData__ParseBlob_
#define  YHaspData__CheckBlob      _YHaspData__CheckBlob_
#define  YHaspData__DecodeBlob     _YHaspData__DecodeBlob_
#define  YHaspData__WriteData      _YHaspData__WriteData_
#undef   HASP_PASS1
#undef   HASP_PASS2
#undef   HASP_MASK
#undef   HASP_VENDOR_CODE
#define  HASP_VENDOR_CODE "bLG7D50+MqcOrGShjsx5y7NfCxOgR9vtoQrq3XfWcF9Xfj0Zotqe4sSBbxT+NzyF5UvErIWF9Uza5AHwp7FcMSDqwX/QW/4Iq4RsbE+q34z9Iv9pTPmFw6iMg8oTscv1UUNxtRKsuXi8V6bvfz8ZMDB7Hxyr0xPktHGcXDMWcvCxzz/OW2Yl4jvi+w5fPKRiVpeoXZ2rLkfMWlxcswhnR+QdPg+F2k04n0UjCTWTVOlGjKxbTAYLOXg+zcWHEYfX3xgEtIUjLNb84+y4s6kZsgkKvVvF6PMwgK8w/85UdAConQbWczFjFGWzJ+5r9ZPYDGSAL8/c6fADL8AgAgPqRee9JMA2yftoVwMrNcQFW910TaIfjyN2JVjedtrkYIBPYNb+x07ABZyjj1F/Q1BjIGltW7c2Hf2RuU9V9dDmOdOjCl6hNUVe8NeacAAADJACppa1JpNn8tA2RNEiPxQ/dv2YE/LpWfTZsgAI3xbrJfaQJCcTXL5AdNEnLEhFmo2LGKdZjsw9tEFTmj5SD+3/WETAK5vemZKRMM+2MFHqnz1IdoGTivcHBUg1DWX9YwEx+lrfPC+h9VzohwQhGd1SQpzOoqTw2mbcCQVzcxgCcQ21ImWzxYMZnPTtanymI93Ral+MNlOUgPVit/4DMJAzSNL9cgQAjy1PIj1NPE6K1zhfeGVC/KpHTrHp99+OfKdSMJLLflUboMWBl0gsfk+sUVs5OJ8SGp4xvVdkcICYXJUF6om6bk9nq3akbVTIDntdnpYYaRqhCFlsxVsSToJwLN8LzYjLjmHpNVV4GoA57Cwu0/3LznRqFdBBmBBtE5Vz6LKHL6rvLwjGd9tKSCdCAkzn4rPWMHio8nMzsEVdIUbV7KNz2o8KFvt8i0WXGB1yVLnRBULO4zV0ZdSD7NP4ZgUaPfthF4h1nNmHd135dDI="
#define  HASP_PASS1  12956
#define  HASP_PASS2  17458
#define  HASP_MASK   (0x37373737-0x77777777)
#include "YHaspBlob.inl"

//restore defaults
#undef   YHaspData__WriteLicense
#undef   YHaspData__ParseBlob
#undef   YHaspData__CheckBlob
#undef   YHaspData__DecodeBlob
#undef   YHaspData__WriteData
#undef   HASP_MASK
#define  YHaspData__WriteLicense   YHaspData__WriteLicense__
#define  YHaspData__ParseBlob      YHaspData__ParseBlob__
#define  YHaspData__CheckBlob      YHaspData__CheckBlob__
#define  YHaspData__DecodeBlob     YHaspData__DecodeBlob__
#define  YHaspData__WriteData      YHaspData__WriteData__
#include "YHaspPass.h"
#define  HASP_MASK   (0x37373737+0x77777777)
#endif

#pragma warning(default: 4005)

#if !defined(YHASP_USE_MEMOHASP)//emulation
#endif

//----------------------------------------------------------------------------------

#if defined(YHASP_USE_MEMOHASP) //YHaspBlob.cpp for HASP editor only
CString YHaspData__MakeBlob(int nItems, int* pnOffs, int* pnData, int nHaspID=0, int Program=0, YTime tTime=YTime());
int     YHaspData__WriteBlob(CString szBlob, int Program=0, BOOL bCheckOnly=FALSE, int nCheckedHaspID=0);
int     YHaspData__WriteDefaults(int Program=0);
int     YHaspData__WriteRandoms(int Program=0);
#endif

#endif//__YHASPBLOB_H
#pragma once
