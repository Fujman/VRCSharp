#ifndef __XCRESOURCE
#define __XCRESOURCE

#ifdef _UNICODE
#define _NULLA
#define _NULLW =NULL
#else
#define _NULLA =NULL
#define _NULLW
#endif

#ifndef RT_DLGINIT
#define RT_DLGINIT  MAKEINTRESOURCE(240)
#endif

////////////////////////////////////////////////////////////////////////////////////
// multilanguage resource support
#if defined(MULTILANG) || defined(MULTILANGSTRINGS) //see yResLang.h for details
extern "C" BOOL    GetApplicationLanguageResourceHandles(HMODULE* pModules, const int* aPriorities/*NULL*/, int nPriorities/*0*/);//+NULL terminated
extern "C" WORD    GetApplicationLanguageID();
#endif

CString CString__MultilanguageResourceMessage(UINT nID, const wchar_t* psz _NULLW);//must be xCMessage.cpp recompiled - for libraries support
CString CString__MultilanguageResourceMessage(UINT nID, const char*    psz _NULLA);//must be xCMessage.cpp recompiled - for libraries support
CString CString__MultilanguageResourceString (UINT nID, const wchar_t* psz _NULLW);//must be xCString.cpp recompiled  - for libraries support
CString CString__MultilanguageResourceString (UINT nID, const char*    psz _NULLA);//must be xCString.cpp recompiled  - for libraries support
HGLOBAL CDialog__MultilanguageDialogTemplate (LPCTSTR lpszTemplate);               //must be xCDialog.cpp recompiled  - for libraries support
HGLOBAL CDialog__MultilanguageDialogTemplate (UINT     nIDTemplate);               //must be xCDialog.cpp recompiled  - for libraries support

BOOL    CString__LoadMultilanguageResourceMessage(CString& sz, UINT nID, WORD wLangID, const HMODULE* pModules,                    int* pError=NULL);
BOOL    CString__LoadMultilanguageResourceString (CString& sz, UINT nID, WORD wLangID, const HMODULE* pModules,                    int* pError=NULL);
HGLOBAL CDialog__LoadMultilanguageDialogTemplate (LPCTSTR  lpszTemplate, WORD wLangID, const HMODULE* pModules, LPCTSTR type=NULL, int* pError=NULL);
HGLOBAL CDialog__LoadMultilanguageDialogTemplate (UINT      nIDTemplate, WORD wLangID, const HMODULE* pModules, LPCTSTR type=NULL, int* pError=NULL);

CString CString__MultilanguageResourceFont(LPCTSTR szFont=NULL); //must be xCString.cpp recompiled - for libraries support
BOOL    CString__MapMultilanguageResourceFont(CString& sz, LPCTSTR font, CString& szMap);

////////////////////////////////////////////////////////////////////////////////////
// helpers AY 25.05.2010 :two additional resource module loading

//  RT_MESSAGETABLE: BOOL     bRet = CString__LoadMultilanguageResourceMessage(CString& sz, UINT nID, WORD wLangID, const HMODULE* pModules, int* pError=NULL);
//  RT_STRING:       BOOL     bRet = CString__LoadMultilanguageResourceString (CString& sz, UINT nID, WORD wLangID, const HMODULE* pModules, int* pError=NULL);
//  any:             HGLOBAL  hRet = CDialog__LoadMultilanguageDialogTemplate (             UINT nID, WORD wLangID, const HMODULE* pModules, LPCTSTR type=NULL, int* pError=NULL);
//  any:             HGLOBAL  hRet = CDialog__LoadMultilanguageDialogTemplate (         LPCTSTR szID, WORD wLangID, const HMODULE* pModules, LPCTSTR type=NULL, int* pError=NULL);

HGLOBAL/*or BOOL*/ LoadMultilanguageResource(LPCTSTR type, UINT     nID, CString* pSz=NULL, int* pError=NULL, WORD wLangID=0);
HGLOBAL/*or BOOL*/ LoadMultilanguageResource(LPCTSTR type, LPCTSTR szID, CString* pSz=NULL, int* pError=NULL, WORD wLangID=0);

//inline  int      LoadMultilanguageResourceMessageString(CString& sz, UINT nID, WORD wLangID=0);//see xCString.h

__inline  BOOL     LoadMultilanguageResourceMessage(CString& sz, UINT nID, int* pError=NULL, WORD wLangID=0) //AY 25.10.2010 add wLangID
                     { return (BOOL)LoadMultilanguageResource(RT_MESSAGETABLE, nID, &sz, pError, wLangID); }

__inline  BOOL     LoadMultilanguageResourceString(CString& sz, UINT nID, int* pError=NULL, WORD wLangID=0)  //AY 25.10.2010 add wLangID
                     { return (BOOL)LoadMultilanguageResource(RT_STRING, nID, &sz, pError, wLangID); }

__inline  HGLOBAL  LoadMultilanguageDialogTemplate (LPCTSTR lpszTemplate, LPCTSTR type=NULL, int* pError=NULL, WORD wLangID=0) //AY 25.10.2010 add wLangID
                     { return       LoadMultilanguageResource(type, lpszTemplate, NULL, pError, wLangID); }  

__inline  HGLOBAL  LoadMultilanguageDialogTemplate (UINT     nIDTemplate, LPCTSTR type=NULL, int* pError=NULL, WORD wLangID=0) //AY 25.10.2010 add wLangID
                     { return       LoadMultilanguageResource(type, nIDTemplate, NULL, pError, wLangID); }

////////////////////////////////////////////////////////////////////////////////////
// CString extensions implementation helpers

inline  UINT  __IsMultilanguageResourceMessageStringID(UINT nID)
{
  UINT STRINGS = 0x4078;//see vr_res/strings/strings.h: FACILITY_STRINGS|SEVERITY_DESCRIPTION
  BOOL bStrings = ((nID&0x0FFF0000)>>16)==(STRINGS&0x0FFF) || (nID&0xFFFF0000)==0;
  UINT nMsgID = (nID|(STRINGS<<16));
  return bStrings?nMsgID:0;
}
inline  BOOL __IsMultilanguageResourceMessageEventID(UINT nID)
{
  UINT EVENTS  = 0x4076;//see vr_res/strings/strings.h: FACILITY_EVENT|SEVERITY_DESCRIPTION
  BOOL bEvents = ((nID&0x0FFF0000)>>16)==(EVENTS &0x0FFF);
  return bEvents;
}
inline  BOOL __IsMultilanguageResourceMessageControlID(UINT nID)
{
  UINT CONTROLS = 0x4075;
  BOOL bControl = ((nID&0x0FFF0000)>>16)==(CONTROLS&0x0FFF);
  return bControl;
}

int     CString__FormatErrorStringV(CString& sz, DWORD dwError, LPCTSTR lpszFormat, va_list args);

#undef  _NULLA
#undef  _NULLW
#endif//__XCRESOURCE
#pragma once