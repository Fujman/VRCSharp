/*---------------------------------------------------------------------------\
| Name: YQSORT                             Language: C++     Model: All      |
|----------------------------------------------------------------------------|
| Description:  Extended sorting package                                     |
|                                                                            |
|   Warning! This storage can't be used for objects with binary copying      |
|   implementation of operator=                                              |
|                                                                            |
| Used Macro & Subroutines: yqsort, ybsearch, ylfind(non-ANSI)               |
| Source:                                                                    |
| Notes:                                                                     |
\---Last change 09.06.05 19:11-----Copyright (c) 2005, Anton Yavorsky, SRS--*/
#ifndef __YQSORT_H
#define __YQSORT_H

#include "xqsort.h"
#include <mbstring.h>

//C,C++///////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
#define _0 =0
extern "C" {
#endif
void  __cdecl y_qsort(void *base, unsigned num, unsigned width,
                int (__cdecl *compare)(const void *, const void *, void* ),void* data _0, unsigned cutoff _0);

void* __cdecl y_bsearch(const void *key, const void *base, size_t num, size_t width,
                int (__cdecl *compare)(const void *, const void *, void*),void* data _0);

void* __cdecl y_search(const void *key, const void *base, unsigned* num, unsigned width,
                int (__cdecl *compare)(const void *, const void *, void*),void* data _0);

void* __cdecl y_bsearch_range(int mode, const void *key, const void *base, size_t num, size_t width,
                int (__cdecl *compare)(const void *, const void *, void*),void* data _0);

#ifdef __cplusplus
}
#undef _0
#endif

#ifdef __cplusplus
//C++////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
// sorting types declaration by constants
// Usage example:
//   YCOMPARE_SPECIFIC(TYPE,YSORT<0>) {...}
//   yqsort(TYPE*, size_t, (YSORT<0>*)NULL);
// or
//   YSORT_DECLARE(S,0);//S-name,0-algorythm
//   YCOMPARE_SPECIFIC(TYPE,YSORT_S_) {...}
//   yqsort(TYPE*, size_t, YSORT_S);
// or
//   YSORT_DECLARE_SPECIFIC(S,CLASS,0){...}

template <int S0RT, class POBJ=void*> class YSORT { public: POBJ pObj; static int SORT; };

#define YSORT_DECLARE(NAME,S0RT)  typedef YSORT<S0RT> YSORT_##NAME##_; \
  __declspec(selectany) int YSORT<S0RT>::SORT = S0RT; \
  __declspec(selectany) YSORT<S0RT>* YSORT_##NAME=NULL;

#define YSORT_DECLARE_SPECIFIC(TYPE,NAME,S0RT)\
  YSORT_DECLARE(NAME,S0RT);\
  YCOMPARE_SPECIFIC(TYPE,YSORT<S0RT>)

/////////////////////////////////////////////////////////////////////////////////////////
// sorting routines

#define YQSORT_VOID ((yqsort_void*)NULL) //must be used as SORT for instrinsic types!
class   yqsort_void {void* unused_ptr;}; //if xcompare redefined, it will be used instead default implementation

#define YQSORT_BACK ((yqsort_back*)NULL) //may  be used as SORT for instrinsic types
class   yqsort_back {void* unused_ptr;}; //if xcompare redefined, it will be used instead default implementation

//class ycompareclass: default xqsort compatible implementation
template <class TYPE, class SORT> class ycompareclass
{ 
  public: static int compare(TYPE* e1, TYPE* e2, SORT sort)
    { return xcompareclass<TYPE>::compare(e1,e2); } //sort unused
};

//compare
//  int ycompare(const TYPE& e1, const TYPE& e2, SORT sort);//for objects
//  int ycompare(TYPE1* e1, TYPE2* e2, SORT sort);          //for pointers
template <class TYPE, class SORT> inline int  ycompare(const TYPE& e1, const TYPE& e2, SORT sort)
  { return ycompareclass<const TYPE, SORT>::compare(&e1,&e2,sort); }
template <class TYPE1, class TYPE2, class SORT> inline int  ycompare(TYPE1* e1, TYPE2* e2, SORT sort)
  { return ycompareclass<const TYPE1*,SORT>::compare((const TYPE1**)&e1,(const TYPE2**)&e2,sort); }

//sorting
//  void yqsort(const TYPE *base, size_t num, SORT sort);   //for objects
//  void yqsort(TYPE* *base, size_t num, SORT sort);        //for pointers
template <class TYPE, class SORT> inline void yqsort(const TYPE  *base, size_t num, SORT sort)
  { ::y_qsort((void*)base,num,sizeof(TYPE),(int (*)(const void *, const void *, void*))ycompareclass<const TYPE,SORT>::compare, (void*)sort); }
