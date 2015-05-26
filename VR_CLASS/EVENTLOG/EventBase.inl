/////////////////////////////////////////////////////////////////////////////
// YEventBaseData inline implementation
#define time_t YEventBaseData::time_t //AY 01.02.2011
#include "xCTime.h"

inline WORD  YEventBaseData::GetClass() const
  { return m_nClass; }

inline WORD  YEventBaseData::GetType() const
  { return m_nClass==EVN_20BIT_CLASS? 0 : m_nType; } //AY 1.02.2005 OLD:{ return m_nType; }

inline WORD  YEventBaseData::GetMessageID() const
  { return m_nData; }

inline DWORD YEventBaseData::GetSignature() const //EVN_xxBIT_CLASS only
  { return m_nClass==EVN_xxBIT_CLASS?((const tagYEventBaseDataEx*)this)->m_nSignature:0; }

inline WORD  YEventBaseData::SetClass(WORD nClass)
  { ASSERT(nClass<=3); return (m_nClass = nClass); }

inline WORD  YEventBaseData::SetType(WORD nType)
  { ASSERT(nType<=15); return (m_nType = nType); }

inline WORD   YEventBaseData::SetMessageID(WORD  nMessageID)
  { return (m_nData = nMessageID); }

inline DWORD  YEventBaseData::SetSignature(DWORD dwSignature)  //EVN_xxBIT_CLASS only
  { ASSERT(m_nClass==3); return m_nClass==EVN_xxBIT_CLASS?(((tagYEventBaseDataEx*)this)->m_nSignature=dwSignature):0; }


inline YTime  YEventBaseData::GetTimeEx() const
{
  const struct tagYEventBaseDataEx& bdex = *reinterpret_cast<const struct tagYEventBaseDataEx*>(this);
  YTIME t = YTime(CTime(m_tTime).GetTime(),m_nMsec);
  if(m_nClass==EVN_xxBIT_CLASS){
    t -= YTIME_CTIME_BASE-YTIME_YTIME_BASE;
    t += bdex.m_nYsec;                             //14 bits
    t += bdex.m_nYera * (0x80000000*YTIME_1SECOND);// 2 bits
    t += YTIME_CTIME_BASE-YTIME_YTIME_BASE;
  }
  return t;
}

inline YTime  YEventBaseData::SetTimeEx(YTime tTime)
{
  struct tagYEventBaseDataEx& bdex = *reinterpret_cast<struct tagYEventBaseDataEx*>(this);
  YTIME t = tTime;
  m_tTime = CTime2TIME_T(tTime);
  m_nMsec = tTime.GetMilliseconds();
  if(m_nClass==EVN_xxBIT_CLASS){
    t -= YTIME_CTIME_BASE-YTIME_YTIME_BASE;
    bdex.m_nYsec = t % YTIME_1MS;                 //14 bits
    bdex.m_nYera = t / (0x80000000*YTIME_1SECOND);// 2 bits
    t += YTIME_CTIME_BASE-YTIME_YTIME_BASE;
    //TO DO: check dates later 2038.01.19 03:14:07 gmt?
  }
  return t;
}

inline time_t YEventBaseData::GetTime(WORD *pnMsec/*NULL*/) const {
  if(pnMsec!=NULL)
    *pnMsec = m_nMsec;
  return m_tTime;
}

inline time_t YEventBaseData::SetTime(time_t tTime, WORD nMsec/*0*/) {
  struct tagYEventBaseDataEx& bdex = *reinterpret_cast<struct tagYEventBaseDataEx*>(this);
  m_tTime = tTime;
  m_nMsec = nMsec;
  if(m_nClass==EVN_xxBIT_CLASS){ //AY 31.01.2005
    bdex.m_nYsec = 0;
    bdex.m_nYera = 0;
  }
  return m_tTime;
}

inline YTime YEventBaseData::SetTimeEx()
  { return SetTimeEx(YTime::GetCurrentTime()); }//TO DO: query true server time

inline void  YEventBaseData::Invalidate()
  { m_tTime=-2, m_nMsec=1000; }

///////////////////////////////////////////////////////////////////////////////////
// YEventBaseData allocation helpers

inline void* YEventBaseData::SetData(const void *pRawData, int nRawSize, size_t nOffset)
{
  ASSERT(GetSize()==nRawSize+nOffset);
  size_t nNeed = GetSize();
  if(nRawSize!=0 && (size_t)nRawSize+nOffset>nNeed)
    return NULL;
  if(nRawSize!=0 && (size_t)nRawSize+nOffset<nNeed)
    nNeed = (size_t)nRawSize+nOffset;
  void* pData = GetData();
  if(nNeed-nOffset==0 || pData==NULL)
    return pData;
  if(pData!=NULL)
    pData = (void*)(((BYTE*)pData)+nOffset);
  memcpy(pData, pRawData, nNeed-nOffset);
  return pData;
}

