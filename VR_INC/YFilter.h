#ifndef __YFILTER_H
#define __YFILTER_H
#include "YQueue.h"

///////////////////////////////////////////////////////////////////////////
// YBaseFilter
class YBaseFilter
{
public:
                        YBaseFilter(YBaseFilter& prev)
                          { m_pPrev = (&prev==&ROOT ? NULL : &prev); }
                        YBaseFilter()
                          { m_pPrev = NULL; }
  virtual               ~YBaseFilter()
                          { }
  virtual int           reset(unsigned fs=0, int nFlags=0, int nGroupDelay=0)//0-sequential,1-parallel
                          { return 0; }
  virtual int           create(unsigned fs=0, int nDelay=0)
                          { return 0; }
  virtual int           delay(int order=0, int window=0) const
                          { return 0; }
  virtual int           group() const
                          { return 0; }
  virtual int           order() const
                          { return 0; }
  virtual int           window() const
                          { return 0; }
  YBaseFilter*          m_pPrev;
public:
  static YBaseFilter    ROOT;
};

///////////////////////////////////////////////////////////////////////////
// YDelayFilter
template <class _FILTER> class YDelayFilter: public YBaseFilter
{
public:
  typedef typename _FILTER         FILTER;
  typedef typename _FILTER::SIGNAL SIGNAL;
  typedef typename _FILTER::ANSWER ANSWER;

public:
  FILTER                m_filter;
protected:
  YStaticQueue<ANSWER>  m_queue;
  int                   m_delay;
  int                   m_order;
  int                   m_window;
public:
  YDelayFilter(unsigned fs=0, int order=0, int window=0)//undependent of fs default implementation
    { m_order = order; m_window = window; create(fs); }

  YDelayFilter(YBaseFilter& filter, int order=0, int window=0) //need reset() call
    : YBaseFilter(filter) { m_delay = 0; m_order = order; m_window = window;}

  void construct(YBaseFilter& filter, int order=0, int window=0)
    { m_pPrev = &filter; m_delay = 0; m_order = order; m_window = window; }

  virtual int reset(unsigned fs=0, int nFlags=0, int nGroupDelay=0)//0-sequential,1-parallel
  { 
    if((nFlags&3)==3) 
      return undependent(nGroupDelay,fs);
    return (nFlags&1)?parallel(nGroupDelay,fs):sequence(nGroupDelay,fs);
  }

  virtual int create(unsigned fs=0, int nDelay=0)
  {
    m_filter.reset(fs, m_order, m_window); 
    m_delay = nDelay; 
    if(nDelay){
      m_queue.Create(m_delay); 
      m_queue.InitQueue(0); 
    }
    return 0;
  }

  virtual int order() const
  {
    return m_order;
  }

  virtual int window() const
  {
    return m_window;
  }

  virtual int delay(int order=0, int window=0) const //TO DO: all==0?
  {
    return m_filter.delay(m_order, m_window);
  }

  virtual int group() const
  {
    if(m_pPrev==NULL || m_pPrev==&ROOT)
      return m_delay + m_filter.delay();
    for(const YBaseFilter* pFilter=this; pFilter->m_pPrev!=NULL && pFilter->m_pPrev!=&ROOT; pFilter=pFilter->m_pPrev)
      0;
    return pFilter->group();
  }

#ifdef _DEBUG
  int _delay() const { return m_delay; }
  int _queue() const { return m_queue.GetArraySize(); }
#endif
protected:

  int parallel(int nGroupDelay=0, unsigned fs=0)
  {
/*
   01234567890  01234567890  delay
s: !..........  !_________r= 10-0 =10
3: ...!.......  ...!______r= 10-3  =7
5: .....!.....  .....!____r= 10-5  =5
2: ..!........  ..!_______r= 10-2  =8
*/
    YBaseFilter* pFilter;
    int group = 0;
    for(pFilter=this; pFilter!=NULL && pFilter!=&ROOT; pFilter=pFilter->m_pPrev){
	    group = max(group, pFilter->delay());
    }

    if(nGroupDelay){ 
      ASSERT(nGroupDelay>=group); nGroupDelay = max(nGroupDelay,group);
    }else{
      nGroupDelay = group;
    }

    for(pFilter=this; pFilter!=NULL && pFilter!=&ROOT; pFilter=pFilter->m_pPrev){
	    pFilter->create(fs,nGroupDelay - pFilter->delay());
    }
    return 0;
  }

  int sequence(int nGroupDelay=0, unsigned fs=0)
  {
/*
   01234567890  01234567890  delay
s: !..........  r_________!= 3+5+2 =10
3: ...!.......  ...r______!= 5+2   =7
5: ........!..  ........r_!= 2     =2
2: ..........!  ..........?= 0     =0
*/
    YBaseFilter* pFilter;
    int group = 0;
    for(pFilter=this; pFilter!=NULL && pFilter!=&ROOT; pFilter=pFilter->m_pPrev){
	    group += pFilter->delay();
    }

    if(nGroupDelay){ 
      ASSERT(nGroupDelay>=group); nGroupDelay = max(nGroupDelay,group);
    }else{
      nGroupDelay = group;
    }

    int delay = nGroupDelay-group;
    for(pFilter=this; pFilter!=NULL && pFilter!=&ROOT; pFilter=pFilter->m_pPrev){
	    pFilter->create(fs,delay);
      delay += pFilter->delay();
    }
    return 0;
  }

  int undependent(int nGroupDelay=0, unsigned fs=0)
  {
    YBaseFilter* pFilter;
    for(pFilter=this; pFilter!=NULL && pFilter!=&ROOT; pFilter=pFilter->m_pPrev){
	    pFilter->create(fs,nGroupDelay);
    }
    return 0;
  }

public:
  ANSWER filter(SIGNAL s, ANSWER* px)
  {
    ANSWER x = m_filter.filter(s);
    ANSWER o = x;//delay>0
    if(m_delay>0) {
      ASSERT(m_delay<=m_queue.GetSize());
      if(m_delay>=m_queue.GetSize())
        o = m_queue[0];//lastest
      m_queue.AddTail(x);
      if(m_delay<m_queue.GetSize())
        o = m_queue[m_delay];
      *px = x;
    }else{//delay==0
      if(m_pPrev!=0 && m_pPrev!=&ROOT)//sequential mode?
        *px = x;
    }
    return o;
  }

  ANSWER filter(SIGNAL s)
  {
    ANSWER x, o;
    o = filter(s, &x); 
    return o;
  }
};

