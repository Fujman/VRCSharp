/*---------------------------------------------------------------------------\
| Name: XQSORT                             Language: C++     Model: All      |
|----------------------------------------------------------------------------|
| Description:  Extended sorting package                                     |
|                                                                            |
|   Warning! This storage can't be used for objects with binary copying      |
|   implementation of operator=                                              |
|                                                                            |
| Used Macro & Subroutines: qsort, bsearch, _lfind(non-ANSI)                 |
| Source:                                                                    |
| Notes:                                                                     |
\---Last change 18.06.00 19:11-----Copyright (c) 2000, Anton Yavorsky, KPI--*/
#ifndef __XQSORT_H
#define __XQSORT_H

#include <search.h>

template <class TYPE> class xcompareclass { public:
  static int  compare(const TYPE* e1, const TYPE* e2)
    { return( *e1==*e2 ? 0 : (*e1<*e2 ? -1: 1) ); }
};

template <class TYPE> inline int  xcompare(TYPE e1, TYPE e2)
  { return xcompareclass<TYPE>::compare(&e1,&e2); }

template <class TYPE> inline void xqsort(TYPE *base, size_t num)
  { ::qsort(base,num,sizeof(TYPE),(int (*)(const void *, const void *))xcompareclass<TYPE>::compare); }

template <class TYPE> inline TYPE* xsearch(TYPE key, const TYPE *base, unsigned int num) // NULL on error, pointer on success
  { return (TYPE*)::_lfind(&key,base,&num,sizeof(TYPE),(int (*)(const void *, const void *))xcompareclass<TYPE>::compare); }

template <class TYPE> inline size_t xsearch_index(TYPE key, const TYPE *base, unsigned int num) // -1 on error, index on success
  { TYPE* p = xsearch(key,base,num); return (p==NULL?-1:p-base); }

template <class TYPE> inline TYPE* xbsearch(TYPE key, const TYPE *base, unsigned int num) // NULL on error, pointer on success
  { return (TYPE*)::bsearch(&key,base,num,sizeof(TYPE),(int (*)(const void *, const void *))xcompareclass<TYPE>::compare); }

template <class TYPE> inline size_t xbsearch_index(TYPE key, const TYPE *base, unsigned int num) // -1 on error, index on success
  { TYPE* p = xbsearch(key,base,num); return (p==NULL?-1:p-base); }

template <class TYPE> size_t xbsearch_range(TYPE key, const TYPE *base, unsigned int num) {
  size_t left, right, middle;
  for(left=0,right=num-1; right-left > 1; ) {
    middle = (right+left) / 2;
    if(xcompareclass<TYPE>::compare(&key,base+middle)<0)
      right = middle;
    else
      left = middle;
  }
  return(left);
}

#define xqsortCArray(a)   xqsort(a.GetData(),a.GetSize()) // MFC specific
#define xbsearchCArray(x,a) xbsearch((x),a.GetData(),a.GetSize()) // MFC specific
#define xbsearch_indexCArray(x,a) xbsearch_index((x),a.GetData(),a.GetSize()) // MFC specific


//AY additions on 24.11.2004 - string compare support /////////////////////////
/* 
Note: for enable string sorting must be defined single of such macro variables:
  XQSORT_STRING_COMRARE_NO_CASE
  XQSORT_STRING_COLLATE_NO_CASE
  XQSORT_STRING_COMRARE
  XQSORT_STRING_COLLATE
*/

#ifdef  __XQSORT_STRING_COMRARE_NO_CASE
#pragma message("XQSORT.H: compare no case for strings used")
class xcompareclass<LPCTSTR>  { public:
  static int  compare(const LPCTSTR* e1, const LPCTSTR* e2)
    { return _tcsicmp(*e1,*e2); } };
class xcompareclass<LPTSTR>  { public:
  static int  compare(const LPCTSTR* e1, const LPCTSTR* e2)
    { return _tcsicmp(*e1,*e2); } };
class xcompareclass<CString*>  { public:
  static int  compare(const CString** e1, const CString** e2)
    { return (**e1).CompareNoCase(**e2); } };
class xcompareclass<CString>  { public:
  static int  compare(const CString* e1, const CString* e2)
    { return (*e1).CompareNoCase(*e2); } };
#endif//__XQSORT_STRING_COMRARE_NO_CASE

#ifdef  __XQSORT_STRING_COLLATE_NO_CASE
#pragma message("XQSORT.H: collate no case for strings used")
class xcompareclass<LPCTSTR>  { public:
  static int  compare(const LPCTSTR* e1, const LPCTSTR* e2)
    { return _tcsicoll(*e1,*e2); } };
class xcompareclass<LPTSTR>  { public:
  static int  compare(const LPCTSTR* e1, const LPCTSTR* e2)
    { return _tcsicoll(*e1,*e2); } };
class xcompareclass<CString*>  { public:
  static int  compare(const CString** e1, const CString** e2)
    { return (**e1).CollateNoCase(**e2); } };
#endif//__XQSORT_STRING_COLLATE_NO_CASE

#ifdef  __XQSORT_STRING_COMRARE
#pragma message("XQSORT.H: compare for strings used")
class xcompareclass<LPCTSTR>  { public:
  static int  compare(const LPCTSTR* e1, const LPCTSTR* e2)
    { return _tcscmp(*e1,*e2); } };
class xcompareclass<LPTSTR>  { public:
  static int  compare(const LPCTSTR* e1, const LPCTSTR* e2)
    { return _tcscmp(*e1,*e2); } };
class xcompareclass<CString*>  { public:
  static int  compare(const CString** e1, const CString** e2)
    { return (**e1).Compare(**e2); } };
