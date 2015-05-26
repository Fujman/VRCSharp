#ifndef __YPTR_H
#define __YPTR_H

/////////////////////////////////////////////////////////////////////////////
// YPTR: smart pointers templete classes collection with auto deleting memory
//
// Typical usage:
#if  0
      struct YStr {
        int dummy;
      };
      class  YObj: public YStr { public:
        YObj(int i=0);
      };

      YArrPtr<YObj>  ao = new YObj[11];//default constructors used //delete []
      YObjPtr<YObj>  po = new YObj(33);//special constructor used  //delete
      YPtr<YStr>     ps = (YStr*) malloc(11*sizeof(YStr));         //free()
      YPtr<long>     pl = (long*) malloc(11*sizeof(long));         //free()
      YVoidPtr<>     p  = malloc(11);                              //free()
#endif

/////////////////////////////////////////////////////////////////////////////
// YPtrBase
template <int STORAGE=0/*malloc*/, class T=BYTE/*byte_t*/>
class YPtrBase
{
public:
  typedef BYTE  byte_t;
public:
  enum { storage_malloc  = 0 }; //T* p = malloc(size). calloc(size)
  enum { storage_new     = 1 }; //T* p = new T
  enum { storage_array   = 2 }; //T* p = new T[size]
#if defined(_WINDOWS) || defined(WIN32)
  enum { storage_global  = 3 }; //T* p = ::GlobalAlloc(GPTR,size)
  enum { storage_local   = 4 }; //T* p = ::LocalAlloc(LPTR,size)
#endif
#ifdef WIN32
  enum { storage_heap    = 5 }; //T* p = ::HeapAlloc(::GetProcessHeap(),0,size)
  enum { storage_virtual = 6 }; //T* p = ::VirtualAlloc(NULL,size,MEM_COMMIT,?)
#endif
  enum { storage_vmalloc = 7 }; //T* p = vmalloc(size)

	static  T* Alloc(size_t size=0);
	static  T* ReAlloc(T* p, size_t size);
	static  T* Free(T* p);

	typedef T  YObjClass;
	typedef T* YPtrClass;
};

/////////////////////////////////////////////////////////////////////////////
// YBasePtr
template <int STORAGE=YPtrBase<>::storage_malloc, class T=YPtrBase<>::byte_t>
class YBasePtr : public YPtrBase<STORAGE,T>
{
public:
	YBasePtr()                                    { p = NULL; }
	YBasePtr(const YBasePtr<STORAGE,T>& lp)       { p = lp.p; }
	YBasePtr(T* lp)                               { p = lp;	}
	~YBasePtr();
	T* operator=(const YBasePtr<STORAGE,T>& lp)   { return (T*)(p = lp.p); 	}
	T* operator=(T* lp)                           { return (T*)(p = lp); 	}

	operator T*() const                           { return (T*)p; }
  //T& operator[](unsigned i) const   //can't be implemented in common case
  //T& operator *() const;            //can't be implemented in common case
	//T* operator->() const;            //can't be implemented in common case
	T** operator&();                              //see YPtr.inl for comments

//inheritable operators
	bool operator !() const                       { return (p == NULL); 	}
	bool operator <(T* pT) const                  {	return p < pT;	}
	bool operator >(T* pT) const                  {	return p > pT;	}
	bool operator<=(T* pT) const                  {	return p <= pT;	}
	bool operator>=(T* pT) const                  {	return p >= pT;	}
	bool operator==(T* pT) const                  { return p == pT; }
	bool operator!=(T* pT) const                  { return p != pT; }

	int  operator -(T* pT) const                  { return p - pT; }
	T*   operator -(int i) const                  { return p - i; }
	T*   operator +(int i) const                  { return p + i; }

//implementation
	T* p;
};

/////////////////////////////////////////////////////////////////////////////
// YVoidPtr - special case for void* pointers without dereference operators
template <int STORAGE=YBasePtr<>::storage_malloc>
class YVoidPtr : public YBasePtr<STORAGE,void>
{
public:
	YVoidPtr()                                    {}
	YVoidPtr(const YVoidPtr<STORAGE>& lp)         { p = lp.p; }
	YVoidPtr(void* lp)                            { p = lp; }
	void* operator=(const YVoidPtr<STORAGE>& lp)  { return (void*)(p = lp.p); }
	void* operator=(void* lp)                     { return (void*)(p = lp);}

	operator void*() const                        { return (void*)p; }
};

#pragma warning(disable:4284)

/////////////////////////////////////////////////////////////////////////////
// YPtr  - common case pointer with malloc/free storage by default
template <class T=YBasePtr<>::byte_t, int STORAGE=YBasePtr<>::storage_malloc>
class YPtr : public YBasePtr<STORAGE,T>
{
public:
	YPtr()                                        {}
	YPtr(const YPtr<T,STORAGE>& lp)               { p = lp.p;	}
	YPtr(T* lp)                                   {	p = lp; }
	T* operator=(const YPtr<T,STORAGE>& lp)       { return (T*)(p = lp.p); }
	T* operator=(T* lp)                           { return (T*)(p = lp); }

	operator T*() const                           { return (T*)p;	}
	T& operator *() const                         { ASSERT(p!=NULL); return *p;	}
	T* operator->() const                         { ASSERT(p!=NULL); return p; }
};

/////////////////////////////////////////////////////////////////////////////
// YObjPtr  - common case pointer with new/delete storage by default for C++ objects
template <class T=YBasePtr<>::byte_t, int STORAGE=YBasePtr<>::storage_new>
class YObjPtr : public YBasePtr<STORAGE,T>
{
public:
	YObjPtr()                                     {}
	YObjPtr(const YObjPtr<T,STORAGE>& lp)         { p = lp.p;	}
	YObjPtr(T* lp)                                {	p = lp; }
	T* operator=(const YObjPtr<T,STORAGE>& lp)    { return (T*)(p = lp.p); }
	T* operator=(T* lp)                           { return (T*)(p = lp); }

	operator T*() const                           { return (T*)p;	}
	T& operator *() const                         { ASSERT(p!=NULL); return *p;	}
	T* operator->() const                         { ASSERT(p!=NULL); return p; }
};

/////////////////////////////////////////////////////////////////////////////
// YArrPtr  - common case pointer with new[]/delete[] storage by default for C++ arrays of objects
template <class T=YBasePtr<>::byte_t, int STORAGE=YBasePtr<>::storage_array>
class YArrPtr : public YBasePtr<STORAGE,T>
{
public:
	YArrPtr()                                     {}
	YArrPtr(const YArrPtr<T,STORAGE>& lp)         { p = lp.p;	}
	YArrPtr(T* lp)                                {	p = lp; }
	T* operator=(const YArrPtr<T,STORAGE>& lp)    { return (T*)(p = lp.p); }
	T* operator=(T* lp)                           { return (T*)(p = lp); }

	operator T*() const                           { return (T*)p;	}
	T& operator *() const                         { ASSERT(p!=NULL); return *p;	}
	T* operator->() const                         { ASSERT(p!=NULL); return p; }
};

#pragma warning(default:4284)

#include "YPtr.inl"
/////////////////////////////////////////////////////////////////////////////
#endif//__YPTR_H
#pragma once