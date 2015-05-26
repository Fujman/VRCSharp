#ifndef __YDATA_H
#define __YDATA_H
///////////////////////////////////////////////////////////////////////////////////////

template <class T, class ITEMS> struct YCyclicData;
template <class T, class ITEMS> struct    YCacheData;
template <class T, class ITEMS> struct YCodedData;

///////////////////////////////////////////////////////////////////////////////////////
// YCyclicData (two part buffer implementation)
template <class T, class ITEMS=int>
struct YCyclicData {
public://cyclic buffer data representation
  T*      pData1;
  ITEMS   nSize1;//items
  T*      pData2;
  ITEMS   nSize2;//items

public://packets buffer support
  static ITEMS GetSparseDataSize(ITEMS nSize, int nNumChannels, int nChannel=0);
  ITEMS   GetSparseData(T* pBuffer, ITEMS nSize, int nNumChannels, int nChannel=0) const;
  ITEMS   SetSparseData(const T* pBuffer, ITEMS nSize, int nNumChannels, int nChannel=0);

  static ITEMS GetSparseDataSparseBufferSize(
            int nBufferNumChannels, int nBufferChannel,
            ITEMS nSize, int nNumChannels=1, int nChannel=0);
  ITEMS   GetSparseDataToSparseBuffer(
            T* pBuffer, ITEMS nSize, int nBufferNumChannels=1, int nBufferChannel=0,
            int nNumChannels=1, int nChannel=0) const;
  ITEMS   SetSparseDataToSparseBuffer(
            const T* pBuffer, ITEMS nSize, int nBufferNumChannels=1, int nBufferChannel=0,
            int nNumChannels=1, int nChannel=0);

  //WARNING: functions are not tested!
  ITEMS   GetSparseDataToSparseData(
            YCyclicData<T,ITEMS>* pData, ITEMS nDataNumChannels=1, ITEMS nDataChannel=0,
            int nNumChannels=1, int nChannel=0) const;
  ITEMS   SetSparseDataToSparseData(
            const YCyclicData<T,ITEMS>* pData, ITEMS nDataNumChannels=1, ITEMS nDataChannel=0,
            int nNumChannels=1, int nChannel=0);

public://data copying functions
  ITEMS   GetData(T* pBuffer, ITEMS nSize) const;
  ITEMS   SetData(const T* pBuffer, ITEMS nSize);

public://data copying functions
  ITEMS   GetData(YCyclicData<T,ITEMS>* pData) const
            { return GetSparseDataToSparseData(pData); }
  ITEMS   SetData(const YCyclicData<T,ITEMS>* pData)
            { return SetSparseDataToSparseData(pData); }

public://data converting functions
  ITEMS   GetData(YCodedData<T,ITEMS>* pData) const;
  ITEMS   SetData(const YCodedData<T,ITEMS>* pData);

public://attributes
  ITEMS   GetSize() const;

public://operations
  BOOL    Verify() const;
  ITEMS   Truncate(ITEMS nSize); //items truncated, nSize - new size
  ITEMS   Displace(ITEMS nSize); //items skipped  , nSize - new size

public://operators
  T&      operator[](ITEMS i) const;

public:
#ifdef _DEBUG
  int     DumpElement(const T* e);
  int     Dump() const;
#else
  int     Dump() const {return 0;}
#endif
};

///////////////////////////////////////////////////////////////////////////////////////
// YCacheData (three mirrored part buffer implementation)
template <class T, class ITEMS=int>
struct YCacheData : public YCyclicData<T,ITEMS> {
public://cache duplet buffer data representation
//T*      pData1;
//ITEMS   nSize1;//items
//T*      pData2;
//ITEMS   nSize2;//items
public:
  int     Plain(T* pBuffer, ITEMS nSize, ITEMS nTile=-1);//with data copy
  int     Cycle(T* pBuffer, ITEMS nSize, ITEMS nTile=-1);//with data copy
  int     Plain(const T* pBuffer, ITEMS nSize, ITEMS nTile=-1);
  int     Cycle(const T* pBuffer, ITEMS nSize, ITEMS nTile=-1);
public:
  BOOL    IsSparse() const;
  BOOL    IsPlain() const;
  BOOL    IsCycle() const;
public:
          operator const T*() const;//NULL and assert in cycle state
          operator T*();            //NULL and assert in cycle state
};

