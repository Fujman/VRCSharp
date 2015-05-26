#ifndef __EVENTSTR_INL
#define __EVENTSTR_INL

/////////////////////////////////////////////////////////////////////////////
// YEventString inline implementation

inline YEventString::YEventString(const void *p, int n)
  :YEventEx(p,n) { ASSERT(m_nType==EVN_GENERIC_UNICODE); }

inline YEventString::YEventString(WORD nMessageID, LPCTSTR sz, int nLen, DWORD dwSignature)
  :YEventEx(EVN_GENERIC_UNICODE,nMessageID,YEventString::SizeOf(sz, nLen),NULL,dwSignature)
    { SetData(sz,nLen); }

inline LPTSTR YEventString::GetText(LPTSTR szEvent, int nLength) const
  { return GetInfo(szEvent, nLength); }

inline LPTSTR YEventString::GetDump(LPTSTR szEvent, int nLength) const
  { return YEventEx::GetDump(szEvent, nLength); }

/////////////////////////////////////////////////////////////////////////////
// YEventCryptedString inline implementation

inline YEventCryptedString::YEventCryptedString(const void *p, int n)
  :YEventEx(p,n) { ASSERT(m_nType==EVN_CRYPTED_STRING); }

inline YEventCryptedString::YEventCryptedString(WORD nMessageID, LPCTSTR sz, int nLen, DWORD dwSignature)
  :YEventEx(EVN_CRYPTED_STRING,nMessageID,YEventString::SizeOf(sz, nLen),NULL,dwSignature)
    { SetData(sz,nLen); }

inline LPTSTR YEventCryptedString::GetText(LPTSTR szEvent, int nLength) const
  { return GetInfo(szEvent, nLength); }

inline LPTSTR YEventCryptedString::GetDump(LPTSTR szEvent, int nLength) const
  { return YEventEx::GetDump(szEvent, nLength); }

inline void  YEventCryptedString::Encode(void *pData, size_t nSize, size_t nOffset) const
  { Crypto(pData, nSize, nOffset); }

inline void  YEventCryptedString::Decode(void *pData, size_t nSize, size_t nOffset) const
  { Crypto(pData, nSize, nOffset); }

#endif//__EVENTSTR_INL