template <class TYPE, class SORT> inline void yqsort(TYPE* *base, size_t num, SORT sort)
  { ::y_qsort((void*)base,num,sizeof(TYPE*),(int (*)(const void *, const void *, void*))ycompareclass<const TYPE*,SORT>::compare, (void*)sort); }

//search
//  const TYPE* ysearch (const TYPE& key, const TYPE *base, unsigned num, SORT sort)  //for objects
//  TYPE2*      ysearch (TYPE1* key, TYPE2 *base, unsigned num, SORT sort)            //for pointers
//  const TYPE* ybsearch(const TYPE& key, const TYPE *base, unsigned num, SORT sort) //for objects
//  TYPE2*      ybsearch(TYPE1* key, TYPE2 *base, unsigned num, SORT sort)           //for pointers
template <class TYPE, class SORT> inline const TYPE* ysearch(const TYPE& key, const TYPE *base, unsigned num, SORT sort) // NULL on error, pointer on success
  { return (TYPE*)::y_search((const void*)&key,(const void*)base,&num,sizeof(TYPE),(int (*)(const void *, const void *, void*))ycompareclass<const TYPE,SORT>::compare, (void*)sort); }
template <class TYPE1, class TYPE2, class SORT> inline TYPE2* ysearch(TYPE1* key, TYPE2 *base, unsigned num, SORT sort) // NULL on error, pointer on success
  { return (TYPE2*)::y_search((const void*)(const TYPE1**)&key,(const void*)base,&num,sizeof(TYPE1*),(int (*)(const void *, const void *, void*))ycompareclass<const TYPE1*,SORT>::compare, (void*)sort); }

template <class TYPE, class SORT> inline const TYPE* ybsearch(const TYPE& key, const TYPE *base, unsigned num, SORT sort) // NULL on error, pointer on success
  { return (TYPE*)::y_bsearch((const void*)&key,(const void*)base,num,sizeof(TYPE),(int (*)(const void *, const void *, void*))ycompareclass<const TYPE,SORT>::compare, (void*)sort); }
template <class TYPE1, class TYPE2, class SORT> inline TYPE2* ybsearch(TYPE1* key, TYPE2 *base, unsigned num, SORT sort) // NULL on error, pointer on success
  { return (TYPE2*)::y_bsearch((const void*)(const TYPE1**)&key,(const void*)base,num,sizeof(TYPE1*),(int (*)(const void *, const void *, void*))ycompareclass<const TYPE1*,SORT>::compare, (void*)sort); }

//index search
//  size_t ysearch_index (const TYPE& key, const TYPE *base, unsigned num, SORT sort)  //for objects
//  size_t ysearch_index (TYPE1* key, TYPE2 *base, unsigned num, SORT sort)            //for pointers
//  size_t ybsearch_index(const TYPE& key, const TYPE *base, unsigned num, SORT sort) //for objects
//  size_t ybsearch_index(TYPE1* key, TYPE2 *base, unsigned num, SORT sort)           //for pointers
template <class TYPE, class SORT> inline size_t ysearch_index(const TYPE& key, const TYPE *base, unsigned num, SORT sort) // -1 on error, index on success
  { const TYPE* p = ysearch(key,base,num,sort); return (p==NULL?-1:p-base); }
template <class TYPE1, class TYPE2, class SORT> size_t ysearch_index(TYPE1* key, TYPE2 *base, unsigned num, SORT sort)    // -1 on error, index on success
  { TYPE2* p = ysearch(key,base,num,sort); return (p==NULL?-1:p-base); }

template <class TYPE, class SORT> inline size_t ybsearch_index(const TYPE& key, const TYPE *base, unsigned num, SORT sort) // -1 on error, index on success
  { const TYPE* p = ybsearch(key,base,num,sort); return (p==NULL?-1:p-base); }
template <class TYPE1, class TYPE2, class SORT> size_t ybsearch_index(TYPE1* key, TYPE2 *base, unsigned num, SORT sort)    // -1 on error, index on success
  { TYPE2* p = ybsearch(key,base,num,sort); return (p==NULL?-1:p-base); }

