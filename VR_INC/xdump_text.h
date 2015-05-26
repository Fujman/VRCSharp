#ifndef  __XDUMP_TEXT_H
#define  __XDUMP_TEXT_H

#include "YText.h"
#include "YCookie.h"
#include "xCString.h"
#include "xCCmdLine.h"
#include "fs/fs.h"
#include "YRegKeyEx.h"

////////////////////////////////////////////////////////////////////////
// globals

CString  LoadMachineSettingsString(LPCSTR szSection, LPCSTR szName);
CString  LoadMachineSettingsString(LPCWSTR szSection, LPCWSTR szName);

////////////////////////////////////////////////////////////////////////
// class CDumpText

class CDumpText: public CText
{
  static YCookie s_cookie;
  YCookie        m_cookie;
  int            m_dumped;
  CString        CString_REGKEY_INI_;
public: 
                CDumpText(LPCTSTR szREGKEY_INI)
                  :m_cookie(s_cookie.Increase()) { m_dumped = 0; CString_REGKEY_INI_ = szREGKEY_INI; }

  CWinApp*      GetApp()
                  { return ::AfxGetApp(); }

  CDumpText&    operator+=(const CString& sz)
                { 
                  Add(sz);
                  for(int i=0; i<sz.GetLength(); i+=256){
                    TRACE(_T("%s"),sz.Mid(i,256));
                  }
                  return *this; 
                }
  CDumpText&    operator+=(LPCTSTR a_sz)
                { 
                  CString sz(a_sz);
                  operator+=(sz);
                  return *this; 
                }
  CDumpText&    operator+=(const CText& text)
                { 
                  for(int i=0; i<text.GetSize(); i++){
                    operator+=(text[i]); eol();
                  }
                  return *this; 
                }
  CDumpText&    eol()
                { 
                  CString sz;
                  if(GetSize()<=0)
                    return *this;
                  sz = GetAt(GetSize()-1);
                  if(sz.GetLength()<=0)
                    return *this;
                  if(sz[sz.GetLength()-1]=='\n')
                    return *this;
                  sz += _T("\n"); //TO DO: use modeCRLF?
                  TRACE(_T("\n"));
                  return *this;
                }
  CDumpText&    EOL()
                { 
                  (*this)+=_T("\n");
                  return *this;
                }
  
public:
//CWinApp  compatible
  virtual 
  CString       CWinApp__GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault = NULL)
                  { return GetApp()->GetProfileString(lpszSection, lpszEntry, lpszDefault); }
  virtual
  UINT          CWinApp__GetProfileInt( LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault )
                  { return GetApp()->GetProfileInt(lpszSection, lpszEntry, nDefault); }

  CString       GetProfileString( LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault = NULL )
                {
                  CString sz = CWinApp__GetProfileString(lpszSection, lpszEntry, lpszDefault);
                  *this += _T("HKEY_CURRENT_USER\\Software\\") + CString(GetApp()->m_pszRegistryKey) 
                              + CString(GetApp()->m_pszExeName)+ _T(".INI\\") + CString(lpszSection) + _T(":\n");
                  *this += _T("  [") + CString(lpszSection) + _T("] ") + CString(lpszEntry) +  _T("=\"") + sz + _T("\"\n");
                  return sz;
                }
  UINT          GetProfileInt( LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault )
                {
                  UINT u = CWinApp__GetProfileInt(lpszSection, lpszEntry, nDefault);
                  *this += _T("HKEY_CURRENT_USER\\Software\\") + CString(GetApp()->m_pszRegistryKey) 
                              + CString(GetApp()->m_pszExeName)+ _T(".INI\\") + CString(lpszSection) + _T(":\n");
                  *this += _T("  [") + CString(lpszSection) + _T("] ") + CString(lpszEntry) +  _T("=") + FormatString(_T("%d (0x%08.8X)"),u,u) + _T("\n");
                  return u;
                }
