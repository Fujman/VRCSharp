#ifndef __XCSYNCAR_H
#define __XCSYNCAR_H
#include <afxmt.h>

class  CSingleLockEx: public CSingleLock
{
public: CSingleLockEx(CSyncObject* pObject, DWORD dwTimeout=INFINITE)
          : CSingleLock(pObject, FALSE) { Lock(dwTimeout); }
};

template <class TELEM>
class CGuardStruct : protected TELEM
{
};

template <class TARRAY, class TELEM>
class CGuardElem
{
protected:
                      CSingleLockEx       m_lock;
                      TARRAY&             m_array;
                      int                 m_iElem;
                      TELEM*              m_pDef;

public:
                      CGuardElem(TARRAY& array, int iElem, CSyncObject& cs, TELEM* pDef, DWORD dwTimeout=INFINITE)
                        : m_array(array) 
                        , m_iElem(iElem)
                        , m_lock(&cs,dwTimeout)
                        , m_pDef(pDef) 
                      {}
//OLD REALIZATION:                      // Non-standard extension: write access to locked element  through -> instead .
//TELEM*              operator->()      // ATTENTION! Don't reassign TELEM { LPCTSTR m_as[]; } fields for the CStringStructArray objects!
//                                      { return &element(); }
  CGuardStruct<TELEM>*operator->()
                                        { return (CGuardStruct<TELEM>*) &element(); }

                      operator TELEM() const
                                        { return  element(); }
//const TELEM&        operator *() const// ?
//                                      { return  element(); }

  const TELEM&        operator =(const TELEM& ss) //non-standard extrnsion: read only result of operator=()
                      {
                        if(m_iElem>=0 && m_iElem<m_array.GetSize())
                          m_array.SetAt(m_iElem,ss);
                        return element();  
                      }
private:
  TELEM&              element() const
                      {
                        if(m_iElem>=0 && m_iElem<m_array.GetSize())
                          return m_array.ElementAt(m_iElem);
                        TRACE(DEBUGPLACE("ERROR: must be never reached!\n"));
                        return *m_pDef;
                      }
};

#endif//__XCSYNCAR_H
#pragma once