//range search: base[min]<=key, base[min+1]>=key, base[max]>=key, base[max-1]<=key, mid-insert point
// const TYPE* _ybsearch_min(const TYPE& key, const TYPE *base, unsigned num, SORT sort);//for objects
// TYPE2*      _ybsearch_min(TYPE1* key, TYPE2 *base, unsigned num, SORT sort);          //for pointers
// const TYPE* _ybsearch_max(const TYPE& key, const TYPE *base, unsigned num, SORT sort);//for objects
// TYPE2*      _ybsearch_max(TYPE1* key, TYPE2 *base, unsigned num, SORT sort);          //for pointers
// const TYPE* _ybsearch_mid(const TYPE& key, const TYPE *base, unsigned num, SORT sort);//for objects
// TYPE2*      _ybsearch_mid(TYPE1* key, TYPE2 *base, unsigned num, SORT sort);          //for pointers
// size_t       ybsearch_min(const TYPE& key, const TYPE *base, unsigned num, SORT sort);//for objects
// size_t       ybsearch_min(TYPE1* key, TYPE2 *base, unsigned num, SORT sort);          //for pointers
// size_t       ybsearch_max(const TYPE& key, const TYPE *base, unsigned num, SORT sort);//for objects
// size_t       ybsearch_max(TYPE1* key, TYPE2 *base, unsigned num, SORT sort);          //for pointers
// size_t       ybsearch_mid(const TYPE& key, const TYPE *base, unsigned num, SORT sort);//for objects
// size_t       ybsearch_mid(TYPE1* key, TYPE2 *base, unsigned num, SORT sort);          //for pointers
template <class TYPE, class SORT> inline const TYPE* _ybsearch_min(const TYPE& key, const TYPE *base, unsigned num, SORT sort) // NULL on error, pointer on success
  { return (TYPE*)::y_bsearch_range(-1,(const void*)&key,(const void*)base,num,sizeof(TYPE),(int (*)(const void *, const void *, void*))ycompareclass<const TYPE,SORT>::compare, (void*)sort); }
template <class TYPE1, class TYPE2, class SORT> inline TYPE2* _ybsearch_min(TYPE1* key, TYPE2 *base, unsigned num, SORT sort) // NULL on error, pointer on success
  { return (TYPE2*)::y_bsearch_range(-1,(const void*)(const TYPE1**)&key,(const void*)base,num,sizeof(TYPE1*),(int (*)(const void *, const void *, void*))ycompareclass<const TYPE1*,SORT>::compare, (void*)sort); }
template <class TYPE, class SORT> inline const TYPE* _ybsearch_max(const TYPE& key, const TYPE *base, unsigned num, SORT sort) // NULL on error, pointer on success
  { return (TYPE*)::y_bsearch_range( 1,(const void*)&key,(const void*)base,num,sizeof(TYPE),(int (*)(const void *, const void *, void*))ycompareclass<const TYPE,SORT>::compare, (void*)sort); }
template <class TYPE1, class TYPE2, class SORT> inline TYPE2* _ybsearch_max(TYPE1* key, TYPE2 *base, unsigned num, SORT sort) // NULL on error, pointer on success
  { return (TYPE2*)::y_bsearch_range( 1,(const void*)(const TYPE1**)&key,(const void*)base,num,sizeof(TYPE1*),(int (*)(const void *, const void *, void*))ycompareclass<const TYPE1*,SORT>::compare, (void*)sort); }
template <class TYPE, class SORT> inline const TYPE* _ybsearch_mid(const TYPE& key, const TYPE *base, unsigned num, SORT sort) // NULL on error, pointer on success
  { return (TYPE*)::y_bsearch_range( 0,(const void*)&key,(const void*)base,num,sizeof(TYPE),(int (*)(const void *, const void *, void*))ycompareclass<const TYPE,SORT>::compare, (void*)sort); }
template <class TYPE1, class TYPE2, class SORT> inline TYPE2* _ybsearch_mid(TYPE1* key, TYPE2 *base, unsigned num, SORT sort) // NULL on error, pointer on success
  { return (TYPE2*)::y_bsearch_range( 0,(const void*)(const TYPE1**)&key,(const void*)base,num,sizeof(TYPE1*),(int (*)(const void *, const void *, void*))ycompareclass<const TYPE1*,SORT>::compare, (void*)sort); }

template <class TYPE, class SORT> inline size_t ybsearch_min(const TYPE& key, const TYPE *base, unsigned num, SORT sort) // -1 on error, index on success
  { const TYPE* p = _ybsearch_min(key,base,num,sort); return (p==NULL?-1:p-base); }
template <class TYPE1, class TYPE2, class SORT> size_t ybsearch_min(TYPE1* key, TYPE2 *base, unsigned num, SORT sort)    // -1 on error, index on success
  { TYPE2* p = _ybsearch_min(key,base,num,sort); return (p==NULL?-1:p-base); }
template <class TYPE, class SORT> inline size_t ybsearch_max(const TYPE& key, const TYPE *base, unsigned num, SORT sort) // -1 on error, index on success
  { const TYPE* p = _ybsearch_max(key,base,num,sort); return (p==NULL?-1:p-base); }
template <class TYPE1, class TYPE2, class SORT> size_t ybsearch_max(TYPE1* key, TYPE2 *base, unsigned num, SORT sort)    // -1 on error, index on success
  { TYPE2* p = _ybsearch_max(key,base,num,sort); return (p==NULL?-1:p-base); }
