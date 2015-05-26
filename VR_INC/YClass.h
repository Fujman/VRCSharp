#ifndef __YCLASS_H
#define __YCLASS_H
#ifdef  __cplusplus

/////////////////////////////////////////////////////////////////////////////
// YMetaClass
template<class YBASEDATA,class YCLASSINFO> class YMetaClass: public YBASEDATA
{
public:
  static YCLASSINFO*    CreateClass(YCLASSINFO* );
  static YCLASSINFO*    DeleteClass(YCLASSINFO* );
  static YCLASSINFO*    SearchClass(const YBASEDATA*);
  static YCLASSINFO*    FirstClass();
  static YCLASSINFO*    NextClass(YCLASSINFO*);
protected:
  static YCLASSINFO*    s_pClassesList;
  static DWORD          s_nClassesLock;
public:
  typedef YCLASSINFO    YBaseClassInfo;
  typedef YBASEDATA     YBaseDataType;
  typedef YMetaClass    YBaseMetaClass;
};

/////////////////////////////////////////////////////////////////////////////
// YClass
template<class YCLASS, class YPARENT> class YClass
{
public:
  typedef typename YPARENT::YBaseClassInfo YClassInfoType;
  struct                                YClassObject {YClassObject() {YClass<YCLASS,YPARENT>::RegistrateClass();}};
public:
  static           YClassInfoType*      RegistrateClass();
                                        YClass();
  static  volatile YClassInfoType       s_ClassInfo;
  static  volatile YClassObject*        s_pClassObj;
  static           YClassObject         s_ClassObj;
};

//s_ClassInfo must be defined manually with initializers list

/////////////////////////////////////////////////////////////////////////////
// Macro to manually initialization classes descriptions

#define YCLASS_DECLARE(class_name, class_parent) \
  volatile __declspec(selectany) \
    YClass<class_name,class_parent>::YClassObject* \
      YClass<class_name,class_parent>::s_pClassObj = \
        &YClass<class_name,class_parent>::s_ClassObj; \
  volatile __declspec(selectany) \
    YClass<class_name,class_parent>::YClassInfoType \
      YClass<class_name,class_parent>::s_ClassInfo

#define YCLASS_IMPLEMENT(class_name, class_parent) \
  YClass<class_name,class_parent>::YClassObject \
    YClass<class_name,class_parent>::s_ClassObj;

#define YCLASS_REGISTRATE(class_name, class_parent) \
  YClass<class_name,class_parent>::RegistrateClass();

/////////////////////////////////////////////////////////////////////////////
#ifndef YCLASS_NO_INL
#include "YClass.inl"
#endif//YCLASS_NO_INL

#endif//__cplusplus
#endif//__YCLASS_H
