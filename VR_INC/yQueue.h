#ifndef __YQUEUE_H
#define __YQUEUE_H
#include "yArray.h"

////////////////////////////////////////////////////////////////////////////////////

#ifdef INULL
  #pragma message("INULL alredy defined!");
#endif

////////////////////////////////////////////////////////////////////////////////////
// YQueue <class T, class REF_T, class YARRAY>

template <class T, class REF_T, class YARRAY>
class YQueue: public YARRAY
{
public:
  typedef YARRAY YParent; //typedef YStaticArray<T> YParent;
  enum    { INULL = -1 };
protected:
  signed        m_iHead;
  signed        m_iTail;
public:
  YQueue(int nSize, void* p=NULL)
                                : YParent(nSize, p) { m_iHead=m_iTail=INULL; }
  ~YQueue()                     {}
  YQueue()                      : YParent() { m_iHead=m_iTail=INULL; }
  void*         Create(int nSize, void* p=NULL)      //throw CMemoryException on error
                                { m_iHead=m_iTail=INULL; return YParent::Create(nSize, p); }
  void*         Clear()
                                { m_iHead=m_iTail=INULL; return YParent::Clear(); }
  int           Reset(int iHead=0, int iTail=0)
                                { return InitBounds(iHead,iTail-iHead); }
  int           Empty()
                                { return Reset(); }
  int           InitBounds(int iHead, int nLength);
  int           InitQueue(T item, int iHead=0, int nLength=0);
public:
                operator const T*() const { return ((const T*)ptr); }
                operator T*()             { return ((T*)ptr); }
  T             operator [](int i) const;
  REF_T         operator [](int i);
  T             GetHead() const;
  REF_T         GetHead();
  T             GetTail() const;
  REF_T         GetTail();
public:
  int           GetArraySize() const;
  int           GetSize() const;
  int           isEmpty() const;
  int           isCycle() const;
  int           isNormalized() const;
  int           isContinuous() const;
public:
  int           AddHead(T item, BOOL bCyclic=TRUE);
  int           AddTail(T item, BOOL bCyclic=TRUE);
  int           Add(T item);//array like
  int           RemoveHead();
  int           RemoveTail();
  int           RemoveAll();
  int           Normalize();
  int           AddHeadGrow(T item, int nMaxSize=0);
  int           AddTailGrow(T item, int nMaxSize=0);
  int           AddGrow(T item, int nMaxSize=0);//array like
#ifdef _DEBUG
  int           Dump();
#else
  int           Dump(){}
#endif
public:
  int           GetQueueIdx(signed iPos) const;//index in queue
  signed        GetArrayPos(int iIdx) const;   //index in array
  signed        GetHeadPos() const;// index in array
  signed        GetTailPos() const;// index in array
  signed        GetNextPos(signed iPos) const;
  signed        GetPrevPos(signed iPos) const;
  T             GetNext(signed& iPos) const;
  REF_T         GetNext(signed& iPos);
  T             GetPrev(signed& iPos) const;
  REF_T         GetPrev(signed& iPos);
  T             GetAt(signed& iPos) const;
  REF_T         GetAt(signed& iPos);
};

// IMPLEMENTATION //////////////////////////////////////////////////////////////////
// (>head, <tail)
// AddTail:
//  1.X........ AT  ><......   GetLength()=0 -> 1, GetSize()=8
//     ********     0*******
//  2. ><...... AT  >.<.....   GetLength()=1 -> 2
//     0*******     01******
//  3. >.....<. AT  >......<   GetLength()=6 -> 7
//     012345**     0123456*
//  4. >......< AT  X.......   GetLength()=7 -> 8
//     0123456*     01234567
//  5. X....... AT  .X......   GetLength()=8 -> 8
//     01234567     81234567
//  6. .......X AT  X.......   GetLength()=8 -> 8
//     89ABCDE7     89ABCDEF
//  7.              <......>   GetLength()=0 -> 1, GetSize()=8
//                  *******0

