#ifndef __EVNTDATA_INL
#define __EVNTDATA_INL
/////////////////////////////////////////////////////////////////////////////
// YEventEx inline implementation

inline YEventData::YEventData(const void* p, int n)
  :YEventEx(p,n) { ASSERT(m_nType==EVN_GENERIC_DATA); }

inline YEventData::YEventData(WORD nMessageID, int nRawSize, const void *pRawData, DWORD dwSignature)
  :YEventEx(EVN_GENERIC_DATA,nMessageID,nRawSize,pRawData,dwSignature) {}

#endif//__EVNTDATA_INL
