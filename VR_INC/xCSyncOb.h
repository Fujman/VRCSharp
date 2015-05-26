#ifndef __XCSYNCOB_H
#define __XCSYNCOB_H
#include <afxmt.h>

#pragma warning(disable:4284)//#pragma warning(once:4284)

/////////////////////////////////////////////////////////////////////////////////////
// CSignalEvent (CSingleLock compatible)
//
// main thread:
//    CSignalEvent.Start()  // start signal processing in worker thread
//    CSignalEvent.Wait()   // wait on finishing of signal processing in worker thread 
//
// worker thread:
//    while( !CSignalEvent )// check if signal present // while( !CSignalEvent.IsStarted() )
//      ...process...
//    CSignalEvent.Stop();  // finish the signal processing

class CSignalEvent : public CEvent
{
  int m_isExistBeforeConstruct;
  int m_isStarted;
public:
  HANDLE GetHandle()
    { return (HANDLE)*this; }
  int IsSuspend()// check in control process
    { return Lock(0); }
  int IsStarted() // check in worker process
    { return m_isStarted; }
  int Start() // call from control process
    { return m_isStarted=TRUE; }
  int Stop()  // call from worker process
    { return SetEvent(); }
  int Wait(DWORD dwTimeout = INFINITE) // call from control process
    { return (m_isStarted ? Lock(dwTimeout) : TRUE); }
  int Reset()
    { return ResetEvent(), m_isStarted=FALSE; }
public:
  CSignalEvent( BOOL bInitialActive=FALSE, LPCTSTR lpszName = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL ):
    CEvent(TRUE,TRUE,lpszName,lpsaAttribute)
  {
    // not tested!
    m_isExistBeforeConstruct = lpszName!=NULL && (::GetLastError()==ERROR_ALREADY_EXISTS);
    Reset();
    if(bInitialActive)
      Start();
  }
  BOOL operator!()
    { return !IsStarted(); }
  operator BOOL()
    { return IsStarted(); }
};


/////////////////////////////////////////////////////////////////////////////////////
// CLockEvent
class CLockEvent
{
  int     m_isExistBeforeConstruct;
  HANDLE  m_hEvent;
  CString m_szName;
public:
  BOOL Lock( DWORD dwTimeout = INFINITE ) {
    DWORD dwRet = ::WaitForSingleObject(m_hEvent,dwTimeout);
    if(dwRet==WAIT_TIMEOUT)
      return 0; // lock failure
    if(dwRet==WAIT_OBJECT_0)
      return 1; // lock ok
    return 0;   // common failure
  }

  BOOL Unlock() {
    DWORD dwRet = ::SetEvent(m_hEvent);
    if(dwRet==0)
      return 0; // failure
    return 1;   // unlock ok
  }

  BOOL IsLocked() {
    DWORD dwRet = ::WaitForSingleObject(m_hEvent,0);
    if(dwRet==WAIT_TIMEOUT)
      return 1; // locked
    if(dwRet==WAIT_OBJECT_0) {
      BOOL bRet = Unlock();
      if(bRet==FALSE)
        return 1; // still locked - unlock failure
      return 0; // is not locked
    }
    return -1; // failure
  }
public:
  CLockEvent( LPCTSTR lpszName=NULL, BOOL bInitialLocked=FALSE, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL )
  {
    m_hEvent = ::CreateEvent(
      lpsaAttribute,      // pointer to security attributes
      FALSE,              // flag for manual-reset event
      !bInitialLocked,    // TRUE=unlocked    // flag for initial state
      lpszName            // pointer to event-object name
    );
    m_isExistBeforeConstruct = lpszName!=NULL && (::GetLastError()==ERROR_ALREADY_EXISTS);
    if(lpszName!=NULL)
      m_szName = lpszName;
    //ASSERT(m_hEvent!=NULL); //AY commented 13.01.2012
  }
  int IsAttached()
    { return m_isExistBeforeConstruct; }
};

/////////////////////////////////////////////////////////////////////////////////////
// CArrayGuard : Single write and multi read critical section analog (CSingleLock compatible)
// Lock(dwTimeout)/Unlock()           - read guard, timeout ignored
// LockWrite(dwTimeout)/UnlockWrite() - write guard
//   (wait on end of writting operation is infinite, on reading operations - by timeout)
class CArrayGuard : public CSyncObject
{
  volatile LONG         m_nReadLockCount;//-1:write, 0:free, >0:read operations
  CEvent                ev;
  CCriticalSection      cs;
public:
  CArrayGuard():
    CSyncObject(NULL),
    ev(TRUE,TRUE,NULL,NULL)//manual reset
  {
    m_nReadLockCount = 0;
    m_hObject = cs.m_hObject;
  }