//Win32    compatible
  DWORD         GetPrivateProfileString(
                  LPCTSTR lpAppName,
                  LPCTSTR lpKeyName,
                  LPCTSTR lpDefault,
                  LPTSTR lpReturnedString,
                  DWORD nSize,
                  LPCTSTR lpFileName
                ){
                  DWORD dw = ::GetPrivateProfileString(lpAppName,lpKeyName,lpDefault,lpReturnedString,nSize,lpFileName);
                  *this += _T("") + CString(lpFileName) + _T(":\n");
                  *this += _T("  [") + CString(lpAppName) + _T("] ") + CString(lpKeyName) +  _T("=\"") + lpReturnedString + _T("\"\n");
                  return dw;
                }
  UINT          GetPrivateProfileInt(
                    LPCTSTR lpAppName,
                    LPCTSTR lpKeyName,
                    INT nDefault,
                    LPCTSTR lpFileName
                    ){
                  UINT u = ::GetPrivateProfileInt(lpAppName,lpKeyName,nDefault,lpFileName);
                  *this += _T("") + CString(lpFileName) + _T(":\n");
                  *this += _T("  [") + CString(lpAppName) + _T("] ") + CString(lpKeyName) +  _T("=") + FormatString(_T("%d (0x%08.8X)"),u,u) + _T("\n");
                  return u;
                }


//xCCmdLine compatible
  typedef const CString& CCMDLINE;
  CString       CCmdLine__GetCmdArg(CCMDLINE szCmdLine, int nArg)
                {
                  CString sz = ::CCmdLine__GetCmdArg(szCmdLine, nArg);
                  *this += FormatString(_T("ARG%d:\"")) + sz + _T("\"\n");
                  return sz;
                }

  BOOL          CCmdLine__IsCmdKey(CCMDLINE szCmdLine, LPCTSTR szKey, BOOL bAlredyUpper=FALSE)
                {
                  BOOL b = ::CCmdLine__IsCmdKey(szCmdLine, szKey, bAlredyUpper);
                  LPCTSTR szSlash = *szKey=='/'?_T("") : _T("/");
                  if(b)
                    *this += szSlash + CString(szKey) + _T("\n");
                  return b;
                }

  CString       CCmdLine__GetCmdKey(CCMDLINE szCmdLine, LPCTSTR szKey, BOOL bAlredyUpper=FALSE)
                {
                  CString sz = ::CCmdLine__GetCmdKey(szCmdLine, szKey, bAlredyUpper);
                  LPCTSTR szSlash = *szKey=='/'?_T("") : _T("/");
                  *this += szSlash + CString(szKey) + _T("=\"") + sz + _T("\"\n");
                  return sz;
                }

  BOOL          CCmdLine__IsCmdKey(CCMDLINE szCmdLine, LPCTSTR_COMPLEMENT szKey, BOOL bAlredyUpper=FALSE)
                  { return CCmdLine__IsCmdKey(szCmdLine, CString(szKey), bAlredyUpper); }

  CString       CCmdLine__GetCmdKey(CCMDLINE szCmdLine, LPCTSTR_COMPLEMENT szKey, BOOL bAlredyUpper=FALSE)
                  { return CCmdLine__GetCmdKey(szCmdLine, CString(szKey), bAlredyUpper); }

//CCmdLine compatible


//vr_court - REGKEY_INI compatible 
  CString       LoadMachineSettingsString(LPCSTR szSection, LPCSTR szName)
                {
                  CString sz = ::LoadMachineSettingsString(szSection, szName);
                  *this += _T("HKEY_LOCAL_MACHINE\\") + CString_REGKEY_INI_ + MS_SLASH + CString(szSection) + _T("\n");
                  *this += _T("  [") + CString(szSection) + _T("] ") + CString(szName) +  _T("=\"") + sz + _T("\"\n");
                  return sz;
                }
  CString       LoadMachineSettingsString(LPCWSTR szSection, LPCWSTR szName)
                {
                  CString sz = ::LoadMachineSettingsString(szSection, szName);
                  *this += _T("HKEY_LOCAL_MACHINE\\") + CString_REGKEY_INI_ + MS_SLASH + CString(szSection) + _T("\n");
                  *this += _T("  [") + CString(szSection) + _T("] ") + CString(szName) +  _T("=\"") + sz + _T("\"\n");
                  return sz;
                }