///////////////////////////////////////////////////////////////////////////////////////
// YCodedData
template <class T, class ITEMS=int>
struct YCodedData
{
protected://buffer data
  void*   pData;//bytes
  size_t  nSize;//bytes

public://data copying/converting functions
  virtual ITEMS GetData(YCyclicData<T,ITEMS>* pData) const;
  virtual ITEMS SetData(const YCyclicData<T,ITEMS>* pData);

  virtual ITEMS GetData(T* pBuffer, ITEMS nSize) const;
  virtual ITEMS SetData(const T* pBuffer, ITEMS nSize);

  virtual ITEMS GetSize() const;//items

public://data converting functions
  virtual/*static*/ int decode(T* pBuffer, const void* pCoded, ITEMS nSize, ITEMS nOffs=0) const;//copy implementation by default
  virtual/*static*/ int encode(void* pCoded, const T* pBuffer, ITEMS nSize, ITEMS nOffs=0);//copy implementation by default
};


// YCyclicData implementation ////////////////////////////////////////////////////////

template <class T, class ITEMS> inline
ITEMS YCyclicData<T,ITEMS>::GetData(T* pBuffer, ITEMS nSize) const
{
  if(nSize1+nSize2>nSize)
    return -1;
  memcpy(pBuffer,pData1,nSize1*sizeof(T));
  if(nSize2>0)
    memcpy(pBuffer+nSize1,pData2,nSize2*sizeof(T));
  return nSize1+nSize2;
}

template <class T, class ITEMS> inline
ITEMS YCyclicData<T,ITEMS>::SetData(const T* pBuffer, ITEMS nSize)
{
  if(nSize>nSize1+nSize2)
    return -1;
  memcpy(pData1,pBuffer,(nSize>nSize1?nSize1:nSize)*sizeof(T));
  if(nSize>nSize1)
    memcpy(pData2,pBuffer+nSize1,(nSize-nSize1)*sizeof(T));
  return nSize;
}

template <class T, class ITEMS> inline
ITEMS YCyclicData<T,ITEMS>::GetSparseDataSize(ITEMS nSize, int nNumChannels, int nChannel)
{
  ASSERT(nChannel>=0 && nChannel<nNumChannels); return (nSize-nChannel+(nNumChannels-1))/nNumChannels;
}

template <class T, class ITEMS> inline //packet aligned data in pData1(nSize1)+pData2(nSize2) needed
ITEMS  YCyclicData<T,ITEMS>::GetSparseData(T* pBuffer, ITEMS nSize, int nNumChannels, int nChannel) const
{
  if(GetSparseDataSize(nSize1+nSize2, nNumChannels, nChannel) > nSize)
    return -1;
  ITEMS j = 0;
  for(ITEMS i=nChannel; j<nSize && i<nSize1;        i+=nNumChannels)
    pBuffer[j++] = pData1[i];
  for(              ; j<nSize && i<nSize1+nSize2; i+=nNumChannels)
    pBuffer[j++] = pData2[i-nSize1];
  return GetSparseDataSize(nSize1+nSize2, nNumChannels, nChannel);
}

template <class T, class ITEMS> inline //packet aligned data in pData1(nSize1)+pData2(nSize2) needed
ITEMS YCyclicData<T,ITEMS>::SetSparseData(const T* pBuffer, ITEMS nSize, int nNumChannels, int nChannel)
{
  if(nSize > GetSparseDataSize(nSize1+nSize2, nNumChannels, nChannel))
    return -1;
  ITEMS j = 0;
  for(ITEMS i=nChannel; j<nSize && i<nSize1;        i+=nNumChannels)
    pData1[i] = pBuffer[j++];
  for(              ; j<nSize && i<nSize1+nSize2; i+=nNumChannels)
    pData2[i-nSize1] = pBuffer[j++];
  return nSize;
}

