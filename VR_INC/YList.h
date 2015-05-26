#ifndef __YLIST_H
#define __YLIST_H

#include "xCSyncOb.h"
#include "xCExcept.h"

///////////////////////////////////////////////////////////////////////////////////
template <class T> class YHierarhyItem;
template <class T> class YHierarhyItemExt;
template <class T> class YHierarhyIterator;
///////////////////////////////////////////////////////////////////////////////////
// YHierarhyItem : list of any number of parents or childs. 
// Buddies is not send messages one to one?
/*
  A    B    A----B    A  B  C    A---B---C                                  Parents
   \  /  => |          \ | /  => |
    \/      |           \|/      |       
     1      1            1       1                                          Childs

     A      A            A       A                                          Parents
    /\      |           /|\      |       
   /  \  => |          / | \  => |
  1    2    1----2    1  2  3    1---2---3                                  Childs

   A  B     A---B
  /|\/|\ => |         (partially supported)
 / |/\| \   |         
1  2  3  4  1---2---3--4
*/

template <class T> 
class YHierarhyItem // hi // this is multi inheritable class, T - pointer
{ // operator YHierarhyItem*(T) must be defined!
public:
  typedef CGuardPtr<T>       YHierarhyItemPtr;
  typedef CGuardPtrConst<T>  constYHierarhyItemPtr;
protected:
  CArrayGuard*          m_pcsGuard;
  T*                    m_pThis;//volatile
  YHierarhyItem<T>*     m_pParent;//volatile
  YHierarhyItem<T>*     m_pChild;//volatile 
  YHierarhyItem<T>*     m_pBuddy;//volatile
  YHierarhyItem<T>*     m_pPrevBuddy;//volatile
public:
                        YHierarhyItem(T* pThis, CArrayGuard* pcsGuard);// build owner of list, if NULL - unprotected
                        YHierarhyItem(T* pThis=NULL, YHierarhyItem<T>* pParent=NULL, YHierarhyItem<T>* pBuddy=NULL, YHierarhyItem<T>* pChild=NULL);
                        ~YHierarhyItem();
  int                   Create(T* pThis, CArrayGuard* pcsGuard); // create owner of list
  int                   AddParent(YHierarhyItem<T>* pParent,BOOL bAddToAllBuddies=FALSE, DWORD dwTimeout=INFINITE);
  int                   AddChild(YHierarhyItem<T>* pChild,BOOL bAddToAllBuddies=FALSE, DWORD dwTimeout=INFINITE);
  int                   AddBuddy(YHierarhyItem<T>* pBuddy, DWORD dwTimeout=INFINITE);
  int                   Delete(DWORD dwTimeout=INFINITE);

  int                   AttachParent(YHierarhyItem<T>* pParent,BOOL bAttachToAllBuddies=FALSE, DWORD dwTimeout=INFINITE);
  int                   AttachChild(YHierarhyItem<T>* pChild,BOOL bAttachToAllBuddies=FALSE, DWORD dwTimeout=INFINITE);
  int                   AttachBuddy(YHierarhyItem<T>* pBuddy,BOOL bAttachParents=FALSE, BOOL bAttachChilds=FALSE, DWORD dwTimeout=INFINITE);
  int                   DetachParent(YHierarhyItem<T>* pParent,BOOL bDetachFromAllBuddies=FALSE, DWORD dwTimeout=INFINITE);
  int                   DetachChild(YHierarhyItem<T>* pChild,BOOL bDetachFromAllBuddies=FALSE, DWORD dwTimeout=INFINITE);
  int                   DetachBuddy(YHierarhyItem<T>* pBuddy,BOOL bDetachParents=FALSE, BOOL bDetachChilds=FALSE, DWORD dwTimeout=INFINITE);

  constYHierarhyItemPtr GetHierarhyItem() const // this
                                          { 
                                            return constYHierarhyItemPtr(&m_pThis, m_pcsGuard);
                                          }
  constYHierarhyItemPtr GetHierarhyBuddy() const// first buddy
                                          {
                                            CGuardPtrConst<T> lock(&m_pThis,m_pcsGuard);//locking
                                            const YHierarhyItem<T>* p = m_pBuddy;
                                            return constYHierarhyItemPtr( (p!=NULL ? &(p->m_pThis) : NULL),m_pcsGuard);
                                          }
  constYHierarhyItemPtr GetHierarhyChild() const  // first child
                                          {
                                            CGuardPtrConst<T> lock(&m_pThis,m_pcsGuard);//locking
                                            const YHierarhyItem<T>* p = m_pChild;
                                            return constYHierarhyItemPtr( (p!=NULL ? &(p->m_pThis) : NULL),m_pcsGuard);
                                          }
  constYHierarhyItemPtr GetHierarhyParent() const // first parent
                                          {
                                            CGuardPtrConst<T> lock(&m_pThis,m_pcsGuard);//locking
                                            const YHierarhyItem<T>* p = m_pParent;
                                            return constYHierarhyItemPtr( (p!=NULL ? &(p->m_pThis) : NULL),m_pcsGuard);
                                          }
  constYHierarhyItemPtr GetHierarhyRoot() const
                                          {
                                            CGuardPtrConst<T> lock(&m_pThis,m_pcsGuard);//locking
                                            const YHierarhyItem<T>* pRoot = _GetHierarhyRoot();
                                            return constYHierarhyItemPtr( (pRoot!=NULL ? &(pRoot->m_pThis) : NULL),m_pcsGuard);
                                          }