#define YQUEUE(TYPE) template <class T, class REF_T, class YARRAY> inline TYPE YQueue<T,REF_T,YARRAY>::
#define YQUEUE$$     template <class T, class REF_T, class YARRAY> inline int YQueue<T,REF_T,YARRAY>::

YQUEUE$$ InitBounds(int iHead, int nLength)
{ 
  if(iHead<0||iHead>=GetArraySize()||nLength<0||nLength>GetArraySize())
    return INULL;
  if(iHead==0 && nLength==0)//AY 18.12.2002
    return m_iTail=m_iHead=INULL;
  m_iHead = iHead; 
  m_iTail = m_iHead + nLength; 
  if(m_iTail>=GetArraySize())
    m_iTail -= GetArraySize();
  return m_iTail;
}

YQUEUE$$ InitQueue(T item, int iHead, int nLength)
{ 
  if(nLength==0) //AY 09.01.2008
    nLength = GetArraySize();
  int iRet = InitBounds(iHead, nLength);
  if(iRet==INULL)
    return INULL;
  for(int i=0; i<GetSize(); ++i)
    operator[](i) = item;
  return iRet;
}

YQUEUE$$ GetArraySize() const
  { return YParent::GetSize(); }
YQUEUE$$ isEmpty() const 
  { return YParent::isEmpty() || (m_iHead==INULL && m_iTail==INULL); }
YQUEUE$$ isCycle() const
  { return (!isEmpty() && m_iHead==m_iTail); }
YQUEUE$$ isContinuous() const
  { return (isEmpty() || m_iHead<m_iTail); }
YQUEUE$$ isNormalized() const
  { return (isEmpty() || m_iHead==0); }

YQUEUE$$ GetSize() const
{ 
  int nDiff = m_iTail - m_iHead;
  if(nDiff==0 && m_iHead==INULL)//empty
    return 0; 
  if(nDiff<=0)                  //cycle
    nDiff += GetArraySize();
  return nDiff;
}

YQUEUE$$ AddTail(T item, BOOL bCyclic/*TRUE*/)
{
  YMEMORY_ASSERT(!YParent::isEmpty() && GetArraySize()>0);
  int nSize = GetSize();
  if(!bCyclic && nSize>=GetArraySize())
    return INULL;
  if(nSize==0){                   /*empty Add*/  ASSERT(INULL==m_iHead && INULL==m_iTail);
    m_iTail = m_iHead = 0;
    YParent::operator[](m_iTail) = item;
    if(++m_iTail>= GetArraySize())
      m_iTail = 0;
  }else if(nSize==GetArraySize()){/*cyclic Add*/ ASSERT(m_iHead>=0 && m_iHead<GetArraySize() && m_iHead==m_iTail);
    YParent::operator[](m_iTail) = item;
    if(++m_iTail,++m_iHead >= GetArraySize())
      m_iTail = m_iHead = 0;
  }else{                          /*normal Add*/
    YParent::operator[](m_iTail) = item;
    if(++m_iTail>= GetArraySize())
      m_iTail = 0;
  }
  return GetTailPos();
}

YQUEUE$$ AddHead(T item, BOOL bCyclic/*TRUE*/)
{
  YMEMORY_ASSERT(!YParent::isEmpty() && GetArraySize()>0);
  int nSize = GetSize();
  if(!bCyclic && nSize>=GetArraySize())
    return -1;
  if(nSize==0){                   /*empty Add*/  ASSERT(INULL==m_iHead && INULL==m_iTail);
    m_iTail = 0, m_iHead = GetArraySize()-1;
    YParent::operator[](m_iHead) = item;
  }else if(nSize==GetArraySize()){/*cyclic Add*/ ASSERT(m_iHead>=0 && m_iHead<GetArraySize() && m_iHead==m_iTail);
    if(--m_iTail,--m_iHead < 0)
      m_iTail = m_iHead = GetArraySize()-1;
    YParent::operator[](m_iHead) = item;
  }else{                          /*normal Add*/
    if(--m_iHead < 0)
      m_iHead = GetArraySize()-1;
    YParent::operator[](m_iHead) = item;
  }
  return GetHeadPos();
}