template <class T, class ITEMS> inline //packet aligned data in pData1(nSize1)+pData2(nSize2) needed
ITEMS  YCyclicData<T,ITEMS>::GetSparseDataSparseBufferSize(
  int nBufferNumChannels, int nBufferChannel, 
  ITEMS nSize, int nNumChannels, int nChannel)
{
  ASSERT(nBufferChannel>=0 && nBufferChannel<nBufferNumChannels); 
  int nChannelSize = GetSparseDataSize(nSize, nNumChannels, nChannel);
  if(nChannelSize==0)
    return 0;
  return nChannelSize*nBufferNumChannels-nBufferNumChannels+nBufferChannel+1;
}

template <class T, class ITEMS> inline //packet aligned data in pData1(nSize1)+pData2(nSize2) needed
ITEMS  YCyclicData<T,ITEMS>::GetSparseDataToSparseBuffer(
  T* pBuffer, ITEMS nSize, int nBufferNumChannels, int nBufferChannel,
  int nNumChannels, int nChannel) const
{
  ITEMS nBufferSize = GetSparseDataSparseBufferSize(
                      nBufferNumChannels, nBufferChannel, 
                      nSize1+nSize2, nNumChannels, nChannel);
  if(nBufferSize > nSize)
    return -1;
  ITEMS j = nBufferChannel;
  for(ITEMS i=nChannel; j<nSize && i<nSize1;        i+=nNumChannels)
    { pBuffer[j] = pData1[i]; j+=nBufferNumChannels; }
  for(              ; j<nSize && i<nSize1+nSize2; i+=nNumChannels)
    { pBuffer[j] = pData2[i-nSize1]; j+=nBufferNumChannels; }
  return nBufferSize;
}

template <class T, class ITEMS> inline //packet aligned data in pData1(nSize1)+pData2(nSize2) needed
ITEMS  YCyclicData<T,ITEMS>::SetSparseDataToSparseBuffer(
  const T* pBuffer, ITEMS nSize, int nBufferNumChannels, int nBufferChannel, 
  int nNumChannels, int nChannel)
{
  ITEMS nBufferSize = GetSparseDataSparseBufferSize(
                      nBufferNumChannels, nBufferChannel, 
                      nSize1+nSize2, nNumChannels, nChannel);
  if(nSize > nBufferSize)
    return -1;

  ITEMS j = nBufferChannel;
  for(ITEMS i=nChannel; j<nSize && i<nSize1;        i+=nNumChannels)
    { pData1[i] = pBuffer[j]; j+=nBufferNumChannels; }
  for(              ; j<nSize && i<nSize1+nSize2; i+=nNumChannels)
    { pData2[i-nSize1] = pBuffer[j]; j+=nBufferNumChannels; }

  return nSize;
}

