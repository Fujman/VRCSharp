#ifndef __YPOINTER_H
#define __YPOINTER_H
#include "vmalloc.h"
#include "emalloc.h"

#ifdef __cplusplus
// C++ declarations \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
                                                              //Usage:
#define AUTO_DELETE_OBJECT(p)     AutoDeleteObject(p)         // CObject* p=new CObject; AUTO_DELETE_OBJECT(p)
#define AUTO_DELETE_POINTER(p)    AutoDeletePointer(p)        // type* p=new type;       AUTO_DELETE_POINTER(p);
#define AUTO_DELETE_ARRAY(p)      AutoDeleteArray(p)          // type* p=new type[1];    AUTO_DELETE_ARRAY(p);
#define AUTO_DELETE_MEMORY(p)     AutoDeleteMemory(p)         // void* p=malloc(1);      AUTO_DELETE_MEMORY(p);
#define AUTO_DELETE_VIRTUAL(p)    AutoDeleteVirtual(p)        // void* p=v_malloc(1);    AUTO_DELETE_VIRTUAL(p);
#define AUTO_DELETE_EXTERN(p)     AutoDeleteExtern(p)         // void* p=e_malloc(1);    AUTO_DELETE_EXTERN(p);
#define AUTO_DELETE_COTASKMEM(p)  AutoDeleteCoTaskMem(p)      // LPVOID p=::CoTaskMemAlloc(1); AUTO_DELETE_COTASK(p);
#define AUTO_DELETE_HGLOBAL(h,p)  AutoDeleteWindowsGlobal(h,p)// HGLOBAL h=GlobalAlloc(); void* p=::GlobalLock(); AUTO_DELETE_HGLOBAL(h,p); or { HGLOBAL h=::GlobalAlloc();AUTO_DELETE_HGLOBAL(h,0); }
#define AUTO_DELETE_HLOCAL(h,p)   AutoDeleteWindowsLocal(h,p) // HLOCAL h=::LocalAlloc(); void* p=::LocalLock();  AUTO_DELETE_HLOCAL(h,p);  or { HLOCAL h=::LocalAlloc();AUTO_DELETE_HLOCAL(h,0); }
#define AUTO_CLOSE_HANDLE(h)      AutoCloseWindowsHandle(h)   // HANDLE h=::Create*();   AUTO_CLOSE_HANDLE(h);

#define AUTO_DELETE_DISABLE(p)    p##__autodelete.disable();
#define AUTO_CLOSE_DISABLE(p)     p##__autoclose.disable();

// C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

class YAutoDeleteObject;          // new CObject();

class YAutoDeletePointer;         // new int;
class YAutoDeleteArray;           // new int[];
class YAutoDeleteMemory;          // malloc();
class YAutoDeleteVirtual;         // v_malloc();
class YAutoDeleteExtern;          // e_malloc();

#ifdef _WINDOWS
class YAutoDeleteCoTaskMem;       //::CoTaskMemAlloc()
class YAutoDeleteWindowsGlobal;   //::GlobalAlloc()
class YAutoDeleteWindowsLocal;    //::LocalAlloc()
class YAutoCloseWindowsHandle;    //::CloseHandle()
#endif//WINDOWS

