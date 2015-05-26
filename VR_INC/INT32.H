#ifndef __INT32_H
#define __INT32_H
///////////////////////////////////////////////////////////////////////

// ATTENTION! x86 architecture dependent!

///////////////////////////////////////////////////////////////////////
// types and constants

#ifndef BASETYPES
#ifndef DWORD
#define DWORD unsigned
#endif
#endif

#ifndef DWORD_MAX
#define DWORD_MAX (0xFFFFFFFF)
#endif

#ifndef DLONG_DEFINED
#define DLONG_DEFINED
  typedef signed DLONG;
#endif

#ifndef DLONG_MAX
#define DLONG_MAX (0x7FFFFFFF)
#endif
#ifndef DLONG_MIN
#define DLONG_MIN (0x80000000)
#endif

//////////////////////////////////////////////////////////////////////
// macroses

#define ROR32(b)   ((b)&1?((b)=(b)>>1,(b)|=0x80000000,1):((b)=(b)>>1,0))
#define ROL32(b)   ((b)&0x80000000?((b)=(b)<<1,(b)|=1,1):((b)=(b)<<1,0))

#define RCR32(b,c) ((b)&         1?( ((b)>>1)|((c)<<31) ,1):( ((b)>>1)|((c)<<31) ,0) ) //AY 03.11.2011 //not tested!
#define RCL32(b,c) ((b)&0x80000000?( ((b)<<1)|((c)&  1) ,1):( ((b)<<1)|((c)&  1) ,1) ) //AY 03.11.2011 //not tested!

#ifdef __cplusplus
//////////////////////////////////////////////////////////////////////
// functions

// clp32(x) = 31 - nlz32(x) = [ log2(x) ] (round down)
// flp32(x) = 32-nlz32(x-1) = [ log2(x) ] (round up)

inline  DWORD flp32(DWORD x) //maximal N, that 2**N<=x  //Henry S. Warren, Jr. Hacker's Delight, p.59  NOTE: flp32(3)==2
{  
  x = x | (x >>  1);
  x = x | (x >>  2);
  x = x | (x >>  4);
  x = x | (x >>  8);
  x = x | (x >> 16);
  return x - (x >> 1);
}

inline  DWORD clp32(DWORD x) //minimal N, that 2**N>=x  //Henry S. Warren, Jr. Hacker's Delight, p.60  NOTE: clp32(3)==4
{
  x = x - 1;
  x = x | (x >>  1);
  x = x | (x >>  2);
  x = x | (x >>  4);
  x = x | (x >>  8);
  x = x | (x >> 16);
  return x + 1;
}

inline  DWORD _pop32(DWORD x) //count of non-zero bits  //Henry S. Warren, Jr. Hacker's Delight, p.80
{
  DWORD s = x;
  while(x) {
    x >>= 1;
    s -= x;
  }
  return s;
}

inline  DWORD pop32(DWORD x) //count of non-zero bits   //Henry S. Warren, Jr. Hacker's Delight, p.80
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
  DWORD s = 
    count[(x >>  0) & 0xFF] +
    count[(x >>  8) & 0xFF] +
    count[(x >> 16) & 0xFF] +
    count[(x >> 24) & 0xFF];
  return s;
}

inline  DWORD nlz32(DWORD x) //count of head zero bits  //Henry S. Warren, Jr. Hacker's Delight, p.89
{
  x = x | (x >>  1);
  x = x | (x >>  2);
  x = x | (x >>  4);
  x = x | (x >>  8);
  x = x | (x >> 16);
  return pop32(x);
}

inline  DWORD ntz32(DWORD x) //count of tail zero bits  //Henry S. Warren, Jr. Hacker's Delight, p.94
{
  DWORD n = 32;
  while(x) {
    n -= 1;
    x += x;
  }
  return n;
}


inline  DWORD bitsofsigned32(DLONG x) //Henry S. Warren, Jr. Hacker's Delight, p.92
{
// bitsize(x) = count of bits signed additional code:
//   1, x=-1       or x=0     ,
//   2, x=-2       or x=1     ,
//   3, -4<=x<=-3  or 2<=x<=3 ,
//   4, -8<=x<=-5  or 4<=x<=7 ,
//   ...
//   32, -2^31<=x<=-2^30+1 or 2^30<=x<=2^31-1.
// shift is signed!
  DWORD s = x ^ (x >> 1);
  return 33 - nlz32(s);
}

