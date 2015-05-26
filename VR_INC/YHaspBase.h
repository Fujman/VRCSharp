#ifndef __YHASPBASE_H
#define __YHASPBASE_H
#include "YHaspPCS.h"
#include "os/OsCS.h"

extern "C" BOOL   YHasp__ForceHaspHL(BOOL bForce);
extern "C" BOOL   YHasp__UseHaspHL();
extern "C" BOOL   YHasp__ForceHasp4(BOOL bForce);
extern "C" BOOL   YHasp__UseHasp4();

#define YHASP_USE_HASPHL   1

#define YHasp__USEHASPHL() (YHASP_USE_HASPHL && YHasp__UseHaspHL())
#define YHasp__USEHASP4()  (                    YHasp__UseHasp4() )

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


#endif//__YHASPBASE_H
#pragma once