template <class TYPE, class SORT> inline size_t ybsearch_mid(const TYPE& key, const TYPE *base, unsigned num, SORT sort) // index on success
  { const TYPE* p = _ybsearch_mid(key,base,num,sort); return (p==NULL?0:p-base); }
template <class TYPE1, class TYPE2, class SORT> size_t ybsearch_mid(TYPE1* key, TYPE2 *base, unsigned num, SORT sort)    // index on success
  { TYPE2* p = _ybsearch_mid(key,base,num,sort); return (p==NULL?0:p-base); }

/////////////////////////////////////////////////////////////////////////////////////////
//sorting declaration helpers

#define YCOMPARE_BY_C_DEFAULT(TYPE) YCOMPARE_DEFAULTS(TYPE)\
  { return( *e1==*e2 ? 0 : (*e1<*e2 ? -1: 1) ); }

#define YCOMPARE_BY_DEFAULT(TYPE) YCOMPARE_DEFAULTS(TYPE)\
  { return xcompareclass<TYPE>::compare(e1,e2); } //Attention! XQSORT don't support backward sorting of pointers!

#define YCOMPARE_BY_OBJECT(TYPE,SORT)\
  inline int ycompareclass< const TYPE, SORT* >::\
    compare(const TYPE *e1, const TYPE *e2, SORT* sort)\
      { return /*virtual*/ sort->compare(e1,e2); }

#define YCOMPARE_BY_CLASS(TYPE,SORT)\
  inline int ycompareclass< const TYPE, SORT* >::\
    compare(const TYPE *e1, const TYPE *e2, SORT* sort)\
      { return /*static*/ SORT::compare(e1,e2); }

#define YCOMPARE_SPECIFIC(TYPE,SORT)\
  inline int ycompareclass< const TYPE, SORT* >::\
    compare(const TYPE *e1, const TYPE *e2, SORT* sort)
//    { body }

#define YCOMPARE_DEFAULTS(TYPE)\
  YCOMPARE_SPECIFIC(TYPE,yqsort_back)\
      { return -ycompareclass< const TYPE, yqsort_void* >::compare(e1,e2,(yqsort_void*)sort); }\
  YCOMPARE_SPECIFIC(TYPE,yqsort_void)
//    { body }

/////////////////////////////////////////////////////////////////////////////////////////
// strings sorting
#define YQSORT_COMRARE_NO_CASE        ((yqsort_compare_no_case*)NULL)
#define YQSORT_COLLATE_NO_CASE        ((yqsort_collate_no_case*)NULL)
#define YQSORT_STRING_COLLATE         ((yqsort_string_collate*) NULL)
#define YQSORT_STRING_COMRARE         ((yqsort_string_compare*) NULL)

class   yqsort_compare_no_case        {void* unused_ptr;};
class   yqsort_collate_no_case        {void* unused_ptr;};
class   yqsort_string_compare         {void* unused_ptr;};
class   yqsort_string_collate         {void* unused_ptr;};

#define YS yqsort_compare_no_case
YCOMPARE_SPECIFIC(CString       ,YS)  { return (*e1).CompareNoCase(*e2); }
YCOMPARE_SPECIFIC(char          ,YS)  { return _strnicmp(e1,e2,1); }
YCOMPARE_SPECIFIC(unsigned char ,YS)  { return _mbsnicmp(e1,e2,1); }
YCOMPARE_SPECIFIC(wchar_t       ,YS)  { return _wcsnicmp(e1,e2,1); }
                                              
YCOMPARE_SPECIFIC(CString*      ,YS)  { return (**e1).CompareNoCase(**e2); }
YCOMPARE_SPECIFIC(char*         ,YS)  { return _stricmp(*e1,*e2); }
YCOMPARE_SPECIFIC(unsigned char*,YS)  { return _mbsicmp(*e1,*e2); }
YCOMPARE_SPECIFIC(wchar_t*      ,YS)  { return _wcsicmp(*e1,*e2); }
#undef  YS

#define YS yqsort_collate_no_case
YCOMPARE_SPECIFIC(CString       ,YS)  { return (*e1).CollateNoCase(*e2); }
YCOMPARE_SPECIFIC(char          ,YS)  { return _strnicoll(e1,e2,1); }
YCOMPARE_SPECIFIC(unsigned char ,YS)  { return _mbsnicoll(e1,e2,1); }
YCOMPARE_SPECIFIC(wchar_t       ,YS)  { return _wcsnicoll(e1,e2,1); }
                                              
YCOMPARE_SPECIFIC(CString*      ,YS)  { return (**e1).CollateNoCase(**e2); }
YCOMPARE_SPECIFIC(char*         ,YS)  { return _stricoll(*e1,*e2); }
YCOMPARE_SPECIFIC(unsigned char*,YS)  { return _mbsicoll(*e1,*e2); }
YCOMPARE_SPECIFIC(wchar_t*      ,YS)  { return _wcsicoll(*e1,*e2); }
#undef  YS

