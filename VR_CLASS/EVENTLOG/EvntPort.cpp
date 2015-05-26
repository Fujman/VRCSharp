#include "stdafx.h"
/*---------------------------------------------------------------------------\
| Class: YEventPorts                       Language: C++     Model: All      |
|----------------------------------------------------------------------------|
| Description:  Make event messages for I/O ports in range 0..0x7FF
| Derived from: YEvent
| Constructors: default
| Methods:
| Members:
| Note:
\---Last change 28.04.01 15:36-----Copyright (c) 1999, Anton Yavorsky, KPI--*/

#include "EvntPort.h"
#include "EventLog.h"

LPTSTR YEventPort::GetText(LPTSTR szEvent, int nLength) const {
  TCHAR szText[80], *sz;
  int  i;

  if(nLength<46)
    return NULL;

  sz = YEvent::GetTime(szText,80); ASSERT(sz!=NULL);
  if(isIn()) {
    i=_stprintf(szEvent,_T("%s     IN (%3.3XH)  %2.2XH"),
        szText,
        GetPort(),
        GetByte());
  }else{
    i=_stprintf(szEvent,_T("%s     OUT(%3.3XH)  %2.2XH"),
        szText,
        GetPort(),
        GetByte());
  }
  ASSERT(i!=EOF);
  return szEvent;
}

int  YEventPort::Validate()const{
  if(YEvent20::Validate()==FALSE)
    return FALSE;
  return TRUE;
}


int YLogInPortEvent(WORD nPort, BYTE bData){
  YEventPort ev; ev.in(nPort,bData);
  return YEvent::GetLog()->PutEvent(ev);
}
int YLogOutPortEvent(WORD nPort, BYTE bData){
  YEventPort ev; ev.out(nPort,bData);
  return YEvent::GetLog()->PutEvent(ev);
}

// dynamic construction //////////////////////////////////////////////////////
#include "xnew.h"//*{

YEvent* YEventPort::Allocate(const void *pEBD, size_t nDataSize, void *pMem, size_t nSize, LPCSTR szFileName, int nLine)
{
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  if(szFileName!=NULL)
    return new(szFileName, nLine, pMem, nSize, pEBD, nDataSize) YEventPort(pEBD,nDataSize);
#endif
  return new(pMem, nSize, pEBD, nDataSize) YEventPort(pEBD,nDataSize);
}

#include "xnew.h"//}*

YEVENT_CLASS_IMPLEMENT(YEventPort,YEvent20);
