#ifndef __YVARIANT_H
#define __YVARIANT_H
#include <comdef.h>
#include "int64.h"
#include "xassert.h"

//////////////////////////////////////////////////////////////////////////////
// YVARIANT: extension of VARIANT with C++ static initialization ability
//
/* Example:

    YVARIANT v = { YVARIANT_VALUE(33.) };
    struct C 
    { 
      int      i; 
      double   d; 
      YVARIANT v; 
    } c = {0,0,{ YVARIANT_VALUE(2.0) }};

*/

#define YVARIANT_VALUE(value) YVARIANT::static_construct1(_variant_t(value)), YVARIANT::static_construct2()


union YVARIANT
{ 
  QWORD   m_qw[2];
  VARIANT m_var;

//dynamic construction
  operator const _variant_t& () const  { return *(const _variant_t*)this; }
  operator       _variant_t& ()        { return *(      _variant_t*)this; }

  void construct(const _variant_t & v) { operator _variant_t & () = v; }

//static construction
  static DWORD s_lock;
  static QWORD s_qw[2];

  static QWORD static_construct1(const _variant_t & v)
  { 
    STATIC_ASSERT(sizeof(YVARIANT)==sizeof(VARIANT)   , type_size_mithmatch );
    STATIC_ASSERT(sizeof(YVARIANT)==sizeof(_variant_t), type_size_mithmatch );
    QWORD qw = 0;
    ASSERT(s_lock==0); ++s_lock; //check: if static buffer busy? allocate static buffer
    *((_variant_t*)s_qw) = v; //initialize: call _variant_t(...) constructor
    qw = s_qw[0]; //raw copy _variant_t to static destignation (qword 0)
    return qw;
  }
  static QWORD static_construct2()
  { 
    QWORD qw = 0;
    qw = s_qw[1]; //raw copy _variant_t to static destignation (qword 1)
    s_qw[0] = s_qw[1]= 0; // clean: don't call ~_variant_t() destructor!
    ASSERT(s_lock==1); --s_lock; //check: free static buffer
    return qw;
  }
};



#endif//__YVARIANT_H