YQUEUE$$ Add(T item)               //array like
{
  if(!isNormalized())
    return INULL;
  return AddTail(item,FALSE);
}

YQUEUE$$ RemoveHead()
{
  YMEMORY_ASSERT(!YParent::isEmpty());
  int nSize = GetSize();
  if(nSize==0)
    return INULL;
  if(nSize==1)
    return m_iHead=m_iTail=INULL;
  if(++m_iHead >= GetArraySize())
    m_iHead = 0;
  return m_iHead;
}

YQUEUE$$ RemoveTail()
{
  YMEMORY_ASSERT(!YParent::isEmpty());
  int nSize = GetSize();
  if(nSize==0)
    return INULL;
  if(nSize==1)
    return m_iHead=m_iTail=INULL;
  if(--m_iTail < 0)
    m_iTail = GetArraySize()-1;
  return m_iTail;
}

YQUEUE$$ RemoveAll()
{
  m_iHead=m_iTail=INULL;
  return 0;
}

YQUEUE$$ Normalize()
{
  if(isNormalized())
    return 0;
  ASSERT(0);//TO DO
  return 0;
}

YQUEUE$$ AddHeadGrow(T item, int nMaxSize/*0*/) //cyclic queue
{ 
  int  nArraySize = GetArraySize();
  BOOL bAllowMem = (nMaxSize>nArraySize || nMaxSize==0);
  BOOL bOutOfMem = (GetSize()==nArraySize);
  if(bOutOfMem && !bAllowMem)
    return AddHead(item,TRUE);//cyclic
  if(bOutOfMem) {
    Normalize();
    if(0!=YParent::Expand(nArraySize+1))//TO DO
      return INULL;
    m_iTail = nArraySize;
  }
  return AddHead(T,FALSE);
}

YQUEUE$$ AddTailGrow(T item, int nMaxSize/*0*/) //cyclic queue
{ 
  int  nArraySize = GetArraySize();
  BOOL bAllowMem = (nMaxSize>nArraySize || nMaxSize==0);
  BOOL bOutOfMem = (GetSize()==nArraySize);
  if(bOutOfMem && !bAllowMem)
    return AddTail(item,TRUE);//cyclic
  if(bOutOfMem) {
    Normalize();
    if(0!=YParent::Expand(nArraySize+1))//TO DO
      return INULL;
    m_iTail = nArraySize;
  }
  return AddTail(T,FALSE);
}

YQUEUE$$ AddGrow(T item, int nMaxSize/*0*/) //array like
{ 
  if(!isNormalized())
    return INULL;
  int  nArraySize = GetArraySize();
  BOOL bAllowMem = (nMaxSize>nArraySize || nMaxSize==0);
  BOOL bOutOfMem = (GetSize()==nArraySize);
  if(bOutOfMem && !bAllowMem)
    return INULL;
  if(bOutOfMem)
    if(0!=YParent::Expand(nArraySize+1))//TO DO
      return INULL;
  return AddTail(T,FALSE);
}



YQUEUE(T) operator [](int i) const
{
  YMEMORY_ASSERT(i>=0 && i<GetSize() && !isEmpty());
  signed iIndex = m_iHead + i;
  if(iIndex>=GetArraySize())
    iIndex -= GetArraySize();
  return YParent::operator[](iIndex);
}

YQUEUE(REF_T) operator [](int i)
{
  YMEMORY_ASSERT(i>=0 && i<GetSize() && !isEmpty());
  signed iIndex = m_iHead + i;
  if(iIndex>=GetArraySize())
    iIndex -= GetArraySize();
  return YParent::operator[](iIndex);
}

////////////////////////////////////////////////////////////////////////////

