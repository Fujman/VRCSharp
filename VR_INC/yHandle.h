#ifndef __YHANDLE_H
#define __YHANDLE_H

////////////////////////////////////////////////////////////////////////////////////
// YHANDLE, YHandle (multithreading ready, platform dependent!)

// C,C++ declarations \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

#define YHANDLE_INVALID ((void*)0xFFFFFFFF)
#define YHANDLE_INITIAL ((void*)0x00000000)
#define YHANDLE_NULL    ((void*)0x00000000)
#define YHANDLE_NONAMED ((LPCSTR)0xFFFFFFFF)

typedef void*   YHANDLE;

// C compatible global declarations /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef  __cplusplus
#define _0 =0
extern "C" {
#endif//__cplusplus

typedef LPVOID (*YHANDLE_OBJECT_DESTRUCTOR)(LPVOID pObject);

YHANDLE YHANDLE_CREATE_NAMESPACE(YHANDLE hnamespace, YHANDLE_OBJECT_DESTRUCTOR pfnDestructor _0, YHANDLE maxval _0, BOOL *pbExists _0, LPCSTR szNameSpace _0);
YHANDLE YHANDLE_CREATE_TEMPSPACE(LPCSTR szNameSpace, YHANDLE_OBJECT_DESTRUCTOR pfnDestructor _0, YHANDLE maxval _0, BOOL *pbExists _0);
YHANDLE YHANDLE_DELETE_NAMESPACE(YHANDLE hnamespace);
LPCSTR  YHANDLE_NAMEOF_NAMESPACE(YHANDLE hnamespace);
YHANDLE YHANDLE_HANDLE_NAMESPACE(LPCSTR szNameSpace);

YHANDLE YHANDLE_CREATE(LPVOID pObject, YHANDLE hnamespace _0, YHANDLE handle _0);
YHANDLE YHANDLE_DELETE(YHANDLE handle, YHANDLE hnamespace _0);
LPVOID  YHANDLE_OBJECT(YHANDLE handle, YHANDLE hnamespace _0);
BOOL  YHANDLE_IS_EXIST(YHANDLE handle, YHANDLE hnamespace _0);

#ifdef  __cplusplus
#undef  _0
}
#endif//__cplusplus
// C/C++ dual inline/global declarations /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef  __cplusplus
#define _0 =0
#ifdef  __YHANDLE_C
extern "C" {
#endif//__YHANDLE_C
#endif//__cplusplus

BOOL    YHANDLE_IS_VALID(YHANDLE handle);

#ifdef  __cplusplus
#undef  _0
#ifdef  __YHANDLE_C
}
#endif//__YHANDLE_C
#endif//__cplusplus

// C++ declarations \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef  __cplusplus

template <int HNAMESPACE=(int)YHANDLE_INVALID> class YHandleNamespace;
template <int HNAMESPACE=(int)YHANDLE_INVALID> class YHandle;

class   CMapPtrToPtr;
typedef CMapPtrToPtr CMapPtrToHandle;
typedef CMapPtrToPtr CMapHandleToPtr;

////////////////////////////////////////////////////////////////////////////////////
// YHandle
template <int HNAMESPACE /*= (int)YHANDLE_INVALID*/ >
class YHandle //initial value is 0, invalid values are 0, 0xFFFFFFFF
{ 
protected:      typedef YHandleNamespace<HNAMESPACE> YNamespace;
  YHANDLE       m_handle;
public:         
                YHandle()
                  { m_handle = YHANDLE_INITIAL; }

                YHandle(const YHandle& handle)
                  { m_handle = handle.m_handle; ASSERT(m_handle!=YHANDLE_INVALID); }

  YHandle&      operator= (const YHandle& handle)
                  { m_handle = handle; ASSERT(m_handle!=YHANDLE_INVALID); return *this;}

                YHandle(YHANDLE handle)
                  { m_handle = handle; ASSERT(m_handle!=YHANDLE_INVALID); }
                operator YHANDLE() const
                  { return m_handle; }

  BOOL          operator==(const YHandle& handle) const
                  { return m_handle==handle.m_handle; }
  BOOL          operator!=(const YHandle& handle) const
                  { return m_handle!=handle.m_handle; }

