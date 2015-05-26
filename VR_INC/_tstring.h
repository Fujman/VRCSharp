#ifndef ___TSTRING_H
#define ___TSTRING_H
#include <tchar.h>

//
//constant strings definition macro for templates
//
#define CSTR(CHAR,s) (sizeof(CHAR)==sizeof(char)?(const CHAR*)(s):(const CHAR*)(L ## s) )

#endif//___TSTRING_H
#pragma once