#define YS yqsort_string_collate
YCOMPARE_SPECIFIC(CString       ,YS)  { return (*e1).Collate(*e2); }
YCOMPARE_SPECIFIC(char          ,YS)  { return _strncoll(e1,e2,1); }
YCOMPARE_SPECIFIC(unsigned char ,YS)  { return _mbsncoll(e1,e2,1); }
YCOMPARE_SPECIFIC(wchar_t       ,YS)  { return _wcsncoll(e1,e2,1); }
                                              
YCOMPARE_SPECIFIC(CString*      ,YS)  { return (**e1).Collate(**e2); }
YCOMPARE_SPECIFIC(char*         ,YS)  { return  strcoll(*e1,*e2); }
YCOMPARE_SPECIFIC(unsigned char*,YS)  { return _mbscoll(*e1,*e2); }
YCOMPARE_SPECIFIC(wchar_t*      ,YS)  { return  wcscoll(*e1,*e2); }
#undef  YS

#define YS yqsort_string_compare
YCOMPARE_SPECIFIC(CString       ,YS)  { return (*e1).Compare(*e2); }
YCOMPARE_SPECIFIC(char          ,YS)  { return  strncmp(e1,e2,1); }
YCOMPARE_SPECIFIC(unsigned char ,YS)  { return _mbsncmp(e1,e2,1); }
YCOMPARE_SPECIFIC(wchar_t       ,YS)  { return  wcsncmp(e1,e2,1); }
                                              
YCOMPARE_SPECIFIC(CString*      ,YS)  { return (**e1).Compare(**e2); }
YCOMPARE_SPECIFIC(char*         ,YS)  { return  strcmp(*e1,*e2); }
YCOMPARE_SPECIFIC(unsigned char*,YS)  { return _mbscmp(*e1,*e2); }
YCOMPARE_SPECIFIC(wchar_t*      ,YS)  { return  wcscmp(*e1,*e2); }
#undef  YS

/////////////////////////////////////////////////////////////////////////////////////////
// win32 strings word sorting (see lstrcmp() documentation for details)
#define YQSORT_WIN32_COMPARE_NO_CASE  ((yqsort_win32_compare_no_case*) NULL)
#define YQSORT_WIN32_STRING_COMPARE   ((yqsort_win32_string_compare*) NULL)

class   yqsort_win32_compare_no_case  {void* unused_ptr;};//lstrcmpi
class   yqsort_win32_string_compare   {void* unused_ptr;};//lstrcmp

#define YS yqsort_win32_compare_no_case
YCOMPARE_SPECIFIC(char          ,YS)  { char          c1[2]={*e1}, c2[2]={*e2}; return ::lstrcmpiA(c1,c2); }
YCOMPARE_SPECIFIC(unsigned char ,YS)  { unsigned char c1[2]={*e1}, c2[2]={*e2}; return ::lstrcmpiA((LPCSTR)c1,(LPCSTR)c2); }
YCOMPARE_SPECIFIC(wchar_t       ,YS)  { wchar_t       c1[2]={*e1}, c2[2]={*e2}; return ::lstrcmpiW(c1,c2); }
                                              
YCOMPARE_SPECIFIC(char*         ,YS)  { return ::lstrcmpiA(*e1,*e2); }
YCOMPARE_SPECIFIC(unsigned char*,YS)  { return ::lstrcmpiA((LPCSTR)*e1,(LPCSTR)*e2); }
YCOMPARE_SPECIFIC(wchar_t*      ,YS)  { return ::lstrcmpiW(*e1,*e2); }
#undef  YS

#define YS yqsort_win32_string_compare
YCOMPARE_SPECIFIC(char          ,YS)  { char          c1[2]={*e1}, c2[2]={*e2}; return ::lstrcmpA(c1,c2); }
YCOMPARE_SPECIFIC(unsigned char ,YS)  { unsigned char c1[2]={*e1}, c2[2]={*e2}; return ::lstrcmpA((LPCSTR)c1,(LPCSTR)c2); }
YCOMPARE_SPECIFIC(wchar_t       ,YS)  { wchar_t       c1[2]={*e1}, c2[2]={*e2}; return ::lstrcmpW(c1,c2); }
                                                                                                                          
YCOMPARE_SPECIFIC(char*         ,YS)  { return ::lstrcmpA(*e1,*e2); }                                                      
YCOMPARE_SPECIFIC(unsigned char*,YS)  { return ::lstrcmpA((LPCSTR)*e1,(LPCSTR)*e2); }                                      
YCOMPARE_SPECIFIC(wchar_t*      ,YS)  { return ::lstrcmpW(*e1,*e2); }                                                      
#undef  YS