//YRegKey compatible (notify only)
  LPCTSTR       hkey_Name(HKEY hBaseKey)
                {
                  if(hBaseKey==HKEY_LOCAL_MACHINE) return _T("HKEY_LOCAL_MACHINE");
                  if(hBaseKey==HKEY_CURRENT_CONFIG)return _T("HKEY_CURRENT_CONFIG");
                  if(hBaseKey==HKEY_CURRENT_USER)  return _T("HKEY_CURRENT_USER");
                  if(hBaseKey==HKEY_USERS)         return _T("HKEY_USERS");
                  if(hBaseKey==HKEY_CLASSES_ROOT)  return _T("HKEY_CLASSES_ROOT");
                  if(hBaseKey==HKEY_DYN_DATA)      return _T("HKEY_DYN_DATA");
                  if(hBaseKey==HKEY_PERFORMANCE_DATA)  return _T("HKEY_PERFORMANCE_DATA");
                  return _T("");
                }

  int           key_Enum(HKEY hBaseKey, LPCTSTR lpszKeyName, REGSAM samDesired = KEY_READ, COsException* e = NULL)
                {
                  *this += CString(hkey_Name(hBaseKey)) + MS_SLASH + CString(lpszKeyName) + _T(" :REGKEY_ENUM\n");
                  return 0;
                }

  int           key_GetString(CString& szValue, HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName = NULL, COsException* e = NULL)
                {
                  if(!szValue.IsEmpty()) {
                    *this += CString(hkey_Name(hKey)) + MS_SLASH + CString(lpszKeyName) + _T(":\n");
                    *this += _T("  ") + CString(lpszValueName?lpszValueName:_T("")) +  _T("=\"") + szValue + _T("\"\n");
                  }
                  return 0;
                }

//CText::GetXmlProfileString compatible (notify only)
  CString       GetXmlProfileString(LPCTSTR szXML, CString& sz, LPCTSTR szSection, LPCTSTR szKey)
                {
                  if(!sz.IsEmpty()) {
                    *this += CString(szXML) + _T(":\n");
                    *this += _T("  [") + CString(szSection?szSection:_T("config")) + _T("] ") + CString(szKey) +  _T("=\"") + sz + _T("\"\n");
                  }
                  return sz;
                }
  ULONG         GetXmlProfileInt(LPCTSTR szXML, ULONG u, LPCTSTR szSection, LPCTSTR szKey)
                {
                  if(u!=0) {
                    *this += CString(szXML) + _T(":\n");
                    *this += _T("  [") + CString(szSection?szSection:_T("config")) + _T("] ") + CString(szKey) +  _T("=\"") + FormatString(_T("%d (0x%08.8X)"),u,u) + _T("\"\n");
                  }
                  return u;
                }
//variables
  CDumpText&    VariableString(LPCSTR szKey, LPCTSTR szValue, LPCSTR szInternal=NULL)
                {
                  *this += CString(szKey) + _T("\t:\"") + CString(szValue) + _T("\" ") + CString(szInternal?CString(_T("\t-"))+CString(szInternal):CString()) + _T("\n");
                  return *this;
                }
};

////////////////////////////////////////////////////////////////////////
// class TCDumpText

template <class CWINAPP> class TCDumpText: public CDumpText
{
public: 
                TCDumpText(LPCTSTR szREGKEY_INI)
                  :CDumpText(szREGKEY_INI) {};
  CWINAPP*      GetApp()
                  { return (CWINAPP*)::AfxGetApp(); }
  virtual 
  CString       CWinApp__GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault = NULL)
                  { return GetApp()->GetProfileString(lpszSection, lpszEntry, lpszDefault); }
  virtual
  UINT          CWinApp__GetProfileInt( LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault )
                  { return GetApp()->GetProfileInt(lpszSection, lpszEntry, nDefault); }
};


#endif//__XDUMP_TEXT_H
#pragma once