inline  DWORD gray32(DWORD x) //Gray code of unsigned   //Henry S. Warren, Jr. Hacker's Delight, p.228
{
  DWORD g = x ^ (x >> 1);
  return g;
}

inline  DWORD ungray32(DWORD g) //Gray code to unsigned //Henry S. Warren, Jr. Hacker's Delight, p.229
{
  DWORD x = g ^ (g >> 1 );
        x = x ^ (x >> 2 );
        x = x ^ (x >> 4 );
        x = x ^ (x >> 8 );
        x = x ^ (x >> 16);
  return x;
}

inline  DWORD LOG32(DWORD x, DWORD* r=0/*<=0*/)//AY //round up   // log32(x) - r = x  //log(0)=32[0]  log(-1)=32[1]  log(0x8000001)=32[0x7FFFFFFF]  log(0x800000)=31[0]
{
  DWORD res  = clp32(x);
  r? *r = res - x :0;
  return nlz32(res - 1);
}

inline  DWORD log32(DWORD x, DWORD* r=0/*>=0*/)//AY //round down // loz32(x) + r = x  //log(0)=-1[0]  log(-1)=31[0x7FFFFFFF]  log(0x8000001)=31[1]  log(0x800000)=31[0]
{
  DWORD res  = flp32(x);
  r? *r = x - res :0;
  return nlz32(res) - 1;
}

inline  DWORD mask32(BYTE bits)//AY //no verflow calculation// mask32(1)=1, mask32(16)=0xFFFF, mask32(32)=0xFFFFFFFF
{
  DWORD  l = 1;
  DWORD  m = l << (bits-1);
  return m + (m - 1);
} //note: MASK32(DWORD x)==mask32(LOG32(x)), except 0;

inline void swap32(DWORD& x, DWORD& y)                         //Henry S. Warren, Jr. Hacker's Delight, p.51
{
  x = x ^ y;
  y = y ^ x;
  x = x ^ y;
}


inline DWORD clrlowbit32(DWORD x) // 0101I000=>0101O000, 0=>0  //Henry S. Warren, Jr. Hacker's Delight, p.25
{
  return x & (x-1);
}
inline DWORD getlowbit32(DWORD x) // 0101I000=>0O0OI000, 0=>0  //Henry S. Warren, Jr. Hacker's Delight, p.25
{
  return x & (-(DLONG)x);//== x & (~x+1)
}
inline DWORD getlowmask32(DWORD x)// 0101I000=>0000IIII, 0=>-1 //Henry S. Warren, Jr. Hacker's Delight, p.25
{
  return x ^ (x-1);
}


inline DWORD setlowzero32(DWORD x)// 1010O111=>1010I111, 0=>-1!//Henry S. Warren, Jr. Hacker's Delight, p.25
{
  return x | (x+1);
}
inline DWORD getlowzero32(DWORD x)// 1010O111=>0000IOOO,-1=>0  //Henry S. Warren, Jr. Hacker's Delight, p.25
{
  return ~x & (x+1);
}
inline DWORD getlowzeros32(DWORD x)//01011OOO=>00000III, 0=>-1 //Henry S. Warren, Jr. Hacker's Delight, p.25
{
  return ~x & (x-1);
}


inline DWORD filllowzeros32(DWORD x)//01011OOO=>01011III,0=>-1 //Henry S. Warren, Jr. Hacker's Delight, p.26
{
  return x | (x-1);
}
inline DWORD clrlowones32(DWORD x)// 010II000=>010OO000, 0=>-1 //Henry S. Warren, Jr. Hacker's Delight, p.26
{
  return ((x | (x-1)) + 1) & x;
}

inline DWORD ispower32(DWORD x)  // x = 2^N                    //Henry S. Warren, Jr. Hacker's Delight, p.25
{
  return (x&(x-1))==0; //see clrminbit32
}
inline DWORD ismask32(DWORD x)   // x = 2^N-1                  //Henry S. Warren, Jr. Hacker's Delight, p.25
{
  return (x&(x+1))==0;
}

inline DWORD ispowdiff32(DWORD x)// x = 2^N-2^J                //Henry S. Warren, Jr. Hacker's Delight, p.26
{
  return (((x|(x-1))+1)&x)==0; //see clrlowones32
}