template <class T, class ITEMS> inline //packet aligned data in pData1(nSize1)+pData2(nSize2) needed
ITEMS YCyclicData<T,ITEMS>::GetSparseDataToSparseData(
  YCyclicData<T,ITEMS>* pData, ITEMS nDataNumChannels, ITEMS nDataChannel, 
  int nNumChannels, int nChannel) const
{
  ITEMS nDataSize = GetSparseDataSparseBufferSize(
                    nDataNumChannels, nDataChannel, 
                    nSize1+nSize2, nNumChannels, nChannel);
  if(nDataSize > pData->nSize1+pData->nSize2)
    return -1;

  ITEMS nSourceSize1 = GetSparseDataSparseBufferSize(
                       nNumChannels, nNumChannels-1, 
                       pData->nSize1, nDataNumChannels, nDataChannel);
  ITEMS nSourceSize2 = GetSparseDataSparseBufferSize(
                       nNumChannels, nNumChannels-1, 
                       pData->nSize2, nDataNumChannels, nDataChannel);
  ASSERT(nSourceSize1+nSourceSize2<=nSize1+nSize2);

  YCyclicData<T,ITEMS> dataSource1;
  YCyclicData<T,ITEMS> dataSource2;

  if(nSourceSize1 <= nSize1){
    dataSource1.nSize1 = nSourceSize1;
    dataSource1.pData1 = pData1;
    dataSource1.nSize2 = 0;
    dataSource1.pData2 = NULL;

    dataSource2.nSize1 = nSize1 - nSourceSize1;
    dataSource2.pData1 = pData1 + nSourceSize1;
    dataSource2.nSize2 = nSize2;
    dataSource2.pData2 = pData2;

  }else{//nSourceSize1 > nSize1
    dataSource1.nSize1 = nSize1;
    dataSource1.pData1 = pData1;
    dataSource1.nSize2 = nSourceSize1 - nSize1;
    dataSource1.pData2 = pData2;

    dataSource2.nSize1 = nSourceSize2;
    dataSource2.pData1 = pData2 + nSourceSize1 - nSize1;
    dataSource2.nSize2 = 0;
    dataSource2.pData2 = NULL;
  }

  ITEMS iSize1 = dataSource1.GetSparseDataToSparseBuffer(
                 pData->pData1,pData->nSize1,nDataNumChannels,nDataChannel,
                 nNumChannels,nChannel); 
  ITEMS iSize2 = dataSource2.GetSparseDataToSparseBuffer(
                 pData->pData2,pData->nSize2,nDataNumChannels,nDataChannel,
                 nNumChannels,nChannel); 
  ASSERT(iSize1>=0 && iSize2>=0);
  return nDataSize;
}

template <class T, class ITEMS> inline //packet aligned data in pData1(nSize1)+pData2(nSize2) needed
ITEMS YCyclicData<T,ITEMS>::SetSparseDataToSparseData(
  const YCyclicData<T,ITEMS>* pData, ITEMS nDataNumChannels, ITEMS nDataChannel, 
  int nNumChannels, int nChannel)
{
  ITEMS nDataSize = GetSparseDataSparseBufferSize(
                    nDataNumChannels, nDataChannel, 
                    nSize1+nSize2, nNumChannels, nChannel);
  if(pData->nSize1+pData->nSize2 > nDataSize)
    return -1;

  ITEMS nSourceSize1 = GetSparseDataSparseBufferSize(
                       nNumChannels, nNumChannels-1, 
                       pData->nSize1, nDataNumChannels, nDataChannel);
  ITEMS nSourceSize2 = GetSparseDataSparseBufferSize(
                       nNumChannels, nNumChannels-1, 
                       pData->nSize2, nDataNumChannels, nDataChannel);
  ASSERT(nSourceSize1+nSourceSize2<=nSize1+nSize2);

  YCyclicData<T,ITEMS> dataSource1;
  YCyclicData<T,ITEMS> dataSource2;

  if(nSourceSize1 <= nSize1){
    dataSource1.nSize1 = nSourceSize1;
    dataSource1.pData1 = pData1;
    dataSource1.nSize2 = 0;
    dataSource1.pData2 = NULL;

    dataSource2.nSize1 = nSize1 - nSourceSize1;
    dataSource2.pData1 = pData1 + nSourceSize1;
    dataSource2.nSize2 = nSize2;
    dataSource2.pData2 = pData2;

  }else{//nSourceSize1 > nSize1
    dataSource1.nSize1 = nSize1;
    dataSource1.pData1 = pData1;
    dataSource1.nSize2 = nSourceSize1 - nSize1;
    dataSource1.pData2 = pData2;

    dataSource2.nSize1 = nSourceSize2;
    dataSource2.pData1 = pData2 + nSourceSize1 - nSize1;
    dataSource2.nSize2 = 0;
    dataSource2.pData2 = NULL;
  }

  ITEMS iSize1 = dataSource1.SetSparseDataToSparseBuffer(
                 pData->pData1,pData->nSize1,nDataNumChannels,nDataChannel,
                 nNumChannels,nChannel); 
  ITEMS iSize2 = dataSource2.SetSparseDataToSparseBuffer(
                 pData->pData2,pData->nSize2,nDataNumChannels,nDataChannel,
                 nNumChannels,nChannel); 
  ASSERT(iSize1>=0 && iSize2>=0);

  return pData->nSize1+pData->nSize2;
}

