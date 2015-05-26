#ifndef __XPRAGMA2_H
#define __XPRAGMA2_H
#include "xpragma.h"

//Example: #pragma message(__FILE__LINE__ ": warning : text text text" )

//#pragma message() support macroces:

/*
  #define xpragma__line__(line)    #line
  #define xpragma__line(line)      xpragma__line__(line)

  #define __FILE__LINE__ __FILE__ "(" xpragma__line(__LINE__) ")"
*/
    //      __DATE__ "Jun 10 2010"
    //                           n  B  r  r  Y  n  L  G  P  T  V  C
    //                          a  e  a  P  a  u  u  u  e  C  O  e
    //                         j  F  m  a  m  j  j  a  S  O  N  D
  //static LPCSTR s_months  = "JanFebMarAprMayJunJulAugSepOctNovDec";
  //static char   s_month[] = {__DATE__[0],__DATE__[1],__DATE__[2],0};

    #define __YEAR__ ((__DATE__[ 7]-'0')*1000 + \
                      (__DATE__[ 8]-'0')*100  + \
                      (__DATE__[ 9]-'0')*10   + \
                      (__DATE__[10]-'0'))

   #define __MONTH__ ( __DATE__[0]=='J'&&__DATE__[1]=='a'?  1 :\
                       __DATE__[0]=='F'                  ?  2 :\
                       __DATE__[0]=='M'&&__DATE__[2]=='r'?  3 :\
                     /*__DATE__[0]=='A'*/__DATE__[1]=='p'?  4 :\
                     /*__DATE__[0]=='M'*/__DATE__[2]=='y'?  5 :\
                       __DATE__[0]=='J'&&__DATE__[2]=='n'?  6 :\
                       __DATE__[0]=='J'&&__DATE__[2]=='l'?  7 :\
                     /*__DATE__[0]=='A'*/__DATE__[2]=='g'?  8 :\
                     /*__DATE__[0]=='S'*/__DATE__[2]=='p'?  9 :\
                     /*__DATE__[0]=='O'*/__DATE__[2]=='t'? 10 :\
                     /*__DATE__[0]=='N'*/__DATE__[2]=='v'? 11 :\
                     /*__DATE__[0]=='D'*/__DATE__[2]=='c'? 12 : 0)

    #define __DAY__  ((__DATE__[ 4]-'0')*10 + \
                      (__DATE__[ 5]-'0'))

    #define xpragma__number(num)  xpragma__line(num)

    #define __YEAR__MONTH__DAY__  xpragma__number(__YEAR__) "." xpragma__number(__MONTH__) "." xpragma__number(__DAY__)
    #define __DAY__MONTH__YEAR__  xpragma__number(__DAY__) "." xpragma__number(__MONTH__) "." xpragma__number(__YEAR__)

#endif//__XPRAGMA2_H
#pragma once