	virtual BOOL Lock(DWORD /*dwTimeout=INFINITE*/) { // parameter ignored
    cs.Lock();
    ++m_nReadLockCount; ASSERT(m_nReadLockCount>0);   //still locked
    cs.Unlock(); 
    return TRUE;
  }
	virtual BOOL Unlock() {
    cs.Lock();
    if(m_nReadLockCount==0)
      { ASSERT(!"programmer error: unlock in non-locked state"); cs.Unlock(); return FALSE; }
    --m_nReadLockCount; ASSERT(m_nReadLockCount>=0);  //unlock
    if(m_nReadLockCount==0)
      ev.SetEvent();
    cs.Unlock(); 
    return TRUE;
  }
	virtual BOOL RelockArray(DWORD dwTimeout=INFINITE) {  //LockArray + Unlock
    cs.Lock();
    if(m_nReadLockCount==0)
      { ASSERT(!"programmer error: unlock in non-locked state"); cs.Unlock(); return FALSE; }
    while(m_nReadLockCount>1) {//need wait
      ev.ResetEvent();
      cs.Unlock();
      if(!ev.Lock(dwTimeout))
        return FALSE;
      cs.Lock();
      if(m_nReadLockCount>1 && dwTimeout!=INFINITE)
        { cs.Unlock(); return FALSE; } // failure
    }
    --m_nReadLockCount;
    --m_nReadLockCount; ASSERT(m_nReadLockCount==-1); //still array locked
    return TRUE;
  }
 	virtual BOOL LockArray(DWORD dwTimeout=INFINITE){ // wait of UnlockWrite - infinite, of Unlock - by timeout
    cs.Lock();
    while(m_nReadLockCount>0) {//need wait
      ev.ResetEvent();
      cs.Unlock();
      if(!ev.Lock(dwTimeout))
        return FALSE;
      cs.Lock();
      if(m_nReadLockCount>0 && dwTimeout!=INFINITE)
        { cs.Unlock(); return FALSE; } // failure
    }
    --m_nReadLockCount; ASSERT(m_nReadLockCount==-1); //still array locked
    return TRUE;
  }
	virtual BOOL UnlockArray() {
    if(m_nReadLockCount>=0)
      { ASSERT(!"programmer error: unlock array in non-locked state"); return FALSE; }
    ++m_nReadLockCount; ASSERT(m_nReadLockCount==0);  //unlock
    ev.SetEvent();//if another array modifier wait
    cs.Unlock();
    return TRUE;
  }
	virtual BOOL Relock() { //Lock + UnlockArray
    if(m_nReadLockCount>=0)
      { ASSERT(!"programmer error: unlock array in non-locked state"); return FALSE; }
    ++m_nReadLockCount;
    ++m_nReadLockCount; ASSERT(m_nReadLockCount==1);  //still locked
    cs.Unlock();
    return TRUE;
  }
  BOOL IsLocked()
    { return m_nReadLockCount!=0; }
  BOOL InArrayLocked()
    { return m_nReadLockCount<=0; }

};

/////////////////////////////////////////////////////////////////////////////////////
// CGuardedPtr
template <class TYPE>
class CGuardPtrConst;

template <class TYPE>
class CGuardPtr
{
protected: // types
  typedef CGuardPtr<TYPE> CThis;
protected: // members
  TYPE*         m_pPointer;
  CSyncObject*  m_pSyncObject;//recomended CSyncObject that support multilocking, such as CArrayGuard or CSemaphore!
protected: // helpers
  int _lock()   { return m_pSyncObject ? m_pSyncObject->Lock() : 1; }
  int _unlock() { return m_pSyncObject ? m_pSyncObject->Unlock() : 1; }

public: // construction / destruction
  CGuardPtr()
    { m_pPointer = NULL; m_pSyncObject = NULL; } // make null pointer
  ~CGuardPtr()
    { _unlock(); }
//CGuardPtr(TYPE** ppPointer, CSyncObject* pSyncObject) //ERROR:owner must be locked first, pointers from owner obtained second!
//  { m_pPointer = *pPointer; m_pSyncObject = pSyncObject; _lock(); } // error implementation!
  CGuardPtr(TYPE** ppPointer, CSyncObject* pSyncObject)
    { m_pSyncObject = pSyncObject; _lock(); m_pPointer = (ppPointer?*ppPointer:NULL); }
  CGuardPtr(TYPE* pPointer, CSyncObject* pSyncObject) // may be used only if pPointer and *pSyncObject objects exists and modified strongly sinchroniously
    { m_pSyncObject = pSyncObject; _lock(); m_pPointer = pPointer; } // pPointer must be constant during this function call!
  CGuardPtr(const CThis& ptr)
    { m_pSyncObject = ptr.m_pSyncObject; _lock(); m_pPointer = ptr.m_pPointer; }

public: // operators (pointer like)
  CThis& operator = (const CThis& ptr)
    { _unlock(); m_pSyncObject = ptr.m_pSyncObject; _lock(); m_pPointer = ptr.m_pPointer; return *this; }