////////////////////////
#ifdef __AFX_H__
class CObject;
class YAutoDeleteObject  //Usage: CObject* p=new CObject; AutoDeleteObject(p)
{
  void* *ptr;
public:
  YAutoDeleteObject(CObject* *p)
    { ptr = (void* *)p; }
  ~YAutoDeleteObject() {
    if(ptr==NULL)
      return;
    if(*ptr!=NULL)
      delete (CObject*)*ptr;
    *ptr = NULL;
  }
  void enable(void* p)
    { ptr = (void* *)p; ASSERT(!!!"may be programmer error"); }
  void disable()
    { ptr = NULL; }
};
#define AutoDeleteObject(p)  YAutoDeleteObject p##__autodelete(&(CObject*&)(p));
#endif
////////////////////////
class YAutoDeletePointer //Usage: type* p=new type; AutoDeletePointer(p);
{
  void* *ptr;
public:
  YAutoDeletePointer(void* p)
    { ptr = (void* *)p; }
  ~YAutoDeletePointer() {
    if(ptr==NULL)
      return;
    if(*ptr!=NULL)
      delete *ptr;
    *ptr = NULL;
  }
  void enable(void* p)
    { ptr = (void* *)p; ASSERT(!!!"may be programmer error"); }
  void disable()
    { ptr = NULL; }
};
#define AutoDeletePointer(p)  YAutoDeletePointer p##__autodelete(&(p));
////////////////////////
class YAutoDeleteArray   //Usage: type* p=new type[2]; AutoDeleteArray(p);
{
  void* *ptr;
public:
  YAutoDeleteArray(void* p)
    { ptr = (void* *)p; }
  ~YAutoDeleteArray() {
    if(ptr==NULL)
      return;
    if(*ptr!=NULL)
      delete [] *ptr;
    *ptr = NULL;
  }
  void enable(void* p)
    { ptr = (void* *)p; ASSERT(!!!"may be programmer error"); }
  void disable()
    { ptr = NULL; }
};
#define AutoDeleteArray(p)  YAutoDeleteArray p##__autodelete(&(p));
////////////////////////
class YAutoDeleteMemory  //Usage: void* p=malloc(1); AutoDeleteMemory(p);
{
  void* *ptr;
public:
  YAutoDeleteMemory(void* p)
    { ptr = (void* *)p; }
  ~YAutoDeleteMemory() {
    if(ptr==NULL)
      return;
    if(*ptr!=NULL)
      free(*ptr);
    *ptr = NULL;
  }
  void enable(void* p)
    { ptr = (void* *)p; ASSERT(!!!"may be programmer error"); }
  void disable()
    { ptr = NULL; }
};
#define AutoDeleteMemory(p)  YAutoDeleteMemory p##__autodelete(&(p));

////////////////////////
#ifdef  __VMALLOC_H

class YAutoDeleteVirtual  //Usage: void* p=v_malloc(1); YAutoDeleteVirtual _(&p);
{
  void* *ptr;
public:
  YAutoDeleteVirtual(void* p)
    { ptr = (void* *)p; }
  ~YAutoDeleteVirtual() {
    if(ptr==NULL)
      return;
    if(*ptr!=NULL)
      v_free(*ptr);
    *ptr = NULL;
  }
  void enable(void* p)
    { ptr = (void* *)p; ASSERT(!!!"may be programmer error"); }
  void disable()
    { ptr = NULL; }
};
#define AutoDeleteVirtual(p)  YAutoDeleteVirtual p##__autodelete(&(p));

#endif//__VMALLOC_H
////////////////////////
#ifdef  __EMALLOC_H

class YAutoDeleteExtern   //Usage: void* p=v_malloc(1); YAutoDeleteVirtual _(&p);
{
  void* *ptr;
public:
  YAutoDeleteExtern(void* p)
    { ptr = (void* *)p; }
  ~YAutoDeleteExtern() {
    if(ptr==NULL)
      return;
    if(*ptr!=NULL)
      e_free(*ptr);
    *ptr = NULL;
  }
  void enable(void* p)
    { ptr = (void* *)p; ASSERT(!!!"may be programmer error"); }
  void disable()
    { ptr = NULL; }
};
#define AutoDeleteExtern(p)   YAutoDeleteExtern  p##__autodelete(&(p));

#endif//__EMALLOC_H

#ifdef _WINDOWS
#ifdef WINOLEAPI
////////////////////////
class YAutoDeleteCoTaskMem //Usage: LPVOID p=::CoTaskMem(1); AutoDeleteCoTaskMem(p);
{
  void* *ptr;
public:
  YAutoDeleteCoTaskMem(void* p)
    { ptr = (void* *)p; }
  ~YAutoDeleteCoTaskMem() {
    if(ptr==NULL)
      return;
    if(*ptr!=NULL)
      ::CoTaskMemFree((LPVOID)*ptr);
    *ptr = NULL;
  }
  void enable(void* p)
    { ptr = (void* *)p; ASSERT(!!!"may be programmer error"); }
  void disable()
    { ptr = NULL; }
};
#define AutoDeleteCoTaskMem(p)  YAutoDeleteCoTaskMem p##__autodelete(&(p));