inline void*  YEventBaseData::GetData(void *pRawData, int nMaxSize, size_t nOffset) const
{
  size_t nNeed = GetSize();
  if(nOffset>nNeed)
    return NULL;
  if(nMaxSize!=0 && (size_t)nMaxSize<nNeed-nOffset)
    return NULL;
  const void* pData = GetData();
  if(nNeed-nOffset==0 || pData==NULL)
    return pRawData;
  if(pData!=NULL)
    pData = (const void*)(((const BYTE*)pData)+nOffset);
  memcpy(pRawData, pData, nNeed-nOffset);
  return pRawData;
}

inline void* YEventBaseData::GetData()
{
  BOOL bxx = (m_nClass==EVN_xxBIT_CLASS);
  BOOL b64 = (m_nClass==EVN_64BIT_CLASS);
  BOOL b20 = (m_nClass==EVN_20BIT_CLASS);
  BOOL b16 = (m_nClass==EVN_16BIT_CLASS);
  if(bxx) return (void*) (((struct tagYEventBaseDataEx*)this) + 1);
  if(b64) return (void*) (((struct tagYEventBaseData*)this) + 1);
  if(b20) return (void*) &m_nData;
  if(b16) return (void*) &m_nData;
  return NULL;//never reached
}

inline const void* YEventBaseData::GetData() const
{
  BOOL bxx = (m_nClass==EVN_xxBIT_CLASS);
  BOOL b64 = (m_nClass==EVN_64BIT_CLASS);
  BOOL b20 = (m_nClass==EVN_20BIT_CLASS);
  BOOL b16 = (m_nClass==EVN_16BIT_CLASS);
  if(bxx) return (const void*) (((const struct tagYEventBaseDataEx*)this) + 1);
  if(b64) return (const void*) (((const struct tagYEventBaseData*)this) + 1);
  if(b20) return (const void*) &m_nData;
  if(b16) return (const void*) &m_nData;
  return NULL;//never reached
}


inline size_t YEventBaseData::GetSize() const
{
  BOOL bxx = (m_nClass==EVN_xxBIT_CLASS);
  BOOL b64 = (m_nClass==EVN_64BIT_CLASS);
  BOOL b20 = (m_nClass==EVN_20BIT_CLASS);
  BOOL b16 = (m_nClass==EVN_16BIT_CLASS);
  if(bxx) return ((const struct tagYEventBaseDataEx*)this)->m_nSize;
  if(b64) return sizeof(struct tagYEventBaseData64)-sizeof(struct tagYEventBaseData);
  if(b20) return 0;
  if(b16) return sizeof(WORD);
  return 0;//never reached
}

inline size_t YEventBaseData::SizeOf() const
{
  BOOL bxx = (m_nClass==EVN_xxBIT_CLASS);
  BOOL b64 = (m_nClass==EVN_64BIT_CLASS);
  BOOL b20 = (m_nClass==EVN_20BIT_CLASS);
  BOOL b16 = (m_nClass==EVN_16BIT_CLASS);
  if(bxx) return sizeof(struct tagYEventBaseDataEx) + ((const struct tagYEventBaseDataEx*)this)->m_nSize;
  if(b64) return sizeof(struct tagYEventBaseData64);
  if(b20) return sizeof(struct tagYEventBaseData);
  if(b16) return sizeof(struct tagYEventBaseData);
  return 0;//never reached
}

inline size_t YEventBaseData::SizeOf(const YEventBaseData* pData, size_t nDataSize)
{
  if(pData==NULL && nDataSize==0)
    return 0;
  if(pData!=NULL && nDataSize==0)
    return pData->SizeOf();
  if(pData==NULL && nDataSize!=0)
    return nDataSize;
  //(pData!=NULL && nDataSize!=0):
  if(nDataSize < sizeof(struct tagYEventBaseData))
    return 0;//error
  if(pData->m_nClass!=EVN_xxBIT_CLASS)
    return pData->SizeOf()<=nDataSize?pData->SizeOf()/*ok*/:0/*error*/;
  if(nDataSize < sizeof(struct tagYEventBaseDataEx))
    return 0;//error
  return pData->SizeOf();
}

#undef  time_t
/////////////////////////////////////////////////////////////////////////////
// YEventBaseDataEx inline implementation

#define time_t YEventBaseDataEx::time_t //AY 01.02.2011
#define YEVENTBASEDATA YEventBaseDataEx //under degisn

