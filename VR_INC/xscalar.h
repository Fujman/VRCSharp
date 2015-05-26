#ifndef __XSCALAR_H
#define __XSCALAR_H

__inline safe_get_yield(unsigned increment=1) //call safe_get_yield(0) for query only
{ 
  static unsigned nSpinCycles=0;
  ::Sleep(0); 
  return nSpinCycles+=increment;
}

__inline          __int64 __safe_get_i64(volatile const          __int64* p)
{                                                                
  __int64 v;

  for(v=*p; v!=*p; )
    safe_get_yield();

  return v;
}

__inline unsigned __int64 __safe_get_u64(volatile const unsigned __int64* p)
{
  unsigned __int64 v;

  for(v=*p; v!=*p; )
    safe_get_yield();

  return v;
}


__inline void __safe_put_i64(         __int64 v, volatile           __int64* p)
{                                                                
  for(*p=v; v!=*p; )
    safe_get_yield();
}

__inline void __safe_put_u64(unsigned __int64 v, volatile unsigned __int64* p)
{
  for(*p=v; v!=*p; )
    safe_get_yield();
}

__inline          __int64 safe_get_i64(const          __int64* p)   { return __safe_get_i64((volatile const          __int64*) p); }

__inline unsigned __int64 safe_get_u64(const unsigned __int64* p)   { return __safe_get_u64((volatile const unsigned __int64*) p); }

__inline void safe_put_i64(         __int64 v,          __int64* p) { __safe_put_i64(v, (volatile          __int64*) p); }

__inline void safe_put_u64(unsigned __int64 v, unsigned __int64* p) { __safe_put_u64(v, (volatile unsigned __int64*) p); }


#endif//__XSCALAR_H
#pragma once