#endif
////////////////////////
class YAutoDeleteWindowsGlobal //Usage: void* p=::GlobalAlloc(); AutoDeleteWindowsGlobal(p);
{
  void* *ptr;
  void* pMem;
public:
  YAutoDeleteWindowsGlobal(void* pHandle, void* pMemory)
    { ptr = (void* *)pHandle; pMem = pMemory; }
  ~YAutoDeleteWindowsGlobal() {
    if(ptr==NULL)
      return;
    if(pMem!=NULL)
      { ASSERT(*ptr!=NULL); VERIFY( ::GlobalUnlock(*(HGLOBAL*)ptr) ); pMem = NULL; }
    if(*ptr!=NULL)
      if(::GlobalFree(*(HGLOBAL*)ptr)==NULL)
        *ptr = NULL;
    ASSERT(*ptr==NULL);
  }
  void enable(void* pHandle, void* pMemory)
    { ptr = (void* *)pHandle; pMem = pMemory; ASSERT(!!!"may be programmer error"); }
  void disable()
    { ptr = NULL; pMem = NULL; }
};
#define AutoDeleteWindowsGlobal(h,p)  YAutoDeleteWindowsGlobal p##__autodelete(&(h),(p));

////////////////////////
class YAutoDeleteWindowsLocal //Usage: void* p=::LocalAlloc(); AutoDeleteWindowsLocal(p);
{
  void* *ptr;
  void* pMem;
public:
  YAutoDeleteWindowsLocal(void* pHandle, void* pMemory)
    { ptr = (void* *)pHandle; pMem = pMemory; }
  ~YAutoDeleteWindowsLocal() {
    if(ptr==NULL)
      return;
    if(pMem!=NULL)
      { ASSERT(*ptr!=NULL); VERIFY( ::LocalUnlock(*(HGLOBAL*)ptr) ); pMem = NULL; }
    if(*ptr!=NULL)
      if(::LocalFree(*(HLOCAL*)ptr)==NULL)
        *ptr = NULL;
    ASSERT(*ptr==NULL);
  }
  void enable(void* pHandle, void* pMemory)
    { ptr = (void* *)pHandle; pMem = pMemory; ASSERT(!!!"may be programmer error"); }
  void disable()
    { ptr = NULL; pMem = NULL; }
};
#define AutoDeleteWindowsLocal(h,p)  YAutoDeleteWindowsLocal p##__autodelete(&(h),(p));

////////////////////////
class YAutoCloseWindowsHandle //Usage: HANDLE h=::Create*(...); AutoCloseWindowsHandle(h);
{
  void* *ptr;
public:
  YAutoCloseWindowsHandle(void* p)
    { ptr = (void* *)p; }
  ~YAutoCloseWindowsHandle() {
    if(ptr==NULL)
      return;
    if(*ptr!=NULL)
      if( ::CloseHandle(*(HANDLE*)ptr) )
        *ptr = NULL;
    ASSERT(*ptr==NULL);
  }
  void enable(void* p)
    { ptr = (void* *)p; ASSERT(!!!"may be programmer error"); }
  void disable()
    { ptr = NULL; }
};
#define AutoCloseWindowsHandle(p)  YAutoCloseWindowsHandle p##__autoclose(&(p));
#endif//_WINDOWS

///////////////////////////////////////////////////////////////////////////////////////
// class definitions //////////////////////////////////////////////////////////////////

#define DEFINE_ALL_PTR_CONVERSIONS_OPERATORS(ptr) \
  operator void*() { return(ptr); }                                       \
  operator char*() { return((char*)ptr); }                                \
  operator short*(){ return((short*)ptr); }                               \
  operator int*()  { return((int*)ptr); }                                 \
  operator long*() { return((long*)ptr); }                                \
  operator unsigned char*() { return((unsigned char*)ptr); }              \
  operator unsigned short*(){ return((unsigned short*)ptr); }             \
  operator unsigned int*()  { return((unsigned int*)ptr); }               \
  operator unsigned long*() { return((unsigned long*)ptr); }              \
  operator float*()  { return((float*)ptr); }                             \
  operator double*() { return((double*)ptr); }                            \
  operator long double*() { return((long double*)ptr); }                  \
  operator const void*() const { return((const void *)ptr); }                   \
  operator const char*() const { return((const char*)ptr); }                    \
  operator const short*()const { return((const short*)ptr); }                   \
  operator const int*()  const { return((const int*)ptr); }                     \
  operator const long*() const { return((const long*)ptr); }                    \
  operator const unsigned char*() const { return((const unsigned char*)ptr); }  \
  operator const unsigned short*()const { return((const unsigned short*)ptr); } \
  operator const unsigned int*()  const { return((const unsigned int*)ptr); }   \
  operator const unsigned long*() const { return((const unsigned long*)ptr); }  \
  operator const float*()  const { return((const float*)ptr); }                 \
  operator const double*() const { return((const double*)ptr); }                \
  operator const long double*() const { return((const long double*)ptr); }

#endif//__cplusplus

#endif//__YPOINTER_H
#pragma once