template <class T, class ITEMS> inline ITEMS 
YCyclicData<T,ITEMS>::GetSize() const
{
  return (pData1==NULL?0:nSize1) + (pData2==NULL?0:nSize2);
}

template <class T, class ITEMS> inline BOOL  
YCyclicData<T,ITEMS>::Verify() const
{
  BOOL bOk0 = (pData2==NULL || pData1!=NULL);
  BOOL bOk1 = (pData1!=NULL || nSize1==0);
  BOOL bOk2 = (pData2!=NULL || nSize2==0);
  BOOL bOk3 = pData1==NULL||pData2==NULL||((pData1<pData2 || (pData1==pData2&&nSize1==0)) || pData1>=pData2+nSize2);
  BOOL bOk4 = pData1==NULL||pData2==NULL||((pData2<pData1 || (pData2==pData1&&nSize2==0)) || pData2>=pData1+nSize1);
  ASSERT(bOk0 && bOk1 && bOk2 && bOk3 && bOk4);
  return bOk0 && bOk1 && bOk2 && bOk3 && bOk4;
}

template <class T, class ITEMS> inline ITEMS 
YCyclicData<T,ITEMS>::Truncate(ITEMS nSize)
{
  ASSERT(Verify());
  ASSERT(nSize>=0);
  ITEMS nDelta = GetSize() - nSize;
  if(nDelta<=0)
    return nDelta;//negative on error!
  if(nDelta>=nSize2)
    nSize1-=nDelta-nSize2, pData2-=nDelta-nSize2, nSize2 = 0;
  else
    nSize2-=nDelta; 
  return nDelta;
}

template <class T, class ITEMS> inline ITEMS 
YCyclicData<T,ITEMS>::Displace(ITEMS nSize)
{
  ASSERT(Verify());
  ASSERT(nSize>=0);
  ITEMS nDelta = GetSize() - nSize;
  if(nDelta<=0)
    return nDelta;//negative on error!
  if(nDelta>=nSize1)
    nSize2-=nDelta-nSize1, pData2+=nDelta-nSize1, pData1+=nSize1, nSize1=0;
  else
    nSize1-=nDelta; pData1+=nDelta;
  return nDelta;
}

template <class T, class ITEMS> inline
T& YCyclicData<T,ITEMS>::operator[](ITEMS i) const
{ 
  ASSERT(Verify());
  static T item; //Needed defaut constructor or overloading this function!
  if(i>=GetSize())
    { ASSERT(i<GetSize()); return item; }
  if(i<nSize1)
    return pData1[i];
  return pData2[i-nSize1];
}


