/*---------------------------------------------------------------------------\
| Class: YRegKeyEx                         Language: C++     Model: flat     |
\---Last change 17.05.04 18:01-----Copyright (c) 2004, Sergej Kondratjuk,SRS*/

// Attention! On OS error throw provided!

#ifndef __YREGKEYEX_H
#define __YREGKEYEX_H
////////////////////////////////////////////////////////////////////////

#include "xCExcept.h"
#include "yArray.h"
#include "yRegKey.h"
#include "fs/fs2.h"

typedef   YFileTreeEntry YRegTreeEntry;
class     YRegKeyEx;
class     YRegKeyWatcher;

////////////////////////////////////////////////////////////////////////
// YRegKeyEx
class YRegKeyEx : public YRegKey {
  typedef YRegKey YParent;
public:
  enum          {MAX_KEY_LENGTH = MAX_PATH};

public://support of YRegKey //m_szBaseKey not defined
                YRegKeyEx();
                ~YRegKeyEx();

  int           Create(HKEY hBaseKey, LPCTSTR lpszKeyName, REGSAM samDesired = KEY_ALL_ACCESS, COsException* e = NULL);//throw COsException
  int           CreateInMemory(HKEY hBaseKey, LPCTSTR lpszKeyName, REGSAM samDesired = KEY_ALL_ACCESS, COsException* e = NULL);//throw COsException
  int           Open(HKEY hBaseKey, LPCTSTR lpszKeyName, REGSAM samDesired = KEY_READ, COsException* e = NULL);//throw COsException

public://destruction
  int           Close(COsException* e = NULL);//throw COsException
 
  static int    Delete(HKEY hBaseKey, LPCTSTR lpszKeyName, COsException* e = NULL);//throw COsException
  static int    DeleteTree(HKEY hBaseKey, LPCTSTR lpszKeyName, COsException* e = NULL);//throw COsException

public://support of YRegKeyEx // base key must opened during life of object!
                YRegKeyEx(HKEY hBaseKey, LPCTSTR lpszName, DWORD dwIndex=-1, LPCTSTR lpszBaseKey=NULL);

  int           Open(REGSAM samDesired = KEY_READ, COsException* e = NULL);
  int           Create(REGSAM samDesired = KEY_ALL_ACCESS, COsException* e = NULL);
  int           CreateInMemory(REGSAM samDesired = KEY_ALL_ACCESS, COsException* e = NULL);
  int           Delete(COsException* e = NULL);//throw COsException

public://support of subkey enumaration
                YRegKeyEx(const YRegKeyEx&);//simple copy! - don't close any handles
  YRegKeyEx&    operator=(const YRegKeyEx&);//simple copy! - don't close any handles
                   
  BOOL          IsSubKey() const { return m_dwIndex!=-1; }
  YRegKeyEx     GetSubKeyFirst(COsException* e = NULL);
  YRegKeyEx     GetSubKeyLast(COsException* e = NULL);
  YRegKeyEx     GetSubKeyPrev(const YRegKeyEx* pRegKey, COsException* e = NULL);
  YRegKeyEx     GetSubKeyNext(const YRegKeyEx* pRegKey, COsException* e = NULL);

public://support of values enumaration //TO DO
//int           GetValuesNum(COsException* e = NULL) const;
//CString       GetValueName(int iIndex, COsException* e = NULL) const;
//DWORD         GetValueType(int iIndex, COsException* e = NULL) const; //RegEnumValue

public://support of tree operations
  //Example:    YRegKeyEx source(hBaseKey,lpszBaseKey,lpszName); //is not opened now!
  //            YRegKeyEx target(hBaseKey,lpszBaseKey,lpszName); //is not opened now!
  //            source.Copy(target);
  //            //stil not opened!
  int           ReplaceTree(YRegKeyEx& keyTarget, YRegKeyWatcher* pWatcher = NULL);//{ target.DeleteTree(); sourcr.CopyTree(target); }
  int           CopyTree(YRegKeyEx& keyTarget, YRegKeyWatcher* pWatcher =NULL) ;
  int           MoveTree(YRegKeyEx& keyTarget, YRegKeyWatcher* pWatcher = NULL);
  int           DeleteTree(YRegKeyWatcher* pWatcher=NULL, BOOL bMustExists=FALSE);//throw COsException
  LONG          Import(LPCTSTR szFile, COsException* e = NULL);
  LONG          Export(LPCTSTR szFile, COsException* e = NULL);
  LONG          Dump(YDynamicArray<TCHAR>& szDump, COsException* e = NULL);

public://helpers
  static LONG   CopyTree(HKEY hSrcParent, HKEY hTargParent, LPCTSTR szSrcKey, LPCTSTR szTargKey, COsException* e = NULL);
  static LONG   DumpTree(YDynamicArray<TCHAR>& szDump, HKEY hSrcParent, LPCTSTR szSrcKey, COsException* e = NULL, void* pRecource=NULL);

public://attributes
  LPCTSTR       GetName() const//always stored
                  { return m_szName; }
  //LPCTSTR     GetBaseName() const;//stored by second constructor only, "" elsewhere
  //CString     GetFullName();// ==GetName()+GetBaseName()
//protected:
  //int         Set(HKEY hBaseKey, LPCTSTR lpszName, LPCTSTR lpszBaseKey=NULL);//for GetSubKeyFirst/GetSubKeyLast

protected://implementation
  int           CheckErr(BOOL bSuccess, YRegKeyWatcher* pWatcher, LPCTSTR szFile, COsException* e);
  int           CheckErr(BOOL bSuccess, YRegKeyWatcher* pWatcher, const YRegTreeEntry* pEntry, COsException* e);

