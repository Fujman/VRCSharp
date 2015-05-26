//////////////////////////////////////////////////////////////////////////////
// yResourc.h
#ifndef __YRESOURC_H
#define __YRESOURC_H
#include "yResBase.h"
#include "yResLang.h"
#ifdef  __cplusplus
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////

class YResourceType;
class YResourceName;
class YResourceLanguage;
class YResource;
class YModuleResources;
class YFontResource;

/////////////////////////////////////////////////////////////////////////////
// YResourceType

class YResourceType {
  static int            GetStdTypeName(LPCTSTR lpszType, CString* pszName=NULL); // 0 - standard name (no save to CString)
  LPCTSTR               m_lpszType;
  CString               m_szType;
public:                 
                        YResourceType(LPCTSTR lpszType)
                          { Init(lpszType); }
                        YResourceType()
                          { m_lpszType = NULL; }
                        YResourceType(const YResourceType& rt)
                          { operator=(rt); }
public:                 
  YResourceType&        operator=(const YResourceType& rt)
                          { Init(rt.m_lpszType); return *this; }
  void                  Init(LPCTSTR lpszType);
                        
  BOOL                  IsStandardType() const
                          { return m_lpszType!=NULL && m_szType.IsEmpty(); }
  BOOL                  IsNumericType() const
                          { return m_lpszType!=NULL && ((((DWORD)m_lpszType)>>16)==0); }
  CString               GetTypeName() const;
                        
                        operator LPCTSTR() const //may be INTRESOURCE
                          { return m_lpszType; }
  BOOL                  operator==(LPCTSTR lpType) const;
};


/////////////////////////////////////////////////////////////////////////////
// YResourceName
class YResourceName {
  static int            GetStdName(LPCTSTR lpszName, CString* pszName=NULL); 
  YResourceType         m_rt;
  LPCTSTR               m_lpszName;
  CString               m_szName;
public:                 
                        YResourceName(LPCTSTR lpszType, LPCTSTR lpszName)
                          { Init(lpszType, lpszName); }
                        YResourceName()
                          {}
                        YResourceName(const YResourceName& rn)
                          { operator=(rn); }
public:                 
  YResourceName&        operator=(const YResourceName& rn)
                          { Init(rn.GetType(),rn); return *this; }
  void                  Init(LPCTSTR lpszType, LPCTSTR lpszName);
                        
  const YResourceType&  GetType() const
                          { return m_rt; }
                        
  BOOL                  IsNumericName() const
                          { return m_lpszName!=NULL && ((((DWORD)m_lpszName)>>16)==0); }
  CString               GetName() const;
                        
                        operator LPCTSTR() const //may be INTRESOURCE
                          { return m_lpszName; }
  BOOL                  operator==(LPCTSTR lpName) const;//name only
                        
  BOOL                  operator==(const YResourceType&) const;
  BOOL                  operator==(const YResourceName&) const;
};


/////////////////////////////////////////////////////////////////////////////
// YResourceLanguage
class YResourceLanguage {
  WORD                  m_wLanguage;
public:                 
                        YResourceLanguage();
                        YResourceLanguage(WORD wPrimaryLanguage/*LANG_NEUTRAL*/, WORD wSublanguage=SUBLANG_NEUTRAL);
                        YResourceLanguage(const YResourceLanguage& rl)
                          { operator=(rl); }
public:                 
  YResourceLanguage&    operator=(const YResourceLanguage& rl)
                          { m_wLanguage=rl.m_wLanguage; return *this; }
  WORD                  operator=(WORD wIDLanguage)
                          { m_wLanguage=wIDLanguage; return wIDLanguage; }

                        operator WORD()
                          { return m_wLanguage; }

  BOOL                  operator==(const YResourceLanguage& rl)
                          { return m_wLanguage==rl.m_wLanguage; }
  BOOL                  operator==(WORD wLanguage)
                          { return m_wLanguage==wLanguage; }
public:                 
  WORD                  GetLanguage() const;
  WORD                  GetSublanguage() const;
  LPCTSTR               GetPrimaryLanguageName() const;
  LPCTSTR               GetSublanguageName() const;
  CString               GetLanguageName(BOOL bUseNumber=FALSE) const;
                        
public: //AY 1.12.2004
static CString          GetOsLanguageName(WORD wLang);
static CString          GetEnLanguageName(WORD wLang);
static int              IsCodePageAllowed(WORD wLang, UINT cpSystem);
static UINT             GetLanguageCodePage(WORD wLang);//AY 29.04.2013
                        
  CString               GetOsLanguageName() const
                          { return GetOsLanguageName(m_wLanguage); }
  CString               GetEnLanguageName() const
                          { return GetEnLanguageName(m_wLanguage); }
  int                   IsCodePageAllowed(UINT cpSystem) const
                          { return IsCodePageAllowed(m_wLanguage, cpSystem); }
  UINT                  GetLanguageCodePage() const
                          { return GetLanguageCodePage(m_wLanguage); }
};


