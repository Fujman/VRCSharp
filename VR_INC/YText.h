#ifndef __YTEXT_H
#define __YTEXT_H
#pragma warning(disable: 4430)

#include <afxwin.h>
#ifdef _RICHEDIT_VER
#undef _RICHEDIT_VER
#endif
#define _RICHEDIT_VER 0x0200 //redefine _RICHEDIT_VER 0x0100->0x0200
#include <richedit.h>
#include <afxcoll.h>
#include <afxrich.h>
#include <atlconv.h>

#include "xmalloc.h"
#include "xstring.h"
#include "xdebug.h"

#include "YSTRING/YStrArrA.h"
#include "YSTRING/YStrArrW.h"

#define PAGE_WIDTH  62
#define PAGE_HEIGHT 46

/////////////////////////////////////////////////////////////////////////////
// Text collection

class CStringArray;
      class CText;
            class CFormattedText;

template <class TYPE> class CSimpleTextT;
      class CEditText;
      class CRichEditText;
class CRTFText;

typedef   CSimpleTextT<char>    CSimpleTextA;
typedef   CSimpleTextT<wchar_t> CSimpleTextW;

#if defined(UNICODE) || defined(_UNICODE)
  typedef CSimpleTextW   CSimpleText;
#else
  typedef CSimpleTextA   CSimpleText;
#endif
/////////////////////////////////////////////////////////////////////////////
// TEXT_FORMAT

#ifndef __TEXT_FORMAT_DEFINED
#define __TEXT_FORMAT_DEFINED
typedef struct tagTEXT_FORMAT {
  int nPageWidth;
  int nPageHeight;
  int nMarginLeft;
  int nMarginRight;
  int nMarginTop;
  int nMarginBottom;
} TEXT_FORMAT;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleTextT

template<class TYPE> class YTextT
{
public://s - this char type, t-TCHAR, w-wchar_t, a-char, m-unsigned char (multibyte)
                                                                      //  TYPE:   char      wchar_t             unsigned char
  static TYPE*            w2scpy(TYPE* szDst, const wchar_t* wzSrc);         //   W2A       wcscpy              WideCharToMultiByte
  static wchar_t*         s2wcpy(wchar_t* wzDst, const TYPE* szSrc);         //   A2W       wcscpy              MultiByteToWideChar

  static TYPE*            a2scpy(TYPE* szDst, const char* azSrc);            //   strcpy    A2W                 ?strcpy
  static char*            s2acpy(char* azDst, const TYPE* szSrc);            //   strcpy    W2A                 ?strcpy

  static TYPE*            m2scpy(TYPE* szDst, const unsigned char* mzSrc);   //   ?strcpy   MultiByteToWideChar strcpy
  static unsigned char*   s2mcpy(unsigned char* mzDst, const TYPE* szSrc);   //   ?strcpy   WideCharToMultiByte strcpy

  static TYPE*            t2scpy(TYPE* szDst, const TCHAR* tzSrc);           //   strcpy/wcscpy
  static TCHAR*           s2tcpy(TCHAR* tzDst, const TYPE* szSrc);           //   strcpy
};

template<> inline char*    YTextT<char   >::w2scpy(char*    szDst, LPCWSTR wzSrc)  { return ystring_wcstombsz_str(szDst,wzSrc); } /*USES_CONVERSION; LPSTR  szSrc = W2A(wzSrc); return strcpy(szDst,szSrc);*/ 
template<> inline wchar_t* YTextT<wchar_t>::w2scpy(wchar_t* szDst, LPCWSTR wzSrc)  { return wcscpy(szDst,wzSrc); }

template<> inline char*    YTextT<char   >::a2scpy(char*    szDst, LPCSTR  azSrc)  { return strcpy(szDst,azSrc); }
template<> inline wchar_t* YTextT<wchar_t>::a2scpy(wchar_t* szDst, LPCSTR  azSrc)  { return ystring_mbstowcsz_str(szDst,azSrc); } /*USES_CONVERSION; LPWSTR wzSrc = A2W(azSrc); return wcscpy(szDst,wzSrc);*/

