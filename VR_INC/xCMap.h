#ifndef __XCMAP_H
#define __XCMAP_H
#include <afxtempl.h>
#include "yqsort.h"

//////////////////////////////////////////////////////////////////////////////
// CCommonMap<KEY,STRUCT>
//
// Needed functions:
//         TYPE::TYPE()
//   TYPE& TYPE::operator=(TYPE)
//   BOOL  TYPE::operator==(TYPE)

template <class KEY, class VALUE>
class CSimpleMap: public CMap<KEY,KEY&,VALUE,VALUE&>
{
  public: CSimpleMap( int nBlockSize = 10 ) : CMap<KEY,KEY&,VALUE,VALUE&>(nBlockSize){}
};

//////////////////////////////////////////////////////////////////////////////
// CSimpleMap<KEY,STRUCT>
//
// Needed functions:
//         TYPE::TYPE()
//   TYPE& TYPE::operator=(TYPE)
//   BOOL  TYPE::operator==(TYPE)

template <class KEY, class VALUE>
class CStructMap: public CMap<KEY,KEY,VALUE,VALUE&>
{
  public: CStructMap( int nBlockSize = 10 ) : CMap<KEY,KEY,VALUE,VALUE&>(nBlockSize){}
};

//////////////////////////////////////////////////////////////////////////////
// CScalarMap<KEY,VALUE>
//
// Needed functions:
//         TYPE::TYPE()
//   TYPE& TYPE::operator=(TYPE)
//   BOOL  TYPE::operator==(TYPE)

template <class KEY, class VALUE>
class CScalarMap: public CMap<KEY,KEY,VALUE,VALUE>
{
  public: CScalarMap( int nBlockSize = 10 ) : CMap<KEY,KEY,VALUE,VALUE>(nBlockSize){}
};

//////////////////////////////////////////////////////////////////////////////
// CAddressMapKEY,VALUE>
//
// Needed functions:
//         TYPE::TYPE()
//         TYPE::~TYPE()
//   TYPE& TYPE::operator=(TYPE)
//   BOOL  TYPE::operator==(TYPE)

//TO DO

//////////////////////////////////////////////////////////////////////////////
// CPointerMap<KEY,VALUE>
//
// Needed functions:
//         TYPE::TYPE()
//         TYPE::~TYPE()
//   TYPE& TYPE::operator=(TYPE)
//   BOOL  TYPE::operator==(TYPE)
// For serialization:
//   operator<<(CArchive&  ar, TYPE)
//   operator>>(CArchive&  ar, TYPE)
// For dump:
//   operator<<(CDumpContext& dc, TYPE)

//TO DO

//////////////////////////////////////////////////////////////////////////////
// CObjectMap<KEY,VALUE>
//
// Needed functions:
//         TYPE::TYPE()
//         TYPE::~TYPE()
//   TYPE& TYPE::operator=(TYPE)
//   BOOL  TYPE::operator==(TYPE)
// For serialization:
//   operator<<(CArchive&  ar, const TYPE*)
//   operator>>(CArchive&  ar, TYPE*)
// For dump:
//   operator<<(CDumpContext& dc, TYPE)


#endif// __XCMAP_H
#pragma once
