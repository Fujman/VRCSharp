#ifndef __YTYPE_H
#define __YTYPE_H

template <class INTEGER1, class INTEGER2=INTEGER1> class OP_RESULT;


#ifdef   __DSP32_MATH_H

#if !VS2010_VERSION//AY 17.01.2011
#define __int32 int
#define __int16 short
#define __int8  char
#include "YType.inl"
#undef  __int32
#undef  __int16
#undef  __int8
#endif

#include "YType.inl"

template <> class OP_RESULT<signed __int64,signed __int64> { public:
  typedef __int32               JUNIOR;
//typedef __int128              SENIOR;

  typedef __int80               ADD64K;
  typedef __int96               ADD4GB;
  typedef __int80               SUB;
  typedef __int80               ADD;
//typedef unsigned___int128     MUL;
//typedef unsigned___int128     SQUARE;
};

template <> class OP_RESULT<unsigned __int64,unsigned __int64> { public:
  typedef unsigned __int32      JUNIOR;
//typedef unsigned___int128     SENIOR;

  typedef unsigned___int80      ADD64K;
  typedef unsigned___int96      ADD4GB;
  typedef __int80               SUB;
  typedef unsigned___int80      ADD;
//typedef unsigned___int128     MUL;
//typedef unsigned___int128     SQUARE;
};
#endif// __DSP32_MATH_H

#endif//__YTYPE_H
#pragma once