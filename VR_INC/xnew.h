//dumb MFC feature fixing - replace operator new
#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)
  #define DEBUG_NEW_FILE_LINE ,__FILE__,__LINE__
#else
  #define DEBUG_NEW_FILE_LINE
#endif

#ifdef _DEBUG

#ifndef  XNEW_ALREADY_INCLUDED
#define  XNEW_ALREADY_INCLUDED

#if defined(new) && defined(DEBUG_NEW)
#define  XNEW_MFC_MEMORY_CONTROL_USED
#undef   new
#endif

#else // XNEW_ALREADY_INCLUDED

#if defined(XNEW_MFC_MEMORY_CONTROL_USED) && defined(DEBUG_NEW)
#undef   XNEW_MFC_MEMORY_CONTROL_USED
#define  new DEBUG_NEW
#endif

#undef   XNEW_ALREADY_INCLUDED
#endif// XNEW_ALREADY_INCLUDED

#endif