#ifdef _DEBUG
template <class T, class ITEMS> inline int
YCyclicData<T,ITEMS>::DumpElement(const T* e)
{
  switch(sizeof(T)) {
    default:
      if(e!=NULL)
        for(unsigned i=0; i<sizeof(T); ++i)
          TRACE("%2.2X",(unsigned) *(const BYTE*)(const void*)e);
      else
        for(unsigned i=0; i<sizeof(T); ++i)
          TRACE("-");
    break;
    case 1:  e!=NULL? TRACE("%2.2X",(unsigned)*(const BYTE *)e) : TRACE("--");break;
    case 2:  e!=NULL? TRACE("%4.4X",(unsigned)*(const WORD *)e) : TRACE("----");break;
    case 4:  e!=NULL? TRACE("%8.8X",(unsigned)*(const DWORD*)e) : TRACE("---------");break;
    case 8:  e!=NULL? TRACE("%16.16I64X",     *(const QWORD*)e) : TRACE("-----------------");break;
  }
  return 0;
}
template <class T, class ITEMS> inline
int YCyclicData<T,ITEMS>::Dump() const
{
  //if(GetSize())
  unsigned long ulData1 = (unsigned long)pData1;
  unsigned long ulData2 = (unsigned long)pData2;
  unsigned long ulAlign = sizeof(T)*16;//16items
  //Data:  1234=234+1000 items, 4567=567+4000 bytes at 8000000A, 81000004
  //80000000: -- -- -- -- -- -- -- -- -- -- -- -- -- -- AB CD EF 01 23 45
  //80000010: 67 89 
  //81000000: -- -- AB CD EF -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
  TRACE("Data: %u=%u+%u items, %u=%u+%u bytes at %8.8X",
    (unsigned)(nSize1+nSize2),(unsigned)nSize1,(unsigned)nSize2,
    sizeof(T)*(nSize1+nSize2),sizeof(T)*(nSize1),sizeof(T)*(nSize2),
    pData1
  ); 
  if(pData2!=0)
    TRACE(",%8.8X",pData2);
  TRACE("\n");

  if(pData1!=NULL) {
    const T* pBeg = (const T*) (ulData1 - ulData1%ulAlign);
    const T* pEnd = (const T*) (pData1 + nSize1);
    for(int i=0; pBeg<pEnd; i++, pBeg++){
      if(i%16==0 && i!=0)
        TRACE("\n");
      if(i%16==0)
        TRACE("%8.8X:",pBeg);
      if(i%8==0 && i%16!=0)
        TRACE(" ");//additional space at center
      if(pBeg>=pData1)
        { TRACE(" "); DumpElement(pBeg); }
      else
        { TRACE(" "); DumpElement(NULL); }
      if(i%96==0 && i>0)
        ::Sleep(100);
    }
    if(i!=0)
      TRACE("\n");
  }

  if(pData2!=NULL) {
    const T* pBeg = (const T*) (ulData2 - ulData2%ulAlign);
    const T* pEnd = (const T*) (pData2 + nSize2);
    for(int i=0; pBeg<pEnd; i++, pBeg++){
      if(i%16==0 && i!=0)
        TRACE("\n");
      if(i%16==0)
        TRACE("%8.8X:",pBeg);
      if(i%8==0 && i%16!=0)
        TRACE(" ");//additional space at center
      if(pBeg>=pData1)
        { TRACE(" "); DumpElement(pBeg); }
      else
        { TRACE(" "); DumpElement(NULL); }
      if(i%96==0 && i>0)
        ::Sleep(100);
    }
    if(i!=0)
      TRACE("\n");
  }
  return 0;
}
#endif

///////////////////////////////////////////////////////////////////////////////////////
// YCacheData inline implementation

template <class T, class ITEMS> inline BOOL YCacheData<T,ITEMS>::
IsPlain() const
{
  return (pData2==NULL && nSize2==0);
}

template <class T, class ITEMS> inline BOOL YCacheData<T,ITEMS>::
IsCycle() const
{
  return (pData2!=NULL && nSize2>0 && pData1!=NULL && nSize1>0 && pData1>pData2);
}

template <class T, class ITEMS> inline BOOL YCacheData<T,ITEMS>::
IsSparse() const
{
  return (pData2!=NULL && nSize2>0 && pData1!=NULL && nSize1>0 && pData1<pData2);
}

template <class T, class ITEMS> inline int  YCacheData<T,ITEMS>::
Plain(T* pBuffer, ITEMS nSize, ITEMS nTile/*nSize*/)//with data copy
{
  ASSERT(pData1==NULL || (pData1>=pBuffer && pData1+nSize1<=pBuffer+nSize+nTile));
  ASSERT(pData2==NULL || (pData2>=pBuffer && pData2+nSize2<=pBuffer+nSize+nTile));
  nTile = (nTile<0?nSize:nTile);

  T* pTile = pBuffer+nSize;
  T* pEnd1 = pData1+nSize1;
  if      (IsCycle()){
    if(nSize2>nTile)
      return -1;
    memcpy(pTile,pData2,nSize2*sizeof(T));
    nSize1 += nSize2;
    pData2 = NULL;
    nSize2 = 0;
  }else if(IsSparse() && pEnd==pData2){
    nSize1 += nSize2;
    pData2 = NULL;
    nSize2 = 0;
  }else if(!IsPlain()){
    ASSERT(0); 
    return -1;
  }
  return nSize1;
}