  BOOL          operator==(YHANDLE handle) const
                  { return m_handle==handle; }
  BOOL          operator!=(YHANDLE handle) const
                  { return m_handle!=handle; }
 
  YHandle       Invalidate()
                  { return( m_handle=YHANDLE_INVALID ); }
  BOOL          IsValid() const
                  { return YHANDLE_IS_VALID(m_handle); }

public: //auto create namespace if needed
  //for special or default namespaces
  YHandle       Create(void* pObject=NULL, YHANDLE handle=NULL);
  YHandle       Delete();
  void*         Object() const;
  BOOL          IsExist()const;
  //for according existing namespaces
  YHandle       Create(const YNamespace& , void* pObject=NULL, YHANDLE handle=NULL);
  YHandle       Delete(const YNamespace& );
  void*         Object(const YNamespace& ) const;
  BOOL          IsExist(const YNamespace&) const;
  //for according namespaces
  YHandle       Create(LPCSTR szNameSpace, void* pObject=NULL, YHANDLE handle=NULL);
  YHandle       Delete(LPCSTR szNameSpace);
  void*         Object(LPCSTR szNameSpace) const;
  BOOL          IsExist(LPCSTR sNameSpace) const;

public: //namespace must exists
  //for special or default namespaces
  static YHandle CreateHandle(void* pObject=NULL, YHANDLE handle=NULL);
  static YHandle DeleteHandle(YHandle handle);
  static void*   HandleObject(YHandle handle);
  static BOOL    IsHandleExist(YHandle handle);
  //for according existing namespaces
  static YHandle CreateHandle(const YNamespace& , void* pObject=NULL, YHANDLE handle=NULL);
  static YHandle DeleteHandle(const YNamespace& , YHandle handle);
  static void*   HandleObject(const YNamespace& , YHandle handle);
  static BOOL    IsHandleExist(const YNamespace& , YHandle handle);
  //for according namespaces
  static YHandle CreateHandle(LPCSTR szNameSpace, void* pObject=NULL, YHANDLE handle=NULL);
  static YHandle DeleteHandle(LPCSTR szNameSpace, YHandle handle);
  static void*   HandleObject(LPCSTR szNameSpace, YHandle handle);
  static BOOL    IsHandleExist(LPCSTR szNameSpace, YHandle handle);

public:
  YHANDLE       GetNameSpace() const
                  { ASSERT(sizeof(YHANDLE)==sizeof(int)); return (YHANDLE)HNAMESPACE; }
};

////////////////////////////////////////////////////////////////////////////////////
// YHandleNamespace
template <int HNAMESPACE /*= (int)YHANDLE_INVALID*/ >
class YHandleNamespace
{
protected:      typedef YHandle<HNAMESPACE> Yhandle;
  YHANDLE       m_hnamespace;
  BOOL          m_autodelete;
  static        p_hnamespace;
public://construction/destruction 
                YHandleNamespace(YHANDLE hnamespace = YHANDLE_INVALID);
                YHandleNamespace(YHANDLE hnamespace, YHANDLE_OBJECT_DESTRUCTOR pfnDestructor, YHANDLE maxval=0, BOOL bOpenIfExist=TRUE, LPCSTR szNameSpace=NULL);
                YHandleNamespace(LPCSTR szNameSpace, YHANDLE_OBJECT_DESTRUCTOR pfnDestructor, YHANDLE maxval=0, BOOL bOpenIfExist=TRUE);
                YHandleNamespace(const YHandleNamespace& hnamespace);
                ~YHandleNamespace();
  YHandleNamespace& operator = (const YHandleNamespace& hnamespace);
  YHANDLE       Create(BOOL bOpenIfExists=TRUE,                YHANDLE_OBJECT_DESTRUCTOR pfnDestructor=NULL, YHANDLE maxval=0, LPCSTR szNameSpace=NULL);
  YHANDLE       Create(BOOL bOpenIfExists, YHANDLE hnamespace, YHANDLE_OBJECT_DESTRUCTOR pfnDestructor=NULL, YHANDLE maxval=0, LPCSTR szNameSpace=NULL);
  YHANDLE       Create(BOOL bOpenIfExists, LPCSTR szNameSpace, YHANDLE_OBJECT_DESTRUCTOR pfnDestructor=NULL, YHANDLE maxval=0);
  YHANDLE       Done();  //stiil existing if created
  YHANDLE       Open(BOOL bCreateIfAbsent=FALSE,               YHANDLE_OBJECT_DESTRUCTOR pfnDestructor=NULL, YHANDLE maxval=0, LPCSTR szNameSpace=NULL);
  YHANDLE       Open(BOOL bCreateIfAbsent, YHANDLE hnamespace, YHANDLE_OBJECT_DESTRUCTOR pfnDestructor=NULL, YHANDLE maxval=0, LPCSTR szNameSpace=NULL);
  YHANDLE       Open(BOOL bCreateIfAbsent, LPCSTR szNameSpace, YHANDLE_OBJECT_DESTRUCTOR pfnDestructor=NULL, YHANDLE maxval=0);
  YHANDLE       Close(); //delete if created //call in destructor
  YHANDLE       Delete();//delete in any case
                operator LPCSTR () const;
                operator YHANDLE() const;

