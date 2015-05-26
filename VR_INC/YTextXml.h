#ifndef __YTEXTXML_H
#define __YTEXTXML_H
#include <comutil.h>
#include "xunicod.h"
#include "YText.h"

class CXMLAttribute;
class CXMLSection;
class CXMLAttr;
class CXMLItem;


/////////////////////////////////////////////////////////
// CXMLText
//
class CXMLText : public CSimpleTextT<wchar_t>
{
public:
#if __IS_UNICODE
                CXMLText(LPCTSTR szSec, int nLen)
                  { m_nFlags=0; AttachWSTR(szSec,nLen); }
#else
                CXMLText(LPCTSTR szSec, int nLen)
                  { m_nFlags=0; ASSERT(0); } //TO DO?
#endif
                CXMLText(LPCTSTR_COMPLEMENT szSec, int nLen)
                  { m_nFlags=0; ASSERT(0); } //TO DO?

                CXMLText()
                  { m_nFlags=0; }

                CXMLText(const CString& sz)
                  : CSimpleTextT<wchar_t>(sz) { m_nFlags=0; }

                ~CXMLText();

    int         Create(LPCWSTR wzText, int nLen)
                  { return CSimpleTextT<wchar_t>::Create((const void*) wzText, (nLen>=0?nLen:wcslen(wzText))*sizeof(wchar_t), typeUNICODE); }

    int         Create(LPCSTR  azText, int nLen, int nType=typeUTF8)//AY 02.06.2014
                  { return CSimpleTextT<wchar_t>::Create((const void*) azText, (nLen>=0?nLen:strlen(azText))*sizeof(char)   , nType);    }

    LPCWSTR     GetText() const
                  { return (LPCWSTR)CSimpleTextT<wchar_t>::GetText(); }
    int         GetLen() const //may be no zero!
                  { return GetSize()/sizeof(wchar_t); }


    CString     GetStrValue(LPCSTR azSec, LPCSTR azVal, LPCTSTR szDef=NULL, int* pErr=NULL) const
                  { return GetXmlProfileString(CString(azSec), CString(azVal), szDef, pErr); }
    ULONG       GetIntValue(LPCSTR azSec, LPCSTR azVal, ULONG nDef=0) const
                  { return GetXmlProfileInt(CString(azSec), CString(azVal), nDef); }

    LPCWSTR     GetXmlSection(LPCSTR azSec, int& nSecLen) const;

static LPCWSTR  GetXmlSectionData(LPCSTR azSec, LPCWSTR xml, int nLen, int& nDataLen);
static LPCWSTR  GetXmlSection(LPCSTR azSec, LPCWSTR xml, int nLen, int& nSecLen);
static CString  GetXmlSection(LPCSTR azSec, const CString& xml);
static LPCWSTR  ParseXmlItem(LPCSTR azSec, LPCWSTR xml, int nLen, int& nSecLen, int& nDataLen, LPCWSTR& wzData);

    int         Parse(void* pObj);

    LPCWSTR     AttachSection(LPCSTR azSec)
                  {
                    AttachBSTR();
                    int     nSec  = 0;
                    LPCWSTR wzSec = GetXmlSection(azSec,nSec);
                    LPCWSTR wzEnd = wzSec + nSec;
                    DetachBSTR();
                    if(wzSec!=NULL)
                      AttachWSTR(wzSec,nSec);//attention! is not zero terminated at nSec, but zero terminated later
                    return  wzSec;
                  }

    void        AttachWSTR(LPCWSTR wz, int nLen=-1);
    LPCWSTR     DetachWSTR();

    void        AttachBSTR(); //ATTENTION! ReadOnly functions must be used!
    void*       DetachBSTR();    
    _bstr_t&    AsBSTR()
                  { return m_bzText; }
protected:
    _bstr_t     m_bzText;
    int         m_nFlags;
};

/////////////////////////////////////////////////////////
// CXMLAttribute
//
// Usage:
//
//   CString xml;
//   CXMLAttribute attr1(xml,"Name1") = "Value1";
//   CXMLAttribute attr2(xml,"Name2") = "Value2";
//
// Result:
//   "  Name1=\"Value1\"\n"
//   "  Name2=\"Value2\"\n"

class CXMLAttribute: public CString
{

