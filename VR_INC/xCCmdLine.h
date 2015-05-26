#ifndef __XCCMDLINE_H
#define __XCCMDLINE_H
#include "xCString.h"
#include "xunicod.h"
#include "xdebug.h"

////////////////////////////////////////////////////////////////////////
//
// CCmdLine
//
#define CCMDLINE__DELIMITERS _T(" \t")
#define CCMDLINE__KEY_SLASH  _T('/')
#define CCMDLINE__KEY_EQUAL  _T('=')
#define CCMDLINE__KEY_QUOTE  _T('\"')
#define CCMDLINE__KEY_QMASK  _T('\\')

#define CCMDLINE const CString&

inline
CString CCmdLine__InsertQuotes(CCMDLINE a_szKeyValue)
{
  TCHAR cQuote = CCMDLINE__KEY_QUOTE;
  CString szKeyValue = a_szKeyValue;
  BOOL bBegQuote = !szKeyValue.IsEmpty() && szKeyValue[0]==cQuote;
  BOOL bEndQuote = szKeyValue.GetLength()>1 && szKeyValue[szKeyValue.GetLength()-1]==cQuote;
  if(bBegQuote!=bEndQuote)
    TRACE(DEBUGPLACE("WARNING : unbalanced quotes\n"));

  if(!bBegQuote)
    szKeyValue.Insert(0,cQuote);
  if(!bEndQuote)
    szKeyValue += cQuote;
  return szKeyValue;
}

inline
CString CCmdLine__RemoveQuotes(CCMDLINE a_szKeyValue)
{
  static const TCHAR szQMasked[3] = {CCMDLINE__KEY_QMASK,CCMDLINE__KEY_QUOTE};
  TCHAR cQuote = CCMDLINE__KEY_QUOTE;

  CString szKeyValue = a_szKeyValue;
  BOOL bBegQuote = !szKeyValue.IsEmpty()    && szKeyValue[0]==cQuote;
  BOOL bEndQuote = szKeyValue.GetLength()>1 && szKeyValue[szKeyValue.GetLength()-1]==cQuote;
  if(bBegQuote!=bEndQuote)
    TRACE(DEBUGPLACE("WARNING : unbalanced quotes\n"));

  if(bBegQuote)
    szKeyValue.Delete(0,1);
  if(bEndQuote)
    szKeyValue.Delete(szKeyValue.GetLength()-1,1);

  if(bBegQuote && bEndQuote) { // \" -> "
    int iPos = -1;
    do {
      iPos = szKeyValue.Find(szQMasked);
      if(iPos>=0)
        szKeyValue.Delete(iPos,1);
    }while(iPos>=0);
  }
  return szKeyValue;
}

inline CString CCmdLine__GetCmdLineToken(CCMDLINE szCmdLine, int nLine, LPCTSTR szDelimiters=NULL) //NULL is " \t"
{
  szDelimiters = szDelimiters!=NULL ? szDelimiters : CCMDLINE__DELIMITERS;
  TCHAR cQuote = CCMDLINE__KEY_QUOTE;
  TCHAR cQMask = CCMDLINE__KEY_QMASK;
  CString sz   = szCmdLine;
  //replace quotes and spaces in temporary copy
    LPTSTR s = sz.LockBuffer();
    BOOL bInQuote = FALSE;
    for(int i=0; i<sz.GetLength(); ++i) {
      if(s[i]==cQuote && !bInQuote) {
        bInQuote = TRUE;
        s[i] = '_';
      }
      if(s[i]==cQuote &&  bInQuote) {
        if(i>0 && s[i-1]==cQMask){ // \"
          //skip
        }else{
          bInQuote = FALSE;
        }
        s[i] = '_';
      }

      BOOL bIsDelimiter = _tcschr(szDelimiters,s[i])!=NULL;
      BOOL bIsPrevDelim = i>0 && _tcschr(szDelimiters,s[i-1])!=NULL;

      if(bInQuote && bIsDelimiter)
        s[i] = '_'; //mask spaces

      if(!bInQuote && bIsDelimiter && bIsPrevDelim) 
        s[i-1] = '_'; //concatenate delimiters
    }
    sz.UnlockBuffer();
  //
  size_t  nAns  = 0; 
  LPTSTR  szAns = xstrnsub(nLine,(LPCTSTR)sz,sz.GetLength(),&nAns,szDelimiters); //parse masked...
  int     nPos  = LPCTSTR(szAns)-LPCTSTR(sz); //... return original
  CString szRet = nAns?szCmdLine.Mid(nPos,nAns):CString(); //OLD: CString szRet(szAns,nAns);
  szRet.TrimRight(szDelimiters);
//szRet.TrimRight(_T("\r\n\f\x1A"));//CR,LF,FF,EOF
  return szRet;
}

