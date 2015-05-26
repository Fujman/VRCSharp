#ifndef __XDEBUG_H
#define __XDEBUG_H

#ifndef DEBUGONLY
#ifdef _DEBUG
  #define DEBUGONLY(e)    e
  #define DEBUGBLOCK(e)   {e};
  #define __IS_DEBUG      (1)
#else
  #define DEBUGONLY(e)
  #define DEBUGBLOCK(e)   ;
  #define __IS_DEBUG      (0)
#endif
#endif

#define __IF_DEBUG(tru,fal) (__IS_DEBUG?(tru):(fal))

#define __PLACE__     C_FILE_LINE(__FILE__,__LINE__)

#define DEBUGPLACE(s) _T("%hs(%d): ") _T(s),C_FILE_LINE(__FILE__,__LINE__)
//same  DEBUGPLACE(s) _T("%hs(%d): ") _T(s),__FILE__,__LINE__ 

#pragma pack(push,1)
struct C_FILE_LINE
{
  const char* szFile;//order as in stack!
  int   nLine;       //order as in stack!
#ifdef  __cplusplus
  static inline const char* name(const char* s)
  {
    const char* szFile=s+strlen(s);
    for(; szFile>=s; --szFile) 
    {
      char c = *szFile;
      if(c=='\\' || c=='/')
        { ++szFile; break; }
    }
    return szFile;
  }
#endif//__cplusplus
};
#pragma pack(pop)

__inline struct C_FILE_LINE C_FILE_LINE(const char* s, int n)
{
  struct C_FILE_LINE a;
#ifdef  __cplusplus
  a.szFile = s;//C_FILE_LINE::name(s);//?
#else
  a.szFile = s;
#endif
  a.nLine = n;
  return a;
}

// debug notifications /////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#define _0 =0
#else
#define _0
#endif

int     xdebug_notify(int message, const char* file, int line, void* info _0);

int     xdebug_report(int type, const char *file, int line, const char *module, const char *format, ... );//_CrtDbgReport() analog

#define xdebug_break() __asm { int 3 } //_CrtDbgBreak() analog  

#undef _0
#ifdef __cplusplus
}//extern "C"
#endif

//Debug notifications support

#if defined(_DEBUG) || defined(XDEBUGFORCE)
#define XDEBUG_NOTIFY(e)    xdebug_notify(e,__FILE__,__LINE__,NULL)
#define XDEBUG_NOTIFY2(e,s) xdebug_notify(e,__FILE__,__LINE__,(void*)(s))
#else
#define XDEBUG_NOTIFY(e)    (0)
#define XDEBUG_NOTIFY2(e,s) (0)
#endif

#define XDEBUG_RESOURCE_STRING  1  //UINT nID
#define XDEBUG_UNKNOWN_STRING   2  //UINT nID
#define XDEBUG_RESOURCE_FONT    3  //"font"
#define XDEBUG_ANSI_TO_UNICODE  4  // "string"
#define XDEBUG_UNICODE_TO_ANSI  5  //L"string"
#define XDEBUG_RESOURCE_DIALOG  6  //UINT nID
#define XDEBUG_RESOURCE_MESSAGE 7  //UINT nID
#define XDEBUG_UNKNOWN_MESSAGE  8  //UINT nID
#define XDEBUG_STRING_ONLY      9  //UINT nID

#endif//__XDEBUG_H
#pragma once
