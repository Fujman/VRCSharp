#ifndef __EVENT_INL
#define __EVENT_INL
///////////////////////////////////////////////////////////////////////////////////
// YEvent allocation helpers

inline size_t YEvent::SizeOf() const
{
  return YEventBaseData::SizeOf();
}

///////////////////////////////////////////////////////////////////////////////////
// YEvent
inline int    YEvent::GetDataSize() const
{
  return YEventBaseData::SizeOf();
}

inline void*  YEvent::GetData(void *pData, int nMaxSize) const
{
  size_t nNeed = YEventBaseData::SizeOf();
  if(nMaxSize!=0 && (size_t)nMaxSize<nNeed)
    return NULL;
  memcpy(pData, (const YEventBaseData*)this, nNeed);
  return pData;
}

inline void*  YEvent::GetRawData(void *pRawData, int nMaxSize, size_t nOffset) const
{
  void* pData = YEventBaseData::GetData(pRawData, nMaxSize, nOffset);
  if(pData!=NULL)
    Decode(pData, YEventBaseData::GetSize()-nOffset, nOffset);
  return pData;//pRawData;
}

inline void*  YEvent::SetRawData(const void *pRawData, int nRawSize, size_t nOffset)
{
  void* pData = YEventBaseData::SetData(pRawData, nRawSize, nOffset);
  if(pData!=NULL)
    Encode(pData, YEventBaseData::GetSize()-nOffset, nOffset);
  return pData;//this;
}

inline int    YEvent::GetRawSize() const // without base data
{
  return YEventBaseData::GetSize();
}

inline int    YEvent::IsEmpty() const 
{
  return (m_tTime==0 && m_nMsec==0 && m_nClass==0 && m_nType==0);
}

inline void   YEvent::Encode(void *pData, size_t nSize, size_t nOffset) const
{
}
inline void   YEvent::Decode(void *pData, size_t nSize, size_t nOffset) const
{
}

inline YEventsProtocol* YEvent::GetLog()
{
  /*ASSERT(s_pLog!=NULL);*/ return s_pLog;
}

inline int YEvent::SetLog(YEventsProtocol* pLog)
{
  s_pLog = pLog; return 0;
}

/////////////////////////////////////////////////////////////////////////////
// YEvent16 inline implementation
inline WORD  YEvent16::GetData16() const
  { return m_nData; }
inline WORD  YEvent16::SetData16(WORD nData)
  { return (m_nData = nData); }

inline YEvent16::YEvent16(const void *p, int n/*0*/) {
  const tagYEventBaseData *pEBD = (const tagYEventBaseData *)p;
  ASSERT(pEBD!=NULL);  ASSERT(pEBD->m_nClass==EVN_16BIT_CLASS);
	m_nClass = EVN_16BIT_CLASS;
  if(n>0 && n>=sizeof(tagYEventBaseData)) {
    m_nClass=pEBD->m_nClass;
    m_nType=pEBD->m_nType;
    m_nMsec=pEBD->m_nMsec;
    m_tTime=pEBD->m_tTime;
    m_nData=pEBD->m_nData;
  }else{
    Invalidate();
  }
}
inline YEvent16::YEvent16() {
  m_nClass=EVN_16BIT_CLASS;
  m_nType=0;
  m_nMsec=0;
  m_tTime=0;
  m_nData=0;
}
inline YEvent16::YEvent16(WORD nType, WORD nData/*0*/) { // 16 bit
  m_nClass=EVN_16BIT_CLASS;
  SetType(nType);
  m_nMsec=0;
  m_tTime=0;
  SetData16(nData);
}

/////////////////////////////////////////////////////////////////////////////
// YEvent20 inline implementation
inline DWORD YEvent20::GetData20() const
  { return (((DWORD)m_nType)<<16) | m_nData; }

inline DWORD YEvent20::SetData20(DWORD dwData) {
  ASSERT((dwData>>16)<=15);
  m_nData = (WORD)dwData;
  m_nType = (WORD)(dwData>>16);
  return dwData;
}