//
// returned key value is always with quotes
//
inline CString CCmdLine__GetCmdLineArg(CCMDLINE szCmdLine, int nArg)
{
  TCHAR cSlash = CCMDLINE__KEY_SLASH;
  ASSERT(nArg>0);
  CString szCmd = szCmdLine;
  CString szToken;
  int iArg   = 0;
  int iToken = 0;
  do{
    szToken = CCmdLine__GetCmdLineToken(szCmd,iToken++);
    if(!szToken.IsEmpty() && szToken[0]!=cSlash)
      iArg++;
    if(iArg==nArg)
      return CCmdLine__InsertQuotes(szToken);
  }while(!szToken.IsEmpty());
  return CString();
}

//
// returned key value is always with quotes
//
inline CString CCmdLine__GetCmdLineKey(CCMDLINE szCmdLine, LPCTSTR szKey, BOOL bAlredyUpper=FALSE, LPCTSTR szDelimiters=NULL, BOOL bIsPath=FALSE)
{
  static const TCHAR szQuotes[3] = {CCMDLINE__KEY_QUOTE,CCMDLINE__KEY_QUOTE};
  szDelimiters = szDelimiters!=NULL ? szDelimiters : CCMDLINE__DELIMITERS;
  TCHAR cSlash = CCMDLINE__KEY_SLASH;
  TCHAR cEqual = CCMDLINE__KEY_EQUAL;
  TCHAR cQuote = CCMDLINE__KEY_QUOTE;
  TCHAR cQMask = CCMDLINE__KEY_QMASK;

  CString szCmd = szCmdLine;
  if(!bAlredyUpper)
    szCmd.MakeUpper();//copy
  CString szBeg = szKey;
  CString szBeQ = szBeg + cEqual;
#ifdef _DEBUG
  ASSERT(!szBeg.IsEmpty() && szBeg[szBeg.GetLength()-1]!=cEqual);
  szBeg.MakeUpper();
  ASSERT(szBeg==szKey);
#endif
  if(szBeg[0]!=cSlash)
    szBeg.Insert(0,cSlash);
  int nKey = szCmd.Find(szBeg);
  if(nKey<0)
    return CString();

  CString szKeyValue = szQuotes;    //empty
  if(szCmd.Find(szBeQ,nKey)==nKey) {// /KEY=
    szKeyValue = szCmdLine.Mid(nKey+1+szBeg.GetLength());
    if(!szKeyValue.IsEmpty()) {     // /KEY=*
      if(szKeyValue[0]==cQuote) {     // /KEY="*"
        int iEnd = -1;
        int iBeg = 1;
        LPCTSTR s = LPCTSTR(szKeyValue);
        do{
          iEnd = szKeyValue.Find(cQuote,iBeg);
          if(!bIsPath)//AY 24.07.2012
            if(iEnd>0 && szKeyValue[iEnd-1]==cQMask) //skip \"
              { iBeg = iEnd+1; continue; }
          break;
        }while(1);
        if(iEnd>=0)
          szKeyValue = szKeyValue.Left(iEnd+1);
        else
          szKeyValue += cQuote;
      }else{                        // /KEY=*
        int iEnd = szKeyValue.FindOneOf(CCMDLINE__DELIMITERS);
        if(iEnd>=0)
          szKeyValue = szKeyValue.Left(iEnd);
        CCmdLine__InsertQuotes(szKeyValue);
      }
    }
  }else{                            // /KEY
    TCHAR c = LPCTSTR(szCmd)[nKey+szBeg.GetLength()];
    if(c!='\0' && _tcschr(szDelimiters,c)==NULL)
      szKeyValue.Empty();//not found   /KEYANOTHER
  }
  return szKeyValue;
}