YQUEUE(int)   GetQueueIdx(signed iPos) const
{ 
  signed i = iPos;
  if      (m_iHead<m_iTail) {   // --<***>-
    if(!(i>=m_iHead && i<m_iTail))
      return -1;
  }else if(m_iHead>m_iTail) {   // **>---<*
    if(!(i>=m_iHead || i<m_iTail))
      return -1;
  //lse if(m_iHead==m_iTail){   // ***X****
  }
  signed iIndex = i - m_iHead;
  if(iIndex<0)
    iIndex += GetArraySize();
  return iIndex;
}
YQUEUE(signed) GetArrayPos(int iIdx) const
{ 
  if(isEmpty() || iIdx<0 || iIdx>=GetSize())
    return INULL;
  signed iIndex = m_iHead + iIdx;
  if(iIndex>=GetArraySize())
    iIndex -= GetArraySize();
  return iIndex;
}

YQUEUE(signed) GetHeadPos() const
  { return m_iHead; }
YQUEUE(signed) GetTailPos() const
  { return(isEmpty()?INULL:(m_iTail>0?m_iTail-1:GetSize()-1)); }

YQUEUE(signed)  GetNextPos(signed iPos) const
{ 
  if(iPos==INULL) return INULL;
  if(isEmpty())   return INULL;

  int iIdx = GetQueueIdx(iPos);
  int nSize = GetSize();
  if(iIdx==-1 || iIdx>=nSize)
    { return INULL; }
  if(iIdx+1>=nSize)
    return INULL;     
  return GetArrayPos(iIdx+1);
}
YQUEUE(signed)  GetPrevPos(signed iPos) const
{ 
  if(iPos==INULL) return INULL;
  if(isEmpty())   return INULL;

  int iIdx = GetQueueIdx(iPos);
  int nSize = GetSize();
  if(iIdx==-1 || iIdx>=nSize)
    { return INULL; }
  if(iIdx==0)
    return INULL;     
  return GetArrayPos(iIdx-1);
}

YQUEUE(T) GetHead() const
  { ASSERT(!isEmpty()); return operator[](0); }
YQUEUE(REF_T) GetHead()
  { ASSERT(!isEmpty()); return operator[](0); }
YQUEUE(T) GetTail() const
  { ASSERT(!isEmpty()); return operator[](GetSize()-1); }
YQUEUE(REF_T) GetTail()
  { ASSERT(!isEmpty()); return operator[](GetSize()-1); }

YQUEUE(T)       GetNext(signed& iPos) const
  { iPos = GetNextPos(); ASSERT(iPos!=INULL); return YParent::operator[](iPos); }
YQUEUE(REF_T)   GetNext(signed& iPos)
  { iPos = GetNextPos(); ASSERT(iPos!=INULL); return YParent::operator[](iPos); }
YQUEUE(T)       GetPrev(signed& iPos) const
  { iPos = GetPrevPos(); ASSERT(iPos!=INULL); return YParent::operator[](iPos); }
YQUEUE(REF_T)   GetPrev(signed& iPos)
  { iPos = GetPrevPos(); ASSERT(iPos!=INULL); return YParent::operator[](iPos); }
YQUEUE(T)       GetAt(signed& iPos) const
  { return YParent::operator[](iPos); }
YQUEUE(REF_T)   GetAt(signed& iPos)
  { return YParent::operator[](iPos); }

#ifdef _DEBUG
YQUEUE$$ Dump()
{
  if(GetSize()==0) {
    afxDump << "<empty>";
    return 0;
  }
  int i;
  afxDump << GetSize() << "/" << GetArraySize() << ": ";
  if(m_iTail==m_iHead) {     //23401
    for(i=0; i<GetArraySize(); ++i)
      afxDump << YParent::operator[](i) << " ";
  }else if(m_iHead<m_iTail){ //**23*
    for(i=0; i<m_iHead; ++i)
      afxDump << "*" << " ";
    for(i=m_iHead; i<m_iTail; ++i)
      afxDump << YParent::operator[](i) << " ";
    for(i=m_iTail; i<GetArraySize(); ++i)
      afxDump << "*" << " ";
  }else{                     //4**23
    for(i=0; i<m_iTail; ++i)
      afxDump << YParent::operator[](i) << " ";
    for(i=m_iTail; i<m_iHead; ++i)
      afxDump << "*" << " ";
    for(i=m_iHead; i<GetArraySize(); ++i)
      afxDump << YParent::operator[](i) << " ";
  }
  afxDump << "  Queue: ";
  for(i=0; i<GetSize(); ++i) 
    afxDump << operator[](i) << " ";

  //afxDump << "\n";
  return 0;
}
#endif//_DEBUG

