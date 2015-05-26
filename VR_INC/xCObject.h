#ifndef __XCOBJECT_H
#define __XCOBJECT_H
#include "xsignature.h"

#ifdef _DEBUG
  void    xcobject__assert(BOOL e, int l);
  #define XCOBJECT__ASSERT(e,l)  xcobject__assert(e,l); ASSERT(e)
#else
  #define XCOBJECT__ASSERT(e,l)
#endif

//////////////////////////////////////////////////////////////////////////////
// Class creation subroutines: polymorhic construction by ID /////////////////
//    will be used in data headers and external links (such as files)
//    must be derived from CObject or CObject based classes
// Macro will generate declaration and implementation of such procedures:
// 1. virtual class_classid_type GetRuntimeClassID() = 0;
// 2. static  CreateClass(const CRuntimeClass* pNewClass, class_classid_type classid, void*);
// 3. static  CreateObject(class_classid_type classid)
// Note: for class_classid_type must be defined operator== and operator=

#define DECLARE_DYNCREATE_METACLASS(meta_class_name,class_classid_type)\
  DECLARE_DYNAMIC(meta_class_name);\
  public:\
    static meta_class_name* CreateObject(class_classid_type classid);\
    static CreateClass(const CRuntimeClass*,class_classid_type,void *);\
    struct class_create_##meta_class_name {\
      struct class_create_##meta_class_name* pNext;\
      const CRuntimeClass* pClass;\
      class_classid_type classid;\
      class_create_##meta_class_name(const CRuntimeClass* pClass, class_classid_type classid)\
        { meta_class_name::CreateClass(pClass,classid,this); }\
    };\
  protected:\
    static struct class_create_##meta_class_name* m_aClassesListHead;\
  public:\
    static const void* GetClassesListHead(){return m_aClassesListHead;}\
    typedef class_classid_type classid##meta_class_name;\
    virtual classid##meta_class_name GetRuntimeClassID() const = 0;


