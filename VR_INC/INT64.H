#ifndef __INT64_H
#define __INT64_H
///////////////////////////////////////////////////////////////////////

// ATTENTION! x86 architecture dependent!

///////////////////////////////////////////////////////////////////////
// types and constants

#ifndef QWORD_DEFINED
#define QWORD_DEFINED
  typedef unsigned __int64 QWORD;
  #define LODWORD(qw)      ((DWORD)(((QWORD)(qw))&0x00000000FFFFFFFF))
  #define HIDWORD(qw)      LODWORD((DWORD)(((QWORD)(qw))>>32))//__int64 is signed!
  #define MAKEI64(dw0,dw1) ((((QWORD)((DWORD)(dw1)))<<32) | ((DWORD)(dw0)))
#endif

#ifndef QWORD_MAX
#define QWORD_MAX (0xFFFFFFFFFFFFFFFFui64)
#endif

#ifndef QLONG_DEFINED
#define QLONG_DEFINED
  typedef signed __int64 QLONG;
#endif

#ifndef QLONG_MAX
#define QLONG_MAX (0x7FFFFFFFFFFFFFFFi64)
#endif
#ifndef QLONG_MIN
#define QLONG_MIN (0x8000000000000000i64)
#endif

//////////////////////////////////////////////////////////////////////
// macroses

#define ROR64(b) ((b)&1?((b)=(b)>>1,(b)|=0x8000000000000000i64,1):((b)=(b)>>1,0))
#define ROL64(b) ((b)&0x8000000000000000i64?((b)=(b)<<1,(b)|=1,1):((b)=(b)<<1,0))

#ifdef __cplusplus
///////////////////////////////////////////////////////////////////////////
// functions

// clp64(x) = 63 - nlz64(x) = [ log2(x) ] (round down)
// flp64(x) = 64-nlz64(x-1) = [ log2(x) ] (round up)

inline  QWORD flp64(QWORD x) //maximal N, that 2**N<=x  //Henry S. Warren, Jr. Hacker's Delight, p.59  NOTE: flp64(3)==2
{  
  x = x | (x >>  1);
  x = x | (x >>  2);
  x = x | (x >>  4);
  x = x | (x >>  8);
  x = x | (x >> 16);
  x = x | (x >> 32);
  return x - (x >> 1);
}

inline  QWORD clp64(QWORD x) //minimal N, that 2**N>=x  //Henry S. Warren, Jr. Hacker's Delight, p.60  NOTE: clp64(3)==4
{
  x = x - 1;
  x = x | (x >>  1);
  x = x | (x >>  2);
  x = x | (x >>  4);
  x = x | (x >>  8);
  x = x | (x >> 16);
  x = x | (x >> 32);
  return x + 1;
}

inline  QWORD _pop64(QWORD x) //count of non-zero bits  //Henry S. Warren, Jr. Hacker's Delight, p.80
{
  QWORD s = x;
  while(x) {
    x >>= 1;
    s -= x;
  }
  return s;
}

inline  QWORD pop64(QWORD x) //count of non-zero bits   //Henry S. Warren, Jr. Hacker's Delight, p.80
{
  static const char count[256] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,  
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,  
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,  
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,  
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,  
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,  
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,  
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,  
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,  
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,  
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,  
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,  
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,  
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,  
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,  
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
  };
  QWORD s = 
    count[(x >>  0) & 0xFF] +
    count[(x >>  8) & 0xFF] +
    count[(x >> 16) & 0xFF] +
    count[(x >> 24) & 0xFF] +
    count[(x >> 32) & 0xFF] +
    count[(x >> 40) & 0xFF] +
    count[(x >> 48) & 0xFF] +
    count[(x >> 56) & 0xFF];
  return s;
}

inline  QWORD nlz64(QWORD x) //count of head zero bits  //Henry S. Warren, Jr. Hacker's Delight, p.89
{
  x = x | (x >>  1);
  x = x | (x >>  2);
  x = x | (x >>  4);
  x = x | (x >>  8);
  x = x | (x >> 16);
  x = x | (x >> 32);
  return pop64(x);
}

inline  QWORD ntz64(QWORD x) //count of tail zero bits  //Henry S. Warren, Jr. Hacker's Delight, p.94
{
  QWORD n = 64;
  while(x) {
    n -= 1;
    x += x;
  }
  return n;
}