#undef YQUEUE
#undef YQUEUE$$

//////////////////////////////////////////////////////////////////////////////////// 
// YStaticQueue  <class T>
// YDynamicQueue <class T>
// //template <class T> typedef YStaticQueue<T> YQueue< T, YStaticArray<T> >;

template <class T> class YStaticQueue: public YQueue< T, T&, YStaticArray<T> > {
  public: YStaticQueue(int nSize, void* p=NULL) : YQueue< T, T&, YStaticArray<T> >(nSize, p) {}
  public: YStaticQueue() {}
};

template <class T> class YDynamicQueue: public YQueue< T, T&, YDynamicArray<T> > { 
  public: YDynamicQueue(int nSize, void* p=NULL) : YQueue< T, T&, YDynamicArray<T> >(nSize, p) {}
  public: YDynamicQueue() {}
};

/////////////////////////////////////////////////////////////////////////////////////////
typedef YStaticQueue<char> YStaticCharQueue;
typedef YStaticQueue<unsigned char> YStaticUCharQueue;
typedef YStaticQueue<int> YStaticIntQueue;
typedef YStaticQueue<unsigned int> YStaticUIntQueue;
typedef YStaticQueue<long> YStaticLongQueue;
typedef YStaticQueue<unsigned long> YStaticULongQueue;
typedef YStaticQueue<float> YStaticFloatQueue;
typedef YStaticQueue<double> YStaticDoubleQueue;
typedef YStaticQueue<long double> YStaticLDoubleQueue;

typedef YDynamicQueue<char> YDynamicCharQueue;
typedef YDynamicQueue<unsigned char> YDynamicUCharQueue;
typedef YDynamicQueue<int> YDynamicIntQueue;
typedef YDynamicQueue<unsigned int> YDynamicUIntQueue;
typedef YDynamicQueue<long> YDynamicLongQueue;
typedef YDynamicQueue<unsigned long> YDynamicULongQueue;
typedef YDynamicQueue<float> YDynamicFloatQueue;
typedef YDynamicQueue<double> YDynamicDoubleQueue;
typedef YDynamicQueue<long double> YDynamicLDoubleQueue;

typedef YQueue<YBit,YBit,YStaticBitArray> YStaticBitQueue;
typedef YQueue<YBit,YBit,YDynamicBitArray> YDynamicBitQueue;

////////////////////////////////////////////////////////////////////////////////////
// YSummedQueue <class T, class S, class YQUEUE>
template <class T, class S, class YQUEUE>
class YSummedQueue: public YQUEUE
{
protected:
  S             m_sum;
public:
                YSummedQueue(int nSize, void* p=NULL) 
                                : YQUEUE(nSize, p) { m_sum=0; }
                YSummedQueue()  : YQUEUE() { m_sum=0; }
  void*         Create(int nSize, void* p=NULL)      //throw CMemoryException on error
                                { m_sum=0; return YQUEUE::Create(nSize, p); }
  void*         Clear()         { m_sum=0; return YQUEUE::Clear(); }
  int           Reset()         { m_sum=0; return YQUEUE::Empty(); }
  S             GetSum() const  { return m_sum; }
public:
  int           AddHead(T item, BOOL bCyclic=TRUE);
  int           AddTail(T item, BOOL bCyclic=TRUE);
  int           RemoveHead();
  int           RemoveTail();

  const S&     _GetSum() const  { return m_sum; }
  S&           _GetSum()        { return m_sum; }
};

// IMPLEMENTATION //////////////////////////////////////////////////////////////////

#define YSUMQUEUE$$ template <class T, class S, class YQUEUE> inline int YSummedQueue<T,S,YQUEUE>::