template <class T, class ITEMS> inline int YCacheData<T,ITEMS>::
Cycle(T* pBuffer, ITEMS nSize, ITEMS nTile/*nSize*/)//with data copy
{
  ASSERT(pData1==NULL || (pData1>=pBuffer && pData1+nSize1<=pBuffer+nSize+nTile));
  ASSERT(pData2==NULL || (pData2>=pBuffer && pData2+nSize2<=pBuffer+nSize+nTile));
  nTile = (nTile<0?nSize:nTile);

  T* pTile = pBuffer+nSize;
  T* pEnd1 = pData1+nSize1;
  if(!IsPlain()){
    ASSERT(0); 
    return -1;
  }
  if(pEnd1>pTile){
    if(pEnd1-pTile>pData1-pBuffer)
      return -1;
    memcpy(pBuffer,pTile,(pEnd1-pTile)*sizeof(T));
    nSize1 -= (pEnd1-pTile);
    pData2 = pBuffer;
    nSize2 = (pEnd1-pTile);
  }
  return nSize1+nSize2;
}

template <class T, class ITEMS> inline int YCacheData<T,ITEMS>::
Plain(const T* pBuffer, ITEMS nSize, ITEMS nTile/*nSize*/)
{
  ASSERT(pData1==NULL || (pData1>=pBuffer && pData1+nSize1<=pBuffer+nSize+nTile));
  ASSERT(pData2==NULL || (pData2>=pBuffer && pData2+nSize2<=pBuffer+nSize+nTile));
  nTile = (nTile<0?nSize:nTile);

  const T* pTile = pBuffer+nSize;
  T* pEnd1 = pData1+nSize1;
  if      (IsCycle()){
    if(nSize2>nTile)
      return -1;
    nSize1 += nSize2;
    pData2 = NULL;
    nSize2 = 0;
  }else if(IsSparse() && pEnd1==pData2){
    nSize1 += nSize2;
    pData2 = NULL;
    nSize2 = 0;
  }else if(!IsPlain()){
    ASSERT(0); 
    return -1;
  }
  return nSize1;
}

template <class T, class ITEMS> inline int YCacheData<T,ITEMS>::
Cycle(const T* pBuffer, ITEMS nSize, ITEMS nTile/*nSize*/)
{
  ASSERT(pData1==NULL || (pData1>=pBuffer && pData1+nSize1<=pBuffer+nSize+nTile));
  ASSERT(pData2==NULL || (pData2>=pBuffer && pData2+nSize2<=pBuffer+nSize+nTile));
  nTile = (nTile<0?nSize:nTile);

  const T* pTile = pBuffer+nSize;
  T* pEnd1 = pData1+nSize1;
  if(!IsPlain()){
    ASSERT(0); 
    return -1;
  }
  if(pEnd1>pTile){
    if(pEnd1-pTile>pData1-pBuffer)
      return -1;
    nSize1 -= (pEnd1-pTile);
    pData2 = pBuffer;
    nSize2 = (pEnd1-pTile);
  }
  return nSize1+nSize2;
}

template <class T, class ITEMS> inline YCacheData<T,ITEMS>::
operator const T*() const//NULL and assert in cycle state
{
  ASSERT(IsPlain());
  if(!IsPlain())
    return NULL;
  return pData1;
}

template <class T, class ITEMS> inline YCacheData<T,ITEMS>::
operator T*()            //NULL and assert in cycle state
{
  ASSERT(IsPlain());
  if(!IsPlain())
    return NULL;
  return pData1;
}