inline YTime  YEVENTBASEDATA::SetTimeEx() //TO DO: query true server time
  { return SetTimeEx(YTime::GetCurrentTime()); } //AY 01.02.2011 OLD:{ return SetTimeEx(YTime::GetCurrentTime()).GetTime(); }

inline time_t YEVENTBASEDATA::SetTime()
  { return CTime2TIME_T(SetTimeEx().GetTime()); }//AY 01.02.2011 OLD: return SetTimeEx().GetTime()

inline WORD   YEVENTBASEDATA::GetClass() const
  { return m_nClass; }

inline WORD   YEVENTBASEDATA::GetType() const
  { return m_nClass==EVN_20BIT_CLASS? 0 : m_nType; }

inline WORD   YEVENTBASEDATA::GetMessageID() const
  { return m_nData; }

inline DWORD  YEVENTBASEDATA::GetSignature() const //EVN_xxBIT_CLASS only
  { return m_nClass==EVN_xxBIT_CLASS?((const tagYEventBaseDataEx*)this)->m_nSignature:0; }


inline WORD   YEVENTBASEDATA::SetClass(WORD nClass)
  { ASSERT(nClass<=3); return (m_nClass = nClass); }

inline WORD   YEVENTBASEDATA::SetType(WORD nType)
  { ASSERT(nType<=15); return (m_nType = nType); }

inline WORD   YEVENTBASEDATA::SetMessageID(WORD  nMessageID)
  { return (m_nData = nMessageID); }

inline DWORD  YEVENTBASEDATA::SetSignature(DWORD dwSignature)  //EVN_xxBIT_CLASS only
  { ASSERT(m_nClass==3); return m_nClass==EVN_xxBIT_CLASS?(((tagYEventBaseDataEx*)this)->m_nSignature=dwSignature):0; }

inline time_t YEVENTBASEDATA::GetTime(WORD *pnMsec) const
{ 
  YTime t = GetTimeEx(); 
  if(pnMsec!=NULL)
    *pnMsec = t.GetMilliseconds();
  return CTime2TIME_T(t.GetTime());//AY 01.02.2011
}

inline time_t YEVENTBASEDATA::SetTime(time_t tTime, WORD nMsec)
{
  struct tagYEventBaseDataEx& bdex = *reinterpret_cast<struct tagYEventBaseDataEx*>(this);
  m_tTime = tTime;
  m_nMsec = nMsec;
  if(m_nClass==EVN_xxBIT_CLASS){ //AY 31.01.2005
    bdex.m_nYsec = 0;
    bdex.m_nYera = 0;
  }
  return m_tTime;
}

inline YTime  YEVENTBASEDATA::GetTimeEx() const
{
  const struct tagYEventBaseDataEx& bdex = *reinterpret_cast<const struct tagYEventBaseDataEx*>(this);
  YTIME t = YTime(CTime(m_tTime).GetTime(),m_nMsec);
  if(m_nClass==EVN_xxBIT_CLASS){
    t += bdex.m_nYsec;            //14 bits
    t += bdex.m_nYera*(0x80000000*YTIME_1SECOND) + YTIME_CTIME_BASE;// 2 bits
  }
  return t;
}

inline YTime  YEVENTBASEDATA::SetTimeEx(YTime tTime)
{
  struct tagYEventBaseDataEx& bdex = *reinterpret_cast<struct tagYEventBaseDataEx*>(this);
  YTIME t = tTime;
  m_tTime = CTime2TIME_T(tTime);//AY 01.02.2011 OLD: CTime(tTime).GetTime()
  m_nMsec = tTime.GetMilliseconds();
  if(m_nClass==EVN_xxBIT_CLASS){
    bdex.m_nYsec = t % YTIME_1MS;//14 bits
    bdex.m_nYera = (t - YTIME_CTIME_BASE)/(0x80000000*YTIME_1SECOND);// 2 bits
  }
  ASSERT(t==GetTimeEx());//TO DO: check dates later 2038.01.19 03:14:07 gmt?
  return t;
}

inline DWORD YEVENTBASEDATA::GetSize()const
{
  const YEventBaseData& bd = *reinterpret_cast<const YEventBaseData*>(this);
  return bd.GetSize();
}
inline const void* YEVENTBASEDATA::GetData()const
{
  const YEventBaseData& bd = *reinterpret_cast<const YEventBaseData*>(this);
  return bd.GetData();
}
inline void* YEVENTBASEDATA::GetData()
{
  YEventBaseData& bd = *reinterpret_cast<YEventBaseData*>(this);
  return bd.GetData();
}

#undef time_t
#undef YEVENTBASEDATA//under degisn