inline  QWORD bitsofsigned64(QLONG x)          //Henry S. Warren, Jr. Hacker's Delight, p.92
{
// bitsize(x) = count of bits signed additional code:
//   1, x=-1       or x=0     ,
//   2, x=-2       or x=1     ,
//   3, -4<=x<=-3  or 2<=x<=3 ,
//   4, -8<=x<=-5  or 4<=x<=7 ,
//   ...
//   64, -2^63<=x<=-2^62+1 or 2^62<=x<=2^63-1.
// shift is signed!
  QWORD s = x ^ (x >> 1);
  return 65 - nlz64(s);
}

inline  QWORD gray64(QWORD x) //Gray code of unsigned   //Henry S. Warren, Jr. Hacker's Delight, p.228
{
  QWORD g = x ^ (x >> 1);
  return g;
}

inline  QWORD ungray64(QWORD g) //Gray code to unsigned //Henry S. Warren, Jr. Hacker's Delight, p.229
{
  QWORD x = g ^ (g >> 1 );
        x = x ^ (x >> 2 );
        x = x ^ (x >> 4 );
        x = x ^ (x >> 8 );
        x = x ^ (x >> 16);
  return x;
}

inline  QWORD LOG64(QWORD x, QWORD* r=0/*<=0*/)//AY //round up   // log64(x) - r = x  //log(0)=64[0]  log(-1)=64[1]  log(0x8000001)=64[0x7FFFFFFF]  log(0x800000)=31[0]
{
  QWORD res  = clp64(x);
  r? *r = res - x :0;
  return nlz64(res - 1);
}

inline  QWORD log64(QWORD x, QWORD* r=0/*>=0*/)//AY //round down // loz64(x) + r = x  //log(0)=-1[0]  log(-1)=31[0x7FFFFFFF]  log(0x8000001)=31[1]  log(0x800000)=31[0]
{
  QWORD res  = flp64(x);
  r? *r = x - res :0;
  return nlz64(res) - 1;
}

inline  QWORD mask64(BYTE bits)//AY //no verflow calculation// mask64(1)=1, mask64(16)=0xFFFF, mask64(64)=0xFFFFFFFF
{
  QWORD  l = 1;
  QWORD  m = l << (bits-1);
  return m + (m - 1);
} //note: MASK64(QWORD x)==mask64(LOG64(x)), except 0;

inline void swap64(QWORD& x, QWORD& y)                         //Henry S. Warren, Jr. Hacker's Delight, p.51
{
  x = x ^ y;
  y = y ^ x;
  x = x ^ y;
}


inline QWORD clrlowbit64(QWORD x) // 0101I000=>0101O000, 0=>0  //Henry S. Warren, Jr. Hacker's Delight, p.25
{
  return x & (x-1);
}
inline QWORD getlowbit64(QWORD x) // 0101I000=>0O0OI000, 0=>0  //Henry S. Warren, Jr. Hacker's Delight, p.25
{
  return x & (-(QLONG)x);//== x & (~x+1)
}
inline QWORD getlowmask64(QWORD x)// 0101I000=>0000IIII, 0=>-1 //Henry S. Warren, Jr. Hacker's Delight, p.25
{
  return x ^ (x-1);
}


inline QWORD setlowzero64(QWORD x)// 1010O111=>1010I111, 0=>-1!//Henry S. Warren, Jr. Hacker's Delight, p.25
{
  return x | (x+1);
}
inline QWORD getlowzero64(QWORD x)// 1010O111=>0000IOOO,-1=>0  //Henry S. Warren, Jr. Hacker's Delight, p.25
{
  return ~x & (x+1);
}
inline QWORD getlowzeros64(QWORD x)//01011OOO=>00000III, 0=>-1 //Henry S. Warren, Jr. Hacker's Delight, p.25
{
  return ~x & (x-1);
}


inline QWORD filllowzeros64(QWORD x)//01011OOO=>01011III,0=>-1 //Henry S. Warren, Jr. Hacker's Delight, p.26
{
  return x | (x-1);
}
inline QWORD clrlowones64(QWORD x)// 010II000=>010OO000, 0=>-1 //Henry S. Warren, Jr. Hacker's Delight, p.26
{
  return ((x | (x-1)) + 1) & x;
}