class xcompareclass<CString>  { public:
  static int  compare(const CString* e1, const CString* e2)
    { return (*e1).Compare(*e2); } };
#endif//__XQSORT_STRING_COMRARE

#ifdef  __XQSORT_STRING_COLLATE
#pragma message("XQSORT.H: collate for strings used")
class xcompareclass<LPCTSTR>  { public:
  static int  compare(const LPCTSTR* e1, const LPCTSTR* e2)
    { return _tcscoll(*e1,*e2); } };
class xcompareclass<LPTSTR>  { public:
  static int  compare(const LPCTSTR* e1, const LPCTSTR* e2)
    { return _tcscoll(*e1,*e2); } };
class xcompareclass<CString*>  { public:
  static int  compare(const CString** e1, const CString** e2)
    { return (**e1).Collate(**e2); } };
class xcompareclass<CString>  { public:
  static int  compare(const CString* e1, const CString* e2)
    { return (*e1).Collate(*e2); } };
#endif//__XQSORT_STRING_COLLATE

//AY additions on 24.11.2004 - MFC collections support ////////////////////////
/*
  xqsort( CArray<*,*>& );

  xqsort(CStringArray& a);
  CMapStringToString__Sort(const CMapStringToString& as, CStringArray& aOrd);

  CMapStringToString__SortByKeys(const CMapStringToString& as, CArray<LPCTSTR,LPCTSTR>);
  CMapStringToPtr__SortByKeys(const CMapStringToPtr& as, CArray<LPCTSTR,LPCTSTR>);
  CMapStringToOb__SortByKeys(const CMapStringToOb& as, CArray<LPCTSTR,LPCTSTR>);

  CMap__SortByKeys(const CMap<*,*,X,Y>&, CArray<X,Y>& order);
  CMap__Sort(const CMap<*,*,X,Y>&, CArray<X,Y>& order);
*/

#ifdef  __AFXTEMPL_H__

template < class VALUE, class ARG_VALUE >
  inline void xqsort(CArray<VALUE,ARG_VALUE>& a)
    { xqsort(a.GetData(), a.GetSize()); }

#endif//__AFXTEMPL_H__
#if defined(__AFXCOLL_H__) && defined(__AFXTEMPL_H__)

inline void xqsort(CStringArray& a) //must be defined one of XQSORT_STRING_*
  { xqsort(a.GetData(), a.GetSize()); }

inline void CMapStringToString__Sort(const CMapStringToString& as, CStringArray& aOrd)
{
  aOrd.SetSize(as.GetCount());
  CString szIdx, szVal;
  POSITION pos=as.GetStartPosition();
  for(int i=0; i<as.GetCount(); ++i){
    as.GetNextAssoc(pos,szIdx,szVal);
    aOrd[i] = szVal;
  }
  xqsortCArray(aOrd);
}

template <class VALUE, class ARG_VALUE>
inline void CMapStringToString__SortByKeys(const CMapStringToString& as, CArray<VALUE,ARG_VALUE>& aOrd)
{
  aOrd.SetSize(as.GetCount());
  CString szIdx, szVal;
  LPCTSTR szKey = NULL;
  POSITION pos=as.GetStartPosition();
  for(int i=0; i<as.GetCount(); ++i){
    as.GetNextAssoc(pos,szIdx,szVal);
    as.LookupKey(szIdx,szKey);
    aOrd[i] = szKey;
  }
  xqsortCArray(aOrd);
}

template <class VALUE, class ARG_VALUE>
inline void CMapStringToOb__SortByKeys(const CMapStringToOb& as, CArray<VALUE,ARG_VALUE>& aOrd)
{
  aOrd.SetSize(as.GetCount());
  CString  szIdx; 
  CObject* szVal;
  LPCTSTR  szKey;
  POSITION pos=as.GetStartPosition();
  for(int i=0; i<as.GetCount(); ++i){
    as.GetNextAssoc(pos,szIdx,szVal);
    as.LookupKey(szIdx,szKey);
    aOrd[i] = szKey;
  }
  xqsortCArray(aOrd);
}

template <class VALUE, class ARG_VALUE>
inline void CMapStringToPtr__SortByKeys(const CMapStringToPtr& as, CArray<VALUE,ARG_VALUE>& aOrd)
{
  aOrd.SetSize(as.GetCount());
  CString  szIdx; 
  void*    szVal;
  LPCTSTR  szKey;
  POSITION pos=as.GetStartPosition();
  for(int i=0; i<as.GetCount(); ++i){
    as.GetNextAssoc(pos,szIdx,szVal);
    as.LookupKey(szIdx,szKey);
    aOrd[i] = szKey;
  }
  xqsortCArray(aOrd);
}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
inline void CMap__SortByKeys(const CMap<KEY,ARG_KEY,VALUE,ARG_VALUE>& as, CArray<KEY,ARG_KEY>& aOrd)
{
  aOrd.SetSize(as.GetCount());
  KEY   key;
  VALUE val;
  POSITION pos=as.GetStartPosition();
  for(int i=0; i<as.GetCount(); ++i){
    as.GetNextAssoc(pos,key,val);
    aOrd[i] = key;
  }
  xqsortCArray(aOrd);
}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
inline void CMap__Sort(const CMap<KEY,ARG_KEY,VALUE,ARG_VALUE>& as, CArray<KEY,ARG_KEY>& aOrd)
{
  aOrd.SetSize(as.GetCount());
  KEY   key;
  VALUE val;
  POSITION pos=as.GetStartPosition();
  for(int i=0; i<as.GetCount(); ++i){
    as.GetNextAssoc(pos,key,val);
    aOrd[i] = val;
  }
  xqsortCArray(aOrd);
}

#endif//__AFXCOLL_H__ && __AFXTEMPL_H__


#endif//__XQSORT_H
