#ifndef __EVENTCLASS_H
#define __EVENTCLASS_H
#define  YCLASS_NO_INL
#include "YClass.h"
#ifdef  __cplusplus
#pragma pack(push,1)
/////////////////////////////////////////////////////////////////////////////

class   YEventObject;   //+
class   YEventBaseData; //+
struct  YEventClassInfo;//=
class       YEvent;

/////////////////////////////////////////////////////////////////////////////
// YEventClassInfo
struct YEventClassInfo
{
  typedef YEvent*       (*ALLOCATOR)(const void *pEBD, size_t nSize, void *pMem, size_t nMemSize, LPCSTR szFileName, int nLine);
  WORD                  m_nClass;
  WORD                  m_nType;
  WORD                  m_nMessageID; //message ID ?
  DWORD                 m_nSignature; //YEventEx only
  ALLOCATOR             m_fnAllocate;
  LPCTSTR               m_szDescript;
  YEventClassInfo*      m_pHead;
  YEventClassInfo*      m_pNext;
  BOOL                  operator==(const YEventBaseData& data) const;
  BOOL                  operator!=(const YEventBaseData& data) const;
};

/////////////////////////////////////////////////////////////////////////////
// Globals
int   YEVENT__ClassReplaceDump(const YEventClassInfo*);
int   YEVENT__ClassesDump();

/////////////////////////////////////////////////////////////////////////////
// Macro to obtain initialized classes data from static library
#define YEVENT_CLASS_DECLARE(class_name, class_parent)\
  YCLASS_DECLARE(class_name,class_parent)={class_name::eventCLASS,class_name::eventTYPE, 0, 0, class_name::Allocate,_T(#class_name)};

#define YEVENT_CLASS_IMPLEMENT(class_name, class_parent)\
  YCLASS_IMPLEMENT(class_name,class_parent);

#define YEVENT_CLASS_REGISTRATE(class_name, class_parent)\
  YCLASS_REGISTRATE(class_name,class_parent)

#define YEVENT_CLASSES_DUMP(isSignature)\
  YEVENT__ClassesDump()

#define YEVENT_CLASS(class_name,class_parent)\
  class_parent, public YClass<class_name,class_parent>

#pragma  pack(pop)
#endif __cplusplus
#endif//__EVENTOBJ_H
#pragma once
