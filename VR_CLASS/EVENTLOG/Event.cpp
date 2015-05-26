#include "stdafx.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include <stdio.h>
#include <time.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include "event.h"
#include "xCString.h"

//////////////////////////////////////////////////////////////////////////////

YEventsProtocol* YEvent::s_pLog = NULL;
YEVENT_CLASS_IMPLEMENT(YEvent16,YEvent);
YEVENT_CLASS_IMPLEMENT(YEvent20,YEvent);
YEVENT_CLASS_IMPLEMENT(YEvent64,YEvent);

/*---------------------------------------------------------------------------\
| Class: YEventBaseData                    Language: C++     Model: All      |
|----------------------------------------------------------------------------|
| Description: Base implementation of event object, which include time
|              processing and 16 or 20 bit message variants.
|              Size of base structure is 64 bit (8 bytes).
| Derived from: none
| Constructors: default
| Destructors:  default
| Methods:
| Members:
| Note:
\---Last change 27.04.01 19:02-----Copyright (c) 1999, Anton Yavorsky, KPI--*/

#define time_t YEventBaseData::time_t //AY 01.02.2011

time_t YEventBaseData::SetTime() {
#if _DEBUG //under design
  return SetTimeEx().GetTime();
#else
  struct _timeb theTimeb;
  _ftime(&theTimeb);//!!TIME!!
  m_tTime = theTimeb.time;
  m_nMsec = theTimeb.millitm;
  return m_tTime;
#endif
}

//012345678901234567890123456 7          // len=28
//01.02.1980 Wed 02:03:55,999\0
LPTSTR  YEventBaseData::GetTime(LPTSTR szEvent, int nLength) const {
  TCHAR szTime[28];
  if(nLength<28)
    return NULL;
  __TIME_T tTime = m_tTime;
  _tcsftime(szTime,28,_T("%d.%m.%Y %a %H:%M:%S,"),localtime(&tTime));
  _stprintf(szEvent,_T("%s%03d"),szTime,m_nMsec);
  return szEvent;
}

/*
int   YEventBaseData::Compare(time_t tTime, WORD nMsec) const {
  // this < tTime:nMsec: -1
  // this > tTime:nMsec: +1
  // this = tTime:nMsec:  0
  if     (m_tTime<tTime)
    return -1;
  else if(m_tTime>tTime)
    return +1;
  else if(m_nMsec<nMsec)
    return -1;
  else if(m_nMsec>nMsec)
    return +1;
  else
    return  0;

}

int   YEventBaseData::Compare(const YEventBaseData& evbd) const{
  return Compare(evbd.m_tTime,evbd.m_nMsec);
}

int   YEventBaseData::CompareTime(time_t tTime1, WORD nMsec1, time_t tTime2, WORD nMsec2) {
  // tTime1:nMsec1 < tTime2:nMsec2: -1
  // tTime1:nMsec1 > tTime2:nMsec2: +1
  // tTime1:nMsec1 = tTime2:nMsec2:  0
  if     (tTime1<tTime2)
    return -1;
  else if(tTime1>tTime2)
    return +1;
  else if(nMsec1<nMsec2)
    return -1;
  else if(nMsec1>nMsec2)
    return +1;
  else
    return  0;
}
*/

/*---------------------------------------------------------------------------\
| Class: YEvent                            Language: C++     Model: All      |
|----------------------------------------------------------------------------|
| Description: Base implementation of event object, which include time
|              processing, 4 bit type and 16 bit message data.
|              Fully virtual.
|              Size of base structure is 64 bit (8 bytes).
| Derived from: YEventBaseData
| Constructors: default
| Destructors:  default
| Methods:
| Members:
| Note:
\---Last change 27.04.01 19:02-----Copyright (c) 1999, Anton Yavorsky, KPI--*/

