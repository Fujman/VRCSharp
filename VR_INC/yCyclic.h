#ifndef __YCYCLIC_H
#define __YCYCLIC_H

#include "yPos.h"
#include "yData.h"
#include "yArray.h"

///////////////////////////////////////////////////////////////////////////////////////
// YCyclicBuffer (multithread prepared)
template <class T>
class YCyclicBuffer: public YStaticArray<T>
{
protected://multithread access to this class members allowed//
  volatile YPos m_qBeg, m_qEnd;
public:   //multithread OS and compiler dependent protection//
  static YPos GetSafePos(const volatile YPos& qPos)//spin locking used!
    { for(YPos q=qPos; q!=qPos; q=qPos) ::Sleep(0); return q; }
  static YPos SetSafePos(volatile YPos& qPos, YPos qVal)
    { return qPos = qVal; } //must be very quick!
public:                                                                //types::
  typedef YCyclicData<T> YData;
  typedef YCodedData<T> YCoded;
public:                                             //construction/destruction::
  YCyclicBuffer(int nSize, void* p=NULL) : YStaticArray<T>((size_t)nSize, p)
          { m_qEnd=m_qBeg=0; }
  ~YCyclicBuffer() 
          {}
  YCyclicBuffer() : YStaticArray<T>()
          { m_qEnd=m_qBeg=0; }

  void* Create(int nSize, void* p=NULL)      //throw CMemoryException on error
          { Reset(); return YStaticArray<T>::Create(nSize, p); }
  void* Clear()
          { Reset(); return YStaticArray<T>::Clear(); }
  int   Empty()
          { YPos qEnd=GetEnd(); return Reset(qEnd,qEnd); }
  int   Reset(YPos qBeg=0, YPos qEnd=0)
          { ASSERT(qEnd>=qBeg); SetSafePos(m_qBeg,qBeg); SetSafePos(m_qEnd,qEnd); return 0; }
  int   InitBounds(YPos qBeg, int nSize)
          { return Reset(qBeg,qBeg+nSize); }
public:                                                           //attributes::
//int   GetBufferSize();//*inherited*//bytes

  int   GetArraySize() const
          { return YStaticArray<T>::GetSize(); }
  int   GetSize() const
          { return (int)(GetEnd()-GetBeg()); }
  int   isEmpty() const
          { return GetSize()==0; }
  int   isCycle() const
          { return GetEnd()>GetArraySize(); }
public:
  YPos  GetBeg() const //note:  always GetEnd()<=GetBeg() must be satified
          { return GetSafePos(m_qBeg); }
  YPos  GetEnd() const //note:  always GetEnd()<=GetBeg() must be satified
          { return GetSafePos(m_qEnd); }
public:
  YPos  GetHeadPos() const
        { return GetBeg(); }
  YPos  GetTailPos() const
        { return GetEnd(); }
public:                                                           //operations::
  YPos  PrepareAddTailData(const YCoded* pCoded, YData* pPlace=NULL);//0-success, -1-error //must be owner thread called only
  YPos  AddTailData       (const YCoded* pCoded, YData* pPlace=NULL);//0-success, -1-error //must be owner thread called only
  YPos  PrepareAddTailData(const T* pData, int nSize, YData* pPlace=NULL);//0-success, -1-error //must be owner thread called only
  YPos  AddTailData       (const T* pData, int nSize, YData* pPlace=NULL);//0-success, -1-error //must be owner thread called only
  YPos  RemoveHeadData(YPos qBeg, YPos qEnd);                        //must be owner thread called only

  YPos  PrepareAddHeadData(const YCoded* pCoded, YData* pPlace=NULL);//0-success, -1-error //must be owner thread called only
  YPos  AddHeadData       (const YCoded* pCoded, YData* pPlace=NULL);//0-success, -1-error //must be owner thread called only
  YPos  PrepareAddHeadData(const T* pData, int nSize, YData* pPlace=NULL);//0-success, -1-error //must be owner thread called only
  YPos  AddHeadData       (const T* pData, int nSize, YData* pPlace=NULL);//0-success, -1-error //must be owner thread called only
  YPos  RemoveTailData(YPos qBeg, YPos qEnd);                        //must be owner thread called only