///////////////////////////////////////////////////////////////////////////////////////
// YCodedData inline implementation
template <class T, class ITEMS> inline ITEMS YCodedData<T,ITEMS>::
GetData(YCyclicData<T,ITEMS>* pData) const
{
  YCyclicData<T,ITEMS> data = *pData;
  const void* pCoded = this->pData;
  if(!! decode(data.pData1,pCoded,data.nSize1) )              //AY 20.02.2008 OLD: !decode
    return -1;
  if(!! decode(data.pData2,pCoded,data.nSize2, data.nSize1) ) //AY 20.02.2008 OLD: !decode
    return -1;
  return data.nSize1+data.nSize2;
}

template <class T, class ITEMS> inline ITEMS YCodedData<T,ITEMS>::
GetData(T* pBuffer, ITEMS nSize) const
{
  const void* pCoded = this->pData;
  return decode(pBuffer, pCoded, nSize);
}

template <class T, class ITEMS> inline ITEMS YCodedData<T,ITEMS>::
SetData(const YCyclicData<T,ITEMS>* pData)
{
  const YCyclicData<T,ITEMS> data = *pData;
  void* pCoded = this->pData;
  if(! encode(pCoded,data.pData1,data.nSize1) )
    return -1;
  if(! encode(pCoded,data.pData2,data.nSize2, data.nSize1) )
    return -1;
  return data.nSize1+data.nSize2;
}

template <class T, class ITEMS> inline ITEMS YCodedData<T,ITEMS>::
SetData(const T* pBuffer, ITEMS nSize)
{
  void* pCoded = this->pData;
  return encode(pCoded, pBuffer, nSize);
}

template <class T, class ITEMS> inline ITEMS YCodedData<T,ITEMS>::
GetSize() const
{
  return this->nSize/sizeof(T);
}

template <class T, class ITEMS> inline int   YCodedData<T,ITEMS>::
decode(T* pBuffer, const void* pCoded, ITEMS nSize, ITEMS nOffs) const
{
  if((nSize+nOffs)*sizeof(T)>this->nSize)
    return -1;
  memcpy(pBuffer,reinterpret_cast<const BYTE*>(pCoded)+nOffs*sizeof(T),nSize*sizeof(T));
  return 0;
}

template <class T, class ITEMS> inline int   YCodedData<T,ITEMS>::
encode(void* pCoded, const T* pBuffer, ITEMS nSize, ITEMS nOffs)
{
  if((nSize+nOffs)*sizeof(T)>this->nSize)
    return -1;
  memcpy(reinterpret_cast<BYTE*>(pCoded)+nOffs*sizeof(T),pBuffer,nSize*sizeof(T));
  return 0;
}

///////////////////////////////////////////////////////////////////////////
// YCodedData <-> YCyclicData

template <class T, class ITEMS> inline //packet aligned data in pData1(nSize1)+pData2(nSize2) needed
ITEMS YCyclicData<T,ITEMS>::GetData(YCodedData<T,ITEMS>* pCoded) const
{
  return pCoded->SetData(this);
}

template <class T, class ITEMS> inline //packet aligned data in pData1(nSize1)+pData2(nSize2) needed
ITEMS YCyclicData<T,ITEMS>::SetData(const YCodedData<T,ITEMS>* pCoded)
{
  return pCoded->GetData(this);
}

// types //////////////////////////////////////////////////////////////////
typedef YCyclicData<char> YCyclicCharData;
typedef YCyclicData<unsigned char> YCyclicUCharData;
typedef YCyclicData<int> YCyclicIntData;
typedef YCyclicData<unsigned int> YCyclicUIntData;
typedef YCyclicData<long> YCyclicLongData;
typedef YCyclicData<unsigned long> YCyclicULongData;
typedef YCyclicData<float> YCyclicFloatData;
typedef YCyclicData<double> YCyclicDoubleData;
typedef YCyclicData<long double> YCyclicLDoubleData;

typedef YCyclicData<unsigned char, unsigned long> YCyclicVoidData;//byte array

#endif//__YDATA_H
#pragma once
