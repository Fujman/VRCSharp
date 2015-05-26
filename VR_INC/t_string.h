#ifndef __T_STRING_H
#define __T_STRING_H
#include <stdarg.h>
#include <tchar.h>
#include <wchar.h>
#include <mbstring.h>
#include <malloc.h>

#define  tchr TCHAR 
#define  wchr wchar_t
#define  mchr unsigned char

#ifdef __cplusplus

template <class CHAR> size_t strlenT         (const CHAR *s);
template <class CHAR> CHAR*  strdupT         (const CHAR *s);
template <class CHAR> CHAR*  struprT         (      CHAR *s);
template <class CHAR> CHAR*  strlwrT         (      CHAR *s);
template <class CHAR> CHAR*  strrevT         (      CHAR *s);
template <class CHAR> CHAR*  strrchrT        (const CHAR *s,       CHAR  c);
template <class CHAR> CHAR*  strchrT         (const CHAR *s,       CHAR  c);
template <class CHAR> CHAR*  strstrT         (const CHAR *s, const CHAR *e);
template <class CHAR> CHAR*  strcpyT         (      CHAR *t, const CHAR *s);
template <class CHAR> CHAR*  strcatT         (      CHAR *t, const CHAR *s);
template <class CHAR> CHAR*  strsetT         (      CHAR *t,       CHAR  s);
template <class CHAR> CHAR*  strncpyT        (      CHAR *t, const CHAR *s, size_t  n);
template <class CHAR> CHAR*  strncatT        (      CHAR *t, const CHAR *s, size_t  n);
template <class CHAR> CHAR*  strnsetT        (      CHAR *s,       CHAR  c, size_t  n);
template <class CHAR> int    strcmpT         (const CHAR *s, const CHAR *t);
template <class CHAR> int    stricmpT        (const CHAR *s, const CHAR *t);
template <class CHAR> int    strncmpT        (const CHAR *t, const CHAR *s, size_t  n);
template <class CHAR> int    strnicmpT       (const CHAR *t, const CHAR *s, size_t  n);
template <class CHAR> int    strcollT        (const CHAR *s, const CHAR *t);
template <class CHAR> int    stricollT       (const CHAR *s, const CHAR *t);
template <class CHAR> int    strncollT       (const CHAR *t, const CHAR *s, size_t  n);
template <class CHAR> int    strnicollT      (const CHAR *t, const CHAR *s, size_t  n);
template <class CHAR> CHAR*  strspnpT        (const CHAR *s, const CHAR *t);
template <class CHAR> size_t strcspnT        (const CHAR *s, const CHAR *t);
template <class CHAR> size_t strspnT         (const CHAR *s, const CHAR *t);
template <class CHAR> CHAR*  strpbrkT        (const CHAR *s, const CHAR *t);
template <class CHAR> CHAR*  strtokT         (      CHAR *s, const CHAR *t);

template <class CHAR> ULONG  strtoulT        (const CHAR *s,       CHAR**e, int base ); //AY 30.08.2011