YEvent* YEvent::Create(const void *pData, int nDataSize/*0*/, void *pMem/*NULL*/, int nMemSize/*0*/, LPCSTR szFileName/*0*/, int nLine/*0*/) {
  const tagYEventBaseData64* pEBD = (const tagYEventBaseData64*)pData;
  //check size
  if(nDataSize>0) {
    if(pEBD->m_nClass==EVN_xxBIT_CLASS && nDataSize<YEvent64::SIZE_OF_BASE_DATA) return NULL;
    if(pEBD->m_nClass==EVN_16BIT_CLASS && nDataSize<YEvent16::SIZE_OF_BASE_DATA) return NULL;
    if(pEBD->m_nClass==EVN_20BIT_CLASS && nDataSize<YEvent20::SIZE_OF_BASE_DATA) return NULL;
    if(pEBD->m_nClass==EVN_64BIT_CLASS && nDataSize<YEvent64::SIZE_OF_BASE_DATA) return NULL;
  }
  //check empty
  if(pEBD->m_nClass==EVN_16BIT_CLASS && pEBD->m_nType==0 && pEBD->m_tTime==0 && pEBD->m_nMsec==0 && 
    pEBD->m_nData==0) 
      return NULL;
  if(pEBD->m_nClass==EVN_64BIT_CLASS && pEBD->m_nType==0 && pEBD->m_tTime==0 && pEBD->m_nMsec==0 && 
    pEBD->m_nData==0 && pEBD->m_dwData[0]==0 && pEBD->m_dwData[1]==0) 
      return NULL;

  YEventClassInfo* pInfo = YEvent::SearchClass((const YEventBaseData*)pData);
  if(pInfo==NULL)
    return NULL;
  YEvent *pEvent = (*(pInfo->m_fnAllocate))(pData, nDataSize, pMem, nMemSize, szFileName, nLine);
  if(pEvent==NULL)
    return NULL;
  return pEvent;
}

static class YEventCurrentDate { // Obtain & save current date on start program
public:
  time_t m_tDate;
  YEventCurrentDate() {
    m_tDate = time(NULL);
  }
} tCurrentDate; // at program start constructor will be started

int    YEvent::Validate() const {
#ifdef _DEBUG //xtest support - non-initilized variable
  tCurrentDate.m_tDate = time(NULL);
#endif
  if(m_tTime==-1)
    return FALSE;
  if(m_nMsec>999)
    return FALSE;
  if(m_tTime > tCurrentDate.m_tDate+(((366L)*24)*60)*60)
    return FALSE;
  if(m_tTime!=0 && m_tTime < CTime(1980,1,1,00,00,00).GetTime()) //AY 20.01.2005
    return FALSE;
  return TRUE;
}

int YEvent::GetMessageInfo(UINT nMessageID, CString& szText, int* pnLevel, int* pnClass, DWORD* pdwCategory)
{
  UINT EVENTS = 0x4076;//see vr_res/strings/strings.h: FACILITY_EVENT|SEVERITY_DESCRIPTION
  UINT nMsgID = (nMessageID|(EVENTS<<16));
  szText = CString__MultilanguageResourceString(nMsgID);//AY 18.08.2010 OLD:CString__MultilanguageResourceString(nMessageID)
	int nMesLen	=	szText.GetLength();
  if(szText.GetLength()>4 && szText[0]=='$') {
    switch(szText[1]) {
      case 'W':
        if(pnClass) *pnClass = YEvent::classWARNING;
      break;
      case 'I':
        if(pnClass) *pnClass = YEvent::classINFO;
      break;
      default:
        ASSERT(!"undefined class type!");
      case 'E':
        if(pnClass) *pnClass = YEvent::classERROR;
    }
    if(pnLevel) *pnLevel = _ttoi((LPCTSTR)szText+2);
    szText = szText.Right(szText.GetLength()-4);
  }else{
    if(pnClass)     *pnClass     = classERROR;
    if(pnLevel)     *pnLevel     = 0;
	  if(pdwCategory) *pdwCategory = 0xffffffff;
    return 1;
  }
  return 0;
}