  int   RawData(YPos qBeg, YPos qEnd, T* pData, int nSize) const;//>=0-success
  int   GetData(YPos qBeg, YPos qEnd, T* pData, int nSize) const;//>=0-success,-1-lost
  int   SetData(YPos qBeg, YPos qEnd, const T* pData, int nSize);//>=0-success,-1-data destroyed during writting

  int   GetSparseData(YPos qBeg, YPos qEnd, T* pData, int nSize, int nNumChannels, int nChannel) const;//>=0-success,-1-lost
  int   SetSparseData(YPos qBeg, YPos qEnd, const T* pData, int nSize, int nNumChannels, int nChannel);//>=0-success,-1-lost
  int   GetSparseDataSize(YPos qBeg, YPos qEnd, int nNumChannels, int nChannel) const; //bytes
public:                                                              //helpers::
  BOOL  IsDataChanged(YPos qBeg, YPos qEnd) const
          { return qEnd!=GetEnd() || qBeg!=GetBeg(); }//m_qBeg must be obtained last! It will be changed first in AddData.
  BOOL  IsDataExists(YPos qBeg, YPos qEnd) const
          { return qBeg<=qEnd && qEnd<=GetEnd() && qBeg>=GetBeg(); }//m_qBeg must be obtained last! It will be changed first in AddData.
  T*    GetDataOffset(YPos q) const
          { return ((T*)ptr) + (q % GetArraySize()); }
  int   GetDataSize(YPos qBeg, YPos qEnd) const //items //changed by AY 14.12.2002
          { ASSERT((qEnd-qBeg)==(YPos)(int)(qEnd-qBeg)); return (int)(qEnd-qBeg); }
  int   GetDataPlace(YPos qBeg, YPos qEnd, YData& data) const;
  int   GetVoidPlace(int nSize, YData& data) const;
public:                                                            //operators::
        operator const T*() const
          { return (const T*)GetDataOffset(GetBeg()); }//AY 16.05.2003 { return ((const T*)ptr)+GetDataOffset(GetBeg()); }
        operator T*()
          { return (T*)GetDataOffset(GetBeg()); }    //AY 16.05.2003 { return ((T*)ptr) + GetDataOffset(GetBeg()); }

        const T& operator [](int i) const
          { YMEMORY_ASSERT(i>=0 && i<GetSize()); return *( GetDataOffset(GetBeg()+i) ); }
        T& operator [](int i)
          { YMEMORY_ASSERT(i>=0 && i<GetSize()); return *( GetDataOffset(GetBeg()+i) ); }

#ifdef _DEBUG
  int   Dump();
#else
  int   Dump(){}
#endif
public:                                                             //macroses::
  static YPos ITEMS(YPos cbPos) { YMEMORY_ASSERT(cbPos%sizeof(T)==0); return cbPos/sizeof(T); }
  static YPos BYTES(YPos qPos)  { return qPos*sizeof(T); }
};

// YCyclicBuffer implementation //////////////////////////////////////////////////////

template <class T> inline int YCyclicBuffer<T>::
GetDataPlace(YPos qBeg, YPos qEnd, YData& data) const //>=0-success,-1-lost
{
  ASSERT((qEnd-qBeg)==(int)(qEnd-qBeg));
  int nArraySize = GetArraySize();
  data.pData1 = nArraySize?GetDataOffset(qBeg):NULL;
  T* pDataEnd = nArraySize?GetDataOffset(qEnd):NULL;
  int nSize = GetDataSize(qBeg,qEnd);
  if(nSize>nArraySize)
    return -1;

  if(nSize==0)
    { data.pData2=NULL; data.nSize1=data.nSize2=0; return 0; }
  if(pDataEnd>data.pData1)// case ========--
    { data.pData2=NULL; data.nSize2=0; data.nSize1=nSize; }
  else                    // case ===----===
    { data.pData2=GetDataOffset(0); data.nSize2=pDataEnd-data.pData2; data.nSize1=nSize-data.nSize2; }

  if(data.pData2!=NULL && data.nSize2==0) //AY 22.05.2003
    { data.pData2=NULL; }

  ASSERT(data.nSize2<nSize);//AY15.04.2003 error?!
  ASSERT(data.nSize1>0    );//AY15.04.2003 error?!
  return nSize;
}