template <> __inline  size_t strlenT   <char>(const char *s)                           { return  strlen(s);   }
template <> __inline  char*  strdupT   <char>(const char *s)                           { return _strdup(s);   }
template <> __inline  char*  struprT   <char>(      char *s)                           { return  strupr(s);   }
template <> __inline  char*  strlwrT   <char>(      char *s)                           { return  strlwr(s);   }
template <> __inline  char*  strrevT   <char>(      char *s)                           { return  strrev(s);   }
template <> __inline  char*  strrchrT  <char>(const char *s,       char  c)            { return  (char*)strrchr(s,c);}
template <> __inline  char*  strchrT   <char>(const char *s,       char  c)            { return  (char*)strchr(s,c); }
template <> __inline  char*  strstrT   <char>(const char *s, const char *e)            { return  (char*)strstr(s,e); }
template <> __inline  char*  strcpyT   <char>(      char *t, const char *s)            { return  (char*)strcpy(t,s); }
template <> __inline  char*  strcatT   <char>(      char *t, const char *s)            { return  (char*)strcat(t,s); }
template <> __inline  char*  strsetT   <char>(      char *t,       char  c)            { return  (char*)strset(t,c); }
template <> __inline  char*  strncpyT  <char>(      char *t, const char *s, size_t  n) { return  strncpy(t,s,n);  }
template <> __inline  char*  strncatT  <char>(      char *t, const char *s, size_t  n) { return  strncat(t,s,n);  }
template <> __inline  char*  strnsetT  <char>(      char *s,       char  c, size_t  n) { return  strnset(s,c,n);  }
template <> __inline  int    strcmpT   <char>(const char *s, const char *e)            { return  strcmp(s,e); }
template <> __inline  int    stricmpT  <char>(const char *s, const char *e)            { return  stricmp(s,e);}
template <> __inline  int    strncmpT  <char>(const char *t, const char *s, size_t  n) { return  strncmp(t,s,n);  }
template <> __inline  int    strnicmpT <char>(const char *t, const char *s, size_t  n) { return  strnicmp(t,s,n); }
template <> __inline  int    strcollT  <char>(const char *s, const char *e)            { return  strcoll(s,e);    }
template <> __inline  int    stricollT <char>(const char *s, const char *e)            { return _stricoll(s,e);}
template <> __inline  int    strncollT <char>(const char *t, const char *s, size_t  n) { return _strncoll(t,s,n); }
template <> __inline  int    strnicollT<char>(const char *t, const char *s, size_t  n) { return _strnicoll(t,s,n);}
template <> __inline  char*  strspnpT  <char>(const char *s, const char *e)            { return (*(s += strspn(s,e))!='\0') ? (char*)s : NULL; } //{ return _strspnp(s,e); }
template <> __inline  size_t strcspnT  <char>(const char *s, const char *e)            { return  strcspn(s,e); }
template <> __inline  size_t strspnT   <char>(const char *s, const char *e)            { return  strspn(s,e);  }
template <> __inline  char*  strpbrkT  <char>(const char *s, const char *e)            { return  (char*)strpbrk(s,e); }
template <> __inline  char*  strtokT   <char>(      char *s, const char *e)            { return  strtok(s,e);  }

template <> __inline  ULONG  strtoulT  <char>(const char *s,       char**e, int base ) { return  strtoul(s,e,base);  }

template <> __inline  size_t strlenT   <wchr>(const wchr *s)                           { return  wcslen(s);   }
template <> __inline  wchr*  strdupT   <wchr>(const wchr *s)                           { return _wcsdup(s);   }
template <> __inline  wchr*  struprT   <wchr>(      wchr *s)                           { return _wcsupr(s);   }
template <> __inline  wchr*  strlwrT   <wchr>(      wchr *s)                           { return _wcslwr(s);   }
template <> __inline  wchr*  strrevT   <wchr>(      wchr *s)                           { return _wcsrev(s);   }
template <> __inline  wchr*  strrchrT  <wchr>(const wchr *s,       wchr  c)            { return  (wchar_t*)wcsrchr(s,c);}
template <> __inline  wchr*  strchrT   <wchr>(const wchr *s,       wchr  c)            { return  (wchar_t*)wcschr(s,c); }
template <> __inline  wchr*  strstrT   <wchr>(const wchr *s, const wchr *e)            { return  (wchar_t*)wcsstr(s,e); }
template <> __inline  wchr*  strcpyT   <wchr>(      wchr *t, const wchr *s)            { return  (wchar_t*)wcscpy(t,s); }
template <> __inline  wchr*  strcatT   <wchr>(      wchr *t, const wchr *s)            { return  (wchar_t*)wcscat(t,s); }
template <> __inline  wchr*  strsetT   <wchr>(      wchr *t,       wchr  c)            { return  (wchar_t*)wcsset(t,c); }
template <> __inline  wchr*  strncpyT  <wchr>(      wchr *t, const wchr *s, size_t n)  { return  wcsncpy(t,s,n);  }
template <> __inline  wchr*  strncatT  <wchr>(      wchr *t, const wchr *s, size_t n)  { return  wcsncat(t,s,n);  }
template <> __inline  wchr*  strnsetT  <wchr>(      wchr *s,       wchr  c, size_t n)  { return  wcsnset(s,c,n);  }
template <> __inline  int    strcmpT   <wchr>(const wchr *s, const wchr *e)            { return  wcscmp(s,e); }
template <> __inline  int    stricmpT  <wchr>(const wchr *s, const wchr *e)            { return  wcsicmp(s,e);}
template <> __inline  int    strncmpT  <wchr>(const wchr *t, const wchr *s, size_t n)  { return  wcsncmp(t,s,n);  }
template <> __inline  int    strnicmpT <wchr>(const wchr *t, const wchr *s, size_t n)  { return _wcsnicmp(t,s,n); }
template <> __inline  int    strcollT  <wchr>(const wchr *s, const wchr *e)            { return  wcscoll(s,e); }
template <> __inline  int    stricollT <wchr>(const wchr *s, const wchr *e)            { return _wcsicoll(s,e);}
template <> __inline  int    strncollT <wchr>(const wchr *t, const wchr *s, size_t n)  { return _wcsncoll(t,s,n);  }
template <> __inline  int    strnicollT<wchr>(const wchr *t, const wchr *s, size_t n)  { return _wcsnicoll(t,s,n); }
template <> __inline  wchr*  strspnpT  <wchr>(const wchr *s, const wchr *e)            { return (*(s += wcsspn(s,e))!='\0') ? (wchar_t*)s : NULL; }//{ return _wcsspnp(s,e); }
template <> __inline  size_t strcspnT  <wchr>(const wchr *s, const wchr *e)            { return  wcscspn(s,e); }
template <> __inline  size_t strspnT   <wchr>(const wchr *s, const wchr *e)            { return  wcsspn(s,e);  }
template <> __inline  wchr*  strpbrkT  <wchr>(const wchr *s, const wchr *e)            { return  (wchar_t*)wcspbrk(s,e); }
template <> __inline  wchr*  strtokT   <wchr>(      wchr *s, const wchr *e)            { return  wcstok(s,e);  }

