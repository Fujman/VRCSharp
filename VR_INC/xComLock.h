#ifndef __XCOMLOCK_H
#define __XCOMLOCK_H

class CComCS
{
  CComCriticalSection* m_pcs;
public:
  CComCS(CComCriticalSection& cs)
    { m_pcs = &cs; m_pcs->Lock(); }
  ~CComCS() 
    { if(m_pcs) m_pcs->Unlock(); }
  void Enter(CComCriticalSection& cs)
    { ASSERT(!m_pcs); m_pcs = &cs; m_pcs->Lock(); }
  void Leave()
    { ASSERT(m_pcs); m_pcs->Unlock(); m_pcs=NULL; }
};


#endif//__XCOMLOCK_H
#pragma once