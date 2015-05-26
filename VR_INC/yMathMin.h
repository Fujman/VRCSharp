#ifndef __YMATH_H
#define __YMATH_H

template <class T> __inline T _ymin1(const T& pData, T nmin)
{
  return pData<nmin?pData:nmin;
}

template <class T> __inline T _ymin8(const T* pData, T nmin)
{
  T min21 = pData[0]<pData[1]?pData[0]:pData[1];
  T min22 = pData[2]<pData[3]?pData[2]:pData[3];
  T min23 = pData[4]<pData[5]?pData[4]:pData[5];
  T min24 = pData[6]<pData[7]?pData[6]:pData[7];
  T min41 = min21<min23?min21:min23;
  T min42 = min22<min24?min22:min24;
  T min81 = min41<min42?min41:min42;
  return min81< nmin?min81: nmin;
}

template <class T> __inline T _ymin8(const T* pData)
{
  T min21 = pData[0]<pData[1]?pData[0]:pData[1];
  T min22 = pData[2]<pData[3]?pData[2]:pData[3];
  T min23 = pData[4]<pData[5]?pData[4]:pData[5];
  T min24 = pData[6]<pData[7]?pData[6]:pData[7];
  T min41 = min21<min23?min21:min23;
  T min42 = min22<min24?min22:min24;
  T min81 = min41<min42?min41:min42;
  return min81;
}

template <class T> inline T ymin8(const T* pData, T nmin)
{
  return _ymin8(pData, nmin);
}

template <class T> inline T ymin8(const T* pData)
{
  return _ymin8(pData);
}

template <class T> T ymin64(const T* pData, T nmin)
{
  T an[8];
  an[0] = _ymin8(pData+0*8);
  an[1] = _ymin8(pData+1*8);
  an[2] = _ymin8(pData+2*8);
  an[3] = _ymin8(pData+3*8);
  an[4] = _ymin8(pData+4*8);
  an[5] = _ymin8(pData+5*8);
  an[6] = _ymin8(pData+6*8);
  an[7] = _ymin8(pData+7*8);
  return  _ymin8(an,nmin);
}

template <class T> T ymin64(const T* pData)
{
  T an[8];
  an[0] = _ymin8(pData+0*8);
  an[1] = _ymin8(pData+1*8);
  an[2] = _ymin8(pData+2*8);
  an[3] = _ymin8(pData+3*8);
  an[4] = _ymin8(pData+4*8);
  an[5] = _ymin8(pData+5*8);
  an[6] = _ymin8(pData+6*8);
  an[7] = _ymin8(pData+7*8);
  return  _ymin8(an);
}

template <class T> T yminN(int n, const T* pData, T nmin)
{
  for(int i=0; i+8<n; i+=8)
    nmin = _ymin8(pData+i,nmin);
  for(       ;   i<n; i++)
    nmin = _ymin1(pData[i],nmin);
  return nmin;
}

template <class T> T yminN(int n, const T* pData)
{
  T nmin; if(n) nmin = *pData;//warning: use uninitialized value if n==0
  for(int i=0; i+8<n; i+=8)
    nmin = _ymin8(pData+i,nmin);
  for(       ;   i<n; i++)
    nmin = _ymin1(pData[i],nmin);
  return nmin;
}

template <class T, int N64, int N1K> struct Ymin
{
  static T min64(const T *pData)
  {
    ASSERT( (N64 % 8)==0 );
    ASSERT( N64 >= 8 );
    T nmin = _ymin8(pData);
    for(unsigned i=8; i<N64; i+=8)
      nmin = _ymin8(pData+i, nmin);
    return nmin;
  }

  static T min1K(const T* pData, T *pmin)
  {
    ASSERT( (N1K % N64)==0 );
    ASSERT( N1K > N64 );

    for(unsigned i=0; i<N1K; i+=N64)
      pmin[i/N64] = Ymin<T,N64,N1K>::min64(pData+i);

    enum { N8 = N1K/N64 };
    ASSERT( (N8 % 8)==0 );
    ASSERT( N8 >= 8 );

    T nmin = _ymin8(pmin);
    for(i=8; i<N8; i+=8)
      nmin = _ymin8(pmin+i, nmin);
    return nmin;
  }
};

#endif//__YMATH_H