  CThis operator ++ (int) { ASSERT(m_pPointer+1!=NULL); //postfix 
                                        return CThis(m_pPointer++,m_pSyncObject); }
  CThis operator -- (int) { ASSERT(m_pPointer-1!=NULL); //postfix 
                                        return CThis(m_pPointer--,m_pSyncObject); }
  CThis& operator ++ () { ASSERT(m_pPointer+1!=NULL); //prefix 
                                        ++m_pPointer; return *this; }
  CThis& operator -- () { ASSERT(m_pPointer-1!=NULL); //prefix 
                                        --m_pPointer; return *this; }

  CThis& operator += (int nIncrease) { ASSERT(m_pPointer+nIncrease!=NULL);
                                        m_pPointer += nIncrease; return *this; }
  CThis& operator -= (int nIncrease) { ASSERT(m_pPointer-nIncrease!=NULL);
                                        m_pPointer -= nIncrease; return *this; }
  CThis operator + (int nIncrease) const { ASSERT(m_pPointer+nIncrease!=NULL);
                                        return CThis(m_pPointer+nIncrease, m_pSyncObject); }
  CThis operator - (int nIncrease) const { ASSERT(m_pPointer-nIncrease!=NULL);
                                        return CThis(m_pPointer-nIncrease, m_pSyncObject); }

  int operator - (const CThis& ptr) const
                                        { return m_pPointer - ptr.m_pPointer; }
  BOOL operator>(const CThis& ptr) const
                                        { return m_pPointer > ptr.m_pPointer; }
  BOOL operator<(const CThis& ptr) const
                                        { return m_pPointer < ptr.m_pPointer; }
  BOOL operator>=(const CThis& ptr) const
                                        { return m_pPointer >= ptr.m_pPointer; }
  BOOL operator<=(const CThis& ptr) const
                                        { return m_pPointer <= ptr.m_pPointer; }
  BOOL operator==(const CThis& ptr) const
                                        { return m_pPointer == ptr.m_pPointer; }
  BOOL operator!=(const CThis& ptr) const
                                        { return m_pPointer != ptr.m_pPointer; }

  int operator - (const TYPE* ptr) const
                                        { return m_pPointer - ptr; }
  BOOL operator>(const TYPE*  ptr) const
                                        { return m_pPointer > ptr; }
  BOOL operator<(const TYPE*  ptr) const
                                        { return m_pPointer < ptr; }
  BOOL operator>=(const TYPE*  ptr) const
                                        { return m_pPointer >= ptr; }
  BOOL operator<=(const TYPE*  ptr) const
                                        { return m_pPointer <= ptr; }
  BOOL operator==(const TYPE*  ptr) const
                                        { return m_pPointer == ptr; }
  BOOL operator!=(const TYPE*  ptr) const
                                        { return m_pPointer != ptr; }
public: // operators (contents access)
               operator TYPE*() const
                                        { return m_pPointer; }
  TYPE*        operator->() const
                                        { return m_pPointer; }
  TYPE&        operator *() const
                                        { return *m_pPointer; }
  TYPE&        operator[](int i) const
                                        { return m_pPointer[i]; }
  friend class CGuardPtrConst<TYPE>;
};

