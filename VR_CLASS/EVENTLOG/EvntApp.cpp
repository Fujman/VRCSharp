#include "stdafx.h"
/*---------------------------------------------------------------------------\
| Class: YEventChannel                     Language: C++     Model: All      |
|----------------------------------------------------------------------------|
| Description:  Make event messages for application. ID of message is same as
|   resource string ID with text of message. Warning: ID must be < 65535!
|   This even can save or two DWORD values, or 8 bytes length string.
| Derived from: YEvent64
| Constructors:
| Methods:
| Members:
| Note:
\---Last change 06.06.01 15:23pm---Copyright (c) 1999, Anton Yavorsky, KPI--*/

#include <afxmt.h>
#include <string.h>
#include "xCString.h"
#include "EvntApp.h"
#include "EvntInfo.h"
#include "EventLog.h"

//012345678901234567890123456789012345678901234567890123 4  //
//01.02.1980 Wed 02:03:55,999 #32 DATA32BI   Message        // old
//01.02.1980 Wed 02:03:55,999     Message.....

LPTSTR  YEventApplication::GetText(LPTSTR szEvent, int nLength) const 
{
  return GetInfo(szEvent, nLength);
}

LPTSTR  YEventApplication::GetInfo(LPTSTR szEvent, int nLength, int* pnLevel/*NULL*/, int* pnClass/*NULL*/, DWORD* pdwCategory) const
{
  CString szText;  GetMessageInfo(GetMessage(),szText,pnLevel,pnClass,pdwCategory);
  TCHAR acTime[28]; GetTime(acTime,28);
  
  char sz[sizeof(DWORD)*2+1];

  //LCID lcid = ::GetThreadLocale();

  CString szMessage = FormatString(_T("%s     "),acTime);
  if(szText.Find(_T("%Z"))>=0){  // "Timer %8.8X thread %Z.\nstarted\nterminated\naborted"
    int nCase = m_dwData[0];
    int nData = m_dwData[1];
    CString szCase;
    int iEnd = 0;
    for(int i=0; i<szText.GetLength(); ++i) {
      if(szText[i]=='\n') {
        if(iEnd==nCase) {
          szCase = szText.Mid(i+1);
          break;
        }
        ++iEnd;
      }
    }
    if(!szCase.IsEmpty()) {
      int iPos = szCase.Find('\n');
      if(iPos>=0)
        szCase = szCase.Left(iPos);
    }
    CString szFormat = szText;
    szFormat.Replace(_T("%Z"),_T("%s"));
    if(!szFormat.IsEmpty()) {
      int iPos = szFormat.Find('\n');
      if(iPos>=0)
        szFormat = szFormat.Left(iPos);
    }
    BOOL bRevert = FALSE;
    if(!szFormat.IsEmpty()) {
      int iPos1 = szFormat.Find(_T("%s")); ASSERT(iPos1>=0);
      int iPos2 = szFormat.Find('%');  ASSERT(iPos2>=0);
      bRevert = iPos1==iPos2;
    }
    if(!bRevert)
      szMessage += FormatString(szFormat,nData,(LPCTSTR)szCase);
    else
      szMessage += FormatString(szFormat,(LPCTSTR)szCase,nData);//AY 27.01.2006
  }else if(szText.Find(_T("%s"))>=0) {// "ERROR: file %s can not be deleted!"
    GetString(sz);
    #if defined(UNICODE) || defined(_UNICODE)
      const int nLen = sizeof(sz)/sizeof(sz[0]);
      wchar_t szConverted[nLen];
      ::MultiByteToWideChar(CP_ACP,0,sz,nLen,(LPWSTR)szConverted,nLen);
      szMessage += FormatString(szText,szConverted);
    #else
      szMessage += FormatString(szText,sz);
    #endif
  }else if(szText.Find(_T("%Y"))>=0) { // "%Y"
    unsigned uData1 = (unsigned)m_dwData[0];
    unsigned uData2 = (unsigned)m_dwData[1];
    unsigned uMask  = 1;
    BOOL bContinue = FALSE;
    CString szBits;
    for(int i=0; i<sizeof(uData1)*8/*bits*/; ++i, uMask<<=1){
      if(uData1&uMask){
        if(bContinue)
          szBits += ',';
        else
          bContinue = TRUE;
        szBits += FormatString(_T("%d%s"),i,(uData2&uMask?_T("-on"):_T("-off")));
      }
    }
    szText.Replace(_T("%Y"),szBits);
    if(szText.Replace(_T("%.0d"),_T("")))
      szMessage += FormatString(szText,m_dwData[1],m_dwData[0]);
    else
      szMessage += FormatString(szText,m_dwData[0],m_dwData[1]);
  }else if(szText.Find(_T("%.0d"))>=0) { // "Channel %.0d attached to line %d"
    szText.Replace(_T("%.0d"),_T(""));
    szMessage += FormatString(szText,m_dwData[1],m_dwData[0]);
  }else                           // "%lu files deleted. %lu bytes purged."
    szMessage += FormatString(szText,m_dwData[0],m_dwData[1]);

  if(szMessage.GetLength()+1 > nLength)
    return NULL;

  _tcscpy(szEvent,szMessage);
  return szEvent;
}


union tagDW2STR
{
  BYTE  ab[sizeof(DWORD)];
  DWORD dw;
};

const char* YEventApplication::SetString(const char* psz) {
  union tagDW2STR dw[2];
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

char* YEventApplication::GetString(char* psz) const {
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

int  YEventApplication::Validate()const{
  if(YEvent64::Validate()==FALSE)
    return FALSE;
  return TRUE;
}

int YLogApplicationEventIC(int nMessage, int nData, int nCase) {
  YEventApplication ev(nMessage, nCase, nData);
  return YEvent::GetLog()->PutEvent(ev);
}

int YLogApplicationEventII(int nMessage, int n1, int n2) {
  YEventApplication ev(nMessage, n1, n2);
  return YEvent::GetLog()->PutEvent(ev);
}

int YLogApplicationEventS(int nMessage, const char* szMessage) {
  #define MAX_DATA_SIZE (sizeof(DWORD)*2)
  if(strlen(szMessage)<=MAX_DATA_SIZE) {
    YEventApplication ev(nMessage, szMessage);
    return YEvent::GetLog()->PutEvent(ev);
  }else{
    CCriticalSection cr; CSingleLock sl(&cr,TRUE);
    int iRet;
    for(const char *p = szMessage; strlen(p)>0; p+=min(MAX_DATA_SIZE,strlen(p))) {
      YEventApplication ev(nMessage, p);
      iRet = YEvent::GetLog()->PutEvent(ev);
    }
    return iRet;
  }
}

// dynamic construction //////////////////////////////////////////////////////
#include "xnew.h"//*{

YEvent* YEventApplication::Allocate(const void *pEBD, size_t nDataSize, void *pMem, size_t nSize, LPCSTR szFileName, int nLine)
{
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  if(szFileName!=NULL)
    return new(szFileName, nLine, pMem, nSize, pEBD, nDataSize) YEventApplication(pEBD,nDataSize);
#endif
  return new(pMem, nSize, pEBD, nDataSize) YEventApplication(pEBD,nDataSize);
}

#include "xnew.h"//}*

YEVENT_CLASS_IMPLEMENT(YEventApplication,YEvent64);