template <> __inline  ULONG  strtoulT  <wchr>(const wchr *s,       wchr**e, int base ) { return  wcstoul(s,e,base);  }

template <> __inline  size_t strlenT   <mchr>(const mchr *s)                           { return _mbslen(s);   }
template <> __inline  mchr*  strdupT   <mchr>(const mchr *s)                           { return _mbsdup(s);   }
template <> __inline  mchr*  struprT   <mchr>(      mchr *s)                           { return _mbsupr(s);   }
template <> __inline  mchr*  strlwrT   <mchr>(      mchr *s)                           { return _mbslwr(s);   }
template <> __inline  mchr*  strrevT   <mchr>(      mchr *s)                           { return _mbsrev(s);   }
template <> __inline  mchr*  strrchrT  <mchr>(const mchr *s,       mchr  c)            { return (mchr*)_mbsrchr(s,c);}
template <> __inline  mchr*  strchrT   <mchr>(const mchr *s,       mchr  c)            { return (mchr*)_mbschr(s,c); }
template <> __inline  mchr*  strstrT   <mchr>(const mchr *s, const mchr *e)            { return (mchr*)_mbsstr(s,e); }
template <> __inline  mchr*  strcpyT   <mchr>(      mchr *t, const mchr *s)            { return _mbscpy(t,s); }
template <> __inline  mchr*  strcatT   <mchr>(      mchr *t, const mchr *s)            { return _mbscat(t,s); }
template <> __inline  mchr*  strsetT   <mchr>(      mchr *t,       mchr  c)            { return _mbsset(t,c); }
template <> __inline  mchr*  strncpyT  <mchr>(      mchr *t, const mchr *s, size_t n)  { return _mbsncpy(t,s,n);  }
template <> __inline  mchr*  strncatT  <mchr>(      mchr *t, const mchr *s, size_t n)  { return _mbsncat(t,s,n);  }
template <> __inline  mchr*  strnsetT  <mchr>(      mchr *s,       mchr  c, size_t n)  { return _mbsnset(s,c,n);  }
template <> __inline  int    strcmpT   <mchr>(const mchr *s, const mchr *e)            { return _mbscmp(s,e); }
template <> __inline  int    stricmpT  <mchr>(const mchr *s, const mchr *e)            { return _mbsicmp(s,e);}
template <> __inline  int    strncmpT  <mchr>(const mchr *t, const mchr *s, size_t n)  { return _mbsncmp(t,s,n);  }
template <> __inline  int    strnicmpT <mchr>(const mchr *t, const mchr *s, size_t n)  { return _mbsnicmp(t,s,n); }
template <> __inline  int    strcollT  <mchr>(const mchr *s, const mchr *e)            { return _mbscoll(s,e); }
template <> __inline  int    stricollT <mchr>(const mchr *s, const mchr *e)            { return _mbsicoll(s,e);}
template <> __inline  int    strncollT <mchr>(const mchr *t, const mchr *s, size_t n)  { return _mbsncoll(t,s,n);  }
template <> __inline  int    strnicollT<mchr>(const mchr *t, const mchr *s, size_t n)  { return _mbsnicoll(t,s,n); }
template <> __inline  mchr*  strspnpT  <mchr>(const mchr *s, const mchr *e)            { return _mbsspnp(s,e); }
template <> __inline  size_t strcspnT  <mchr>(const mchr *s, const mchr *e)            { return _mbscspn(s,e); }
template <> __inline  size_t strspnT   <mchr>(const mchr *s, const mchr *e)            { return _mbsspn(s,e);  }
template <> __inline  mchr*  strpbrkT  <mchr>(const mchr *s, const mchr *e)            { return (mchr*)_mbspbrk(s,e); }
template <> __inline  mchr*  strtokT   <mchr>(      mchr *s, const mchr *e)            { return _mbstok(s,e);  }