/////////////////////////////////////////////////////////////////////////////////////////
// win32 NLS strings sorting (see CompareString() documentation for details)
#define YQSORT_NLS_COMPARE_NO_CASE  ((yqsort_nls_compare_no_case*) NULL)   //don't work??
#define YQSORT_NLS_COMPARE_STRING   ((yqsort_nls_compare_string*)  NULL)

struct  yqsort_nls_compare_string
{ 
  LCID    m_lcid; 
  DWORD   m_flags; 
  BOOL    m_back; 

  yqsort_nls_compare_string(LCID lcid=LOCALE_USER_DEFAULT,DWORD dwCmpFlags=0, BOOL bBack=FALSE)
    { m_lcid = lcid; m_flags = dwCmpFlags; m_back = bBack; }

  int ans(int ret) const
    { ASSERT(ret); ret = (ret==CSTR_LESS_THAN?-1:(ret==CSTR_GREATER_THAN?1:(ret==CSTR_EQUAL?0:0))); ret = (m_back?-ret:ret); return ret; }
};

struct  yqsort_nls_compare_no_case: public yqsort_nls_compare_string
{
  yqsort_nls_compare_no_case(LCID lcid=LOCALE_USER_DEFAULT,DWORD dwCmpFlags=0, BOOL bBack=FALSE)
    : yqsort_nls_compare_string(lcid,dwCmpFlags|NORM_IGNORECASE/*|NORM_IGNOREWIDTH*/, bBack) {}
};

#define YS yqsort_nls_compare_no_case
YCOMPARE_SPECIFIC(char          ,YS)  { static YS s_ys; YS& ys=sort?*sort:s_ys; return ys.ans( ::CompareStringA(ys.m_lcid,ys.m_flags, e1, 1, e2, 1) ); }
YCOMPARE_SPECIFIC(unsigned char ,YS)  { static YS s_ys; YS& ys=sort?*sort:s_ys; return ys.ans( ::CompareStringA(ys.m_lcid,ys.m_flags,(LPCSTR) e1, 1,(LPCSTR) e2, 1) ); }
YCOMPARE_SPECIFIC(wchar_t       ,YS)  { static YS s_ys; YS& ys=sort?*sort:s_ys; return ys.ans( ::CompareStringW(ys.m_lcid,ys.m_flags, e1, 1, e2, 1) ); }

YCOMPARE_SPECIFIC(char*         ,YS)  { static YS s_ys; YS& ys=sort?*sort:s_ys; return ys.ans( ::CompareStringA(ys.m_lcid,ys.m_flags,*e1,-1,*e2,-1) ); }
YCOMPARE_SPECIFIC(unsigned char*,YS)  { static YS s_ys; YS& ys=sort?*sort:s_ys; return ys.ans( ::CompareStringA(ys.m_lcid,ys.m_flags,(LPCSTR)*e1,-1,(LPCSTR)*e2,-1) ); }
YCOMPARE_SPECIFIC(wchar_t*      ,YS)  { static YS s_ys; YS& ys=sort?*sort:s_ys; return ys.ans( ::CompareStringW(ys.m_lcid,ys.m_flags,*e1,-1,*e2,-1) ); }
#undef  YS

#define YS yqsort_nls_compare_string
YCOMPARE_SPECIFIC(char          ,YS)  { static YS s_ys; YS& ys=sort?*sort:s_ys; return ys.ans( ::CompareStringA(ys.m_lcid,ys.m_flags, e1, 1, e2, 1) ); }
YCOMPARE_SPECIFIC(unsigned char ,YS)  { static YS s_ys; YS& ys=sort?*sort:s_ys; return ys.ans( ::CompareStringA(ys.m_lcid,ys.m_flags,(LPCSTR) e1, 1,(LPCSTR) e2, 1) ); }
YCOMPARE_SPECIFIC(wchar_t       ,YS)  { static YS s_ys; YS& ys=sort?*sort:s_ys; return ys.ans( ::CompareStringW(ys.m_lcid,ys.m_flags, e1, 1, e2, 1) ); }

YCOMPARE_SPECIFIC(char*         ,YS)  { static YS s_ys; YS& ys=sort?*sort:s_ys; return ys.ans( ::CompareStringA(ys.m_lcid,ys.m_flags,*e1,-1,*e2,-1) ); }
YCOMPARE_SPECIFIC(unsigned char*,YS)  { static YS s_ys; YS& ys=sort?*sort:s_ys; return ys.ans( ::CompareStringA(ys.m_lcid,ys.m_flags,(LPCSTR)*e1,-1,(LPCSTR)*e2,-1) ); }
YCOMPARE_SPECIFIC(wchar_t*      ,YS)  { static YS s_ys; YS& ys=sort?*sort:s_ys; return ys.ans( ::CompareStringW(ys.m_lcid,ys.m_flags,*e1,-1,*e2,-1) ); }
#undef  YS