inline QWORD ispower64(QWORD x)  // x = 2^N                    //Henry S. Warren, Jr. Hacker's Delight, p.25
{
  return (x&(x-1))==0; //see clrminbit64
}
inline QWORD ismask64(QWORD x)   // x = 2^N-1                  //Henry S. Warren, Jr. Hacker's Delight, p.25
{
  return (x&(x+1))==0;
}

inline QWORD ispowdiff64(QWORD x)// x = 2^N-2^J                //Henry S. Warren, Jr. Hacker's Delight, p.26
{
  return (((x|(x-1))+1)&x)==0; //see clrlowones64
}

///////////////////////////////////////////////////////////////////////////

inline QWORD possub64(QWORD a, QWORD b)
{
  return a>=b?a-b:0;
}

inline QWORD abssub64(QWORD a, QWORD b)
{
  return a>=b?a-b:b-a;
}

inline QLONG abs64(QLONG qw)
{
  return qw<0?-qw:qw;
}

inline double UInt64ToDbl(QWORD q)
{
  DWORD& lo = ((DWORD*)&q)[0];
  DWORD& hi = ((DWORD*)&q)[1];
  DWORD one = (lo&0x00000001);
  DWORD neg = (hi&0x80000000);
  if(neg)
    return one + 2.0*(double)(__int64)( q>>1 );//unsigned shift!
  return (double)(__int64)q;
}

//inline double UInt64ToDbl(QWORD q)
//{
//  if(q&0x8000000000000000i64)
//    { return ((double)(__int64)(q/2))*2.0 + ((q&1)?1.0:0.0); }
//  return (double)(__int64)q;
//}

//inline QWORD DblToUInt64(double d)
//{
//  QLONG q = (QLONG)d;
//  if(q&0x8000000000000000i64)
//    return 0;//signed underflow
//  return (QWORD) q;
//}

inline QWORD UInt64x64To64( // ATTENTION! x86 architecture dependent!
  QWORD nNumber,       // 64-bit unsigned multiplicand
  QWORD nNumerator,    // 64-bit unsigned multiplier
  QWORD nDenominator   // 64-bit unsigned divisor
)
{
  DWORD& dwlo1 = ((DWORD*)&nNumerator)[0];
  DWORD& dwhi1 = ((DWORD*)&nNumerator)[1];
  DWORD& dwlo2 = ((DWORD*)&nNumber)[0];
  DWORD& dwhi2 = ((DWORD*)&nNumber)[1];
  BOOL   bPos1 = dwhi1==0x00000000 && (dwlo1&0x10000000)==0;
  BOOL   bPos2 = dwhi2==0x00000000 && (dwlo2&0x10000000)==0;
  BOOL   bNeg1 = dwhi1==0xFFFFFFFF && (dwlo1&0x10000000)!=0;
  BOOL   bNeg2 = dwhi2==0xFFFFFFFF && (dwlo2&0x10000000)!=0;
  if((bPos1||bNeg1)&&(bPos2||bNeg2))//use 64-bit aryphmetics
    return (nNumber*nNumerator)/nDenominator;
  return (QWORD)( ((long double)nNumber)/((long double)(nDenominator))*((long double)(nNumerator)) );
}

inline QLONG MulDiv64( // ATTENTION! x86 architecture dependent!
  QLONG nNumber,       // 64-bit signed multiplicand
  QLONG nNumerator,    // 64-bit signed multiplier
  QLONG nDenominator   // 64-bit signed divisor
)
{
  ASSERT(nDenominator!=0);//AY 13.08.2014
  DWORD& dwlo1 = ((DWORD*)&nNumerator)[0];
  DWORD& dwhi1 = ((DWORD*)&nNumerator)[1];
  DWORD& dwlo2 = ((DWORD*)&nNumber)[0];
  DWORD& dwhi2 = ((DWORD*)&nNumber)[1];
  BOOL   bPos1 = dwhi1==0x00000000 && (dwlo1&0x10000000)==0;
  BOOL   bPos2 = dwhi2==0x00000000 && (dwlo2&0x10000000)==0;
  BOOL   bNeg1 = dwhi1==0xFFFFFFFF && (dwlo1&0x10000000)!=0;
  BOOL   bNeg2 = dwhi2==0xFFFFFFFF && (dwlo2&0x10000000)!=0;
  if((bPos1||bNeg1)&&(bPos2||bNeg2))//use 64-bit aryphmetics
    return (nNumber*nNumerator)/nDenominator;
  return (__int64)( ((long double)nNumber)/((long double)(nDenominator))*((long double)(nNumerator)) );
}