/////////////////////////////////////////////////////////////////////////////
// YResource
class YResource
{
protected:
  HRSRC                 m_hResInfo;
  HGLOBAL               m_hData;
  void*                 m_lpData;
  DWORD                 m_dwSize;
public:
  YResourceLanguage     m_lang;
  YResourceType         m_type;
  YResourceName         m_name;
  YResourceLanguage     m_true;
public:
                        YResource();
                        YResource(
                          LPCTSTR lpszType,  // pointer to resource type
                          LPCTSTR lpszName,  // pointer to resource name
                          WORD wIDLanguage   // resource language identifier    
                        );
                        YResource(const YResource& res)
                          { operator=(res); }
public:
  YResource&            operator=(const YResource& res);

  LPVOID                GetResource(HMODULE hModule=NULL);

  HRSRC                 FindResource(HMODULE hModule=NULL);//AY 17.02.2005
  LPVOID                LoadResource(HMODULE hModule=NULL);//AY 17.02.2005

                        operator HRSRC() const
                          { return m_hResInfo; }
                        operator HGLOBAL() const
                          { return m_hData; }
  void*                 GetData() const
                          { return m_lpData; }
  DWORD                 GetSize() const
                          { return m_dwSize; }

public://safe finf of concrete resource instead FindResourceEx?
  static YResource      FindResource(//find HRSRC only
                          HMODULE hModule, // module handle
                          LPCTSTR lpType,  // resource type
                          LPCTSTR lpName,  // resource name
                          WORD wLanguage   // resource language
                        );
  static YResource      LoadResource(//find HRSRC and load (m_lpData,m_dwSize is filled)
                          HMODULE hModule, // module handle
                          LPCTSTR lpType,  // resource type
                          LPCTSTR lpName,  // resource name
                          WORD wLanguage   // resource language
                        );
  friend class          YModuleResources;
};


/////////////////////////////////////////////////////////////////////////////
// YModuleResources
class YModuleResources
{
protected:
  CArray<YResourceLanguage,YResourceLanguage&> m_languages;
  CArray<YResourceLanguage,YResourceLanguage&> m_map_langs;
  CArray<YResource,YResource&>                 m_resources;
  WORD                  m_wLanguageMask;
  HINSTANCE             m_hInstance;
  HMODULE               m_hModule;
public:
  YModuleResources(LPCTSTR lpszType=NULL, LPCTSTR lpszName=NULL, WORD wIDLanguage=-1, HMODULE hModule=NULL, HINSTANCE hInstance=NULL);
  int EnumResources(LPCTSTR lpszType=NULL, LPCTSTR lpszName=NULL, WORD wIDLanguage=-1, HMODULE hModule=NULL, HINSTANCE hInstance=NULL);
  int DumpResources(LPCTSTR szFileName);

  int                   GetLanguagesNum() const
                          { return m_languages.GetSize(); }
  YResourceLanguage     GetLanguage(int i) const
                          { return m_languages[i]; }
  int                   GetResourcesNum() const
                          { return m_resources.GetSize(); }
  YResource             GetResource(int i) const
                          { return m_resources[i]; }
  YResourceLanguage     GetEmulatedLanguage(int i) const //AY 1.12.2004
                          { return m_map_langs[i]; }

  HINSTANCE             GetInstanceHandle() const
                          { return m_hInstance; }
  HMODULE               GetModuleHandle() const
                          { return m_hModule; }
protected:
  static BOOL CALLBACK  EnumResTypeProc(
                          HINSTANCE hModule,  // resource-module handle
                          LPTSTR lpszType, // pointer to resource type
                          LONG lParam      // application-defined parameter
                        );
  static BOOL CALLBACK  EnumResNameProc(
                          HINSTANCE hModule,   // module handle
                          LPCTSTR lpszType, // pointer to resource type
                          LPTSTR lpszName,  // pointer to resource name
                          LONG lParam       // application-defined parameter
                        );
  static BOOL CALLBACK  EnumResLangProc(
                          HINSTANCE hModule,    // module handle
                          LPCTSTR lpszType,  // pointer to resource type
                          LPCTSTR lpszName,  // pointer to resource name
                          WORD wIDLanguage,  // resource language identifier
                          LONG lParam        // application-defined parameter
                        );
};

/////////////////////////////////////////////////////////////////////////////
// YModuleResourceFonts
class YModuleResourceFonts: public YModuleResources
{
public:
  YModuleResourceFonts(WORD wIDLanguage=-1, HMODULE hModule=NULL, HINSTANCE hInstance=NULL);
  EnumFonts(WORD wIDLanguage=-1, HMODULE hModule=NULL, HINSTANCE hInstance=NULL);
//DumpFonts(LPCTSTR szFileName);

  BOOL                  InstallFonts();
  BOOL                  UninstallFonts();

  int                   GetFontsNum()const;
  CString               GetFontName(int i);

  static BOOL           InstallFont(LPCTSTR szFont, WORD wLangID, HMODULE hModule);
  static BOOL           UninstallFont(LPCTSTR szFont, WORD wLangID, HMODULE hModule);
};

#endif//__cplusplus
#endif//__YRESOURC_H