LPTSTR  YEvent::GetInfo(LPTSTR szEvent, int nLength, int* pnClass, int* pnLevel, DWORD* pdwCategory) const
{
  if(pnClass) *pnClass		      = classERROR;
  if(pnLevel) *pnLevel		      = 0;
	if(pdwCategory) *pdwCategory  = 0xffffffff;
  if(nLength==0 || nLength>=1)  *szEvent='\0';
  return NULL;
}

LPTSTR  YEvent::GetDump(LPTSTR szEvent, int nLength) const
{
  return NULL;//by default
}

/*---------------------------------------------------------------------------\
| Class: YEvent16                          Language: C++     Model: All      |
|----------------------------------------------------------------------------|
| Description: Base implementation of event object, which include time
|              processing, 4 bit type and 16 bit message data.
|              Size of data structure is 64 bit (8 bytes).
| Derived from: YEvent
| Constructors: default
| Destructors:  default
| Methods:
| Members:
| Note:
\---Last change 27.04.01 19:02-----Copyright (c) 1999, Anton Yavorsky, KPI--*/

//012345678901234567890123456789012345 6  // len=37
//01.02.1980 Wed 02:03:55,999 C T DATA\0  // 16 bit C-class, T-type, DATA-16 bit data in hex
//01.02.1980 Wed 02:03:55,999 C  XDATA\0  // 20 bit C-class, XDATA-20 bit data in hex
LPTSTR  YEvent16::GetText(LPTSTR szEvent, int nLength) const {
  TCHAR szTime[28], *sz;
  int  i;
  if(nLength<37)
    return NULL;
  sz = GetTime(szTime,28); ASSERT(sz!=NULL);

  i=_stprintf(szEvent,_T("%s %X %X %4.4X"),
      szTime,
      GetClass(),
      GetType(),
      GetData16());

  ASSERT(i!=EOF);
  return szEvent;
}


/*---------------------------------------------------------------------------\
| Class: YEvent20                          Language: C++     Model: All      |
|----------------------------------------------------------------------------|
| Description: Base implementation of event object, which include time
|              processing, 20 bit message data.
|              Size of data structure is 64 bit (8 bytes).
| Derived from: YEvent
| Constructors: default
| Destructors:  default
| Methods:
| Members:
| Note:
\---Last change 27.04.01 19:02-----Copyright (c) 1999, Anton Yavorsky, KPI--*/

//012345678901234567890123456789012345 6  // len=37
//01.02.1980 Wed 02:03:55,999 C T DATA\0  // 16 bit C-class, T-type, DATA-16 bit data in hex
//01.02.1980 Wed 02:03:55,999 C  XDATA\0  // 20 bit C-class, XDATA-20 bit data in hex
LPTSTR  YEvent20::GetText(LPTSTR szEvent, int nLength) const {
  TCHAR szTime[28], *sz;
  int  i;
  if(nLength<37)
    return NULL;
  sz = GetTime(szTime,28); ASSERT(sz!=NULL);

  i=_stprintf(szEvent,_T("%s %X  %5.5lX"),
      szTime,
      GetClass(),
      GetData20());

  ASSERT(i!=EOF);
  return szEvent;
}


/*---------------------------------------------------------------------------\
| Class: YEvent64                          Language: C++     Model: All      |
|----------------------------------------------------------------------------|
| Description: Implementation of event object, which include time
|              processing and 16+32+32 bit message (10 bytes).
|              Size of base structure is 128 bit (16 bytes).
| Derived from: YEvent
| Constructors: default
| Destructors:  default
| Methods:
| Members:
| Note:
\---Last change 27.04.01 19:02-----Copyright (c) 1999, Anton Yavorsky, KPI--*/