template <class T> inline int YCyclicBuffer<T>::
GetVoidPlace(int nSize, YData& data) const
{// must be called in locked state
  ASSERT(nSize>=0);
  YPos qStart = GetSafePos(m_qEnd);
  YPos qFinis = qStart + nSize;
  data.pData1 = GetDataOffset(qStart);
  T* pDataEnd = GetDataOffset(qFinis);
  int nFree = GetArraySize()-GetSize();
  if(nSize>nFree)
    return -1;

  if(nSize==0)
    { data.pData2=NULL; data.nSize1=data.nSize2=0; return 0; }
  if(pDataEnd<data.pData1)// case -=======--
    { data.pData2=GetDataOffset(0); data.nSize2=pDataEnd-data.pData2; data.nSize1=nSize-data.nSize2; }
  else                    // case ===----===
    { data.pData2=NULL; data.nSize2=0; data.nSize1=nSize; }

  if(data.pData2!=NULL && data.nSize2==0) //AY 22.05.2003
    { data.pData2=NULL; }

  ASSERT(data.nSize2<nSize);//AY15.04.2003 error?!
  ASSERT(data.nSize1>0    );//AY15.04.2003 error?!
  return nSize;
}

template <class T> inline int YCyclicBuffer<T>::
RawData(YPos qBeg, YPos qEnd, T* pData, int nSize) const//>=0-success
{ 
  YCyclicData<T> data;
  if(GetDataPlace(qBeg,qEnd,data)<0)
    return -1;
  if( (nSize=data.GetData(pData,nSize) )<0) //copy data
    return -1;
  return nSize;
}

template <class T> inline int YCyclicBuffer<T>::
GetData(YPos qBeg, YPos qEnd, T* pData, int nSize) const//>=0-success,-1-lost
{ 
  YCyclicData<T> data;
  if(GetDataPlace(qBeg,qEnd,data)<0)
    return -1;
  if(!IsDataExists(qBeg,qEnd))  //first check
    return -1;//error
  if( (nSize=data.GetData(pData,nSize) )<0) //copy data
    return -1;
  if(!IsDataExists(qBeg,qEnd))  //second check: failure if another thread destroy data
    return -1;//error
  return nSize;
}

template <class T> inline int YCyclicBuffer<T>::
SetData(YPos qBeg, YPos qEnd, const T* pData, int nSize)//>=0-success,-1-lost
{ 
  YCyclicData<T> data;
  if(GetDataPlace(qBeg,qEnd,data)<0)
    return -1; 
  if(!IsDataExists(qBeg,qEnd))  //first check
    return -1;//error
  if( (nSize=data.SetData(pData,nSize) )<0) //copy data
    return -1;
  if(!IsDataExists(qBeg,qEnd))  //second check: failure if another thread destroy data
    return -1;//error
  return nSize;
}

template <class T> inline YPos YCyclicBuffer<T>::
PrepareAddTailData(const T* pData, int nSize, YData* pPlace)//0-success, -1-error //must be owner thread called only
{
  if(nSize>GetArraySize())
    return m_qBeg;//error: m_qBeg is not changed
  YCyclicData<T>  data={0};
  YPos qEnd = GetEnd();
  YPos qBeg = GetBeg();//must later then qEnd

  if(GetDataPlace(qEnd,qEnd+nSize,data)<0)
    return m_qBeg;//error: m_qBeg is not changed

  int nDataSize = GetDataSize(qBeg,qEnd);
  int nFreeSize = GetArraySize()-nDataSize;
  if(nFreeSize<nSize)
    RemoveHeadData(qBeg,qBeg+nSize-nFreeSize);

  if(pData!=NULL)
    data.SetData(pData,nSize); //copy data

  if(pPlace)
    *pPlace = data;

  return m_qBeg;
}