  CString*  m_pXML;
public:
  CXMLAttribute()
    { m_pXML = NULL; }
  CXMLAttribute(CString& xml, LPCWSTR wzAttrName)
    : CString(wzAttrName) { m_pXML = &xml; }
  CXMLAttribute(CString& xml, LPCSTR  azAttrName)
    : CString(azAttrName) { m_pXML = &xml; }

  CXMLAttribute& operator = (LPCWSTR wzValue)
    { return Assign(CString(wzValue)); }
  CXMLAttribute& operator = (LPCSTR  azValue)
    { return Assign(CString(azValue)); }

#define _T_SPACE   _T(" ")
#define _T_QUOTE   _T("\"")
//efine _T_SLASH   _T("/")
#define _T_EQ      _T("=")
#define _T_BEG     _T("<")
#define _T_END     _T(">")
#define _T_EOS     _T(">\n")
#define _T_EOL      _T("\n")
#define _T_FINIS   _T("</")
#define _T_EMPTY   _T(" />")

  static CString Normalize(const CString& szValue)
  {
    CString szVal = szValue;
    szVal.Replace(_T("&"),_T("&amp;"));   //&#38;#38;
    szVal.Replace(_T("<"),_T("&lt;"));    //&#60;
    szVal.Replace(_T(">"),_T("&gt;"));    //&#62;
    szVal.Replace(_T("\""),_T("&quot;")); //&#34;
    szVal.Replace(_T("\'"),_T("&apos;")); //&#39;
    return szVal;
  }

  CXMLAttribute& AssignValue(const CString& szValue)
  {
    ASSERT( this->Find(_T_EQ)<0 );//TO DO?
    CString szVal = Normalize(szValue);
    *this += _T_EQ _T_QUOTE;
    *this += szVal;
    *this +=       _T_QUOTE;
    return *this;
  }

  CXMLAttribute& AssignToXML(BOOL bNewLine=TRUE)
  {
    if(m_pXML!=NULL) {
      if(bNewLine)
        *m_pXML += _T_SPACE _T_SPACE + *this + _T_EOL;
      else
        *m_pXML +=          _T_SPACE + *this;
    }
    return *this;
  }

  CXMLAttribute& Assign(const CString& szValue, BOOL bNewLine=TRUE)
  {
    return AssignValue(szValue), AssignToXML(bNewLine);
  }

};

/////////////////////////////////////////////////////////
// CXMLSection
//
//   Usage:
//
//   { CXMLSection sec(xml,"SectName",TRUE);
//                                                 //... add attributes ...
//       CXMLAttr/*attr1*/(sec,"Name1") = "Value1";
//       CXMLAttr/*attr2*/(sec,"Name2") = "Value2";
//       sec.Body();
//                                                 //... add items ...
//       CXMLItem/*item1*/(sec,"Item1") = "Value3";
//       CXMLItem/*item2*/(sec,"Item2") = "Value4";
//   }                                             //at this point </SectName> added
// Result:
//   <SectName Name1="Value1" Name2="Value2">
//     <Item1>Value3</Item1>
//     <Item2>Value4</Item2>
//   </SectName>


class CXMLSection : public CString
{
  friend class CXMLAttr;
  friend class CXMLItem;
protected:
  CString*     m_pXML;
  CXMLSection* m_pParent;
  BOOL         m_bAttr;
public:
  CXMLSection(CXMLSection& sec, LPCWSTR wzSection, BOOL bAttr=FALSE, BOOL bEOL=TRUE)
    : CString(wzSection) { m_pParent = &sec; m_pXML = sec.m_pXML; m_bAttr = bAttr;
                           Beg(bEOL); }
  CXMLSection(CXMLSection& sec, LPCSTR  azSection, BOOL bAttr=FALSE, BOOL bEOL=TRUE)
    : CString(azSection) { m_pParent = &sec; m_pXML = sec.m_pXML; m_bAttr = bAttr;
                           Beg(bEOL); }
  ~CXMLSection()
                         { End(); }

  CXMLSection(CString& xml, LPCWSTR wzSection, BOOL bAttr=FALSE, BOOL bEOL=TRUE)
    : CString(wzSection) { m_pParent = NULL; m_pXML = &xml; m_bAttr = bAttr;
                           Beg(bEOL); }
  CXMLSection(CString& xml, LPCSTR  azSection, BOOL bAttr=FALSE, BOOL bEOL=TRUE)
    : CString(azSection) { m_pParent = NULL; m_pXML = &xml; m_bAttr = bAttr;
                           Beg(bEOL); }

