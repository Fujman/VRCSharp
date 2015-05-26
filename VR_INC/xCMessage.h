#ifndef __XCMESSAGE_H
#define __XCMESSAGE_H
#include "xCResLoad.h"
#include "xdebug.h"
#include "xCString.h"

////////////////////////////////////////////////////////////////////////////////////

#ifdef  MULTILANG
#define MULTILANGMESSAGES 1
#endif

////////////////////////////////////////////////////////////////////////////////////
// CString resource oriented extensions

#if IS_CSTRING_UNICODE
CString ResourceMessage(UINT nID, const wchar_t* psz=NULL);//AY 25.05.2010
CString ResourceMessage(UINT nID, const char*    psz     );
#else
CString ResourceMessage(UINT nID, const wchar_t* psz     );//AY 25.05.2010
CString ResourceMessage(UINT nID, const char*    psz=NULL);
#endif

////////////////////////////////////////////////////////////////////////////////////
// CString extensions implementation

__inline CString __ResourceMessage__(UINT nID, const char* psz) {
  CString sz = FormatErrorString(nID);
  if( !sz.IsEmpty() )
    return sz;
  RESOURCE_MESSAGE_DEFAULT(psz);
}
__inline CString __ResourceMessage__(UINT nID, const wchar_t* psz) {
  CString sz = FormatErrorString(nID);
  if( !sz.IsEmpty() )
    return sz;
  RESOURCE_MESSAGE_DEFAULT(psz);
}


#if defined(MULTILANGMESSAGES)
__inline CString __ResourceMessageML(UINT nID, const char* psz) 
{
  CString sz;
  if( LoadMultilanguageResourceMessage(sz, nID) )
    return sz;
  RESOURCE_MESSAGE_DEFAULT(psz);
}
__inline CString __ResourceMessageML(UINT nID, const wchar_t* psz) 
{
  CString sz;
  if( LoadMultilanguageResourceMessage(sz, nID) )
    return sz;
  RESOURCE_MESSAGE_DEFAULT(psz);
}
#endif


__inline CString ResourceMessage(UINT nID, const char* psz) {
#if defined(MULTILANGMESSAGES)
  return __ResourceMessageML(nID, psz);
#else
  return __ResourceMessage__(nID, psz);
#endif
}

__inline CString ResourceMessage(UINT nID, const wchar_t* psz) {
#if defined(MULTILANGMESSAGES)
  return __ResourceMessageML(nID, psz);
#else
  return __ResourceMessage__(nID, psz);
#endif
}


#endif//__XCMESSAGE_H