template <class T> inline YPos YCyclicBuffer<T>::
AddTailData(const T* pData, int nSize, YData* pPlace)//0-success, -1-error //must be owner thread called only
{
  if(nSize>GetArraySize())
    return -1;
  YCyclicData<T>  data={0};
  YPos qEnd = GetEnd();
  YPos qBeg = GetBeg();//must later then qEnd

  if(GetDataPlace(qEnd,qEnd+nSize,data)<0)
    return -1;

  int nDataSize = GetDataSize(qBeg,qEnd);
  int nFreeSize = GetArraySize()-nDataSize;
  if(nFreeSize<nSize)
    RemoveHeadData(qBeg,qBeg+nSize-nFreeSize);

  if(pData!=NULL)
    data.SetData(pData,nSize); //copy data

  if(pPlace)
    *pPlace = data;

  return m_qEnd += nSize;
}

template <class T> inline YPos YCyclicBuffer<T>::
PrepareAddTailData(const YCoded* pCoded, YData* pPlace)//0-success, -1-error //must be owner thread called only
{
  int nSize = pCoded->GetSize();
  if(nSize>GetArraySize())
    return m_qBeg;//error: m_qBeg is not changed
  YCyclicData<T>  data={0};
  YPos qEnd = GetEnd();
  YPos qBeg = GetBeg();//must later then qEnd

  if(GetDataPlace(qEnd,qEnd+nSize,data)<0)
    return m_qBeg;//error: m_qBeg is not changed

  int nDataSize = GetDataSize(qBeg,qEnd);
  int nFreeSize = GetArraySize()-nDataSize;
  if(nFreeSize<nSize)
    RemoveHeadData(qBeg,qBeg+nSize-nFreeSize);

  if(pCoded!=NULL)
    data.SetData(pCoded); //copy data

  if(pPlace)
    *pPlace = data;

  return m_qBeg;
}


template <class T> inline YPos YCyclicBuffer<T>::
AddTailData(const YCoded* pCoded, YData* pPlace)//0-success, -1-error //must be owner thread called only
{
  int nSize = pCoded->GetSize();
  if(nSize>GetArraySize())
    return -1;
  YCyclicData<T>  data={0};
  YPos qEnd = GetEnd();
  YPos qBeg = GetBeg();//must later then qEnd

  if(GetDataPlace(qEnd,qEnd+nSize,data)<0)
    return -1;

  ASSERT(data.nSize2==0);//AY 21.07.2007
  if(data.nSize2){//debug repeat
    GetDataPlace(qEnd,qEnd+nSize,data);
  }

  int nDataSize = GetDataSize(qBeg,qEnd);
  int nFreeSize = GetArraySize()-nDataSize;
  if(nFreeSize<nSize)
    RemoveHeadData(qBeg,qBeg+nSize-nFreeSize);

  if(pCoded!=NULL)
    data.SetData(pCoded); //copy data

  if(pPlace)
    *pPlace = data;

  return m_qEnd += nSize;
}

template <class T> inline YPos YCyclicBuffer<T>::
RemoveHeadData(YPos qBeg, YPos qEnd)//0-success, -1-error //must be owner thread called only
{
  YPos qCurEnd = GetEnd();
  YPos qCurBeg = GetBeg();//must later then qEnd
  if(qBeg>qEnd)
    return qCurBeg;//nothing to do
  if(qEnd<=qCurBeg) //case --+=====+-(--)---
    return qCurBeg;//nothing to do
  if(qBeg>=qCurEnd) //case --(-----)-+===+--
    return qCurBeg;//nothing to do

  if(qBeg>=qCurBeg && qEnd<=qCurEnd) //case --(-+=====+-)--- -> ----+=====(-)---
    return m_qBeg = qEnd;//TO DO?

  if(qBeg<qCurBeg) //case --+==(===+---)---  -> --+======(---)---
    return m_qBeg = qEnd;
  if(qEnd>qCurEnd) //case --(---+===)===+--  -> ------(===)===+-- Error? AY 15.05.2003
    return m_qBeg = qBeg; //may be           -> ------+=======()- m_qBeg=m_qEnd=qEnd
  ASSERT(0); return m_qBeg;
}

//AY 15.05.2003 ///////////////////////////