  CXMLSection& Beg(BOOL bEOL=TRUE)
  {
    if(m_pParent!=NULL)
      m_pParent->Body();//terminate attributes
    AddTabs();
    if(m_bAttr)
      *m_pXML += _T_BEG + *this;
    else
      *m_pXML += _T_BEG + *this + (bEOL ? _T_EOS : _T_END);
    return *this;
  }

  CXMLSection& Body(LPCTSTR szBody=NULL)
  {
    if(m_bAttr)
      *m_pXML += _T_EOS;
    m_bAttr = FALSE;
    if(szBody!=NULL)
      *m_pXML += CXMLAttribute::Normalize(szBody);
    return *this;
  }

  CXMLSection& End(BOOL bTAB=TRUE, BOOL bEOL=FALSE, BOOL bConcat=FALSE) //concat <Name></Name> -> <Name />
  {
    if(IsEmpty())
      return *this;

    Body(); //finish attributes

    if(bConcat) 
      (*m_pXML).TrimRight(_T_END);// TO DO: test AddTabs() after *m_pXML -= _T_END;

    if(bTAB)
      AddTabs();

    if(bConcat)
      *m_pXML += _T_EMPTY + CString() + (bTAB||bEOL ? _T_EOL : _T(""));
    else
      *m_pXML += _T_FINIS + *this     + (bTAB||bEOL ? _T_EOS : _T_END);

    Empty();
    return *this;
  }

  void AddTabs()
  {
    int nLevel = 0;
    for(CXMLSection* pSec = m_pParent; pSec!=NULL; pSec = pSec->m_pParent)
      ++nLevel;
    *m_pXML += CString( *_T_SPACE, nLevel*2);
  }

};


/////////////////////////////////////////////////////////
// CXMLAttr
//
// Usage:
//
//   CXMLAttr attr(sec,"Name") = "Value";
//
// Addeed string to XML:
//   Name="Value"
//
class CXMLAttr :public CXMLAttribute
{
//CString*      m_pXML; //inherited
  CXMLSection*  m_pSec;
public:
  CXMLAttr(CXMLSection& sec, LPCWSTR wzAttrName)
    : CXMLAttribute(*(&sec?sec.m_pXML:NULL), wzAttrName) { m_pSec = &sec; }
  CXMLAttr(CXMLSection& sec, LPCSTR  azAttrName)
    : CXMLAttribute(*(&sec?sec.m_pXML:NULL), azAttrName) { m_pSec = &sec; }

  CXMLAttr& operator = (LPCWSTR wzValue)   //same as CXMLAttribute, except no EOL if section is not specified
    { return Assign(CString(wzValue),-1); }
  CXMLAttr& operator = (LPCSTR  azValue)   //same as CXMLAttribute, except no EOL if section is not specified
    { return Assign(CString(azValue),-1); }

  CXMLAttr& Assign(const CString& szValue, BOOL bNewLine=-1) //same as CXMLAttribute
  {
    BOOL bInside = m_pSec!=NULL;
    if(bNewLine==-1)
      bNewLine = !bInside;
    AssignValue(szValue);
    AssignToXML(bNewLine);
    return *this;
  }
};

/////////////////////////////////////////////////////////
// CXMLItem  (simplest section with immediate terninating)
//
// Usage:
//
//   CXMLItem item(sec,"Item") = "Text";
//
// Addeed string to section:
//   <Name>Text</Name>
//
class CXMLItem :public CXMLSection
{
public:
  CXMLItem(CXMLSection& sec, LPCWSTR wzItemName)
    : CXMLSection(sec, wzItemName, FALSE, FALSE) { }
  CXMLItem(CXMLSection& sec, LPCSTR  azItemName)
    : CXMLSection(sec, azItemName, FALSE, FALSE) { }

  CXMLItem& operator = (LPCWSTR wzValue)
    { return Assign(CString(wzValue)); }
  CXMLItem& operator = (LPCSTR  azValue)
    { return Assign(CString(azValue)); }

  CXMLItem& Assign(const CString& szText)
  {
    if(m_pParent!=NULL)
      m_pParent->Body();//terminate attributes
  //CXMLSection::Beg() already called
    CXMLSection::Body(szText);
    CXMLSection::End(FALSE,TRUE);
    return *this;
  }

  static int Replace(CString& xml, LPCSTR azItemName, LPCTSTR szValue, LPCTSTR szCondValue=NULL);
};

