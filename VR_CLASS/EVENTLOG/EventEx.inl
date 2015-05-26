#ifndef __EVENTEX_INL
#define __EVENTEX_INL
/////////////////////////////////////////////////////////////////////////////
// YEventEx inline implementation

inline YEventEx::YEventEx(const void* p/*EBD*/, int n/*MaxSize*/)
{
  const tagYEventBaseDataEx *pEBD = (const tagYEventBaseDataEx *)p;
  ASSERT(pEBD!=NULL);  ASSERT(pEBD->m_nClass==EVN_xxBIT_CLASS);
	m_nClass = EVN_xxBIT_CLASS;
  if(n>0 && n>=YEventEx::SIZE_OF_BASE_DATA) {
    tagYEventBaseDataEx* pTHIS = (tagYEventBaseDataEx *)(YEventBaseData*)this;
    pTHIS->m_nType=pEBD->m_nType;
    pTHIS->m_nMsec=pEBD->m_nMsec;
    pTHIS->m_tTime=pEBD->m_tTime;
    pTHIS->m_nData=pEBD->m_nData;
    pTHIS->m_nYsec=pEBD->m_nYsec;
    pTHIS->m_nYera=pEBD->m_nYera;
    pTHIS->m_nSize=pEBD->m_nSize;
    pTHIS->m_nSignature=pEBD->m_nSignature;
    const YEventBaseData* pBase = (const YEventBaseData*)p;
    if(pBase->GetSize()>0)
      VERIFY(NULL!= YEventBaseData::SetData(pBase->GetData(), pBase->GetSize()) );
  }else{
    Invalidate();
  }
}

inline YEventEx::YEventEx(WORD nType, WORD nMessageID, int nRawSize, const void *pRawData, DWORD nSignature)
{
  ASSERT(nRawSize>=0 && nRawSize<=0xFFFF);
  tagYEventBaseDataEx* pTHIS = (tagYEventBaseDataEx *)(YEventBaseData*)this;
	m_nClass = EVN_xxBIT_CLASS;
  pTHIS->m_nType=nType;
  pTHIS->m_nMsec=0;
  pTHIS->m_tTime=0;
  pTHIS->m_nData=nMessageID;
  pTHIS->m_nYsec=0;
  pTHIS->m_nYera=0;
  pTHIS->m_nSize=(WORD) nRawSize;
  pTHIS->m_nSignature=nSignature;
  if(pRawData!=NULL)
    VERIFY(NULL!= YEventBaseData::SetData(pRawData, nRawSize) );
}


inline BYTE     YEventEx::GetData8 (int n)const
{
  BYTE v=0;
  GetRawData((void*)&v,sizeof(v),n*sizeof(v)); 
  return v;
}

inline BYTE     YEventEx::SetData8 (BYTE v, int n)
{
  SetRawData((void*)&v,sizeof(v),n*sizeof(v)); 
  return v;
}

inline WORD     YEventEx::GetData16(int n)const
{
  WORD v=0;
  GetRawData((void*)&v,sizeof(v),n*sizeof(v)); 
  return v;
}

inline WORD     YEventEx::SetData16(WORD v, int n)
{
  SetRawData((void*)&v,sizeof(v),n*sizeof(v)); 
  return v;
}

inline DWORD    YEventEx::GetData32(int n)const
{
  DWORD v=0;
  GetRawData((void*)&v,sizeof(v),n*sizeof(v)); 
  return v;
}

inline DWORD    YEventEx::SetData32(DWORD v, int n)
{
  SetRawData((void*)&v,sizeof(v),n*sizeof(v)); 
  return v;
}

inline QWORD    YEventEx::GetData64(int n)const
{
  QWORD v=0;
  GetRawData((void*)&v,sizeof(v),n*sizeof(v)); 
  return v;
}

inline QWORD    YEventEx::SetData64(QWORD v, int n)
{
  SetRawData((void*)&v,sizeof(v),n*sizeof(v)); 
  return v;
}

#endif//__EVENTEX_INL