/////////////////////////////////////////////////////////////////////////////////////
// CGuardPtrConst
template <class TYPE>
class CGuardPtrConst
{
protected: // types
  typedef CGuardPtrConst<TYPE> CThis;
  typedef const TYPE*         PCTYPE;
protected: // members
  PCTYPE  m_pPointer;
  CSyncObject*  m_pSyncObject;//recomended CSyncObject that support multilocking, such as CArrayGuard or CSemaphore!
protected: // helpers
  int _lock()   { return m_pSyncObject ? m_pSyncObject->Lock() : 1; }
  int _unlock() { return m_pSyncObject ? m_pSyncObject->Unlock() : 1; }

public: // construction / destruction
  CGuardPtrConst()
    { m_pPointer = NULL; m_pSyncObject = NULL; } // make null pointer
  ~CGuardPtrConst()
    { _unlock(); }
//CGuardPtrConst(PCTYPE* ppPointer, CSyncObject* pSyncObject) //ERROR:owner must be locked first, pointers from owner obtained second!
//  { m_pPointer = *pPointer; m_pSyncObject = pSyncObject; _lock(); } // error implementation!
  CGuardPtrConst(const PCTYPE* ppPointer, CSyncObject* pSyncObject)
    { m_pSyncObject = pSyncObject; _lock(); m_pPointer = (ppPointer?*ppPointer:NULL); }
  CGuardPtrConst(PCTYPE pPointer, CSyncObject* pSyncObject) // may be used only if pPointer and *pSyncObject objects exists and modified strongly sinchroniously
    { m_pSyncObject = pSyncObject; _lock(); m_pPointer = pPointer; } // pPointer must be constant during this function call!
  CGuardPtrConst(const CThis& ptr)
    { m_pSyncObject = ptr.m_pSyncObject; _lock(); m_pPointer = ptr.m_pPointer; }
  CGuardPtrConst(const CGuardPtr<TYPE>& ptr) //AY 20.01.2011 OLD: const CGuardPtr& ptr
    { m_pSyncObject = ptr.m_pSyncObject; _lock(); m_pPointer = ptr.m_pPointer; }

public: // operators (pointer like)
  CThis& operator = (const CThis& ptr)
    { _unlock(); m_pSyncObject = ptr.m_pSyncObject; _lock(); m_pPointer = ptr.m_pPointer; return *this; }

  CThis operator ++ (int) { ASSERT(m_pPointer+1!=NULL); //postfix 
                                        return CThis(m_pPointer++,m_pSyncObject); }
  CThis operator -- (int) { ASSERT(m_pPointer-1!=NULL); //postfix 
                                        return CThis(m_pPointer--,m_pSyncObject); }
  CThis& operator ++ () { ASSERT(m_pPointer+1!=NULL); //prefix 
                                        ++m_pPointer; return *this; }
  CThis& operator -- () { ASSERT(m_pPointer-1!=NULL); //prefix 
                                        --m_pPointer; return *this; }

  CThis& operator += (int nIncrease) { ASSERT(m_pPointer+nIncrease!=NULL);
                                        m_pPointer += nIncrease; return *this; }
  CThis& operator -= (int nIncrease) { ASSERT(m_pPointer-nIncrease!=NULL);
                                        m_pPointer -= nIncrease; return *this; }
  CThis operator + (int nIncrease) const { ASSERT(m_pPointer+nIncrease!=NULL);
                                        return CThis(m_pPointer+nIncrease, m_pSyncObject); }
  CThis operator - (int nIncrease) const { ASSERT(m_pPointer-nIncrease!=NULL);
                                        return CThis(m_pPointer-nIncrease, m_pSyncObject); }

  int operator - (const CThis& ptr) const
                                        { return m_pPointer - ptr.m_pPointer; }
  BOOL operator>(const CThis& ptr) const
                                        { return m_pPointer > ptr.m_pPointer; }
  BOOL operator<(const CThis& ptr) const
                                        { return m_pPointer < ptr.m_pPointer; }
  BOOL operator>=(const CThis& ptr) const
                                        { return m_pPointer >= ptr.m_pPointer; }
  BOOL operator<=(const CThis& ptr) const
                                        { return m_pPointer <= ptr.m_pPointer; }
  BOOL operator==(const CThis& ptr) const
                                        { return m_pPointer == ptr.m_pPointer; }
  BOOL operator!=(const CThis& ptr) const
                                        { return m_pPointer != ptr.m_pPointer; }

  int operator - (const TYPE* ptr) const
                                        { return m_pPointer - ptr; }
  BOOL operator>(const TYPE*  ptr) const
                                        { return m_pPointer > ptr; }
  BOOL operator<(const TYPE*  ptr) const
                                        { return m_pPointer < ptr; }
  BOOL operator>=(const TYPE*  ptr) const
                                        { return m_pPointer >= ptr; }
  BOOL operator<=(const TYPE*  ptr) const
                                        { return m_pPointer <= ptr; }
  BOOL operator==(const TYPE*  ptr) const
                                        { return m_pPointer == ptr; }
  BOOL operator!=(const TYPE*  ptr) const
                                        { return m_pPointer != ptr; }
public: // operators (contents access)
               operator TYPE*() const
                                        { return m_pPointer; }
  PCTYPE       operator->() const
                                        { return m_pPointer; }
  const TYPE&  operator *() const
                                        { return *m_pPointer; }
  const TYPE&  operator[](int i) const
                                        { return m_pPointer[i]; }
};

#endif//__XCSYNCOB_H
#pragma once
