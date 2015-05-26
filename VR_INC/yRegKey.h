/*---------------------------------------------------------------------------\
| Class: YRegKey                           Language: C++     Model: All      |
\---Last change 26.06.01 18:01pm---Copyright (c) 2001, Anton Yavorsky, KPI--*/

// Attention! On OS error throw provided!

#ifndef  __YREGKEY_H
#define  __YREGKEY_H

#include <afxcoll.h>
#include "xCExcept.h"

class YRegKey
{
protected:
  HKEY   m_hKey;
  REGSAM m_regsam;
public:
  YRegKey() {m_hKey = NULL;}
  ~YRegKey() {Close();}
  operator HKEY() const
    { return m_hKey; }

// Attributes
public:
  BOOL  isValueExists(DWORD dwType, LPCTSTR lpszValueName = NULL, COsException* e = NULL);
  DWORD GetValueSize(LPCTSTR lpszValueName = NULL, COsException* e = NULL);
  DWORD GetValueType(LPCTSTR lpszValueName = NULL, COsException* e = NULL);
  int   GetValue(DWORD dwType, void* lpValue, UINT nSize, LPCTSTR lpszValueName = NULL, COsException* e = NULL);//throw COsException
  int   SetValue(DWORD dwType, const void* lpValue, UINT nSize, LPCTSTR lpszValueName = NULL, COsException* e = NULL);//throw COsException
  int   DeleteValue(LPCTSTR lpszValueName = NULL, COsException* e = NULL);//throw COsException
  int   DeleteKey(LPCTSTR lpszKeyName, COsException* e = NULL);//throw COsException

  int   SetString(LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL, COsException* e = NULL);//throw COsException
  int   SetBinary(const void* lpValue, UINT nSize, LPCTSTR lpszValueName = NULL, COsException* e = NULL);//throw COsException
  int   SetInt(DWORD dwValue, LPCTSTR lpszValueName = NULL, COsException* e = NULL);//throw COsException
  int   GetString(CString& szValue, LPCTSTR lpszValueName = NULL, COsException* e = NULL);//throw COsException, CMemoryException
  int   GetBinary(CByteArray& ab, LPCTSTR lpszValueName = NULL, COsException* e = NULL);//throw COsException, CMemoryException
  int   GetInt(DWORD& dwValue, LPCTSTR lpszValueName = NULL, COsException* e = NULL);//throw COsException

  CString GetDefStr(LPCTSTR szValue, LPCTSTR lpszValueName = NULL, COsException* e = NULL);//throw COsException, CMemoryException
  DWORD   GetDefInt(DWORD dwValue, LPCTSTR lpszValueName = NULL, COsException* e = NULL);//throw COsException

// Statics
  static BOOL   isKeyExists(HKEY hKey, LPCTSTR lpszKeyName, COsException* e = NULL);
  static BOOL   isValueExists(DWORD dwType, HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName = NULL, COsException* e = NULL);
  static DWORD  GetValueSize(HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName = NULL, COsException* e = NULL);
  static DWORD  GetValueType(HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName = NULL, COsException* e = NULL);
  static int    GetValue(DWORD dwType, void* lpValue, UINT nSize, HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName = NULL, COsException* e = NULL);//throw COsException
  static int    SetValue(DWORD dwType, const void* lpValue, UINT nSize, HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName = NULL, COsException* e = NULL);//throw COsException
  static int    DeleteValue(HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName = NULL, COsException* e = NULL);//throw COsException
  static int    DeleteKey(HKEY hKey, LPCTSTR lpszKeyName, COsException* e = NULL);//throw COsException

  static int    SetString(LPCTSTR szValue,             HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName = NULL, COsException* e = NULL); //throw COsException
  static int    SetBinary(const BYTE* ab, UINT nSize,  HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName = NULL, COsException* e = NULL); //throw COsException
  static int    SetInt(DWORD dw,                       HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName = NULL, COsException* e = NULL); //throw COsException
  static int    GetString(CString& szValue,            HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName = NULL, COsException* e = NULL); //throw COsException, CMemoryException
  static int    GetBinary(CByteArray& ab,              HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName = NULL, COsException* e = NULL); //throw COsException, CMemoryException
  static int    GetInt(DWORD& dw,                      HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName = NULL, COsException* e = NULL); //throw COsException

  static CString GetDefStr(LPCTSTR szValue,            HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName = NULL, COsException* e = NULL); //throw COsException, CMemoryException
  static DWORD   GetDefInt(DWORD dwValue,              HKEY hKey, LPCTSTR lpszKeyName, LPCTSTR lpszValueName = NULL, COsException* e = NULL); //throw COsException

  static LPCTSTR GetKeyText(HKEY hkey, int* pnLength=NULL);

// Operations
public:
  int   CreateInMemory(HKEY hKey, LPCTSTR lpszKeyName, REGSAM samDesired = KEY_ALL_ACCESS, COsException* e = NULL);//throw COsException
  int   Create(HKEY hKey, LPCTSTR lpszKeyName, REGSAM samDesired = KEY_ALL_ACCESS, COsException* e = NULL);//throw COsException
  int   Open(HKEY hKey, LPCTSTR lpszKeyName, REGSAM samDesired = KEY_READ, COsException* e = NULL);//throw COsException
  int   Close(COsException* e = NULL);//throw COsException

// Overrides

// Implementation
protected:

};

#endif// __YREGKEY_H