  YHierarhyItemPtr      GetHierarhyItem() // this
                                          { 
                                            return YHierarhyItemPtr(&m_pThis, m_pcsGuard);
                                          }
  YHierarhyItemPtr      GetHierarhyBuddy() // first buddy
                                          {
                                            CGuardPtr<T> lock(&m_pThis,m_pcsGuard);//locking
                                            YHierarhyItem<T>* p = m_pBuddy;
                                            return YHierarhyItemPtr( (p!=NULL ? &(p->m_pThis) : NULL),m_pcsGuard);
                                          }
  YHierarhyItemPtr      GetHierarhyChild()  // first child
                                          {
                                            CGuardPtr<T> lock(&m_pThis,m_pcsGuard);//locking
                                            YHierarhyItem<T>* p = m_pChild;
                                            return YHierarhyItemPtr( (p!=NULL ? &(p->m_pThis) : NULL),m_pcsGuard);
                                          }
  YHierarhyItemPtr      GetHierarhyParent() // first parent
                                          {
                                            CGuardPtr<T> lock(&m_pThis,m_pcsGuard);//locking
                                            YHierarhyItem<T>* p = m_pParent;
                                            return YHierarhyItemPtr( (p!=NULL ? &(p->m_pThis) : NULL),m_pcsGuard);
                                          }
  YHierarhyItemPtr      GetHierarhyRoot()
                                          {
                                            CGuardPtr<T> lock(&m_pThis,m_pcsGuard);//locking
                                            YHierarhyItem<T>* pRoot = _GetHierarhyRoot();
                                            return YHierarhyItemPtr( (pRoot!=NULL ? &(pRoot->m_pThis) : NULL),m_pcsGuard);
                                          }

  YHierarhyItemPtr      FindHierarhyParentItem(const T* pParentItem)
                                          {
                                            for(YHierarhyIterator<T> itr(this,YHierarhyIterator<T>::PARENTS); itr!=NULL; ++itr)
                                              if(&*itr == pParentItem)
                                                return YHierarhyItemPtr(itr._GetThis(),m_pcsGuard);
                                            return YHierarhyItemPtr();
                                          }
  YHierarhyItemPtr      FindHierarhyChildItem(const T* pChildItem)
                                          {
                                            for(YHierarhyIterator<T> itr(this,YHierarhyIterator<T>::CHILDS); itr!=NULL; ++itr)
                                              if(&*itr == pChildItem)
                                                return YHierarhyItemPtr(itr._GetThis(),m_pcsGuard);
                                            return YHierarhyItemPtr();
                                          }

  YHierarhyIterator<T>  GetHierarhyItems();  // this
  YHierarhyIterator<T>  GetHierarhyBuddies(); //all buddies exclude this
  YHierarhyIterator<T>  GetHierarhyChilds(); //all childs: child and its buddies
  YHierarhyIterator<T>  GetHierarhyParents(); //immediate parents
  YHierarhyIterator<T>  GetHierarhyGrands(); //immediate parent->grandparent->grandgrandparent...
  YHierarhyIterator<T>  GetHierarhyRoots(); //
protected: // helpers
  int                   LockArray(DWORD dwTimeout=INFINITE);
  int                   UnlockArray(DWORD dwTimeout=INFINITE);
  int                   _AddBuddy(YHierarhyItem<T>* pBuddy, DWORD dwTimeout=INFINITE);
  const YHierarhyItem<T>* _GetHierarhyRoot() const;
  const YHierarhyItem<T>* _GetHierarhyRootBuddy() const;
  const YHierarhyItem<T>* _GetHierarhyLastBuddy() const;
  YHierarhyItem<T>*     _GetHierarhyRoot();
  YHierarhyItem<T>*     _GetHierarhyRootBuddy();
  YHierarhyItem<T>*     _GetHierarhyLastBuddy();
  YHierarhyItem<T>*     _GetHierarhyLastTwin(YHierarhyItem<T>* pBuddy);
  BOOL                  _CheckParents(YHierarhyItem<T>* pChild);
  BOOL                  _CheckChilds(YHierarhyItem<T>* pParent);
  BOOL                  _CheckParentsOnNULL();
  BOOL                  _CheckChildsOnNULL();
  int                   _CorrectParents(YHierarhyItem<T>* pNewChild);
  int                   _CorrectChilds(YHierarhyItem<T>* pNewParent);
  int                   _DetachFromBuddies();