//012345678901234567890123456789012345678901234567890123 4  // len=54
//01.02.1980 Wed 02:03:55,999 C T DA16 DATA32BI DATA32BI\0  // 64 bit
LPTSTR  YEvent64::GetText(LPTSTR szEvent, int nLength) const {
  TCHAR szTime[28], *sz;
  int  i;
  if(nLength<54)
    return NULL;
  sz = GetTime(szTime,28); ASSERT(sz!=NULL);

  i=_stprintf(szEvent,_T("%s %X %X %4.4X %8.8lX %8.8lX"),
      szTime,
      GetClass(),
      GetType(),
      GetData16(),
      m_dwData[0],
      m_dwData[1]);

  ASSERT(i!=EOF);
  return szEvent;
}


#pragma pack(push)
#pragma pack(1)
union tagDW2STR
{
  DWORD dw;
  BYTE  ab[sizeof(DWORD)];
};
#pragma pack(pop)

const char* YEvent64::SetString(const char* psz) {
  union tagDW2STR dw[2] = {0,0};
  int   nLen = strlen(psz);
  int   i;

  dw[0].dw = 0;
  dw[1].dw = 0;
  for(i=0; i<nLen && i<sizeof(DWORD); ++i)
    dw[0].ab[i] = psz[i];
  for(   ; i<nLen && i<2*sizeof(DWORD); ++i)
    dw[1].ab[i-sizeof(DWORD)] = psz[i];

  dw[0].dw ^= 0xAEAEAEAE;
  dw[1].dw ^= 0xEAEAEAEA;
  SetData64(&(dw[0].dw)); // Compiler dependent!
  return(psz);
}

char* YEvent64::GetString(char* psz) const {
  union tagDW2STR dw1, dw2;
  char  sz[sizeof(DWORD)*2+1];
  int   i;

  dw1.dw = GetData64(&dw2.dw);
  dw1.dw ^= 0xAEAEAEAE;
  dw2.dw ^= 0xEAEAEAEA;

  for(i=0; i<sizeof(DWORD); i++)
    sz[i] = dw1.ab[i];
  for(i=0; i<sizeof(DWORD); i++)
    sz[i+sizeof(DWORD)] = dw2.ab[i];
  sz[sizeof(DWORD)*2] = '\0';

  strcpy(psz,sz);
  return(psz);
}


// dynamic construction //////////////////////////////////////////////////////
#include "xnew.h"//*{

YEvent* YEvent16::Allocate(const void *pEBD, size_t nDataSize, void *pMem, size_t nSize, LPCSTR szFileName, int nLine)
{
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  if(szFileName!=NULL)
    return new(szFileName, nLine, pMem, nSize, pEBD, nDataSize) YEvent16(pEBD,nDataSize);
#endif
  return new(pMem, nSize, pEBD, nDataSize) YEvent16(pEBD,nDataSize);
}

YEvent* YEvent20::Allocate(const void *pEBD, size_t nDataSize, void *pMem, size_t nSize, LPCSTR szFileName, int nLine)
{
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  if(szFileName!=NULL)
    return new(szFileName, nLine, pMem, nSize, pEBD, nDataSize) YEvent20(pEBD,nDataSize);
#endif
  return new(pMem, nSize, pEBD, nDataSize) YEvent20(pEBD,nDataSize);
}

YEvent* YEvent64::Allocate(const void *pEBD, size_t nDataSize, void *pMem, size_t nSize, LPCSTR szFileName, int nLine)
{
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  if(szFileName!=NULL)
    return new(szFileName, nLine, pMem, nSize, pEBD, nDataSize) YEvent64(pEBD,nDataSize);
#endif
  return new(pMem, nSize, pEBD, nDataSize) YEvent64(pEBD,nDataSize);
}

YEvent* YEvent::Delete(YEvent* pEvent, void *pMem)
{
  if(pMem!=NULL)
    YEvent::operator delete(pEvent, pMem);
  else
    YEvent::operator delete(pEvent);
  return NULL;
}

#include "xnew.h"//}*