template<> inline wchar_t* YTextT<char   >::s2wcpy(wchar_t* wzDst, LPCSTR  szSrc)  { return ystring_mbstowcsz_str(wzDst,szSrc); } /*USES_CONVERSION; LPWSTR wzSrc = A2W(szSrc); return wcscpy(wzDst,wzSrc);*/
template<> inline wchar_t* YTextT<wchar_t>::s2wcpy(wchar_t* wzDst, LPCWSTR szSrc)  { return wcscpy(wzDst,szSrc); }

template<> inline char*    YTextT<char   >::s2acpy(char*    azDst, LPCSTR  szSrc)  { return strcpy(azDst,szSrc); }
template<> inline char*    YTextT<wchar_t>::s2acpy(char*    azDst, LPCWSTR szSrc)  { return ystring_wcstombsz_str(azDst,szSrc); } /*USES_CONVERSION; LPSTR  azSrc = W2A(szSrc); return strcpy(azDst,azSrc);*/

template<class TYPE> inline TYPE* YTextT<TYPE>::t2scpy(TYPE* szDst, const TCHAR* tzSrc)  
{ 
  #if defined(UNICODE) || defined(_UNICODE)
    return w2scpy(szDst,tzSrc); 
  #else
    return a2scpy(szDst,tzSrc); 
  #endif
}
template<class TYPE> inline TCHAR* YTextT<TYPE>::s2tcpy(TCHAR* tzDst, const TYPE* szSrc)
{ 
  #if defined(UNICODE) || defined(_UNICODE)
    return s2wcpy(szDst,tzSrc); 
  #else
    return s2acpy(szDst,tzSrc); 
  #endif
}


/////////////////////////////////////////////////////////////////////////////
// CSimpleTextBase

class CSimpleTextBase
{
public:
  CSimpleTextBase();
  ~CSimpleTextBase();
  
  void* alloc(UINT size);
  void* free();

  const void* GetText() const 
    {return (m_pText);}
  UINT  GetSize() const /*bytes*/
    {return (m_nSize);}

  void  Attach(void* pText, UINT nSize/*bytes*/)
    { m_pText = pText; m_nSize = nSize; }
  void* Detach() //AY 26.08.2010 OLD: void Detach() { m_pText = NULL; m_nSize = 0; }
    { void* text=m_pText; m_pText = NULL; m_nSize = 0; return text; }

  void* Assign(const CSimpleTextBase& text)
    { free(); alloc(text.m_nSize); return m_pText!=NULL?memcpy(m_pText,text.m_pText,m_nSize):NULL; }

protected:
  void* m_pText;
  UINT  m_nSize;//bytes, without zero, but zero always present in allocated buffer
};

/////////////////////////////////////////////////////////////////////////////
// CSimpleTextT

template<class TYPE>
class CSimpleTextT: public CSimpleTextBase
{
protected://inherited
//void* m_pText;
//UINT  m_nSize;//bytes, without zero, but zero always present in allocated buffer
public:
  enum { typeANSI=1, typeUNICODE=2, typeEDOCINU=3, typeUTF8=4, typeDEFAULT=0, typeUNKNOWN=-1 };

  // nMode=-1 - nothig add to end of each string
  // nMode=0  - add \0 to end of each string and \0\0 at and
  // nMode=1  - add \n to end of each string and \0 at and
  // nMode=2  - add \r\n to end of each string and \0 at and

  enum { modeCONCAT=-1, modeZEROS=2, modeUNIX=3, modeCRLF=2, flagFFFE=0x8000 };

public:
  enum { IS_UNICODE=sizeof(TYPE)/sizeof(char)-1 };
  typedef TYPE        char_t;
  typedef TYPE*       str_t;
  typedef const TYPE* str_ct;
public:
  CSimpleTextT();
  CSimpleTextT(const CString& sz);
  ~CSimpleTextT();
  static int DetectType(const void* pBuffer, UINT nSize/*bytes*/); //1 - ANSI, 2 - UNICODE, 3-UNICODE (big endian&)
  static int SelectType(const void* pBuffer, UINT nSize/*bytes*/); //1 - ANSI, 2 - UNICODE, 3-UNICODE (big endian&), -1 - unknown