/////////////////////////////////////////////////////////////////////////////////////////
// CString characters sort support //TO DO - design fast string-oriented character sort and search?
//   void    yqsort(CString& sz, SORT sort);
//   LPCTSTR ysearch(TCHAR c, const CString& sz, SORT sort)
//   LPCTSTR ybsearch(TCHAR c, const CString& sz, SORT sort)
//   size_t  ysearch_index(TCHAR c, const CString& sz, SORT sort)
//   size_t  ybsearch_index(TCHAR c, const CString& sz, SORT sort)
//   size_t  ybsearch_min(TCHAR c, const CString& sz, SORT sort)
//   size_t  ybsearch_max(TCHAR c, const CString& sz, SORT sort)

template <class SORT> inline void yqsort(CString& sz, SORT sort)
  { ::y_qsort((void*)sz.LockBuffer(),sz.GetLength(),sizeof(TCHAR),(int (*)(const void *, const void *, void*))ycompareclass<const TCHAR, SORT>::compare, (void*)sort); sz.UnlockBuffer(); }

template <class SORT> inline LPCTSTR ysearch(TCHAR c, const CString& sz, SORT sort)
  { size_t num = sz.GetLength(); return (LPCTSTR)::y_search((const void*)&c,(const void*)(LPCTSTR)sz,&num,sizeof(TCHAR),(int (*)(const void *, const void *, void*))ycompareclass<const TCHAR, SORT>::compare, (void*)sort); }

template <class SORT> inline LPCTSTR ybsearch(TCHAR c, const CString& sz, SORT sort)
  { size_t num = sz.GetLength(); return (LPCTSTR)::y_bsearch((const void*)&c,(const void*)(LPCTSTR)sz,num,sizeof(TCHAR),(int (*)(const void *, const void *, void*))ycompareclass<const TCHAR, SORT>::compare, (void*)sort); }

template <class SORT> inline size_t ysearch_index(TCHAR c, const CString& sz, SORT sort)
  { LPCTSTR p = ysearch(c,sz,sort); return (p==NULL?-1:p-(LPCTSTR)sz); }

template <class SORT> inline size_t ybsearch_index(TCHAR c, const CString& sz, SORT sort)
  { LPCTSTR p = ybsearch(c,sz,sort); return (p==NULL?-1:p-(LPCTSTR)sz); }

template <class SORT> inline LPCTSTR _ybsearch_min(TCHAR c, const CString& sz, SORT sort) // NULL on error, pointer on success
  { return (LPCTSTR)::y_bsearch_range(-1,(const void*)&c,(const void*)(LPCTSTR)sz,sz.GetLength(),sizeof(TCHAR),(int (*)(const void *, const void *, void*))ycompareclass<const TCHAR, SORT>::compare, (void*)sort); }

template <class SORT> inline LPCTSTR _ybsearch_max(TCHAR c, const CString& sz, SORT sort) // NULL on error, pointer on success
  { return (LPCTSTR)::y_bsearch_range( 1,(const void*)&c,(const void*)(LPCTSTR)sz,sz.GetLength(),sizeof(TCHAR),(int (*)(const void *, const void *, void*))ycompareclass<const TCHAR, SORT>::compare, (void*)sort); }

template <class SORT> inline LPCTSTR _ybsearch_mid(TCHAR c, const CString& sz, SORT sort) // NULL on error, pointer on success
  { return (LPCTSTR)::y_bsearch_range( 0,(const void*)&c,(const void*)(LPCTSTR)sz,sz.GetLength(),sizeof(TCHAR),(int (*)(const void *, const void *, void*))ycompareclass<const TCHAR, SORT>::compare, (void*)sort); }

template <class SORT> inline size_t ybsearch_min(TCHAR c, const CString& sz, SORT sort) // NULL on error, pointer on success
  { LPCTSTR p = _ybsearch_min(c,sz,sort); return (p==NULL?-1:p-(LPCTSTR)sz); }

template <class SORT> inline size_t ybsearch_max(TCHAR c, const CString& sz, SORT sort) // NULL on error, pointer on success
  { LPCTSTR p = _ybsearch_max(c,sz,sort); return (p==NULL?-1:p-(LPCTSTR)sz); }

template <class SORT> inline size_t ybsearch_mid(TCHAR c, const CString& sz, SORT sort) // NULL on error, pointer on success
  { LPCTSTR p = _ybsearch_mid(c,sz,sort); return (p==NULL?-1:p-(LPCTSTR)sz); }

/////////////////////////////////////////////////////////////////////////////////////////
// MFC collections sorting