YSUMQUEUE$$ AddHead(T item, BOOL bCyclic/*TRUE*/)
{
  if(bCyclic && isCycle()) m_sum -= YQUEUE::GetTail();
  int iReturn = YQUEUE::AddHead(item,bCyclic);
  if(iReturn!=INULL)       m_sum += YQUEUE::GetHead();
  return iReturn;
}

YSUMQUEUE$$ AddTail(T item, BOOL bCyclic/*TRUE*/)
{
  if(bCyclic && isCycle()) m_sum -= YQUEUE::GetHead();
  int iReturn = YQUEUE::AddTail(item,bCyclic);
  if(iReturn!=INULL)       m_sum += YQUEUE::GetTail();
  return iReturn;
}

YSUMQUEUE$$ RemoveHead()
{
  if(!isEmpty()) m_sum -= YQUEUE::GetHead();
  return YQUEUE::RemoveHead();
}

YSUMQUEUE$$ RemoveTail()
{
  if(!isEmpty()) m_sum -= YQUEUE::GetTail();
  return YQUEUE::RemoveTail();
}

#undef  YSUMQUEUE$$

//////////////////////////////////////////////////////////////////////////////////// 
// YStaticSummedQueue  <class T>
// YDynamicSummedQueue <class T>
template <class T> class YStaticSummedQueue: public YSummedQueue< T, T, YStaticQueue<T> > {
  public: YStaticSummedQueue(int nSize, void* p=NULL) : YSummedQueue< T, T, YStaticQueue<T> >(nSize, p) {}
  public: YStaticSummedQueue() {}
};

template <class T> class YDynamicSummedQueue: public YSummedQueue< T, T, YDynamicQueue<T> > {
  public: YDynamicSummedQueue(int nSize, void* p=NULL) : YSummedQueue< T, T, YDynamicQueue<T> >(nSize, p) {}
  public: YDynamicSummedQueue() {}
};
/////////////////////////////////////////////////////////////////////////////////////////
typedef YStaticSummedQueue<char         > YStaticSummedCharQueue   ;
typedef YStaticSummedQueue<unsigned char> YStaticSummedUCharQueue  ;
typedef YStaticSummedQueue<int          > YStaticSummedIntQueue    ;
typedef YStaticSummedQueue<unsigned int > YStaticSummedUIntQueue   ;
typedef YStaticSummedQueue<long         > YStaticSummedLongQueue   ;
typedef YStaticSummedQueue<unsigned long> YStaticSummedULongQueue  ;
typedef YStaticSummedQueue<float        > YStaticSummedFloatQueue  ;
typedef YStaticSummedQueue<double       > YStaticSummedDoubleQueue ;
typedef YStaticSummedQueue<long double  > YStaticSummedLDoubleQueue;

typedef YDynamicSummedQueue<char         > YDynamicSummedCharQueue   ;
typedef YDynamicSummedQueue<unsigned char> YDynamicSummedUCharQueue  ;
typedef YDynamicSummedQueue<int          > YDynamicSummedIntQueue    ;
typedef YDynamicSummedQueue<unsigned int > YDynamicSummedUIntQueue   ;
typedef YDynamicSummedQueue<long         > YDynamicSummedLongQueue   ;
typedef YDynamicSummedQueue<unsigned long> YDynamicSummedULongQueue  ;
typedef YDynamicSummedQueue<float        > YDynamicSummedFloatQueue  ;
typedef YDynamicSummedQueue<double       > YDynamicSummedDoubleQueue ;
typedef YDynamicSummedQueue<long double  > YDynamicSummedLDoubleQueue;

typedef YSummedQueue<YBit,unsigned,YStaticBitQueue> YStaticSummedBitQueue;
typedef YSummedQueue<YBit,unsigned,YDynamicBitQueue> YDynamicSummedBitQueue;

