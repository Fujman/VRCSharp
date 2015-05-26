#ifndef __YCOOKIE_H
#define __YCOOKIE_H

////////////////////////////////////////////////////////////////////////////////////
// YCOOKIE, YCookie (multithreading ready, platform dependent!)

// C,C++ declarations \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

#define YCOOKIE_INVALID (0xFFFFFFFF)
#define YCOOKIE_INITIAL (0x00000000)

typedef DWORD   YCOOKIE;

// C/C++ dual inline/global declarations /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef  __cplusplus
#ifdef  __YCOOKIE_C
extern "C" {
#endif//__YCOOKIE_C 
#endif//__cplusplus

YCOOKIE YCOOKIE_INCREASE(YCOOKIE* pcookie);
BOOL    YCOOKIE_IS_VALID(YCOOKIE cookie);
BOOL    YCOOKIE_IN_RANGE(YCOOKIE cookie, YCOOKIE c0, YCOOKIE c1);

#ifdef  __cplusplus
#ifdef  __YCOOKIE_C
}
#endif//__YCOOKIE_C 
#endif//__cplusplus

// C++ declarations \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef  __cplusplus

class YCookie   //initial value is 0, invalid values are 0, 0xFFFFFFFF
{ 
protected:    
  YCOOKIE       m_cookie;
public:         
                YCookie()
                  { m_cookie = YCOOKIE_INITIAL; }

                YCookie(const YCookie& cookie)
                  { m_cookie = cookie.m_cookie; ASSERT(m_cookie!=YCOOKIE_INVALID); }
  YCookie&      operator= (const YCookie& cookie)
                  { m_cookie = cookie; ASSERT(m_cookie!=YCOOKIE_INVALID); return *this;}

                YCookie(YCOOKIE cookie)
                  { m_cookie = cookie; ASSERT(m_cookie!=YCOOKIE_INVALID); }
                operator YCOOKIE() const
                  { return m_cookie; }

  BOOL          operator==(const YCookie& cookie) const
                  { return m_cookie==cookie.m_cookie; }
  BOOL          operator!=(const YCookie& cookie) const
                  { return m_cookie!=cookie.m_cookie; }

  BOOL          operator==(YCOOKIE cookie) const
                  { return m_cookie==cookie; }
  BOOL          operator!=(YCOOKIE cookie) const
                  { return m_cookie!=cookie; }

  BOOL          IsValid() const
                  { return YCOOKIE_IS_VALID(m_cookie); }

  BOOL          InRange(const YCookie& c0, const YCookie& c1) const
                  { return YCOOKIE_IN_RANGE(m_cookie,c0,c1); }
  BOOL          InRange(YCOOKIE c0, YCOOKIE c1) const
                  { return YCOOKIE_IN_RANGE(m_cookie,c0,c1); }

  YCookie       Increase()
                  { return YCOOKIE_INCREASE(&m_cookie); }
  YCookie       Invalidate()
                  { return( m_cookie=YCOOKIE_INVALID ); }
};

#endif//__cplusplus


// C/C++ dual inline/global implementation /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#if      defined(__YCOOKIE_C) || defined(__cplusplus)

#if     !defined(__YCOOKIE_C) && defined(__cplusplus)
  #define YCOOKIE_INLINE   inline
#else
  #define YCOOKIE_INLINE //global
#endif//!defined(__YCOOKIE_C) && defined(__cplusplus)

YCOOKIE_INLINE YCOOKIE YCOOKIE_INCREASE(YCOOKIE* pcookie)
{
  register YCOOKIE cookie;
  while((cookie = ::InterlockedExchange((LONG*)pcookie,YCOOKIE_INVALID))==YCOOKIE_INVALID)
    ::Sleep(0);            //lock by spin
  ++cookie;
  if     (cookie==YCOOKIE_INVALID) { cookie = YCOOKIE_INITIAL+1; ASSERT(!"COOKIE owerflow"); }
  else if(cookie==YCOOKIE_INITIAL) { cookie = YCOOKIE_INITIAL+1; ASSERT(!"COOKIE owerflow"); }
  return *pcookie = cookie;//unlock
}

YCOOKIE_INLINE BOOL    YCOOKIE_IS_VALID(YCOOKIE cookie)
{
  return cookie!=YCOOKIE_INVALID &&
         cookie!=YCOOKIE_INITIAL;
}

YCOOKIE_INLINE BOOL    YCOOKIE_IN_RANGE(YCOOKIE cookie, YCOOKIE c0, YCOOKIE c1)
{
  if(!YCOOKIE_IS_VALID(cookie)) return FALSE;
  return((YCOOKIE)(c0)<=(YCOOKIE)(c1)     ? 
         (YCOOKIE)(c0)<=(YCOOKIE)(cookie) &&
         (YCOOKIE)(c1)>=(YCOOKIE)(cookie) : 
         (YCOOKIE)(c1)<=(YCOOKIE)(cookie) &&
         (YCOOKIE)(c0)>=(YCOOKIE)(cookie));
}

#undef YCOOKIE_INLINE

#endif// defined(__YCOOKIE_C) || defined(__cplusplus)
////////////////////////////////////////////////////////////////////////////////////

#endif//__YCOOKIE_H
#pragma once