template <class T> inline YPos YCyclicBuffer<T>::
PrepareAddHeadData(const T* pData, int nSize, YData* pPlace)//0-success, -1-error //must be owner thread called only
{
  if(nSize>GetArraySize())
    return m_qEnd;//error: m_qEnd is not changed
  YCyclicData<T>  data={0};
  YPos qEnd = GetEnd();
  YPos qBeg = GetBeg();

  if(GetDataPlace(qBeg-nSize,qBeg,data)<0)
    return m_qEnd;//error: m_qEnd is not changed

  int nDataSize = GetDataSize(qBeg,qEnd);
  int nFreeSize = GetArraySize()-nDataSize;
  if(nFreeSize<nSize)
    RemoveTailData(qEnd-nSize+nFreeSize,qEnd);

  if(pData!=NULL)
    data.SetData(pData,nSize); //copy data

  if(pPlace)
    *pPlace = data;

  return m_qEnd;
}


template <class T> inline YPos YCyclicBuffer<T>::
AddHeadData(const T* pData, int nSize, YData* pPlace)//0-success, -1-error //must be owner thread called only
{
  if(nSize>GetArraySize())
    return -1;
  YCyclicData<T>  data={0};
  YPos qEnd = GetEnd();
  YPos qBeg = GetBeg();//must later then qEnd

  if(GetDataPlace(qBeg-nSize,qBeg,data)<0)
    return -1;

  int nDataSize = GetDataSize(qBeg,qEnd);
  int nFreeSize = GetArraySize()-nDataSize;
  if(nFreeSize<nSize)
    RemoveTailData(qEnd-nSize+nFreeSize,qEnd);

  if(pData!=NULL)
    data.SetData(pData,nSize); //copy data

  if(pPlace)
    *pPlace = data;

  return m_qBeg -= nSize;
}

template <class T> inline YPos YCyclicBuffer<T>::
PrepareAddHeadData(const YCoded* pCoded, YData* pPlace)//0-success, -1-error //must be owner thread called only
{
  int nSize = pCoded->GetSize();
  if(nSize>GetArraySize())
    return m_qEnd;//error: m_qEnd is not changed
  YCyclicData<T>  data={0};
  YPos qEnd = GetEnd();
  YPos qBeg = GetBeg();

  if(GetDataPlace(qBeg-nSize,qBeg,data)<0)
    return m_qEnd;//error: m_qEnd is not changed

  int nDataSize = GetDataSize(qBeg,qEnd);
  int nFreeSize = GetArraySize()-nDataSize;
  if(nFreeSize<nSize)
    RemoveTailData(qEnd-nSize+nFreeSize,qEnd);

  if(pCoded!=NULL)
    data.SetData(pCoded); //copy data

  if(pPlace)
    *pPlace = data;

  return m_qEnd;
}


template <class T> inline YPos YCyclicBuffer<T>::
AddHeadData(const YCoded* pCoded, YData* pPlace)//0-success, -1-error //must be owner thread called only
{
  int nSize = pCoded->GetSize();
  if(nSize>GetArraySize())
    return -1;
  YCyclicData<T>  data={0};
  YPos qEnd = GetEnd();
  YPos qBeg = GetBeg();//must later then qEnd

  if(GetDataPlace(qBeg-nSize,qBeg,data)<0)
    return -1;

  int nDataSize = GetDataSize(qBeg,qEnd);
  int nFreeSize = GetArraySize()-nDataSize;
  if(nFreeSize<nSize)
    RemoveTailData(qEnd-nSize+nFreeSize,qEnd);

  if(pCoded!=NULL)
    data.SetData(pCoded); //copy data

  if(pPlace)
    *pPlace = data;

  return m_qBeg -= nSize;
}

template <class T> inline YPos YCyclicBuffer<T>::
RemoveTailData(YPos qBeg, YPos qEnd)//0-success, -1-error //must be owner thread called only
{
  YPos qCurEnd = GetEnd();
  YPos qCurBeg = GetBeg();
  if(qBeg>qEnd)     //case --+=====+--------
    return qCurEnd;//nothing to do
  if(qEnd<=qCurBeg) //case --+=====+-(--)---
    return qCurEnd;//nothing to do
  if(qBeg>=qCurEnd) //case --(-----)-+===+--
    return qCurEnd;//nothing to do

  if(qBeg>=qCurBeg && qEnd<=qCurEnd) //case --(-+=====+-)--- -> --(-)=====+-----
    return m_qEnd = qBeg;//TO DO?

  if(qBeg<qCurBeg) //case --+==(===+---)---  -> --)==(===+------- ??
    return m_qEnd = qBeg;
  if(qEnd>qCurEnd) //case --(---+===)===+--  -> --(---)=======+--
    return m_qEnd = qEnd;
  ASSERT(0); return m_qEnd;
}
//YA 15.05.2003 ///////////////////////////