inline YEvent20::YEvent20(const void *p, int n/*0*/) {
  const tagYEventBaseData *pEBD = (const tagYEventBaseData *)p;
  ASSERT(pEBD!=NULL);  ASSERT(pEBD->m_nClass==EVN_20BIT_CLASS);
	m_nClass = EVN_20BIT_CLASS;
  if(n>0 && n>=sizeof(tagYEventBaseData)) {
    m_nClass=pEBD->m_nClass;
    m_nType=pEBD->m_nType;
    m_nMsec=pEBD->m_nMsec;
    m_tTime=pEBD->m_tTime;
    m_nData=pEBD->m_nData;
  }else{
    Invalidate();
  }
}
inline YEvent20::YEvent20() {
  m_nClass=EVN_20BIT_CLASS;
  m_nMsec=0;
  m_tTime=0;
  m_nType=0;
  m_nData=0;
}
inline YEvent20::YEvent20(DWORD dwData/*0*/) {              // 20 bit
  m_nClass=EVN_20BIT_CLASS;
  m_nMsec=0;
  m_tTime=0;
  SetData20(dwData);
}

/////////////////////////////////////////////////////////////////////////////
// YEvent64 implementation
inline BYTE  YEvent64::GetData8(int n/*0*/)const {
  if(n<=1)
    return ((const BYTE*)m_nData)[n];
  ASSERT(n<10);
  return ((const BYTE*)m_dwData)[n-2];
}

inline BYTE  YEvent64::SetData8(BYTE nData, int n/*0*/) {
  if(n<=1)
    return ( ((BYTE*)m_nData)[n] = n );
  ASSERT(n<10);
  return ( ((BYTE*)m_dwData)[n-2] = n );
}

inline WORD  YEvent64::GetData16(int n/*0*/) const {
  if(n<=0)
    return m_nData;
  ASSERT(n<5);
  return ((const WORD*)m_dwData)[n-1];
}
inline WORD  YEvent64::SetData16(WORD nData, int n/*0*/) {
  if(n<=0)
    return (m_nData = nData);
  ASSERT(n<5);
  return ((WORD*)m_dwData)[n-1] = nData;
}

inline DWORD  YEvent64::GetData32(int n/*0*/) const {
  ASSERT(n>=0 && n<2);
  return m_dwData[n];
}
inline DWORD  YEvent64::SetData32(DWORD dwData, int n/*0*/) {
  ASSERT(n>=0 && n<2);
  return (m_dwData[n] = dwData);
}

inline DWORD  YEvent64::GetData64(DWORD* pdwData2) const {
  if(pdwData2!=NULL)
    *pdwData2 = m_dwData[1];
  return m_dwData[0];
}

inline DWORD  YEvent64::SetData64(DWORD* pdwData2) {
  ASSERT(pdwData2!=NULL);
  m_dwData[0] = pdwData2[0];
  m_dwData[1] = pdwData2[1];
  return m_dwData[0];
}

inline YEvent64::YEvent64(const void* p, int n/*0*/) {
  const tagYEventBaseData *pEBD = (const tagYEventBaseData *)p;
  ASSERT(pEBD!=NULL);  ASSERT(pEBD->m_nClass==EVN_64BIT_CLASS);
  m_nClass = EVN_64BIT_CLASS;
  if(n>0 && n>=sizeof(tagYEventBaseData64)) {
    m_nType=pEBD->m_nType;
    m_nMsec=pEBD->m_nMsec;
    m_tTime=pEBD->m_tTime;
    m_nData=pEBD->m_nData;
    DWORD *pdw = (DWORD *)((BYTE*)p + sizeof(YEventBaseData)); // Intel!
    m_dwData[0] = pdw[0];
    m_dwData[1] = pdw[1];
  }else{
    Invalidate();
  }
}
inline YEvent64::YEvent64(WORD nType/*0*/, DWORD dwData/*0*/, DWORD dwData2/*0*/)
{
  m_nClass=EVN_64BIT_CLASS;
  m_nMsec=0;
  m_tTime=0;
  SetData16(0);
  SetType(nType);
  m_dwData[0] = dwData;
  m_dwData[1] = dwData2;
}

inline int YEvent64::IsEmpty() const 
{
  return (YEvent::IsEmpty() && m_dwData[0]==0 && m_dwData[1]==0);
}

#endif//__EVENT_INL
