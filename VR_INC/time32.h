#ifndef __TIME32_H
#define __TIME32_H
#include <time.h>

#ifdef _TIME32_T_DEFINED //VS2010
typedef __time32_t TIME_T;
typedef __time64_t __TIME_T;
#else
typedef time_t     TIME_T;
typedef time_t     __TIME_T;
#endif//_TIME32_T_DEFINED

#endif//__TIME32_H
#pragma once
