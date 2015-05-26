#ifndef __XMETADATA_H
#define __XMETADATA_H
#include "xunicod.h"
#include "xdebug.h"
#include "YTimeTZ.h"

//////////////////////////////////////////////////////////////////////////
// CMetaData

class CMetaData: public CStringArray
{
public:
  struct CSchema { LPCTSTR szName; UINT nID; LPCTSTR szDesc; }; //zero is array terminator
public:
                CMetaData(const CSchema* as)
                  { Initialize(as); }
                CMetaData()
                  {}
  void          SetSize(int nSize, int nGrowBy=-1 )
                  { CStringArray::SetSize(nSize, nGrowBy); }
  int           GetSize() const
                  { return CStringArray::GetSize(); }
  int           GetMetaDataNum() const
                  { return CStringArray::GetSize()/2; }

                CMetaData(const CMetaData& e, BOOL bPurge=FALSE);//without Purge by default
  CMetaData&    operator=(const CMetaData& e); //with Purge()

  int           Include(LPCTSTR sz, LPCTSTR szValue=NULL);
  int           Add(LPCTSTR sz, LPCTSTR szValue=NULL);
  int           Find(LPCTSTR sz) const;
  CString       GetAt(LPCTSTR sz) const { return valGetAt(Find(sz)); }
  CString&      ElementAt(LPCTSTR sz)   { return valElementAt(Find(sz)); }

  int           Include(LPCTSTR_COMPLEMENT az, LPCTSTR szValue=NULL);
  int           Add(LPCTSTR_COMPLEMENT az, LPCTSTR szValue=NULL);
  int           Find(LPCTSTR_COMPLEMENT az) const;
  CString       GetAt(LPCTSTR_COMPLEMENT az) const { return valGetAt(Find(az)); }
  CString&      ElementAt(LPCTSTR_COMPLEMENT az)   { return valElementAt(Find(az)); }

  int           Include(const CMetaData& src);

  int           Merge(const CMetaData& src, BOOL bOverwrite=FALSE);//return overwrites count

  void          Copy(const CMetaData& src);

  // overloaded operator helpers
  CString&      operator[](int nIndex)                      { return CStringArray::operator[](nIndex); }
  CString       operator[](int nIndex) const                { return CStringArray::operator[](nIndex); }
  CString&      operator[](LPCTSTR szName)                  { return ElementAt(szName); }
  CString       operator[](LPCTSTR szName) const            { return GetAt(szName); }
  CString&      operator[](LPCTSTR_COMPLEMENT azName)       { return ElementAt(azName); }
  CString       operator[](LPCTSTR_COMPLEMENT azName) const { return GetAt(azName); }
protected:
  CString       valGetAt(int iRawIndex) const;
  CString&      valElementAt(int iRawIndex);
public:
 static CString CTimeToMetaData(CTime t); //2011-07-21T14:43:40.687936300+03:00
 static CTime   MetaDataToCTime(LPCTSTR);

 static CString TimeToMetaData(YTime t, int nDigits=0, YTIME t_Bias=0); //2011-07-21T14:43:40.687936300+03:00
 static YTime   MetaDataToTime(LPCTSTR s, YTimeSpan* tsBias=NULL);

 static CString TimeToMetaData(YTimeTZ t, int nDigits=0);
 static CString BiasToMetaData(YTIME t_Bias);

public: //schema processing
  static int    FindName(LPCTSTR szName, const CSchema* as);
  BOOL          IsNormalized(const CSchema* as) const;

  int           Initialize(const CSchema* as);
  int           Validate(const CSchema* as) const;
  int           Normalize(const CSchema* as); //resort and add empty
  int           Purge(const CSchema* as);//delete non-schema entries //TO DO
  int           Purge();//delete empty entries
private://hide non-supported
  void          SetAt(int nIndex, const CString& newElement);
  void          SetAt(int nIndex, LPCTSTR newElement);
  int           Append(const CMetaData& src);
};

//////////////////////////////////////////////////////////////////
//  serialization is don't work! (example: archive >> m_szVar)
#define DECLARE_METADATA_STRING(name,var,array)\
  __declspec( property( get=get_##var, put=put_##var ) )\
  CString var;\
  inline TCHAR    get_##var(int i) const  { CString  sz = array[name];         return sz[i]; }\
  inline CString  get_##var() const       { CString  sz = array[name];         return sz; }\
  inline CString& put_##var(CString s)    { CString& sz = array[name]; sz = s; return sz; }

#define DECLARE_METADATA_CTIME(name,var,array)\
  __declspec( property( get=get_##var, put=put_##var ) )\
  CTime   var;\
  inline CTime    get_##var() const       { return CMetaData::MetaDataToCTime(array[name]); }

//////////////////////////////////////////////////////////////////
//  Inline implementation

#endif//__XMETADATA_H
#pragma once
