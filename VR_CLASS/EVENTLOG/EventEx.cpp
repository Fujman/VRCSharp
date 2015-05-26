#include "stdafx.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "EventEx.h"

///////////////////////////////////////////////////////////////////////////////
// YEventEx

//012345678901234567890123456789012345678901234567890123456789012345 6 //len=54+
//01.02.1980 Wed 02:03:55,999 C T DA16 DATA32BI DATA32BI XX XX XX...\0 //64 bit+
LPTSTR YEventEx::GetText(LPTSTR szEvent, int nLength) const
{ ASSERT(!"check"); //KSN
  LPTSTR szRet = YEvent64::GetText(szEvent, nLength);
  if(szRet!=NULL){
    const BYTE* pData = (const BYTE*)YEventBaseData::GetData();
    int nSize = GetRawSize();
    int nLen = _tcslen(szEvent);
    LPTSTR sz = szEvent + nLen;
    for(int i=0; i<nSize&&i<64&&nLen+4/*...| XX*/<nLength; ++i,sz+=3,nLen+=3){
      BYTE by = pData[i], by0=(by>>4), by1=(by&0xF);
      sz[3] = '\0';
      sz[0] = ' ';
      sz[1] = (by0<10)?'0'+by0:'A'+by0-10;
      sz[2] = (by1<10)?'0'+by1:'A'+by1-10;
    }
    if(i<nSize)
      sz[3]='\0',sz[0]=sz[1]=sz[2]='.';
  }
  return szRet;
}

LPTSTR YEventEx::GetDump(LPTSTR szEvent, int nLength) const
{

  const BYTE* pData = (const BYTE*)YEventBaseData::GetData();
  int nSize = GetRawSize();
  int nLen = 0;
  LPTSTR sz = szEvent;
  for(int i=0; i<nSize&&nLen+6/*...|   XX*/<nLength; ++i,sz+=3,nLen+=3){
    BYTE by = pData[i], by0=(by>>4), by1=(by&0xF);
    sz[2] = '\0';
    if     (i!=0 && i%16==0)
      {sz[0]='\r'; sz[1]='\n'; sz+=2; nLen+=2;}
    else if(i!=0 && i%8==0)
      {sz[0]=sz[1]=' '; sz+=2; nLen+=2;}
    sz[2] = '\0';
    sz[0] = (by0<10)?'0'+by0:'A'+by0-10;
    sz[1] = (by1<10)?'0'+by1:'A'+by1-10;
  }
  if(i<nSize)
    sz[3]='\0',sz[0]=sz[1]=sz[2]='.';
  return szEvent;
}

LPTSTR YEventEx::GetInfo(LPTSTR szEvent, int nLength, int* pnLevel, int* pnClass, DWORD* pdwCategory) const
{
  LPTSTR szEvent1 = YEvent64::GetInfo(szEvent, nLength, pnLevel, pnClass, pdwCategory);
  LPTSTR szEvent2 = YEvent64::GetText(szEvent, nLength);
  return szEvent2;
}

inline const BYTE *memxchr(const void *buf, int c, size_t size)
{
  const BYTE *p = (const BYTE *)buf;
  for(size_t n=0; n<size; ++n){
    if(p[n]!=(BYTE)(unsigned)c)
      return p;
    else if(n==size)
      break;
  }
  return NULL;
}

