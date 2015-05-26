#ifndef __YMATH_H
#define __YMATH_H

template <class T> __inline T _ymax1(const T& pData, T nMax)
{
  return pData>nMax?pData:nMax;
}

template <class T> __inline T _ymax8(const T* pData, T nMax)
{
  T max21 = pData[0]>pData[1]?pData[0]:pData[1];
  T max22 = pData[2]>pData[3]?pData[2]:pData[3];
  T max23 = pData[4]>pData[5]?pData[4]:pData[5];
  T max24 = pData[6]>pData[7]?pData[6]:pData[7];
  T max41 = max21>max23?max21:max23;
  T max42 = max22>max24?max22:max24;
  T max81 = max41>max42?max41:max42;
  return max81> nMax?max81: nMax;
}

template <class T> __inline T _ymax8(const T* pData)
{
  T max21 = pData[0]>pData[1]?pData[0]:pData[1];
  T max22 = pData[2]>pData[3]?pData[2]:pData[3];
  T max23 = pData[4]>pData[5]?pData[4]:pData[5];
  T max24 = pData[6]>pData[7]?pData[6]:pData[7];
  T max41 = max21>max23?max21:max23;
  T max42 = max22>max24?max22:max24;
  T max81 = max41>max42?max41:max42;
  return max81;
}

template <class T> inline T ymax8(const T* pData, T nMax)
{
  return _ymax8(pData, nMax);
}

template <class T> inline T ymax8(const T* pData)
{
  return _ymax8(pData);
}

template <class T> T ymax64(const T* pData, T nMax)
{
  T an[8];
  an[0] = _ymax8(pData+0*8);
  an[1] = _ymax8(pData+1*8);
  an[2] = _ymax8(pData+2*8);
  an[3] = _ymax8(pData+3*8);
  an[4] = _ymax8(pData+4*8);
  an[5] = _ymax8(pData+5*8);
  an[6] = _ymax8(pData+6*8);
  an[7] = _ymax8(pData+7*8);
  return  _ymax8(an,nMax);
}

template <class T> T ymax64(const T* pData)
{
  T an[8];
  an[0] = _ymax8(pData+0*8);
  an[1] = _ymax8(pData+1*8);
  an[2] = _ymax8(pData+2*8);
  an[3] = _ymax8(pData+3*8);
  an[4] = _ymax8(pData+4*8);
  an[5] = _ymax8(pData+5*8);
  an[6] = _ymax8(pData+6*8);
  an[7] = _ymax8(pData+7*8);
  return  _ymax8(an);
}

template <class T> T ymaxN(int n, const T* pData, T nMax)
{
  for(int i=0; i+8<n; i+=8)
    nMax = _ymax8(pData+i,nMax);
  for(       ;   i<n; i++)
    nMax = _ymax1(pData[i],nMax);
  return nMax;
}

template <class T> T ymaxN(int n, const T* pData)
{
  T nMax; if(n) nMax = *pData;//warning: use uninitialized value if n==0
  for(int i=0; i+8<n; i+=8)
    nMax = _ymax8(pData+i,nMax);
  for(       ;   i<n; i++)
    nMax = _ymax1(pData[i],nMax);
  return nMax;
}

template <class T, int N64, int N1K> struct YMax
{
  static T max64(const T *pData)
  {
    ASSERT( (N64 % 8)==0 );
    ASSERT( N64 >= 8 );
    T nMax = _ymax8(pData);
    for(unsigned i=8; i<N64; i+=8)
      nMax = _ymax8(pData+i, nMax);
    return nMax;
  }

  static T max1K(const T* pData, T *pMax)
  {
    ASSERT( (N1K % N64)==0 );
    ASSERT( N1K > N64 );

    for(unsigned i=0; i<N1K; i+=N64)
      pMax[i/N64] = YMax<T,N64,N1K>::max64(pData+i);

    enum { N8 = N1K/N64 };
    ASSERT( (N8 % 8)==0 );
    ASSERT( N8 >= 8 );

    T nMax = _ymax8(pMax);
    for(i=8; i<N8; i+=8)
      nMax = _ymax8(pMax+i, nMax);
    return nMax;
  }
};

#endif//__YMATH_H