/////////////////////////////////////////////////////////
// CXMLEmpt - same as CXMLItem, but on empty item will be used " />" terminator
//
// Usage:
//
//   CXMLEmpt item(sec,"Item") = "Text";
//
// Addeed string to section:
//   <Name>Text</Name> 
// or 
//   <Name />
//

class CXMLEmpt :public CXMLSection
{
public:
  CXMLEmpt(CXMLSection& sec, LPCWSTR wzItemName)
    : CXMLSection(sec, wzItemName, FALSE, FALSE) { }
  CXMLEmpt(CXMLSection& sec, LPCSTR  azItemName)
    : CXMLSection(sec, azItemName, FALSE, FALSE) { }

  CXMLEmpt& operator = (LPCWSTR wzValue)
    { return Assign(CString(wzValue)); }
  CXMLEmpt& operator = (LPCSTR  azValue)
    { return Assign(CString(azValue)); }

  CXMLEmpt& Assign(const CString& szText)
  {
    if(m_pParent!=NULL)
      m_pParent->Body();//terminate attributes
  //CXMLSection::Beg() already called
    CXMLSection::Body(szText);
    CXMLSection::End(FALSE,TRUE,szText.IsEmpty());
    return *this;
  }
};


/////////////////////////////////////////////////////////
// CXMLIter - section iterator
//
// Usage:
//
//   CXMLText xml;
//   for(CXMLIter wzSec(xml,"Section"); wzSec; ++wzSec) 
//   { 
//     CString szSec(wzSec,wzSec.GetLen()); ...
//   }

class CXMLIter //iterator 
{
protected:
  LPCSTR      azSec; //section name
  LPCWSTR     wzData;//data 
  LPCWSTR     wzEnd; //data end
  int         nLen;  //current rest of data length
  LPCWSTR     wzSec; //current section text
  int         nSec;  //current section length
public:
  CXMLIter(const CXMLText& xml, LPCSTR a_azSec)
                            {
                              azSec  = a_azSec;
                              wzData = xml.GetText();
                              nLen   = xml.GetLen();
                              wzEnd  = wzData + nLen;
                              nSec   = 0;
                              wzSec  = CXMLText::GetXmlSection(azSec, wzData, nLen, nSec);
                            }
  CXMLIter(LPCWSTR wzText, int nLen, LPCSTR a_azSec)
                            {
                              azSec  = a_azSec;
                              wzData = wzText;
                              nLen   = nLen;
                              wzEnd  = wzData + nLen;
                              nSec   = 0;
                              wzSec  = CXMLText::GetXmlSection(azSec, wzData, nLen, nSec);
                            }
  LPCWSTR  operator++()     {
                              wzData = wzSec + nSec;
                              nLen   = wzEnd - (wzSec+nSec);
                              wzSec  = CXMLText::GetXmlSection(azSec, wzData, nLen, nSec);
                              return wzSec;
                            }
  operator bool() const     { return wzSec!=NULL; }
  operator LPCWSTR() const  { return wzSec; }
  int      GetLen() const   { return nSec; }
};

/////////////////////////////////////////////////////////
// CXMLSec
//
// Usage:
//
//   CXMLText xml;
//
//   for(CXMLIter wzSec(xmlAnswer,"Section"); wzSec; ++wzSec)
//   {
//     CXMLSec xmlSec(wzSec,wzSec.GetLen(),"Section");
//     CString szName   = xmlSec["Name"];
//   }

class CXMLSec: public CXMLText
{
  LPCSTR        m_azSec;
public: 
                CXMLSec(LPCTSTR szData, int nLen, LPCSTR azSec) //TO DO: auto fill m_azSec
                  : CXMLText(szData,nLen) { m_azSec=azSec; }

                CXMLSec(LPCTSTR_COMPLEMENT szData, int nLen, LPCSTR azSec) //AY 18.12.2013 TO DO
                  : CXMLText(szData,nLen) { m_azSec=azSec; }

  CString       operator[](LPCSTR azVal)const
                  { return GetStrValue(m_azSec, azVal); }
};


#undef _T_SPACE
#undef _T_QUOTE
//ndef _T_SLASH
#undef _T_EQ
#undef _T_BEG
#undef _T_END
#undef _T_EOL
#undef _T_EOS
#undef _T_FINIS

#endif//__YTEXTXML_H
#pragma once
