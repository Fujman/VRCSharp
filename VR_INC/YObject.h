#ifndef __YOBJECTSTATE_H
#define __YOBJECTSTATE_H

class YObjectState //MT guarded
{
public:
  enum { stateENABLED=1/*reserved*/, stateACTIVE=2, statePAUSED=8, stateOPENED=16 }; // Note: statuses ACTIVE & OPENED is independent
  enum { stateREADY=4/*perspective*/ };
  enum { stateBUSY=32/*perspective*/ };
  enum { stateMASK = stateENABLED|stateACTIVE|statePAUSED|stateOPENED|stateREADY|stateBUSY };
public:
                        YObjectState()
                          { m_ObjectState = 0; m_ObjectEvent = 0; }

  BOOL                  IsEnabled() const       { return HasFlag(stateENABLED); }
  BOOL                  IsOpened() const        { return HasFlag(stateOPENED ); }
  BOOL                  IsActive() const        { return HasFlag(stateACTIVE ); }
  BOOL                  IsPaused() const        { return HasFlag(statePAUSED ); }

  BOOL                  Enable()                { BOOL bOK=!IsEnabled(); SetFlag(stateENABLED); ASSERT(bOK); return bOK; }
  BOOL                  Open()                  { BOOL bOK=!IsOpened();  SetFlag(stateOPENED ); ASSERT(bOK); return bOK; }
  BOOL                  Start()                 { BOOL bOK=!IsActive();  SetFlag(stateACTIVE ); ASSERT(bOK); return bOK; }
  BOOL                  Pause()                 { BOOL bOK=!IsPaused();  SetFlag(statePAUSED ); ASSERT(bOK); return bOK; }
  BOOL                  Resume()                { BOOL bOK= IsPaused();  ClrFlag(statePAUSED ); ASSERT(bOK); return bOK; }
  BOOL                  Stop()                  { BOOL bOK= IsActive();  ClrFlag(stateACTIVE ); ASSERT(bOK); return bOK; }
  BOOL                  Close()                 { BOOL bOK= IsOpened();  ClrFlag(stateOPENED ); ASSERT(bOK); return bOK; }
  BOOL                  Disable()               { BOOL bOK= IsEnabled(); ClrFlag(stateENABLED); ASSERT(bOK); return bOK; }

  BOOL                  Enable(BOOL bEnable)    { return  bEnable    ?Enable():Disable(); }
  BOOL                  ToggleEnable()          { return !IsEnabled()?Enable():Disable(); } //TO DO: make MT guarded

  BOOL                  Start(BOOL bStart)      { return  bStart    ?Start():Stop(); }
  BOOL                  ToggleActive()          { return !IsActive()?Start():Stop(); }      //TO DO: make MT guarded

  BOOL                  Pause(BOOL bPause)      { return  bPause    ?Pause():Resume(); }
  BOOL                  TogglePause()           { return !IsPaused()?Pause():Resume(); }    //TO DO: make MT guarded

  int                   FireEvent(int nEvent=1);
  BOOL                  TryEvent(int nEvent=1) const;
  BOOL                  IsEvent(BOOL bReset=FALSE, int nEvent=1);
  void                  ResetEvents();

public: //helpers
  BOOL                  SpinCycle(BOOL bReset=FALSE);
  BOOL                  SetFlag(int flag);
  BOOL                  ClrFlag(int flag);
  BOOL                  HasFlag(int flag) const;
public: //debug helpers
  const char*           ideDump() const;

protected:
  volatile mutable LONG m_ObjectState;
  volatile mutable LONG m_ObjectEvent;//non-message single event
};//YObjectState

inline BOOL YObjectState::SpinCycle(BOOL bReset)
{
  static volatile LONG s_nSpinCycles = 0;
  int    nSpinCycles = s_nSpinCycles;
  if(bReset) { 
    if(nSpinCycles) 
      TRACE(_T("\nYObjectState: *** %d spin cycles ***\n")); 
    nSpinCycles = s_nSpinCycles = 0; 
  }else{ 
    ::Sleep(0); 
    nSpinCycles = ::InterlockedIncrement((LONG*)&s_nSpinCycles);
    if(nSpinCycles==0) //override integer owerflow: force TRUE answer always
      nSpinCycles = 1; 
  }
  return nSpinCycles!=0;
}

inline BOOL YObjectState::HasFlag(int flag) const
{
  return (m_ObjectState&flag)!=0;
}

inline BOOL YObjectState::SetFlag(int flag)
{
  do{
    LONG old = m_ObjectState;
    LONG now = old | LONG(flag);
    if(old==(LONG)::InterlockedCompareExchange((PVOID*)&m_ObjectState,(PVOID)now,(PVOID)old))
      return TRUE;//ok
  }while(SpinCycle());//spin locking!  //TO DO: implement max retries?
  return FALSE;
}

inline BOOL YObjectState::ClrFlag(int flag)
{
  do{
    LONG old = m_ObjectState;
    LONG now = old & ~LONG(flag);
    if(old==(LONG)::InterlockedCompareExchange((PVOID*)&m_ObjectState,(PVOID)now,(PVOID)old))
      return TRUE;//ok
  }while(SpinCycle());//spin locking!  //TO DO: implement max retries?
  return FALSE;
}


inline int  YObjectState::FireEvent(int nEvent)//ret old state
{ 
  return ::InterlockedExchange((LONG*)&m_ObjectEvent, nEvent);
}
inline BOOL YObjectState::TryEvent(int nEvent) const
{
  return nEvent==m_ObjectEvent;
}
inline BOOL YObjectState::IsEvent(BOOL bReset, int nEvent)
{ 
  if(bReset)
    return ::InterlockedExchange((LONG*)&m_ObjectEvent,0)==nEvent;
  return nEvent==m_ObjectEvent;
}
inline void YObjectState::ResetEvents()
{
  m_ObjectEvent = 0;
}


/* to see:
  BOOL                  IsStoped() const        { return (m_ObjectState&stateACTIVE)==0; }
  BOOL                  IsClosed() const        { return (m_ObjectState&stateOPENED)==0; }
*/

#endif//__YOBJECTSTATE_H
#pragma once
