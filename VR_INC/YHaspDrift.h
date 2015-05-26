#ifndef __YHASPDRIFT_H
#define __YHASPDRIFT_H
#include "YTime.h"

// C++ section /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
#ifdef __cplusplus

////////////////////////////////////////////////////////////////////////////////////
// YHaspDrift

class YHaspDrift
{
public:
  static YTimeSpan      CheckDrift();
  static YTimeSpan      GetDrift();
  static YTimeSpan      ResetDrift();
};

#endif//__cplusplus
////////////////////////////////////////////////////////////////////////////////////

#endif//__YHASPDRIFT_H
#pragma once