template <class T> inline int YCyclicBuffer<T>::
GetSparseDataSize(YPos qBeg, YPos qEnd, int nNumChannels, int nChannel) const //bytes
{
  YPos qAlignedBeg = qBeg - (qBeg%nNumChannels) + nChannel; if(qAlignedBeg<qBeg) qAlignedBeg += nNumChannels;
  int  nAlignedSize = YCyclicData<T>::GetSparseDataSize((int)(qEnd-qAlignedBeg),nNumChannels);
//YPos qAlignedEnd = qEnd - (qEnd%nNumChannels) + nChannel; if(qAlignedEnd>qEnd) qAlignedEnd -= nNumChannels;
  YPos qAlignedEnd = qAlignedBeg+nAlignedSize*nNumChannels; if(qAlignedEnd>qEnd) qAlignedEnd  = qEnd;
  return nAlignedSize;
}

template <class T> inline int YCyclicBuffer<T>::
GetSparseData(YPos qBeg, YPos qEnd, T* pData, int nSize, int nNumChannels, int nChannel) const//>=0-success,-1-lost
{
  YPos qAlignedBeg = qBeg - (qBeg%nNumChannels) + nChannel; if(qAlignedBeg<qBeg) qAlignedBeg += nNumChannels;
  int  nAlignedSize = YCyclicData<T>::GetSparseDataSize((int)(qEnd-qAlignedBeg),nNumChannels);
//YPos qAlignedEnd = qEnd - (qEnd%nNumChannels) + nChannel; if(qAlignedEnd>qEnd) qAlignedEnd -= nNumChannels;
  YPos qAlignedEnd = qAlignedBeg+nAlignedSize*nNumChannels; if(qAlignedEnd>qEnd) qAlignedEnd  = qEnd;

  YCyclicData<T> data;
  if(GetDataPlace(qAlignedBeg,qAlignedEnd,data)<0)
    return -1;
  if(!IsDataExists(qAlignedBeg,qAlignedBeg))  //first check
    return -1;//error
  if( (nSize=data.GetSparseData(pData,nSize,nNumChannels) )<0) //copy data
    return -1;
  if(!IsDataExists(qAlignedBeg,qAlignedBeg))  //second check: failure if another thread destroy data
    return -1;//error
  return nSize;//(int)((qAlignedEnd-qAlignedBeg+1)/nNumChannels);//items
}

template <class T> inline int YCyclicBuffer<T>::
SetSparseData(YPos qBeg, YPos qEnd, const T* pData, int nSize, int nNumChannels, int nChannel)//>=0-success,-1-lost
{
  YPos qAlignedBeg = qBeg - (qBeg%nNumChannels) + nChannel; if(qAlignedBeg<qBeg) qAlignedBeg += nNumChannels;
  int  nAlignedSize = YCyclicData<T>::GetSparseDataSize((int)(qEnd-qAlignedBeg),nNumChannels);
//YPos qAlignedEnd = qEnd - (qEnd%nNumChannels) + nChannel; if(qAlignedEnd>qEnd) qAlignedEnd -= nNumChannels;
  YPos qAlignedEnd = qAlignedBeg+nAlignedSize*nNumChannels; if(qAlignedEnd>qEnd) qAlignedEnd  = qEnd;

  YCyclicData<T> data;
  if(GetDataPlace(qAlignedBeg,qAlignedEnd,data)<0)
    return -1; 
  if(!IsDataExists(qAlignedBeg,qAlignedBeg))  //first check
    return -1;//error
  if( (nSize=data.SetSparseData(pData,nSize,nNumChannels) )<0) //copy data
    return -1;
  if(!IsDataExists(qAlignedBeg,qAlignedBeg))  //second check: failure if another thread destroy data
    return -1;//error
  return nSize;
}


#endif//__YCYCLIC_H
#pragma once