  LONG          GetValue(DWORD nIndex, LPTSTR lpValueName, DWORD* lpdwNameLen,
                         DWORD* lpdwType, LPBYTE lpdwData, DWORD* lpdwDataSize, COsException* e);
  LONG          QueryInfo(DWORD* lpcSubKeys, DWORD* lpcMaxSubKeyLen,
                          DWORD* lpcValues,DWORD* lpcMaxValueNameLen, DWORD* lpcMaxValueLen, COsException* e=NULL);

  TCHAR         m_szName[MAX_KEY_LENGTH];    //relative path

  DWORD         m_dwIndex;//RegEnumKeyEx default: -1
  HKEY          m_hBaseKey;
  TCHAR         m_szBaseKey[MAX_KEY_LENGTH]; //full path to key (basekey)
};

////////////////////////////////////////////////////////////////////////
// YRegKeyWatcher
class YRegKeyWatcher {
public:
  enum /*ans*/{ ansABORT=-1, ansRETRY=0, ansOK=1, ansIGNORE=2 };
protected:
  int                           m_nErrors;
  int                           m_nSkips;
  int                           m_nRetries;//current operation
public://construction/destruction
                                YRegKeyWatcher();
public://notifications
  virtual int                   OnError(const YRegTreeEntry* pyfte, CException* e);//0-retry,1-ok,2-skip,-1-abort
  virtual int                   CheckOsErr(BOOL bSuccess, const YRegTreeEntry* pEntry);//0-retry,1-ok,2-skip,-1-abort
  virtual int                   CheckFsErr(BOOL bSuccess, UINT nError, const YRegTreeEntry* pEntry=NULL, HANDLE hFile=NULL);//0-retry,1-ok,2-skip,-1-abort
};

/*
  Enumeration:
  YRegKeyEx key; key.Open(...,"Hardware\\WAVEIN\\StandardWaveIn");
  for(YRegKeyEx subkey=key.GetSubKeyFirst(); subkey.IsSubKey(); subkey=key.GetSubKeyNext(&subkey))
  {
//  cout<<key.GetName()<<endl;
    //subkey.Open();   or    subkey.Create();
    //operations
    subkey.Close();
    //subkey.Delete();
    //subkey.DeleteTree();
  }
*/

/* create
  YRegKeyEx rkex(hBaseKey,lpszBaseKey,lpszName); //is not opened now!
  rkex.Create(KEY_READ,e);

  YRegKeyEx rkex1(); //is not opened now!
  rkex.Create(hBaseKey, lpszKeyName, KEY_ALL_ACCESS, e);
*/

/* copy/move/replace key 
  YRegKeyEx source(hBaseKey1,lpszBaseKey1,lpszName1); //is not opened now!
  YRegKeyEx target(hBaseKey2,lpszBaseKey2,lpszName2); //is not opened now!
  source.CopyTree(target);
  //  source.CopyTree(target);
  //  source.ReplaceTree(target);
  //  source.MoveTree(target);
  //stil not opened!
*/

#endif//__YREGKEYEX_H
#pragma once