//////////////////////////////////////////////////////////////////////////////////// 
// math array operators
template <class S, class A> inline                            //array
S sum_array(S* pSum, const A& ar, int i=0, int n=-1)
{
  int nSize = ar.GetSize();
  ASSERT(i!=-1 || n!=-1);
  if(i==-1) { i=nSize-n;   if(i<0) {n+=i; i=0;} } // n or less items from end
  if(n==-1) { n=nSize-i; } if(n+i>=nSize) n=nSize-i;// n or less items from i
  S SSum = 0; 
  for(int j=i; j<i+n; ++j)
    SSum += (S)ar[j];
  return NULL==pSum ? SSum : *pSum=SSum;
}

template <class S, class A> inline                            //array
S max_array(S* pMax, const A& ar, int i=0, int n=-1)
{       
  int nSize = ar.GetSize();
  ASSERT(i!=-1 || n!=-1);
  if(i==-1) { i=nSize-n;   if(i<0) {n+=i; i=0;} } // n or less items from end
  if(n==-1) { n=nSize-i; } if(n+i>=nSize) n=nSize-i;// n or less items from i
  S SMax;//SIC! use uninitilized variable
  if(n>0)
    SMax = ar[i];
  for(int j=i+1; j<i+n; ++j)
    if(SMax < (S)ar[j])
      SMax = ar[j];
  return NULL==pMax ? SMax : *pMax=SMax;
}

template <class S, class A> inline                            //array
S min_array(S* pMin, const A& ar, int i=0, int n=-1)
{
  int nSize = ar.GetSize();
  ASSERT(i!=-1 || n!=-1);
  if(i==-1) { i=nSize-n;   if(i<0) {n+=i; i=0;} } // n or less items from end
  if(n==-1) { n=nSize-i; } if(n+i>=nSize) n=nSize-i;// n or less items from i
  S SMin;//SIC! use uninitilized variable
  if(n>0)
    SMin = ar[i];
  for(int j=i+1; j<i+n; ++j)
    if(SMin > (S)ar[j])
      SMin = ar[j];
  return NULL==pMin ? SMin : *pMin=SMin;
}

// default cases ///////////////
template <class T> inline T sum(const YStaticArray<T>& ar, int i=0, int n=-1)
  { return sum_array((T*)NULL,ar,i,n); }
template <class T> inline T sum(const YDynamicArray<T>& ar, int i=0, int n=-1)
  { return sum_array((T*)NULL,ar,i,n); }

template <class T> inline T _max(const YStaticArray<T>& ar, int i=0, int n=-1)
  { return max_array((T*)NULL,ar,i,n); }
template <class T> inline T _max(const YDynamicArray<T>& ar, int i=0, int n=-1)
  { return max_array((T*)NULL,ar,i,n); }

template <class T> inline T _min(const YStaticArray<T>& ar, int i=0, int n=-1)
  { return min_array((T*)NULL,ar,i,n); }
template <class T> inline T _min(const YDynamicArray<T>& ar, int i=0, int n=-1)
  { return min_array((T*)NULL,ar,i,n); }


//////////////////////////////////////////////////////////////////////////////////// 
// math queue operators
template <class S, class T, class REF_T, class YARRAY> inline //queue
S sum_queue(S* pSum, const YQueue<T,REF_T,YARRAY>& que, int i=0, int n=-1)
{
  if(que.GetSize()==que.GetArraySize() && i==0 && n==-1)
    return sum_array(pSum,(const YQueue<T,REF_T,YARRAY>::YParent&)que);
  else
    return sum_array(pSum,que,i,n);
}

template <class S, class T, class REF_T, class YARRAY> inline //queue
S max_queue(S* pMax, const YQueue<T,REF_T,YARRAY>& que, int i=0, int n=-1)
{
  if(que.GetSize()==que.GetArraySize() && i==0 && n==-1)
    return max_array(pMax,(const YQueue<T,REF_T,YARRAY>::YParent&)que);
  else
    return max_array(pMax,que,i,n);
}

