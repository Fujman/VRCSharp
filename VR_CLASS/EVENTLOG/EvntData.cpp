#include "stdafx.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "EvntData.h"
#include "EventLog.h"

///////////////////////////////////////////////////////////////////////////////
// YEventData

//012345678901234567890123456789012345678901234567890123456789012345 6 //len=54+
//01.02.1980 Wed 02:03:55,999 C T xxxx xxxx xxxxxxxx "resource string" XX XX XX...\0 //64 bit+
//                                mess size signature

LPTSTR YEventData::GetInfo(LPTSTR szEvent, int nLength, int* pnLevel, int* pnClass, DWORD* pdwCategory) const
{
  CString szText;
  if(GetMessageID())
    GetMessageInfo(GetMessageID(),szText,pnLevel,pnClass,pdwCategory);
  else //defaults
    YEvent::GetInfo(szEvent,nLength, pnLevel, pnClass, pdwCategory);
  if(szEvent==NULL)
    return NULL;
  LPTSTR sz = YEventEx::GetText(szEvent, nLength);
  if(sz==NULL)
    return NULL;
  ASSERT(_tcslen(szEvent)>=41);
  _tcscpy(szEvent+41,szEvent+45);//skip Ysec=Yera
  if(!szText.IsEmpty())
    szText += ' ';
  if(_tcslen(szEvent)+1+szText.GetLength()>nLength)
    return NULL;
  ASSERT(_tcslen(szEvent)>=51);
  if(!szText.IsEmpty()) {
    ASSERT(!"check");
    memmove(szEvent+51+szText.GetLength(),szEvent+51,(_tcslen(szEvent+51)+1)*sizeof(*szEvent));
    _tcsncpy(szEvent+51,szText,szText.GetLength());
  }
  return szEvent;
}
LPTSTR YEventData::GetText(LPTSTR szEvent, int nLength) const
{
  return YEventEx::GetText(szEvent, nLength);
}
LPTSTR YEventData::GetDump(LPTSTR szEvent, int nLength) const
{
  return YEventEx::GetDump(szEvent, nLength);
}

int YLogDataEvent(WORD nMessageID, const void* pData, int nSize, DWORD nSignature)
{
  BYTE abyBuffer[512];//on stack data size
  YEvent* pev = YEventData::CreateEx(nMessageID, nSize, pData, nSignature, (void *)abyBuffer, sizeof(abyBuffer) DEBUG_NEW_FILE_LINE);
  int iRet = YEvent::GetLog()->PutEvent(*pev);
  YEvent::Delete(pev,(void*)abyBuffer);
  return iRet;
}


// dynamic construction //////////////////////////////////////////////////////
#include "xnew.h"//*{

YEvent* YEventData::Allocate(const void *pEBD, size_t nDataSize, void *pMem, size_t nMemSize, LPCSTR szFileName, int nLine)
{
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  if(szFileName!=NULL)
    return new(szFileName, nLine, pMem, nMemSize, pEBD, nDataSize) YEventData(pEBD,nDataSize);
#endif
  return new(pMem, nMemSize, pEBD, nDataSize) YEventData(pEBD,nDataSize);
}

YEvent* YEventData::CreateEx(WORD nMessageID, int nRawSize, const void *pRawData, DWORD nSignature, void *pMem, int nMemSize, LPCSTR szFileName, int nLine)
{
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  if(szFileName!=NULL)
    return new(szFileName, nLine, pMem, nMemSize, NULL, nRawSize) YEventData(nMessageID, nRawSize, pRawData, nSignature);
#endif
  return new(pMem, nMemSize, NULL, nRawSize)  YEventData(nMessageID, nRawSize, pRawData, nSignature);
}


#include "xnew.h"//}*

YEVENT_CLASS_IMPLEMENT(YEventData,YEventEx);
