#ifndef _CSTR_FMT_
#define _CSTR_FMT_
#include "xunicod.h"
template <class STRING=CString>
class CStrFmtTmpl: public STRING
{
public:
	CStrFmtTmpl(LPCTSTR lpszFormat, ...)
	{
		va_list argList;
		va_start(argList, lpszFormat);
		FormatV(lpszFormat, argList);
		va_end(argList);
	}
};

typedef CStrFmtTmpl<> CStrFmt;


class CStringMBCS: public CString
{
public:  
    CStringMBCS():CString(){}
    // copy constructor
    CStringMBCS(const CString& stringSrc):CString(stringSrc){}
    // from a single character
    CStringMBCS(TCHAR ch, int nRepeat = 1):CString(ch,nRepeat){}
    // from an ANSI string (converts to TCHAR)
    CStringMBCS(LPCSTR lpsz):CString(lpsz){}
    // from a UNICODE string (converts to TCHAR)
    CStringMBCS(LPCWSTR lpsz):CString(lpsz){}
    // subset of characters from an ANSI string (converts to TCHAR)
    CStringMBCS(LPCSTR lpch, int nLength):CString(lpch, nLength){}
    // subset of characters from a UNICODE string (converts to TCHAR)
    CStringMBCS(LPCWSTR lpch, int nLength):CString(lpch,nLength){}
    // from unsigned characters
    CStringMBCS(const unsigned char* psz):CString(psz){}
    const CString& operator=(const CStringMBCS& stringSrc) { *(CString*)this = stringSrc; return *this;}

    CString& Str(){ return *(CString*)this;}
    LPCTSTR lpctstr(){ return (LPCTSTR)*(CString*)this;}
    
    //operator LPCSTR() {  return MBCS();    }

     LPCSTR MBCS(){
      
#ifndef UNICODE
      return (LPCTSTR)(*this);
#else
      int l1=GetLength()+1;
      ba.SetSize(l1);
      LPSTR szData = (LPSTR)ba.GetData();
      
      wz2szncpy(szData, lpctstr(), l1,l1-1);
      /*	
      BOOL bDefaultChar=FALSE;
      char def='#';
      int r=WideCharToMultiByte(CP_ACP, 0, lpctstr(),0, szData ,l1-1,&def, &bDefaultChar);
      //*/
      return szData;
#endif
    }

    CByteArray ba;
};

#include "YTime.h"
__inline YTimeSpan SRTTime2YTimeSpan(LPCTSTR szTime, BOOL bForcePoint=FALSE, TCHAR spl1=_T(':'), TCHAR spl2=_T(','))
{
    CString szt(szTime);
    int l=szt.GetLength();
    int p1=szt.Find(spl1);
    int p2=szt.Find(spl1,p1+1);
    int p3=szt.Find(spl2,p2+1);
    if(p1<0 || p2 <0 || (p3<0 && !bForcePoint))
        return YTimeSpan(0,0,0,0,0);
    CString sz(bForcePoint);
    CString H=szt.Left(p1);
    CString M=szt.Mid(p1+1,p2-p1-1);
    CString S=szt.Mid(p2+1,p3-p2-1);
    CString MS=p3>=0?szt.Mid(p3+1,l-p3-1):"";
    int h=_ttoi(H);
    int m=_ttoi(M);
    int s=_ttoi(S);
    int ms=_ttoi(MS);
    
    return YTimeSpan(0,h,m,s,ms);
}

__inline YTimeSpan Str2YTimeSpan(LPCTSTR szTime, TCHAR spl1=_T('-'), TCHAR spl2=_T('.'))
{
    CString szt(szTime);
    int l=szt.GetLength();
    int p1=szt.Find(spl1);
    int p2=szt.Find(spl1,p1+1);
    int p3=szt.ReverseFind(spl2);
    
    CString H=(p2>0)?szt.Left(p1):"";
    CString M=(p2>0)?szt.Mid(p1+1,p2-p1-1):
    (p1>0?szt.Left(p1):(p3>0?"":szt));
    CString S=(p2>0)?szt.Mid(p2+1,__max(p3,l)-p2-1):(p1>0?szt.Mid(p1+1,__max(p3,l)-p1-1):(p3>0?szt.Left(p3):""));
    CString MS=p3>=0?szt.Mid(p3+1,l-p3-1):"";
    int h=_ttoi(H);
    int m=_ttoi(M);
    int s=_ttoi(S);
    int ms=_ttoi(MS);
    
    return YTimeSpan(0,h,m,s,ms);
}



