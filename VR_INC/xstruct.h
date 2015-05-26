#ifndef __XSTRUCT_H
#define __XSTRUCT_H
#ifdef __cplusplus

#define DECLARE_STRUCT_EQ(STRUCT)\
  inline BOOL operator==(const STRUCT& s1, const STRUCT& s2) { return 0==memcmp(&s1,&s2,sizeof(s1)); }

#define DECLARE_STRUCT_NE(STRUCT)\
  inline BOOL operator!=(const STRUCT& s1, const STRUCT& s2) { return 0!=memcmp(&s1,&s2,sizeof(s1)); }

#define DECLARE_STRUCT_OP(STRUCT)\
  DECLARE_STRUCT_EQ(STRUCT)\
  DECLARE_STRUCT_NE(STRUCT)

#endif//__cplusplus
#endif//__XSTRUCT_H
#pragma once