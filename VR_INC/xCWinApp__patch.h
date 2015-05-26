#ifndef __XCWINAPP__PATCH_H
#define __XCWINAPP__PATCH_H

class CWinApp__patch : public CWinApp
{
public:
	// Profile settings (to the app specific .INI file, or registry)
	UINT GetProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault);
	CString GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault = NULL);
	BOOL GetProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPBYTE* ppData, UINT* pBytes);
//BOOL WriteProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue);
//BOOL WriteProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue);
//BOOL WriteProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPBYTE pData, UINT nBytes);
protected:
  HKEY GetAppRegistryKey();
  HKEY GetSectionKey(LPCTSTR lpszSection);
};

#endif//__XCWINAPP__PATCH_H
#pragma once