  int                   _AttachBuddy(YHierarhyItem<T>* pBuddy, DWORD dwTimeout=INFINITE);
public: // dump support
  void                  DumpHierarhyItem();
  static void           DumpHierarhyList(YHierarhyItem<T>* pItem, int nLevel=-1, BOOL bSplit=FALSE);
  void                  DumpItem(int nLevel=-1) const;
  void                  DumpList(const YHierarhyItem<T>* pItem=NULL, int nLevel=-1) const;
//LPCTSTR               GetHierarhyItemName() const; must be defined for dump

  friend class  YHierarhyIterator<T>;
  friend class  YHierarhyItemExt<T>;
};

///////////////////////////////////////////////////////////////////////////////////
// YHierarhyIterator

template <class T>
class YHierarhyIterator//typedef CGuardPtr<YHierarhyItem<T>*> YParent;
{
public: enum { PARENTS=1, CHILDS=2, BUDDIES=3, GRANDS=4, ROOTS=5 };
public: //construction / destruction
                        YHierarhyIterator(YHierarhyItem<T>* pItem, int nDirection=BUDDIES);
                        ~YHierarhyIterator();
                        YHierarhyIterator(const YHierarhyIterator<T>& itr);
  int                   Reset(int nDirection=0);// move iterator to start item
  YHierarhyIterator<T>& operator = (const YHierarhyIterator& itr);
public: // operators (pointer like)
  YHierarhyIterator<T>  operator ++ (int); //postfix
  YHierarhyIterator<T>  operator -- (int); //postfix
  YHierarhyIterator<T>& operator ++ ();  //prefix
  YHierarhyIterator<T>& operator -- ();  //prefix
  YHierarhyIterator<T>& operator += (int nDistance); // next buddy
  YHierarhyIterator<T>& operator -= (int nDistance); // prev buddy

  YHierarhyIterator<T>& operator >>=(int nDistance); // next buddy  //nDirection independent
  YHierarhyIterator<T>& operator <<=(int nDistance); // prev buddy  //nDirection independent
  YHierarhyIterator<T>& operator /= (int nDistance); // parent      //nDirection independent
  YHierarhyIterator<T>& operator %= (int nDistance); // child       //nDirection independent

  YHierarhyIterator<T>  operator >> (int nDistance) const; // next buddy  //nDirection independent
  YHierarhyIterator<T>  operator << (int nDistance) const; // prev buddy  //nDirection independent
  YHierarhyIterator<T>  operator /  (int nDistance) const; // parent      //nDirection independent
  YHierarhyIterator<T>  operator %  (int nDistance) const; // child       //nDirection independent

  BOOL                  operator == (const YHierarhyIterator<T>& itr) const;
  BOOL                  operator != (const YHierarhyIterator<T>& itr) const;
  BOOL                  IsTwin(const YHierarhyIterator<T>& itr) const; // same childs and parents
  BOOL                  IsBrat(const YHierarhyIterator<T>& itr) const; // buddy from another owner

public: // operators (pointer like compare)
  BOOL                  operator == (const YHierarhyItem<T>* pItem) const;
  BOOL                  operator != (const YHierarhyItem<T>* pItem) const;
  //                    operator YHierarhyItem<T>*() const;           //Internal Compiler Error!
  BOOL                  IsTwin(const YHierarhyItem<T>* pItem) const; // same childs and parents
  BOOL                  IsBrat(const YHierarhyItem<T>* pItem) const; // buddy from another owner
  YHierarhyItem<T>*     _GetItem() const; // without locking!
public: // operators (contents access)
  T*                    operator -> () const;       // special future!
  //                    operator T* () const;       // special future!  Internal Compiler Error!
  T&                    operator *  () const;       // special future!
  T&                    operator [] (int i) const;  // special future!
  T*                    _GetThis() const; // without locking!
protected:
  int                   m_nDirection;
  YHierarhyItem<T>*     m_pStart;   // start of moving
  YHierarhyItem<T>*     m_pItem;    // position of moving
  CGuardPtr<T>          m_pLock;    // locking
};

//for(YHierarhyIterator<P> p(this); p!=NULL; ++p)
//  p->OnData(...);

#include "YList.inl"

#ifdef _DEBUG
  int YHierarhyItem_CString_TEST();
#endif

#endif//__YLIST_H
#pragma once