  static Yhandle MKHANDLE(YHANDLE);

public://handle operations attributes
  Yhandle       CreateHandle(void* pObject=NULL, YHANDLE handle=NULL);
  Yhandle       DeleteHandle(Yhandle handle);
  void*         HandleObject (Yhandle handle) const;
  BOOL          IsHandleExist(Yhandle handle) const;

public://attributes
  YHANDLE       GetHandle()   const  { return IsSpecial()||IsDefault()?(YHANDLE)HNAMESPACE:m_hnamespace; }
  LPCSTR        GetName()     const  { return YHANDLE_NAMEOF_NAMESPACE(GetHandle()); }
  BOOL          IsExists()    const  { return NULL!=YHANDLE_NAMEOF_NAMESPACE(GetHandle()); }

  BOOL          IsInvalid()   const  { return (m_hnamespace==YHANDLE_INVALID); }
  BOOL          IsTemporary() const  { return (HNAMESPACE==(int)YHANDLE_INVALID); }
  BOOL          IsDefault()   const  { return (HNAMESPACE==(int)YHANDLE_INITIAL); }
  BOOL          IsSpecial()   const  { return !IsTemporary() && !IsDefault(); }

  static YHANDLE GetHandle(LPCSTR szNameSpace);
  static LPCSTR  GetName(YHANDLE hnamespace);
  static BOOL    IsExists(YHANDLE hnamespace);
  static BOOL    IsExists(LPCSTR szNameSpace);

protected://implemetation
  static BOOL   IsInvalid(YHANDLE h) { return (h==YHANDLE_INVALID); }
  static BOOL   IsInitial(YHANDLE h) { return (h==YHANDLE_INITIAL); }
  static BOOL   IsValid(YHANDLE h)   { return !IsInvalid(h) && !IsInitial(h); }

  BOOL          CanAssign(YHANDLE h) const;
  BOOL          OkCreate(YHANDLE h, BOOL autodelete) const;
  BOOL          OkDelete(YHANDLE h, BOOL autodelete) const;
#ifdef _DEBUG
  public: void  Dump(BOOL bFull=FALSE);
#else
  public: void  Dump(BOOL bFull=FALSE){}
#endif
};

// YHandleNamespace inline implementation //////////////////////////////////////////
#include "YHandleNamespace.inl"
#include "YHandle.inl"

#endif//__cplusplus

// C/C++ dual inline/global implementation /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#if      defined(__YHANDLE_C) || defined(__cplusplus)

#if     !defined(__YHANDLE_C) && defined(__cplusplus)
  #define YHANDLE_INLINE   inline
#else
  #define YHANDLE_INLINE //global
#endif//!defined(__YHANDLE_C) && defined(__cplusplus)

YHANDLE_INLINE BOOL    YHANDLE_IS_VALID(YHANDLE handle)
{
  return handle!=YHANDLE_INVALID &&
         handle!=YHANDLE_INITIAL;
}

#undef YHANDLE_INLINE

#endif// defined(__YHANDLE_C) || defined(__cplusplus)
////////////////////////////////////////////////////////////////////////////////////

#endif//__YHANDLE_H
#pragma once