template <> __inline  ULONG  strtoulT  <mchr>(const mchr *s,       mchr**e, int base ) { return  strtoul((const char*)s,(char**)e,base);  } //?


// strinc.strdec,strnextc,strninc,strncnt

template <class CHAR> unsigned strnextcT     (const CHAR *s)                { return (unsigned int)*s; }
template <class CHAR> CHAR*  strdecT         (const CHAR *b, const CHAR *s) { return b>=s?NULL:s-1; }
template <class CHAR> CHAR*  strincT         (const CHAR *s)                { return s+1; }
template <class CHAR> CHAR*  strnincT        (const CHAR *s, size_t n)      { return s+n; }
template <class CHAR> size_t strnbcntT       (const CHAR *s, size_t n)      { size_t len = strlenT(s); return (len>n) ? n : len; }
template <class CHAR> size_t strnccntT       (const CHAR *s, size_t n)      { size_t len = strlenT(s); return (len>n) ? n : len; }

template <> __inline  unsigned strnextcT<mchr>(const mchr *s)               { return _mbsnextc(s); }
template <> __inline  mchr*  strdecT   <mchr>(const mchr *b, const mchr *s) { return _mbsdec(b,s); }
template <> __inline  mchr*  strincT   <mchr>(const mchr *s)                { return _mbsinc(s);   }
template <> __inline  mchr*  strnincT  <mchr>(const mchr *s, size_t n)      { return _mbsninc(s,n);}
template <> __inline  size_t strnbcntT <mchr>(const mchr *s, size_t n)      { return _mbsnbcnt(s,n); }
template <> __inline  size_t strnccntT <mchr>(const mchr *s, size_t n)      { return _mbsnccnt(s,n); }

// sprintf

template <class CHAR, class CHARF> int    sprintfT (CHAR *s, const CHARF *f, ... );
template <class CHAR, class CHARF> int    vsprintfT(CHAR *s, const CHARF *f, va_list a);

template <> __inline int     sprintfT<char,char>(char *s, const char *f, ...)
{ 
  va_list args; va_start(args,f); return vsprintf(s,f,args);
}
template <> __inline int     sprintfT<wchr,wchr>(wchr *s, const wchr *f, ...)
{ 
  va_list args; va_start(args,f); return vswprintf(s,f,args);
}

template <> __inline int     vsprintfT<char,char>(char *s, const char *f, va_list a) 
{ 
  return  vsprintf(s,f,a); 
}
template <> __inline int     vsprintfT<wchr,wchr>(wchr *s, const wchr *f, va_list a) 
{ 
  return  vswprintf(s,f,a); 
}

template <> inline int sprintfT<char,wchr>(char *s, const wchr *f, ...)
{ 
  size_t n = wcstombs(NULL,f,0) + 1;
  char* pf = (char*)_alloca(n*sizeof(char));
  wcstombs(pf,f,n);
  va_list args; va_start(args,f); return vsprintf(s,pf,args);
}
template <> inline int sprintfT<wchr,char>(wchr *s, const char *f, ...)
{ 
  size_t n = mbstowcs(NULL,f,0) + 1;
  wchr* pf = (wchr*)_alloca(n*sizeof(wchr));
  mbstowcs(pf,f,n);
  va_list args; va_start(args,f); return vswprintf(s,pf,args);
}

template <> inline int     vsprintfT<char,wchr>(char *s, const wchr *f, va_list a)
{ 
  size_t n = wcstombs(NULL,f,0) + 1;
  char* pf = (char*)_alloca(n*sizeof(char));
  wcstombs(pf,f,n);
  return  vsprintf(s,pf,a); 
}
template <> inline int     vsprintfT<wchr,char>(wchr *s, const char *f, va_list a) 
{ 
  size_t n = mbstowcs(NULL,f,0) + 1;
  wchr* pf = (wchr*)_alloca(n*sizeof(wchr));
  mbstowcs(pf,f,n);
  return  vswprintf(s,pf,a); 
}

#endif//__cplusplus

#undef   tchr
#undef   wchr
#undef   mchr
#endif//__T_STRING_H