  int CreateFromString(LPCTSTR szString)//AY 05.03.2010
    { return Create((const void*)szString,_tcslen(szString)*sizeof(*szString), typeDEFAULT); }

  int Create(const void* pBuffer, UINT nSize/*bytes*/, int nBufType=typeDEFAULT); //nBufType=1 - ANSI, 2 - UNICODE, -1 - Autodetect, add zero anyway!
  int Create(const CSimpleTextT& sText);
  int Create(const CString& sz);
  int Create(const CStringArray& as, int nMode=modeCRLF);//==Create(const CText& aszText);

  void Attach(void* pText, UINT nSize/*bytes*/)
    { CSimpleTextBase::Attach(pText,nSize); /* ASSERT(((TYPE*)m_pText)[m_nSize/sizeof(TYPE)]=='\0'); AY commented 07.10.2012 */ }

  int Replace(const TYPE* szSrc, const TYPE* szTar, int mode=0);

  int RemoveZeros();

  CString GetString(int nString, const TYPE* szDelimiters=NULL);//NULL is \r\n
  CString GetAsString() const; //AY 19.07.2011

  int Save(LPCTSTR szFileName, int nSaveBufType=0) const; //nSaveBufType=1 - ANSI, 2 - UNICODE, -1 - Autodetect, add zero anyway!
  int Load(LPCTSTR szFileName, int nBufType=0);       //nBufType        =1 - ANSI, 2 - UNICODE, -1 - Autodetect, add zero anyway!
  int AddFormattedString(LPCTSTR lpszFormat, ... );

public:
  CSimpleTextT(const CSimpleTextT<TYPE>& text)//copy constructor //AY 20.07.2011
    { CSimpleTextBase::Assign(text); TRACE(DEBUGPLACE(" Algorythm changed!\n")); }
  CSimpleTextT<TYPE>& operator=(const CSimpleTextT<TYPE>& text)  //AY 20.07.2011
    { CSimpleTextBase::Assign(text); TRACE(DEBUGPLACE(" Algorythm changed!\n")); return *this; }
  CSimpleTextT<TYPE>& operator=(const CString& sz)               //AY 20.07.2011
    { free(); Create(sz); /*TRACE(DEBUGPLACE(" Algorythm changed!\n"));*/ return *this; }

  CString  operator [](int nIndex) const;
  friend class CText;

public:
  CString  GetXmlProfileString(LPCTSTR szSection, LPCTSTR szKeyName, LPCTSTR szDefault=NULL, int* piErr=NULL) const;
  ULONG    GetXmlProfileInt(LPCTSTR szSection, LPCTSTR szKeyName, UINT nDefault=0, int*piErr=NULL) const;

  CString  GetXmlProfileAttr(LPCTSTR szSection, int iSection, LPCTSTR szKeyName, LPCTSTR szDefault) const;
  CString  GetXmlSettingsAttr(LPCTSTR szSection, LPCTSTR szKeyName, LPCTSTR szDefault) const;
	
  static 
  CString  GetXmlProfileValue(LPCTSTR szXML, int nLen, LPCTSTR szSection, LPCTSTR szKeyName, LPCTSTR szDefault);

public://non-nteget constants
  static const wchar_t&  UNICODE_CHAR() { static const wchar_t c = L'\xFEFF'; return c; } //little endian
  static const wchar_t&  EDOCINU_CHAR() { static const wchar_t c = L'\xFFFE'; return c; } //big endian

#ifdef _DEBUG
  int      m_bNoDebug;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// CText
class CText : public CStringArray
{
public:
  enum { modeANSI=CSimpleText::typeANSI, modeUNICODE=CSimpleText::typeUNICODE, modeEDOCINU=CSimpleText::typeEDOCINU, modeUTF8=CSimpleText::typeUTF8, modeDEFAULT=CSimpleText::typeDEFAULT, modeAUTO=CSimpleText::typeUNKNOWN/*-1*/ };
public:
  CText(){}
  CText(const CSimpleText& sText);
  CText(const CText& sText);//AY 31.08.2010
public:

  int CreateFromString(LPCTSTR szString)//AY 05.03.2010
    { return Create((const void*)szString,_tcslen(szString)*sizeof(*szString), modeDEFAULT); }

#ifndef _DEBUG
  int Create(const void* pBuffer, unsigned nSize/*bytes*/, int mode =0);//1-ansi,2-unicode,0-default,-1-autodetect
#else
  int Create(const void* pBuffer, unsigned nSize/*bytes*/, int mode);//force debug compilation error
#endif
  int _Create(LPCSTR  pBuffer, unsigned nSize/*bytes*/);
  int _Create(LPCWSTR pBuffer, unsigned nSize/*bytes*/);
//int  Create(const CSimpleText& sText);

  int Create(const CSimpleTextA& sText);
  int Create(const CSimpleTextW& sText);

  int Create(const CText& sText);//AY 31.08.2010

  int Replace(LPCTSTR szSrc, LPCTSTR szTar);

  int RemoveEmpty();

  int Export(CSimpleTextBase& sText, int mode=modeDEFAULT) const;
  int Save(LPCTSTR szFileName, int mode=modeDEFAULT) const; //compile dependent ANSI/UNICODE output text format by default
  int Load(LPCTSTR szFileName, int mode=modeDEFAULT);       //compile dependent ANSI/UNICODE input  text format by default

  int GetParagraph(CString& sz) const;

  int GetListCtrl(CListCtrl* pList);
  int SetListCtrl(CListCtrl* pList) const;
  int GetComboCtrl(CComboBox* pCombo);
  int SetComboCtrl(CComboBox* pCombo, int* aiData=NULL) const;
public:
  CString& operator [](int nIndex)       {return CStringArray::operator[](nIndex);}
  CString  operator [](int nIndex) const {return CStringArray::operator[](nIndex);}

  int AddFormattedString(LPCTSTR lpszFormat, ... );
public:
  CString  GetProfileString(LPCTSTR szSection, LPCTSTR szKeyName, LPCTSTR szDefault=NULL);
  ULONG    GetProfileInt(LPCTSTR szSection, LPCTSTR szKeyName, UINT nDefault=0);
};

/////////////////////////////////////////////////////////////////////////////
// CFormattedText
class CFormattedText : public CText
{
  CText m_aszFormat;
public:
  int Create(const CStringArray& aszTemplate, const CStringArray& aszVariables);
  int Append(const CStringArray& aszTemplate, const CStringArray& aszVariables);
  int GetTextFormat(TEXT_FORMAT* ptf) const;
public:
  CText& GetTextFormat()
    {return m_aszFormat;}
  const CText& GetTextFormat() const
    {return m_aszFormat;}
  static LPCTSTR EnumFormat(TCHAR& cType, LPCTSTR szFormat, int& nStart, int& nStop, TEXT_FORMAT* ptf);
  static int     MakeFormat(char cType, CString& szFormat, int nStart, int nStop=0, TEXT_FORMAT* ptf=NULL);
public:// helpers
  static int RecognizeTemplateString(const CString& szTemplate, CString& szString, CString& szFormat, TEXT_FORMAT* tf);
  static int AddRecognizedString(CString& szString, CString& szFormat, CStringArray& aszText, CStringArray& aszFormat, TEXT_FORMAT* ptf);
  static int FormatParagraph(CString& szString, CStringArray& asz, int nWidth);
  static int SubstituteVariables(const CString& szTemplate, const CStringArray& aszVars, CStringArray& aszText);
  static int GetVariablesCount(const CStringArray& aszVars, const CString& szVarName);
  static int FindVariable(int nStartIndex, const CStringArray& aszVars, const CString& szVarName, CString* pszVarValue);
  static int GetToken(LPCTSTR sText, int nSize, int& nTokenSize);
public: // operators
  CString& operator [](int nIndex)       {return CText::operator[](nIndex);}
  CString  operator [](int nIndex) const {return CText::operator[](nIndex);}
  CString& GetFormat(int nIndex)         {return m_aszFormat[nIndex];}
  CString  GetFormat(int nIndex) const   {return m_aszFormat[nIndex];}
};

/////////////////////////////////////////////////////////////////////////////
// CEditText
class CEditText : public CSimpleText
{
  TEXT_FORMAT tf;
public:
  CEditText();
  int Create(const CFormattedText& Text);
  int Create(const CText& aszText, int nMode=2);
  int Create(const CSimpleText& sText);
  int Save(LPCTSTR szFileName) const;
  int Load(LPCTSTR szFileName);