__inline YTimeSpan DLGTime2YTimeSpan(LPCTSTR szTime)
{
    CString szt(szTime);
    int l=szt.GetLength();
    int p1=szt.Find(_T(':'));
    int p2=szt.Find(_T(':'),p1+1);
    int p3=szt.Find(_T(','),p2+1);
    if(p3<0)p3=szt.Find(_T('.'),p2+1);
    if(p3<0)p3=szt.GetLength(), szt+=_T(".0");
    if(p1<0 || p2 <0 || p3<0)
        return YTimeSpan(0,0,0,0,0);
    CString H=szt.Left(p1);
    CString M=szt.Mid(p1+1,p2-p1-1);
    CString S=szt.Mid(p2+1,p3-p2-1);
    CString MS=szt.Mid(p3+1,l-p3-1);
    int h=_ttoi(H);
    int m=_ttoi(M);
    int s=_ttoi(S);
    int ms=_ttoi(MS);
    
    return YTimeSpan(0,h,m,s,ms);
}


__inline CTime FileDateToCTime(LPCTSTR szDate, TCHAR spl1=_T('-'))
{
    CString szt(szDate);
    int l=szt.GetLength();
    int p1=szt.Find(spl1);
    int p2=szt.Find(spl1,p1+1);
    if(p2<0)
        return CTime();
    CString Y=szt.Left(p1);
    CString M=szt.Mid(p1+1,p2-p1-1);
    CString D=szt.Mid(p2+1, l-p2-1);
    int y =_ttoi(Y);
    int m =_ttoi(M);
    int d =_ttoi(D);
    
    return CTime(y,m,d,0,0,0);
}

__inline int FileNamePeriod(LPCTSTR strPeriod, CString& szBeg, CString& szEnd)
{
    CString szPeriod(strPeriod);
    int l_1 = szPeriod.GetLength()-1;
    int p=szPeriod.Find(_T("--"),0);
    int p1=p>0?p: (szPeriod[l_1]==_T('-')?l_1:0);
    int p2=p>0?l_1-1-p: (szPeriod[0]==_T('-')?l_1:0);

    szBeg = szPeriod.Left(p1);
    szEnd = szPeriod.Right(p2);

    YTimeSpan tsBeg = Str2YTimeSpan(szBeg);
    YTimeSpan tsEnd = Str2YTimeSpan(szEnd);

    szBeg=tsBeg.Format(_T("%H:%M:%S.%3R"));
    szEnd=tsEnd.Format(_T("%H:%M:%S.%3R"));

    return (p1>0 || p2>0)?0:-1;
}



__inline YTimeSpan XMLTime2YTimeSpan(LPCTSTR szTime)
{
    CString szt(szTime);
    int l=szt.GetLength();
    int p1=szt.Find(_T('.'));
    if(p1<0 )
        return YTimeSpan(0,0,0,0,0);
   
    CString S=szt.Left(p1);
    CString MS=szt.Mid(p1+1,l-p1-1);
    
    int s=_ttoi(S);
    int h=s/3600;
    int m=(s%3600)/60;
    s=s%60;
    int ms=_ttoi(MS);
    
    return YTimeSpan(0,h,m,s,ms);
}

__inline CString GetWord(LPCTSTR pszText, int iWord=0, LPCTSTR* pszWordEnd=NULL)
{
    do{
        CString text(pszText);
        text.TrimLeft();
        int p1=text.Find(_T(' '));
        int p2=text.Find(_T(','));
        int p3=text.Find(_T('.'));
        int p4=text.Find(_T(';'));
    
        int p=p1>0?p1:(p2>0?p2:(p3>0?p3:p4>0?p4:text.GetLength()));
        iWord--;
        if(p<1)
            return _T("");
        if(iWord<0)
        {  
            CString szRet=text.Left(p);
            if(pszWordEnd)
                *pszWordEnd=pszText+p+1;
            return szRet;
        }
        pszText+=p+1;
    }while(1);
    ASSERT(0);
    return _T("");
}


#endif// _CSTR_FMT_


