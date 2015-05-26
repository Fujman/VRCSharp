#ifndef __C_STRING_H
#define __C_STRING_H
#include <string.h>
#include "xunicod.h"

#define  C_STRING_IS_EMPTY(s) ((s)==NULL || *(s)=='\0') //AY 31.08.2012

#define  C_STRING_ONE_OF(s1,s2) (!C_STRING_IS_EMPTY(s1)?(s1):(s2)) //AY 17.04.2014

//------------------------------------------------------------
// C++ extensions

#ifdef __cplusplus
  size_t c_string_text2c(LPTSTR_COMPLEMENT sz);
  size_t c_string_c2text(LPTSTR_COMPLEMENT sz);
#endif

//------------------------------------------------------------
// C  compatible

#ifdef __cplusplus
extern "C" {
#endif

  size_t c_string_text2c(LPTSTR sz); // "\x0A"->"\\n" == '\n'
  size_t c_string_c2text(LPTSTR sz); // "\\n"->"\x0A" == EOL

  LPTSTR strins(LPTSTR dest, LPCTSTR targ, int pos);
  LPTSTR strnins(LPTSTR string, LPCTSTR substring, int pos, int max);
  LPTSTR strrpl(LPTSTR string, LPCTSTR substring, LPTSTR replace);
  LPTSTR strnrpl(LPTSTR string, LPCTSTR substring, LPTSTR replace, int max);
  LPTSTR strirpl(LPTSTR string, LPCTSTR substring, LPTSTR replace);
  LPTSTR strnirpl(LPTSTR string, LPCTSTR substring, LPTSTR replace, int max);
  int    replaced_substrings(void);
  LPTSTR strcatp(LPTSTR string, LPTSTR *substrings, int count, TCHAR delim);
  LPTSTR strncatp(LPTSTR string, LPTSTR *substrings, int count, TCHAR delim, int max);
  LPTSTR rtrim(LPTSTR string);
  LPTSTR ltrim(LPTSTR string);
  LPTSTR strtrim(LPTSTR string);
  LPTSTR strdelsp(LPTSTR string);
  LPTSTR strgluesp(LPTSTR string);
  LPTSTR rspace(LPTSTR string, int length);
  LPTSTR lastchar(LPTSTR string);
  LPTSTR ctos(TCHAR c);
  LPTSTR strlow(LPTSTR str);
  LPTSTR strupp(LPTSTR str);
  LPTSTR strfill(LPTSTR str, LPCTSTR szFill, size_t n);//AY 25.10.2006

  typedef struct tag_string_parserA {
    LPSTR path;
    int  size;
    CHAR last;
    CHAR delimiter;
  } string_parserA;

  void  parse_initA(string_parserA *pi, LPSTR path, CHAR delimiter);
  LPSTR parse_firstA(string_parserA *pi, LPSTR path, CHAR delimiter);
  LPSTR parse_nextA(string_parserA *pi);
  void  parse_termA(string_parserA *pi);

  typedef struct tag_string_parserW {
    LPWSTR path;
    int  size;
    WCHAR last;
    WCHAR delimiter;
  } string_parserW;

  void  parse_initW(string_parserW *pi, LPWSTR path, WCHAR delimiter);
  LPWSTR parse_firstW(string_parserW *pi, LPWSTR path, WCHAR delimiter);
  LPWSTR parse_nextW(string_parserW *pi);
  void  parse_termW(string_parserW *pi);

#if defined(UNICODE) || defined(_UNICODE)
  #define parse_init      parse_initW
  #define parse_first     parse_firstW
  #define parse_next      parse_nextW
  #define parse_term      parse_termW
  typedef string_parserW  string_parser;
#else
  #define parse_init      parse_initA
  #define parse_first     parse_firstA
  #define parse_next      parse_nextA
  #define parse_term      parse_termA
  typedef string_parserA  string_parser;
#endif

#ifdef __cplusplus
}
#endif

#endif//__C_STRING_H