int YEventEx::IsEmpty() const
{
  if(YEvent64::IsEmpty())
    return TRUE;
  return FALSE;
#if 0 //?
  struct tagYEventBaseDataEx& bdex = *reinterpret_cast<struct tagYEventBaseDataEx*>(this);
  BOOL bEmpty = (m_tTime==0 && m_nMsec==0 && m_nClass==0 && m_nType==0)
         &&(bdex.m_nSignature==0 && bdex.m_nYsec==0 && bdex.m_nYera==0)
         &&(NULL==memxchr(YEventBaseData::GetData(),0,YEventBaseData::GetSize());
  return bEmpty;
#endif
}

LPWSTR   YEventEx::SetString(LPCWSTR sz, int nLen)
{
  if(sz==NULL) return NULL;
  nLen = nLen>=0 ? nLen : wcslen(sz);  ASSERT(YEventBaseData::GetSize()>=(nLen+1)*sizeof(wchar_t));
  LPWSTR szTHIS = (LPWSTR)YEventBaseData::GetData();
  VERIFY( SetRawData(sz, ((size_t)nLen)*sizeof(wchar_t)) !=NULL);
  wchar_t wc[1] = {L'\0'};
  VERIFY( SetRawData(wc, sizeof(wchar_t), ((size_t)nLen)*sizeof(wchar_t)) !=NULL);
  return szTHIS;
}

LPWSTR   YEventEx::GetString(LPWSTR sz,int nMaxLen) const
{
  if(sz==NULL) return NULL;
  int nLen = (GetRawSize()+sizeof(wchar_t)-1)/sizeof(wchar_t);
  if(nLen>nMaxLen) //TO DO: truncated strings?
    return NULL;
  VERIFY( GetRawData(sz, ((size_t)nLen)*sizeof(wchar_t)) !=NULL);
  return sz;
}

LPCWSTR  YEventEx::GetString()const
{
  return (LPCWSTR)YEventBaseData::GetData();
}

// dynamic construction //////////////////////////////////////////////////////
#include "xnew.h"//*{

YEvent* YEventEx::Allocate(const void *pEBD, size_t nDataSize, void *pMem, size_t nMemSize, LPCSTR szFileName, int nLine)
{
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  if(szFileName!=NULL)
    return new(szFileName, nLine, pMem, nMemSize, pEBD, nDataSize) YEventEx(pEBD,nDataSize);
#endif
  return new(pMem, nMemSize, pEBD, nDataSize) YEventEx(pEBD,nDataSize);
}

YEvent* YEventEx::CreateEx(WORD nType, WORD nMessageID, int nRawSize, const void *pRawData, DWORD nSignature, void *pMem, int nMemSize, LPCSTR szFileName, int nLine)
{
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  if(szFileName!=NULL)
    return new(szFileName, nLine, pMem, nMemSize, NULL, nRawSize) YEventEx(nType, nMessageID, nRawSize, pRawData, nSignature);
#endif
  return new(pMem, nMemSize, NULL, nRawSize)  YEventEx(nType, nMessageID, nRawSize, pRawData, nSignature);
}

#include "xnew.h"//}*

YEVENT_CLASS_IMPLEMENT(YEventEx,YEvent64);

#if 0 ////////////////////////////////////////////////////////////////////////////////
YMidiCallback::OnEvent(YDevice* pDevice, int nCommand, UINT nAnswer)
{
  YMidiActionInfo info(nCommand,nAnswer);
  YEventMidi ev(info); m_pJournal->PutEvent(ev);

#ifdef _DEBUG$$
  YEventsProtocol* pJournal = m_pJournal;
  BYTE abyBuffer[256];

  YEventData* pEvData = (YEventData*) YEventData::
    CreateEx(0,sizeof(YMidiActionInfo),&info,0x12ABCDEF,(void*)abyBuffer,sizeof(abyBuffer) DEBUG_NEW_FILE_LINE);
  pJournal->PutEvent(*pEvData);
  char sz[256]; pEvData->GetInfo(sz,256);
  YEventData::Delete(pEvData,(void*)abyBuffer);

  pEvData = (YEventData*) YEventData::
    CreateEx(IDSE_CHN_START,sizeof(YMidiActionInfo),&info,0x12ABCDEF,NULL,0 DEBUG_NEW_FILE_LINE);
  pJournal->PutEvent(*pEvData);
  pEvData->GetInfo(sz,256);
  YEventData::Delete(pEvData);

  char sTest[] = "ABCDEFGHIJKLMNOPQRSTUVWXY"; sTest[sizeof(sTest)-1]='Z';
  char* szTest = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  YEventString* pEvStr = (YEventString*) YEventString::
    CreateEx(IDSE_CHN_START,szTest,-1,0xABCDEF,NULL,0 DEBUG_NEW_FILE_LINE);
  LPCWSTR wzStr = ((YEventEx*)pEvStr)->GetString();
  CString szStr = pEvStr->GetString();
  pJournal->PutEvent(*pEvStr);
  pEvStr->GetInfo(sz,256);
  YEventString::Delete(pEvStr);

  pEvStr = (YEventString*) YEventString::
    CreateEx(IDSE_CHN_START,sTest,24,0x123456,NULL,0 DEBUG_NEW_FILE_LINE);
  pJournal->PutEvent(*pEvStr);
  pEvStr->GetInfo(sz,256);
  YEventString::Delete(pEvStr);

  YEventCryptedString* pEvCry = (YEventCryptedString*) YEventCryptedString::
    CreateEx(IDSE_CHN_START,szTest,-1,0xABCDEF,NULL,0 DEBUG_NEW_FILE_LINE);
  szStr = pEvCry->GetString();
  pJournal->PutEvent(*pEvCry);
  pEvCry->GetInfo(sz,256);
  YEventCryptedString::Delete(pEvCry);

  pEvCry = (YEventCryptedString*) YEventCryptedString::
    CreateEx(IDSE_CHN_START,sTest,24,0x123456,NULL,0 DEBUG_NEW_FILE_LINE);
  pJournal->PutEvent(*pEvCry);
  pEvCry->GetInfo(sz,256);
  YEventCryptedString::Delete(pEvCry);

  pEvCry = (YEventCryptedString*) YEventCryptedString::
    CreateEx(IDSE_CHN_START,sTest,23,0x123456,NULL,0 DEBUG_NEW_FILE_LINE);
  pJournal->PutEvent(*pEvCry);
  pEvCry->GetInfo(sz,256);
  YEventCryptedString::Delete(pEvCry);

  pEvCry = (YEventCryptedString*) YEventCryptedString::
    CreateEx(IDSE_CHN_START,sTest,22,0x123456,NULL,0 DEBUG_NEW_FILE_LINE);
  pJournal->PutEvent(*pEvCry);
  pEvCry->GetInfo(sz,256);
  YEventCryptedString::Delete(pEvCry);

  pEvCry = (YEventCryptedString*) YEventCryptedString::
    CreateEx(IDSE_CHN_START,sTest,21,0x123456,NULL,0 DEBUG_NEW_FILE_LINE);
  pJournal->PutEvent(*pEvCry);
  pEvCry->GetInfo(sz,256);
  YEventCryptedString::Delete(pEvCry);

  pEvCry = (YEventCryptedString*) YEventCryptedString::
    CreateEx(IDSE_CHN_START,sTest,0,0x123456,NULL,0 DEBUG_NEW_FILE_LINE);
  pJournal->PutEvent(*pEvCry);
  pEvCry->GetInfo(sz,256);
  YEventCryptedString::Delete(pEvCry);

  pEvCry = (YEventCryptedString*) YEventCryptedString::
    CreateEx(IDSE_CHN_START,sTest,1,0x123456,NULL,0 DEBUG_NEW_FILE_LINE);
  pJournal->PutEvent(*pEvCry);
  pEvCry->GetInfo(sz,256);
  YEventCryptedString::Delete(pEvCry);

  pEvCry = (YEventCryptedString*) YEventCryptedString::
    CreateEx(IDSE_CHN_START,sTest,2,0x123456,NULL,0 DEBUG_NEW_FILE_LINE);
  pJournal->PutEvent(*pEvCry);
  pEvCry->GetInfo(sz,256);
  YEventCryptedString::Delete(pEvCry);

  pEvCry = (YEventCryptedString*) YEventCryptedString::
    CreateEx(IDSE_CHN_START,sTest,3,0x123456,NULL,0 DEBUG_NEW_FILE_LINE);
  pJournal->PutEvent(*pEvCry);
  pEvCry->GetInfo(sz,256);
  YEventCryptedString::Delete(pEvCry);

  pEvCry = (YEventCryptedString*) YEventCryptedString::
    CreateEx(IDSE_CHN_START,sTest,4,0x123456,NULL,0 DEBUG_NEW_FILE_LINE);
  pJournal->PutEvent(*pEvCry);
  pEvCry->GetInfo(sz,256);
  YEventCryptedString::Delete(pEvCry);
#endif

  return 0;
}
#endif
