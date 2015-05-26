#ifndef __YMATH_H
#define __YMATH_H
#include "yMathMax.h"
#include "yMathMin.h"

template <class T> __inline T ymax2(const T& e1, const T& e2, T m) //AY 20.07.2012
  { T m2 = e1>e2?e1:e2; return m2>m?m2:m; }

template <class T> __inline T ymin2(const T& e1, const T& e2, T m) //AY 20.07.2012
  { T m2 = e1<e2?e1:e2; return m2<m?m2:m; }

#endif//__YMATH_H
#pragma once