#pragma warning(disable:4035)

__inline DLONG abs32(DLONG x)
{
  __asm MOV EAX, x
  __asm CDQ
  __asm XOR EAX, EDX
  __asm SUB EAX, EDX
  //return   EAX
}

__inline DLONG imuldiv32(DLONG a, DLONG b, BYTE c)//a*b/2^c
{
  __asm MOV  EAX, a
  __asm MOV  EDX, b
  __asm MOV  CL,  c
  __asm IMUL EDX
  __asm SHRD EAX, EDX, CL
  //return   EAX
} 

__inline DWORD muldiv32(DWORD a, DWORD b, BYTE c)//a*b/2^c
{
  __asm MOV  EAX, a
  __asm MOV  EDX, b
  __asm MOV  CL,  c
  __asm MUL  EDX
  __asm SHRD EAX, EDX, CL
  //return   EAX
}

__inline DLONG __fastcall idivmul32(DLONG C, DLONG A, DLONG B)//a*b/2^c - same as imuldiv32, but more faster, a may be constant
{
  __asm MOV  EDX, A
  __asm MOV  EAX, B
  __asm MOV  ECX, C
  __asm IMUL EDX
  __asm SHRD EAX, EDX, CL
  //return   EAX
} 

__inline DWORD __fastcall divmul32(DWORD C, DWORD A, DWORD B)//a*b/2^c - same as imuldiv32, but more faster, a may be constant
{
  __asm MOV  EDX, A
  __asm MOV  EAX, B
  __asm MOV  ECX, C
  __asm MUL  EDX
  __asm SHRD EAX, EDX, CL
  //return   EAX
} 

//AY 08.12.2010
#define MULDIV32UP(a,b,c)  (DWORD( (unsigned __int64(a)*(b)+(c)-1)/(c) )) //round to up
#define MULDIV32DN(a,b,c)  (DWORD( (unsigned __int64(a)*(b)      )/(c) )) //round to down
#define IMULDIV32UP(a,b,c) (DLONG( (         __int64(a)*(b)+(c)-1)/(c) )) //round to up
#define IMULDIV32DN(a,b,c) (DLONG( (         __int64(a)*(b)      )/(c) )) //round to down


#pragma warning(default:4035)


inline DWORD align32(DWORD x, DWORD align=0)
{
  align = align?align:sizeof(DWORD);
  return x - x % align;
}

inline DWORD align32b(DWORD dw, DWORD dwAlign)
{
  ASSERT(pop32(dwAlign)==1);//check power of 2 form (as 0x10..0)
  DWORD dwMask = dwAlign - 1;   //make mask 0x10->0x0F
  DWORD dwClr  = ~dwMask;       //make clean mask
  DWORD dwLow  = DWORD( dw );   //store
  dw &= dwClr;  //clear low bits
  if(dwLow&dwMask)
    dw += dwAlign;
  return dw;
}


inline DWORD sqrx32(DWORD X) // http://www.codenet.ru/progr/alg/sqrtint.php
{
  DWORD R;
  if(X & 0xFFFF0000L)
    if(X & 0xFF000000L)
       R = 0x3FFF;
    else
       R = 0x03FF;
  else
    if(X & 0xFF00)
      R = 0x003F;
    else
      R  = (X > 4) ? 7 : X;
  return R;
}

inline DWORD sqrt32(DWORD X) //truncated   http://www.codenet.ru/progr/alg/sqrtint.php 
{
  DWORD R = X;
  DLONG B = X; 

  B = (DLONG)sqrx32(X); //3 iteration average on using this operator
  while (X) 
  {
    B = (X/B + B)/2; //Newtons method, generally iteration count ~= ln(X)
    if(R > (DWORD) B)
      R = (DWORD) B;
    else
      return R;
  }
  return 0;
}

inline DWORD SQRT32(DWORD X) //rounded     http://www.codenet.ru/progr/alg/sqrtint.php
{
  DWORD R = X;
  DLONG B = X;
  DLONG T;

  B = (DLONG)sqrx32(X);
  while(X)
  {
    T = X/B + B;
    B =  T >>  1;
    B += T & 1;
    if(R > (DWORD) B)
      R = (DWORD) B;
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
#endif//__INT32_H
#pragma once