//////////////////////////////////////////////////////////////////////////
// CCmdLine__

inline CString CCmdLine__GetCmdArg(CCMDLINE szCmdLine, int nArg)
{
  CString szArgValue = CCmdLine__GetCmdLineArg(szCmdLine, nArg);
          szArgValue = CCmdLine__RemoveQuotes(szArgValue);
  return  szArgValue;
}

inline BOOL    CCmdLine__IsCmdKey(CCMDLINE szCmdLine, LPCTSTR szKey, BOOL bAlredyUpper=FALSE)
{
  CString szKeyValue = CCmdLine__GetCmdLineKey(szCmdLine, szKey, bAlredyUpper);
  return !szKeyValue.IsEmpty();
}

inline CString CCmdLine__GetCmdKey(CCMDLINE szCmdLine, LPCTSTR szKey, BOOL bAlredyUpper=FALSE, BOOL bIsPath=FALSE)
{
  CString szKeyValue = CCmdLine__GetCmdLineKey(szCmdLine, szKey, bAlredyUpper, NULL, bIsPath);
          szKeyValue = CCmdLine__RemoveQuotes(szKeyValue);
  return  szKeyValue;
}

inline BOOL    CCmdLine__IsEmptyKey(CCMDLINE szCmdLine, LPCTSTR szKey, BOOL bAlredyUpper=FALSE)
      { return CCmdLine__GetCmdKey(szCmdLine, szKey, bAlredyUpper).IsEmpty(); }


inline BOOL    CCmdLine__IsCmdKey(CCMDLINE szCmdLine, LPCTSTR_COMPLEMENT szKey, BOOL bAlredyUpper=FALSE)
      { return CCmdLine__IsCmdKey(szCmdLine, CString(szKey), bAlredyUpper); }
inline CString CCmdLine__GetCmdKey(CCMDLINE szCmdLine, LPCTSTR_COMPLEMENT szKey, BOOL bAlredyUpper=FALSE, BOOL bIsPath=FALSE)
      { return CCmdLine__GetCmdKey(szCmdLine, CString(szKey), bAlredyUpper,bIsPath); }
inline BOOL    CCmdLine__IsEmptyKey(CCMDLINE szCmdLine, LPCTSTR_COMPLEMENT szKey, BOOL bAlredyUpper=FALSE)
      { return CCmdLine__IsEmptyKey(szCmdLine, CString(szKey), bAlredyUpper); }

#undef CCMDLINE

//////////////////////////////////////////////////////////////////////////
// CCmdLine
class CCmdLine
{
public:
  static CString  GetCmdLine() 
                    { CString szCmdLine = ::AfxGetApp()->m_lpCmdLine; /*szCmdLine.MakeUpper();*/ return szCmdLine; }

  static CString  GetCmdArg(int nArg)
                    { return CCmdLine__GetCmdArg(GetCmdLine(), nArg); }

  static BOOL     IsEmptyKey(LPCTSTR szKey)
                    { return CCmdLine__IsEmptyKey(GetCmdLine(), szKey); }
  static BOOL     IsCmdKey(LPCTSTR szKey)
                    { return CCmdLine__IsCmdKey(GetCmdLine(), szKey); }
  static CString  GetCmdKey(LPCTSTR szKey)
                    { return CCmdLine__GetCmdKey(GetCmdLine(), szKey); }

  static BOOL     IsEmptyKey(LPCTSTR_COMPLEMENT szKey)
                    { return CCmdLine__IsEmptyKey(GetCmdLine(), szKey); }
  static BOOL     IsCmdKey(LPCTSTR_COMPLEMENT szKey)
                    { return CCmdLine__IsCmdKey(GetCmdLine(), szKey); }
  static CString  GetCmdKey(LPCTSTR_COMPLEMENT szKey)
                    { return CCmdLine__GetCmdKey(GetCmdLine(), szKey); }
};


#endif//__XCCMDLINE_H
#pragma once