  int GetEditCtrl(CEdit* pEdit);
  int SetEditCtrl(CEdit* pEdit) const;
};

/////////////////////////////////////////////////////////////////////////////
// CRichEditText
class CRichEditText : public CSimpleText
{
  typedef CSimpleText CParent;
protected:
  TEXT_FORMAT tf;
public:
  CRichEditText();
  int Create(const CFormattedText& Text, CRichEditCtrl* pRichEdit,
      int nFontSize=8);
//int Create(const CString& szText);
//int Create(const CText& aszText);
//int Create(const CSimpleText& aszText);
//  int Save(LPCTSTR szFileName) const;


  int Load(LPCTSTR szFileName);

  int GetRTFText(CRTFText& rtfText);
protected:
  int _SaveToFile(CFile* pFile) const;
protected:
  int GetRichEditCtrl(CRichEditCtrl* pRichEdit);
  int SetRichEditCtrl(CRichEditCtrl* pRichEdit);
public:
  int SetTextFormat(int nPageWidth=-1, int nPageHeight=-1, int nMarginLeft=-1, 
                    int nMarginRight=-1, int nMarginTop=-1, int nMarginBottom=-1); //20.12.02 VEN
protected:
  static  DWORD CALLBACK EditStreamCallback(
    DWORD dwCookie, // application-defined value
    LPBYTE pbBuff,  // pointer to a buffer
    LONG cb,        // number of bytes to read or write
    LONG *pcb       // pointer to number of bytes transferred
  );
  DWORD GetCallback(LPBYTE pbBuff, LONG cb, LONG *pcb);
  DWORD SetCallback(LPBYTE pbBuff, LONG cb, LONG *pcb);
  int   m_isRead;
  ULONG m_nOffset;

private:
  int Save(LPCTSTR szFileName, int mode) const; //compile dependent ANSI/UNICODE output text format by default
  int Load(LPCTSTR szFileName, int mode);       //compile dependent ANSI/UNICODE input  text format by default

};
/////////////////////////////////////////////////////////////////////////////
// CSimpleTextBase

inline CSimpleTextBase::CSimpleTextBase()
{
  m_pText = NULL;
  m_nSize = 0;
}

inline void* CSimpleTextBase::alloc(UINT size) //AY 20.07.2011
{
  ASSERT(m_pText==NULL);
  ASSERT(m_nSize==0);
  void* pRet = throwed_malloc(size+2,&m_pText);// 2 is max(sizeof(wchar_t),sizeof(char))
  if(pRet!=NULL) {
    m_nSize = size;
    ((BYTE*)m_pText)[size+0] = '\0';
    ((BYTE*)m_pText)[size+1] = '\0';
  }
  return pRet;
}

inline void* CSimpleTextBase::free() //AY 20.07.2011
{
  void* pRet = m_pText;
  if(m_pText!=NULL) {
    pRet = throwed_free(m_pText);
    m_nSize = 0;
  }
  return pRet;
}

inline CSimpleTextBase::~CSimpleTextBase()
{
  free();
//  if(m_pText!=NULL) {
//    throwed_free(m_pText);
//    m_nSize = 0;
//  }
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleTextT

template<class TYPE>
inline CSimpleTextT<TYPE>::CSimpleTextT()
{
#ifdef _DEBUG
  m_bNoDebug = 0;
#endif
}

template<class TYPE>
inline CSimpleTextT<TYPE>::~CSimpleTextT()
{
}

template<class TYPE>
CSimpleTextT<TYPE>::CSimpleTextT(const CString& sz) {
#ifdef _DEBUG
  m_bNoDebug = 0;
#endif
  Create(sz);
}

template<class TYPE>
int CSimpleTextT<TYPE>::DetectType(const void* pBuffer, UINT nSize) //1 - ANSI, 2 - UNICODE, 3-UNICODE (big endian&)
{
  const wchar_t* pc = (const wchar_t*) pBuffer;
  if     (nSize>=2 && *pc==EDOCINU_CHAR())
    return typeEDOCINU;
  else if(nSize>=2 && *pc==UNICODE_CHAR())
    return typeUNICODE;
  else
    return typeANSI;
}

template<class TYPE>
int CSimpleTextT<TYPE>::SelectType(const void* pBuffer, UINT nSize) //1 - ANSI, 2 - UNICODE, 3-UNICODE (big endian&), -1-unknown
{
  const wchar_t* pc = (const wchar_t*) pBuffer;
  if     (pBuffer==NULL || nSize==0)
    return typeUNKNOWN;
  else if(nSize>=2 && *pc==EDOCINU_CHAR())
    return typeEDOCINU;
  else if(nSize>=2 && *pc==UNICODE_CHAR())
    return typeUNICODE;
  else if(nSize==1)
    return typeANSI;   //?
  else
    return typeUNKNOWN;//TO DO: scan content?
}

template<> int CSimpleTextT<char>::Create(const void* pBuffer, UINT nSize, int nBufType);
template<> int CSimpleTextT<wchar_t>::Create(const void* pBuffer, UINT nSize, int nBufType);

template<> int CSimpleTextT<char>::Replace(const char* szSrc, const char* szDst, int mode);
template<> int CSimpleTextT<wchar_t>::Replace(const wchar_t* szSrc, const wchar_t* szDst, int mode);


template<class TYPE>
int CSimpleTextT<TYPE>::Create(const CString& sz)
{
  #if defined(UNICODE) || defined(_UNICODE)
    return Create((void*)(LPCTSTR)sz,(sz.GetLength()/*+1*/) *sizeof(TCHAR),typeUNICODE);//copy //KSN 27.01.2009 rem /*+1*/
  #else
    return Create((void*)(LPCTSTR)sz,(sz.GetLength()/*+1*/) *sizeof(TCHAR),typeANSI);//convert //KSN 27.01.2009 rem /*+1*/
  #endif
}

template<class TYPE>
int CSimpleTextT<TYPE>::Create(const CSimpleTextT<TYPE>& sText)
{
  UINT nSize = sText.GetSize();
  const void* pBuffer = sText.GetText();
  m_pText = throwed_malloc(nSize+sizeof(TYPE),&m_pText);
  m_nSize = nSize;
  memcpy(m_pText,pBuffer,nSize);
  ((TYPE*)m_pText)[nSize/sizeof(TYPE)]=_T('\0');
  return 0;
}

template<class TYPE>
int CSimpleTextT<TYPE>::Create(const CStringArray& as, int nMode/*2*/)
{
  // nMode=-1 - nothig add to end of each string
  // nMode=0  - add \0 to end of each string and \0\0 at and
  // nMode=1  - add \n to end of each string and \0 at and
  // nMode=2  - add \r\n to end of each string and \0 at and
  DWORD dwSize = 0;
  /*LPTSTR*/TYPE* p;
  int   i;

  BOOL bFFFE = (nMode&flagFFFE) && (sizeof(TYPE)>1);//UNICODE
  nMode &= ~flagFFFE;

  for(dwSize=0, i=0; i<as.GetSize(); ++i)
    dwSize += as[i].GetLength()*sizeof(TYPE);

  if(nMode==0 || nMode==1)
    dwSize += (as.GetSize() + 0)*sizeof(TYPE);  //AY 23.07.2010 OLD:(as.GetSize() + 1)
  if(nMode==2)
    dwSize += (2*as.GetSize() + 0)*sizeof(TYPE);//AY 23.07.2010 OLD:(2*as.GetSize() + 1)

  if(m_pText!=NULL)
    { throwed_free(m_pText); m_nSize = 0; }
  m_pText = throwed_malloc(dwSize + sizeof(TYPE)/*last zero*/ + sizeof(TYPE)*2/*FFFE reserved*/);
  m_nSize = dwSize;

  p=(TYPE*)m_pText;

  if(bFFFE) {
    *p++ = char_t(UNICODE_CHAR());
    m_nSize += sizeof(TYPE);
  }
  

  for(i=0; i<as.GetSize(); ++i) {
    YTextT<TYPE>::t2scpy(p,(LPCTSTR)as[i]);//AY 07.11.2008
    p += as[i].GetLength();
    if(nMode==0)
      *p++ = _T('\0');
    if(nMode==1)
      *p++ = _T('\n');
    if(nMode==2)
      *p++ = _T('\r'), *p++ = _T('\n');

#if 0 //old realization //AY 07.11.2008
    CString sz = as[i];
    const int nApp = sizeof(TCHAR);
    const int nTyp = sizeof(TYPE);

    #if defined(UNICODE) || defined(_UNICODE)
      if(nApp==nTyp) {
        int nLen = as[i].GetLength();
        w2tcpy(p, as[i]);//AY 07.11.2008
        //memcpy(p,(LPCTSTR)as[i],as[i].GetLength()*sizeof(TCHAR)); //use TCHAR!
        p += as[i].GetLength()/**sizeof(TCHAR)*/;            //use TCHAR!
        if(nMode==0)
          *p++ = '\0';
        if(nMode==1)
          *p++ = '\n';
        if(nMode==2) 
          *p++ = '\r', *p++ = '\n';
      }
      else 
        if(nApp>nTyp) {
          int dst_length = ::WideCharToMultiByte(CP_ACP, 0, as[i], -1, NULL, 0, NULL, NULL);
          char* dst_string = new char[dst_length+1];
//          ::WideCharToMultiByte(CP_ACP, 0, as[i], -1, p, dst_length+1, NULL, NULL);
          
          memcpy(p,dst_string,dst_length);
          p += dst_length;
          if(nMode==0)
            *p++ = _T('\0');
          if(nMode==1)
            *p++ = _T('\n');
          if(nMode==2)
            *p++ = _T('\r'), *p++ = _T('\n');
          delete[] dst_string;
        }
    #else
      if(nApp==nTyp) {
        memcpy(p,as[i],as[i].GetLength()*sizeof(TCHAR)); //use TCHAR!
        p += as[i].GetLength()*sizeof(TCHAR);            //use TCHAR!
        if(nMode==0)
          *p++ = _T('\0');
        if(nMode==1)
          *p++ = _T('\n');
        if(nMode==2)
          *p++ = _T('\r'), *p++ = _T('\n');
      }
      else ASSERT(0);
    #endif
#endif
  }
  *p = char_t('\0');
  return 0;
}

template<class TYPE>
int CSimpleTextT<TYPE>::RemoveZeros()
{
  if(m_nSize<=sizeof(TYPE) || !m_pText)
    return 0;
  TYPE* pBeg = (TYPE*)m_pText;
  TYPE* pEnd = pBeg + m_nSize/sizeof(TYPE);
  TYPE* pSrc = pBeg;
  TYPE* pTar = pBeg;
  while(pSrc+1<pEnd) {
    if(*pSrc) 
      *pTar++ = *pSrc++;
    else //skip zero
      pSrc++;
  }
  *pTar++ = *pSrc++;//last char unconditionally
  m_nSize = (pTar - pBeg)*sizeof(TYPE); //new size
  return pEnd - pTar;//skipped zeros
}

template<> inline
CString CSimpleTextT<char>::GetString(int nString, const char* szDelimiters/*"\r\n"*/)
{
  size_t nAns;
  char* szAns = xstrnsubA(nString,(const char*)m_pText,m_nSize,&nAns,szDelimiters);
  #if  defined(UNICODE)
    XDEBUG_NOTIFY(XDEBUG_ANSI_TO_UNICODE);
  #endif
  return CString(szAns,nAns);
}
template<> inline
CString CSimpleTextT<wchar_t>::GetString(int nString, const wchar_t* szDelimiters/*"\r\n"*/)
{
  size_t   nAns;
  wchar_t* szAns = xstrnsubW(nString,(const wchar_t*)m_pText,m_nSize/sizeof(wchar_t),&nAns,szDelimiters);
  #if !defined(UNICODE)
    XDEBUG_NOTIFY(XDEBUG_UNICODE_TO_ANSI);
  #endif
  return CString(szAns,nAns);
}

template<> inline
CString CSimpleTextT<char>::GetAsString() const
{
  return CString((const char*)GetText(),GetSize()/sizeof(char));
}
template<> inline
CString CSimpleTextT<wchar_t>::GetAsString() const
{
  return CString((const wchar_t*)GetText(),GetSize()/sizeof(wchar_t));
}


template<class TYPE>
int CSimpleTextT<TYPE>::AddFormattedString(LPCTSTR lpszFormat, ... )
{
  CString sz;
  va_list args;
  va_start(args, lpszFormat);
  sz.FormatV(lpszFormat, args);

  int nAddSize = sz.GetLength()*sizeof(TYPE);
  if(m_pText==NULL) { 
    m_pText = throwed_malloc(nAddSize + sizeof(TYPE), NULL);
    m_nSize = 0;
  }else{
    //zero already exists
    m_pText = throwed_realloc(m_pText, m_nSize + nAddSize + sizeof(TYPE));//AY 24.03.2009: add zero
  }

  YTextT<TYPE>::t2scpy(((TYPE*)m_pText)+m_nSize/sizeof(TYPE), (LPCTSTR)sz);//AY 07.11.2008
  m_nSize += nAddSize;

  return 0;
}

template<class TYPE>
ULONG    CSimpleTextT<TYPE>::GetXmlProfileInt(LPCTSTR szSection, LPCTSTR szKeyName, UINT nDefault, int* piErr) const
{
  CString sz = GetXmlProfileString(szSection, szKeyName, NULL, piErr);
  if(sz.IsEmpty())
    return nDefault;
  sz.TrimLeft();
  sz.TrimRight();
  LPTSTR pszEnd;
  unsigned long nValue = _tcstoul((LPCTSTR)sz,&pszEnd,0);
  if(*pszEnd!=_T('\0'))
    return nDefault;
  return nValue;
}

//template<> ULONG  CSimpleTextT<wchar_t>::GetXmlProfileInt(LPCTSTR szSection, LPCTSTR szKeyName, UINT nDefault) const;
//template<> ULONG  CSimpleTextT<char>   ::GetXmlProfileInt(LPCTSTR szSection, LPCTSTR szKeyName, UINT nDefault) const;

template<> CString  CSimpleTextT<wchar_t>::GetXmlProfileString(LPCTSTR szSection, LPCTSTR szKeyName, LPCTSTR szDefault, int* pErr) const;
template<> CString  CSimpleTextT<char>   ::GetXmlProfileString(LPCTSTR szSection, LPCTSTR szKeyName, LPCTSTR szDefault, int* pErr) const;

#endif//__YTEXT_H
#pragma once