template <class S, class T, class REF_T, class YARRAY> inline //queue
S min_queue(S* pMin, const YQueue<T,REF_T,YARRAY>& que, int i=0, int n=-1)
{
  if(que.GetSize()==que.GetArraySize() && i==0 && n==-1)
    return min_array(pMin,(const YQueue<T,REF_T,YARRAY>::YParent&)que);
  else
    return min_array(pMin,que,i,n);
}

// default cases ///////////////
template <class T> inline T sum(const YStaticQueue<T>& ar, int i=0, int n=-1)
  { return sum_queue((T*)NULL,ar,i,n); }
template <class T> inline T sum(const YDynamicQueue<T>& ar, int i=0, int n=-1)
  { return sum_queue((T*)NULL,ar,i,n); }

template <class T> inline T _max(const YStaticQueue<T>& ar, int i=0, int n=-1)
  { return max_queue((T*)NULL,ar,i,n); }
template <class T> inline T _max(const YDynamicQueue<T>& ar, int i=0, int n=-1)
  { return max_queue((T*)NULL,ar,i,n); }

template <class T> inline T _min(const YStaticQueue<T>& ar, int i=0, int n=-1)
  { return min_queue((T*)NULL,ar,i,n); }
template <class T> inline T _min(const YDynamicQueue<T>& ar, int i=0, int n=-1)
  { return min_queue((T*)NULL,ar,i,n); }


template <class T> inline T sum(const YStaticSummedQueue<T>& ar, int i=0, int n=-1)
  { return sum_queue((T*)NULL,ar,i,n); }
template <class T> inline T sum(const YDynamicSummedQueue<T>& ar, int i=0, int n=-1)
  { return sum_queue((T*)NULL,ar,i,n); }

template <class T> inline T _max(const YStaticSummedQueue<T>& ar, int i=0, int n=-1)
  { return max_queue((T*)NULL,ar,i,n); }
template <class T> inline T _max(const YDynamicSummedQueue<T>& ar, int i=0, int n=-1)
  { return max_queue((T*)NULL,ar,i,n); }

template <class T> inline T _min(const YStaticSummedQueue<T>& ar, int i=0, int n=-1)
  { return min_queue((T*)NULL,ar,i,n); }
template <class T> inline T _min(const YDynamicSummedQueue<T>& ar, int i=0, int n=-1)
  { return min_queue((T*)NULL,ar,i,n); }

// special cases ///////////////
inline int sum(const YStaticBitQueue& ar, int i=0, int n=-1)
  { return sum_queue((int*)NULL,ar,i,n); }
inline int sum(const YDynamicBitQueue& ar, int i=0, int n=-1)
  { return sum_queue((int*)NULL,ar,i,n); }

inline int _max(const YStaticBitQueue& ar, int i=0, int n=-1)
  { return max_queue((int*)NULL,ar,i,n); }
inline int _max(const YDynamicBitQueue& ar, int i=0, int n=-1)
  { return max_queue((int*)NULL,ar,i,n); }

inline int _min(const YStaticBitQueue& ar, int i=0, int n=-1)
  { return min_queue((int*)NULL,ar,i,n); }
inline int _min(const YDynamicBitQueue& ar, int i=0, int n=-1)
  { return min_queue((int*)NULL,ar,i,n); }

inline int sum(const YStaticSummedBitQueue& ar, int i=0, int n=-1)
  { return sum_queue((int*)NULL,ar,i,n); }
inline int sum(const YDynamicSummedBitQueue& ar, int i=0, int n=-1)
  { return sum_queue((int*)NULL,ar,i,n); }

inline int _max(const YStaticSummedBitQueue& ar, int i=0, int n=-1)
  { return max_queue((int*)NULL,ar,i,n); }
inline int _max(const YDynamicSummedBitQueue& ar, int i=0, int n=-1)
  { return max_queue((int*)NULL,ar,i,n); }

inline int _min(const YStaticSummedBitQueue& ar, int i=0, int n=-1)
  { return min_queue((int*)NULL,ar,i,n); }
inline int _min(const YDynamicSummedBitQueue& ar, int i=0, int n=-1)
  { return min_queue((int*)NULL,ar,i,n); }

#endif//__YQUEUE_H
#pragma once
