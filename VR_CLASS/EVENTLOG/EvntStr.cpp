#include "stdafx.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "EvntStr.h"
#include "EventLog.h"
#include "xCString.h"

#define  MK_UNI(s,n)      YEventString::Unicode((void*)ab,sizeof(ab),(s),(n))
#define  SIZEOF(s,n)      YEventString::SizeOf((s),(n))

#ifdef UNICODE
#define  TMP_UNICODE_SIZE 1    //no buffer needed
#else
#define  TMP_UNICODE_SIZE 4096 //bytes //event log page size
#endif
#define  MAX_STRING_SIZE  4096 //bytes //event log page size

///////////////////////////////////////////////////////////////////////////////
// YEventString

LPCWSTR YEventString::SetString(LPCTSTR sz, int nLen)
  { BYTE ab[TMP_UNICODE_SIZE]; return YEventEx::SetString(MK_UNI(sz,nLen),nLen); }

CString YEventString::GetString() const
  { return CString(YEventEx::GetString()); } //no encryption

void* YEventString::SetData(LPCTSTR sz, int nLen)
  { BYTE ab[TMP_UNICODE_SIZE]; return YEventBaseData::SetData(MK_UNI(sz,nLen),SIZEOF(sz,nLen)); }

size_t YEventString::SizeOf(LPCTSTR szString, int nLen)
{
  ASSERT( szString!=NULL || nLen>=0 );
  if(szString==NULL && nLen==0)
    return 0;
  nLen = nLen>=0?nLen:_tcslen(szString);
  return (nLen+1)*sizeof(wchar_t);
}