/////////////////////////////////////////////////////////////////////////////
// YDeltaFilter: exmaple filter implementation - delay and scale
template <int DELAY, class _SIGNAL=short> class YDeltaFilter //common delayed filter emulation
{
public: //YFilter base interface
  typedef typename _SIGNAL       SIGNAL, ANSWER;
                        YDeltaFilter() 
                          { m_queue.Create(DELAY+1); m_queue.InitQueue(0,0,DELAY); }
  int                   reset(unsigned fs, int delay=0, int window=0)
                          { ASSERT(0==delay || DELAY==delay); return 0; }
  ANSWER                filter(SIGNAL s)
                          { m_queue.AddHead(s); return m_queue[delay()]*multi(); }
  int                   delay(int order=0, int window=0) const
                          { return DELAY; }
protected: //YDeltaFilter specific
  int                   multi()
                          { return m_queue.GetSize()<2?1:delay(); }
  YStaticQueue<SIGNAL>  m_queue;
};

/* Usage examples ******************************************************

{ //undependent filters//
  YDelayFilter< YDeltaFilter<0> > O;
  YDelayFilter< YDeltaFilter<3> > A;
  YDelayFilter< YDeltaFilter<5> > B;
  YDelayFilter< YDeltaFilter<2> > C;

  for(short s=1,i=0; i<8; ++i,s=0){
    short o = O.filter(s);
    short a = A.filter(s);
    short b = B.filter(s);
    short c = C.filter(s);
    cout << i << o << a << b << c;
  }
}

{ //parallel filters//
  YDelayFilter< YDeltaFilter<0> > O(YBaseFilter::ROOT);
  YDelayFilter< YDeltaFilter<3> > A(O);
  YDelayFilter< YDeltaFilter<5> > B(A);
  YDelayFilter< YDeltaFilter<2> > C(B);
  C.reset(0,1);

  for(short j=1,i=0; i<=8; ++i,j=0){
    short s = j;
    short o = O.filter(s);
    short a = A.filter(s);
    short b = B.filter(s);
    short c = C.filter(s);
    cout << i << o << a << b << c;
  }
}

{ //sequential filters//
  YDelayFilter< YDeltaFilter<0> > O(YBaseFilter::ROOT);
  YDelayFilter< YDeltaFilter<3> > A(O);
  YDelayFilter< YDeltaFilter<5> > B(A);
  YDelayFilter< YDeltaFilter<2> > C(B);
  C.reset();

  for(short j=1,i=0; i<=10; ++i,j=0){
    short s = j;
    short o = O.filter(s,&s); short _o = s;
    short a = A.filter(s,&s); short _a = s;
    short b = B.filter(s,&s); short _b = s;
    short c = C.filter(s,&s); short _c = s;
    cout << i << o << a << b << c << _o << _a << _b << _c;
  }
}

Output /undependent filters/:
 i:     o    a    b    c
 0:     1    0    0    0
 1:     0    0    0    0
 2:     0    0    0    2
 3:     0    3    0    0
 4:     0    0    0    0
 5:     0    0    5    0
 6:     0    0    0    0
 7:     0    0    0    0

Output /parallel filters/:
 i:     o    a    b    c
 0:     0    0    0    0
 1:     0    0    0    0
 2:     0    0    0    0
 3:     0    0    0    0
 4:     0    0    0    0
 5:     1    3    5    2
 6:     0    0    0    0
 7:     0    0    0    0
 8:     0    0    0    0

Output /sequential filters/:
 i:     o    a    b    c   (  _o   _a   _b   _c)
 0:     0    0    0    0   (   1    0    0    0)
 1:     0    0    0    0   (   0    0    0    0)
 2:     0    0    0    0   (   0    0    0    0)
 3:     0    0    0    0   (   0    3    0    0)
 4:     0    0    0    0   (   0    0    0    0)
 5:     0    0    0    0   (   0    0    0    0)
 6:     0    0    0    0   (   0    0    0    0)
 7:     0    0    0    0   (   0    0    0    0)
 8:     0    0    0    0   (   0    0   15    0)
 9:     0    0    0    0   (   0    0    0    0)
10:     1    3   15   30   (   0    0    0   30)

*/

#include "YFilter.inl"

#endif//__YFILTER_H
#pragma once