//if(0==((DWORD*)&nNumber)[1] || 0xFFFFFFFF==((DWORD*)&nNumber)[1])
//  if(0==((DWORD*)&nNumerator)[1] || 0xFFFFFFFF==((DWORD*)&nNumerator)[1])
//    return (nNumber*nNumerator)/nDenominator;
//DON'T WORK: Example: 0x9767C400*0xDBCE34EA<0!

inline QWORD sqrx64(QWORD X) // http://www.codenet.ru/progr/alg/sqrtint.php
{
  QWORD R;
  if    (X & 0xFFFFFFFF00000000i64){
    if  (X & 0xFFFF000000000000i64)
      if(X & 0xFF00000000000000i64)
         R = 0x000000003FFFFFFFi64;
      else
         R = 0x0000000003FFFFFFi64;
    else  // 0x0000FFFF00000000i64
      if(X & 0x0000FF0000000000i64)
         R = 0x00000000003FFFFFi64;
      else
         R = 0x000000000003FFFFi64;
  }else{  // 0x00000000FFFFFFFFi64
    if  (X & 0x00000000FFFF0000L)
      if(X & 0x00000000FF000000L)
         R = 0x0000000000003FFF;
      else
         R = 0x00000000000003FF;
    else
      if(X & 0x000000000000FF00)
         R = 0x000000000000003F;
      else
         R  = (X > 4) ? 7 : X;
  }
  return R;
}

inline QWORD align64(QWORD x, QWORD align=0)
{
  align = align?align:sizeof(QWORD);
  return x - x % align;
}


inline QWORD align64b(QWORD qw, DWORD dwAlign)
{                                                                  //dwAlign=1   //dwAlign=0
  ASSERT(pop64(dwAlign)==1);//check power of 2 form (as 0x10..0)   //TRUE        //FALSE
  DWORD dwMask = dwAlign - 1;   //make mask 0x10->0x0F             //0           //0xFFFFFFFF
  QWORD qwClr  = ~QWORD(dwMask);//make clen mask                   //0xF...FFFF  //0
  DWORD dwLow  = DWORD( qw );   //store low 32 bits                //
  qw &= qwClr;  //clear low bits                                   //qw          //0
  if(dwLow&dwMask)                                                 //FALSE       //FALSE
    qw += dwAlign;
  return qw;
  // if nAlign==1, will be return same value: ( (qw & (~0))  + 0 ),  dwMask=0, ~dwMask=0xFFFFFFFF
  // if nAlign==0, will be return 0:          ( (qw & ( 0))  + 0 ),  dwMask=0xFFFFFFFF, ~dwMask=0
}

inline QWORD sqrt64(QWORD X) //truncated   http://www.codenet.ru/progr/alg/sqrtint.php 
{
  QWORD R = X;
  QLONG B = X; 

  B = (QLONG)sqrx64(X); //3 iteration average on using this operator?
  while (X) 
  {
    B = (X/B + B)/2; //Newtons method, generally iteration count ~= ln(X)
    if(R > (QWORD) B)
      R = (QWORD) B;
    else
      return R;
  }
  return 0;
}

inline QWORD SQRT64(QWORD X) //rounded     http://www.codenet.ru/progr/alg/sqrtint.php
{
  QWORD R = X;
  QLONG B = X;
  QLONG T;

  B = (QLONG)sqrx64(X);
  while(X)
  {
    T = X/B + B;
    B =  T >>  1;
    B += T & 1;
    if(R > (QWORD) B)
      R = (QWORD) B;
    else
    {
      if(X/R==R-1 && X%R==0)
        R--;
      return R;
    }
  }
  return 0;
}


#endif//__cplusplus
#endif//__INT64_H
#pragma once