LPWSTR YEventString::Unicode(void *pMem, int nMax, LPCTSTR sz, int nLen)
{ //ASSERT(!"check");
  if(sizeof(TCHAR)==sizeof(char)){ //codepage
    if(nMax<SizeOf(sz, nLen))
      return NULL;
    int iRet = ::MultiByteToWideChar(CP_ACP,0,(LPCSTR)sz,nLen,(LPWSTR)pMem,nMax);
    if(iRet==0 && !((nLen<0 && *sz=='\0') || nLen==0))
      return NULL;
    ((LPWSTR)pMem)[iRet] = L'\0';
    return (LPWSTR)pMem;
  }else{ //unicode
    if(nLen>=0){ //local copy
      if(nMax<SizeOf(sz, nLen))
        return NULL;
      memcpy(pMem,sz,nLen*sizeof(wchar_t));
      ((LPWSTR)pMem)[nLen] = L'\0';
      return (LPWSTR)pMem;
    }else{
      return (LPWSTR)sz;//same
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
// YEventCryptedString
LPCWSTR YEventCryptedString::SetString(LPCTSTR sz, int nLen)
  { BYTE ab[TMP_UNICODE_SIZE]; return YEventEx::SetString(MK_UNI(sz,nLen),nLen); }

CString YEventCryptedString::GetString() const
  { wchar_t sz[MAX_STRING_SIZE]; return CString(YEventEx::GetString(sz,MAX_STRING_SIZE)); }

void* YEventCryptedString::SetData(LPCTSTR sz, int nLen)
  { BYTE ab[TMP_UNICODE_SIZE]; return Crypto(YEventBaseData::SetData(MK_UNI(sz,nLen),SIZEOF(sz,nLen)),GetSize()); }

void* YEventCryptedString::Crypto(void *pData, size_t nSize, size_t nOffset)
{
  if(pData==NULL) return NULL;
  union{ DWORD dwMask; BYTE abMask[4]; }; dwMask=0x4A5D92C4;
  BYTE* p = ((BYTE*)pData) + nOffset;
  for(size_t n=0; n<nSize && nOffset%4!=0; n+=1, nOffset+=1)
    p[n] ^= abMask[nOffset%4];
  for(          ; n<nSize && (nSize-n)>=4; n+=4, nOffset+=4)
    *(DWORD*)(p+n) ^= dwMask;
  for(          ; n<nSize                ; n+=1, nOffset+=1)
    p[n] ^= abMask[nOffset%4];
  return pData;
}

///////////////////////////////////////////////////////////////////////////////
// GetInfo

LPTSTR YEventString::GetInfo(LPTSTR szEvent, int nLength, int* pnLevel, int* pnClass, DWORD* pdwCategory) const
{
  CString szText;
  if(GetMessageID())
    GetMessageInfo(GetMessageID(),szText,pnLevel,pnClass,pdwCategory);
  else //defaults
    YEvent::GetInfo(szEvent,nLength, pnLevel, pnClass, pdwCategory);
  if(szEvent==NULL)
    return NULL;

  TCHAR acTime[28]; GetTime(acTime,28);
  CString szMessage = FormatString(_T("%s     "),acTime);
  if(GetMessageID())
    if(szText.Find(_T("%s"))>=0)
      szMessage += FormatString(szText,GetString());
    else
      szMessage += szText + GetString();
  else
    szMessage += GetString();
  if(nLength>=0 && nLength<szMessage.GetLength()+1)
    return NULL;
  return _tcscpy(szEvent,szMessage);
}

LPTSTR YEventCryptedString::GetInfo(LPTSTR szEvent, int nLength, int* pnLevel, int* pnClass, DWORD* pdwCategory) const
{
  CString szText;
  if(GetMessageID())
    GetMessageInfo(GetMessageID(),szText,pnLevel,pnClass,pdwCategory);
  else //defaults
    YEvent::GetInfo(szEvent,nLength, pnLevel, pnClass, pdwCategory);
  if(szEvent==NULL)
    return NULL;

  TCHAR acTime[28]; GetTime(acTime,28);
  CString szMessage = FormatString(_T("%s     "),acTime);
  if(GetMessageID())
    if(szText.Find(_T("%s"))>=0)
      szMessage += FormatString(szText,GetString());
    else
      szMessage += szText + GetString();
  else
    szMessage += GetString();
  if(nLength>=0 && nLength<szMessage.GetLength()+1)
    return NULL;
  return _tcscpy(szEvent,szMessage);
}

///////////////////////////////////////////////////////////////////////////////

int YLogStringEvent(WORD nMessageID, LPCTSTR sz, int nLen, DWORD nSignature, BOOL bCript)
{
  BYTE abyBuffer[MAX_STRING_SIZE];
  YEvent* pev = NULL;
  if(bCript) pev = YEventCryptedString::CreateEx(nMessageID, sz, nLen, nSignature, (void *)abyBuffer, sizeof(abyBuffer) DEBUG_NEW_FILE_LINE);
  else       pev = YEventString       ::CreateEx(nMessageID, sz, nLen, nSignature, (void *)abyBuffer, sizeof(abyBuffer) DEBUG_NEW_FILE_LINE);
  YEventsProtocol* pLog = YEvent::GetLog();
  if(pLog!=NULL)
    TRACE(DEBUGPLACE("ERROR : put event to closed log\n"));
  int iRet = pLog?pLog->PutEvent(*pev):-1;
  YEvent::Delete(pev,(void*)abyBuffer);
  return iRet;
}

// dynamic construction //////////////////////////////////////////////////////
#include "xnew.h"//*{

YEvent* YEventString::Allocate(const void *pEBD, size_t nDataSize, void *pMem, size_t nSize, LPCSTR szFileName, int nLine)
{
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  if(szFileName!=NULL)
    return new(szFileName, nLine, pMem, nSize, pEBD, nDataSize) YEventString(pEBD,nDataSize);
#endif
  return new(pMem, nSize, pEBD, nDataSize) YEventString(pEBD,nDataSize);
}

YEvent* YEventString::CreateEx(WORD nMessageID, LPCTSTR szString, int nLen, DWORD nSignature, void *pMem, int nMemSize, LPCSTR szFileName, int nLine)
{
  size_t nRawSize = YEventString::SizeOf(szString,nLen);
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  if(szFileName!=NULL)
    return new(szFileName, nLine, pMem, nMemSize, NULL, nRawSize) YEventString(nMessageID, szString, nLen, nSignature);
#endif
  return new(pMem, nMemSize, NULL, nRawSize)  YEventString(nMessageID, szString, nLen, nSignature);
}


YEvent* YEventCryptedString::Allocate(const void *pEBD, size_t nDataSize, void *pMem, size_t nSize, LPCSTR szFileName, int nLine)
{
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  if(szFileName!=NULL)
    return new(szFileName, nLine, pMem, nSize, pEBD, nDataSize) YEventCryptedString(pEBD,nDataSize);
#endif
  return new(pMem, nSize, pEBD, nDataSize) YEventCryptedString(pEBD,nDataSize);
}

YEvent* YEventCryptedString::CreateEx(WORD nMessageID, LPCTSTR szString, int nLen, DWORD nSignature, void *pMem, int nMemSize, LPCSTR szFileName, int nLine)
{
  size_t nRawSize = YEventString::SizeOf(szString,nLen);
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  if(szFileName!=NULL)
    return new(szFileName, nLine, pMem, nMemSize, NULL, nRawSize) YEventCryptedString(nMessageID, szString, nLen, nSignature);
#endif
  return new(pMem, nMemSize, NULL, nRawSize)  YEventCryptedString(nMessageID, szString, nLen, nSignature);
}

#include "xnew.h"//}*

YEVENT_CLASS_IMPLEMENT(YEventString,YEventEx);
YEVENT_CLASS_IMPLEMENT(YEventCryptedString,YEventEx);