#define CArray__qsort(a,p)             yqsort(a.GetData(),a.GetSize(),(p))
#define CArray__bsearch(x,a,p)         ybsearch((x),a.GetData(),a.GetSize(),(p))
#define CArray__bsearch_index(x,a,p)   ybsearch_index((x),a.GetData(),a.GetSize(),(p))
#define CArray__bsearch_min(x,a,p)     ybsearch_min((x),a.GetData(),a.GetSize(),(p))
#define CArray__bsearch_max(x,a,p)     ybsearch_max((x),a.GetData(),a.GetSize(),(p))
#define CArray__search(x,a,p)          ysearch((x),a.GetData(),a.GetSize(),(p))
#define CArray__search_index(x,a,p)    ysearch_index((x),a.GetData(),a.GetSize(),(p))

/*
  yqsort( CArray<*,*>&, SORT sort);

  yqsort(CStringArray& a, SORT sort);
  CMapStringToString__Sort(const CMapStringToString& as, CStringArray& aOrd, SORT sort);

  CMapStringToString__SortByKeys(const CMapStringToString& as, CArray<LPCTSTR,LPCTSTR>, SORT sort);
  CMapStringToPtr__SortByKeys(const CMapStringToPtr& as, CArray<LPCTSTR,LPCTSTR>, SORT sort);
  CMapStringToOb__SortByKeys(const CMapStringToOb& as, CArray<LPCTSTR,LPCTSTR>, SORT sort);

  CMap__SortByKeys(const CMap<*,*,X,Y>&, CArray<X,Y>& order, SORT sort);
  CMap__Sort(const CMap<*,*,X,Y>&, CArray<X,Y>& order, SORT sort);
*/

#ifdef  __AFXTEMPL_H__

template < class VALUE, class ARG_VALUE, class PSORT >
  inline void yqsort(CArray<VALUE,ARG_VALUE>& a, PSORT sort)
    { yqsort(a.GetData(), a.GetSize(), sort); }

#endif//__AFXTEMPL_H__
#if defined(__AFXCOLL_H__) && defined(__AFXTEMPL_H__)

template < class PSORT >
  inline void yqsort(CStringArray& a, PSORT sort)
    { yqsort(a.GetData(), a.GetSize(), sort); }

template < class PSORT >
inline void CMapStringToString__Sort(const CMapStringToString& as, CStringArray& aOrd, PSORT sort)
{
  aOrd.SetSize(as.GetCount());
  CString szIdx, szVal;
  POSITION pos=as.GetStartPosition();
  for(int i=0; i<as.GetCount(); ++i){
    as.GetNextAssoc(pos,szIdx,szVal);
    aOrd[i] = szVal;
  }
  CArray__qsort(aOrd,sort);
}

template <class VALUE, class ARG_VALUE, class PSORT >
inline void CMapStringToString__SortByKeys(const CMapStringToString& as, CArray<VALUE,ARG_VALUE>& aOrd, PSORT sort)
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
  CArray__qsort(aOrd,sort);
}

template <class VALUE, class ARG_VALUE, class PSORT >
inline void CMapStringToOb__SortByKeys(const CMapStringToOb& as, CArray<VALUE,ARG_VALUE>& aOrd, PSORT sort)
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
  CArray__qsort(aOrd,sort);
}

template <class VALUE, class ARG_VALUE, class PSORT>
inline void CMapStringToPtr__SortByKeys(const CMapStringToPtr& as, CArray<VALUE,ARG_VALUE>& aOrd, PSORT sort)
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
  CArray__qsort(aOrd,sort);
}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PSORT>
inline void CMap__SortByKeys(const CMap<KEY,ARG_KEY,VALUE,ARG_VALUE>& as, CArray<KEY,ARG_KEY>& aOrd, PSORT sort)
{
  aOrd.SetSize(as.GetCount());
  KEY   key;
  VALUE val;
  POSITION pos=as.GetStartPosition();
  for(int i=0; i<as.GetCount(); ++i){
    as.GetNextAssoc(pos,key,val);
    aOrd[i] = key;
  }
  CArray__qsort(aOrd,sort);
}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PSORT>
inline void CMap__Sort(const CMap<KEY,ARG_KEY,VALUE,ARG_VALUE>& as, CArray<KEY,ARG_KEY>& aOrd, PSORT sort)
{
  aOrd.SetSize(as.GetCount());
  KEY   key;
  VALUE val;
  POSITION pos=as.GetStartPosition();
  for(int i=0; i<as.GetCount(); ++i){
    as.GetNextAssoc(pos,key,val);
    aOrd[i] = val;
  }
  CArray__qsort(aOrd,sort);
}

#endif//__AFXCOLL_H__ && __AFXTEMPL_H__

#endif//_cplusplus

#endif//__YQSORT_H