#define IMPLEMENT_DYNCREATE_METACLASS(meta_class_name,base_class)\
  IMPLEMENT_DYNAMIC(meta_class_name,base_class);\
  struct meta_class_name::class_create_##meta_class_name* meta_class_name::m_aClassesListHead = {NULL};\
  \
  meta_class_name::CreateClass(\
    const CRuntimeClass* pClass,\
    meta_class_name::classid##meta_class_name classid,\
    void* pVoid)\
  {\
    struct class_create_##meta_class_name* pNode = (struct class_create_##meta_class_name*)pVoid;\
    XCOBJECT__ASSERT(pNode!=NULL,52);\
    CCriticalSection cs; cs.Lock();\
    for(struct class_create_##meta_class_name* p=m_aClassesListHead; p!=NULL; p=p->pNext)\
      if(p->classid == classid)\
        { XCOBJECT__ASSERT(0,56); }\
    pNode->pNext = m_aClassesListHead;\
    m_aClassesListHead = pNode;\
    pNode->pClass = pClass;\
    pNode->classid = classid;\
    cs.Unlock();\
    return 0;\
  }\
  \
  meta_class_name* meta_class_name::CreateObject(meta_class_name::classid##meta_class_name classid){\
    struct class_create_##meta_class_name* pNode;\
    for(pNode=m_aClassesListHead; pNode!=NULL; pNode=pNode->pNext)\
      if(pNode->classid == classid)\
        break;\
    if(pNode==NULL)\
      return NULL;\
    CObject* (PASCAL* pfnCreateObject)() = pNode->pClass->m_pfnCreateObject;\
    return (meta_class_name*)((*pfnCreateObject)());\
  }

//////////////////////////////////////////////////////////////////////////////
// Objects creation subroutines: /////////////////////////////////////////////
// 1. implement: virtual GetRuntimeClassID()
// 2. auto call: CreateClass(pNewClass,classid)

#define DECLARE_DYNCREATE_CLASS(class_name,class_classid,meta_class_name)\
  DECLARE_DYNCREATE(class_name);\
  public:\
  static const struct class_create_##meta_class_name the_class_create_##class_name##meta_class_name;\
  classid##meta_class_name GetRuntimeClassID() const; \
  static classid##meta_class_name _GetRuntimeClassID() { return class_classid; }

#define IMPLEMENT_DYNCREATE_CLASS(class_name,base_class_name,meta_class_name)\
  IMPLEMENT_DYNCREATE(class_name,base_class_name);\
  const struct meta_class_name::class_create_##meta_class_name \
    class_name::the_class_create_##class_name##meta_class_name(RUNTIME_CLASS(class_name),class_name::_GetRuntimeClassID());\
  meta_class_name::classid##meta_class_name class_name::GetRuntimeClassID() const \
    { return class_name::_GetRuntimeClassID(); }


//////////////////////////////////////////////////////////////////////////////
// Class creation subroutines: polymorhic construction by ID /////////////////
//    will be used in data headers and external links (such as files)
//    must be derived from CObject or CObject based classes
// Macro will generate declaration and implementation of such procedures:
// 1. virtual class_classid_type GetRuntimeClassID() = 0;
// 2. static  CreateClass(const CRuntimeClass* pNewClass, class_classid_type classid);
// 3. static  CreateObject(class_classid_type Type)
// Note: 1. for class_classid_type must be defined operator== and operator=
//       2. meta class must be derived from base_data_struct and
//          base_data_struc must have non-static and non-virtual public function
//          class_classid_type __GetRuntimeClassID(), which define
//          classid by base data struct; also must be defined operator=
//          Example:
//          struct BBaseData {
//            DWORD m_dwClass;
//            DWORD __GetRuntimeClassID() const {return m_dwClass;}
//          };
//       3. Default constructor of derived class must set m_dwClass field!

#define DECLARE_DYNCREATE_METACLASS_BASEDATA(meta_class_name,class_classid_type) \
  DECLARE_DYNCREATE_METACLASS(meta_class_name,class_classid_type)

#define IMPLEMENT_DYNCREATE_METACLASS_BASEDATA(meta_class_name,base_class) \
  IMPLEMENT_DYNCREATE_METACLASS(meta_class_name,base_class)

//////////////////////////////////////////////////////////////////////////////
// Objects creation subroutines: /////////////////////////////////////////////
// 1. implement: virtual GetRuntimeClassID()
// 2. auto call: CreateClass(pNewClass,classid)

#define __DECLARE_DYNCREATE_CLASS_BASEDATA(class_name,meta_class_name)\
  DECLARE_DYNCREATE(class_name);\
  static const classid##meta_class_name classid##class_name;\
  public:\
  static struct class_create_##meta_class_name the_class_create_##class_name##meta_class_name;\
  static classid##meta_class_name _GetRuntimeClassID() { return classid##class_name; }\
  classid##meta_class_name GetRuntimeClassID() const;\

#define __IMPLEMENT_DYNCREATE_CLASS_BASEDATA(class_name,base_class_name,meta_class_name)\
  IMPLEMENT_DYNCREATE(class_name,base_class_name);\
  inline meta_class_name::classid##meta_class_name __DefineRuntimeClassID##class_name##meta_class_name() \
    { class_name theClassObject; return theClassObject.__GetRuntimeClassID(); }\
  const meta_class_name::classid##meta_class_name class_name::classid##class_name =\
    __DefineRuntimeClassID##class_name##meta_class_name();\
  struct meta_class_name::class_create_##meta_class_name \
    class_name::the_class_create_##class_name##meta_class_name(RUNTIME_CLASS(class_name),__DefineRuntimeClassID##class_name##meta_class_name());\
  meta_class_name::classid##meta_class_name class_name::GetRuntimeClassID() const \
    { return class_name::_GetRuntimeClassID(); }

#define DECLARE_DYNCREATE_CLASS_BASEDATA(class_name,meta_class_name)\
      __DECLARE_DYNCREATE_CLASS_BASEDATA(class_name,meta_class_name)

#define IMPLEMENT_DYNCREATE_CLASS_BASEDATA(class_name,base_class_name,meta_class_name)\
      __IMPLEMENT_DYNCREATE_CLASS_BASEDATA(class_name,base_class_name,meta_class_name)

//////////////////////////////////////////////////////////////////////////////
// Class creation subroutines: polymorhic construction by ID with load/store
// Implementation of Load/Store functions based on defined in the each
// class non-virtual non-static functions __Load(void* fp) and __Store(void *fp)
// which operate only on own (not inherited!) class members.
//
//__Load and __Store functions must be manually defined in next manner:
//  size_t CClass::__Store(void *fp) const {
//    size_t nDataSize = ...object data size...;
//    if(fp!=NULL) {
//      *fp = ...object data...
//    }
//    return nDataSize;
//  }
//  size_t CClass::__Load(const void *fp=NULL) {
//    size_t nDataSize = ...object data size...;
//    if(fp!=NULL) {
//      ...object data... = *fp;
//    }
//    return nDataSize;
//  }
//////////////////////////////////////////////////////////////////////////////

#define LOADSTORE_NEEDED_MORE_DATA (-1)
#define LOADSTORE_ILLEGAL_CLASSID  (-2)
#define LOADSTORE_FAILURE          (-3)
#define LOADSTORE_SUCCESS          0
typedef struct tagLOADSTORESTATUS {
  size_t nUsed;
  size_t nNeeded;
  int    iStatus;
}LOADSTORESTATUS;


#define IMPLEMENT_LOADSTORE_CLASS_FUNCTIONS(class_name,base_class_name)\
  class_name::Load(const void *fp, size_t nSize, LOADSTORESTATUS* size){\
    int iRet = base_class_name::Load(fp,nSize,size);\
    if(iRet)\
      return iRet;\
    size_t nDataSize = __Load(NULL);\
    if(nSize < size->nUsed + nDataSize)\
      { size->nNeeded = size->nUsed + nDataSize; return size->iStatus = LOADSTORE_NEEDED_MORE_DATA; }\
    void* pData = (BYTE*)fp + size->nUsed;\
    size->nUsed += __Load(pData);\
    return size->iStatus = LOADSTORE_SUCCESS;\
  }\
  \
  class_name::Store(void *fp, size_t nSize, LOADSTORESTATUS* size) const{\
    int iRet = base_class_name::Store(fp,nSize,size);\
    if(iRet)\
      return iRet;\
    size_t nDataSize = __Store(NULL);\
    if(nSize < size->nUsed + nDataSize)\
      { size->nNeeded = size->nUsed + nDataSize; return size->iStatus = LOADSTORE_NEEDED_MORE_DATA; }\
    void* pData = (BYTE*)fp + size->nUsed;\
    size->nUsed += __Store(pData);\
    return size->iStatus = LOADSTORE_SUCCESS;\
  }


#define DECLARE_LOADSTORE_METACLASS(meta_class_name,class_classid_type)\
  DECLARE_DYNCREATE_METACLASS(meta_class_name,class_classid_type);\
  private: size_t __Load(const void *fp=NULL);\
  private: size_t __Store(void *fp=NULL)const;\
  public:\
  static  meta_class_name* LoadObject(const void *fp, size_t nSize, LOADSTORESTATUS* size);\
  virtual Load(const void *fp, size_t nSize, LOADSTORESTATUS* size);\
  virtual Store(void *fp, size_t nSize, LOADSTORESTATUS* size)const;

#define IMPLEMENT_LOADSTORE_METACLASS(meta_class_name,base_class)\
  IMPLEMENT_DYNCREATE_METACLASS(meta_class_name,base_class);\
  \
  meta_class_name* meta_class_name::LoadObject(const void *fp, size_t nSize, LOADSTORESTATUS* size){\
    size->nUsed = size->nNeeded = size->iStatus = 0;\
    if(nSize<sizeof(classid##meta_class_name))\
      { size->nNeeded = sizeof(classid##meta_class_name); return NULL; }\
    classid##meta_class_name classid = *(const classid##meta_class_name*)fp;\
    meta_class_name *pObject = meta_class_name::CreateObject(classid);\
    if(pObject==NULL)\
      return size->iStatus = LOADSTORE_ILLEGAL_CLASSID, NULL;\
    pObject->Load(fp,nSize,size);\
    return pObject;\
  }\
  meta_class_name::Load(const void *fp, size_t nSize, LOADSTORESTATUS* size) {\
    size->nUsed = size->nNeeded = size->iStatus = 0;\
    size_t nDataSize = __Load(NULL);\
    if(nSize<sizeof(classid##meta_class_name)+nDataSize)\
      { size->nNeeded = sizeof(classid##meta_class_name)+nDataSize;\
        return size->iStatus = LOADSTORE_NEEDED_MORE_DATA; }\
    classid##meta_class_name classid = *(const classid##meta_class_name*)fp;\
    if(classid!=GetRuntimeClassID())\
      return size->iStatus = LOADSTORE_ILLEGAL_CLASSID;\
    size->nUsed += sizeof(classid##meta_class_name)+\
    __Load(((BYTE*)fp)+sizeof(classid##meta_class_name));\
    return size->iStatus = LOADSTORE_SUCCESS;;\
  }\
  \
  meta_class_name::Store(void *fp, size_t nSize, LOADSTORESTATUS* size)const{\
    size->nUsed = size->nNeeded = size->iStatus = 0;\
    size_t nDataSize = __Store(NULL);\
    if(nSize<sizeof(classid##meta_class_name)+nDataSize)\
      { size->nNeeded = sizeof(classid##meta_class_name)+nDataSize;\
        return size->iStatus = LOADSTORE_NEEDED_MORE_DATA; }\
    *(classid##meta_class_name*)fp = GetRuntimeClassID();\
    size->nUsed += sizeof(classid##meta_class_name)+\
    __Store(((BYTE*)fp)+sizeof(classid##meta_class_name));\
    return size->iStatus = LOADSTORE_SUCCESS;\
  }

#define DECLARE_LOADSTORE_CLASS(class_name,class_classid,meta_class_name)\
  DECLARE_DYNCREATE_CLASS(class_name,class_classid,meta_class_name);\
  private: size_t __Load(const void *fp=NULL);\
  private: size_t __Store(void *fp=NULL)const;\
  public:\
  Load(const void *fp, size_t nSize, LOADSTORESTATUS* size);\
  Store(void *fp, size_t nSize, LOADSTORESTATUS* size)const;

#define IMPLEMENT_LOADSTORE_CLASS(class_name,base_class_name,meta_class_name)\
  IMPLEMENT_DYNCREATE_CLASS(class_name,base_class_name,meta_class_name);\
  IMPLEMENT_LOADSTORE_CLASS_FUNCTIONS(class_name,base_class_name);


//////////////////////////////////////////////////////////////////////////////
// Class creation subroutines: polymorhic construction by ID from base data //

#define DECLARE_LOADSTORE_METACLASS_BASEDATA(meta_class_name,class_classid_type) \
  DECLARE_DYNCREATE_METACLASS_BASEDATA(meta_class_name,class_classid_type)\
  private: size_t __Load(const void *fp=NULL);\
  private: size_t __Store(void *fp=NULL)const;\
  public:\
  static  meta_class_name* LoadObject(const void *fp, size_t nSize, LOADSTORESTATUS* size);\
  virtual Load(const void *fp, size_t nSize, LOADSTORESTATUS* size);\
  virtual Store(void *fp, size_t nSize, LOADSTORESTATUS* size)const;


#define IMPLEMENT_LOADSTORE_METACLASS_BASEDATA(meta_class_name,base_class,base_data_struc)\
  IMPLEMENT_DYNCREATE_METACLASS_BASEDATA(meta_class_name,base_class);\
  \
  meta_class_name* meta_class_name::LoadObject(const void *fp, size_t nSize, LOADSTORESTATUS* size){\
    size->nUsed = size->nNeeded = size->iStatus = 0;\
    if(nSize<sizeof(base_data_struc))\
      { size->nNeeded = sizeof(base_data_struc); return NULL; }\
    classid##meta_class_name classid = ((const base_data_struc*)fp)->__GetRuntimeClassID();\
    meta_class_name *pObject = meta_class_name::CreateObject(classid);\
    if(pObject==NULL)\
      return size->iStatus = LOADSTORE_ILLEGAL_CLASSID, NULL;\
    pObject->Load(fp,nSize,size);\
    return pObject;\
  }\
  \
  meta_class_name::Load(const void *fp, size_t nSize, LOADSTORESTATUS* size) {\
    size->nUsed = size->nNeeded = size->iStatus = 0;\
    size_t nDataSize = __Load(NULL);\
    if(nSize < sizeof(base_data_struc)+nDataSize)\
      { size->nNeeded = sizeof(base_data_struc)+nDataSize; \
        return size->iStatus = LOADSTORE_NEEDED_MORE_DATA; }\
    classid##meta_class_name classid = ((const base_data_struc*)fp)->__GetRuntimeClassID();\
    if(classid!=GetRuntimeClassID())\
      return size->iStatus = LOADSTORE_ILLEGAL_CLASSID;\
    *(base_data_struc*)this = *(const base_data_struc*)fp;\
    size->nUsed += sizeof(base_data_struc) + \
    __Load((BYTE*)fp+sizeof(base_data_struc));\
    return size->iStatus = LOADSTORE_SUCCESS;\
  }\
  \
  meta_class_name::Store(void *fp, size_t nSize, LOADSTORESTATUS* size) const{\
    size->nUsed = size->nNeeded = size->iStatus = 0;\
    size_t nDataSize = __Store(NULL);\
    if(nSize<sizeof(base_data_struc)+nDataSize)\
      { size->nNeeded = sizeof(base_data_struc)+nDataSize; \
        return size->iStatus = LOADSTORE_NEEDED_MORE_DATA; }\
    *(base_data_struc*)fp = *(const base_data_struc*)this;\
    size->nUsed += sizeof(base_data_struc) + \
    __Store((BYTE*)fp+sizeof(base_data_struc));\
    return size->iStatus = LOADSTORE_SUCCESS;\
  }\


#define DECLARE_LOADSTORE_CLASS_BASEDATA(class_name,meta_class_name)\
  DECLARE_DYNCREATE_CLASS_BASEDATA(class_name,meta_class_name);\
  private: size_t __Load(const void *fp=NULL);\
  private: size_t __Store(void *fp=NULL)const;\
  public:\
  Load(const void *fp, size_t nSize, LOADSTORESTATUS* size);\
  Store(void *fp, size_t nSize, LOADSTORESTATUS* size)const;


#define IMPLEMENT_LOADSTORE_CLASS_BASEDATA(class_name,base_class_name,meta_class_name)\
  IMPLEMENT_DYNCREATE_CLASS_BASEDATA(class_name,base_class_name,meta_class_name);\
  IMPLEMENT_LOADSTORE_CLASS_FUNCTIONS(class_name,base_class_name);



// HELPERS ///////////////////////////////////////////////////////////////////

#define XCOBJECT_DERIVED_CLASSES_COUNT(meta_class) \
  XCOBJECT_DerivedClassesDump( \
    RUNTIME_CLASS(meta_class), \
    meta_class::GetClassesListHead(), \
    sizeof(meta_class::classid##meta_class), \
    0)
  
#define XCOBJECT_DERIVED_CLASSES_DUMP(meta_class,isSignature) \
  XCOBJECT_DerivedClassesDump( \
    RUNTIME_CLASS(meta_class), \
    meta_class::GetClassesListHead(), \
    ((isSignature)?-(int)sizeof(meta_class::classid##meta_class):(int)sizeof(meta_class::classid##meta_class)), \
    1)

XCOBJECT_DerivedClassesDump(CRuntimeClass* pRuntimeClass, const void* pList, int nSizeOf=0, int nDump=1);


// Macro to obtain initialized classes data from static library
#define XCOBJECT_CLASS_LIBRARY_INITIALIZATION(class_name,meta_class) \
  meta_class::class_create_##meta_class \
  XCOBJECT_class_librery_initialization_##class_name##meta_class [] = \
    { class_name::the_class_create_##class_name##meta_class };

// Macro to obtain initialized classes data from static library
#define XCOBJECT_CLASS_INITIALIZATION(class_name,meta_class) \
  volatile extern __declspec(selectany) meta_class::class_create_##meta_class * \
  XCOBJECT_class_initialization_##class_name##meta_class = \
    &class_name::the_class_create_##class_name##meta_class;

#endif/*__XCOBJECT_H*/
#pragma once
