#include "stdafx.h"
/*---------------------------------------------------------------------------\
| Class: YEventChannel                     Language: C++     Model: All      |
|----------------------------------------------------------------------------|
| Description:  Make event messages for channels. ID of message is same as
|   resource string ID with text of message. Warning: ID must be < 65535!
| Derived from: YEvent64
| Constructors:
| Methods:
| Members:
| Note:
\---Last change 06.06.01 13:58-----Copyright (c) 1999, Anton Yavorsky, KPI--*/

#include <string.h>
#include <afxmt.h>
#include "xstring.h"
#include "xCString.h"
#include "evntchan.h"
#include "EvntInfo.h"
#include "EventLog.h"

//012345678901234567890123456789012345678901234567890123 4  //
//01.02.1980 Wed 02:03:55,999 #32 DATA32BI   Message        // old
//01.02.1980 Wed 02:03:55,999 #32 Message.....

LPTSTR  YEventChannel::GetText(LPTSTR szEvent, int nLength) const 
{
  return GetInfo(szEvent, nLength);
}

LPTSTR  YEventChannel::GetInfo(LPTSTR szEvent, int nLength, int* pnLevel/*NULL*/, int* pnClass/*NULL*/, DWORD* pdwCategory/*NULL*/) const
{
  CString szText;  GetMessageInfo(GetMessage(),szText,pnLevel,pnClass,pdwCategory);
  TCHAR acTime[28]; GetTime(acTime,28);

  char sz[9], szFromBCD[17];

  //LCID lcid = ::GetThreadLocale();

  CString szMessage = FormatString(_T("%s    #%2.2d: "),acTime,1+GetChannel());//AY 4.03.2004 //CString szMessage = FormatString("%s    #%2.2d: ",acTime,GetChannel());
  if(szText.Find(_T("%Z"))>=0){  // "Timer %8.8X thread %Z.\nstarted\nterminated\naborted"
    short nCase;
    int nData = GetData(&nCase);
    CString szCase;
    int iEnd = 0;
    for(int i=0; i<szText.GetLength(); ++i) {
      if(szText[i]=='\n') {
        if(iEnd==(int)nCase) {
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
  }else if(szText.Find(_T("%B"))>=0) { // "Incoming phone number detecting %B"
    GetBCDString(szFromBCD);
    #if defined(UNICODE) || defined(_UNICODE)
      const int nszFromBCDLen = sizeof(szFromBCD)/sizeof(szFromBCD[0]);
      wchar_t szFromBCDw[nszFromBCDLen];
      ::MultiByteToWideChar(CP_ACP,0,szFromBCD,nszFromBCDLen,(LPWSTR)szFromBCDw,nszFromBCDLen);
      szText.Replace(_T("%B"),szFromBCDw);
    #else
      szText.Replace(_T("%B"),szFromBCD);
    #endif
    szMessage += szText;
  }else if(szText.Find(_T("%s"))>=0) { // "Incoming phone number detecting %s"
    GetString(sz);
    #if defined(UNICODE) || defined(_UNICODE)
      const int nszWLen = sizeof(sz)/sizeof(sz[0]);
      TCHAR szW[nszWLen];
      ::MultiByteToWideChar(CP_ACP,0,sz,nszWLen,(LPWSTR)szW,nszWLen);
      szMessage += FormatString(szText,szW);
    #else
      szMessage += FormatString(szText,sz);
    #endif

  }else if(szText.Find(_T("%Y"))>=0) { // "%B"
    short nData2;
    int   nData1 = GetData(&nData2);
    unsigned uData1 = (unsigned)nData1;
    unsigned uData2 = (unsigned)(unsigned short)nData2;
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
  }else if(szText.Find(_T("%.0d"))>=0) { // "$I6 Channel %.0d attached to line %d"
    szText.Replace(_T("%.0d"),_T(""));
    short nData2;
    int   nData1 = GetData(&nData2);
    szMessage += FormatString(szText,(int)nData2,nData1);
  }else{                           // "%ld MB free on operational disk"
    short nData2;
    int   nData1 = GetData(&nData2);
    szMessage += FormatString(szText,nData1,(int)nData2);
  }

  if(szMessage.GetLength()+1 > nLength)
    return NULL;

  _tcscpy(szEvent,szMessage);

  return szEvent;
}

int  YEventChannel::Validate()const{
  if(YEvent64::Validate()==FALSE)
    return FALSE;
  if(GetChannel()>64)
    return FALSE;
  return TRUE;
}

#pragma pack(push)
#pragma pack(1)
union tagSTR {
  struct { WORD w; DWORD dw; BYTE by/*BCD zero*/;} data;
  BYTE  ab[sizeof(DWORD)+sizeof(WORD)];
};
#pragma pack(pop)

const char* YEventChannel::SetString(const char* sz) {
  union tagSTR str = {{0,0}};
  for(unsigned i=0; i<=strlen(sz) && i<sizeof(str.ab); ++i)
    str.ab[i] = sz[i];
  str.data.w  ^= 0xEAEA;
  SetData16(str.data.w,2);
  str.data.dw ^= 0xAEAEAEAE;
  SetData32(str.data.dw,1);
  return(sz);
}

char* YEventChannel::GetString(char* sz) const {
  union tagSTR str = {{0,0}};
  str.data.w  = GetData16(2);
  str.data.w  ^= 0xEAEA;
  str.data.dw = GetData32(1);
  str.data.dw ^= 0xAEAEAEAE;
  for(int i=0; i<sizeof(str.ab) && str.ab[i]!='\0'; i++)
    sz[i] = str.ab[i];
  sz[i] = '\0';
  return(sz);
}
// Input    Internal    Output
// 0..9     0x00..0x09  0..9
// A,a,-    0x0A        -
// B,b,*    0x0B        *
// C,c,#    0x0C        #
// D,d,.    0x0D        .
// '\0'     0x0E        <eol>
// F,f      0x0F        _
//
// other symbols replaced on F

inline int bcdnumber2str(char *sz, const char *bcd)
{
  return bcd2str(sz, bcd, "0123456789-*#.?_");//-:type delimiter, _:skipped digit, .:unrecognized digit,?-zero
}

inline int str2bcdnumber(char *bcd, const char *sz)
{
  return str2bcd(bcd, sz, "0123456789-*#x?_");//-:type delimiter, _:skipped digit, x:unrecognized digit,?-zero 
}

const char* YEventChannel::SetBCDString(const char* _sz) { // 11 chars max (12 with zero)
  union tagSTR str = {{0,0}}; str2bcdnumber((char *)&str.data.by, "");//BCD zero initialization
  char sz[sizeof(str.ab)*2+2];
  strncpy(sz,_sz,sizeof(str.ab)*2);
  sz[sizeof(str.ab)*2] = '\0';
  int i = str2bcdnumber((char *)str.ab, sz);
  str.data.w  ^= 0xEAEA;
  SetData16(str.data.w,2);
  str.data.dw ^= 0xAEAEAEAE;
  SetData32(str.data.dw,1);
  return(_sz);
}

char* YEventChannel::GetBCDString(char* sz) const {
  union tagSTR str = {{0,0}}; str2bcdnumber((char *)&str.data.by, "");//BCD zero initialization
  str.data.w  = GetData16(2);
  str.data.w  ^= 0xEAEA;
  str.data.dw = GetData32(1);
  str.data.dw ^= 0xAEAEAEAE;
  int i = bcdnumber2str(sz,(const char *)str.ab);
  return(sz);
}


int YLogChannelEventIC(int nChannel, int nMessage, int nData, short nCase) {
  YEventChannel ev(nChannel,nMessage,nData,nCase);
  return YEvent::GetLog()->PutEvent(ev);
}

int YLogChannelEventI(int nChannel, int nMessage, int nData)
{
  YEventChannel ev(nChannel,nMessage,nData);
  return YEvent::GetLog()->PutEvent(ev);
}

int YLogChannelEventIW(int nChannel, int nMessage, int nData, short nData2)
{
  YEventChannel ev(nChannel,nMessage,nData,nData2);
  return YEvent::GetLog()->PutEvent(ev);
}

int YLogChannelEventS(int nChannel, int nMessage, const char* szMessage)
{
  #define MAX_DATA_SIZE (sizeof(DWORD)+sizeof(WORD))
  if(strlen(szMessage)<=MAX_DATA_SIZE) {
    YEventChannel ev(nChannel, nMessage, szMessage);
    return YEvent::GetLog()->PutEvent(ev);
  }else{
    CCriticalSection cr; CSingleLock sl(&cr,TRUE);
    int iRet;
    for(const char *p = szMessage; strlen(p)>0; p+=min(MAX_DATA_SIZE,strlen(p))) {
      YEventChannel ev(nChannel, nMessage, p);
      iRet = YEvent::GetLog()->PutEvent(ev);
    }
    return iRet;
  }
}

int YLogChannelEventBCD(int nChannel, int nMessage, const char* szMessage)
{
  #define MAX_DATA_SIZE (sizeof(DWORD)+sizeof(WORD))
  if(strlen(szMessage)<=MAX_DATA_SIZE*2) {
    YEventChannel ev(nChannel, nMessage);
    ev.SetBCDString(szMessage);
    return YEvent::GetLog()->PutEvent(ev);
  }else{
    CCriticalSection cr; CSingleLock sl(&cr,TRUE);
    int iRet;
    for(const char *p = szMessage; strlen(p)>0; p+=min(MAX_DATA_SIZE*2,strlen(p))) {
      YEventChannel ev(nChannel, nMessage);
      ev.SetBCDString(p);
      iRet = YEvent::GetLog()->PutEvent(ev);
    }
    return iRet;
  }
}

// dynamic construction //////////////////////////////////////////////////////
#include "xnew.h"//*{

YEvent* YEventChannel::Allocate(const void *pEBD, size_t nDataSize, void *pMem, size_t nSize, LPCSTR szFileName, int nLine)
{
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  if(szFileName!=NULL)
    return new(szFileName, nLine, pMem, nSize, pEBD, nDataSize) YEventChannel(pEBD,nDataSize);
#endif
  return new(pMem, nSize, pEBD, nDataSize) YEventChannel(pEBD,nDataSize);
}

#include "xnew.h"//}*

YEVENT_CLASS_IMPLEMENT(YEventChannel,YEvent64);
